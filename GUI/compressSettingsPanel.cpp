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

#include "compressSettingsPanel.h"

#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>

CompressSettingsPanel::CompressSettingsPanel() :
    QWidget() {
    QStringList encoderTypes = QStringList() <<
                               "" << "RLE" << "BWT" << "MTF" << "Huffman";

    QLabel* encoder1Label = new QLabel(tr("1 Encoder"));
    QLabel* encoder2Label = new QLabel(tr("2 Encoder"));
    QLabel* encoder3Label = new QLabel(tr("3 Encoder"));
    QLabel* encoder4Label = new QLabel(tr("4 Encoder"));
    QLabel* encoder5Label = new QLabel(tr("5 Encoder"));
    QLabel* encoder6Label = new QLabel(tr("6 Encoder"));
    QLabel* encoder7Label = new QLabel(tr("7 Encoder"));
    QLabel* encoder8Label = new QLabel(tr("8 Encoder"));

    QHBoxLayout* blockSizeHbox = new QHBoxLayout;
    QHBoxLayout* encoder1hbox = new QHBoxLayout;
    QHBoxLayout* encoder2hbox = new QHBoxLayout;
    QHBoxLayout* encoder3hbox = new QHBoxLayout;
    QHBoxLayout* encoder4hbox = new QHBoxLayout;
    QHBoxLayout* encoder5hbox = new QHBoxLayout;
    QHBoxLayout* encoder6hbox = new QHBoxLayout;
    QHBoxLayout* encoder7hbox = new QHBoxLayout;
    QHBoxLayout* encoder8hbox = new QHBoxLayout;

    encoder1ComboBox = new QComboBox;
    encoder2ComboBox = new QComboBox;
    encoder3ComboBox = new QComboBox;
    encoder4ComboBox = new QComboBox;
    encoder5ComboBox = new QComboBox;
    encoder6ComboBox = new QComboBox;
    encoder7ComboBox = new QComboBox;
    encoder8ComboBox = new QComboBox;

    encoder1ComboBox->insertItems(0, encoderTypes);
    encoder2ComboBox->insertItems(0, encoderTypes);
    encoder3ComboBox->insertItems(0, encoderTypes);
    encoder4ComboBox->insertItems(0, encoderTypes);
    encoder5ComboBox->insertItems(0, encoderTypes);
    encoder6ComboBox->insertItems(0, encoderTypes);
    encoder7ComboBox->insertItems(0, encoderTypes);
    encoder8ComboBox->insertItems(0, encoderTypes);

    QLabel* blockSizeLabel = new QLabel(tr("Block Size"));
    blockSizeSpinBox = new QSpinBox;
    blockSizeSpinBox->setRange(10, 10000);
    blockSizeSpinBox->setSingleStep(100);
    blockSizeSpinBox->setSuffix(" kb");
    blockSizeHbox->addWidget(blockSizeLabel);
    blockSizeHbox->addWidget(blockSizeSpinBox);

    encoder1hbox->addWidget(encoder1Label);
    encoder1hbox->addWidget(encoder1ComboBox);

    encoder2hbox->addWidget(encoder2Label);
    encoder2hbox->addWidget(encoder2ComboBox);

    encoder3hbox->addWidget(encoder3Label);
    encoder3hbox->addWidget(encoder3ComboBox);

    encoder4hbox->addWidget(encoder4Label);
    encoder4hbox->addWidget(encoder4ComboBox);

    encoder5hbox->addWidget(encoder5Label);
    encoder5hbox->addWidget(encoder5ComboBox);

    encoder6hbox->addWidget(encoder6Label);
    encoder6hbox->addWidget(encoder6ComboBox);

    encoder7hbox->addWidget(encoder7Label);
    encoder7hbox->addWidget(encoder7ComboBox);

    encoder8hbox->addWidget(encoder8Label);
    encoder8hbox->addWidget(encoder8ComboBox);

    QPushButton* resetEncodersButton = new QPushButton(tr("Disable All Encoders"));
    connect(resetEncodersButton, SIGNAL(clicked()), this, SLOT(disableEncoders()));

    QPushButton* resetToDefaultsButton = new QPushButton(tr("Reset To Defaults"));
    connect(resetToDefaultsButton, SIGNAL(clicked()), this, SIGNAL(resetToDefaults()));

    QGridLayout* grid = new QGridLayout;

    grid->addLayout(blockSizeHbox, 0, 0, Qt::AlignTop);
    grid->addLayout(encoder1hbox, 1, 0, Qt::AlignTop);
    grid->addLayout(encoder2hbox, 2, 0, Qt::AlignTop);
    grid->addLayout(encoder3hbox, 3, 0, Qt::AlignTop);
    grid->addLayout(encoder4hbox, 4, 0, Qt::AlignTop);
    grid->addLayout(encoder5hbox, 5, 0, Qt::AlignTop);
    grid->addLayout(encoder6hbox, 6, 0, Qt::AlignTop);
    grid->addLayout(encoder7hbox, 7, 0, Qt::AlignTop);
    grid->addLayout(encoder8hbox, 8, 0, Qt::AlignTop);
    grid->addWidget(resetEncodersButton, 9, 0, Qt::AlignTop);
    grid->addWidget(resetToDefaultsButton, 10, 0, Qt::AlignTop);

    setupWidgetsConnections();

    setLayout(grid);
}

CompressSettingsPanel::~CompressSettingsPanel() {
}

void CompressSettingsPanel::disableEncoders() {
    encoder1ComboBox->setCurrentIndex(0);
    encoder2ComboBox->setCurrentIndex(0);
    encoder3ComboBox->setCurrentIndex(0);
    encoder4ComboBox->setCurrentIndex(0);
    encoder5ComboBox->setCurrentIndex(0);
    encoder6ComboBox->setCurrentIndex(0);
    encoder7ComboBox->setCurrentIndex(0);
    encoder8ComboBox->setCurrentIndex(0);
}

void CompressSettingsPanel::set(unsigned int blockSize, QList<Compressor::CoderTypes> compressSequence) {
    this->blockSizeSpinBox->setValue(blockSize);

    encoder1ComboBox->setCurrentIndex(compressSequence[0]);
    encoder2ComboBox->setCurrentIndex(compressSequence[1]);
    encoder3ComboBox->setCurrentIndex(compressSequence[2]);
    encoder4ComboBox->setCurrentIndex(compressSequence[3]);
    encoder5ComboBox->setCurrentIndex(compressSequence[4]);
    encoder6ComboBox->setCurrentIndex(compressSequence[5]);
    encoder7ComboBox->setCurrentIndex(compressSequence[6]);
    encoder8ComboBox->setCurrentIndex(compressSequence[7]);
}

void CompressSettingsPanel::setupWidgetsConnections() {
    connect(blockSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(get()));

    connect(encoder1ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(get()));
    connect(encoder2ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(get()));
    connect(encoder3ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(get()));
    connect(encoder4ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(get()));
    connect(encoder5ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(get()));
    connect(encoder6ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(get()));
    connect(encoder7ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(get()));
    connect(encoder8ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(get()));
}

void CompressSettingsPanel::get() {
    QList<Compressor::CoderTypes> compressSequence;
    compressSequence << static_cast<Compressor::CoderTypes>(encoder1ComboBox->currentIndex()) <<
        static_cast<Compressor::CoderTypes>(encoder2ComboBox->currentIndex()) <<
        static_cast<Compressor::CoderTypes>(encoder3ComboBox->currentIndex()) <<
        static_cast<Compressor::CoderTypes>(encoder4ComboBox->currentIndex()) <<
        static_cast<Compressor::CoderTypes>(encoder5ComboBox->currentIndex()) <<
        static_cast<Compressor::CoderTypes>(encoder6ComboBox->currentIndex()) <<
        static_cast<Compressor::CoderTypes>(encoder7ComboBox->currentIndex()) <<
        static_cast<Compressor::CoderTypes>(encoder8ComboBox->currentIndex());

    unsigned int blockSize = blockSizeSpinBox->value();

    emit settingsChanged(blockSize, compressSequence);
}
