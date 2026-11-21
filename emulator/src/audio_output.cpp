#include "audio_output.h"
#include <iostream>
#include <cmath>

AudioOutput::AudioOutput()
  : sampleRate(0), channels(0), isInitialized(false) {
}

AudioOutput::~AudioOutput() {
  stop();
}

bool AudioOutput::initialize(int sr, int ch) {
  sampleRate = sr;
  channels = ch;
  isInitialized = true;

  std::cout << "[AudioOutput] Initialized: " << sampleRate << " Hz, "
    << channels << " channels\n";
  return true;
}

void AudioOutput::playTone(double frequency, float amplitude) {
  if (!isInitialized) {
    std::cerr << "[AudioOutput] Not initialized\n";
    return;
  }

  // For now, just log - will implement actual audio generation
  std::cout << "[AudioOutput] Playing tone: " << frequency << " Hz at amplitude "
    << amplitude << "\n";

  // Generate a simple sine wave
  int bufferSize = sampleRate / 10; // 100ms buffer
  audioBuffer.resize(bufferSize * channels);

  for (int i = 0; i < bufferSize; ++i) {
    float sample = amplitude * std::sin(2.0f * M_PI * frequency * i / sampleRate);

    for (int ch = 0; ch < channels; ++ch) {
      audioBuffer[i * channels + ch] = sample;
    }
  }

  // Audio playback will be implemented through PortAudio or other backend
  std::cout << "[AudioOutput] Generated " << bufferSize << " samples for audio playback\n";
}

void AudioOutput::stop() {
  audioBuffer.clear();
  std::cout << "[AudioOutput] Stopped\n";
}
