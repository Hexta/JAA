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

  unsigned int * index_table = new unsigned int[decodedDataSize];

  encodedDataSize = decodedDataSize;

  dataT buffer(encodedDataSize);

  SA.reserve(decodedDataSize);

  codecParams = divbwt(data, buffer.data(), SA.data(), decodedDataSize);

  inData->setData(buffer.data(), buffer.size());

  recordOutHeader(inData->getHeader(), BWT_ID);
}

void
Codec_BWT::decode_BWT(DataBlock* inData) {
  initDecoder(inData);

  unsigned int * index_table = new unsigned int [encodedDataSize];

  SA.reserve(encodedDataSize);
  inverse_bw_transform(data, data, SA.data(), encodedDataSize, codecParams);

  inData->setBlock(data);
}