#ifndef WAV_SAMPLE_LOADER_H
#define WAV_SAMPLE_LOADER_H

#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <map>

struct WavSample {
  std::string name;
  std::vector<float> data;       // Audio samples (normalized -1.0 to 1.0)
  uint32_t sampleRate;           // Sample rate in Hz
  uint32_t channels;             // Number of channels (1=mono, 2=stereo)
  bool valid;                    // Sample has valid data
};

struct InstrumentPreset {
  std::string name;
  std::vector<WavSample> samples;  // 128 MIDI note samples
  uint8_t midiProgram;
  uint8_t midiBank;
};

class WavSampleLoader {
public:
  WavSampleLoader();
  ~WavSampleLoader();

  /**
   * Load all WAV samples from a directory
   * @param dirPath Path to directory containing WAV files
   * @param instrumentName Name for this instrument
   * @param midiBank MIDI bank number
   * @param midiProgram MIDI program number
   * @return true if successful
   */
  bool loadInstrumentFromWavDirectory(const std::string& dirPath,
                                      const std::string& instrumentName,
                                      uint8_t midiBank,
                                      uint8_t midiProgram);

  /**
   * Get instrument by index
   */
  InstrumentPreset* getInstrument(int index);

  /**
   * Get instrument by name
   */
  InstrumentPreset* getInstrumentByName(const std::string& name);

  /**
   * Get instrument count
   */
  int getInstrumentCount() const { return instruments.size(); }

  /**
   * List all instrument names
   */
  std::vector<std::string> getInstrumentNames() const;

  /**
   * Get sample for a specific MIDI note from an instrument
   * @param instrument Pointer to InstrumentPreset
   * @param midiNote MIDI note (0-127)
   * @return Pointer to WavSample, or nullptr
   */
  WavSample* getSampleForNote(InstrumentPreset* instrument, uint8_t midiNote);

private:
  std::vector<InstrumentPreset> instruments;

  // WAV file parsing
  struct WAVHeader {
    uint32_t chunkId;              // "RIFF"
    uint32_t chunkSize;
    uint32_t format;               // "WAVE"
    uint32_t subchunk1Id;          // "fmt "
    uint32_t subchunk1Size;
    uint16_t audioFormat;          // 1 = PCM
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    uint32_t subchunk2Id;          // "data"
    uint32_t subchunk2Size;
  };

  bool loadWavFile(const std::string& filename, WavSample& sample);
  bool parseWavHeader(std::ifstream& file, WAVHeader& header);
  void normalizeAudioData(std::vector<float>& data, uint16_t bitsPerSample);
};

#endif // WAV_SAMPLE_LOADER_H
