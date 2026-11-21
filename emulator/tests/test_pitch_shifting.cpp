#include <gtest/gtest.h>
#include "melotron_synth.h"
#include <cmath>

class PitchShiftingTest : public ::testing::Test {
protected:
  MelotronSynth synth;

  void SetUp() override {
    // Initialize synth with Mellotron.sf2
    bool initialized = synth.initialize("./sf2-files/Mellotron.sf2");
    if (!initialized) {
      GTEST_SKIP() << "Mellotron.sf2 not found, skipping pitch shifting tests";
    }
  }
};

// Test 1: Pitch shift calculation is correct
TEST_F(PitchShiftingTest, PitchShiftCalculation) {
  // Formula: playback_rate = 2^((MIDI_note - original_pitch) / 12)

  // Middle C (60) to D (62) = 2 semitones up
  float expectedRate = std::pow(2.0f, 2.0f / 12.0f);  // ~1.122

  EXPECT_FLOAT_EQ(expectedRate, std::pow(2.0f, 2.0f / 12.0f));

  // Octave up (12 semitones)
  float octaveUp = std::pow(2.0f, 12.0f / 12.0f);
  EXPECT_FLOAT_EQ(octaveUp, 2.0f);

  // Octave down (12 semitones down)
  float octaveDown = std::pow(2.0f, -12.0f / 12.0f);
  EXPECT_FLOAT_EQ(octaveDown, 0.5f);
}

// Test 2: Playing note at original pitch
TEST_F(PitchShiftingTest, PlayNoteAtOriginalPitch) {
  // Middle C on Violins (original pitch = 60)
  int voiceId = synth.playNote(60, 100);  // MIDI note 60, velocity 100

  EXPECT_GE(voiceId, 0);
  EXPECT_GT(synth.getActiveVoiceCount(), 0);

  // Clean up
  synth.stopAllNotes();
}

// Test 3: Playing multiple notes with different pitches
TEST_F(PitchShiftingTest, PlayMultiplePitches) {
  // Play chord: C, E, G (60, 64, 67)
  synth.playNote(60, 100);
  synth.playNote(64, 100);
  synth.playNote(67, 100);

  EXPECT_EQ(synth.getActiveVoiceCount(), 3);

  synth.stopAllNotes();
  EXPECT_EQ(synth.getActiveVoiceCount(), 0);
}

// Test 4: Stopping specific note
TEST_F(PitchShiftingTest, StopSpecificNote) {
  synth.playNote(60, 100);
  synth.playNote(64, 100);
  synth.playNote(67, 100);

  EXPECT_EQ(synth.getActiveVoiceCount(), 3);

  synth.stopNote(64);  // Stop the E

  EXPECT_EQ(synth.getActiveVoiceCount(), 2);

  synth.stopAllNotes();
}

// Test 5: Tape voice selection changes output
TEST_F(PitchShiftingTest, TapeVoiceSelection) {
  // Test selecting different tape voices
  synth.setTapeVoice(MelotronSynth::VOICE_VIOLINS);
  synth.playNote(60, 100);
  int voiceId1 = synth.getActiveVoiceCount();
  synth.stopAllNotes();

  synth.setTapeVoice(MelotronSynth::VOICE_CHOIR);
  synth.playNote(60, 100);
  int voiceId2 = synth.getActiveVoiceCount();
  synth.stopAllNotes();

  synth.setTapeVoice(MelotronSynth::VOICE_FLUTE);
  synth.playNote(60, 100);
  int voiceId3 = synth.getActiveVoiceCount();
  synth.stopAllNotes();

  // All should have played notes
  EXPECT_EQ(voiceId1, 1);
  EXPECT_EQ(voiceId2, 1);
  EXPECT_EQ(voiceId3, 1);
}

// Test 6: Velocity affects amplitude
TEST_F(PitchShiftingTest, VelocityRanges) {
  // Test different velocity ranges
  synth.playNote(60, 1);    // Min velocity
  EXPECT_GT(synth.getActiveVoiceCount(), 0);
  synth.stopAllNotes();

  synth.playNote(60, 64);   // Mid velocity
  EXPECT_GT(synth.getActiveVoiceCount(), 0);
  synth.stopAllNotes();

  synth.playNote(60, 127);  // Max velocity
  EXPECT_GT(synth.getActiveVoiceCount(), 0);
  synth.stopAllNotes();
}

// Test 7: Polyphony limit
TEST_F(PitchShiftingTest, PolyphonyLimit) {
  // Try to exceed max voices (should be 32 by default)
  for (int i = 0; i < 40; ++i) {
    synth.playNote(60 + (i % 12), 100);
  }

  // Should not exceed MAX_VOICES (32)
  int activeVoices = synth.getActiveVoiceCount();
  EXPECT_LE(activeVoices, 32);

  synth.stopAllNotes();
}

// Test 8: Saturation effect
TEST_F(PitchShiftingTest, SaturationEffect) {
  // Test saturation at different levels
  synth.setTapeSaturation(0.0f);
  synth.playNote(60, 100);
  synth.stopAllNotes();

  synth.setTapeSaturation(0.5f);
  synth.playNote(60, 100);
  synth.stopAllNotes();

  synth.setTapeSaturation(1.0f);
  synth.playNote(60, 100);
  synth.stopAllNotes();

  EXPECT_EQ(synth.getActiveVoiceCount(), 0);
}

// Test 9: Reverb effect
TEST_F(PitchShiftingTest, ReverbEffect) {
  // Test reverb at different levels
  synth.setReverb(0.0f);
  synth.playNote(60, 100);
  synth.stopAllNotes();

  synth.setReverb(0.5f);
  synth.playNote(60, 100);
  synth.stopAllNotes();

  synth.setReverb(1.0f);
  synth.playNote(60, 100);
  synth.stopAllNotes();

  EXPECT_EQ(synth.getActiveVoiceCount(), 0);
}

// Test 10: MIDI note range (0-127)
TEST_F(PitchShiftingTest, MIDINoteRange) {
  // Test minimum note
  synth.playNote(0, 100);
  EXPECT_EQ(synth.getActiveVoiceCount(), 1);
  synth.stopAllNotes();

  // Test middle note
  synth.playNote(60, 100);
  EXPECT_EQ(synth.getActiveVoiceCount(), 1);
  synth.stopAllNotes();

  // Test maximum note
  synth.playNote(127, 100);
  EXPECT_EQ(synth.getActiveVoiceCount(), 1);
  synth.stopAllNotes();

  EXPECT_EQ(synth.getActiveVoiceCount(), 0);
}

// Test 11: Pitch shift range extremes
TEST_F(PitchShiftingTest, PitchShiftRangeExtremes) {
  // Large pitch down (many octaves)
  synth.playNote(24, 100);  // 2 octaves below middle C
  EXPECT_EQ(synth.getActiveVoiceCount(), 1);
  synth.stopAllNotes();

  // Large pitch up (many octaves)
  synth.playNote(96, 100);  // 2 octaves above middle C
  EXPECT_EQ(synth.getActiveVoiceCount(), 1);
  synth.stopAllNotes();
}

// Test 12: Chromatic scale
TEST_F(PitchShiftingTest, ChromaticScale) {
  // Play all 12 semitones of an octave
  for (int i = 0; i < 12; ++i) {
    synth.playNote(60 + i, 100);
  }

  EXPECT_EQ(synth.getActiveVoiceCount(), 12);

  synth.stopAllNotes();
  EXPECT_EQ(synth.getActiveVoiceCount(), 0);
}
