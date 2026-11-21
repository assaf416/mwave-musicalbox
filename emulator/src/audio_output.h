#ifndef AUDIO_OUTPUT_H
#define AUDIO_OUTPUT_H

#include <cstdint>
#include <vector>

class AudioOutput {
public:
  AudioOutput();
  ~AudioOutput();

  bool initialize(int sampleRate, int channels);
  void playTone(double frequency, float amplitude);
  void stop();

private:
  int sampleRate;
  int channels;
  bool isInitialized;
  std::vector<float> audioBuffer;
};

#endif // AUDIO_OUTPUT_H
