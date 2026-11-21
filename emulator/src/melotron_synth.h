#ifndef MELOTRON_SYNTH_H
#define MELOTRON_SYNTH_H

#include <cstdint>
#include <memory>
#include <vector>

class SoundFontLoader;
struct Sample;
struct Instrument;

class MelotronSynth {
public:
  enum TapeVoice {
    VOICE_VIOLINS = 0,
    VOICE_CHOIR = 1,
    VOICE_FLUTE = 2,
    VOICE_ALL_LAYERS = 3
  };

  MelotronSynth();
  ~MelotronSynth();

  /**
   * Initialize Melotron with SoundFont2 file
   * @param sf2Path Path to Mellotron.sf2 file
   * @return true if successful
   */
  bool initialize(const std::string& sf2Path);

  /**
   * Play a MIDI note
   * @param midiNote MIDI note number (0-127)
   * @param velocity Velocity (1-127)
   * @return Voice ID for this note
   */
  int playNote(uint8_t midiNote, uint8_t velocity);

  /**
   * Stop a MIDI note
   * @param midiNote MIDI note number
   */
  void stopNote(uint8_t midiNote);

  /**
   * Stop all notes
   */
  void stopAllNotes();

  /**
   * Set tape voice/tape selection
   * @param voice Tape voice (Violins/Choir/Flute/All)
   */
  void setTapeVoice(TapeVoice voice);

  /**
   * Set tape saturation (warmth/color)
   * @param saturation 0.0 (clean) to 1.0 (saturated)
   */
  void setTapeSaturation(float saturation);

  /**
   * Set reverb amount
   * @param amount 0.0 (dry) to 1.0 (wet)
   */
  void setReverb(float amount);

  /**
   * Process audio and generate samples
   * @param buffer Output buffer for audio samples
   * @param numSamples Number of samples to generate
   */
  void process(float* buffer, int numSamples);

  /**
   * Get active voice count
   * @return Number of currently playing voices
   */
  int getActiveVoiceCount() const { return activeVoices.size(); }

  /**
   * Get currently selected tape voice
   * @return Current TapeVoice
   */
  TapeVoice getCurrentTapeVoice() const { return currentTapeVoice; }

private:
  struct Voice {
    bool active;
    uint8_t midiNote;
    uint8_t velocity;
    float position;        // Sample position (0.0 to 1.0)
    float pitchShift;      // Pitch shift factor
    float amplitude;       // Current amplitude envelope
    float attackTime;      // Attack envelope time
    float releaseTime;     // Release envelope time
    int tapeVoice;         // Which tape was playing
  };

  std::unique_ptr<SoundFontLoader> soundFont;
  std::vector<Voice> activeVoices;
  TapeVoice currentTapeVoice;
  float tapeSaturation;
  float reverbAmount;

  // Sample playback
  Instrument* getInstrumentForVoice(TapeVoice voice);
  void processTapePlayback(Voice& voice, float* buffer, int numSamples);
  float applySaturation(float sample, float saturation);
  float applyReverb(float sample, float amount);

  static const int MAX_VOICES = 32;
};

#endif // MELOTRON_SYNTH_H
