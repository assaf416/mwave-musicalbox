#include "midi_input.h"
#include <QDebug>

MidiInput::MidiInput(QObject *parent)
  : QObject(parent), isListening(false) {
}

MidiInput::~MidiInput() {
  stopListening();
}

bool MidiInput::initialize() {
  qDebug() << "MIDI Input initialized";
  return true;
}

void MidiInput::startListening() {
  isListening = true;
  qDebug() << "MIDI Input started listening";
}

void MidiInput::stopListening() {
  isListening = false;
  qDebug() << "MIDI Input stopped listening";
}
