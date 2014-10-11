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

#ifndef COMPRESSSETTINGSPANEL_H
#define COMPRESSSETTINGSPANEL_H

#include "Compressor/compressor.h"

#include <QWidget>

class QSpinBox;
class QComboBox;

class CompressSettingsPanel : public QWidget {
    Q_OBJECT

public:
    CompressSettingsPanel();
    virtual ~CompressSettingsPanel();

public slots:
    void set(unsigned int blockSize, QList<Compressor::CoderTypes> compressSequence);

signals:
    void settingsChanged(unsigned int blockSize, QList<Compressor::CoderTypes> compressSequence);
    void resetToDefaults(void);

private:
    QSpinBox* blockSizeSpinBox;
    QComboBox* encoder1ComboBox;
    QComboBox* encoder2ComboBox;
    QComboBox* encoder3ComboBox;
    QComboBox* encoder4ComboBox;
    QComboBox* encoder5ComboBox;
    QComboBox* encoder6ComboBox;
    QComboBox* encoder7ComboBox;
    QComboBox* encoder8ComboBox;

    void setupWidgetsConnections();

private slots:
    void get();
    void disableEncoders();
};

#endif /* COMPRESSSETTINGSPANEL_H */
