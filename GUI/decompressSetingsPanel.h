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

#ifndef DECOMPRESSSETTINGSPANEL_H
#define DECOMPRESSSETTINGSPANEL_H

#include "Compressor/compressor.h"

#include <QWidget>

class QCheckBox;

class DecompressSettingsPanel : public QWidget {
    Q_OBJECT

public:
    DecompressSettingsPanel();
    virtual ~DecompressSettingsPanel();

public slots:
    void set(bool keepBroken);

signals:
    void settingsChanged(bool keepBroken);
    void resetToDefaults(void);

private:
    QCheckBox* keepBrokenFilesCheckbox;

    void setupWidgetsConnections();

private slots:
    void get();
};

#endif /* DECOMPRESSSETTINGSPANEL_H */
