#ifndef SAMPLE_BASED_SYNTH_H
#define SAMPLE_BASED_SYNTH_H

#include <cstdint>
#include <memory>
#include <vector>
#include <string>

class WavSampleLoader;
struct WavSample;
struct InstrumentPreset;

class SampleBasedSynth {
public:
  enum Instrument {
    PIANO = 0,
    ELECTRIC_PIANO_1 = 1,
    ELECTRIC_PIANO_2 = 2,
    MELLOTRON = 3
  };

  SampleBasedSynth();
  ~SampleBasedSynth();

  /**
   * Initialize synthesizer with WAV samples
   * @param wavDir Directory containing extracted WAV files
   * @return true if successful
   */
  bool initialize(const std::string& wavDir);

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
   * Set instrument
   * @param instrument Instrument enum value
   */
  void setInstrument(Instrument instrument);

  /**
   * Get current instrument
   */
  Instrument getInstrument() const { return currentInstrument; }

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
   * Get available instruments
   */
  std::vector<std::string> getAvailableInstruments() const;

private:
  struct Voice {
    bool active;
    uint8_t midiNote;
    uint8_t velocity;
    float position;             // Position in sample (0.0 to 1.0)
    float pitchShift;           // Pitch shift factor relative to base sample
    float amplitude;            // Current amplitude envelope
    float velocity_normalized;  // Velocity normalized to 0.0-1.0
    int attackSamples;          // Attack envelope duration
    int releaseSamples;         // Release envelope duration
    int noteStartSample;        // Sample number when note started
    bool isReleasing;           // Is note in release phase
    int releaseStartSample;     // Sample number when release started
  };

  std::unique_ptr<WavSampleLoader> wavLoader;
  std::vector<Voice> activeVoices;
  Instrument currentInstrument;
  float reverbAmount;
  int sampleRate;

  static const int MAX_VOICES = 32;
  static const int SAMPLE_RATE = 44100;

  InstrumentPreset* getCurrentInstrumentPreset();
  void processVoice(Voice& voice, float* buffer, int numSamples);
  float getEnvelopeValue(const Voice& voice, int sampleIndex);
  float applyReverb(float sample, float amount);
  float interpolateSample(const WavSample* sample, float position);
};

#endif // SAMPLE_BASED_SYNTH_H
