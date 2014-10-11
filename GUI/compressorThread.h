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

#ifndef COMPRESSORTHREAD_H
#define COMPRESSORTHREAD_H

#include "Compressor/compressor.h"
#include "Compressor/FilesTable/filesTable.h"

#include <QThread>
#include <QDir>
#include <QVector>

class QProgressDialog;
class CompressorThread;

class CTCompressorStatus : public CompressorStatus {
public:
    CTCompressorStatus();
    void showProgress(float progress, const QString&, float speed);
    void showInfo(ErrorCode errorCode, const QString& currFileName = "", unsigned int id = 0);
    void setCompressorThread(CompressorThread* comprThread);

private:
    CompressorThread* comprThread;
};

class CompressorThread : public QThread {
    Q_OBJECT

public:
    CompressorThread();
    virtual ~CompressorThread();

    void run();
    void showProgress(float progress, const QString& fileName, float speed);
    void showInfo(CompressorStatus::ErrorCode errorCode, const QString& fileName, unsigned int id);
    void initCompress(const QStringList& iFileNames,
        const QString& destFileName,
        unsigned int blocksize,
        const QDir& compressBaseDir,
        const QList<Compressor::CoderTypes>& compressSequence);
    void initDecompress(const QString& iFileName, bool keepBroken = false);
    void initList(const QString& iFileName);
    void compress();
    void decompress();
    void list();

public slots:
    void stop();

signals:
    void progressChanged(int progress, QString fileName, float speed);
    void info(CTCompressorStatus::ErrorCode error, QString fileName, unsigned int id);
    void statInfo(Compressor::Stat stat);

private:
    QStringList iFileNames;
    QString iFileName;
    QString destFileName;
    unsigned int blocksize;
    QDir compressBaseDir;
    bool keepBroken;
    QList<Compressor::CoderTypes> compressSequence;
    CTCompressorStatus* status;

    enum Mode {
        NONE, COMPRESSING, DECOMPRESSING, LIST
    } runMode;
};

#endif /* COMPRESSORTHREAD_H */
