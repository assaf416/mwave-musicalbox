# MWAVE Synthesizer Documentation Library
## Complete Reference & User Manuals

**Generated:** November 21, 2026  
**Version:** 1.0  
**Total Pages:** 1,100+ lines of comprehensive documentation

---

## 📚 DOCUMENTATION FILES

### 1. **MWAVE-FM1-User-Manual.md** (11 KB, 382 lines)
Complete user manual for the professional MWAVE FM-1 synthesizer.

**Contents:**
- Product overview and key features
- Hardware specifications (480 MHz ARM CPU, 32-voice polyphony)
- Getting started guide
- 5 instrument descriptions (Piano, E.Piano, Organ, Melotron, Synth)
- Control reference (16 knobs, 8 faders, 16 buttons)
- Effects processing documentation
- MIDI specifications and CC mappings
- Troubleshooting guide
- Technical specifications
- Warranty and support information

**Best For:** Complete reference for FM-1 users and developers

---

### 2. **MWAVE-SMK37-User-Manual.md** (7.2 KB, 297 lines)
Compact user manual for the portable MWAVE SMK-37 synthesizer.

**Contents:**
- Quick start guide (3-step setup)
- Hardware specifications (portable, battery-powered)
- Key features (1.2 kg, 16-voice polyphony)
- 5 instrument guides with slider mappings
- Front panel control reference
- Built-in effects (reverb, chorus, phaser, distortion)
- Tips & tricks for portable use
- Troubleshooting for field use
- Preset listing (50 presets total, 10 per instrument)
- Support and resource links

**Best For:** On-the-go musicians, quick reference

---

### 3. **MWAVE-CC-Parameter-Reference.md** (18 KB, 477 lines)
Complete MIDI CC parameter documentation for all controls.

**Contents:**
- **FM-1 Hardware Mapping:**
  - 16 knobs (CC#20-35) with instrument-specific overrides
  - 8 motorized faders (CC#36-43) with motor feedback
  - 16 RGB buttons (note-based control)

- **SMK-37 Hardware Mapping:**
  - 8 touch sliders (CC#20-27) with instrument overrides
  - 5 mode buttons (program change)
  - Preset navigation controls

- **Instrument-Specific CC Parameters:**
  - Piano: Reverb, tone, sustain, velocity scaling (CC#20-23, 64, 71-72)
  - E.Piano: Tone, chorus, phaser, tremolo (CC#20-24, 64, 71)
  - Organ: 9 Hammond drawbars (CC#71-79) + Leslie + overdrive
  - Melotron: Tape saturation, voice select, speed (CC#20-23, 51, 64)
  - Synth: Filter, LFO, ADSR envelope (CC#20-24, 52, 73-76)

- **Global MIDI Standards:**
  - CC#1: Modulation Wheel
  - CC#7: Master Volume
  - CC#11: Expression Pedal
  - CC#64-67: Sustain/Soft/Sostenuto
  - CC#120/123: All Sounds Off / All Notes Off

- **Extended Parameters:** 50+ custom MWAVE CC# assignments

**Best For:** MIDI programmers, controller mappers, automation specialists

---

### 4. **MWAVE-Screenshot-Guide.md** (10 KB, 420 lines)
Complete visual reference for all UI mockups and emulator output.

**Contents:**
- **Emulator Screenshots:**
  - Startup screen with initialization status
  - Main menu with instrument selector
  - Hello World melody playback with synthesis logs
  - Instrument switch display

- **FM-1 UI Mockups:**
  - Piano UI (tone, reverb, sustain controls)
  - Electric Piano UI (tine tuning visualization)
  - Organ UI (9 drawbars, Leslie rotary speaker)
  - Melotron UI (tape transport, voice stacking)
  - Synth Pad UI (waveform, ADSR, arpeggiator)

- **SMK-37 UI Mockups:**
  - Compact Piano display (3" OLED)
  - Compact Organ display (drawbar visualization)
  - Compact Synth display (arp/LFO info)

- **Design System:**
  - Color palettes (gold for piano, orange for E.piano, blue for synth)
  - Typography (Helvetica/Monospace hierarchy)
  - Layout principles and responsive design
  - UI element reference guide
  - Accessibility features

**Best For:** UI/UX designers, visual documentation, mockup reference

---

## 📊 DOCUMENTATION STATISTICS

| Document | Size | Lines | Topics |
|----------|------|-------|--------|
| FM-1 Manual | 11 KB | 382 | 10 sections |
| SMK-37 Manual | 7.2 KB | 297 | 10 sections |
| CC Reference | 18 KB | 477 | 180+ CC mappings |
| Screenshot Guide | 10 KB | 420 | 20+ screenshots |
| **TOTAL** | **46.2 KB** | **1,156** | **50+ topics** |

---

## 🎹 QUICK REFERENCE

### FM-1 Hardware
```
- Processor: ARM Cortex-M4 @ 480 MHz
- Polyphony: 32 voices
- Audio: 24-bit @ 48 kHz stereo
- Controls: 16 knobs + 8 motorized faders + 16 RGB buttons
- Display: 7" touchscreen (1024×600)
- MIDI: USB + 5-pin DIN
```

### SMK-37 Hardware
```
- Processor: ARM Cortex-M4 @ 240 MHz
- Polyphony: 16 voices
- Audio: 24-bit @ 48 kHz stereo (3.5mm)
- Controls: 8 touch sliders + 5 mode buttons
- Display: 3" OLED monochrome (128×64)
- MIDI: USB Type-C
- Power: USB or AA batteries (8-10 hours)
```

### Key CC Numbers
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

### Instruments
```
1. Piano (Grand/Home/Old)
2. Electric Piano (Rhodes/Wurlitzer)
3. Organ (Hammond with Bethree engine)
4. Melotron (Tape synthesis)
5. Synth Pad (Wavetable with arpeggiator)
```

---

## 🎯 USE CASES

### For Users
- **FM-1 Manual:** Complete reference for all features and parameters
- **SMK-37 Manual:** Portable user guide for field use
- **Screenshot Guide:** Visual walkthrough of all UI screens

### For Developers
- **CC Reference:** Complete MIDI implementation guide
- **FM-1 Manual:** Hardware specifications and control mappings
- **Screenshot Guide:** UI design system and element reference

### For MIDI Programmers
- **CC Reference:** Parameter mapping for controllers and DAWs
- **Instrument Guides:** Instrument-specific CC assignments
- **Global Parameters:** Standard MIDI CC documentation

### For Sound Designers
- **Instrument Guides:** Sound creation and preset design
- **Effects Documentation:** Reverb, chorus, phaser, delay settings
- **Tips & Tricks:** Optimization for specific musical styles

---

## 📖 CONVERT TO PDF

### Method 1: Using Pandoc (Recommended)
```bash
# Install pandoc
sudo apt-get install pandoc

# Convert single file
pandoc MWAVE-FM1-User-Manual.md -o MWAVE-FM1-User-Manual.pdf

# Convert all files
for file in MWAVE-*.md; do
  pandoc "$file" -o "${file%.md}.pdf"
done
```

### Method 2: Using Markdown to PDF Online Tools
1. Upload .md file to https://pandoc.org/try/
2. Select PDF as output format
3. Download PDF

### Method 3: Browser Print to PDF
1. Open .md file in browser or Markdown viewer
2. Press Ctrl+P (or Cmd+P on Mac)
3. Select "Print to PDF"
4. Save file

### Method 4: VS Code Extension
1. Install "Markdown PDF" extension
2. Right-click on .md file
3. Select "Markdown PDF: Export (PDF)"

---

## 🔗 RELATED DOCUMENTATION

### Project Repository
- **GitHub:** github.com/mwave/musical-box
- **Firmware:** `/firmware/` directory
- **Emulator:** `/emulator/` directory
- **Build System:** CMake configuration

### Additional Resources
- **Architecture Document:** `docs/architecture.md`
- **Hello World Tutorial:** `docs/hello_world.md`
- **Development Setup:** `DEVELOPMENT.md`
- **Quick Start:** `QUICKSTART.md`
- **Build Summary:** `BUILD_SUMMARY.md`

---

## 🏆 FEATURES DOCUMENTED

### FM-1 Features
✓ 32-voice polyphony
✓ 5 instrument families
✓ 24-bit/48kHz audio
✓ Multi-effects processing
✓ 16 velocity-sensitive knobs
✓ 8 motorized faders
✓ 7" touchscreen
✓ MIDI input (USB + 5-pin)
✓ SD card presets
✓ Open-source GPL v3

### SMK-37 Features
✓ 16-voice polyphony
✓ 5 instruments
✓ 24-bit/48kHz audio
✓ Built-in effects
✓ 8 touch sliders
✓ 3" OLED display
✓ USB-C MIDI
✓ Battery powered (8-10 hrs)
✓ Ultra-portable (1.2 kg)
✓ Open-source GPL v3

---

## 📋 DOCUMENTATION CHECKLIST

✓ FM-1 User Manual (complete)
✓ SMK-37 User Manual (complete)
✓ Complete CC Parameter Reference (180+ mappings)
✓ Screenshot & UI Documentation (20+ mockups)
✓ Hardware Specifications (both synths)
✓ Instrument Guides (5 instruments × 2 synths)
✓ Effects Documentation (reverb, chorus, phaser, delay)
✓ MIDI Specifications (CC#, note ranges, channels)
✓ Troubleshooting Guides (both synths)
✓ Design System Reference (colors, typography, layout)
✓ Quick Start Guides (FM-1 and SMK-37)
✓ Control Reference (knobs, faders, buttons, sliders)
✓ Preset Listing (50+ factory presets)
✓ Support & Resources (contact info, links)

---

## 📞 SUPPORT & CONTACT

### Official Resources
- **Website:** mwave-synth.org
- **Email:** support@mwave-synth.org
- **Forum:** forums.mwave-synth.org
- **GitHub:** github.com/mwave/

### Documentation Feedback
- **Report Issues:** github.com/mwave/documentation-feedback
- **Request Features:** forums.mwave-synth.org/feature-requests
- **Submit Corrections:** support@mwave-synth.org

---

## 📝 VERSION INFORMATION

| Component | Version | Date |
|-----------|---------|------|
| FM-1 Firmware | 1.0 | Nov 2026 |
| SMK-37 Firmware | 1.0 | Nov 2026 |
| Documentation | 1.0 | Nov 2026 |
| CC Reference | 1.0 | Nov 2026 |
| UI Design | 1.0 | Nov 2026 |

---

## 📄 LICENSE

All documentation is provided under **Creative Commons Attribution 4.0 (CC-BY-4.0)**.

You are free to:
- **Share:** Copy and redistribute the material
- **Adapt:** Remix, transform, and build upon the material
- **Use Commercially:** Use for any purpose, including commercial applications

**Requirements:**
- **Attribution:** Give appropriate credit

---

**Documentation Library Version 1.0**  
**Generated:** November 21, 2026  
**Total Size:** 46.2 KB (uncompressed)  
**Total Lines:** 1,156 lines of detailed documentation  

**Ready to use!** Convert to PDF or view as Markdown. All files included. ✅

---

*MWAVE Synth Team | Professional Audio Documentation*
