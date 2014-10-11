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

#include "dataBlock.h"
#include "dataBlockHeader.h"
#include "readerDataBlockHeader.h"

#include <QFile>

#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#define MIN_RAW_BLOCK_SIZE (100000)

using JAA_header_constants::HEADER_SIZE;

struct DataBlock::Private {
    Private() :
        header(new DataBlockHeader),
        dataSize(0),
        data(new dataT(dataSize)),
        outBlock(NULL),
        nBytesToRead(0),
        recoveryMode(false) {
    }

    Private(unsigned int dataSize, uint32_t nBytesToRead) :
        header(new DataBlockHeader),
        dataSize(0),
        data(new dataT(dataSize)),
        outBlock(new dataT(dataSize)),
        nBytesToRead(nBytesToRead),
        recoveryMode(false) {
    }

    Private(DataBlockHeader* header, unsigned char* inData) :
        header(header),
        dataSize(header->getEncodedDataSize()),
        data(new dataT(dataSize)),
        outBlock(NULL),
        nBytesToRead(0),
        recoveryMode(false) {
        data->assign(inData + HEADER_SIZE, inData + HEADER_SIZE + dataSize);
    }

    ~Private() {
        delete data;
        delete header;
        delete outBlock;
    }

    unsigned int calcCRC() {
        return crc32(data->data(), dataSize);
    }

    dataT* getBlock() {
        outBlock->assign(header->getData(), header->getData() + HEADER_SIZE);
        outBlock->insert(outBlock->end(), data->begin(), data->end());

        return outBlock;
    }

    void setBlock(unsigned char* inBlock) {
        unsigned char in_header_data[HEADER_SIZE];
        memcpy(in_header_data, inBlock, HEADER_SIZE);

        header->setData(in_header_data);
        dataSize = header->getEncodedDataSize();
        data->assign(inBlock + HEADER_SIZE, inBlock + HEADER_SIZE + dataSize);
    }

    void setData(unsigned char* inData, unsigned int inDataSize) {
        dataSize = inDataSize;
        data->assign(inData, inData + dataSize);
    }

    void recordCRC() {
        header->setDataCRC(calcCRC());
        header->recordCRC();
    }

    int checkCRC() {
        if (calcCRC() != header->getDataCRC())
            return -1;
        return 0;
    }

    DataBlockHeader* readRAW(QFile& in) {
        uint64_t offset = in.pos();

        data->resize(nBytesToRead);

        dataSize = static_cast<uint32_t>(in.read(reinterpret_cast<char*>(data->data()),
                                             nBytesToRead));

        if (!dataSize)
            return NULL;

        data->resize(dataSize);

        header->initRAW(offset, dataSize);
        recordCRC();

        return header;
    }

    JAA::FileIOResult read(QFile& in) {
        ReaderDataBlockHeader readerHeader;

        switch (readerHeader.read(header, in, recoveryMode)) {
            case JAA::FileIOResult::FILE_END:
                return JAA::FileIOResult::FILE_END;
                break;
            case JAA::FileIOResult::FILE_TOO_SMALL:
                return JAA::FileIOResult::FILE_TOO_SMALL;
                break;
            case JAA::FileIOResult::FILE_BROKEN:
                recoveryMode = true;
                return JAA::FileIOResult::HEADER_CORRUPTED;
                break;
            default:
                ;
        }

        data->clear();

        uint32_t origDataSize = header->getEncodedDataSize();

        data->resize(origDataSize);
        dataSize =
            static_cast<uint32_t>(in.read(reinterpret_cast<char*>(data->data()),
                                      origDataSize));

        if ((dataSize != origDataSize) || (checkCRC())) {
            return JAA::FileIOResult::FILE_BROKEN;
        }

        return JAA::FileIOResult::OK;
    }

    JAA::FileIOResult writeRAW() {
        char* oFileName = header->getFileName();
        QFile fout(QString::fromUtf8(oFileName, static_cast<int>(strlen(oFileName))));

        if (!fout.open(QIODevice::ReadWrite))
            return JAA::FileIOResult::OUTPUT_ERROR;

        fout.seek(header->getOffset());
        fout.write(reinterpret_cast<char*>(data->data()), data->size());
        fout.close();

        return JAA::FileIOResult::OK;
    }

    DataBlockHeader* header;
    uint32_t dataSize;
    dataT* data;
    dataT* outBlock;
    uint32_t nBytesToRead;
    bool recoveryMode;
};

/*
 * TODO:setBlockSize*2 <-- !
 */
DataBlock::DataBlock(unsigned int setBlockSize) :
    d(new Private(setBlockSize * 2, setBlockSize)) {
}

DataBlock::DataBlock() :
    d(new Private) {
    d->data->reserve(MIN_RAW_BLOCK_SIZE);
}

DataBlock::DataBlock(unsigned char* inData) :
    d(new Private(new DataBlockHeader(inData), inData)) {
}

DataBlock::~DataBlock() {
}

DataBlockHeader* DataBlock::readRAW(QFile& in) {
    return d->readRAW(in);
}

JAA::FileIOResult DataBlock::read(QFile& in) {
    return d->read(in);
}

unsigned char* DataBlock::getData() {
    return d->data->data();
}

void DataBlock::setData(unsigned char* inData, unsigned int inDataSize) {
    d->setData(inData, inDataSize);
}

void DataBlock::setData(dataT* inData) {
    d->data->assign(inData->begin(), inData->end());
}

void DataBlock::write(QFile& out) {
    recordCRC();
    getBlock();
    out.write(reinterpret_cast<char*>(d->outBlock->data()), d->outBlock->size());
}

DataBlockHeader* DataBlock::getHeader() {
    return d->header;
}

dataT* DataBlock::getBlock() {
    return d->getBlock();
}

void DataBlock::setBlock(unsigned char* inBlock) {
    d->setBlock(inBlock);
}

int DataBlock::checkCRC() {
    return d->checkCRC();
}

void DataBlock::recordCRC() {
    d->recordCRC();
}

JAA::FileIOResult DataBlock::writeRAW() {
    return d->writeRAW();
}
