# Development Setup Guide

## Prerequisites

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install -y \
  build-essential \
  cmake \
  git \
  arm-none-eabi-gcc arm-none-eabi-g++ arm-none-eabi-binutils \
  libsdl2-dev libsdl2-mixer-dev \
  qt5-qmake qtbase5-dev \
  libjack-jackd2-dev \
  libsndfile1-dev
```

### macOS
```bash
brew install cmake arm-gcc-arm-none-eabi sdl2 qt5 jack
```

### Windows (MSYS2)
```bash
pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-arm-none-eabi-gcc mingw-w64-x86_64-arm-none-eabi-binutils mingw-w64-x86_64-sdl2 mingw-w64-x86_64-qt5
```

## Building

### Project Structure Setup
```bash
cd /home/assaf/projects/mwave-musical-box

# Create folder structure
mkdir -p firmware/{src,libs,include}
mkdir -p emulator/{src,resources}
mkdir -p tests/{unit,integration}
mkdir -p docs presets

# Initialize git
git init
git config user.email "assaf.g@comtecglobal.com"
git config user.name "Assaf G"
git add .
git commit -m "Initial commit: project structure"
```

### Build Emulator (Desktop)
```bash
mkdir build && cd build
cmake -DBUILD_EMULATOR=ON ..
make -j4
./emulator/mwave_emulator
```

### Build Firmware (Device)
```bash
mkdir build && cd build
cmake -DBUILD_FIRMWARE=ON -DCMAKE_TOOLCHAIN_FILE=../firmware/arm-toolchain.cmake ..
make -j4
# Output: build/firmware/mwave_firmware.elf
# Flash: st-flash write build/firmware/mwave_firmware.bin 0x08000000
```

### Run Tests
```bash
mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
make -j4
ctest --verbose
```

## Directory Organization

- **firmware/**: ARM embedded C/C++ code for MWAVE devices
- **emulator/**: Qt-based desktop emulator for development & testing
- **tests/**: Unit tests (Unity framework) & integration tests
- **docs/**: Architecture docs, protocol specs, design notes
- **presets/**: Factory presets in JSON format
- **sf2-files/**: SoundFont2 instrument libraries

## Development Workflow

1. **Design** in `docs/`
2. **Implement** in `firmware/src/` or `emulator/src/`
3. **Test** with `tests/unit/` or `tests/integration/`
4. **Emulate** with `./emulator/mwave_emulator` before device testing
5. **Document** in `docs/`

## Key Files

- `CMakeLists.txt` - Main build configuration
- `firmware/arm-toolchain.cmake` - ARM cross-compiler configuration
- `emulator/CMakeLists.txt` - Emulator-specific build
- `tests/CMakeLists.txt` - Test suite configuration

## Debugging

### Firmware (via GDB + ST-Link)
```bash
arm-none-eabi-gdb build/firmware/mwave_firmware.elf
target remote :4242  # Requires st-util running
break main
continue
```

### Emulator
```bash
gdb ./build/emulator/mwave_emulator
# Standard GDB debugging
```

## Next Steps

1. Run the emulator: `./build/emulator/mwave_emulator`
2. See "Hello World" example in `docs/hello_world.md`
3. Review instrument specs in `docs/instruments/`
