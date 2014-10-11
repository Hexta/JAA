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

#include "Compressor/Codec/codec.h"
#include "FilesTable/filesTable.h"
#include "DataBlock/dataBlockHeader.h"

#include <QString>

#include <algorithm>
#include <ctime>
#include <list>

class CompressorStatus {
public:
    CompressorStatus() :
        runStatus(RUN) {
    };

    enum RunStatus {
        RUN, STOP
    };

    enum ErrorCode {
        SUCCESS,
        INPUT_FILE_OPEN_ERROR,
        OUTPUT_FILE_WRITE_ERROR,
        INPUT_FILE_CORRUPTED,
        INPUT_FILE_UNCORRUPTED,
        DECOMPRESS_FAIL,
        PROCEED,
        CANCELLED
    };

    void setRunStatus(RunStatus status) {
        runStatus = status;
    }

    RunStatus getRunStatus() const {
        return runStatus;
    }

    virtual void showProgress(float progress, const QString& fileName, float speed);
    virtual void showInfo(ErrorCode errorCode, const QString& fileName, unsigned int id);

private:
    RunStatus runStatus;
};

class Compressor {
public:
    Compressor(CompressorStatus* status);
    virtual ~Compressor();

    struct Stat {
        off_t decodedSize;
        off_t encodedSize;
        float speed; // enc-/dec- speed (mb/s)
        vector<string> brokenFilesNames;
    };

    enum CoderTypes {
        NONE = 0, RLE, BWT, MTF, HUFFMAN
    };

    /**
     * Compress multiply files
     * @param iFileNames	array with input file names
     * @param iFilesCount	number of input files
     * @param oFileName		output file name
     * @param blocksize		block size
     * @return				error code
     */
    CompressorStatus::ErrorCode compress(const vector<QString>& iFileNames,
        const QString& oFileName,
        unsigned int blocksize,
        const list<CoderTypes>& compressSequence);
    /**
     * Decompress archive
     * @param iFileName		archive filename
     * @param keepBroken	keep broken files
     * @return				error code
     */
    CompressorStatus::ErrorCode decompress(const QString& iFileName, bool keepBroken = false);
    /**
     * Get statistical info
     * @param stat	point to info structure
     */
    void getStat(Stat* stat);

    /**
     * List archive contents
     * @param iFileName	archive filename
     * @param contents	point to output vector with archive contents
     * @return			error code
     */
    CompressorStatus::ErrorCode listArchiveContents(const QString& iFileName,
        vector<FilesTable::FileInfo>* const contents = NULL);

private:
    Codec codec;
    DataBlock* block;
    CompressorStatus* status;
    off_t currReadBytesCount;
    off_t decodedDataSize;
    off_t encodedDataSize;
    uint32_t totalProcessingTime;
    unsigned int sourceDataSize;
    FilesTable blocksTable;
    CompressorStatus::ErrorCode error;
    vector<FilesTable::FileInfo> contents;
    list<CoderTypes> defaultCompressSequence;

    void showEncodingProgress(const QString& currFileName, float speed);
    void showDecodingProgress(const char* currFileName, float speed);
    void showInfo(CompressorStatus::ErrorCode errorCode, const QString& currFileName = "", unsigned int id =
            0);
    void showInfo(CompressorStatus::ErrorCode errorCode, const char* currFileName, unsigned int id = 0);

    void compress(const list<CoderTypes>& compressSequence);
    bool decompress();

    bool createEmptyFile(const char* fileName);
    void removeBrokenFiles();
    float speed(unsigned int nBytes, clock_t elapsedTime);
};

class Encoder {
public:
    Encoder(DataBlock* block, Codec* codec) {
        this->block = block;
        this->codec = codec;
    }

    virtual ~Encoder() {
    }

    void operator()(Compressor::CoderTypes coderType) {
        switch (coderType) {
            case Compressor::BWT:
                codec->encode_BWT(block);
                break;
            case Compressor::RLE:
                codec->encode_RLE(block);
                break;
            case Compressor::MTF:
                codec->encode_MTF(block);
                break;
            case Compressor::HUFFMAN:
                codec->encode_HUFF(block);
                break;
            default:
                break;
        }
    }

private:
    DataBlock* block;
    Codec* codec;
};

void inline Compressor::compress(const list<CoderTypes>& compressSequence) {
    Encoder encoder(block, &codec);
    std::for_each(compressSequence.begin(), compressSequence.end(), encoder);
}

bool inline Compressor::decompress() {
    uint64_t id;
    while ((id = block->getHeader()->getId()) != JAA::CodecID::RAW_ID) {
        switch (id) {
            case JAA::CodecID::HUFF_ID:
                codec.decode_HUFF(block);
                break;
            case JAA::CodecID::RLE_ID:
                codec.decode_RLE(block);
                break;
            case JAA::CodecID::BWT_ID:
                codec.decode_BWT(block);
                break;
            case JAA::CodecID::MTF_ID:
                codec.decode_MTF(block);
                break;
            default:
                return true;
        }
    }
    return false;
}

void inline Compressor::showDecodingProgress(const char* currFileName, float speed) {
    if (status)
        status->showProgress(
            encodedDataSize ? static_cast<float>(currReadBytesCount) / encodedDataSize : 0,
            QString::fromUtf8(currFileName, static_cast<int>(strlen(currFileName))),
            speed);
}

void inline Compressor::showEncodingProgress(const QString& currFileName, const float speed) {
    if (status)
        status->showProgress(
            decodedDataSize ? static_cast<float>(currReadBytesCount) / decodedDataSize : 0,
            currFileName, speed);
}

float inline Compressor::speed(unsigned int nBytes, clock_t elapsedTime) {
    return elapsedTime ? nBytes / (static_cast<double>(elapsedTime) / CLOCKS_PER_SEC) : 0;
}

void inline Compressor::showInfo(CompressorStatus::ErrorCode errorCode,
    const QString& currFileName,
    unsigned int id) {
    if (status) status->showInfo(errorCode, currFileName, id);
}

void inline Compressor::showInfo(CompressorStatus::ErrorCode errorCode,
    const char* currFileName,
    unsigned int id) {
    QString fileName;
    if (!currFileName)
        fileName.clear();
    else
        fileName = QString::fromUtf8(currFileName,
            static_cast<int>(strlen(currFileName)));
    if (status) status->showInfo(errorCode, fileName, id);
}
