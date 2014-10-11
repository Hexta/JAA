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

#pragma once

#include "compressorThread.h"

#include <QMainWindow>

namespace Ui {
class face;
}

class Face : public QMainWindow {
    Q_OBJECT

public:
    Face();
    virtual ~Face();

public slots:
    void about();
    void selectFilesToCompress();
    void selectFileToDecompress();
    void compress();
    void decompress();
    void listArchiveContents();
    void displayCompressStatus(int progress, QString fileName, float speed);
    void displayDecompressStatus(int progress, QString fileName, float speed);
    void displayListStatus(int progress, QString fileName, float speed);
    void showInfo(CTCompressorStatus::ErrorCode error, QString fileName);
    void showCompressStatInfo(Compressor::Stat stat);
    void showDecompressStatInfo(Compressor::Stat stat);
    void setCompressSettings(unsigned int blockSize, QList<Compressor::CoderTypes> compressSequence);
    void setDecompressSettings(bool keepBrokenFiles);

private:
    struct Private;

    std::unique_ptr<Private> d;

    void createActions();
    void createToolBars();
    void createMenus();
    void setupWidgetsConnections();
    void activateCompressMode();
    void activateDecompressMode();

private slots:
    void initSettings();
};
