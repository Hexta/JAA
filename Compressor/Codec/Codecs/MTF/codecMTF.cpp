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

#include "codecMTF.h"

Codec_MTF::Codec_MTF() { }

Codec_MTF::~Codec_MTF() { }

void
Codec_MTF::decode_MTF(DataBlock* inData) {
  initDecoder(inData);

  buffer.reserve(decodedDataSize);
  buffer.resize(encodedDataSize);

  init_mtf(256);

  for (unsigned int i = 0; i < encodedDataSize; ++i)
    buffer[i] = get_mtf_c(data[i]);

  inData->setBlock(buffer.data());
}

void
Codec_MTF::encode_MTF(DataBlock* inData) {
  initEncoder(inData);

  encodedDataSize = decodedDataSize;

  buffer.reserve(encodedDataSize);
  buffer.resize(decodedDataSize);

  init_mtf(256);

  for (unsigned int i = 0; i < decodedDataSize; ++i)
    buffer[i] = mtf(data[i]);

  inData->setData(buffer.data(), encodedDataSize);

  recordOutHeader(inData->getHeader(), JAA::CodecID::MTF_ID);
}

void
Codec_MTF::init_mtf(int tsize) {
  p =
      head =
      tail = NULL;

  table.resize(tsize + 1);
  /* initialize the list. */
  for (int i = tsize; i-- > 0;) {
    table[i].c = i;
 
    if (i >=1) {
        table[i].next = &table[i - 1];
    }

    if (i < tsize)
    {
        table[i].prev = &table[i + 1];
    }
  }

  table[tsize - 1].prev = NULL;
  table[0].next = NULL;
  head = &table[tsize - 1];
  tail = &table[0];
}
