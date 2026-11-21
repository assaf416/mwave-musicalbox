#ifndef MIDI_INPUT_H
#define MIDI_INPUT_H

#include <QObject>

class MidiInput : public QObject {
  Q_OBJECT

public:
  explicit MidiInput(QObject *parent = nullptr);
  ~MidiInput();

  bool initialize();
  void startListening();
  void stopListening();

signals:
  void noteOn(int channel, int note, int velocity);
  void noteOff(int channel, int note);
  void controlChange(int channel, int controller, int value);

private:
  bool isListening;
};

#endif // MIDI_INPUT_H
