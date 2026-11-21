#include "synth_emulator.h"
#include "audio_output.h"
#include <QDebug>
#include <cmath>
#include <algorithm>

SynthEmulator::SynthEmulator(QObject *parent)
  : QObject(parent), audioOut(nullptr), currentInstrument(0), activeVoices(0) {

  initAudioOutput();
  qDebug() << "SynthEmulator initialized";
}

SynthEmulator::~SynthEmulator() {
  if (audioOut) {
    delete audioOut;
  }
}

void SynthEmulator::initAudioOutput() {
  audioOut = new AudioOutput(this);
  if (!audioOut->initialize(44100, 2)) {
    qWarning() << "Failed to initialize audio output";
  } else {
    qDebug() << "Audio output initialized successfully";
  }
}

void SynthEmulator::playNote(int midiNote, int velocity) {
  qDebug() << "Playing MIDI note:" << midiNote << "velocity:" << velocity;

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
  qDebug() << "Stopped MIDI note:" << midiNote;
}

void SynthEmulator::stopAllNotes() {
  activeNotes.clear();
  activeVoices = 0;
}

void SynthEmulator::setInstrument(int index) {
  currentInstrument = index;
  qDebug() << "Instrument set to:" << index;
}

void SynthEmulator::setReverb(float amount) {
  if (audioOut) {
    // Will be implemented in audio effects chain
    qDebug() << "Reverb set to:" << amount;
  }
}

void SynthEmulator::setChorus(float amount) {
  if (audioOut) {
    // Will be implemented in audio effects chain
    qDebug() << "Chorus set to:" << amount;
  }
}

void SynthEmulator::generateTone(int midiNote, int velocity) {
  // Convert MIDI note to frequency
  // Frequency = 440 * 2^((note - 69) / 12)
  double frequency = 440.0 * std::pow(2.0, (midiNote - 69) / 12.0);

  qDebug() << "Generating tone at" << frequency << "Hz with velocity" << velocity;

  if (audioOut) {
    // Send to audio output for synthesis
    // This will be expanded with actual DSP code
    audioOut->playTone(frequency, 0.5f * (velocity / 127.0f));
  }
}
