#include "wav_sample_loader.h"
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cstring>
#include <iostream>

namespace fs = std::filesystem;

WavSampleLoader::WavSampleLoader() {}

WavSampleLoader::~WavSampleLoader() {}

bool WavSampleLoader::loadInstrumentFromWavDirectory(
    const std::string& dirPath,
    const std::string& instrumentName,
    uint8_t midiBank,
    uint8_t midiProgram) {

  if (!fs::exists(dirPath)) {
    std::cerr << "Directory not found: " << dirPath << std::endl;
    return false;
  }

  InstrumentPreset preset;
  preset.name = instrumentName;
  preset.midiBank = midiBank;
  preset.midiProgram = midiProgram;
  preset.samples.resize(128);

  // Collect all WAV files from directory
  std::vector<std::pair<int, std::string>> wavFiles;

  for (const auto& entry : fs::directory_iterator(dirPath)) {
    if (entry.is_regular_file() && entry.path().extension() == ".wav") {
      std::string filename = entry.path().filename().string();

      // Extract preset number from filename (e.g., "mellotron_000.wav" -> 0)
      size_t lastUnderscore = filename.rfind('_');
      size_t dotPos = filename.rfind('.');
      if (lastUnderscore != std::string::npos && dotPos != std::string::npos) {
        try {
          int presetNum = std::stoi(
              filename.substr(lastUnderscore + 1, dotPos - lastUnderscore - 1));
          if (presetNum >= 0 && presetNum < 128) {
            wavFiles.push_back({presetNum, entry.path().string()});
          }
        } catch (...) {
          // Skip files that don't match naming pattern
        }
      }
    }
  }

  // Sort by preset number
  std::sort(wavFiles.begin(), wavFiles.end());

  // Load WAV files into preset samples
  int loadedCount = 0;
  for (const auto& [presetNum, filePath] : wavFiles) {
    if (loadWavFile(filePath, preset.samples[presetNum])) {
      loadedCount++;
    }
  }

  if (loadedCount == 0) {
    std::cerr << "No WAV files successfully loaded from: " << dirPath << std::endl;
    return false;
  }

  std::cout << "Loaded instrument '" << instrumentName << "' with "
            << loadedCount << "/128 presets from " << dirPath << std::endl;

  instruments.push_back(preset);
  return true;
}

InstrumentPreset* WavSampleLoader::getInstrument(int index) {
  if (index >= 0 && index < (int)instruments.size()) {
    return &instruments[index];
  }
  return nullptr;
}

InstrumentPreset* WavSampleLoader::getInstrumentByName(const std::string& name) {
  for (auto& inst : instruments) {
    if (inst.name == name) {
      return &inst;
    }
  }
  return nullptr;
}

std::vector<std::string> WavSampleLoader::getInstrumentNames() const {
  std::vector<std::string> names;
  for (const auto& inst : instruments) {
    names.push_back(inst.name);
  }
  return names;
}

WavSample* WavSampleLoader::getSampleForNote(InstrumentPreset* instrument,
                                              uint8_t midiNote) {
  if (!instrument || midiNote > 127) {
    return nullptr;
  }

  WavSample* sample = &instrument->samples[midiNote];
  if (sample && sample->valid) {
    return sample;
  }

  // Find nearest valid sample
  for (int distance = 1; distance < 128; distance++) {
    if (midiNote - distance >= 0) {
      sample = &instrument->samples[midiNote - distance];
      if (sample->valid) return sample;
    }
    if (midiNote + distance < 128) {
      sample = &instrument->samples[midiNote + distance];
      if (sample->valid) return sample;
    }
  }

  return nullptr;
}

bool WavSampleLoader::loadWavFile(const std::string& filename,
                                   WavSample& sample) {
  std::ifstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    return false;
  }

  WAVHeader header;
  if (!parseWavHeader(file, header)) {
    return false;
  }

  // Only support PCM format
  if (header.audioFormat != 1) {
    std::cerr << "Unsupported audio format in " << filename << std::endl;
    return false;
  }

  sample.sampleRate = header.sampleRate;
  sample.channels = header.numChannels;
  sample.name = fs::path(filename).filename().string();

  // Read audio data
  uint32_t numSamples = header.subchunk2Size / (header.bitsPerSample / 8);
  std::vector<uint8_t> rawData(header.subchunk2Size);
  file.read(reinterpret_cast<char*>(rawData.data()), header.subchunk2Size);

  if (!file) {
    return false;
  }

  // Convert to float samples
  sample.data.resize(numSamples);

  if (header.bitsPerSample == 16) {
    const int16_t* audioData = reinterpret_cast<const int16_t*>(rawData.data());
    for (uint32_t i = 0; i < numSamples; i++) {
      sample.data[i] = audioData[i] / 32768.0f;
    }
  } else if (header.bitsPerSample == 24) {
    for (uint32_t i = 0; i < numSamples; i++) {
      uint32_t sample24 = rawData[i * 3] |
                          (rawData[i * 3 + 1] << 8) |
                          (rawData[i * 3 + 2] << 16);
      if (sample24 & 0x800000) {
        sample24 |= 0xFF000000;  // Sign extend
      }
      int32_t sampleSigned = static_cast<int32_t>(sample24);
      sample.data[i] = sampleSigned / 8388608.0f;
    }
  } else if (header.bitsPerSample == 32) {
    const int32_t* audioData = reinterpret_cast<const int32_t*>(rawData.data());
    for (uint32_t i = 0; i < numSamples; i++) {
      sample.data[i] = audioData[i] / 2147483648.0f;
    }
  } else {
    return false;
  }

  sample.valid = true;
  return true;
}

bool WavSampleLoader::parseWavHeader(std::ifstream& file, WAVHeader& header) {
  file.read(reinterpret_cast<char*>(&header.chunkId), 4);
  if (header.chunkId != 0x46464952) {  // "RIFF"
    return false;
  }

  file.read(reinterpret_cast<char*>(&header.chunkSize), 4);
  file.read(reinterpret_cast<char*>(&header.format), 4);

  if (header.format != 0x45564157) {  // "WAVE"
    return false;
  }

  // Find fmt subchunk
  while (file.good()) {
    file.read(reinterpret_cast<char*>(&header.subchunk1Id), 4);

    if (header.subchunk1Id == 0x20746d66) {  // "fmt "
      file.read(reinterpret_cast<char*>(&header.subchunk1Size), 4);
      file.read(reinterpret_cast<char*>(&header.audioFormat), 2);
      file.read(reinterpret_cast<char*>(&header.numChannels), 2);
      file.read(reinterpret_cast<char*>(&header.sampleRate), 4);
      file.read(reinterpret_cast<char*>(&header.byteRate), 4);
      file.read(reinterpret_cast<char*>(&header.blockAlign), 2);
      file.read(reinterpret_cast<char*>(&header.bitsPerSample), 2);

      // Skip to data chunk
      file.seekg(header.subchunk1Size - 16, std::ios::cur);
      break;
    } else {
      file.read(reinterpret_cast<char*>(&header.subchunk1Size), 4);
      file.seekg(header.subchunk1Size, std::ios::cur);
    }
  }

  // Find data subchunk
  while (file.good()) {
    file.read(reinterpret_cast<char*>(&header.subchunk2Id), 4);

    if (header.subchunk2Id == 0x61746164) {  // "data"
      file.read(reinterpret_cast<char*>(&header.subchunk2Size), 4);
      return true;
    } else {
      file.read(reinterpret_cast<char*>(&header.subchunk2Size), 4);
      file.seekg(header.subchunk2Size, std::ios::cur);
    }
  }

  return false;
}
