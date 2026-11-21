#include <gtest/gtest.h>
#include "soundfont_loader.h"
#include <cstring>
#include <fstream>

class SF2ExtractionTest : public ::testing::Test {
protected:
  SoundFontLoader loader;

  void SetUp() override {
    // Tests will use the actual Mellotron.sf2 file if available
  }
};

// Test 1: Load valid SoundFont2 file
TEST_F(SF2ExtractionTest, LoadValidSF2File) {
  bool result = loader.load("./sf2-files/Mellotron.sf2");

  if (result) {
    EXPECT_GT(loader.getInstrumentCount(), 0);
    EXPECT_EQ(loader.getInstrumentCount(), 3);  // Violins, Choir, Flute
  } else {
    GTEST_SKIP() << "Mellotron.sf2 not found, skipping real file test";
  }
}

// Test 2: Check instrument names
TEST_F(SF2ExtractionTest, InstrumentNamesExtracted) {
  bool result = loader.load("./sf2-files/Mellotron.sf2");

  if (result) {
    auto names = loader.getInstrumentNames();

    ASSERT_EQ(names.size(), 3);
    EXPECT_NE(std::find(names.begin(), names.end(), "Violins"), names.end());
    EXPECT_NE(std::find(names.begin(), names.end(), "Choir"), names.end());
    EXPECT_NE(std::find(names.begin(), names.end(), "Flute"), names.end());
  } else {
    GTEST_SKIP() << "Mellotron.sf2 not found";
  }
}

// Test 3: Get instrument by name
TEST_F(SF2ExtractionTest, GetInstrumentByName) {
  bool result = loader.load("./sf2-files/Mellotron.sf2");

  if (result) {
    Instrument* violins = loader.getInstrumentByName("Violins");
    ASSERT_NE(violins, nullptr);
    EXPECT_EQ(violins->name, "Violins");
    EXPECT_GT(violins->samples.size(), 0);
  } else {
    GTEST_SKIP() << "Mellotron.sf2 not found";
  }
}

// Test 4: Sample has valid metadata
TEST_F(SF2ExtractionTest, SampleMetadataValid) {
  bool result = loader.load("./sf2-files/Mellotron.sf2");

  if (result) {
    Instrument* violins = loader.getInstrumentByName("Violins");
    ASSERT_NE(violins, nullptr);
    ASSERT_GT(violins->samples.size(), 0);

    Sample& sample = violins->samples[0];

    // Check metadata extraction
    EXPECT_GT(sample.name.length(), 0);
    EXPECT_GE(sample.originalPitch, 0);
    EXPECT_LE(sample.originalPitch, 127);
    EXPECT_GT(sample.sampleRate, 0);
    EXPECT_GE(sample.startLoop, 0);
    EXPECT_GE(sample.endLoop, 0);
  } else {
    GTEST_SKIP() << "Mellotron.sf2 not found";
  }
}

// Test 5: Sample data loaded
TEST_F(SF2ExtractionTest, SampleDataLoaded) {
  bool result = loader.load("./sf2-files/Mellotron.sf2");

  if (result) {
    Instrument* violins = loader.getInstrumentByName("Violins");
    ASSERT_NE(violins, nullptr);
    ASSERT_GT(violins->samples.size(), 0);

    Sample& sample = violins->samples[0];

    // Check if sample data is loaded
    EXPECT_TRUE(sample.valid);
    EXPECT_GT(sample.data.size(), 0);

    // Check sample values are in valid range
    for (float val : sample.data) {
      EXPECT_GE(val, -1.0f);
      EXPECT_LE(val, 1.0f);
    }
  } else {
    GTEST_SKIP() << "Mellotron.sf2 not found";
  }
}

// Test 6: Get sample for MIDI note
TEST_F(SF2ExtractionTest, GetSampleForMIDINote) {
  bool result = loader.load("./sf2-files/Mellotron.sf2");

  if (result) {
    Instrument* violins = loader.getInstrumentByName("Violins");
    ASSERT_NE(violins, nullptr);

    // Test middle C
    Sample* sample = loader.getSampleForNote(violins, 60);
    ASSERT_NE(sample, nullptr);
    EXPECT_TRUE(sample->valid);
  } else {
    GTEST_SKIP() << "Mellotron.sf2 not found";
  }
}

// Test 7: Multiple instruments load independently
TEST_F(SF2ExtractionTest, MultipleInstrumentsIndependent) {
  bool result = loader.load("./sf2-files/Mellotron.sf2");

  if (result) {
    Instrument* violins = loader.getInstrumentByName("Violins");
    Instrument* choir = loader.getInstrumentByName("Choir");
    Instrument* flute = loader.getInstrumentByName("Flute");

    ASSERT_NE(violins, nullptr);
    ASSERT_NE(choir, nullptr);
    ASSERT_NE(flute, nullptr);

    // Each instrument should have different samples
    EXPECT_NE(violins, choir);
    EXPECT_NE(choir, flute);
    EXPECT_NE(violins, flute);
  } else {
    GTEST_SKIP() << "Mellotron.sf2 not found";
  }
}

// Test 8: Invalid file returns false
TEST_F(SF2ExtractionTest, InvalidFileReturnsFalse) {
  bool result = loader.load("./nonexistent_file.sf2");
  EXPECT_FALSE(result);
  EXPECT_EQ(loader.getInstrumentCount(), 0);
}

// Test 9: Loop points are valid
TEST_F(SF2ExtractionTest, LoopPointsValid) {
  bool result = loader.load("./sf2-files/Mellotron.sf2");

  if (result) {
    Instrument* violins = loader.getInstrumentByName("Violins");
    ASSERT_NE(violins, nullptr);
    ASSERT_GT(violins->samples.size(), 0);

    Sample& sample = violins->samples[0];

    // Loop points should be within sample bounds
    if (sample.endLoop > sample.startLoop) {  // If loop exists
      EXPECT_LT(sample.startLoop, sample.data.size());
      EXPECT_LT(sample.endLoop, sample.data.size());
      EXPECT_LT(sample.startLoop, sample.endLoop);
    }
  } else {
    GTEST_SKIP() << "Mellotron.sf2 not found";
  }
}

// Test 10: Sample rate is reasonable
TEST_F(SF2ExtractionTest, SampleRateReasonable) {
  bool result = loader.load("./sf2-files/Mellotron.sf2");

  if (result) {
    Instrument* violins = loader.getInstrumentByName("Violins");
    ASSERT_NE(violins, nullptr);
    ASSERT_GT(violins->samples.size(), 0);

    Sample& sample = violins->samples[0];

    // Sample rate should be typical value (44.1kHz, 48kHz, etc.)
    EXPECT_GE(sample.sampleRate, 44100);
    EXPECT_LE(sample.sampleRate, 192000);
  } else {
    GTEST_SKIP() << "Mellotron.sf2 not found";
  }
}
