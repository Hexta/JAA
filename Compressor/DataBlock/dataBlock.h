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

#include "Compressor/private/consts.h"

#include <vector>
#include <memory>

typedef std::vector<unsigned char> dataT;

class QFile;
class DataBlockHeader;

class DataBlock {
private:
    DataBlock(const DataBlock&);
    void operator=(const DataBlock&);

public:
    DataBlock();
    DataBlock(uint32_t block_size);
    DataBlock(unsigned char* inData);
    virtual ~DataBlock();

    /*read-write*/
    DataBlockHeader* readRAW(QFile& in);
    JAA::FileIOResult read(QFile& in);
    JAA::FileIOResult writeRAW();
    void write(QFile& out);

    /*data get*/
    DataBlockHeader* getHeader();
    unsigned char* getData();
    void setData(unsigned char* inData, uint32_t inDataSize);
    void setData(dataT* inData);
    dataT* getBlock();
    void setBlock(unsigned char* inBlock);

    /*Integrity check*/
    int checkCRC();
    void recordCRC();

private:
    struct Private;
    std::unique_ptr<Private> d;
};
