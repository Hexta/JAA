/* 
 * File:   Codec_abstract.cpp
 * Author: art
 * 
 * Created on 5 Февраль 2011 г., 19:16
 */

#include "codecAbstract.h"
#include "../DataBlock/dataBlock.h"
#include "../DataBlock/dataBlockHeader.h"

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
  decodedDataSize = vect->size();
}

void
Codec_abstract::recordOutHeader(DataBlockHeader *outHeader, const uint64_t id) {
  outHeader->clean();
  outHeader->setId(id);
  outHeader->setDecodedDataSize(decodedDataSize);
  outHeader->setEncodedDataSize(encodedDataSize);
  outHeader->setCodecParams(codecParams);
}