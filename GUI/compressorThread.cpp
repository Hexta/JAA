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

#include "compressorThread.h"

CompressorThread::CompressorThread() {
    runMode = NONE;
}

CompressorThread::~CompressorThread() {
}

void CompressorThread::showProgress(float progress, const QString& fileName, float speed) {
    emit progressChanged(progress * 100, fileName, speed);
}

void CompressorThread::compress() {
    bool fail;

    status = new CTCompressorStatus;
    status->setCompressorThread(this);
    Compressor compressor(status);

    vector<QString> relIFileNames;

    for (auto& filename : iFileNames)
        relIFileNames.push_back(compressBaseDir.relativeFilePath(filename));

    auto sequence = compressSequence.toStdList();
    switch (compressor.compress(relIFileNames, destFileName, blocksize, sequence)) {
        case CompressorStatus::OUTPUT_FILE_WRITE_ERROR:
            fail = true;
            break;
        default:
            fail = false;
            break;
    }

    Compressor::Stat stat;
    compressor.getStat(&stat);

    if (!fail) emit statInfo(stat);

    delete status;
}

void CompressorThread::decompress() {
    bool fail;

    status = new CTCompressorStatus;
    status->setCompressorThread(this);
    Compressor compressor(status);

    switch (compressor.decompress(iFileName, keepBroken)) {
        case CompressorStatus::OUTPUT_FILE_WRITE_ERROR:
        case CompressorStatus::INPUT_FILE_OPEN_ERROR:
            fail = true;
            break;
        default:
            fail = false;
            break;
    }

    Compressor::Stat stat;
    compressor.getStat(&stat);
    if (!fail) emit statInfo(stat);

    delete status;
}

void CompressorThread::initCompress(const QStringList& iFileNames,
    const QString& destFileName,
    unsigned int blocksize,
    const QDir& compressBaseDir,
    const QList<Compressor::CoderTypes>& compressSequence) {
    this->iFileNames = iFileNames;
    this->destFileName = destFileName;
    this->blocksize = blocksize;
    this->compressBaseDir = compressBaseDir;
    this->compressSequence = compressSequence;

    runMode = COMPRESSING;
}

void CompressorThread::initDecompress(const QString& iFileName, bool keepBroken) {
    this->iFileName = iFileName;
    this->keepBroken = keepBroken;

    runMode = DECOMPRESSING;
}

void CompressorThread::initList(const QString& iFileName) {
    this->iFileName = iFileName;

    runMode = LIST;
}

void CompressorThread::list() {
    CTCompressorStatus status;
    status.setCompressorThread(this);
    Compressor compressor(&status);

    compressor.listArchiveContents(iFileName);
}

void CompressorThread::run() {
    switch (runMode) {
        case COMPRESSING:
            compress();
            break;
        case DECOMPRESSING:
            decompress();
            break;
        case LIST:
            list();
            break;
        default:
            break;
    }
}

void CompressorThread::showInfo(CompressorStatus::ErrorCode errorCode,
    const QString& fileName,
    unsigned int id) {
    emit info(errorCode, fileName, id);
}

void CompressorThread::stop() {
    status->setRunStatus(CompressorStatus::STOP);
}

/*
 * CompressorThreadCompressorStatus
 */

CTCompressorStatus::CTCompressorStatus() : comprThread(NULL) {
}

void CTCompressorStatus::setCompressorThread(CompressorThread* comprThread) {
    this->comprThread = comprThread;
}

void CTCompressorStatus::showProgress(float progress, const QString& fileName, float speed) {
    comprThread->showProgress(progress, fileName, speed);
}

void CTCompressorStatus::showInfo(ErrorCode errorCode, const QString& fileName, unsigned int id) {
    comprThread->showInfo(errorCode, fileName, id);
}
