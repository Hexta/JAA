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

#ifndef STATINFOW_H
#define	STATINFOW_H

#include "Compressor/compressor.h"

#include <QDialog>

class QTableWidget;

class QLabel;

class StatInfoW : public QDialog {

  Q_OBJECT

public:
  struct StatInfo {
    QList< Compressor::CoderTypes> compressSequence;
    unsigned int blockSize;
    off_t inputSize;
    off_t outputSize;
    float speed;
  };
  StatInfoW(QWidget *parent = NULL);
  virtual ~StatInfoW();

public slots:
  void showInfo(StatInfo info);

private:
  QLabel *blockSizeLabel;
  QLabel *inputDataSizeLabel;
  QLabel *outputDataSizeLabel;
  QLabel *ratioLabel;
  QLabel *speedLabel;
  QLabel *encodingSequenceLabel;
  QLabel *encodingSequenceColumnLabel;
};

#endif	/* STATINFOW_H */

