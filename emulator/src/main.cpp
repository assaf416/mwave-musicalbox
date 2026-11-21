#include <iostream>
#include "synth_emulator.h"
#include "console_ui.h"

int main(int argc, char *argv[]) {
  (void)argc;  // Unused
  (void)argv;  // Unused

  std::cout << "Initializing MWAVE Musical Box Emulator...\n";

  // Create synthesizer emulator
  SynthEmulator synth;

  // Create and run console UI
  ConsoleUI ui(&synth);
  ui.run();

  std::cout << "MWAVE Emulator terminated.\n";
  return 0;
}
