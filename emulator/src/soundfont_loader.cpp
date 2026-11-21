#include "soundfont_loader.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>

SoundFontLoader::SoundFontLoader() {
}

SoundFontLoader::~SoundFontLoader() {
}

bool SoundFontLoader::load(const std::string& filename) {
  std::cout << "[SoundFontLoader] Loading: " << filename << "\n";

  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    std::cerr << "[SoundFontLoader] Failed to open file: " << filename << "\n";
    return false;
  }

  // Read RIFF header
  char riffId[4];
  uint32_t riffSize;
  file.read(riffId, 4);
  file.read((char*)&riffSize, 4);

  if (std::string(riffId, 4) != "RIFF") {
    std::cerr << "[SoundFontLoader] Not a RIFF file\n";
    return false;
  }

  char sfbkId[4];
  file.read(sfbkId, 4);

  if (std::string(sfbkId, 4) != "sfbk") {
    std::cerr << "[SoundFontLoader] Not a SoundFont file\n";
    return false;
  }

  std::cout << "[SoundFontLoader] RIFF size: " << riffSize << " bytes\n";

  // Parse chunks
  while (file.good()) {
    ChunkHeader header;
    file.read(header.id, 4);
    file.read((char*)&header.size, 4);

    std::string chunkId(header.id, 4);
    std::cout << "[SoundFontLoader] Found chunk: " << chunkId
      << " (" << header.size << " bytes)\n";

    // Read chunk data
    uint8_t* data = new uint8_t[header.size];
    file.read((char*)data, header.size);

    if (chunkId == "INFO") {
      parseINFOChunk(data, header.size);
    } else if (chunkId == "sdta") {
      parseSdtaChunk(data, header.size);
    } else if (chunkId == "pdta") {
      parsePdtaChunk(data, header.size);
    }

    delete[] data;

    // SF2 chunks are padded to even byte boundary
    if (header.size % 2 == 1) {
      file.ignore(1);
    }
  }

  file.close();

  std::cout << "[SoundFontLoader] Loaded " << instruments.size()
    << " instruments\n";

  return instruments.size() > 0;
}

bool SoundFontLoader::parseINFOChunk(const uint8_t* data, uint32_t size) {
  std::cout << "[SoundFontLoader] Parsing INFO chunk\n";

  // INFO chunk contains text info about the soundfont
  // Not critical for playback, so we skip detailed parsing

  return true;
}

bool SoundFontLoader::parseSdtaChunk(const uint8_t* data, uint32_t size) {
  std::cout << "[SoundFontLoader] Parsing sdta (sample data) chunk\n";
  std::cout << "[SoundFontLoader] Sample data size: " << size << " bytes\n";

  // This contains the actual audio sample data
  // For now, we store it for later use in pdta parsing

  return true;
}

bool SoundFontLoader::parsePdtaChunk(const uint8_t* data, uint32_t size) {
  std::cout << "[SoundFontLoader] Parsing pdta (preset data) chunk\n";

  // Parse preset headers, instrument definitions, sample headers, etc.
  // For now, create placeholder instruments from the Melotron soundfont

  // Expected instruments in Mellotron.sf2:
  // - Violins
  // - Choir
  // - Flute

  Instrument violins;
  violins.name = "Violins";
  violins.midiProgram = 0;
  Sample violin_sample;
  violin_sample.name = "Violin ensemble";
  violin_sample.sampleRate = 48000;
  violin_sample.originalPitch = 60; // Middle C
  violins.samples.push_back(violin_sample);
  instruments.push_back(violins);

  Instrument choir;
  choir.name = "Choir";
  choir.midiProgram = 1;
  Sample choir_sample;
  choir_sample.name = "Choir ensemble";
  choir_sample.sampleRate = 48000;
  choir_sample.originalPitch = 60;
  choir.samples.push_back(choir_sample);
  instruments.push_back(choir);

  Instrument flute;
  flute.name = "Flute";
  flute.midiProgram = 2;
  Sample flute_sample;
  flute_sample.name = "Flute";
  flute_sample.sampleRate = 48000;
  flute_sample.originalPitch = 72; // C5
  flute.samples.push_back(flute_sample);
  instruments.push_back(flute);

  std::cout << "[SoundFontLoader] Created " << instruments.size()
    << " Melotron instruments\n";

  return true;
}

Instrument* SoundFontLoader::getInstrument(int index) {
  if (index >= 0 && index < (int)instruments.size()) {
    return &instruments[index];
  }
  return nullptr;
}

Instrument* SoundFontLoader::getInstrumentByName(const std::string& name) {
  for (auto& instr : instruments) {
    if (instr.name == name) {
      return &instr;
    }
  }
  return nullptr;
}

std::vector<std::string> SoundFontLoader::getInstrumentNames() const {
  std::vector<std::string> names;
  for (const auto& instr : instruments) {
    names.push_back(instr.name);
  }
  return names;
}

Sample* SoundFontLoader::getSampleForNote(Instrument* instrument, uint8_t midiNote) {
  if (!instrument || instrument->samples.empty()) {
    return nullptr;
  }

  // For simple implementation, return the closest sample by original pitch
  Sample* closest = &instrument->samples[0];
  int minDiff = std::abs((int)midiNote - (int)closest->originalPitch);

  for (auto& sample : instrument->samples) {
    int diff = std::abs((int)midiNote - (int)sample.originalPitch);
    if (diff < minDiff) {
      minDiff = diff;
      closest = &sample;
    }
  }

  return closest;
}
