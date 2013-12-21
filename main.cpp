/******************************************************************************
 * Copyright (c) 2011-2013 Artur Molchanov <artur.molchanov@gmail.com>        *
 *                                                                            *
 * This program is free software: you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
 ******************************************************************************/

#include "GUI/face.h"

#include <QApplication>
#include <QTextCodec>

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
