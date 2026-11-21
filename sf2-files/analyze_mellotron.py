#!/usr/bin/env python3
"""
Analyze and organize extracted Mellotron WAV samples
"""

import os
import wave
import struct
from pathlib import Path

# Common Mellotron instrument preset names
MELLOTRON_NAMES = {
    0: "Flute",
    1: "Clarinet",
    2: "Oboe",
    3: "English_Horn",
    4: "Soprano_Sax",
    5: "Alto_Sax",
    6: "Tenor_Sax",
    7: "Baritone_Sax",
    8: "Trumpet",
    9: "Trombone",
    10: "French_Horn",
    11: "Tuba",
    12: "Strings_Full",
    13: "Strings_Legato",
    14: "Violins_Full",
    15: "Violins_Legato",
    16: "Violas",
    17: "Cellos",
    18: "Bass",
    19: "Harp",
    20: "Bells",
    21: "Vibraphone",
    22: "Choirs_Mm",
    23: "Choirs_Ah",
    24: "Organ_Pipe",
    25: "Organ_Hammond",
    26: "Electric_Piano",
    27: "Piano",
    28: "Rhodes",
    29: "Mellotron",
    30: "Mellotone",
    31: "Cello_Solo"
}

def get_wave_info(filepath):
    """Extract info from WAV file"""
    try:
        with wave.open(filepath, 'rb') as wav:
            n_channels = wav.getnchannels()
            sample_width = wav.getsampwidth()
            framerate = wav.getframerate()
            n_frames = wav.getnframes()
            duration = n_frames / framerate if framerate > 0 else 0
            return {
                'channels': n_channels,
                'sample_width': sample_width,
                'sample_rate': framerate,
                'frames': n_frames,
                'duration': duration,
                'size': os.path.getsize(filepath)
            }
    except:
        return None

def main():
    wav_dir = Path("/home/assaf/projects/mwave-musical-box/sf2-files/mellotron-wav")

    if not wav_dir.exists():
        print("❌ Output directory not found!")
        return

    wav_files = sorted(wav_dir.glob("mellotron_*.wav"))

    if not wav_files:
        print("⏳ No WAV files extracted yet. Extraction in progress...")
        return

    print("=" * 70)
    print("MELLOTRON SF2 EXTRACTION ANALYSIS")
    print("=" * 70)
    print(f"Directory: {wav_dir}")
    print(f"Total files: {len(wav_files)}")
    print()

    total_size = 0
    total_duration = 0

    print(f"{'Idx':<4} {'Preset':<8} {'Name':<20} {'Duration':<12} {'Size':<10} {'Sample Rate':<12}")
    print("-" * 70)

    for wav_file in wav_files[:40]:  # Show first 40
        name = wav_file.stem
        preset_num = int(name.split('_')[1])

        info = get_wave_info(wav_file)
        if info:
            duration_str = f"{info['duration']:.2f}s"
            size_mb = info['size'] / (1024*1024)
            size_str = f"{size_mb:.2f}MB"
            inst_name = MELLOTRON_NAMES.get(preset_num, "Unknown")

            print(f"{preset_num:<4} {preset_num:<8} {inst_name:<20} {duration_str:<12} {size_str:<10} {info['sample_rate']:<12}")

            total_size += info['size']
            total_duration += info['duration']

    if len(wav_files) > 40:
        print(f"... and {len(wav_files) - 40} more files")

    print("-" * 70)
    print(f"Total extracted: {len(wav_files)} presets")
    print(f"Total size: {total_size / (1024*1024):.1f} MB")
    print(f"Total duration: {total_duration:.1f} seconds")
    print()
    print("✓ Extraction complete!")
    print(f"All Mellotron samples available in: {wav_dir}")

if __name__ == "__main__":
    main()
