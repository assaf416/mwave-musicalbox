#ifndef SOUNDFONT_LOADER_H
#define SOUNDFONT_LOADER_H

#include <string>
#include <vector>
#include <cstdint>
#include <memory>

struct Sample {
  std::string name;
  std::vector<float> data;      // Audio samples (normalized -1.0 to 1.0)
  uint32_t sampleRate;           // Sample rate in Hz
  uint32_t startLoop;            // Loop start position
  uint32_t endLoop;              // Loop end position
  uint32_t originalPitch;        // Original MIDI note
  int8_t pitchCorrection;        // Pitch correction in cents
  uint16_t sampleLink;           // Link to another sample
  uint16_t sampleType;           // Sample type (mono/stereo/etc)
};

struct Instrument {
  std::string name;
  std::vector<Sample> samples;
  uint8_t midiProgram;
  uint8_t midiBank;
};

class SoundFontLoader {
public:
  SoundFontLoader();
  ~SoundFontLoader();

  /**
   * Load a SoundFont2 file
   * @param filename Path to .sf2 file
   * @return true if successful, false otherwise
   */
  bool load(const std::string& filename);

  /**
   * Get instrument by index
   * @param index Instrument index
   * @return Pointer to Instrument, or nullptr if not found
   */
  Instrument* getInstrument(int index);

  /**
   * Get instrument by name
   * @param name Instrument name
   * @return Pointer to Instrument, or nullptr if not found
   */
  Instrument* getInstrumentByName(const std::string& name);

  /**
   * Get instrument count
   * @return Number of instruments loaded
   */
  int getInstrumentCount() const { return instruments.size(); }

  /**
   * List all instrument names
   * @return Vector of instrument names
   */
  std::vector<std::string> getInstrumentNames() const;

  /**
   * Get sample by MIDI note from instrument
   * @param instrument Pointer to Instrument
   * @param midiNote MIDI note (0-127)
   * @return Pointer to matching Sample, or nullptr if not found
   */
  Sample* getSampleForNote(Instrument* instrument, uint8_t midiNote);

private:
  std::vector<Instrument> instruments;

  // SF2 parsing helpers
  struct ChunkHeader {
    char id[4];
    uint32_t size;
  };

  bool parseSF2(const std::string& filename);
  bool parseINFOChunk(const uint8_t* data, uint32_t size);
  bool parseSdtaChunk(const uint8_t* data, uint32_t size);
  bool parsePdtaChunk(const uint8_t* data, uint32_t size);
};

#endif // SOUNDFONT_LOADER_H
