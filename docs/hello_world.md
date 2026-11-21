# MWAVE Musical Box - Hello World Example

## Overview

This example demonstrates the MWAVE emulator running a simple "Hello World" melody synthesis.

## Building the Emulator

### Prerequisites

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get install -y \
  build-essential cmake \
  qt5-qmake qtbase5-dev \
  libsdl2-dev
```

**macOS:**
```bash
brew install cmake qt5 sdl2
```

### Build Steps

```bash
cd /home/assaf/projects/mwave-musical-box

# Create build directory
mkdir -p build && cd build

# Configure CMake for emulator only
cmake -DBUILD_EMULATOR=ON -DBUILD_FIRMWARE=OFF ..

# Build
make -j4

# Run emulator
./emulator/mwave_emulator
```

## Running the Hello World Example

1. **Launch the Emulator:**
   ```
   ./emulator/mwave_emulator
   ```

2. **UI Window Opens:**
   - You'll see the main MWAVE emulator window
   - Instrument selector showing Piano, Electric Piano, Organ, Melotron, Synth
   - Control buttons: "Play Hello World" and "Stop"
   - Reverb slider for effects control

3. **Click "Play Hello World":**
   - The emulator will generate a simple 8-note melody
   - Notes: C-C-C-D-E-C-E-G (C major scale arpeggio)
   - Plays on the current instrument (default: Piano)
   - Status display shows "Playing Hello World melody..."

4. **Change Instruments:**
   - Use the instrument selector dropdown
   - Switch between Piano, E.Piano, Organ, Melotron, Synth
   - Each instrument will play the same melody with different timbres

5. **Adjust Effects:**
   - Use the Reverb slider (0-100%)
   - Watch the status display update voice count and reverb level

## Code Structure

### Key Files

| File | Purpose |
|------|---------|
| `emulator/src/main.cpp` | Qt application entry point |
| `emulator/src/ui_window.cpp` | Main UI window and controls |
| `emulator/src/synth_emulator.cpp` | Synthesis engine controller |
| `emulator/src/audio_output.cpp` | Audio generation and playback |
| `emulator/src/midi_input.cpp` | MIDI input handler (stub) |

### MIDI Note to Frequency Conversion

```
Frequency = 440 * 2^((note - 69) / 12)

Example:
- Middle C (note 60): 262 Hz
- A4 (note 69): 440 Hz
- C5 (note 72): 523 Hz
```

## Hello World Melody

| Note | MIDI | Frequency |
|------|------|-----------|
| C | 60 | 262 Hz |
| C | 60 | 262 Hz |
| C | 60 | 262 Hz |
| D | 62 | 294 Hz |
| E | 64 | 330 Hz |
| C | 60 | 262 Hz |
| E | 64 | 330 Hz |
| G | 67 | 392 Hz |

## Next Steps

### Phase 1: Foundation
- [ ] Implement actual audio synthesis (sine wave oscillator)
- [ ] Connect Qt audio output (QAudioOutput or PortAudio)
- [ ] Add note-on/note-off timing and envelope
- [ ] Test with actual MIDI keyboard input

### Phase 2: Instruments
- [ ] Load SoundFont2 files for piano samples
- [ ] Implement polyphonic voice allocation
- [ ] Add velocity sensitivity and dynamics

### Phase 3: Effects
- [ ] Freeverb reverb algorithm
- [ ] LFO-based chorus
- [ ] Phaser effect

### Phase 4: Hardware
- [ ] Cross-compile firmware for STM32H7
- [ ] Test on actual MWAVE device
- [ ] Map hardware controls (knobs, faders, buttons)

## Troubleshooting

### Qt not found
```bash
# Ubuntu
sudo apt-get install qt5-default

# macOS  
brew reinstall qt5
```

### Audio not working
- Check ALSA/PulseAudio on Linux: `aplay -l`
- Check macOS CoreAudio: System Preferences → Sound
- Verify SDL2 installed: `pkg-config --cflags --libs sdl2`

### Build fails
```bash
# Clean build
rm -rf build && mkdir build && cd build
cmake -DBUILD_EMULATOR=ON -DBUILD_FIRMWARE=OFF ..
make -j4
```

## Architecture

```
┌─────────────────────────────────────────┐
│         Qt Application (main)           │
└──────────────────┬──────────────────────┘
                   │
       ┌───────────┴────────────┐
       │                        │
   ┌───▼───────┐        ┌──────▼─────┐
   │ UI Window │        │   Synth    │
   │           │        │  Emulator  │
   └───┬───────┘        │            │
       │                └──────┬─────┘
       │   Controls            │  
       │   & Display           │  Synth Control
       │                       │
       └───────────┬───────────┘
                   │
            ┌──────▼──────────┐
            │  Audio Output   │
            │  & Synthesis    │
            └─────────────────┘
                    │
                    ▼ Audio Samples
            ┌───────────────────┐
            │  System Speaker   │
            └───────────────────┘
```

## See Also

- [Architecture Documentation](architecture.md)
- [MIDI Specification](midi_specification.md)
- [Instrument Specifications](instruments/)
- [Development Guide](../DEVELOPMENT.md)
