#include "console_ui.h"
#include "synth_emulator.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

ConsoleUI::ConsoleUI(SynthEmulator *synth)
  : synth(synth), currentInstrument(0), reverbAmount(50), isRunning(true) {
}

ConsoleUI::~ConsoleUI() {
}

void ConsoleUI::displayBanner() {
  std::cout << "\n";
  std::cout << "╔════════════════════════════════════════════════════════════╗\n";
  std::cout << "║   MWAVE Musical Box - Desktop Emulator                     ║\n";
  std::cout << "║   Firmware for MWAVE FM-1 & SMK-37 Synthesizers           ║\n";
  std::cout << "╚════════════════════════════════════════════════════════════╝\n";
  std::cout << "\n";
}

void ConsoleUI::displayInstruments() {
  const char *instruments[] = {
    "Piano",
    "Electric Piano",
    "Organ",
    "Melotron",
    "Synth Pad"
  };

  std::cout << "┌─ Instruments ─────────────────────────────────────────────┐\n";
  for (int i = 0; i < 5; ++i) {
    std::cout << "│ ";
    if (i == currentInstrument) {
      std::cout << "→ [" << i << "] " << instruments[i];
      // Pad to 55 chars
      int len = std::string(instruments[i]).length() + 7;
      std::cout << std::string(55 - len, ' ');
    } else {
      std::cout << "  [" << i << "] " << instruments[i];
      // Pad to 55 chars
      int len = std::string(instruments[i]).length() + 7;
      std::cout << std::string(55 - len, ' ');
    }
    std::cout << " │\n";
  }
  std::cout << "└───────────────────────────────────────────────────────────┘\n";
}

void ConsoleUI::displayStatus() {
  std::cout << "┌─ Status ──────────────────────────────────────────────────┐\n";
  std::cout << "│ Current Instrument: " << std::setw(38) << std::left
    << (currentInstrument == 0 ? "Piano" :
        currentInstrument == 1 ? "Electric Piano" :
        currentInstrument == 2 ? "Organ" :
        currentInstrument == 3 ? "Melotron" : "Synth Pad");
  std::cout << " │\n";

  std::cout << "│ Active Voices:      " << std::setw(5) << synth->getActiveVoiceCount()
    << "/32                                 │\n";

  std::cout << "│ Reverb Amount:      ";
  std::cout << std::setw(3) << reverbAmount << "%";
  std::cout << std::string(43 - 3, ' ') << " │\n";

  std::cout << "│ MIDI Status:        READY                            │\n";
  std::cout << "└───────────────────────────────────────────────────────────┘\n";
}

void ConsoleUI::displayMenu() {
  std::cout << "\n┌─ Commands ────────────────────────────────────────────────┐\n";
  std::cout << "│ [P] Play Hello World Melody                              │\n";
  std::cout << "│ [S] Stop All Notes                                       │\n";
  std::cout << "│ [I] Select Instrument (0-4)                              │\n";
  std::cout << "│ [R] Adjust Reverb (0-100)                                │\n";
  std::cout << "│ [Q] Quit Emulator                                        │\n";
  std::cout << "└───────────────────────────────────────────────────────────┘\n";
  std::cout << "\n> ";
  std::cout.flush();
}

void ConsoleUI::playHelloWorld() {
  std::cout << "\n▶ Playing Hello World melody on "
    << (currentInstrument == 0 ? "Piano" :
        currentInstrument == 1 ? "Electric Piano" :
        currentInstrument == 2 ? "Organ" :
        currentInstrument == 3 ? "Melotron" : "Synth Pad") << "...\n";

  // Hello World melody: C-C-C-D-E-C-E-G
  int melody[] = {60, 60, 60, 62, 64, 60, 64, 67};
  for (int note : melody) {
    std::cout << "  ♪ Note " << note << " (velocity 100)\n";
    synth->playNote(note, 100);
  }

  std::cout << "✓ Melody complete!\n";
  synth->stopAllNotes();
}

void ConsoleUI::changeInstrument() {
  std::cout << "\nSelect instrument (0-4): ";
  std::cout.flush();
  char choice;
  std::cin >> choice;
  int idx = choice - '0';
  if (idx >= 0 && idx < 5) {
    currentInstrument = idx;
    synth->setInstrument(idx);
    std::cout << "✓ Instrument changed\n";
  } else {
    std::cout << "✗ Invalid selection\n";
  }
}

void ConsoleUI::adjustReverb() {
  std::cout << "\nEnter reverb amount (0-100): ";
  std::cout.flush();
  std::cin >> reverbAmount;
  if (reverbAmount < 0) reverbAmount = 0;
  if (reverbAmount > 100) reverbAmount = 100;
  synth->setReverb(reverbAmount / 100.0f);
  std::cout << "✓ Reverb set to " << reverbAmount << "%\n";
}

void ConsoleUI::handleCommand(char cmd) {
  switch (cmd) {
    case 'P':
    case 'p':
      playHelloWorld();
      break;
    case 'S':
    case 's':
      std::cout << "\n⏹ Stopping all notes\n";
      synth->stopAllNotes();
      break;
    case 'I':
    case 'i':
      changeInstrument();
      break;
    case 'R':
    case 'r':
      adjustReverb();
      break;
    case 'Q':
    case 'q':
      std::cout << "\n✓ Goodbye!\n";
      isRunning = false;
      break;
    default:
      std::cout << "\n✗ Unknown command. Try again.\n";
  }
}

void ConsoleUI::run() {
  displayBanner();

  std::cout << "Initializing MWAVE emulator...\n";
  std::cout << "✓ Audio engine ready\n";
  std::cout << "✓ MIDI parser ready\n";
  std::cout << "✓ Synth ready with " << 32 << " voices\n";

  while (isRunning) {
    displayInstruments();
    displayStatus();
    displayMenu();

    char cmd;
    std::cin >> cmd;
    handleCommand(cmd);
  }

  std::cout << "\n";
}
