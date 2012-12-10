/* 
 * File:   StatInfo.cpp
 * Author: art
 * 
 * Created on 21 Март 2011 г., 14:04
 */

#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include "statInfoW.h"
#include "../DataUnitsToQString/dataUnitsToQString.h"

StatInfoW::StatInfoW(QWidget * parent) : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint) {
  encodingSequenceColumnLabel = new QLabel(tr("Encoding Sequence"));
  encodingSequenceLabel = new QLabel();

  QLabel *blockSizeColumnLabel = new QLabel(tr("Block Size"));
  blockSizeLabel = new QLabel();

  QLabel *inputDataSizeColumnLabel = new QLabel(tr("Input Data Size"));
  inputDataSizeLabel = new QLabel();

  QLabel *outputDataSizeColumnLabel = new QLabel(tr("Output Data Size"));
  outputDataSizeLabel = new QLabel();

  QLabel *ratioColumnLabel = new QLabel(tr("Ratio"));
  ratioLabel = new QLabel();

  QLabel *speedColumnLabel = new QLabel(tr("Speed"));
  speedLabel = new QLabel();

  QPushButton *okButton = new QPushButton("&Ok");
  connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

  QGridLayout *grid = new QGridLayout;

  grid->setRowMinimumHeight(0, 10);

  grid->addWidget(encodingSequenceColumnLabel, 1, 0, Qt::AlignTop);
  grid->addWidget(encodingSequenceLabel, 1, 1, Qt::AlignTop);

  grid->addWidget(blockSizeColumnLabel, 2, 0, Qt::AlignTop);
  grid->addWidget(blockSizeLabel, 2, 1, Qt::AlignTop);

  grid->addWidget(inputDataSizeColumnLabel, 3, 0, Qt::AlignTop);
  grid->addWidget(inputDataSizeLabel, 3, 1, Qt::AlignTop);

  grid->addWidget(outputDataSizeColumnLabel, 4, 0, Qt::AlignTop);
  grid->addWidget(outputDataSizeLabel, 4, 1, Qt::AlignTop);

  grid->addWidget(ratioColumnLabel, 5, 0, Qt::AlignTop);
  grid->addWidget(ratioLabel, 5, 1, Qt::AlignTop);

  grid->addWidget(speedColumnLabel, 6, 0, Qt::AlignTop);
  grid->addWidget(speedLabel, 6, 1, Qt::AlignTop);

  grid->addWidget(okButton, 7, 1, Qt::AlignBottom);

  setLayout(grid);
}

StatInfoW::~StatInfoW() { }

void
StatInfoW::showInfo(StatInfo info) {
  blockSizeLabel->setText(DataUnitsToQString::convertDataSize(info.blockSize, 2));
  inputDataSizeLabel->setText(DataUnitsToQString::convertDataSize(info.inputSize, 2));
  outputDataSizeLabel->setText(DataUnitsToQString::convertDataSize(info.outputSize, 2));

  speedLabel->setText(DataUnitsToQString::convertDataSpeed(info.speed, 2));

  encodingSequenceLabel->setText("");

  QList< Compressor::CoderTypes> &compressSequence = info.compressSequence;

  //Compress Mode
  if (!compressSequence.empty()) {
    ratioLabel->setText(QString::number((float) 100 * info.outputSize / info.inputSize, 'f', 2) + " %");

    for (QList< Compressor::CoderTypes>::iterator i = compressSequence.begin();
         i != compressSequence.end(); ++i) {

      switch (*i) {
      case Compressor::BWT:
        encodingSequenceLabel->setText(encodingSequenceLabel->text() + "BWT ");
        break;
      case Compressor::HUFFMAN:
        encodingSequenceLabel->setText(encodingSequenceLabel->text() + "HUFFMAN ");
        break;
      case Compressor::MTF:
        encodingSequenceLabel->setText(encodingSequenceLabel->text() + "MTF ");
        break;
      case Compressor::RLE:
        encodingSequenceLabel->setText(encodingSequenceLabel->text() + "RLE ");
        break;
      case Compressor::NONE:
        break;
      }
    }
  } else//Decompress Mode
  {
    ratioLabel->setText(QString::number((float) 100 * info.outputSize / info.inputSize, 'f', 2) + " %");
    encodingSequenceColumnLabel->hide();
    encodingSequenceLabel->hide();
  }

  adjustSize();
  setFixedSize(width(), height());
}

