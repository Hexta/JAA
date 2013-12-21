/******************************************************************************
 * Copyright (c) 2011-2013 Artur Molchanov <artur.molchanov@gmail.com>        *
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

#ifndef CONSTS_H
#define	CONSTS_H

#include <stdint.h>
#include <cstddef>

namespace JAA {

const unsigned char ARCHIVER_ID[] = {0x3A, 0x29, 0x4A, 0x41, 0x76, 0x30, 0x31};
const size_t ARCHIVER_ID_SIZE = 7;

namespace CodecID {
const uint64_t RAW_ID = 0x01313076414A293A;
const uint64_t HUFF_ID = 0x02313076414A293A;
const uint64_t RLE_ID = 0x03313076414A293A;
const uint64_t BWT_ID = 0x04313076414A293A;
const uint64_t MTF_ID = 0x05313076414A293A;
}

enum class FileIOResult {
  OK = 0, INPUT_ERROR, OUTPUT_ERROR, FILE_EMPTY, FILE_BROKEN, HEADER_CORRUPTED,
      FILE_END, FILE_TOO_SMALL
};

enum class FileBlockResult {
  OK = 0, BLOCK_OUT_OF_RANGE, BLOCK_ALREADY_RECIEVED, FIRST_RECIEVED_BLOCK,
      ALL_BLOCKS_RECIEVED, FIRST_AND_LAST_RECIEVED_BLOCK
};
} // namespace JAA

#endif	/* CONSTS_H */

