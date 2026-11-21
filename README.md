# MWAVE Musical Box - Open Source Firmware

Professional synthesizer firmware for MWAVE FM-1 and SMK-37 synthesizers, targeting prog rock and contemporary keyboard players.

## Overview

A modern, modular open-source firmware replacing the stock MWAVE synth controllers, featuring industry-standard instruments with hardware control mapping, MIDI support, and extensible preset system.

## Target Hardware

- **MWAVE FM-1 Synthesizer**
- **MWAVE SMK-37 Synthesizer**

### Assumed Hardware Specs
- CPU: ARM Cortex-M4 (STM32H7 series) or similar
- RAM: 256-512 KB
- Storage: 1-4 MB Flash + SD card support
- Audio I/O: 24-bit stereo @ 48kHz
- MIDI: USB + 5-pin DIN
- UI: 7" LCD touchscreen + 16 knobs + 8 faders + 16 buttons
- Audio Engine: Polyphonic (32+ voices)

## Instruments

### 1. **Piano Family**
- Grand Piano (concert sound)
- Home Piano (compact, intimate)
- Old Piano (vintage character)
- Features: Tone control, reverb, touch dynamics
- UI: Keyboard view with pedal indicators

### 2. **Electric Piano**
- Rhodes (vintage electric piano)
- Wurlitzer (bright, percussive)
- Features: Chorus, phaser, bell tone
- UI: Tine tuning visualization

### 3. **Organ**
- Drawbar Organ (Hammond-style)
- Overdrive and Leslie (rotating speaker)
- Features: 9-drawbar configuration, expression pedal control
- UI: Drawbar sliders + Leslie speed knob
- Library: Integration with open-source **Bethree** organ engine

### 4. **Melotron**
- MK400 Violins
- Choir
- Flute
- Combination: All three stacked
- Features: Reverb, tape saturation
- UI: Tape counter, source selector, reverb/delay

### 5. **Polyphonic Synthesizers**
- Arpeggiator Synth (8-voice pad)
- String Synth (lush pad)
- Features: Chorus, reverb, filter envelope
- UI: Waveform selector, envelope editor, LFO

## Development Stack

### Firmware
- **Language**: C/C++ (ARM embedded)
- **Build System**: CMake + GCC ARM
- **Testing**: Unity testing framework + Ceedling
- **Version Control**: Git

### DSP & Audio
- **DSP Library**: CMSIS-DSP (ARM)
- **Sample Playback**: Custom streaming engine
- **Effects**: Reverb (Freeverb), Chorus (LFO-based), Phaser
- **Organ Engine**: Bethree (GPL-licensed Hammond clone)

### MIDI & Control
- **MIDI Parser**: ALSA MIDI (Linux) / USB MIDI (device)
- **Parameter Mapping**: 16 knobs + 8 faders → effect/instrument parameters
- **Preset System**: JSON-based, stored on SD card

### UI
- **Display**: Qt-based for emulator, embedded C for device
- **Touch Input**: Capacitive touchscreen driver
- **Graphics**: Lightweight 2D rendering (Cairo for emulator)

### Emulator
- **Platform**: Linux/macOS/Windows
- **Graphics**: Qt/SDL2
- **Audio**: JACK or PortAudio
- **MIDI**: Virtual MIDI ports

## Project Structure

```
mwave-musical-box/
├── firmware/              # Device firmware
│   ├── src/
│   │   ├── main.c
│   │   ├── synth/        # Audio engine
│   │   ├── midi/         # MIDI input handling
│   │   ├── ui/           # UI drivers
│   │   └── effects/      # DSP effects
│   ├── libs/             # Third-party libraries
│   ├── CMakeLists.txt
│   └── linker_script.ld
├── emulator/             # Desktop emulator
│   ├── src/
│   ├── CMakeLists.txt
│   └── resources/
├── tests/               # Unit and integration tests
│   ├── unit/
│   └── integration/
├── docs/                # Documentation
│   ├── architecture.md
│   ├── midi_specification.md
│   └── preset_format.md
├── presets/             # Factory presets (JSON)
├── plan.json           # Development tracking
└── DEVELOPMENT.md      # Setup instructions
```

## Roadmap

### Phase 1: Foundation
- [ ] Project setup & build system
- [ ] MIDI input layer
- [ ] Basic audio I/O
- [ ] Simple waveform synthesis
- [ ] Emulator framework

### Phase 2: Core Instruments
- [ ] Piano engine (SoundFont-based)
- [ ] Electric piano (Rhodes)
- [ ] Basic organ (drawbars)

### Phase 3: Advanced Instruments
- [ ] Melotron tape playback
- [ ] Arpeggiator synth
- [ ] String pad

### Phase 4: Effects & Polishing
- [ ] Effects chain (reverb, chorus, phaser)
- [ ] Preset management
- [ ] Hardware control mapping
- [ ] UI refinement

### Phase 5: Testing & Documentation
- [ ] Comprehensive test suite
- [ ] User manual
- [ ] Developer guide

## Getting Started

See [DEVELOPMENT.md](DEVELOPMENT.md) for setup instructions.

## Open Source Credits

- **Bethree**: GPL-licensed Hammond organ emulator
- **SoundFont**: SF2 format for instrument samples
- **Freeverb**: GPL reverb algorithm
- **CMSIS-DSP**: ARM Cortex-M DSP library

## License

GPL v3.0 (compatible with Bethree and other GPL libraries)
