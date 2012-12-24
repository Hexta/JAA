/* 
 * File:   codec_BWT.cpp
 * Author: art
 * 
 * Created on 23 Январь 2011 г., 12:47
 */

#include "codecBWT.h"

Codec_BWT::Codec_BWT() { }

Codec_BWT::~Codec_BWT() { }

void
Codec_BWT::encode_BWT(DataBlock* inData) {
  initEncoder(inData);

  encodedDataSize = decodedDataSize;

  buffer.reserve(encodedDataSize);

  SA.reserve(decodedDataSize);

  codecParams = divbwt(data, buffer.data(), SA.data(), decodedDataSize);

  inData->setData(buffer.data(), encodedDataSize);

  recordOutHeader(inData->getHeader(), BWT_ID);
}

void
Codec_BWT::decode_BWT(DataBlock* inData) {
  initDecoder(inData);

  SA.reserve(encodedDataSize);
  inverse_bw_transform(data, data, SA.data(), encodedDataSize, codecParams);

  inData->setBlock(data);
}