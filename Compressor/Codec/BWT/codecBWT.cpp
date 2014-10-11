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

#include "codecBWT.h"

Codec_BWT::Codec_BWT() {
}

Codec_BWT::~Codec_BWT() {
}

void Codec_BWT::encode_BWT(DataBlock* inData) {
    initEncoder(inData);

    encodedDataSize = decodedDataSize;

    buffer.reserve(encodedDataSize);

    SA.reserve(decodedDataSize);

    codecParams = divbwt(data, buffer.data(), SA.data(), decodedDataSize);

    inData->setData(buffer.data(), encodedDataSize);

    recordOutHeader(inData->getHeader(), JAA::CodecID::BWT_ID);
}

void Codec_BWT::decode_BWT(DataBlock* inData) {
    initDecoder(inData);

    SA.reserve(encodedDataSize);
    inverse_bw_transform(data, data, SA.data(), encodedDataSize, codecParams);

    inData->setBlock(data);
}
