# MWAVE Musical Box - Architecture Overview

## System Architecture

```
┌────────────────────────────────────────────────────────────────┐
│                      Hardware Layer                            │
│  ┌──────────┬──────────┬────────────┬──────────┬──────────┐    │
│  │ STM32H7  │ Audio    │ MIDI       │ Display  │ Touch    │    │
│  │ CPU      │ DAC/ADC  │ UART       │ LCD      │ Screen   │    │
│  │ 480 MHz  │ 24-bit   │ 5-pin DIN  │ 7"       │ 16 pots  │    │
│  │ M4+DSP   │ 48kHz    │ USB        │ Touch    │ 8 fadrs  │    │
│  └──────────┴──────────┴────────────┴──────────┴──────────┘    │
└──────────┬─────────────────────────────────────────────────────┘
           │
┌──────────▼─────────────────────────────────────────────────────┐
│                    Firmware Layer (C/C++)                      │
│  ┌────────────┐  ┌──────────┐  ┌────────────┐  ┌───────────┐  │
│  │ Audio      │  │ MIDI     │  │ UI         │  │ Hardware  │  │
│  │ Engine     │  │ Parser   │  │ Driver     │  │ Drivers   │  │
│  │  Synthesis │  │ Control  │  │  Display   │  │  UART,    │  │
│  │  Polyphony │  │  CC Map  │  │  Touch     │  │  SPI, ADC │  │
│  └────────────┘  └──────────┘  └────────────┘  └───────────┘  │
│       │               │              │             │             │
│  ┌────▼────────────────▼──────────────▼─────────────▼──────┐    │
│  │            Instrument Engine & Effects                │    │
│  │  ┌────────────┐  ┌─────────┐  ┌──────────────────────┐  │    │
│  │  │ Instruments│  │ Effects │  │ Preset Manager      │  │    │
│  │  │  - Piano   │  │ - Reverb│  │  - JSON loader      │  │    │
│  │  │  - E.Piano │  │ - Chorus│  │  - SD card I/O      │  │    │
│  │  │  - Organ   │  │ - Phaser│  │  - Factory presets  │  │    │
│  │  │  - Melotron│  │ - Delay │  │                     │  │    │
│  │  │  - Synth   │  │ - Distort│ │                     │  │    │
│  │  └────────────┘  └─────────┘  └──────────────────────┘  │    │
│  └─────────────────────────────────────────────────────────┘    │
└────────────────────────────────────────────────────────────────┘
           │
┌──────────▼─────────────────────────────────────────────────────┐
│                     Emulator Layer (Qt)                        │
│  ┌────────────┐  ┌──────────┐  ┌────────────┐  ┌───────────┐  │
│  │ Qt UI      │  │ Synth    │  │ Audio      │  │ MIDI      │  │
│  │ Window     │  │ Emulator │  │ Output     │  │ Input     │  │
│  │ Controls   │  │ Core     │  │ (PortAudio)│  │ (Virtual) │  │
│  └────────────┘  └──────────┘  └────────────┘  └───────────┘  │
└────────────────────────────────────────────────────────────────┘
```

## Module Breakdown

### 1. Audio Engine (`firmware/src/audio_engine.c`)

**Responsibility:** Core audio synthesis and playback

- Voice allocation (polyphony)
- Sample-accurate timing
- Voice parameters (pitch, amplitude, envelope)
- Interleaved multi-channel output

```c
typedef struct {
  uint16_t note;      // MIDI note
  uint8_t velocity;   // 0-127
  int16_t pitch_bend; // -8192 to 8191
  float envelope;     // 0.0 to 1.0 (ADSR)
  uint32_t phase;     // Oscillator phase accumulator
} Voice;
```

### 2. MIDI Parser (`firmware/src/midi_parser.c`)

**Responsibility:** Parse MIDI events and route to instruments

- Note-on/note-off handling
- Control Change (CC) mapping
- Program Change for preset selection
- Channel filtering

**Hardware CC Mapping:**
- CC#0-15: Instrument-specific parameters
- CC#1: Modulation wheel
- CC#2: Breath controller
- CC#7: Volume
- CC#64-67: Sustain/Soft/Sostenuto pedals

### 3. Instrument Engines

Each instrument implements:
- `instrument_note_on(note, velocity)` - Trigger note
- `instrument_note_off(note)` - Release note
- `instrument_process(sample_buffer)` - Generate samples
- `instrument_set_parameter(param_id, value)` - Effect/tone control

#### 3a. Piano (`firmware/src/instruments/piano.c`)
- SoundFont2 loader for samples
- Layer system (Grand/Home/Old)
- Velocity sensitivity
- Sustain pedal (CC#64)

#### 3b. Electric Piano (`firmware/src/instruments/epiano.c`)
- Rhodes tine model (physical modeling)
- Wurlitzer FM synthesis
- Chorus & Phaser routing
- Tremolo built-in

#### 3c. Organ (`firmware/src/instruments/organ.c`)
- Bethree engine integration (GPL)
- 9 drawbar configuration (Hammond stops)
- Leslie rotary speaker effect
- Overdrive/distortion

#### 3d. Melotron (`firmware/src/instruments/melotron.c`)
- Tape playback engine
- 3 selectable tapes (Violins, Choir, Flute)
- Tape combination mode
- Tape saturation emulation

#### 3e. Synth Pad (`firmware/src/instruments/synth.c`)
- Wavetable synthesis (Sine, Triangle, Square, Saw)
- ADSR envelope
- LFO modulation
- Arpeggiator with up/down/updown modes

### 4. Effects Chain (`firmware/src/effects/`)

**Processing Order (Pre to Post):**
1. Instrument-level filters (LP/BP/HP)
2. Reverb (Freeverb algorithm)
3. Chorus (LFO-based modulation)
4. Phaser (All-pass cascades)
5. Delay (optional, low polyphony impact)
6. Distortion (tube emulation)
7. Output limiter

**Effect Parameters via Hardware:**
Each instrument maps its knobs/faders to parameters. Example for Organ:
- Knob 1 → Reverb Amount
- Knob 2 → Leslie Speed
- Knob 3 → Overdrive Intensity
- Faders 1-9 → Drawbar levels (16', 5⅓', 8', 4', 2⅔', 2', 1⅗', 1⅓', 1')

### 5. UI Driver (`firmware/src/ui/`)

- **Display Driver**: 7" LCD interface (SPI)
  - Instrument selector (touchscreen)
  - Parameter editor
  - Reverb/effect visualizers
  - Preset browser

- **Touchscreen**: Capacitive touch input
  - Buttons, sliders, faders
  - Coordinate mapping to parameters

### 6. Hardware Drivers

- **DAC**: Audio output (stereo, 24-bit, 48 kHz)
- **ADC**: Knob/fader analog input (12-bit, 8+ channels)
- **UART**: MIDI serial input (31.25 kbaud)
- **SPI**: Display communication
- **SD Card**: Preset storage and sample library

## Memory Layout (STM32H7)

```
Typical Allocation:
┌─────────────────────────────┐
│ Flash (2 MB)                │
├─────────────────────────────┤
│ Firmware Code       (~500 KB)│
│ SoundFont/Samples   (~1 MB)  │
│ Factory Presets     (~200 KB)│
│ Bethree Engine      (~300 KB)│
└─────────────────────────────┘

┌─────────────────────────────┐
│ RAM (512 KB)                │
├─────────────────────────────┤
│ Audio Buffers        (~100 KB)│ (DMA double-buffering)
│ Voice State          (~50 KB) │ (32 voices × 1.5 KB)
│ Effects State        (~50 KB) │ (Reverb, Chorus taps)
│ MIDI Queue           (~4 KB)  │
│ UI State             (~10 KB) │
│ Stack                (~50 KB) │
│ Heap                 (~248 KB)│
└─────────────────────────────┘
```

## Real-time Constraints

**Audio Processing:**
- Sample Rate: 48 kHz (20.83 µs per sample)
- Buffer Size: 128 samples (2.67 ms latency)
- CPU Budget: ~40% at 480 MHz for headroom
- Voice Count: 32 polyphonic voices max

**Control Loop:**
- UI Update: ~50 ms (20 Hz refresh)
- MIDI Parse: Real-time, <1 ms per event
- Effect Computation: Within audio buffer window

## Data Flow Example: Playing a Note

```
1. MIDI Input (USB or 5-pin DIN)
   → UART Interrupt Handler
   → midi_parser_process()

2. Note-On Event
   → Find free voice
   → instrument_note_on(note=60, velocity=100)
   → Synth generates first samples

3. Audio Processing (ISR, every 128 samples)
   → Oscillator phase update
   → Envelope modulation
   → Effects processing
   → Output to DAC

4. UI Update (async)
   → Display voice count
   → Visualize envelope
   → Update active preset indicator
```

## Extensibility

### Adding a New Instrument

1. Create `firmware/src/instruments/new_instrument.c`
2. Implement interface:
   ```c
   void new_instrument_note_on(uint8_t note, uint8_t velocity);
   void new_instrument_note_off(uint8_t note);
   int16_t new_instrument_process(void);
   void new_instrument_set_param(uint8_t param, float value);
   ```
3. Register in `firmware/src/audio_engine.c`
4. Add CC mappings in `firmware/src/midi_parser.c`

### Adding a New Effect

1. Create `firmware/src/effects/new_effect.c`
2. Implement DSP algorithm
3. Chain in `audio_engine.c` effects processing loop
4. Map hardware controls

### Open Source Libraries

- **Bethree** (GPL v3): Hammond organ emulation
- **Freeverb** (Public Domain): Room reverb
- **CMSIS-DSP** (ARM License): ARM DSP library
- **SoundFont2** (CC0): Instrument sample format

## Testing Strategy

- **Unit Tests**: CMSIS-DAP via GDB (firmware on device)
- **Integration Tests**: Emulator testing with MIDI input
- **Performance Tests**: Profiling with STM32 STLink utility
- **Regression Tests**: Automated Cucumber BDD scenarios

## Performance Targets

| Metric | Target | Actual |
|--------|--------|--------|
| CPU Usage @ 32 voices | <50% | (TBD) |
| Audio Latency | <5 ms | (TBD) |
| MIDI Latency | <10 ms | (TBD) |
| Effect CPU @ max | <30% | (TBD) |
| Temperature (board) | <70°C | (TBD) |

---

**Last Updated:** 2026-11-21
**Maintainers:** Synth firmware team
