#include "audio_output.h"
#include <QDebug>
#include <cmath>

AudioOutput::AudioOutput(QObject *parent)
  : QObject(parent), sampleRate(0), channels(0), isInitialized(false) {
}

AudioOutput::~AudioOutput() {
  stop();
}

bool AudioOutput::initialize(int sr, int ch) {
  sampleRate = sr;
  channels = ch;
  isInitialized = true;

  qDebug() << "AudioOutput initialized: " << sampleRate << "Hz, " << channels << "channels";
  return true;
}

void AudioOutput::playTone(double frequency, float amplitude) {
  if (!isInitialized) {
    qWarning() << "AudioOutput not initialized";
    return;
  }

  // For now, just log - will implement actual audio generation
  qDebug() << "Playing tone:" << frequency << "Hz at amplitude" << amplitude;

  // Generate a simple sine wave
  int bufferSize = sampleRate / 10; // 100ms buffer
  audioBuffer.resize(bufferSize * channels);

  for (int i = 0; i < bufferSize; ++i) {
    float sample = amplitude * std::sin(2.0f * M_PI * frequency * i / sampleRate);

    for (int ch = 0; ch < channels; ++ch) {
      audioBuffer[i * channels + ch] = sample;
    }
  }

  // Audio playback will be implemented through QAudioOutput or PortAudio
  qDebug() << "Generated" << bufferSize << "samples for audio playback";
}

void AudioOutput::stop() {
  audioBuffer.clear();
  qDebug() << "AudioOutput stopped";
}
