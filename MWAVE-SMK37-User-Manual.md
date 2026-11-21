# MWAVE SMK-37 Compact Digital Synthesizer
## User Manual & Quick Reference

**Version 1.0** | November 2026

---

## QUICK START GUIDE

The SMK-37 is a lightweight, portable synthesizer perfect for gigging musicians and mobile studios. Get started in 3 steps:

### 1. Power Up
Connect USB power or battery pack. Press POWER button. Display initializes in 2 seconds.

### 2. Select Instrument
Press MODE buttons to cycle: **Piano → E.Piano → Organ → Melotron → Synth**
LED indicator shows selection.

### 3. Connect Keyboard & Play
Plug USB MIDI keyboard into USB-C port. Use 8 touch sliders on front panel to control reverb, effects, and tone.

---

## SPECIFICATIONS

| Parameter | SMK-37 Specification |
|-----------|----------------------|
| **Processor** | ARM Cortex-M4 @ 240 MHz (optimized) |
| **Memory** | 128 KB RAM + 2 MB Flash |
| **Audio** | Stereo 3.5mm jack, 24-bit @ 48 kHz |
| **MIDI Input** | USB Type-C (5-pin DIN via adapter) |
| **Controls** | 8 capacitive touch sliders, 5 mode buttons |
| **Display** | 3-inch OLED (128×64), monochrome |
| **Power** | USB-C (5V/2A) or AA batteries (×4) |
| **Battery Life** | 8-10 hours (alkaline) |
| **Dimensions** | 420mm (W) × 70mm (H) × 180mm (D) |
| **Weight** | 1.2 kg |
| **Operating Temp** | 5°C to 35°C |

---

## KEY FEATURES

- ✓ **Ultra-portable design** (1.2 kg, fits in backpack)
- ✓ **16-voice polyphony** (CPU-optimized)
- ✓ **5 instrument families** with preset variations
- ✓ **8 velocity-sensitive touch sliders**
- ✓ **Built-in reverb, chorus, and phaser** effects
- ✓ **3-inch OLED display** with real-time feedback
- ✓ **USB-C for power and MIDI**
- ✓ **2-4 hour battery operation** (AA batteries)
- ✓ **SD card support** (microSD via adapter)
- ✓ **Open-source GPL v3 firmware**
- ✓ **WiFi-ready** (optional module)

---

## INSTRUMENTS

Press **MODE 1-5** to select instruments. Each has 10 presets accessible via PRESET buttons.

### 1. PIANO
Grand, Home, Old piano models. 

**Touch Sliders:**
- Slider 1 = Tone (Dark → Bright)
- Slider 2 = Reverb
- Slider 3 = Sustain
- Slider 4 = Expression (pedal simulation)

**Presets:** Grand Piano Bright, Home Piano Warm, Old Piano Vintage, Concert Grand (stereo)

### 2. ELECTRIC PIANO
Rhodes/Wurlitzer blend.

**Touch Sliders:**
- Slider 1 = Tone
- Slider 2 = Chorus Depth
- Slider 3 = Phaser Rate
- Slider 4 = Tremolo Speed

**Presets:** Rhodes Classic, Wurlitzer Funky, Fender Rhodes Bright, Tine Organ Blend

### 3. ORGAN
Hammond 9-drawbar.

**Touch Sliders:**
- Sliders 1-4 = Drawbar banks (16', 8', 4', 2')
- Sliders 5-8 = Drawbar banks (2⅔', 2', 1⅗', 1')
- Button LESLIE = Toggle Leslie
- Button OVERDRIVE = Enable tube drive

**Presets:** Full Gospel, Soul Drawbars, Classic B3, Prog Rock Deep

### 4. MELOTRON
Tape playback.

**Touch Sliders:**
- Slider 1 = Tape Saturation
- Slider 2 = Reverb
- Slider 3 = Tape Position (manual control)
- Slider 4 = Tape Speed

**Controls:**
- Button TAPE = Select voice (Violins/Choir/Flute)
- Button LAYER = Combine multiple voices

**Presets:** Violins Classic, Choir + Flute Blend, Mellotron Lush, Tape Warmth

### 5. SYNTH
Wavetable arpeggiator.

**Touch Sliders:**
- Slider 1 = Arpeggiator Speed
- Slider 2 = Filter Cutoff
- Slider 3 = Reverb
- Slider 4 = LFO Rate

**Buttons:**
- Button ARP = Toggle/select arpeggiator mode (Up/Down/UpDown)
- Button LFO = Enable LFO modulation

**Presets:** Lush Pad, Bright String, Arpeggio Up/Down, Ambient Synth

---

## FRONT PANEL CONTROLS

| Control | Function | Range |
|---------|----------|-------|
| **Slider 1-8** | Instrument-specific | 0-100% |
| **Mode 1** | Select Piano | - |
| **Mode 2** | Select E.Piano | - |
| **Mode 3** | Select Organ | - |
| **Mode 4** | Select Melotron | - |
| **Mode 5** | Select Synth | - |
| **Preset ◀** | Previous preset | 10 presets per instrument |
| **Preset ▶** | Next preset | 10 presets per instrument |
| **Leslie** | Toggle Leslie (Organ) | On/Off |
| **Tape** | Select Melotron voice | Violins/Choir/Flute/Layer |
| **Power** | Power on/off | Toggle |

---

## BUILT-IN EFFECTS

All instruments have access to the following effects (assigned to touch sliders per instrument):

### Reverb
**Room sizes:** Small, Medium, Large, Hall
**Wet level:** 0-100%

### Chorus
**Depth:** 0-100%
**Rate:** 0.5-10 Hz
**Max:** 4-voice chorus

### Phaser
**Feedback and rate controls**
**Range:** Subtle to extreme phasing

### Distortion
**Soft-clipping drive**
**Range:** 0-50% drive levels

---

## TIPS & TRICKS

### Battery Life
Use rechargeable AA batteries for eco-friendly operation. Alkaline batteries provide ~10 hours. Disable display backlight for extra 2-3 hours.

### Preset Management
Save custom presets to microSD card. Up to 100 presets per instrument. Presets sync across USB updates.

### Portable Setup
Use USB battery pack for extended gigs. Recommended: 10000mAh @ 2A. Connect via USB-C cable (included).

### MIDI Sync
SMK-37 can sync to external MIDI clocks. Use Arpeggiator tempo sync for rhythmic accuracy with drum machines.

---

## TROUBLESHOOTING

| Problem | Solution |
|---------|----------|
| **Display won't turn on** | Check USB power or batteries. Hold POWER 3 seconds. |
| **MIDI not detected** | Verify USB connection. Try different USB cable. |
| **Battery drains fast** | Disable reverb/effects, reduce brightness. Use USB power for long sets. |
| **Audio distorts** | Lower Slider 1 (master), reduce effects mix. |
| **Stuck preset** | Power cycle unit. Remove/reinsert SD card. |

---

## SUPPORT & RESOURCES

### Warranty
**2-year hardware warranty.** Firmware updates free for life.

### Community
Join 10,000+ MWAVE users at **mwave-synth.org**
Share presets, tutorials, and tips.

### Open Source
**GPL v3 firmware**
Contribute at **github.com/mwave/smk37-firmware**

---

## APPENDIX: QUICK PRESET GUIDE

### Piano Presets
1. Grand Piano Bright
2. Home Piano Warm
3. Old Piano Vintage
4. Concert Grand (stereo)
5. Upright Piano Dark
6. Electric Grand
7. Ragtime Piano
8. Jazz Piano
9. Piano with Chorus
10. Piano with Reverb

### E.Piano Presets
1. Rhodes Classic
2. Wurlitzer Funky
3. Fender Rhodes Bright
4. Tine Organ Blend
5. Rhodes Chorus
6. Wurli Vibraphone
7. Electric Honky-Tonk
8. Rhodes Overdrive
9. Electric Piano Phaser
10. Electric Piano Sustain

### Organ Presets
1. Full Gospel
2. Soul Drawbars
3. Classic B3
4. Prog Rock Deep
5. Jazz Combo
6. Gospel with Leslie
7. Rock Hammond
8. Funk Organ
9. Drawbar Flute
10. Organ + Overdrive

### Melotron Presets
1. Violins Classic
2. Choir + Flute Blend
3. Mellotron Lush
4. Tape Warmth
5. Violins Bright
6. Choir Smooth
7. Flute Piccolo
8. String Pad Warm
9. Tape Saturation
10. All Voices Mix

### Synth Presets
1. Lush Pad
2. Bright String
3. Arpeggio Up/Down
4. Ambient Synth
5. Electric Piano Pad
6. Warm Synth Pad
7. Arpeggio Fast
8. Arpeggio Slow
9. Synth Strings
10. Lead Synth

---

**Document Version 1.0** | Generated November 21, 2026
**MWAVE Synth Team** | Portable Synthesis Solutions

---

## Convert to PDF

To convert this manual to PDF, use one of these methods:

**Using markdown-to-pdf:**
```bash
npm install -g md-pdf
md-pdf MWAVE-SMK37-User-Manual.md
```

**Using pandoc:**
```bash
pandoc MWAVE-SMK37-User-Manual.md -o MWAVE-SMK37-User-Manual.pdf
```

**Using your browser:**
- Open the .md file in browser
- Print to PDF (Ctrl+P / Cmd+P)
