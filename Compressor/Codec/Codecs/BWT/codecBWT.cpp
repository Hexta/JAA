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

  int32_t *SA = new int32_t [decodedDataSize];

  codecParams = divbwt(data, buffer.data(), SA, decodedDataSize);

  inData->setData(buffer.data(), buffer.size());

  recordOutHeader(inData->getHeader(), BWT_ID);

  delete[] SA;
  delete[] index_table;
}

void
Codec_BWT::decode_BWT(DataBlock* inData) {
  initDecoder(inData);

  unsigned int * index_table = new unsigned int [encodedDataSize];

  int32_t *A = new int32_t [encodedDataSize];
  inverse_bw_transform(data, data, A, encodedDataSize, codecParams);
  delete[] A;

  inData->setBlock(data);

  delete[] index_table;
}