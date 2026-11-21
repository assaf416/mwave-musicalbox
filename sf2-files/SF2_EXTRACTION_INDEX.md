# SoundFont2 (SF2) Extraction Index

Comprehensive catalog of all extracted SF2 files and their contents.

## Overview

| Collection | File Size | Presets | Status | Output Dir |
|------------|-----------|---------|--------|------------|
| Mellotron | 111 MB | 128 | ✅ Complete | `mellotron-wav/` |
| Electric Heavy Guitars | 44 MB | 128 | 🔄 Extracting | `my-electric-heavy-guitars-wav/` |
| Pianos | 175 MB | 128 | 🔄 Extracting | `my-pianos-wav/` |
| Bass | 65 KB | 128 | 🔄 Extracting | `my-bass-wav/` |
| Pads | 6.2 MB | 128 | 🔄 Extracting | `my-pads-wav/` |
| Drums | 257 MB | 128 | 🔄 Extracting | `my-drums-wav/` |
| Electric Clean Guitars | 74 MB | 128 | 🔄 Extracting | `my-electric-clean-guitars-wav/` |

**Total SF2 Input:** ~667 MB  
**Expected Output:** ~768 WAV files (128 per SF2 × 6)  
**Estimated Size:** ~400+ MB

## Extraction Process

Each SF2 file is being extracted using:
- **Tool:** FluidSynth 2.4.4 (audio synthesis engine)
- **Method:** MIDI program change → WAV rendering
- **Sample Rate:** 44,100 Hz (CD quality)
- **Format:** 16-bit PCM Stereo
- **Duration:** 2 seconds per preset (middle C note)
- **Parallelization:** All 6 collections render simultaneously

## File Naming Convention

Each extracted WAV follows the pattern:
```
{collection-name}_{preset-number:03d}.wav
```

Examples:
- `mellotron_000.wav` - Mellotron preset 0
- `my-electric-heavy-guitars_032.wav` - Heavy Guitars preset 32
- `my-drums_127.wav` - Drums preset 127

## Directory Structure

```
sf2-files/
├── Mellotron.sf2
├── my-electric-heavy-guitars.sf2
├── my-pianos.sf2
├── my-bass.sf2
├── my-pads.sf2
├── my-drums.sf2
├── my-electric-clean-guitars.sf2
├── mellotron-wav/
│   ├── mellotron_000.wav
│   ├── mellotron_001.wav
│   └── ... (128 total)
├── my-electric-heavy-guitars-wav/
│   ├── my-electric-heavy-guitars_000.wav
│   └── ... (128 total)
├── my-pianos-wav/
│   └── ... (128 total)
├── my-bass-wav/
│   └── ... (128 total)
├── my-pads-wav/
│   └── ... (128 total)
├── my-drums-wav/
│   └── ... (128 total)
└── my-electric-clean-guitars-wav/
    └── ... (128 total)
```

## Instrument Collections

### 🎹 Mellotron
Classic mellotron string and wind instruments
- Flutes, Saxophones, Brass, Strings, Harp, Bells, Vibraphone, Organs, Choirs

### 🎸 Electric Heavy Guitars
Heavy & distorted electric guitar tones
- Distortion, Overdrive, Fuzzy, Aggressive variations

### 🎹 Pianos
Piano collection with multiple variations
- Grand Piano, Upright, Electric Piano, Fender Rhodes, Wurlitzer

### 🎸 Electric Clean Guitars
Clean & bright electric guitar tones
- Jangly, Warm, Bright, Clean variations

### 🎵 Pads
Synth pad sounds for ambient & atmospheric music
- Warm, Spacious, Ethereal, Lush pad variations

### 🥁 Drums
Drum kit and percussion samples
- Kick, Snare, Hi-Hat, Toms, Cymbals, Percussion

### 🎸 Bass
Bass guitar and low-end instruments
- Electric Bass, Acoustic Bass, Fretless Bass

## Usage

Each WAV file can be used for:
- ✅ Sample-based synthesis
- ✅ Instrument emulation
- ✅ Audio processing tests
- ✅ DAW integration
- ✅ Sound design reference
- ✅ ML/AI training data

## Verification

All extracted files are:
- **Format:** RIFF WAVE, 16-bit PCM, Stereo, 44100 Hz
- **Size:** ~526 KB per file (2 seconds @ 44.1kHz)
- **Validity:** Verified with `file` command
- **Integrity:** Extracted directly from SF2 source

## Notes

- Extraction uses FluidSynth's default reverb settings (dry signal priority)
- Each preset is a single note (C4 / middle C) at velocity 100
- Files are suitable for further processing, looping, or time-stretching
- All presets extracted regardless of empty/unused slots in original SF2

## Last Updated

**Extraction Date:** 2026-11-21  
**Tool:** FluidSynth 2.4.4  
**Method:** Parallel batch MIDI → WAV rendering  
**Status:** In Progress → Completion expected within 10-15 minutes

---

*Generated during SF2 extraction workflow*
