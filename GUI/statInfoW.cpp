/******************************************************************************
 * Copyright (c) 2011-2014 Artur Molchanov <artur.molchanov@gmail.com>        *
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

#include "statInfoW.h"
#include "dataUnitsToQString.h"

#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

StatInfoW::StatInfoW(QWidget* parent) :
    QDialog(parent,
        Qt::WindowTitleHint | Qt::WindowSystemMenuHint |
        Qt::WindowCloseButtonHint) {
    encodingSequenceColumnLabel = new QLabel(tr("Encoding Sequence"));
    encodingSequenceLabel = new QLabel();

    QLabel* blockSizeColumnLabel = new QLabel(tr("Block Size"));
    blockSizeLabel = new QLabel();

    QLabel* inputDataSizeColumnLabel = new QLabel(tr("Input Data Size"));
    inputDataSizeLabel = new QLabel();

    QLabel* outputDataSizeColumnLabel = new QLabel(tr("Output Data Size"));
    outputDataSizeLabel = new QLabel();

    QLabel* ratioColumnLabel = new QLabel(tr("Ratio"));
    ratioLabel = new QLabel();

    QLabel* speedColumnLabel = new QLabel(tr("Speed"));
    speedLabel = new QLabel();

    QPushButton* okButton = new QPushButton("&Ok");
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

    QGridLayout* grid = new QGridLayout;

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

StatInfoW::~StatInfoW() {
}

void StatInfoW::showInfo(StatInfo info) {
    blockSizeLabel->setText(DataUnitsToQString::convertDataSize(info.blockSize, 2));
    inputDataSizeLabel->setText(DataUnitsToQString::convertDataSize(info.inputSize, 2));
    outputDataSizeLabel->setText(DataUnitsToQString::convertDataSize(info.outputSize, 2));

    speedLabel->setText(DataUnitsToQString::convertDataSpeed(info.speed, 2));

    encodingSequenceLabel->setText("");

    QList<Compressor::CoderTypes>& compressSequence = info.compressSequence;

    // Compress Mode
    if (!compressSequence.empty()) {
        ratioLabel->setText(QString::number(
                static_cast<float>(100) * info.outputSize / info.inputSize, 'f', 2) +
            " %");

        for (QList<Compressor::CoderTypes>::iterator i = compressSequence.begin();
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
    } else { // Decompress Mode
        ratioLabel->setText(QString::number(
                static_cast<float>(100) * info.outputSize / info.inputSize, 'f', 2) +
            " %");
        encodingSequenceColumnLabel->hide();
        encodingSequenceLabel->hide();
    }

    adjustSize();
    setFixedSize(width(), height());
}
