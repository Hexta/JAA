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

#include "codecRLE.h"

#include <climits>

Codec_RLE::Codec_RLE() { }

Codec_RLE::~Codec_RLE() { }

void
Codec_RLE::decode_RLE(DataBlock* inData) {
  initDecoder(inData);

  buffer.reserve(decodedDataSize);
  buffer.clear();

  int prevChar = 0xFFFFFF;

  unsigned char count;

  unsigned int i = 0;
  while (i < encodedDataSize) {
    int currChar = data[i++];

    buffer.push_back(currChar);

    /* check for run */
    if (currChar == prevChar) {
      count = data[i++];
      while (count-- > 0) {
        buffer.push_back(currChar);
      }

      prevChar = 0xFFFFFF;
    } else {
      /* no run */
      prevChar = currChar;
    }
  }

  inData->setBlock(buffer.data());
}

void
Codec_RLE::encode_RLE(DataBlock* inData) {
  initEncoder(inData);

  /*
   * TODO:
   * RLE overhead?!
   */

  encodedDataSize = decodedDataSize * 2; //<---

  buffer.reserve(encodedDataSize);
  buffer.clear();

  int currChar = EOF, prevChar = EOF; /* current and previous characters */
  unsigned char count;
  count = 0;

  unsigned int index = 0;

  while (index != decodedDataSize) {
    currChar = data[index++];
    buffer.push_back(currChar);

    /* check for run */
    if (currChar == prevChar) {
      /* we have a run.  count run length */
      count = 0;

      while (index != decodedDataSize) {
        currChar = data[index++];
        if (currChar == prevChar) {
          ++count;

          if (count == UCHAR_MAX) {
            /* count is as long as it can get */
            buffer.push_back(count);

            /* force next char to be different */
            prevChar = EOF;
            break;
          }
        } else {
          /* run ended */
          buffer.push_back(count);
          buffer.push_back(currChar);

          prevChar = currChar;
          break;
        }
        if (index == decodedDataSize) {
          buffer.push_back(count);
          break;
        }
      }
    } else {
      /* no run */
      prevChar = currChar;
    }
  }
  encodedDataSize = buffer.size();
  inData->setData(buffer.data(), buffer.size());

  recordOutHeader(inData->getHeader(), JAA::CodecID::RLE_ID);
}
