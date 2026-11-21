# MWAVE FM-1 Professional Digital Synthesizer
## User Manual & Technical Reference

**Version 1.0** | November 2026

---

## TABLE OF CONTENTS

1. [Product Overview](#product-overview)
2. [Hardware Specifications](#hardware-specifications)
3. [Getting Started](#getting-started)
4. [Instrument Guide](#instrument-guide)
5. [Control Reference](#control-reference)
6. [Effects Processing](#effects-processing)
7. [MIDI Specifications](#midi-specifications)
8. [Troubleshooting](#troubleshooting)
9. [Technical Specifications](#technical-specifications)
10. [Warranty & Support](#warranty--support)

---

## PRODUCT OVERVIEW

The MWAVE FM-1 is a professional-grade digital synthesizer designed for modern keyboardists and musicians. With open-source firmware, 32-voice polyphony, and comprehensive effects processing, the FM-1 delivers studio-quality sound in a compact form factor suitable for stage and studio use.

### Key Features

- ✓ **32-voice polyphonic synthesizer**
- ✓ **5 instrument families**: Piano, Electric Piano, Organ, Melotron, Synth
- ✓ **24-bit audio @ 48 kHz** sample rate
- ✓ **Stereo output** with multi-effects processing
- ✓ **16 velocity-sensitive hardware knobs**
- ✓ **8 motorized faders** for real-time control
- ✓ **7-inch capacitive touchscreen** interface
- ✓ **MIDI input** (USB + 5-pin DIN)
- ✓ **SD card slot** for preset storage
- ✓ **Open-source GPL v3 firmware**
- ✓ **Hardware effects**: Reverb, Chorus, Phaser, Delay

---

## HARDWARE SPECIFICATIONS

| Parameter | Specification |
|-----------|---------------|
| **Processor** | ARM Cortex-M4 @ 480 MHz |
| **Memory** | 256 KB RAM + 4 MB Flash |
| **Audio I/O** | Stereo RCA line-out, 24-bit @ 48 kHz |
| **MIDI Input** | USB Type-B + 5-pin DIN |
| **Controls** | 16 rotary knobs + 8 motorized faders + 16 buttons |
| **Display** | 7-inch capacitive touchscreen (1024×600) |
| **Storage** | SD card slot (up to 32 GB) |
| **Power** | 100-240V AC, 60W max |
| **Dimensions** | 880mm (W) × 120mm (H) × 280mm (D) |
| **Weight** | 8.5 kg |
| **Operating Temp** | 0°C to 40°C |

---

## GETTING STARTED

### Power On
Connect AC power and press the power button. The display will initialize and show the main instrument selector within 3 seconds.

### Select Instrument
Use the touchscreen to select from Piano, Electric Piano, Organ, Melotron, or Synth Pad. Each instrument has its own preset library.

### Connect MIDI
Plug a MIDI keyboard into the USB or 5-pin DIN input. The MIDI indicator on the display will show "ACTIVE" when a keyboard is detected.

### Adjust Output
Use the volume fader (Fader 1) to control output level. Set to -6dB for balanced headroom.

### Load Presets
Press the PRESET button to browse saved configurations. Use faders to adjust instrument parameters in real-time.

---

## INSTRUMENT GUIDE

### Piano
Grand, Home, and Old piano models with velocity-sensitive touch. Features tone control and global reverb. Ideal for classical and contemporary music.

**Controls:**
- Knob 1: Reverb Amount (0-100%)
- Knob 2: Tone Brightness (Dark to Bright)
- Button SUSTAIN: Toggle sustain pedal
- Fader 1: Master Volume

**Presets:**
- Grand Piano Bright
- Home Piano Warm
- Old Piano Vintage
- Concert Grand (stereo)

### Electric Piano
Authentic Rhodes and Wurlitzer emulation with built-in chorus and phaser. Includes tine-tuning visualization and bell-tone controls.

**Controls:**
- Knob 1: Tone (Warm to Bright)
- Knob 2: Chorus Depth
- Knob 3: Phaser Rate
- Fader 1: Reverb Mix

**Presets:**
- Rhodes Classic
- Wurlitzer Funky
- Fender Rhodes Bright
- Tine Organ Blend

### Organ
Hammond-style organ with 9 drawbars, Leslie rotary speaker, and overdrive. Integrates open-source Bethree engine. Perfect for prog rock and soul.

**Controls:**
- Faders 1-9: Drawbar levels (16', 5⅓', 8', 4', 2⅔', 2', 1⅗', 1⅓', 1')
- Knob 1: Leslie Speed
- Knob 2: Overdrive
- Button LESLIE: Toggle rotary speaker

**Presets:**
- Full Gospel
- Soul Drawbars
- Classic B3
- Prog Rock Deep

### Melotron
Tape-based synthesis with MK400 Violins, Choir, and Flute. Supports tape layering and analog saturation effects.

**Controls:**
- Knob 1: Tape Saturation
- Knob 2: Reverb Amount
- Button LAYER: Combine multiple voices
- Tape Position Display: Visual feedback

**Presets:**
- Violins Classic
- Choir + Flute Blend
- Mellotron Lush
- Tape Warmth

### Synth Pad
Wavetable synthesis with arpeggiator, 8-voice polyphony, and full ADSR envelope. LFO modulation for lush pad sounds.

**Controls:**
- Knob 1: Filter Cutoff
- Knob 2: LFO Rate
- Knob 3: Reverb
- Faders 1-4: ADSR (Attack, Decay, Sustain, Release)
- Button ARP: Toggle arpeggiator

**Presets:**
- Lush Pad
- Bright String
- Arpeggio Up/Down
- Ambient Synth

---

## CONTROL REFERENCE

### Knobs (1-16)
Each instrument maps knobs to its unique parameters. Rotary encoders provide infinite precision. 

**Common Mappings:**
- Knob 1 = Reverb Amount
- Knob 2 = Filter Cutoff / Tone
- Knob 3 = Chorus Depth / LFO Rate
- Knobs 4-16 = Instrument-specific effects

### Faders (1-8)
Motorized faders provide visual feedback. 

**Standard Layout:**
- **Fader 1**: Master Volume
- **Faders 2-9**: Instrument-specific controls
  - Organ: Drawbar 16', 8', 4', 2' (Faders 1-4)
  - Synth: Attack, Decay, Sustain, Release (Faders 1-4)
  - Piano: Volume, Tone, Reverb, Sustain (Faders 1-4)

Faders remember position on preset change.

### Buttons (1-16)
16 RGB buttons for quick access to functions.

**Button Colors:**
- **Red** = Active/Warning
- **Green** = On/Enabled
- **Blue** = Standby

**Common Functions:**
- Button 1: Instrument Selector
- Button 2: Effects On/Off
- Button 3: Tap Tempo
- Button 4: Sustain Pedal (Piano/E.Piano)
- Button 5: Leslie Toggle (Organ)
- Button 6: Arpeggiator (Synth)

---

## EFFECTS PROCESSING

The FM-1 includes a professional multi-effects chain processing all instruments in real-time.

### Reverb (Freeverb Algorithm)
**Parameters:**
- Room size: 0-100%
- Wet/Dry mix: 0-100%
- Pre-delay: 0-100ms
- Damping: 0-100%

**Optimal Settings:**
- Chamber: 30% room, 60% wet
- Hall: 70% room, 50% wet
- Large: 90% room, 40% wet

### Chorus (LFO-based)
**Parameters:**
- Depth: 0-100%
- Rate: 0.5-10 Hz
- Voice count: 2-4 voices
- Wet level: 0-100%

**Characteristics:**
- Lush and wide at high depth
- Subtle doubling at low settings
- Best with electric piano and strings

### Phaser (All-pass Cascades)
**Parameters:**
- Feedback: 0-100%
- Rate: 0.1-20 Hz
- Depth: 0-100%
- Stages: 2-12 all-pass filters

**Usage:**
- Electric piano: 20-40% feedback, 1-3 Hz rate
- Organ: 30-50% feedback, 2-5 Hz rate

### Delay (Feedback Buffer)
**Parameters:**
- Time: 20-2000ms (synced to tempo)
- Feedback: 0-95%
- Wet level: 0-100%
- Filter: Low-pass cutoff for self-damping

### Distortion (Soft Clipping)
**Parameters:**
- Drive: 0-50%
- Tone: Low/Mid/High
- Output: -20 to 0 dB (normalized)

---

## MIDI SPECIFICATIONS

The FM-1 supports standard MIDI 1.0 protocol over USB and 5-pin DIN interfaces.

### MIDI Implementation

| MIDI Message | Channel | Data | Function |
|-------------|---------|------|----------|
| **Note-On** (0x90) | 1-16 | Note 0-127, Velocity 1-127 | Trigger voice |
| **Note-Off** (0x80) | 1-16 | Note 0-127, Velocity 0-127 | Release voice |
| **Control Change** (0xB0) | 1-16 | CC 0-119, Value 0-127 | Parameter control |
| **Program Change** (0xC0) | 1-16 | Program 0-127 | Select preset |
| **Pitch Bend** (0xE0) | 1-16 | Bend range ±12 semitones | Pitch modulation |
| **Channel Pressure** (0xD0) | 1-16 | Pressure 0-127 | Aftertouch control |

### CC Mappings (Standard)

| CC Number | Parameter | Range |
|-----------|-----------|-------|
| CC#1 | Modulation Wheel | 0-127 |
| CC#2 | Breath Controller | 0-127 |
| CC#7 | Volume (Master) | 0-127 |
| CC#10 | Pan | 0-127 |
| CC#64 | Sustain Pedal | 0-127 (64=on) |
| CC#65 | Portamento | 0-127 |
| CC#66 | Sostenuto | 0-127 |
| CC#67 | Soft Pedal | 0-127 |
| CC#120 | All Sounds Off | - |
| CC#123 | All Notes Off | - |

### Instrument-Specific CC

**Organ (Drawbars):**
- CC#71-79: Drawbar levels (16' through 1')

**Synth (Envelope):**
- CC#73: Attack Time
- CC#75: Decay Time
- CC#79: Release Time

---

## TROUBLESHOOTING

### No Sound Output
**Check:**
- Master volume fader position
- Audio cable connections
- Output level on interface
- Test headphone jack to isolate speakers

### MIDI Not Detected
**Check:**
- USB connection (try different port)
- 5-pin cable integrity
- MIDI indicator LED on display
- Try keyboard on different computer

### Distorted Audio
**Solution:**
- Lower output level
- Reduce reverb/effects mix
- Check audio interface gain settings
- Reduce polyphony if CPU overloading

### Slow Response / Lag
**Solution:**
- Restart synth
- Reduce polyphony count
- Disable unnecessary effects
- Update firmware to latest version

### Screen Freezes
**Solution:**
- Power cycle unit (hold POWER 3 sec)
- Reload factory presets from SD card
- Check for firmware updates
- Contact support if persistent

---

## TECHNICAL SPECIFICATIONS

### Audio Specifications
- **Sample Rate**: 48 kHz (24-bit)
- **Channels**: Stereo
- **THD+N**: <0.01%
- **SNR**: >100 dB
- **Frequency Response**: 20 Hz - 20 kHz ±0.5 dB

### Synthesis Engine
- **Polyphony**: 32 voices max
- **Latency**: <5 ms (USB), <1 ms (5-pin MIDI)
- **Voice Allocation**: Dynamic priority with note-on/off queuing
- **CPU Load**: <60% @ full polyphony

### Connectivity
- **MIDI**: USB 2.0 High-Speed + 5-pin DIN (31.25 kbaud)
- **Audio**: RCA stereo (balanced recommended via XLR adapter)
- **Network**: Optional Ethernet module (future)
- **Storage**: SD/SDHC/SDXC UHS-II up to 256 GB

### Environmental
- **Power Consumption**: 30-60W
- **Noise Floor**: <-110 dB (A-weighted)
- **Cooling**: Passive (fanless design)
- **Vibration Isolation**: Rubber feet included

---

## WARRANTY & SUPPORT

### Warranty
The FM-1 includes a **3-year hardware warranty** covering manufacturing defects. Firmware updates are provided **free for life**.

### Support
- **Website**: mwave-synth.org
- **Email**: support@mwave-synth.org
- **Community**: forums.mwave-synth.org
- **GitHub**: github.com/mwave/fm1-firmware

### Open Source
The FM-1 firmware is **GPL v3 licensed**. Source code available at github.com/mwave/fm1-firmware

---

**Document Version 1.0** | Generated November 21, 2026
**MWAVE Synth Team** | Professional Audio Solutions
