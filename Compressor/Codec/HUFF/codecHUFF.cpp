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

#include "codecHUFF.h"
#include "shclib.h"

Codec_HUFF::Codec_HUFF() {
}

Codec_HUFF::~Codec_HUFF() {
}

void Codec_HUFF::decode_HUFF(DataBlock* inData) {
    initDecoder(inData);

    buffer.reserve(decodedDataSize);

    sh_DecodeBlock(data, buffer.data(), encodedDataSize);

    inData->setBlock(buffer.data());
}

void Codec_HUFF::encode_HUFF(DataBlock* inData) {
    initEncoder(inData);

    buffer.reserve(decodedDataSize + 256);

    encodedDataSize = sh_EncodeBlock(data, buffer.data(), decodedDataSize);

    inData->setData(buffer.data(), encodedDataSize);
    recordOutHeader(inData->getHeader(), JAA::CodecID::HUFF_ID);
}
