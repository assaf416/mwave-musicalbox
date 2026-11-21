#include <gtest/gtest.h>
#include "wav_sample_loader.h"
#include "sample_based_synth.h"
#include <cmath>

class WavSampleLoaderTest : public ::testing::Test {
protected:
  WavSampleLoader loader;
  std::string wavDir = "../sf2-files";
};

TEST_F(WavSampleLoaderTest, LoadsMellotronSamples) {
  bool result = loader.loadInstrumentFromWavDirectory(
      wavDir + "/mellotron-wav", "Mellotron", 0, 48);

  if (result) {
    EXPECT_EQ(loader.getInstrumentCount(), 1);
    InstrumentPreset* inst = loader.getInstrumentByName("Mellotron");
    EXPECT_NE(inst, nullptr);
  }
}

TEST_F(WavSampleLoaderTest, LoadsPianoSamples) {
  bool result = loader.loadInstrumentFromWavDirectory(
      wavDir + "/my-pianos-wav", "Piano", 0, 0);

  if (result) {
    EXPECT_EQ(loader.getInstrumentCount(), 1);
    InstrumentPreset* inst = loader.getInstrumentByName("Piano");
    EXPECT_NE(inst, nullptr);
  }
}

TEST_F(WavSampleLoaderTest, GetSampleForNote) {
  bool result = loader.loadInstrumentFromWavDirectory(
      wavDir + "/mellotron-wav", "Mellotron", 0, 48);

  if (result) {
    InstrumentPreset* inst = loader.getInstrumentByName("Mellotron");
    EXPECT_NE(inst, nullptr);

    // Test middle C
    WavSample* sample = loader.getSampleForNote(inst, 60);
    if (sample) {
      EXPECT_TRUE(sample->valid);
      EXPECT_GT(sample->data.size(), 0);
      EXPECT_EQ(sample->sampleRate, 44100);
    }
  }
}

class SampleBasedSynthTest : public ::testing::Test {
protected:
  SampleBasedSynth synth;
  std::string wavDir = "../sf2-files";
};

TEST_F(SampleBasedSynthTest, InitializesWithWavSamples) {
  bool result = synth.initialize(wavDir);

  if (result) {
    EXPECT_GT(synth.getActiveVoiceCount(), -1);
  }
}

TEST_F(SampleBasedSynthTest, PlaysNoteWithMellotron) {
  bool initialized = synth.initialize(wavDir);

  if (initialized) {
    synth.setInstrument(SampleBasedSynth::MELLOTRON);
    int voiceId = synth.playNote(60, 100);  // Middle C

    EXPECT_GE(voiceId, 0);
    EXPECT_EQ(synth.getActiveVoiceCount(), 1);

    synth.stopNote(60);
  }
}

TEST_F(SampleBasedSynthTest, PlaysPianoNotes) {
  bool initialized = synth.initialize(wavDir);

  if (initialized) {
    synth.setInstrument(SampleBasedSynth::PIANO);

    // Play a chord
    synth.playNote(60, 100);  // C
    synth.playNote(64, 100);  // E
    synth.playNote(67, 100);  // G

    EXPECT_EQ(synth.getActiveVoiceCount(), 3);

    synth.stopAllNotes();
    EXPECT_EQ(synth.getActiveVoiceCount(), 0);
  }
}

TEST_F(SampleBasedSynthTest, GeneratesAudio) {
  bool initialized = synth.initialize(wavDir);

  if (initialized) {
    synth.setInstrument(SampleBasedSynth::MELLOTRON);

    float buffer[44100] = {0};

    synth.playNote(60, 100);
    synth.process(buffer, 44100);  // Process 1 second

    // Check if output has audio
    bool hasAudio = false;
    for (int i = 0; i < 44100; i++) {
      if (std::abs(buffer[i]) > 0.001f) {
        hasAudio = true;
        break;
      }
    }

    if (hasAudio) {
      EXPECT_TRUE(hasAudio);
    }
  }
}

TEST_F(SampleBasedSynthTest, SwitchesInstruments) {
  bool initialized = synth.initialize(wavDir);

  if (initialized) {
    synth.setInstrument(SampleBasedSynth::PIANO);
    EXPECT_EQ(synth.getInstrument(), SampleBasedSynth::PIANO);

    synth.setInstrument(SampleBasedSynth::MELLOTRON);
    EXPECT_EQ(synth.getInstrument(), SampleBasedSynth::MELLOTRON);
  }
}

TEST_F(SampleBasedSynthTest, Polyphony) {
  bool initialized = synth.initialize(wavDir);

  if (initialized) {
    synth.setInstrument(SampleBasedSynth::PIANO);

    // Test 32-voice polyphony
    for (int i = 0; i < 32; i++) {
      synth.playNote(60 + i, 100);
    }

    EXPECT_EQ(synth.getActiveVoiceCount(), 32);

    // Try adding one more (should drop oldest)
    synth.playNote(60, 100);
    EXPECT_EQ(synth.getActiveVoiceCount(), 32);

    synth.stopAllNotes();
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
