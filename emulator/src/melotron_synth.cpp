#include "melotron_synth.h"
#include "soundfont_loader.h"
#include <iostream>
#include <cmath>
#include <algorithm>

MelotronSynth::MelotronSynth()
  : soundFont(nullptr), currentTapeVoice(VOICE_VIOLINS),
    tapeSaturation(0.0f), reverbAmount(0.5f) {
}

MelotronSynth::~MelotronSynth() {
}

bool MelotronSynth::initialize(const std::string& sf2Path) {
  std::cout << "[MelotronSynth] Initializing with SoundFont: " << sf2Path << "\n";

  soundFont = std::make_unique<SoundFontLoader>();
  if (!soundFont->load(sf2Path)) {
    std::cerr << "[MelotronSynth] Failed to load SoundFont\n";
    return false;
  }

  std::cout << "[MelotronSynth] Available tapes:\n";
  auto names = soundFont->getInstrumentNames();
  for (size_t i = 0; i < names.size(); ++i) {
    std::cout << "  [" << i << "] " << names[i] << "\n";
  }

  std::cout << "[MelotronSynth] Ready with " << names.size() << " tape voices\n";
  return true;
}

int MelotronSynth::playNote(uint8_t midiNote, uint8_t velocity) {
  std::cout << "[MelotronSynth] Playing MIDI note: " << (int)midiNote
    << " velocity: " << (int)velocity << " on tape: "
    << (int)currentTapeVoice << "\n";

  if (!soundFont || activeVoices.size() >= MAX_VOICES) {
    std::cerr << "[MelotronSynth] Cannot play note: SoundFont not loaded or max voices reached\n";
    return -1;
  }

  Voice voice;
  voice.active = true;
  voice.midiNote = midiNote;
  voice.velocity = velocity;
  voice.position = 0.0f;
  voice.pitchShift = 1.0f;
  voice.amplitude = 1.0f;
  voice.attackTime = 0.05f;  // 50ms attack
  voice.releaseTime = 0.5f;  // 500ms release
  voice.tapeVoice = currentTapeVoice;

  activeVoices.push_back(voice);

  return activeVoices.size() - 1;
}

void MelotronSynth::stopNote(uint8_t midiNote) {
  for (auto& voice : activeVoices) {
    if (voice.midiNote == midiNote && voice.active) {
      voice.active = false;
      std::cout << "[MelotronSynth] Stopped MIDI note: " << (int)midiNote << "\n";
      break;
    }
  }
}

void MelotronSynth::stopAllNotes() {
  std::cout << "[MelotronSynth] Stopping all " << activeVoices.size() << " voices\n";
  activeVoices.clear();
}

void MelotronSynth::setTapeVoice(TapeVoice voice) {
  currentTapeVoice = voice;

  const char* voiceNames[] = { "Violins", "Choir", "Flute", "All Layers" };
  std::cout << "[MelotronSynth] Tape voice changed to: " << voiceNames[voice] << "\n";
}

void MelotronSynth::setTapeSaturation(float saturation) {
  tapeSaturation = std::clamp(saturation, 0.0f, 1.0f);
  std::cout << "[MelotronSynth] Tape saturation: " << (tapeSaturation * 100.0f) << "%\n";
}

void MelotronSynth::setReverb(float amount) {
  reverbAmount = std::clamp(amount, 0.0f, 1.0f);
  std::cout << "[MelotronSynth] Reverb amount: " << (reverbAmount * 100.0f) << "%\n";
}

Instrument* MelotronSynth::getInstrumentForVoice(TapeVoice voice) {
  if (!soundFont) return nullptr;

  switch (voice) {
    case VOICE_VIOLINS:
      return soundFont->getInstrumentByName("Violins");
    case VOICE_CHOIR:
      return soundFont->getInstrumentByName("Choir");
    case VOICE_FLUTE:
      return soundFont->getInstrumentByName("Flute");
    case VOICE_ALL_LAYERS:
      return soundFont->getInstrumentByName("Violins"); // Default to violins, could blend
    default:
      return nullptr;
  }
}

void MelotronSynth::process(float* buffer, int numSamples) {
  // Initialize buffer to silence
  std::fill(buffer, buffer + numSamples, 0.0f);

  // Process active voices
  for (auto& voice : activeVoices) {
    if (!voice.active) continue;

    processTapePlayback(voice, buffer, numSamples);
  }

  // Remove inactive voices
  activeVoices.erase(
    std::remove_if(activeVoices.begin(), activeVoices.end(),
      [](const Voice& v) { return !v.active; }),
    activeVoices.end()
  );
}

void MelotronSynth::processTapePlayback(Voice& voice, float* buffer, int numSamples) {
  Instrument* instrument = getInstrumentForVoice((TapeVoice)voice.tapeVoice);
  if (!instrument) return;

  Sample* sample = soundFont->getSampleForNote(instrument, voice.midiNote);
  if (!sample || sample->data.empty() || !sample->valid) {
    std::cerr << "[MelotronSynth] No valid sample data for note " << (int)voice.midiNote << "\n";
    voice.active = false;
    return;
  }

  // Calculate pitch shift: playback_rate = 2^((MIDI_note - original_pitch) / 12)
  int originalPitch = sample->originalPitch;
  int semitoneDiff = voice.midiNote - originalPitch;
  voice.pitchShift = std::pow(2.0f, semitoneDiff / 12.0f);

  uint32_t loopStart = sample->startLoop;
  uint32_t loopEnd = sample->endLoop;
  uint32_t sampleLength = sample->data.size();
  bool hasLoop = (loopEnd > loopStart) && (loopEnd <= sampleLength);

  for (int i = 0; i < numSamples; ++i) {
    if (!voice.active) break;

    // Update envelope (attack/release)
    if (voice.amplitude < 1.0f) {
      voice.amplitude += (1.0f / (voice.attackTime * 48000.0f));
      voice.amplitude = std::min(1.0f, voice.amplitude);
    }

    // Convert normalized position (0-1) to sample index
    float samplePos = voice.position * sampleLength;

    // Handle looping
    if (hasLoop && samplePos >= loopEnd) {
      float loopLength = loopEnd - loopStart;
      samplePos = loopStart + std::fmod(samplePos - loopStart, loopLength);
    }

    uint32_t sampleIndex = (uint32_t)samplePos;
    if (sampleIndex >= sampleLength) {
      voice.active = false;
      break;
    }

    // Linear interpolation for smooth pitch shifting
    float frac = samplePos - sampleIndex;
    float sample_value = sample->data[sampleIndex];

    if (sampleIndex + 1 < sampleLength) {
      float nextSample = sample->data[sampleIndex + 1];
      sample_value = sample_value * (1.0f - frac) + nextSample * frac;
    }

    // Apply tape saturation
    sample_value = applySaturation(sample_value, tapeSaturation);

    // Apply velocity and envelope
    sample_value *= (voice.velocity / 127.0f) * voice.amplitude;

    // Apply reverb
    sample_value = applyReverb(sample_value, reverbAmount);

    // Add to output buffer (clamp to prevent clipping)
    buffer[i] += std::clamp(sample_value, -1.0f, 1.0f);

    // Advance tape position with pitch shift
    voice.position += (voice.pitchShift / 48000.0f);

    // Check if tape has finished (without looping)
    if (!hasLoop && voice.position >= 1.0f) {
      voice.active = false;
      break;
    }
  }
}

float MelotronSynth::applySaturation(float sample, float saturation) {
  if (saturation <= 0.0f) return sample;

  // Soft clipping saturation
  float drive = 1.0f + (saturation * 10.0f);
  float saturated = sample * drive;

  // Soft clipping with tanh-like behavior
  saturated = (2.0f / M_PI) * std::atan(saturated);

  return saturated;
}

float MelotronSynth::applyReverb(float sample, float amount) {
  // Simple reverb simulation (placeholder)
  // In production, use Freeverb or similar algorithm
  return sample * (1.0f - amount * 0.3f);
}
