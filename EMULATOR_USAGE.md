# MWAVE Emulator - Usage Guide

## Quick Start

```bash
cd /home/assaf/projects/mwave-musical-box
./build/emulator/mwave_emulator
```

## Menu Commands

Once the emulator is running, use these commands:

| Command | Action | Notes |
|---------|--------|-------|
| **P** | Play Hello World | Plays the 8-note C-C-C-D-E-C-E-G melody |
| **S** | Stop All Notes | Halts all currently playing notes |
| **I** | Select Instrument | Prompts to choose 0-4 (Piano, E.Piano, Organ, Melotron, Synth) |
| **R** | Adjust Reverb | Prompts for reverb amount (0-100%) |
| **Q** | Quit | Exits the emulator |

## Example Session

```
> P
▶ Playing Hello World melody on Piano...
  ♪ Note 60 (velocity 100)   # C
  ♪ Note 60 (velocity 100)   # C
  ♪ Note 60 (velocity 100)   # C
  ♪ Note 62 (velocity 100)   # D
  ♪ Note 64 (velocity 100)   # E
  ♪ Note 60 (velocity 100)   # C
  ♪ Note 64 (velocity 100)   # E
  ♪ Note 67 (velocity 100)   # G
✓ Melody complete!

> I
Select instrument (0-4): 2
✓ Instrument changed

> R
Enter reverb amount (0-100): 75
✓ Reverb set to 75%

> Q
✓ Goodbye!
```

## Understanding the Output

### Display Layout

```
┌─ Instruments ─────────────────────────────────────────────┐
│ → [0] Piano                                            │
│   [1] Electric Piano                                   │
│   [2] Organ                                            │
│   [3] Melotron                                         │
│   [4] Synth Pad                                        │
└───────────────────────────────────────────────────────────┘

┌─ Status ──────────────────────────────────────────────────┐
│ Current Instrument: Piano                                  │
│ Active Voices:      0    /32                                 │
│ Reverb Amount:      50 %                                         │
│ MIDI Status:        READY                            │
└───────────────────────────────────────────────────────────┘
```

- **Current Instrument**: Which instrument is selected
- **Active Voices**: How many simultaneous notes are playing (max 32)
- **Reverb Amount**: Current reverb effect level (0-100%)
- **MIDI Status**: Connection status (always READY in emulator mode)

### Audio Synthesis Log

When a note plays, you'll see detailed logs:

```
[SynthEmulator] Playing MIDI note: 60 velocity: 100
[Synth] Generating tone at 261.626 Hz with velocity 100
[AudioOutput] Playing tone: 261.626 Hz at amplitude 0.393701
[AudioOutput] Generated 4410 samples for audio playback
```

This shows:
- **MIDI Note**: Note number (60 = Middle C)
- **Velocity**: Volume (0-127)
- **Frequency**: The tone's frequency in Hz
- **Amplitude**: Volume level (0.0-1.0)
- **Samples**: Generated buffer size (4410 samples = 100ms @ 44.1kHz)

## Frequency Reference

| Note | MIDI | Frequency |
|------|------|-----------|
| C | 60 | 261.626 Hz |
| D | 62 | 293.665 Hz |
| E | 64 | 329.628 Hz |
| G | 67 | 391.995 Hz |

Formula: `Frequency = 440 * 2^((note - 69) / 12)`

## Rebuilding After Code Changes

```bash
cd /home/assaf/projects/mwave-musical-box/build
make -j4
./emulator/mwave_emulator
```

Or full rebuild:

```bash
cd /home/assaf/projects/mwave-musical-box
rm -rf build
mkdir build && cd build
cmake -DBUILD_EMULATOR=ON ..
make -j4
./emulator/mwave_emulator
```

## Current Status

✅ **Working:**
- Console-based UI with menu
- Instrument selection (5 instruments)
- Hello World melody playback
- MIDI note-to-frequency conversion
- Voice tracking (0-32 voices)
- Reverb control parameter
- Audio buffer generation

🔄 **Next Phase:**
- Actual audio playback (PortAudio backend)
- Real-time synthesis with envelope
- Effect processing (reverb, chorus, phaser)
- MIDI keyboard input support
- Load SoundFont2 samples for piano

## Architecture

```
Console UI Menu
     ↓
Command Handler (P/S/I/R/Q)
     ↓
SynthEmulator (playNote, setInstrument)
     ↓
AudioOutput (playTone, generate samples)
     ↓
Audio Buffer (ready for playback)
```

## Troubleshooting

**Q: Emulator doesn't run**
- Check if built: `ls build/emulator/mwave_emulator`
- If missing, run: `cd build && make -j4`

**Q: Can't hear audio**
- Emulator currently generates samples but doesn't play them
- Waiting for PortAudio backend integration
- Check output logs for synthesis activity

**Q: Need to change something?**
- Rebuild: `cd build && make -j4`
- Full clean: `rm -rf build && mkdir build && cd build && cmake .. && make`

## Development Roadmap

| Phase | Status | Focus |
|-------|--------|-------|
| Phase 1: Foundation | ✅ Done | Build system, emulator skeleton, Hello World |
| Phase 2: Audio Synthesis | 🔄 Active | Oscillator, envelope, real playback |
| Phase 3: Instruments | ⏳ Planned | Piano samples, E.piano, organ, melotron, synth |
| Phase 4: Effects | ⏳ Planned | Reverb, chorus, phaser, delay |
| Phase 5: Hardware | ⏳ Planned | Cross-compile for STM32H7, device testing |

---

**Questions?** See [docs/hello_world.md](docs/hello_world.md) or [docs/architecture.md](docs/architecture.md)
