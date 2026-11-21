#include "soundfont_loader.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

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

  while (file.good()) {
    ChunkHeader header;
    file.read(header.id, 4);
    file.read((char*)&header.size, 4);

    std::string chunkId(header.id, 4);
    std::cout << "[SoundFontLoader] Found chunk: " << chunkId
      << " (" << header.size << " bytes)\n";

    uint8_t* data = new uint8_t[header.size];
    file.read((char*)data, header.size);

    if (chunkId == "LIST") {
      uint32_t listType;
      std::memcpy(&listType, data, 4);
      std::string typeStr((char*)data, 4);

      if (typeStr == "INFO") {
        parseINFOChunk(data + 4, header.size - 4);
      } else if (typeStr == "sdta") {
        parseSdtaChunk(data + 4, header.size - 4);
      } else if (typeStr == "pdta") {
        parsePdtaChunk(data + 4, header.size - 4);
      }
    }

    delete[] data;

    if (header.size % 2 == 1) {
      file.ignore(1);
    }
  }

  file.close();

  std::cout << "[SoundFontLoader] Loaded " << instruments.size()
    << " instruments with " << sampleDataBuffer.size() << " bytes of sample data\n";

  return instruments.size() > 0;
}

bool SoundFontLoader::parseINFOChunk(const uint8_t* data, uint32_t size) {
  std::cout << "[SoundFontLoader] Parsing INFO chunk\n";
  return true;
}

bool SoundFontLoader::parseSdtaChunk(const uint8_t* data, uint32_t size) {
  std::cout << "[SoundFontLoader] Parsing sdta (sample data) chunk\n";
  std::cout << "[SoundFontLoader] Sample data size: " << size << " bytes\n";

  // Store raw sample data for later loading
  sampleDataBuffer.resize(size);
  std::memcpy(sampleDataBuffer.data(), data, size);

  return true;
}

bool SoundFontLoader::parsePdtaChunk(const uint8_t* data, uint32_t size) {
  std::cout << "[SoundFontLoader] Parsing pdta (preset data) chunk\n";

  uint32_t offset = 0;
  while (offset < size) {
    ChunkHeader header;
    if (offset + 8 > size) break;

    std::memcpy(&header.id, data + offset, 4);
    std::memcpy(&header.size, data + offset + 4, 4);
    offset += 8;

    std::string subChunkId(header.id, 4);
    std::cout << "[SoundFontLoader] Found pdta sub-chunk: " << subChunkId << "\n";

    if (subChunkId == "SHDR") {
      parseSHDRSubChunk(data + offset, header.size);
    } else if (subChunkId == "INST") {
      parseINSTSubChunk(data + offset, header.size);
    }

    offset += header.size;
    if (header.size % 2 == 1) offset++;
  }

  return true;
}

bool SoundFontLoader::parseSHDRSubChunk(const uint8_t* data, uint32_t size) {
  std::cout << "[SoundFontLoader] Parsing SHDR (Sample Headers)\n";

  uint32_t numSamples = size / 46;
  std::cout << "[SoundFontLoader] Found " << numSamples << " samples\n";

  std::vector<SHDREntry> sampleHeaders;
  for (uint32_t i = 0; i < numSamples; ++i) {
    const uint8_t* sampleData = data + (i * 46);
    SHDREntry shdr;

    std::memcpy(shdr.name, sampleData, 20);
    std::memcpy(&shdr.startOffset, sampleData + 20, 4);
    std::memcpy(&shdr.endOffset, sampleData + 24, 4);
    std::memcpy(&shdr.startLoop, sampleData + 28, 4);
    std::memcpy(&shdr.endLoop, sampleData + 32, 4);
    std::memcpy(&shdr.sampleRate, sampleData + 36, 4);
    std::memcpy(&shdr.originalPitch, sampleData + 40, 1);
    std::memcpy(&shdr.pitchCorrection, sampleData + 41, 1);
    std::memcpy(&shdr.sampleLink, sampleData + 42, 2);
    std::memcpy(&shdr.sampleType, sampleData + 44, 2);

    std::string sampleName(shdr.name);
    std::cout << "[SoundFontLoader] Sample " << i << ": " << sampleName
      << " (pitch=" << (int)shdr.originalPitch << ")\n";

    sampleHeaders.push_back(shdr);
  }

  // Create instruments from samples
  if (sampleHeaders.size() >= 3) {
    // Violins (first sample)
    Instrument violins;
    violins.name = "Violins";
    violins.midiProgram = 0;
    Sample violin_sample;
    violin_sample.name = sampleHeaders[0].name;
    violin_sample.originalPitch = sampleHeaders[0].originalPitch;
    violin_sample.sampleRate = sampleHeaders[0].sampleRate;
    violin_sample.startLoop = sampleHeaders[0].startLoop;
    violin_sample.endLoop = sampleHeaders[0].endLoop;
    violin_sample.startOffset = sampleHeaders[0].startOffset;
    violin_sample.endOffset = sampleHeaders[0].endOffset;
    violin_sample.pitchCorrection = sampleHeaders[0].pitchCorrection;
    violin_sample.valid = false;

    if (sampleDataBuffer.size() > 0) {
      loadSampleData(violin_sample, sampleHeaders[0]);
    }

    violins.samples.push_back(violin_sample);
    instruments.push_back(violins);

    // Choir (second sample)
    Instrument choir;
    choir.name = "Choir";
    choir.midiProgram = 1;
    Sample choir_sample;
    choir_sample.name = sampleHeaders[1].name;
    choir_sample.originalPitch = sampleHeaders[1].originalPitch;
    choir_sample.sampleRate = sampleHeaders[1].sampleRate;
    choir_sample.startLoop = sampleHeaders[1].startLoop;
    choir_sample.endLoop = sampleHeaders[1].endLoop;
    choir_sample.startOffset = sampleHeaders[1].startOffset;
    choir_sample.endOffset = sampleHeaders[1].endOffset;
    choir_sample.pitchCorrection = sampleHeaders[1].pitchCorrection;
    choir_sample.valid = false;

    if (sampleDataBuffer.size() > 0) {
      loadSampleData(choir_sample, sampleHeaders[1]);
    }

    choir.samples.push_back(choir_sample);
    instruments.push_back(choir);

    // Flute (third sample)
    Instrument flute;
    flute.name = "Flute";
    flute.midiProgram = 2;
    Sample flute_sample;
    flute_sample.name = sampleHeaders[2].name;
    flute_sample.originalPitch = sampleHeaders[2].originalPitch;
    flute_sample.sampleRate = sampleHeaders[2].sampleRate;
    flute_sample.startLoop = sampleHeaders[2].startLoop;
    flute_sample.endLoop = sampleHeaders[2].endLoop;
    flute_sample.startOffset = sampleHeaders[2].startOffset;
    flute_sample.endOffset = sampleHeaders[2].endOffset;
    flute_sample.pitchCorrection = sampleHeaders[2].pitchCorrection;
    flute_sample.valid = false;

    if (sampleDataBuffer.size() > 0) {
      loadSampleData(flute_sample, sampleHeaders[2]);
    }

    flute.samples.push_back(flute_sample);
    instruments.push_back(flute);

    std::cout << "[SoundFontLoader] Created 3 Melotron instruments\n";
  }

  return true;
}

bool SoundFontLoader::parseINSTSubChunk(const uint8_t* data, uint32_t size) {
  std::cout << "[SoundFontLoader] Parsing INST (Instruments)\n";
  return true;
}

void SoundFontLoader::loadSampleData(Sample& sample, const SHDREntry& shdr) {
  uint32_t startByte = shdr.startOffset * 2;  // Convert to bytes (samples are 24-bit = 3 bytes)
  uint32_t endByte = shdr.endOffset * 2;

  if (startByte >= sampleDataBuffer.size() || endByte > sampleDataBuffer.size()) {
    std::cerr << "[SoundFontLoader] Invalid sample offsets\n";
    return;
  }

  uint32_t sampleCount = (endByte - startByte) / 3;
  if (sampleCount == 0) {
    std::cerr << "[SoundFontLoader] Sample has no data\n";
    return;
  }

  sample.data.resize(sampleCount);

  // Convert 24-bit PCM to float (-1.0 to 1.0)
  for (uint32_t i = 0; i < sampleCount; ++i) {
    uint32_t byteIdx = startByte + (i * 3);

    int32_t sample24 = 0;
    sample24 |= (sampleDataBuffer[byteIdx]) << 0;
    sample24 |= (sampleDataBuffer[byteIdx + 1]) << 8;
    sample24 |= ((int8_t)sampleDataBuffer[byteIdx + 2]) << 16;

    sample.data[i] = sample24 / 8388608.0f;
  }

  sample.valid = true;
  std::cout << "[SoundFontLoader] Loaded " << sampleCount << " samples for "
    << sample.name << "\n";
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
