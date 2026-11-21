# Quick Start Guide

## 30-Second Setup

```bash
cd /home/assaf/projects/mwave-musical-box

# Install dependencies (Ubuntu)
sudo apt-get install -y build-essential cmake qt5-qmake qtbase5-dev libsdl2-dev

# Build emulator
mkdir build && cd build
cmake -DBUILD_EMULATOR=ON ..
make -j4

# Run Hello World
./emulator/mwave_emulator
```

## What You're Looking At

**UI Mockups** (5 instrument screens):
1. **Piano UI** - Grand/Home/Old piano with tone, reverb, sustain
2. **E. Piano UI** - Rhodes/Wurlitzer with tine tuning visualization, chorus/phaser
3. **Organ UI** - Bethree engine, 9 Hammond drawbars, Leslie rotary speaker
4. **Melotron UI** - Tape transport simulation, voice stacking, analog effects
5. **Synth Pad UI** - Waveform selector, ADSR envelope, arpeggiator, LFO

Each screen shows the hardware touchscreen design with:
- Instrument selector buttons (top)
- Real-time parameter displays
- Hardware knob/slider mappings
- Status bar (MIDI, preset, voice count)

## Project Structure

| Folder | Purpose |
|--------|---------|
| `firmware/` | STM32H7 device code (C/C++) |
| `emulator/` | Qt5 desktop emulator |
| `tests/` | Unit & integration tests |
| `docs/` | Architecture, specs, hello world |
| `presets/` | Factory preset JSON files |
| `plan.json` | Development tasks (Cucumber BDD) |

## Key Files

- **README.md** - Full project overview, specs, roadmap
- **DEVELOPMENT.md** - Build instructions for firmware & emulator
- **docs/architecture.md** - System design, module breakdown, memory layout
- **docs/hello_world.md** - Emulator example walkthrough
- **CMakeLists.txt** - Master build config

## Development Phases

```
Phase 1: Foundation (Weeks 1-3)
 ├─ Build system ✓
 ├─ MIDI parsing
 ├─ Audio I/O
 └─ Basic oscillator

Phase 2: Instruments (Weeks 4-8)
 ├─ Piano (SoundFont)
 ├─ E. Piano (Rhodes/Wurlitzer)
 ├─ Organ (Bethree)
 ├─ Melotron (tape playback)
 └─ Synth (wavetable + arpeggiator)

Phase 3: Effects & Polish (Weeks 9-12)
 ├─ Reverb (Freeverb)
 ├─ Chorus/Phaser
 ├─ Hardware control mapping
 ├─ Preset system
 └─ Comprehensive testing
```

## Next: Build & Test

1. **Emulator hello world**: See `docs/hello_world.md`
2. **Architecture deep-dive**: See `docs/architecture.md`
3. **Instrument specs**: See `docs/instruments/` (to be created)
4. **Hardware specs**: See README.md specifications section

## Commands

```bash
# Build emulator only
mkdir build && cd build && cmake -DBUILD_EMULATOR=ON .. && make

# Build firmware (requires ARM toolchain)
cmake -DBUILD_FIRMWARE=ON -DCMAKE_TOOLCHAIN_FILE=../firmware/arm-toolchain.cmake ..
make

# Run tests
cmake -DBUILD_TESTS=ON .. && make && ctest

# Clean build
rm -rf build && mkdir build && cd build && cmake .. && make
```

## Resources

- **Bethree** (Hammond organ): https://github.com/sinsworld/bethree
- **Freeverb** (Reverb algorithm): https://github.com/thesloe/freeverb
- **SoundFont2 Format**: https://www.wikiwand.com/en/SoundFont
- **ARM CMSIS-DSP**: https://github.com/ARM-software/CMSIS_5
- **STM32H7 Datasheet**: ST Microelectronics official docs

## Status

- ✓ Project foundation & documentation
- ✓ UI mockups (all 5 instruments)
- ✓ Build system (CMake)
- ✓ Emulator skeleton with Hello World demo
- → **Next**: Audio synthesis implementation

---

**Questions?** See DEVELOPMENT.md or docs/architecture.md
