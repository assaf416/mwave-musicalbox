#ifndef SYNTH_EMULATOR_H
#define SYNTH_EMULATOR_H

#include <vector>
#include <memory>

class AudioOutput;
class MelotronSynth;

class SynthEmulator {
public:
  SynthEmulator();
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

  std::unique_ptr<AudioOutput> audioOut;
  std::unique_ptr<MelotronSynth> melotron;
  int currentInstrument;
  int activeVoices;
  std::vector<int> activeNotes;
  bool melotronInitialized;
};

#endif // SYNTH_EMULATOR_H
