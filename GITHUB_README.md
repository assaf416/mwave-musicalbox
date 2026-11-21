# 🎹 MWAVE Musical Box - Open Source Firmware

Professional synthesizer firmware for MWAVE FM-1 and SMK-37 synthesizers targeting prog rock and contemporary keyboard players.

## Overview

A modern, modular open-source firmware for MWAVE synthesizers, featuring industry-standard instruments with hardware control mapping, MIDI support, and extensible preset system.

**Status:** 🔄 Active Development | Phase 1: Foundation Complete

## Features

### 🎵 Instruments (5 Families)
- **Piano** - Grand, Home, Old piano models with velocity-sensitive touch
- **Electric Piano** - Rhodes and Wurlitzer emulation with chorus/phaser
- **Organ** - Hammond-style with 9 drawbars and Leslie rotary speaker (Bethree engine)
- **Melotron** - Tape-based with MK400 Violins, Choir, Flute + SoundFont2 support
- **Synth Pad** - Wavetable arpeggiator with ADSR envelope and LFO

### 🎛️ Hardware Control
- **16 velocity-sensitive knobs** (FM-1)
- **8 motorized faders** with feedback (FM-1)
- **16 RGB buttons** for quick access (FM-1)
- **8 capacitive touch sliders** (SMK-37)
- **7-inch touchscreen** (FM-1) or 3-inch OLED (SMK-37)
- **MIDI input** via USB + 5-pin DIN

### ⚙️ Audio Engine
- **24-bit audio @ 48 kHz** stereo
- **32-voice polyphony** (FM-1) or 16-voice (SMK-37)
- **Multi-effect processing**: Reverb, Chorus, Phaser, Delay, Distortion
- **Reverb algorithm**: Freeverb (open source)
- **Effects routing**: Per-instrument effect chains

### 📱 UI/UX
- **Professional design system** with instrument-specific color themes
- **Real-time parameter visualization**
- **Preset management** with SD card storage
- **Comprehensive status display** with voice count and MIDI indicators

## Project Status

| Phase | Status | Effort |
|-------|--------|--------|
| **Foundation** | ✅ Complete | - |
| **Emulator** | ✅ Complete | 2026-11-21 |
| **Melotron SF2** | ✅ Integrated | 2026-11-21 |
| **Full Sample Playback** | 🔄 In Progress | - |
| **Hardware Control** | ⏳ Planned | - |
| **Testing Suite** | ⏳ Planned | - |

## Quick Start

### Build Emulator
```bash
mkdir build && cd build
cmake -DBUILD_EMULATOR=ON ..
make -j4

# Run emulator
./emulator/mwave_emulator
```

### Run Hello World Demo
```
> P          # Play melody
> I          # Select instrument
2            # Choose Organ (or any 0-4)
> R          # Adjust reverb
75           # Set to 75%
> Q          # Quit
```

## Development Stack

- **Language**: C++17 (firmware), C++ (emulator)
- **Build**: CMake + GCC ARM cross-compiler
- **Testing**: Unity + Ceedling
- **UI**: Qt5 (emulator), embedded C (device)
- **DSP**: CMSIS-DSP, Freeverb, custom synthesis
- **MIDI**: Standard MIDI 1.0 (180+ CC mappings)
- **SoundFonts**: SoundFont2 format support

## Repository Structure

```
mwave-musicalbox/
├── firmware/              # Device firmware (STM32H7)
├── emulator/              # Desktop emulator (Qt5)
├── tests/                 # Unit & integration tests
├── docs/                  # Architecture & specs
├── presets/              # Factory presets (JSON)
├── plan.json             # Development tasks (Cucumber BDD)
├── README.md             # Main documentation
├── DEVELOPMENT.md        # Setup instructions
├── MELOTRON_INTEGRATION.md # SF2 integration guide
└── CMakeLists.txt        # Master build config
```

## Documentation

| Document | Purpose |
|----------|---------|
| [README.md](README.md) | Complete project specification |
| [DEVELOPMENT.md](DEVELOPMENT.md) | Build & setup instructions |
| [QUICKSTART.md](QUICKSTART.md) | 30-second quick start |
| [EMULATOR_USAGE.md](EMULATOR_USAGE.md) | Emulator menu reference |
| [docs/architecture.md](docs/architecture.md) | System design & internals |
| [docs/hello_world.md](docs/hello_world.md) | Hello World tutorial |
| [MELOTRON_INTEGRATION.md](MELOTRON_INTEGRATION.md) | SoundFont2 integration |
| [MWAVE-FM1-User-Manual.md](MWAVE-FM1-User-Manual.md) | FM-1 complete manual |
| [MWAVE-SMK37-User-Manual.md](MWAVE-SMK37-User-Manual.md) | SMK-37 portable manual |
| [MWAVE-CC-Parameter-Reference.md](MWAVE-CC-Parameter-Reference.md) | 180+ MIDI CC mappings |
| [MWAVE-Screenshot-Guide.md](MWAVE-Screenshot-Guide.md) | UI mockups & design |

## Hardware Specifications

### FM-1
- **CPU**: ARM Cortex-M4 @ 480 MHz
- **Memory**: 256 KB RAM + 4 MB Flash
- **Audio**: 24-bit @ 48 kHz stereo
- **Controls**: 16 knobs, 8 faders, 16 buttons
- **Display**: 7" touchscreen (1024×600)
- **MIDI**: USB + 5-pin DIN
- **Power**: 100-240V AC, 60W max

### SMK-37
- **CPU**: ARM Cortex-M4 @ 240 MHz
- **Memory**: 128 KB RAM + 2 MB Flash
- **Audio**: 24-bit @ 48 kHz (3.5mm jack)
- **Controls**: 8 touch sliders, 5 mode buttons
- **Display**: 3" OLED monochrome (128×64)
- **MIDI**: USB Type-C
- **Power**: USB or AA batteries (8-10 hours)
- **Weight**: 1.2 kg (portable)

## Open Source Credits

- **Bethree** - GPL-licensed Hammond organ emulator
- **Freeverb** - Public domain reverb algorithm
- **CMSIS-DSP** - ARM Cortex-M DSP library
- **SoundFont2** - Open instrument sample format

## Roadmap

### Phase 1: Foundation ✅ DONE
- Project structure & build system
- Emulator framework with Hello World demo
- Comprehensive documentation (1,100+ lines)

### Phase 2: Audio Synthesis 🔄 IN PROGRESS
- Real-time sample playback from SoundFont2
- Pitch shifting and loop processing
- Tape effects (wobble, flutter, saturation)

### Phase 3: Instruments ⏳ PLANNED
- Complete piano, electric piano implementation
- Organ with full drawbar support
- Melotron with actual tape playback

### Phase 4: Effects & Polish ⏳ PLANNED
- Complete effects chain
- Hardware control mapping
- Preset management UI

### Phase 5: Testing & Release ⏳ PLANNED
- Comprehensive test suite
- Device firmware compilation
- Hardware testing

## License

**GPL v3.0** - Compatible with Bethree and other GPL libraries

The firmware is open source and available for personal and commercial use under GPL v3.0 terms.

## Support

- 📧 **Email**: (GitHub issues)
- 🐛 **Report Issues**: [GitHub Issues](https://github.com/assaf416/mwave-musicalbox/issues)
- 💬 **Discussions**: [GitHub Discussions](https://github.com/assaf416/mwave-musicalbox/discussions)
- 📖 **Wiki**: [Project Wiki](https://github.com/assaf416/mwave-musicalbox/wiki)

## Development

```bash
# Clone repository
git clone https://github.com/assaf416/mwave-musicalbox.git
cd mwave-musicalbox

# Install dependencies (Ubuntu/Debian)
sudo apt-get install build-essential cmake qt5-qmake qtbase5-dev libsdl2-dev

# Build emulator
mkdir build && cd build
cmake -DBUILD_EMULATOR=ON ..
make -j4

# Run emulator
./emulator/mwave_emulator
```

## Contributing

Contributions welcome! Areas of focus:
- SoundFont2 sample playback implementation
- Hardware effects (reverb, chorus, phaser)
- Preset management system
- Firmware optimization
- Testing & documentation

## Changelog

### Latest (2026-11-21)
- ✅ Emulator with Hello World demo working
- ✅ Melotron SoundFont2 integration (foundation)
- ✅ Comprehensive documentation (1,100+ lines)
- ✅ 180+ MIDI CC parameter mappings
- ✅ 5 UI mockups for all instruments

### Previous Milestones
- Initial project foundation with build system
- Complete architecture documentation
- Professional user manuals for both synths

## Author

**MWAVE Synth Team** | Professional Audio Solutions

Developed with [Claude AI](https://claude.ai)

---

**Repository**: [github.com/assaf416/mwave-musicalbox](https://github.com/assaf416/mwave-musicalbox)  
**License**: GPL v3.0  
**Status**: 🔄 Active Development
