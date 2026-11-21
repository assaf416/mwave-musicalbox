#include "synth_emulator.h"
#include "audio_output.h"
#include <iostream>
#include <cmath>
#include <algorithm>

SynthEmulator::SynthEmulator()
  : audioOut(nullptr), currentInstrument(0), activeVoices(0) {

  initAudioOutput();
  std::cout << "[SynthEmulator] Initialized\n";
}

SynthEmulator::~SynthEmulator() {
  // unique_ptr automatically deletes
}

void SynthEmulator::initAudioOutput() {
  audioOut = std::make_unique<AudioOutput>();
  if (!audioOut->initialize(44100, 2)) {
    std::cerr << "[AudioOutput] Initialization failed\n";
  } else {
    std::cout << "[AudioOutput] Audio output initialized successfully\n";
  }
}

void SynthEmulator::playNote(int midiNote, int velocity) {
  std::cout << "[SynthEmulator] Playing MIDI note: " << midiNote << " velocity: " << velocity << "\n";

  // Add to active notes
  if (std::find(activeNotes.begin(), activeNotes.end(), midiNote) == activeNotes.end()) {
    activeNotes.push_back(midiNote);
    activeVoices = activeNotes.size();
  }

  generateTone(midiNote, velocity);
}

void SynthEmulator::stopNote(int midiNote) {
  auto it = std::find(activeNotes.begin(), activeNotes.end(), midiNote);
  if (it != activeNotes.end()) {
    activeNotes.erase(it);
    activeVoices = activeNotes.size();
  }
  std::cout << "[SynthEmulator] Stopped MIDI note: " << midiNote << "\n";
}

void SynthEmulator::stopAllNotes() {
  activeNotes.clear();
  activeVoices = 0;
  std::cout << "[SynthEmulator] All notes stopped\n";
}

void SynthEmulator::setInstrument(int index) {
  currentInstrument = index;
  std::cout << "[SynthEmulator] Instrument set to: " << index << "\n";
}

void SynthEmulator::setReverb(float amount) {
  if (audioOut) {
    // Will be implemented in audio effects chain
    std::cout << "[Effects] Reverb set to: " << (amount * 100.0f) << "%\n";
  }
}

void SynthEmulator::setChorus(float amount) {
  if (audioOut) {
    // Will be implemented in audio effects chain
    std::cout << "[Effects] Chorus set to: " << (amount * 100.0f) << "%\n";
  }
}

void SynthEmulator::generateTone(int midiNote, int velocity) {
  // Convert MIDI note to frequency
  // Frequency = 440 * 2^((note - 69) / 12)
  double frequency = 440.0 * std::pow(2.0, (midiNote - 69) / 12.0);

  std::cout << "[Synth] Generating tone at " << frequency << " Hz with velocity " << velocity << "\n";

  if (audioOut) {
    // Send to audio output for synthesis
    // This will be expanded with actual DSP code
    audioOut->playTone(frequency, 0.5f * (velocity / 127.0f));
  }
}
