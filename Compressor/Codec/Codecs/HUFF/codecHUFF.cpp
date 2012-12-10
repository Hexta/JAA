/* 
 * File:   codec_HUFF.cpp
 * Author: art
 * 
 * Created on 24 Январь 2011 г., 20:32
 */

#include "codecHUFF.h"
#include "shclib.h"

Codec_HUFF::Codec_HUFF() { }

Codec_HUFF::~Codec_HUFF() { }

void
Codec_HUFF::decode_HUFF(DataBlock* inData) {
  initDecoder(inData);

  dataT buffer(decodedDataSize);

  sh_DecodeBlock(data, buffer.data(), encodedDataSize);

  inData->setBlock(buffer.data());
}

void
Codec_HUFF::encode_HUFF(DataBlock* inData) {
  initEncoder(inData);
  dataT buffer(decodedDataSize + 256);

  encodedDataSize = sh_EncodeBlock(data, buffer.data(), decodedDataSize);

  inData->setData(buffer.data(), encodedDataSize);
  recordOutHeader(inData->getHeader(), HUFF_ID);
}

