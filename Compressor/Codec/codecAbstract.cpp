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

#include "codecAbstract.h"

#include "Compressor/DataBlock/dataBlock.h"
#include "Compressor/DataBlock/dataBlockHeader.h"

Codec_abstract::Codec_abstract() : data(0), decodedDataSize(0),
    encodedDataSize(0), codecParams(0) { }

Codec_abstract::~Codec_abstract() { }

void
Codec_abstract::initDecoder(DataBlock * in_block) {
  DataBlockHeader *header = in_block->getHeader();

  data = in_block->getData();
  encodedDataSize = header->getEncodedDataSize();
  decodedDataSize = header->getDecodedDataSize();
  codecParams = header->getCodecParams();
}

void
Codec_abstract::initEncoder(DataBlock * in_block) {
  dataT * vect = in_block->getBlock();
  data = vect->data();
  decodedDataSize = static_cast<unsigned int> (vect->size());
}

void
Codec_abstract::recordOutHeader(DataBlockHeader *outHeader, uint64_t id) {
  outHeader->clean();
  outHeader->setId(id);
  outHeader->setDecodedDataSize(decodedDataSize);
  outHeader->setEncodedDataSize(encodedDataSize);
  outHeader->setCodecParams(codecParams);
}
