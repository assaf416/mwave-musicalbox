# MWAVE Musical Box - Screenshot & UI Documentation
## Complete Visual Reference Guide

**Version 1.0** | November 2026

---

## TABLE OF CONTENTS

1. [Emulator Screenshots](#emulator-screenshots)
2. [UI Mockups - FM-1](#ui-mockups---fm1)
3. [UI Mockups - SMK-37](#ui-mockups---smk37)
4. [UI Element Reference](#ui-element-reference)
5. [Color Scheme & Design System](#color-scheme--design-system)

---

## EMULATOR SCREENSHOTS

### Screenshot 1: Startup Screen
**Location:** `./build/emulator/mwave_emulator`
**Description:** Initial emulator window showing welcome banner and initialization status

```
╔════════════════════════════════════════════════════════════╗
║   MWAVE Musical Box - Desktop Emulator                     ║
║   Firmware for MWAVE FM-1 & SMK-37 Synthesizers           ║
╚════════════════════════════════════════════════════════════╝

Initializing MWAVE emulator...
✓ Audio engine ready
✓ MIDI parser ready
✓ Synth ready with 32 voices
```

**Elements Visible:**
- ASCII art banner with product name
- Initialization status messages (3 checkmarks)
- Ready state indicators

**Information Conveyed:**
- Application name and version
- Component initialization status
- System readiness indicator

### Screenshot 2: Main Menu Screen
**Description:** Instrument selector and status display

```
┌─ Instruments ─────────────────────────────────────────────┐
│ → [0] Piano                                            │
│   [1] Electric Piano                                   │
│   [2] Organ                                            │
│   [3] Melotron                                         │
│   [4] Synth Pad                                        │
└───────────────────────────────────────────────────────────┘

┌─ Status ──────────────────────────────────────────────────┐
│ Current Instrument: Piano                                  │
│ Active Voices:      0    /32                                 │
│ Reverb Amount:      50 %                                         │
│ MIDI Status:        READY                            │
└───────────────────────────────────────────────────────────┘

┌─ Commands ────────────────────────────────────────────────┐
│ [P] Play Hello World Melody                              │
│ [S] Stop All Notes                                       │
│ [I] Select Instrument (0-4)                              │
│ [R] Adjust Reverb (0-100)                                │
│ [Q] Quit Emulator                                        │
└───────────────────────────────────────────────────────────┘
```

**Elements Visible:**
- Instrument selector box with current selection indicator (→)
- Status display box with real-time information
- Command menu with keyboard shortcuts

**Information Conveyed:**
- 5 selectable instruments
- Current voice count vs maximum (0/32)
- Reverb parameter value
- MIDI connection status
- 5 available commands

### Screenshot 3: Hello World Playback
**Description:** Melody playing with synthesis logs

```
▶ Playing Hello World melody on Piano...
  ♪ Note 60 (velocity 100)
[SynthEmulator] Playing MIDI note: 60 velocity: 100
[Synth] Generating tone at 261.626 Hz with velocity 100
[AudioOutput] Playing tone: 261.626 Hz at amplitude 0.393701
[AudioOutput] Generated 4410 samples for audio playback
  ♪ Note 60 (velocity 100)
[SynthEmulator] Playing MIDI note: 60 velocity: 100
...
✓ Melody complete!
```

**Elements Visible:**
- Melody playback indicator (▶)
- Note display with velocity
- Synthesis debug logs (3 per note)
- Completion indicator (✓)

**Information Conveyed:**
- Note numbers and velocities
- Frequency calculation (Hz)
- Amplitude normalization
- Sample buffer size (4410 samples = 100ms)
- Completion status

### Screenshot 4: Instrument Switch Display
**Description:** Screen after switching to Organ

```
┌─ Instruments ─────────────────────────────────────────────┐
│   [0] Piano                                            │
│   [1] Electric Piano                                   │
│ → [2] Organ                                            │
│   [3] Melotron                                         │
│   [4] Synth Pad                                        │
└───────────────────────────────────────────────────────────┘

┌─ Status ──────────────────────────────────────────────────┐
│ Current Instrument: Organ                                  │
│ Active Voices:      0    /32                                 │
│ Reverb Amount:      50 %                                         │
│ MIDI Status:        READY                            │
└───────────────────────────────────────────────────────────┘
```

**Elements Visible:**
- Updated instrument selection (→ moved to position 2)
- Status display updated to show "Organ"
- Voice count reset

**Information Conveyed:**
- Successful instrument switch
- Current instrument name
- Status persists across modes

---

## UI MOCKUPS - FM-1

### Piano UI Mockup
**File:** Located in project documentation  
**Display:** 7-inch touchscreen (1024×600)  
**Theme:** Dark slate (#1a1f2e) with gold accents (#d4af37)

**Elements:**
- **Top Section:**
  - Instrument buttons (Piano/E.Piano/Organ/Melotron/Synth)
  - Current selection highlighted in gold

- **Main Section:**
  - Tone control slider (Warm to Bright)
  - Reverb Amount slider
  - Sustain Pedal toggle
  - Piano type selector (Grand/Home/Old)

- **Hardware Mapping:**
  - 4 knobs visualization showing current positions
  - Knob assignments clearly labeled
  - Real-time parameter values

- **Status Bar:**
  - Voices: X/32
  - Preset name: "Grand_Bright_Reverb"
  - MIDI Activity indicator

**Color Scheme:**
- Background: Dark slate
- Accent: Gold (#d4af37)
- Text: Light gray
- Active: Green (#2ecc71)
- Inactive: Dark gray

### Electric Piano UI Mockup
**Display:** 7-inch touchscreen

**Elements:**
- **Instrument Selector:** E.Piano highlighted
- **Tine Tuning Visualization:**
  - 12 tine bars showing tuning status
  - Some highlighted in orange (detuned)
  - Real-time visual feedback

- **Effects Chain:**
  - Chorus on/off toggle with depth slider
  - Phaser on/off toggle with rate slider
  - Bell Tone toggle
  - Reverb on/off toggle

- **Parameters:**
  - Tone brightness slider
  - Velocity response slider
  - Tremolo speed slider

**Visual Features:**
- Color accent: Orange (#e67e22)
- Detuned indicators: Bright orange with glow
- Effect toggles: Green when active

### Organ UI Mockup
**Display:** 7-inch touchscreen

**Elements:**
- **9 Hammond Drawbars:**
  - Vertical bar chart visualization
  - Each drawbar shows current level (0-8)
  - Labeled: 16', 5⅓', 8', 4', 2⅔', 2', 1⅗', 1⅓', 1'

- **Leslie Rotary Speaker:**
  - 3 wheel visualizations
  - Stop/Slow/Fast states
  - Rotating animation (Slow = 0.8Hz, Fast = 2.5Hz)
  - Current speed indicator

- **Effects:**
  - Overdrive drive slider
  - Reverb room slider

**Visual Features:**
- Color accent: Orange (#f39c12)
- Animated Leslie wheels
- Drawbar visualization with gradient fill

### Melotron UI Mockup
**Display:** 7-inch touchscreen

**Elements:**
- **Tape Transport Visualization:**
  - Supply reel and take-up reel
  - Tape threading visualization
  - Tape position counter (00:45.2)
  - Tape running indicator

- **Voice Selection:**
  - 3 buttons: Violins (active), Choir, Flute
  - Selected voice highlighted

- **Tape Stacking:**
  - Combination mode checkboxes
  - Multi-select for layer combinations
  - "All Three Layers" enabled

- **Effects:**
  - Reverb (Hall Space) slider
  - Tape Saturation slider
  - Delay slider
  - Wow & Flutter slider

**Visual Features:**
- Color accent: Cream (#e8dcc8) - vintage aesthetic
- Reel animation (supply/take-up)
- Tape counter display
- Tape running status indicator

### Synth Pad UI Mockup
**Display:** 7-inch touchscreen

**Elements:**
- **Waveform Selector:**
  - 4 buttons: Sine (active), Triangle, Square, Sawtooth
  - Each with waveform preview

- **ADSR Envelope:**
  - Visual graph showing attack/decay/sustain/release curve
  - Interactive envelope points
  - Attack: 45ms, Decay: 120ms, Sustain: 65%, Release: 200ms

- **Arpeggiator Settings:**
  - Mode selector: Up (active), Down, UpDn
  - Tempo display: 120 BPM
  - Note range slider
  - Gate time slider

- **Effects Chain:**
  - Chorus slider (70%)
  - Reverb slider (60%)
  - LFO Rate slider (40%)
  - LFO Depth slider (45%)

**Visual Features:**
- Color accent: Blue (#4a90e2)
- Animated envelope visualization
- Real-time parameter display
- Tempo synchronization display

---

## UI MOCKUPS - SMK-37

### Compact Piano UI
**Display:** 3-inch OLED (128×64 monochrome)

**Elements:**
- Instrument name: "PIANO"
- Mode indicator: [1] active
- Touch slider labels: Tone, Reverb, Sustain, Expr
- Preset display: "Grand_Bright"
- Voice indicator: "0/16"

**Character-Based Display:**
- Minimal information density
- Clear text hierarchy
- Real-time parameter values

### Compact Organ UI
**Display:** 3-inch OLED

**Elements:**
- Instrument name: "ORGAN"
- Drawbar visualization (text-based):
  ```
  16' ████░░░░
  8'  ██████░░
  4'  ████░░░░
  ...
  ```
- Leslie status: "FAST 2.5Hz"
- Overdrive level: "45%"

### Compact Synth UI
**Display:** 3-inch OLED

**Elements:**
- Instrument name: "SYNTH"
- Arp status: "UP 120BPM"
- LFO: "5.5Hz, 45%"
- Filter: "2.4kHz"
- Voice pool: "8/16"

---

## UI ELEMENT REFERENCE

### Common UI Components

#### Status Bar (All Instruments)
```
┌──────────────────────────────────────────────────────────┐
│ ✓ MIDI Active │ Preset_Name │ Voices: X/32              │
└──────────────────────────────────────────────────────────┘
```

**Elements:**
- MIDI activity indicator (dot or checkmark)
- Current preset name
- Voice count (current/maximum)
- Update frequency: 50ms

#### Instrument Selector
```
┌─ Instruments ─────────────────────────────────────────────┐
│ → [0] Piano                                            │
│   [1] Electric Piano                                   │
│   [2] Organ                                            │
│   [3] Melotron                                         │
│   [4] Synth Pad                                        │
└───────────────────────────────────────────────────────────┘
```

**Elements:**
- 5 instrument options
- Arrow indicator for current selection
- Number keys for quick access

#### Parameter Slider
```
Parameter Name: Tone Brightness
━━━━◉━━━━━━ [35%]
Dark        Bright
```

**Elements:**
- Label
- Slider bar with filled section
- Circular knob indicator
- Percentage display
- Min/Max labels

#### Button Grid (FM-1)
```
[Red] [Green] [Blue]  [Yellow]
[Purple] [Cyan] [White] [Orange]
...
```

**States:**
- **Off (Gray):** Disabled
- **Green:** Enabled/Active
- **Red:** Warning/Alert
- **Blue:** Standby
- **Yellow/Cyan/Purple:** Secondary functions

---

## COLOR SCHEME & DESIGN SYSTEM

### FM-1 Color Palette

| Color | Hex | Usage | Notes |
|-------|-----|-------|-------|
| Dark Slate | #1a1f2e | Main background | Professional, dark theme |
| Gold | #d4af37 | Accent, Piano theme | Warm, luxury feel |
| Orange | #e67e22 | E.Piano/Organ theme | Energetic |
| Blue | #4a90e2 | Synth theme | Cool, modern |
| Cream | #e8dcc8 | Melotron theme | Vintage, warm |
| Green | #2ecc71 | Active state | Success indicator |
| Red | #e74c3c | Warning/Active | Alert indicator |
| Gray | #999999 | Inactive labels | Low emphasis |

### Typography

| Element | Font | Size | Weight |
|---------|------|------|--------|
| Title | Helvetica-Bold | 24pt | Bold |
| Heading | Helvetica-Bold | 14pt | Bold |
| Parameter | Helvetica | 12pt | Regular |
| Value | Monospace | 10-12pt | Regular |
| Label | Helvetica | 11pt | Regular |

### Layout Principles

**FM-1 (1024×600 display):**
- 50px top margin for instrument selector
- 300px main parameter area
- 200px knob visualization
- 50px status bar

**SMK-37 (128×64 OLED):**
- Minimal whitespace
- Monochrome optimization
- Text-based visualization
- Real-time parameter display

### Visual Hierarchy

1. **Primary:** Instrument name, main parameters
2. **Secondary:** Effect controls, preset name
3. **Tertiary:** Status indicators, voice count

---

## SCREENSHOT CAPTURE INSTRUCTIONS

### How to Capture Emulator Screenshots

```bash
# Start emulator
./build/emulator/mwave_emulator

# In separate terminal, send commands
echo "P" | nc localhost 9999  # Send command via network
```

### How to Capture UI Mockup Displays

The UI mockups are rendered as interactive HTML in the documentation. To capture:

1. **HTML Mockup Location:** Located in Claude documentation artifacts
2. **Capture Method:** Browser screenshot tool
3. **Resolution:** Full browser window (responsive design)
4. **Export Formats:** PNG, SVG, PDF

### Recommended Screenshot Tools

| Tool | Platform | Quality |
|------|----------|---------|
| Flameshot | Linux | High |
| Snagit | Windows/Mac | Very High |
| Screenshot | macOS | High |
| Print Screen | All | Medium |

---

## UI DESIGN DOCUMENTATION

### Design System Files

Located in project repository:
- `docs/ui-design-system.md` - Complete design guidelines
- `emulator/resources/themes/` - Theme definitions
- `firmware/src/ui/` - Hardware UI rendering code

### Responsive Design

**FM-1:**
- Display: 1024×600 (fixed resolution)
- Touch: Capacitive (10-point multitouch)
- Orientation: Landscape only

**SMK-37:**
- Display: 128×64 monochrome OLED (fixed)
- Touch: 8 capacitive sliders (vertical)
- Orientation: Portrait only

### Accessibility Features

✓ High contrast (dark theme)
✓ Large touch targets (>44px minimum)
✓ Clear color coding (green=on, red=off)
✓ Text-based labels (not icon-only)
✓ Real-time feedback (status updates)

---

## APPENDIX: DESIGN RESOURCES

### Download UI Mockup Files

All UI mockups are available as:
- **HTML (Interactive):** View in browser with real-time interaction
- **SVG (Vector):** Scalable for documentation
- **PNG (Raster):** 1024×600 @ 72 DPI

### Theme Customization

Themes can be customized via EEPROM settings:
- Accent color (RGB)
- Brightness levels
- Font selection
- Layout variants

### Design Tools Used

- **SVG/HTML:** Hand-coded for performance
- **Color Scheme:** Professional palette generator
- **Typography:** System fonts (no external dependencies)
- **Icons:** ASCII art + Unicode symbols

---

**Document Version 1.0** | Generated November 21, 2026
**MWAVE Design Team** | UI/UX Documentation

---

## Document Revision History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | Nov 2026 | Initial screenshot and UI documentation |

---

## Support & Feedback

For design feedback:
- **GitHub Issues:** github.com/mwave/ui-feedback
- **Forum:** forums.mwave-synth.org/ui-design
- **Email:** design@mwave-synth.org
