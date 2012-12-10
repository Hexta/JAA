/*
 * File:   main.cpp
 * Author: art
 *
 * Created on 7 Март 2011 г., 22:14
 */

#include <QApplication>
#include <QTextCodec>
#include "GUI/Face/face.h"

int
main(int argc, char *argv[]) {
  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForTr(codec);

  QApplication app(argc, argv);

  Face * mainw = new Face();

  mainw->setWindowTitle(QObject::tr("Just another archiver"));
  mainw->show();

  return app.exec();
}
