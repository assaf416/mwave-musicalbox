#include "midi_input.h"
#include <iostream>

MidiInput::MidiInput()
  : isListening(false) {
}

MidiInput::~MidiInput() {
  stopListening();
}

bool MidiInput::initialize() {
  std::cout << "[MidiInput] Initialized\n";
  return true;
}

void MidiInput::startListening() {
  isListening = true;
  std::cout << "[MidiInput] Started listening\n";
}

void MidiInput::stopListening() {
  isListening = false;
  std::cout << "[MidiInput] Stopped listening\n";
}
