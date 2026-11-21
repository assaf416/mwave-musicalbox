#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <string>

class SynthEmulator;

class ConsoleUI {
public:
  ConsoleUI(SynthEmulator *synth);
  ~ConsoleUI();

  void displayMenu();
  void displayStatus();
  void run();

private:
  void displayBanner();
  void displayInstruments();
  void handleCommand(char cmd);
  void playHelloWorld();
  void changeInstrument();
  void adjustReverb();

  SynthEmulator *synth;
  int currentInstrument;
  int reverbAmount;
  bool isRunning;
};

#endif // CONSOLE_UI_H
