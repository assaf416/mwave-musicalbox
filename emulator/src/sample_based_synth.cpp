#include "sample_based_synth.h"
#include "wav_sample_loader.h"
#include <cmath>
#include <iostream>
#include <algorithm>

SampleBasedSynth::SampleBasedSynth()
    : wavLoader(std::make_unique<WavSampleLoader>()),
      currentInstrument(MELLOTRON),
      reverbAmount(0.5f),
      sampleRate(SAMPLE_RATE) {}

SampleBasedSynth::~SampleBasedSynth() {}

bool SampleBasedSynth::initialize(const std::string& wavDir) {
  // Load instrument presets from WAV directories
  std::string pianoDir = wavDir + "/my-pianos-wav";
  std::string mellotronDir = wavDir + "/mellotron-wav";

  // Load pianos (using different preset ranges for different variations)
  if (!wavLoader->loadInstrumentFromWavDirectory(pianoDir, "Piano", 0, 0)) {
    std::cerr << "Warning: Could not load Piano samples from " << pianoDir << std::endl;
  }

  if (!wavLoader->loadInstrumentFromWavDirectory(pianoDir, "Electric Piano 1", 0, 4)) {
    std::cerr << "Warning: Could not load Electric Piano 1 samples" << std::endl;
  }

  if (!wavLoader->loadInstrumentFromWavDirectory(pianoDir, "Electric Piano 2", 0, 5)) {
    std::cerr << "Warning: Could not load Electric Piano 2 samples" << std::endl;
  }

  // Load mellotron
  if (!wavLoader->loadInstrumentFromWavDirectory(mellotronDir, "Mellotron", 0, 48)) {
    std::cerr << "Warning: Could not load Mellotron samples from " << mellotronDir << std::endl;
    return false;
  }

  std::cout << "SampleBasedSynth initialized successfully with "
            << wavLoader->getInstrumentCount() << " instruments" << std::endl;

  return wavLoader->getInstrumentCount() > 0;
}

int SampleBasedSynth::playNote(uint8_t midiNote, uint8_t velocity) {
  if (activeVoices.size() >= MAX_VOICES) {
    // Stop the oldest voice
    activeVoices.erase(activeVoices.begin());
  }

  Voice voice;
  voice.active = true;
  voice.midiNote = midiNote;
  voice.velocity = velocity;
  voice.position = 0.0f;
  voice.pitchShift = 1.0f;
  voice.amplitude = velocity / 127.0f;
  voice.velocity_normalized = velocity / 127.0f;
  voice.attackSamples = sampleRate * 0.01f;  // 10ms attack
  voice.releaseSamples = sampleRate * 0.1f;  // 100ms release
  voice.noteStartSample = 0;
  voice.isReleasing = false;
  voice.releaseStartSample = 0;

  activeVoices.push_back(voice);
  return activeVoices.size() - 1;
}

void SampleBasedSynth::stopNote(uint8_t midiNote) {
  for (auto& voice : activeVoices) {
    if (voice.active && voice.midiNote == midiNote) {
      voice.isReleasing = true;
      voice.releaseStartSample = voice.noteStartSample;
    }
  }
}

void SampleBasedSynth::stopAllNotes() {
  for (auto& voice : activeVoices) {
    voice.active = false;
  }
  activeVoices.clear();
}

void SampleBasedSynth::setInstrument(Instrument instrument) {
  currentInstrument = instrument;
}

InstrumentPreset* SampleBasedSynth::getCurrentInstrumentPreset() {
  const char* instrumentNames[] = {"Piano", "Electric Piano 1", "Electric Piano 2", "Mellotron"};
  return wavLoader->getInstrumentByName(instrumentNames[currentInstrument]);
}

void SampleBasedSynth::process(float* buffer, int numSamples) {
  // Clear output buffer
  std::fill(buffer, buffer + numSamples, 0.0f);

  InstrumentPreset* currentInst = getCurrentInstrumentPreset();
  if (!currentInst) {
    return;
  }

  // Process each active voice
  std::vector<Voice> voicesToRemove;
  for (size_t i = 0; i < activeVoices.size(); ++i) {
    Voice& voice = activeVoices[i];
    if (!voice.active) {
      voicesToRemove.push_back(voice);
      continue;
    }

    processVoice(voice, buffer, numSamples);
    voice.noteStartSample += numSamples;

    // Check if release is complete
    if (voice.isReleasing &&
        (voice.noteStartSample - voice.releaseStartSample) > voice.releaseSamples) {
      voice.active = false;
      voicesToRemove.push_back(voice);
    }
  }

  // Remove inactive voices
  for (const auto& voiceToRemove : voicesToRemove) {
    auto it = std::find_if(activeVoices.begin(), activeVoices.end(),
                          [&voiceToRemove](const Voice& v) {
                            return v.midiNote == voiceToRemove.midiNote &&
                                   v.noteStartSample == voiceToRemove.noteStartSample;
                          });
    if (it != activeVoices.end()) {
      activeVoices.erase(it);
    }
  }
}

void SampleBasedSynth::processVoice(Voice& voice, float* buffer, int numSamples) {
  InstrumentPreset* currentInst = getCurrentInstrumentPreset();
  if (!currentInst) return;

  WavSample* sample = wavLoader->getSampleForNote(currentInst, voice.midiNote);
  if (!sample || !sample->valid) return;

  float sampleDuration = sample->data.size() / (float)sample->sampleRate;
  float samplePlaybackSpeed = 1.0f;  // Can adjust for pitch if needed

  for (int i = 0; i < numSamples; ++i) {
    if (!voice.active) break;

    // Get current envelope value
    float envelope = getEnvelopeValue(voice, i);
    voice.amplitude = envelope * voice.velocity_normalized;

    // Interpolate sample
    float sampleValue = interpolateSample(sample, voice.position);

    // Apply amplitude
    sampleValue *= voice.amplitude;

    // Add to output buffer
    buffer[i] += sampleValue * 0.5f;  // Scale down to prevent clipping

    // Advance position
    voice.position += samplePlaybackSpeed / sample->sampleRate * sampleRate;

    // Loop or stop at end of sample
    if (voice.position >= 1.0f) {
      voice.position = std::fmod(voice.position, 1.0f);
    }
  }
}

float SampleBasedSynth::getEnvelopeValue(const Voice& voice, int sampleIndex) {
  int currentSample = sampleIndex;

  if (!voice.isReleasing) {
    // Attack phase
    if (currentSample < voice.attackSamples) {
      return currentSample / (float)voice.attackSamples;
    }
    return 1.0f;
  } else {
    // Release phase
    int releaseElapsed = currentSample + (voice.noteStartSample - voice.releaseStartSample);
    if (releaseElapsed >= voice.releaseSamples) {
      return 0.0f;
    }
    return 1.0f - (releaseElapsed / (float)voice.releaseSamples);
  }
}

float SampleBasedSynth::interpolateSample(const WavSample* sample, float position) {
  if (!sample || sample->data.empty()) {
    return 0.0f;
  }

  position = std::clamp(position, 0.0f, 0.9999f);
  size_t index = (size_t)(position * sample->data.size());
  size_t nextIndex = std::min(index + 1, sample->data.size() - 1);
  float fraction = (position * sample->data.size()) - index;

  float current = sample->data[index];
  float next = sample->data[nextIndex];

  return current + (next - current) * fraction;
}

void SampleBasedSynth::setReverb(float amount) {
  reverbAmount = std::clamp(amount, 0.0f, 1.0f);
}

std::vector<std::string> SampleBasedSynth::getAvailableInstruments() const {
  return wavLoader->getInstrumentNames();
}
