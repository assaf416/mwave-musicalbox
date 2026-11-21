#ifndef MIDI_INPUT_H
#define MIDI_INPUT_H

class MidiInput {
public:
  MidiInput();
  ~MidiInput();

  bool initialize();
  void startListening();
  void stopListening();

private:
  bool isListening;
};

#endif // MIDI_INPUT_H
