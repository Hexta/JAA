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

#include "readerDataBlockHeader.h"
#include  "dataBlockHeader.h"

#include <QFile>

#include <algorithm>

#define BUFFER_SIZE (100000)

ReaderDataBlockHeader::ReaderDataBlockHeader() {
}

ReaderDataBlockHeader::~ReaderDataBlockHeader() {
}

using JAA_header_constants::HEADER_SIZE;

JAA::FileIOResult ReaderDataBlockHeader::read(DataBlockHeader* outHeader, QFile& in, bool recoverMode) {
    if (recoverMode) {
        if (find(outHeader, in)) {
            return JAA::FileIOResult::FILE_END;
        }
    } else {
        unsigned char in_header_data[HEADER_SIZE];
        unsigned int receivedBytesCount = in.read(reinterpret_cast<char*>(in_header_data),
            HEADER_SIZE);

        if (receivedBytesCount == 0)
            return JAA::FileIOResult::FILE_END;

        else if (receivedBytesCount < HEADER_SIZE)
            return JAA::FileIOResult::FILE_TOO_SMALL;

        outHeader->setData(in_header_data);

        if (outHeader->checkCRC())
            return JAA::FileIOResult::FILE_BROKEN;
    }

    return JAA::FileIOResult::OK;
}

bool ReaderDataBlockHeader::find(DataBlockHeader* outHeader, QFile& fin) {
    unsigned char buffer[BUFFER_SIZE];

    unsigned int nReadBytes;

    while ((nReadBytes = fin.read(reinterpret_cast<char*>(buffer), BUFFER_SIZE)) >
           HEADER_SIZE) {
        unsigned char* findPos =
            std::search(buffer, buffer + nReadBytes + 1, JAA::ARCHIVER_ID,
                JAA::ARCHIVER_ID + JAA::ARCHIVER_ID_SIZE);

        if (findPos == buffer + nReadBytes + 1) {
            fin.seek(-(std::streamoff)(HEADER_SIZE - 1) + fin.pos());
        } else {
            // found at findPos

            if ((BUFFER_SIZE - (findPos - buffer)) > HEADER_SIZE) {
                // enough space in buffer

                outHeader->setData(findPos);

                if (!outHeader->checkCRC()) {
                    // valid CRC
                    fin.seek(-(std::streamoff)(nReadBytes - (findPos - buffer) - HEADER_SIZE) + fin.pos());
                    return false;
                } else {
                    // not valid CRC may be not header?
                    fin.seek(-static_cast<std::streamoff>(nReadBytes - (findPos - buffer) - 2) + fin.pos());
                    // try again with offset
                }
            } else {
                // not enough space
                fin.seek(-(nReadBytes - (findPos - buffer) - 1) + fin.pos());
            }
        }
    }

    return true;
}
