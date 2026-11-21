# MWAVE Synthesizers - Complete CC Parameter Reference
## Full Control Documentation for FM-1 and SMK-37

**Version 1.0** | November 2026

---

## TABLE OF CONTENTS

1. [FM-1: Knob CC Mappings](#fm1-knob-cc-mappings)
2. [FM-1: Fader CC Mappings](#fm1-fader-cc-mappings)
3. [FM-1: Button CC Mappings](#fm1-button-cc-mappings)
4. [SMK-37: Touch Slider CC Mappings](#smk37-touch-slider-cc-mappings)
5. [SMK-37: Button CC Mappings](#smk37-button-cc-mappings)
6. [Instrument-Specific CC Parameters](#instrument-specific-cc-parameters)
7. [Global CC Parameters](#global-cc-parameters)
8. [CC Implementation Notes](#cc-implementation-notes)

---

## FM-1: KNOB CC MAPPINGS

### Hardware Layout
The FM-1 has **16 rotary knobs** arranged in 2 rows (8 knobs each). Each knob sends MIDI CC messages.

### Default Knob Layout (All Channels)

| Knob # | CC Number | Parameter Name | Range | Notes |
|--------|-----------|----------------|-------|-------|
| **1** | CC#20 | Reverb Amount | 0-127 | Global reverb wet level |
| **2** | CC#21 | Filter Cutoff | 0-127 | Instrument filter center frequency |
| **3** | CC#22 | Chorus Depth | 0-127 | Chorus effect amount |
| **4** | CC#23 | Phaser Rate | 0-127 | LFO speed (0.1-20 Hz) |
| **5** | CC#24 | Distortion Drive | 0-127 | Overdrive/saturation level |
| **6** | CC#25 | Delay Time | 0-127 | Feedback delay duration (20-2000ms) |
| **7** | CC#26 | Delay Feedback | 0-127 | Delay repeats (0-95%) |
| **8** | CC#27 | Delay Mix | 0-127 | Delay wet/dry mix |
| **9** | CC#28 | LFO Rate | 0-127 | LFO speed (0.1-20 Hz) |
| **10** | CC#29 | LFO Depth | 0-127 | LFO modulation amount |
| **11** | CC#30 | Tone Brightness | 0-127 | Dark (0) to Bright (127) |
| **12** | CC#31 | Vibrato Speed | 0-127 | Vibrato LFO rate |
| **13** | CC#32 | Attack Time | 0-127 | ADSR attack (1ms-5s) |
| **14** | CC#33 | Decay Time | 0-127 | ADSR decay (1ms-5s) |
| **15** | CC#34 | Release Time | 0-127 | ADSR release (1ms-10s) |
| **16** | CC#35 | Expression | 0-127 | Master dynamics/velocity scaling |

### Knob CC Mapping by Instrument

**PIANO:**
- Knob 1 (CC#20): Reverb Amount
- Knob 2 (CC#21): Tone Brightness
- Knob 3 (CC#22): Sustain Pedal Duration
- Knob 4 (CC#23): Touch Sensitivity
- Knobs 5-16: Effects and global controls

**ELECTRIC PIANO:**
- Knob 1 (CC#20): Reverb Amount
- Knob 2 (CC#21): Tone (Warm to Bright)
- Knob 3 (CC#22): Chorus Depth
- Knob 4 (CC#23): Phaser Rate
- Knob 5 (CC#24): Tremolo Speed
- Knob 6 (CC#25): Bell Tone Amount
- Knobs 7-16: Secondary effects

**ORGAN:**
- Knob 1 (CC#20): Leslie Speed (Slow = 0.8Hz, Fast = 2.5Hz)
- Knob 2 (CC#21): Overdrive Amount
- Knob 3 (CC#22): Reverb
- Knob 4 (CC#23): Drawbar Mix (all drawbars together)
- Knobs 5-16: Individual drawbar modulation

**MELOTRON:**
- Knob 1 (CC#20): Tape Saturation
- Knob 2 (CC#21): Reverb Amount
- Knob 3 (CC#22): Tape Speed (Pitch)
- Knob 4 (CC#23): Tape Rewind Rate
- Knobs 5-16: Layer controls and effects

**SYNTH:**
- Knob 1 (CC#20): Filter Cutoff
- Knob 2 (CC#21): LFO Rate
- Knob 3 (CC#22): LFO Depth
- Knob 4 (CC#23): Chorus Depth
- Knob 5 (CC#24): Reverb
- Knob 6 (CC#25): Arpeggiator Speed
- Knobs 7-16: Secondary LFO and effects

---

## FM-1: FADER CC MAPPINGS

### Hardware Layout
The FM-1 has **8 motorized faders** that provide visual feedback. Faders send CC messages and receive motor commands.

### Fader CC Mapping (Global)

| Fader # | CC Number | Parameter Name | Range | Motor Feedback | Notes |
|---------|-----------|----------------|-------|-----------------|-------|
| **1** | CC#36 | Master Volume | 0-127 | Yes | Output level -60dB to 0dB |
| **2** | CC#37 | Instrument Mix | 0-127 | Yes | Blend dry/processed signal |
| **3** | CC#38 | Effects Send | 0-127 | Yes | Wet/dry mix to effect chain |
| **4** | CC#39 | Reverb Room Size | 0-127 | Yes | Small (0) to Hall (127) |
| **5** | CC#40 | Sustain Pedal | 0-127 | Yes | CC#64 extended control |
| **6** | CC#41 | Modulation Wheel | 0-127 | Yes | Also receives CC#1 |
| **7** | CC#42 | Expression Pedal | 0-127 | Yes | Also receives CC#11 |
| **8** | CC#43 | Reserved | 0-127 | Yes | Instrument-specific |

### Fader CC Mapping by Instrument

**PIANO - Faders 2-8:**
- Fader 2: Tone Brightness
- Fader 3: Sustain Amount
- Fader 4: Touch Sensitivity
- Faders 5-8: Reverb Room/Delay/Chorus controls

**ELECTRIC PIANO - Faders 2-8:**
- Fader 2: Tone (Warm to Bright)
- Fader 3: Chorus Depth
- Fader 4: Phaser Rate
- Fader 5: Tremolo Speed
- Fader 6: Bell Tone Amount
- Fader 7: Reverb Mix
- Fader 8: Effects Balance

**ORGAN - Faders 1-9 (Override Defaults):**
- Fader 1: Master Volume (unchanged)
- Fader 2 (CC#37): Drawbar 16' | CC#71
- Fader 3 (CC#38): Drawbar 5⅓' | CC#72
- Fader 4 (CC#39): Drawbar 8' | CC#73
- Fader 5 (CC#40): Drawbar 4' | CC#74
- Fader 6 (CC#41): Drawbar 2⅔' | CC#75
- Fader 7 (CC#42): Drawbar 2' | CC#76
- Fader 8 (CC#43): Drawbar 1⅗' | CC#77
- Fader 9 (virtual): Drawbar 1⅓' | CC#78
- (Also mapped to knobs 5-13)

**MELOTRON - Faders 2-8:**
- Fader 2: Tape Saturation
- Fader 3: Tape Speed/Pitch
- Fader 4: Tape Position (manual scrub)
- Fader 5: Reverb Room Size
- Fader 6: Delay Time
- Fader 7: Reverb Mix
- Fader 8: Effects Balance

**SYNTH - Faders 2-8:**
- Fader 2 (CC#37): Attack Time | CC#73
- Fader 3 (CC#38): Decay Time | CC#74
- Fader 4 (CC#39): Sustain Level | CC#75
- Fader 5 (CC#40): Release Time | CC#76
- Fader 6 (CC#41): Filter Cutoff
- Fader 7 (CC#42): LFO Rate
- Fader 8 (CC#43): Chorus Depth

---

## FM-1: BUTTON CC MAPPINGS

### Hardware Layout
The FM-1 has **16 RGB buttons** arranged in a 4×4 grid. Buttons send CC note-on/note-off messages.

### Button CC Mapping (Note-Based)

| Button # | Note Number | Note Name | Function | LED Color | Notes |
|----------|-------------|-----------|----------|-----------|-------|
| **1** | 48 | C3 | Instrument Selector | Multi | Cycles through 5 instruments |
| **2** | 50 | D3 | Effects On/Off Toggle | Green/Red | Toggles effect chain |
| **3** | 52 | E3 | Tap Tempo | Blue | Sets BPM for delay/arp |
| **4** | 53 | F3 | Sustain Pedal (Piano) | Red/Green | CC#64 toggle |
| **5** | 55 | G3 | Leslie Toggle (Organ) | Red/Green | CC#67 toggle |
| **6** | 57 | A3 | Arpeggiator (Synth) | Blue/Green | Enables arpeggiator |
| **7** | 59 | B3 | Modulation Toggle | Yellow | Enables LFO routing |
| **8** | 60 | C4 | Reverb Bypass | Yellow/Green | Reverb on/off |
| **9** | 62 | D4 | Chorus Bypass | Cyan/Green | Chorus on/off |
| **10** | 64 | E4 | Phaser Bypass | Purple/Green | Phaser on/off |
| **11** | 65 | F4 | Delay Bypass | Orange/Green | Delay on/off |
| **12** | 67 | G4 | Distortion Bypass | Red/Green | Distortion on/off |
| **13** | 69 | A4 | Preset Save | White | Save current settings |
| **14** | 71 | B4 | Preset Load | White | Load from SD card |
| **15** | 72 | C5 | MIDI Learn | Cyan | Learn CC mappings |
| **16** | 74 | D5 | Master Reset | Red | Reset to defaults |

### Button LED Color Meanings

| Color | Meaning |
|-------|---------|
| **Green** | On/Enabled |
| **Red** | Active/Warning |
| **Blue** | Standby/Ready |
| **Yellow** | Modulation Active |
| **Cyan** | MIDI Learning |
| **Purple** | Secondary Function |
| **Off** | Disabled/Inactive |

---

## SMK-37: TOUCH SLIDER CC MAPPINGS

### Hardware Layout
The SMK-37 has **8 capacitive touch sliders** (vertical). Each slider sends CC messages.

### Touch Slider CC Mapping (Global)

| Slider # | CC Number | Parameter Name | Range | Notes |
|----------|-----------|----------------|-------|-------|
| **1** | CC#20 | Primary Control | 0-127 | Instrument-specific primary parameter |
| **2** | CC#21 | Secondary Control | 0-127 | Instrument-specific secondary parameter |
| **3** | CC#22 | Tertiary Control | 0-127 | Instrument-specific tertiary parameter |
| **4** | CC#23 | Quaternary Control | 0-127 | Effects or modulation |
| **5** | CC#24 | Reverb Amount | 0-127 | Global reverb wet level |
| **6** | CC#25 | Chorus Depth | 0-127 | Chorus effect amount |
| **7** | CC#26 | Filter Cutoff | 0-127 | Master filter center frequency |
| **8** | CC#27 | Master Volume | 0-127 | Output level -60dB to 0dB |

### Touch Slider by Instrument

**PIANO - Sliders 1-4:**
- Slider 1 (CC#20): Tone Brightness
- Slider 2 (CC#21): Reverb Amount
- Slider 3 (CC#22): Sustain Pedal Duration
- Slider 4 (CC#23): Expression/Velocity Scale
- Sliders 5-8: Global reverb, chorus, filter, volume

**ELECTRIC PIANO - Sliders 1-4:**
- Slider 1 (CC#20): Tone (Warm to Bright)
- Slider 2 (CC#21): Chorus Depth
- Slider 3 (CC#22): Phaser Rate
- Slider 4 (CC#23): Tremolo Speed
- Sliders 5-8: Global effects and volume

**ORGAN - Sliders 1-8:**
- Slider 1 (CC#20): Drawbar 16' | CC#71
- Slider 2 (CC#21): Drawbar 5⅓' | CC#72
- Slider 3 (CC#22): Drawbar 8' | CC#73
- Slider 4 (CC#23): Drawbar 4' | CC#74
- Slider 5 (CC#24): Drawbar 2⅔' | CC#75
- Slider 6 (CC#25): Drawbar 2' | CC#76
- Slider 7 (CC#26): Drawbar 1⅗' | CC#77
- Slider 8 (CC#27): Drawbar 1⅓' | CC#78

**MELOTRON - Sliders 1-4:**
- Slider 1 (CC#20): Tape Saturation
- Slider 2 (CC#21): Reverb Amount
- Slider 3 (CC#22): Tape Position (scrub)
- Slider 4 (CC#23): Tape Speed
- Sliders 5-8: Global effects and volume

**SYNTH - Sliders 1-4:**
- Slider 1 (CC#20): Arpeggiator Speed
- Slider 2 (CC#21): Filter Cutoff
- Slider 3 (CC#22): LFO Rate
- Slider 4 (CC#23): LFO Depth
- Sliders 5-8: Global reverb, chorus, filter, volume

---

## SMK-37: BUTTON CC MAPPINGS

### Hardware Layout
The SMK-37 has **5 mode buttons** + **preset controls** + **function buttons**

### Mode Buttons (Exclusive Selection)

| Button | Function | MIDI Output | LED Indicator |
|--------|----------|-------------|---------------|
| **MODE 1** | Select Piano | Program Change 0-9 | Green |
| **MODE 2** | Select E.Piano | Program Change 10-19 | Green |
| **MODE 3** | Select Organ | Program Change 20-29 | Green |
| **MODE 4** | Select Melotron | Program Change 30-39 | Green |
| **MODE 5** | Select Synth | Program Change 40-49 | Green |

### Preset Navigation

| Button | Function | MIDI Output | Notes |
|--------|----------|-------------|-------|
| **PRESET ◀** | Previous Preset | CC#50, value=0 | 10 presets per instrument |
| **PRESET ▶** | Next Preset | CC#50, value=127 | Wraps around |

### Function Buttons

| Button | Function | MIDI Output | Notes |
|--------|----------|-------------|-------|
| **LESLIE** (Organ) | Toggle Leslie | CC#67, value=0/127 | Organ mode only |
| **TAPE** (Melotron) | Select voice | CC#51, value varies | Violins/Choir/Flute/Layer |
| **ARP** (Synth) | Toggle Arpeggiator | CC#52, value=0/127 | Synth mode only |
| **Power** | Power on/off | - | Long press = shutdown |

---

## INSTRUMENT-SPECIFIC CC PARAMETERS

### PIANO CC Parameters

| CC # | Parameter | Range | Min-Max | Notes |
|------|-----------|-------|---------|-------|
| CC#20 | Reverb Amount | 0-127 | 0% - 100% | Wet level |
| CC#21 | Tone Brightness | 0-127 | Dark - Bright | Filter tone color |
| CC#22 | Sustain Duration | 0-127 | 0s - 10s | Sustain pedal hold |
| CC#23 | Velocity Scaling | 0-127 | 0% - 100% | Touch sensitivity |
| CC#64 | Sustain Pedal | 0/127 | Off/On | Standard sustain |
| CC#71 | Hammer Release | 0-127 | Slow - Fast | Note release speed |
| CC#72 | Lid Position | 0-127 | Closed - Open | Resonance/projection |

### ELECTRIC PIANO CC Parameters

| CC # | Parameter | Range | Min-Max | Notes |
|------|-----------|-------|---------|-------|
| CC#20 | Tone | 0-127 | Warm - Bright | Tine filter position |
| CC#21 | Chorus Depth | 0-127 | 0% - 100% | Chorus wet amount |
| CC#22 | Phaser Rate | 0-127 | 0.1Hz - 20Hz | LFO speed |
| CC#23 | Tremolo Speed | 0-127 | 0.1Hz - 20Hz | Tremolo rate |
| CC#24 | Bell Tone | 0-127 | 0% - 100% | Bell harmonics blend |
| CC#64 | Sustain | 0/127 | Off/On | Sustain control |
| CC#71 | Phaser Feedback | 0-127 | Light - Extreme | Phaser intensity |

### ORGAN CC Parameters

| CC # | Parameter | Range | Min-Max | Notes |
|------|-----------|-------|---------|-------|
| CC#71 | Drawbar 16' | 0-127 | 0 - 8 | Hammond drawbar level |
| CC#72 | Drawbar 5⅓' | 0-127 | 0 - 8 | Hammond drawbar level |
| CC#73 | Drawbar 8' | 0-127 | 0 - 8 | Hammond drawbar level |
| CC#74 | Drawbar 4' | 0-127 | 0 - 8 | Hammond drawbar level |
| CC#75 | Drawbar 2⅔' | 0-127 | 0 - 8 | Hammond drawbar level |
| CC#76 | Drawbar 2' | 0-127 | 0 - 8 | Hammond drawbar level |
| CC#77 | Drawbar 1⅗' | 0-127 | 0 - 8 | Hammond drawbar level |
| CC#78 | Drawbar 1⅓' | 0-127 | 0 - 8 | Hammond drawbar level |
| CC#79 | Drawbar 1' | 0-127 | 0 - 8 | Hammond drawbar level |
| CC#67 | Leslie On/Off | 0/127 | Off/On | Rotary speaker toggle |
| CC#20 | Leslie Speed | 0-127 | Slow (0.8Hz) - Fast (2.5Hz) | Variable Leslie speed |
| CC#21 | Overdrive | 0-127 | 0% - 100% | Tube drive amount |

### MELOTRON CC Parameters

| CC # | Parameter | Range | Min-Max | Notes |
|------|-----------|-------|---------|-------|
| CC#20 | Tape Saturation | 0-127 | Clean - Saturated | Tape color/warmth |
| CC#21 | Reverb Amount | 0-127 | 0% - 100% | Reverb wet level |
| CC#22 | Tape Speed | 0-127 | -50% - +50% | Pitch shift (cents) |
| CC#23 | Tape Rewind | 0-127 | Slow - Fast | Rewind rate on release |
| CC#51 | Voice Selection | 0/42/84/127 | Violins/Choir/Flute/Layer | Tape voice select |
| CC#64 | Note Hold | 0/127 | Off/On | Sustain tape playback |

### SYNTH CC Parameters

| CC # | Parameter | Range | Min-Max | Notes |
|------|-----------|-------|---------|-------|
| CC#20 | Filter Cutoff | 0-127 | 50Hz - 20kHz | Low-pass filter freq |
| CC#21 | LFO Rate | 0-127 | 0.1Hz - 20Hz | LFO speed |
| CC#22 | LFO Depth | 0-127 | 0% - 100% | LFO modulation amount |
| CC#23 | Chorus Depth | 0-127 | 0% - 100% | Chorus wet amount |
| CC#24 | Reverb Amount | 0-127 | 0% - 100% | Reverb wet level |
| CC#73 | Attack Time | 0-127 | 1ms - 5s | ADSR attack |
| CC#74 | Decay Time | 0-127 | 1ms - 5s | ADSR decay |
| CC#75 | Sustain Level | 0-127 | 0% - 100% | ADSR sustain |
| CC#76 | Release Time | 0-127 | 1ms - 10s | ADSR release |
| CC#52 | Arpeggiator | 0/42/84/127 | Off/Up/Down/UpDn | Arpeggiator mode |

---

## GLOBAL CC PARAMETERS

### Standard MIDI CC (All Instruments)

| CC # | Parameter | Range | Function |
|------|-----------|-------|----------|
| **CC#1** | Modulation Wheel | 0-127 | Vibrato/tremolo depth |
| **CC#2** | Breath Controller | 0-127 | Volume envelope modifier |
| **CC#7** | Volume (Master) | 0-127 | Master output level |
| **CC#10** | Pan | 0-127 | Left (0) - Center (64) - Right (127) |
| **CC#11** | Expression Pedal | 0-127 | Dynamic volume control |
| **CC#64** | Sustain Pedal | 0-127 | Note sustain toggle (≥64 = on) |
| **CC#65** | Portamento | 0-127 | Glide time (0-5s) |
| **CC#66** | Sostenuto Pedal | 0-127 | Selective sustain |
| **CC#67** | Soft Pedal | 0-127 | Reduce volume and attack |
| **CC#120** | All Sounds Off | - | Stop all notes |
| **CC#123** | All Notes Off | - | Release all sustaining notes |

### Extended Parameters (MWAVE-Specific)

| CC # | Parameter | Range | Function |
|------|-----------|-------|----------|
| **CC#36-43** | Faders 1-8 (FM-1) | 0-127 | Motorized fader feedback |
| **CC#20-35** | Knobs 1-16 (FM-1) | 0-127 | Rotary encoder feedback |
| **CC#50** | Preset Navigation | 0/127 | Previous (0) / Next (127) |
| **CC#51** | Mode Selection | 0-49 | Instrument select (8 per mode) |
| **CC#52** | Arpeggiator Mode | 0/42/84/127 | Off/Up/Down/UpDn |
| **CC#53** | Reverb Preset | 0-31 | Small/Medium/Large/Hall + variants |
| **CC#54** | Reverb Room Mix | 0-127 | Reverb algorithm blend |
| **CC#55** | Master Tuning | 50-78 | A4 = 65 (440Hz), ±50 cents |

---

## CC IMPLEMENTATION NOTES

### Response Ranges
- **Value 0-1**: Off/Minimum
- **Value 1-63**: Low/Dark/Slow
- **Value 64**: Center/Neutral (for pan)
- **Value 65-126**: High/Bright/Fast
- **Value 127**: Maximum/On

### Ramping Behavior
- Faders: Linear ramping over 20ms
- Knobs: Logarithmic scaling for natural feel
- Sustain pedal: Immediate on/off at CC value 64 threshold

### Motorized Fader Feedback (FM-1 Only)
When external MIDI sends CC values to faders 1-8, motors move physical faders to match:
- Faders respond to CC#36-43
- Motor speed: ~1 octave per second
- Position sync occurs within 500ms

### MIDI Channel Filtering
- All instruments respond on **MIDI Channel 1 by default**
- Omnibus mode available via settings (responds to all channels)
- Channel can be remapped via MIDI Learn function

### CC Resolution
- 7-bit resolution (0-127): Standard MIDI
- 14-bit resolution available via CC# + CC#+32 pairing (NRPN mode)
- Faders: Smooth tracking at 20ms intervals

### CC Ramping Time
| Control | Ramp Time | Curve |
|---------|-----------|-------|
| Faders | 20ms | Linear |
| Knobs | 10ms | Logarithmic |
| Sliders (SMK) | 15ms | Linear |
| Sustain Pedal | 0ms | On/Off |

---

## APPENDIX: QUICK CC REFERENCE

### Most Important CCs (Quick Reference)

```
CC#1   = Modulation (vibrato/tremolo)
CC#7   = Master Volume
CC#11  = Expression Pedal
CC#20  = Primary Instrument Parameter
CC#64  = Sustain Pedal
CC#71-79 = Organ Drawbars (or general parameters)
CC#120 = All Sounds Off
CC#123 = All Notes Off
```

### Pro Tips

1. **Layer Effects**: Use CC#20-27 to modulate multiple effects simultaneously
2. **Drawbar Automation**: Record organ drawbar CC#71-79 changes for dynamic performances
3. **Performance Control**: Map expression pedal (CC#11) to both volume and filter cutoff
4. **Synth Pads**: Use LFO via CC#21-22 with delay (CC#26-27) for evolving textures
5. **MIDI Learn**: Press "MIDI Learn" button, move hardware control, then send CC - auto-maps!

---

**Document Version 1.0** | Generated November 21, 2026
**MWAVE Synth Team** | Professional Control Reference

---

## Document Revision History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | Nov 2026 | Initial release with complete CC reference |

---

## Support

For questions about CC implementation:
- **Email**: support@mwave-synth.org
- **Forum**: forums.mwave-synth.org/cc-reference
- **GitHub Issues**: github.com/mwave/firmware-docs/issues
