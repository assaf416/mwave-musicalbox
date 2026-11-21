#ifndef SYNTH_EMULATOR_H
#define SYNTH_EMULATOR_H

#include <QObject>
#include <vector>

class AudioOutput;

class SynthEmulator : public QObject {
  Q_OBJECT

public:
  explicit SynthEmulator(QObject *parent = nullptr);
  ~SynthEmulator();

  // Playback control
  void playNote(int midiNote, int velocity = 100);
  void stopNote(int midiNote);
  void stopAllNotes();

  // Instrument selection
  void setInstrument(int index);

  // Effects
  void setReverb(float amount);
  void setChorus(float amount);

  // Status
  int getActiveVoiceCount() const { return activeVoices; }

private:
  void initAudioOutput();
  void generateTone(int midiNote, int velocity);

  AudioOutput *audioOut;
  int currentInstrument;
  int activeVoices;
  std::vector<int> activeNotes;
};

#endif // SYNTH_EMULATOR_H
