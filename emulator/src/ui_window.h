#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QTimer>

class SynthEmulator;

class UIWindow : public QMainWindow {
  Q_OBJECT

public:
  UIWindow(QWidget *parent = nullptr);
  ~UIWindow();

private slots:
  void onPlayHelloWorld();
  void onStopAll();
  void onInstrumentChanged(int index);
  void onUpdateDisplay();

private:
  void setupUI();
  void connectSignals();

  SynthEmulator *synth;
  QLabel *statusLabel;
  QPushButton *playBtn;
  QPushButton *stopBtn;
  QSlider *instrumentSlider;
  QSlider *reverbSlider;
  QTimer *updateTimer;
};

#endif // UI_WINDOW_H
