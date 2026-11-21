// MWAVE FM-1 Web Synthesizer Engine
// Real-time audio synthesis with 32-voice polyphony

const audioContext = new (window.AudioContext || window.webkitAudioContext)();

// Global parameters
let currentOctave = 4;
let currentInstrument = 3; // Melotron
let currentWaveform = 'triangle';
let masterVolume = 0.7;
let reverbAmount = 0.5;
let decayTime = 0.5;

// Control state
const knobValues = new Array(16).fill(0);
const faderValues = new Array(8).fill(0);
const activeVoices = new Map();
const MAX_VOICES = 32;

// Reverb setup
const convolver = audioContext.createConvolver();
const dryGain = audioContext.createGain();
const wetGain = audioContext.createGain();
const masterGain = audioContext.createGain();

dryGain.connect(masterGain);
wetGain.connect(masterGain);
masterGain.connect(audioContext.destination);
convolver.connect(wetGain);

// Create reverb impulse response
function createReverbImpulse() {
    const rate = audioContext.sampleRate;
    const length = rate * 2;
    const impulse = audioContext.createBuffer(2, length, rate);
    const left = impulse.getChannelData(0);
    const right = impulse.getChannelData(1);
    for (let i = 0; i < length; i++) {
        left[i] = (Math.random() * 2 - 1) * Math.pow(1 - i / length, 2);
        right[i] = (Math.random() * 2 - 1) * Math.pow(1 - i / length, 2);
    }
    return impulse;
}

convolver.buffer = createReverbImpulse();

// Instrument characteristics
const instrumentSettings = {
    0: { name: 'Piano', attack: 0.01, sustain: 0.9, timbre: 1.2 },
    1: { name: 'Electric Piano', attack: 0.02, sustain: 0.7, timbre: 1.5 },
    2: { name: 'Organ', attack: 0.05, sustain: 1.0, timbre: 2.0 },
    3: { name: 'Melotron', attack: 0.1, sustain: 0.8, timbre: 1.8 },
    4: { name: 'Synth Pad', attack: 0.2, sustain: 1.0, timbre: 1.0 }
};

// Presets storage
let allPresets = [];
let currentPresetId = null;

// Load presets from JSON file
async function loadPresets() {
    try {
        const response = await fetch('presets.json');
        const data = await response.json();
        allPresets = data.presets;
        populatePresetDropdown();
        console.log(`✓ Loaded ${allPresets.length} presets`);
    } catch (error) {
        console.error('Failed to load presets:', error);
    }
}

// Populate preset dropdown
function populatePresetDropdown() {
    const dropdown = document.getElementById('presetSelector');
    if (!dropdown) return;

    dropdown.innerHTML = '<option value="">-- Select a Preset --</option>';

    // Group presets by instrument
    const mellotronPresets = allPresets.filter(p => p.instrument === 'Melotron');
    const organPresets = allPresets.filter(p => p.instrument === 'Organ');
    const pianoPresets = allPresets.filter(p => p.instrument === 'Piano');
    const epPresets = allPresets.filter(p => p.instrument === 'Electric Piano');

    if (mellotronPresets.length > 0) {
        const group = document.createElement('optgroup');
        group.label = '🎺 Mellotron Presets';
        mellotronPresets.forEach(p => {
            const option = document.createElement('option');
            option.value = p.id;
            option.textContent = `${p.name} (${p.artist})`;
            group.appendChild(option);
        });
        dropdown.appendChild(group);
    }

    if (organPresets.length > 0) {
        const group = document.createElement('optgroup');
        group.label = '🎹 Organ Presets';
        organPresets.forEach(p => {
            const option = document.createElement('option');
            option.value = p.id;
            option.textContent = `${p.name} (${p.artist})`;
            group.appendChild(option);
        });
        dropdown.appendChild(group);
    }

    if (pianoPresets.length > 0) {
        const group = document.createElement('optgroup');
        group.label = '🎼 Piano Presets';
        pianoPresets.forEach(p => {
            const option = document.createElement('option');
            option.value = p.id;
            option.textContent = `${p.name} (${p.artist})`;
            group.appendChild(option);
        });
        dropdown.appendChild(group);
    }

    if (epPresets.length > 0) {
        const group = document.createElement('optgroup');
        group.label = '⚡ Electric Piano Presets';
        epPresets.forEach(p => {
            const option = document.createElement('option');
            option.value = p.id;
            option.textContent = `${p.name} (${p.artist})`;
            group.appendChild(option);
        });
        dropdown.appendChild(group);
    }
}

// Apply a preset to the synthesizer
function applyPreset(presetId) {
    const preset = allPresets.find(p => p.id === presetId);
    if (!preset) return;

    currentPresetId = presetId;
    const s = preset.settings;

    // Apply instrument
    const instrumentMap = { 'Piano': 0, 'Electric Piano': 1, 'Organ': 2, 'Melotron': 3, 'Synth Pad': 4 };
    const instIndex = instrumentMap[preset.instrument] || 3;
    document.getElementById('instrument').value = instIndex;
    changeInstrument();

    // Apply waveform
    if (s.waveform) {
        document.getElementById('waveform').value = s.waveform;
        changeWaveform();
    }

    // Apply master volume
    document.getElementById('volume').value = s.masterVolume;
    updateVolume();

    // Apply reverb
    document.getElementById('reverb').value = s.reverb;
    updateReverb();

    // Apply decay time
    document.getElementById('decay').value = s.decayTime;
    updateDecay();

    // Apply knobs (CC20-CC35)
    const knobMap = {
        'cc20_filter': 0, 'cc21_resonance': 1, 'cc22_attack': 2, 'cc23_decay': 3,
        'cc24_sustain': 4, 'cc25_release': 5, 'cc26_lfo_amt': 6, 'cc27_lfo_rate': 7,
        'cc28_vibrato': 8, 'cc29_tremolo': 9, 'cc30_pan': 10, 'cc31_tuning': 11,
        'cc32_env_amt': 12, 'cc33_chorus': 13, 'cc34_phaser': 14, 'cc35_delay': 15
    };

    Object.entries(s.knobs).forEach(([ccName, value]) => {
        const knobIndex = knobMap[ccName];
        if (knobIndex !== undefined) {
            knobValues[knobIndex] = value;
            const knob = document.getElementById(`knob${knobIndex}`);
            if (knob) {
                knob.style.setProperty('--rotation', value * 3.6);
                const valDisplay = document.getElementById(`knob${knobIndex}Val`);
                if (valDisplay) valDisplay.textContent = Math.round(value) + '%';
            }
        }
    });

    // Apply faders (CC36-CC43)
    if (s.faders) {
        s.faders.forEach((value, index) => {
            const fader = document.getElementById(`fader${index}`);
            if (fader) {
                fader.value = value;
                faderValues[index] = value;
            }
        });
    }

    // Show preset info
    const presetInfo = document.getElementById('presetInfo');
    if (presetInfo) {
        presetInfo.innerHTML = `<strong>${preset.name}</strong><br><small>${preset.artist}</small><br><em>${preset.description}</em>`;
    }

    console.log(`✓ Applied preset: ${preset.name} (${preset.artist})`);
}

// Handle preset selection
function handlePresetChange() {
    const presetId = document.getElementById('presetSelector').value;
    if (presetId) {
        applyPreset(presetId);
    }
}

// Initialize keyboard
function initKeyboard() {
    const keyboard = document.getElementById('keyboard');
    const notes = ['C', 'D', 'E', 'F', 'G', 'A', 'B'];
    const noteValues = [0, 2, 4, 5, 7, 9, 11];

    for (let i = 0; i < 7; i++) {
        const key = document.createElement('div');
        key.className = 'key';
        key.textContent = notes[i];
        key.id = `key-${i}`;

        const freq = noteToFrequency(60 + noteValues[i], currentOctave);
        key.dataset.frequency = freq;
        key.dataset.note = i;

        key.addEventListener('mousedown', () => playNote(key));
        key.addEventListener('mouseup', () => stopNote(key));
        key.addEventListener('mouseleave', () => stopNote(key));

        keyboard.appendChild(key);
    }
}

// Initialize knobs with mouse drag
function initKnobs() {
    for (let i = 0; i < 16; i++) {
        const knob = document.getElementById(`knob${i}`);
        let isDragging = false;
        let lastY = 0;

        knob.addEventListener('mousedown', (e) => {
            isDragging = true;
            lastY = e.clientY;
        });

        document.addEventListener('mousemove', (e) => {
            if (!isDragging) return;

            const delta = lastY - e.clientY;
            knobValues[i] = Math.max(0, Math.min(100, knobValues[i] + delta));

            knob.style.setProperty('--rotation', knobValues[i] * 3.6);
            document.getElementById(`knob${i}Val`).textContent = Math.round(knobValues[i]) + '%';

            lastY = e.clientY;
        });

        document.addEventListener('mouseup', () => {
            isDragging = false;
        });
    }
}

// Note to frequency conversion
function noteToFrequency(note, octave) {
    return 440 * Math.pow(2, (note - 69 + (octave - 4) * 12) / 12);
}

// Create voice (oscillator + envelope)
function createVoice(frequency) {
    if (activeVoices.size >= MAX_VOICES) return null;

    const settings = instrumentSettings[currentInstrument];

    const osc = audioContext.createOscillator();
    const gain = audioContext.createGain();
    const filter = audioContext.createBiquadFilter();

    osc.type = currentWaveform;
    osc.frequency.value = frequency;

    // Apply filter cutoff based on knob 0 (CC20)
    filter.frequency.value = 500 + (knobValues[0] / 100) * 7500;
    filter.type = 'lowpass';
    filter.Q.value = 2 + (knobValues[1] / 100) * 10;

    osc.connect(filter);
    filter.connect(gain);
    gain.connect(dryGain);
    gain.connect(convolver);

    // Attack envelope
    const now = audioContext.currentTime;
    const attackTime = settings.attack + (knobValues[2] / 100) * 0.2;
    gain.gain.setValueAtTime(0, now);
    gain.gain.linearRampToValueAtTime(masterVolume * settings.attack, now + attackTime);

    osc.start(now);

    const voiceId = `${frequency}-${now}`;
    activeVoices.set(voiceId, { osc, gain, filter, startTime: now });

    return voiceId;
}

// Stop voice with release envelope
function stopVoice(voiceId) {
    if (!activeVoices.has(voiceId)) return;

    const voice = activeVoices.get(voiceId);
    const now = audioContext.currentTime;

    voice.gain.gain.setValueAtTime(voice.gain.gain.value, now);
    voice.gain.gain.linearRampToValueAtTime(0, now + decayTime);

    voice.osc.stop(now + decayTime);

    setTimeout(() => {
        activeVoices.delete(voiceId);
        updateDisplay();
    }, decayTime * 1000);

    updateDisplay();
}

// Play note from keyboard
function playNote(keyElement) {
    const freq = parseFloat(keyElement.dataset.frequency);
    const voiceId = createVoice(freq);

    if (voiceId) {
        keyElement.classList.add('active');
        keyElement.dataset.voiceId = voiceId;
        document.getElementById('freqDisplay').textContent = freq.toFixed(1) + ' Hz';
    }
}

// Stop note from keyboard
function stopNote(keyElement) {
    const voiceId = keyElement.dataset.voiceId;
    if (voiceId) {
        stopVoice(voiceId);
        keyElement.classList.remove('active');
        delete keyElement.dataset.voiceId;
    }
}

// Control functions
function changeInstrument() {
    currentInstrument = parseInt(document.getElementById('instrument').value);
    const names = ['Piano', 'Electric Piano', 'Organ', 'Melotron', 'Synth Pad'];
    document.getElementById('instrumentDisplay').textContent = names[currentInstrument];
    updateOledScreen();
}

function changeWaveform() {
    currentWaveform = document.getElementById('waveform').value;
}

function updateVolume() {
    const val = document.getElementById('volume').value;
    masterVolume = val / 100;
    document.getElementById('volPercent').textContent = val + '%';
    document.getElementById('volumeDisplay').textContent = val + '%';
    masterGain.gain.value = masterVolume;
    updateOledScreen();
}

function updateReverb() {
    const val = document.getElementById('reverb').value / 100;
    wetGain.gain.value = val * 0.3;
    dryGain.gain.value = 1;
    document.getElementById('revPercent').textContent = Math.round(val * 100) + '%';
    document.getElementById('reverbDisplay').textContent = Math.round(val * 100) + '%';
}

function updateDecay() {
    const val = document.getElementById('decay').value;
    decayTime = parseFloat(val);
    document.getElementById('decayPercent').textContent = val + 's';
}

function updateFader(index) {
    const val = document.getElementById(`fader${index}`).value;
    faderValues[index] = val;
}

function increaseOctave() {
    if (currentOctave < 7) {
        currentOctave++;
        document.getElementById('octaveNum').textContent = currentOctave;
        updateKeyboardFrequencies();
    }
}

function decreaseOctave() {
    if (currentOctave > 1) {
        currentOctave--;
        document.getElementById('octaveNum').textContent = currentOctave;
        updateKeyboardFrequencies();
    }
}

function updateKeyboardFrequencies() {
    const notes = [0, 2, 4, 5, 7, 9, 11];
    for (let i = 0; i < 7; i++) {
        const key = document.getElementById(`key-${i}`);
        const freq = noteToFrequency(60 + notes[i], currentOctave);
        key.dataset.frequency = freq;
    }
}

function stopAll() {
    const keys = document.querySelectorAll('.key.active');
    keys.forEach(key => stopNote(key));
    activeVoices.forEach((voice, id) => stopVoice(id));
}

function pressButton(index) {
    console.log(`Button ${index + 1} pressed (Note ${60 + index})`);
    // Could trigger MIDI or preset changes
}

function playDemo() {
    stopAll();
    const sequence = [
        { note: 0, octave: currentOctave, duration: 300 },
        { note: 0, octave: currentOctave, duration: 300 },
        { note: 2, octave: currentOctave, duration: 300 },
        { note: 4, octave: currentOctave, duration: 300 },
        { note: 0, octave: currentOctave, duration: 300 },
        { note: 4, octave: currentOctave, duration: 300 },
        { note: 7, octave: currentOctave, duration: 600 }
    ];

    let time = 0;
    sequence.forEach(note => {
        setTimeout(() => {
            const freq = noteToFrequency(60 + [0, 2, 4, 5, 7, 9, 11][note.note], note.octave);
            const voiceId = createVoice(freq);
            setTimeout(() => {
                if (voiceId && activeVoices.has(voiceId)) {
                    stopVoice(voiceId);
                }
            }, note.duration);
        }, time);
        time += note.duration;
    });
}

function updateDisplay() {
    document.getElementById('voiceDisplay').textContent = `${activeVoices.size} / ${MAX_VOICES}`;
}

// Waveform visualization
const canvas = document.getElementById('waveform');
const canvasCtx = canvas.getContext('2d');
let analyser = null;
let dataArray = null;

function initAnalyser() {
    if (!analyser) {
        analyser = audioContext.createAnalyser();
        masterGain.connect(analyser);
        analyser.fftSize = 2048;
        dataArray = new Uint8Array(analyser.frequencyBinCount);
    }
}

function drawWaveform() {
    initAnalyser();
    analyser.getByteFrequencyData(dataArray);

    canvasCtx.fillStyle = '#0a0e27';
    canvasCtx.fillRect(0, 0, canvas.width, canvas.height);

    // Draw frequency bars
    canvasCtx.strokeStyle = '#00ff88';
    canvasCtx.lineWidth = 2;
    canvasCtx.beginPath();

    const sliceWidth = canvas.width / analyser.frequencyBinCount;
    let x = 0;

    for (let i = 0; i < analyser.frequencyBinCount; i++) {
        const v = dataArray[i] / 128.0;
        const y = (v * canvas.height) / 2;

        if (i === 0) {
            canvasCtx.moveTo(x, y);
        } else {
            canvasCtx.lineTo(x, y);
        }

        x += sliceWidth;
    }

    canvasCtx.stroke();

    // Draw grid
    canvasCtx.strokeStyle = 'rgba(0, 255, 136, 0.1)';
    canvasCtx.lineWidth = 0.5;
    for (let i = 0; i < 5; i++) {
        const y = (canvas.height / 5) * i;
        canvasCtx.beginPath();
        canvasCtx.moveTo(0, y);
        canvasCtx.lineTo(canvas.width, y);
        canvasCtx.stroke();
    }

    requestAnimationFrame(drawWaveform);
}

// OLED Screen Management
function updateOledScreen() {
    const screen = document.getElementById('oledScreen');
    const content = document.getElementById('oledContent');
    const status = document.getElementById('screenStatus');

    const instrumentName = instrumentSettings[currentInstrument].name;
    const voiceCount = activeVoices.size;
    const volumePercent = Math.round(masterVolume * 100);

    // Update screen content
    let screenText = `${instrumentName}\n`;
    screenText += `Voices: ${voiceCount}/32\n`;
    screenText += `Vol: ${volumePercent}% Oct:${currentOctave}`;

    content.textContent = screenText;

    // Update status indicator
    if (voiceCount > 0) {
        status.textContent = `● PLAYING (${voiceCount})`;
        screen.classList.add('on');
    } else {
        status.textContent = '● READY';
        screen.classList.add('on');
    }
}

function updateScreenWhenNotesChange() {
    updateOledScreen();
}

// Initialize everything
window.addEventListener('DOMContentLoaded', () => {
    loadPresets();
    initKeyboard();
    initKnobs();
    updateVolume();
    updateReverb();
    updateDecay();
    updateOledScreen();
    drawWaveform();

    // Update screen every 100ms
    setInterval(updateOledScreen, 100);
});
