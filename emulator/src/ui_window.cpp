#include "ui_window.h"
#include "synth_emulator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QDebug>
#include <QComboBox>

UIWindow::UIWindow(QWidget *parent)
  : QMainWindow(parent), synth(nullptr) {

  synth = new SynthEmulator(this);
  setupUI();
  connectSignals();

  updateTimer = new QTimer(this);
  connect(updateTimer, &QTimer::timeout, this, &UIWindow::onUpdateDisplay);
  updateTimer->start(50); // Update every 50ms

  qDebug() << "UIWindow initialized";
}

UIWindow::~UIWindow() {
}

void UIWindow::setupUI() {
  QWidget *centralWidget = new QWidget(this);
  QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

  // Title
  QLabel *titleLabel = new QLabel("MWAVE Musical Box - Hello World Demo");
  titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; padding: 10px;");
  mainLayout->addWidget(titleLabel);

  // Instrument selector
  QHBoxLayout *instrumentLayout = new QHBoxLayout();
  instrumentLayout->addWidget(new QLabel("Instrument:"));
  QComboBox *instrumentCombo = new QComboBox();
  instrumentCombo->addItem("Piano");
  instrumentCombo->addItem("Electric Piano");
  instrumentCombo->addItem("Organ");
  instrumentCombo->addItem("Melotron");
  instrumentCombo->addItem("Synth");
  connect(instrumentCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &UIWindow::onInstrumentChanged);
  instrumentLayout->addWidget(instrumentCombo);
  instrumentLayout->addStretch();
  mainLayout->addLayout(instrumentLayout);

  // Control group
  QGroupBox *controlGroup = new QGroupBox("Playback Controls");
  QHBoxLayout *controlLayout = new QHBoxLayout(controlGroup);

  playBtn = new QPushButton("Play Hello World");
  playBtn->setMinimumHeight(40);
  playBtn->setStyleSheet("background-color: #2ecc71; color: white; font-weight: bold;");
  connect(playBtn, &QPushButton::clicked, this, &UIWindow::onPlayHelloWorld);
  controlLayout->addWidget(playBtn);

  stopBtn = new QPushButton("Stop");
  stopBtn->setMinimumHeight(40);
  stopBtn->setStyleSheet("background-color: #e74c3c; color: white; font-weight: bold;");
  connect(stopBtn, &QPushButton::clicked, this, &UIWindow::onStopAll);
  controlLayout->addWidget(stopBtn);

  mainLayout->addWidget(controlGroup);

  // Effects group
  QGroupBox *effectsGroup = new QGroupBox("Effects");
  QVBoxLayout *effectsLayout = new QVBoxLayout(effectsGroup);

  effectsLayout->addWidget(new QLabel("Reverb Amount:"));
  reverbSlider = new QSlider(Qt::Horizontal);
  reverbSlider->setMinimum(0);
  reverbSlider->setMaximum(100);
  reverbSlider->setValue(50);
  effectsLayout->addWidget(reverbSlider);

  mainLayout->addWidget(effectsGroup);

  // Status display
  QGroupBox *statusGroup = new QGroupBox("Status");
  QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);
  statusLabel = new QLabel("Ready. Click 'Play Hello World' to start.");
  statusLabel->setStyleSheet("padding: 10px; background-color: #f0f0f0; border-radius: 4px;");
  statusLayout->addWidget(statusLabel);
  mainLayout->addWidget(statusGroup);

  mainLayout->addStretch();
  setCentralWidget(centralWidget);
}

void UIWindow::connectSignals() {
  // Signals connected in setupUI
}

void UIWindow::onPlayHelloWorld() {
  qDebug() << "Playing Hello World melody...";

  // Hello World melody: C-C-C-D-E-C-E-G (C major scale arpeggio)
  synth->playNote(60, 100);  // Middle C
  synth->playNote(60, 100);
  synth->playNote(60, 100);
  synth->playNote(62, 100);  // D
  synth->playNote(64, 100);  // E
  synth->playNote(60, 100);  // C
  synth->playNote(64, 100);  // E
  synth->playNote(67, 100);  // G

  statusLabel->setText("Playing Hello World melody...");
}

void UIWindow::onStopAll() {
  qDebug() << "Stopping all notes";
  synth->stopAllNotes();
  statusLabel->setText("Stopped. Ready to play again.");
}

void UIWindow::onInstrumentChanged(int index) {
  qDebug() << "Instrument changed to:" << index;
  synth->setInstrument(index);
  statusLabel->setText(QString("Instrument set to index: %1").arg(index));
}

void UIWindow::onUpdateDisplay() {
  // Update status display with live info
  int activeVoices = synth->getActiveVoiceCount();
  QString status = QString("Active Voices: %1/32 | Reverb: %2%")
    .arg(activeVoices)
    .arg(reverbSlider->value());

  if (!statusLabel->text().contains("Playing") && !statusLabel->text().contains("Stopped")) {
    statusLabel->setText(status);
  }
}
