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

#include "compressor.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>

#include <QFile>

using JAA::FileIOResult;
using JAA::FileBlockResult;

void CompressorStatus::showProgress(float, const QString&, float) {
}

void CompressorStatus::showInfo(ErrorCode, const QString&, unsigned int) {
}

Compressor::Compressor(CompressorStatus* status) :
    codec(),
    block(NULL),
    status(status),
    currReadBytesCount(0),
    decodedDataSize(0),
    encodedDataSize(0),
    totalProcessingTime(0),
    sourceDataSize(0),
    blocksTable(),
    defaultCompressSequence() {
    defaultCompressSequence.push_back(RLE);
    defaultCompressSequence.push_back(BWT);
    defaultCompressSequence.push_back(MTF);
    defaultCompressSequence.push_back(RLE);
    defaultCompressSequence.push_back(BWT);
    defaultCompressSequence.push_back(RLE);
    defaultCompressSequence.push_back(HUFFMAN);
}

Compressor::~Compressor() {
}

/*
 * Encoding
 */

bool Compressor::createEmptyFile(const char* fileName) {
    QFile fout(QString::fromUtf8(fileName, static_cast<int>(strlen(fileName))));
    if (!fout.open(QIODevice::Truncate | QIODevice::WriteOnly)) return false;
    fout.close();
    return true;
}

CompressorStatus::ErrorCode Compressor::compress(const vector<QString>& iFileNames,
    const QString& oFileName,
    unsigned int blocksize,
    const list<CoderTypes>& compressSequence) {
    totalProcessingTime = 0;
    decodedDataSize = 0;
    currReadBytesCount = 0;
    encodedDataSize = 0;
    error = CompressorStatus::SUCCESS;

    vector<int> proceedFiles;

    int fileId = 0;

    for (const auto& iFileName : iFileNames) {
        QFile fin(iFileName);

        if (!fin.open(QIODevice::ReadOnly)) {
            showInfo(CompressorStatus::INPUT_FILE_OPEN_ERROR, iFileName, fileId + 1);
            error = CompressorStatus::INPUT_FILE_OPEN_ERROR;
            continue;
        }
        fin.close();

        proceedFiles.push_back(fileId);
        decodedDataSize += fin.size();

        ++fileId;
    }

    block = new DataBlock(blocksize);
    DataBlockHeader* header = block->getHeader();

    QFile fout(oFileName);
    if (!fout.open(QIODevice::WriteOnly)) {
        showInfo(CompressorStatus::OUTPUT_FILE_WRITE_ERROR);
        return error = CompressorStatus::OUTPUT_FILE_WRITE_ERROR;
    }

    bool stop = false;
    for (auto i = proceedFiles.begin(); i != proceedFiles.end(); ++i) {
        showInfo(CompressorStatus::PROCEED, iFileNames[*i], *i + 1);

        QFile fin(iFileNames[*i]);
        if (!fin.open(QIODevice::ReadOnly)) {
            fout.close();
            showInfo(CompressorStatus::INPUT_FILE_OPEN_ERROR, iFileNames[*i], *i + 1);
            error = CompressorStatus::INPUT_FILE_OPEN_ERROR;
            continue;
        }

        uint32_t partsCount = ceil(static_cast<float>(fin.size()) / blocksize);
        uint32_t part = 0;

        while (1) {
            if (status) {
                if (status->getRunStatus() == CompressorStatus::STOP) {
                    stop = true;
                    break;
                }
            }

            // compress current file
            if (!block->readRAW(fin)) break;

            sourceDataSize = header->getDecodedDataSize();
            currReadBytesCount += sourceDataSize;

            header->setFileName(iFileNames[*i].toUtf8().constData());
            header->setPart(part++);
            header->setPartsCount(partsCount);

            clock_t startTime = clock();

            compress(compressSequence);

            clock_t stoptTime = clock();
            totalProcessingTime += stoptTime - startTime;

            header->setFileName(iFileNames[*i].toUtf8().constData());
            encodedDataSize += header->getEncodedDataSize();
            header->setRAWDataSize(sourceDataSize);
            header->setPart(part - 1);
            header->setPartsCount(partsCount);
            block->write(fout);

            showEncodingProgress(iFileNames[*i],
                speed(sourceDataSize, stoptTime - startTime));
        }

        fin.close();

        if (!stop)
            showInfo(CompressorStatus::SUCCESS, iFileNames[*i], *i + 1);
        else {
            do {
                showInfo(CompressorStatus::CANCELLED, iFileNames[*i], *i + 1);
            } while (++i != proceedFiles.end());
            break;
        }
    }

    delete block;
    return error;
}

/*
 * Decoding
 */

CompressorStatus::ErrorCode Compressor::decompress(const QString& iFileName, bool keepBroken) {
    blocksTable.clean();
    totalProcessingTime = 0;
    decodedDataSize = 0;
    currReadBytesCount = 0;
    encodedDataSize = 0;
    unsigned int nextId = 1;
    error = CompressorStatus::SUCCESS;

    QFile fin(iFileName);
    if (!fin.open(QIODevice::ReadOnly)) {
        showInfo(CompressorStatus::INPUT_FILE_OPEN_ERROR);
        return error = CompressorStatus::INPUT_FILE_OPEN_ERROR;
    }

    block = new DataBlock();
    DataBlockHeader* header = block->getHeader();

    encodedDataSize = fin.size();

    bool stop = false;
    while (!stop) {
        switch (block->read(fin)) {
            case FileIOResult::FILE_END:
                stop = true;
                continue;

            case FileIOResult::FILE_BROKEN: {
                error = CompressorStatus::INPUT_FILE_CORRUPTED;
                unsigned id = blocksTable.getId(header);
                id = id ? id : nextId++;
                showInfo(CompressorStatus::INPUT_FILE_CORRUPTED, header->getFileName(),
                    id);
                continue;
            }
            case FileIOResult::HEADER_CORRUPTED: {
                error = CompressorStatus::INPUT_FILE_CORRUPTED;
                showInfo(CompressorStatus::INPUT_FILE_CORRUPTED);
                continue;
            }
            case FileIOResult::FILE_TOO_SMALL: {
                if (keepBroken == false) removeBrokenFiles();
                showInfo(CompressorStatus::INPUT_FILE_CORRUPTED);
                return error = CompressorStatus::INPUT_FILE_CORRUPTED;
            }
            default:
                break;
        }

        currReadBytesCount = fin.pos();

        clock_t startTime = clock();

        decompress();

        clock_t stoptTime = clock();
        totalProcessingTime += stoptTime - startTime;

        decodedDataSize += header->getDecodedDataSize();
        showDecodingProgress(header->getFileName(),
            speed(header->getEncodedDataSize(), stoptTime - startTime));

        if (block->checkCRC()) {
            delete block;
            fin.close();
            showInfo(CompressorStatus::DECOMPRESS_FAIL);
            return error = CompressorStatus::DECOMPRESS_FAIL;
        }

        switch (blocksTable.add(header, nextId)) {
            case FileBlockResult::FIRST_AND_LAST_RECIEVED_BLOCK:
                blocksTable.remove(header);
                if (!createEmptyFile(header->getFileName())) {
                    showInfo(CompressorStatus::OUTPUT_FILE_WRITE_ERROR);
                    return error = CompressorStatus::OUTPUT_FILE_WRITE_ERROR;
                }
                showInfo(CompressorStatus::SUCCESS, header->getFileName(), nextId++);
                break;

            case FileBlockResult::FIRST_RECIEVED_BLOCK:
                createEmptyFile(header->getFileName());
                showInfo(CompressorStatus::PROCEED, header->getFileName(), nextId++);
                break;

            case FileBlockResult::ALL_BLOCKS_RECIEVED:
                showInfo(CompressorStatus::SUCCESS, header->getFileName(),
                blocksTable.getId(header));
                blocksTable.remove(header);
                break;

            case FileBlockResult::BLOCK_OUT_OF_RANGE:
            case FileBlockResult::BLOCK_ALREADY_RECIEVED:
                showInfo(CompressorStatus::INPUT_FILE_CORRUPTED);
                return error = CompressorStatus::INPUT_FILE_CORRUPTED;
                break;

            default:
                break;
        }

        if (block->writeRAW() != FileIOResult::OK) {
            delete block;
            fin.close();
            showInfo(CompressorStatus::OUTPUT_FILE_WRITE_ERROR);
            return error = CompressorStatus::OUTPUT_FILE_WRITE_ERROR;
        }

        if (status->getRunStatus() == CompressorStatus::STOP) {
            stop = true;
            showInfo(CompressorStatus::CANCELLED, header->getFileName(),
                blocksTable.getId(header));
        }
    }

    // Check for broken files

    auto& brokenFilesNames = blocksTable.getNonCompleteFilesNames();

    if (!brokenFilesNames.empty())
        for (auto& brokenFileName : brokenFilesNames) {
            showInfo(CompressorStatus::INPUT_FILE_CORRUPTED, brokenFileName.c_str(),
                blocksTable.getId(brokenFileName));
            if (keepBroken == false) removeBrokenFiles();
        }

    fin.close();
    delete block;
    return error;
}

void Compressor::getStat(Stat* stat) {
    auto& nonCompleteFilesNames =
        blocksTable.getNonCompleteFilesNames();

    if (!nonCompleteFilesNames.empty()) stat->brokenFilesNames = nonCompleteFilesNames;
    stat->decodedSize = decodedDataSize;
    stat->encodedSize = encodedDataSize;
    stat->speed = speed(decodedDataSize, totalProcessingTime);
}

void Compressor::removeBrokenFiles() {
    auto& nonCompleteFilesNames =
        blocksTable.getNonCompleteFilesNames();

    if (nonCompleteFilesNames.empty()) return;

    for (auto& fileName : nonCompleteFilesNames)
        QFile::remove(QString::fromUtf8(fileName.c_str(),
                static_cast<int>(strlen(fileName.c_str()))));
}

CompressorStatus::ErrorCode Compressor::listArchiveContents(const QString& iFileName,
    vector<FilesTable::FileInfo>* const contents /*=NULL*/) {
    blocksTable.clean();
    unsigned int nextId = 1;

    if (contents) {
        contents->clear();
        contents->reserve(1000);
    }

    totalProcessingTime = 0;
    decodedDataSize = 0;
    currReadBytesCount = 0;
    encodedDataSize = 0;
    error = CompressorStatus::SUCCESS;

    QFile fin(iFileName);
    if (!fin.open(QIODevice::ReadOnly)) {
        error = CompressorStatus::INPUT_FILE_OPEN_ERROR;
        showInfo(error);
        return error;
    }

    block = new DataBlock();
    DataBlockHeader* header = block->getHeader();
    encodedDataSize = fin.size();

    bool stop = false;
    while (!stop) {
        if (status) {
            if (status->getRunStatus() == CompressorStatus::STOP) {
                stop = true;
            }
        }

        clock_t startTime = clock();
        switch (block->read(fin)) {
            case FileIOResult::FILE_END:
                stop = true;
                continue;

            case FileIOResult::FILE_BROKEN: {
                error = CompressorStatus::INPUT_FILE_CORRUPTED;

                unsigned id = blocksTable.getId(header);
                id = id ? id : nextId++;
                showInfo(error, header->getFileName(), id);

                if (contents) {
                    // Add to archive contents broken 1-block-size file`s info
                    FilesTable::FileInfo fileInfo;
                    fileInfo.corrupted = true;
                    fileInfo.fileName = header->getFileName();
                    contents->push_back(fileInfo);
                }
                continue;
            }

            case FileIOResult::HEADER_CORRUPTED: {
                error = CompressorStatus::INPUT_FILE_CORRUPTED;
                showInfo(error);
                continue;
            }

            case FileIOResult::FILE_TOO_SMALL: {
                error = CompressorStatus::INPUT_FILE_CORRUPTED;
                showInfo(error);
                delete block;
                return error;
            }

            default:
                break;
        }

        currReadBytesCount += header->getEncodedDataSize() +
                              JAA_header_constants::HEADER_SIZE;

        clock_t stoptTime = clock();
        totalProcessingTime += stoptTime - startTime;

        showDecodingProgress(header->getFileName(),
            speed(header->getEncodedDataSize(), stoptTime - startTime));

        switch (blocksTable.add(header, nextId)) {
            case FileBlockResult::FIRST_AND_LAST_RECIEVED_BLOCK:
                blocksTable.remove(header);
                showInfo(CompressorStatus::INPUT_FILE_UNCORRUPTED,
                header->getFileName(), nextId++);
                break;

            case FileBlockResult::FIRST_RECIEVED_BLOCK:
                showInfo(CompressorStatus::PROCEED, header->getFileName(), nextId++);
                break;

            case FileBlockResult::ALL_BLOCKS_RECIEVED:
                showInfo(CompressorStatus::INPUT_FILE_UNCORRUPTED,
                header->getFileName(), blocksTable.getId(header));
                blocksTable.remove(header);
                break;

            case FileBlockResult::BLOCK_OUT_OF_RANGE:
            case FileBlockResult::BLOCK_ALREADY_RECIEVED:
                error = CompressorStatus::INPUT_FILE_CORRUPTED;
                showInfo(error);
                delete block;
                return error;
                break;

            default:
                break;
        }
    }

    fin.close();
    delete block;

    auto& brokenFilesNames = blocksTable.getNonCompleteFilesNames();

    if (!brokenFilesNames.empty())
        for (auto& i : brokenFilesNames) {
            showInfo(CompressorStatus::INPUT_FILE_CORRUPTED, i.c_str(),
                blocksTable.getId(i));
        }

    if (contents) {
        auto& partialArchiveContents =
            blocksTable.getArchiveContent();
        contents->insert(contents->end(), partialArchiveContents.begin(),
            partialArchiveContents.end());
    }

    return error;
}
