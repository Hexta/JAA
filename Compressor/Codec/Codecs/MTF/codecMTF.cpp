/* 
 * File:   codec_MTF.cpp
 * Author: art
 * 
 * Created on 23 Январь 2011 г., 20:50
 */

#include "codecMTF.h"

Codec_MTF::Codec_MTF() { }

Codec_MTF::~Codec_MTF() { }

void
Codec_MTF::decode_MTF(DataBlock* inData) {
  initDecoder(inData);

  buffer.reserve(decodedDataSize);

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

  init_mtf(256);

  for (unsigned int i = 0; i < decodedDataSize; ++i)
    buffer[i] = mtf(data[i]);

  inData->setData(buffer.data(), encodedDataSize);

  recordOutHeader(inData->getHeader(), MTF_ID);
}

void
Codec_MTF::init_mtf(int tsize) {
  p =
      head =
      tail = NULL;

  table.reserve(tsize);
  /* initialize the list. */
  for (int i = tsize; i-- > 0;) {
    table[i].c = i;
    table[i].next = &table[i - 1];
    table[i].prev = &table[i + 1];
  }

  table[tsize - 1].prev = NULL;
  table[0].next = NULL;
  head = &table[tsize - 1];
  tail = &table[0];
}
