#include <QApplication>
#include <QDebug>
#include "ui_window.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  qDebug() << "MWAVE Musical Box - Desktop Emulator";
  qDebug() << "Starting UI...";

  UIWindow window;
  window.setWindowTitle("MWAVE FM-1 & SMK-37 Emulator");
  window.resize(1024, 768);
  window.show();

  return app.exec();
}
