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

#include "dataBlock.h"
#include "dataBlockHeader.h"
#include "readerDataBlockHeader.h"

#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#define MIN_RAW_BLOCK_SIZE (100000)

using namespace std;

/*
 * TODO:setBlockSize*2 <-- !
 */
DataBlock::DataBlock(unsigned int setBlockSize) : data(new dataT(setBlockSize * 2)),
dataSize(0), nBytesToRead(setBlockSize), header(new DataBlockHeader()),
outBlock(new dataT(setBlockSize * 2)),
recoveryMode(false) { }

DataBlock::DataBlock() : data(new vector < unsigned char >), dataSize(0), nBytesToRead(0),
header(new DataBlockHeader()), outBlock(NULL), recoveryMode(false) {
  data->reserve(MIN_RAW_BLOCK_SIZE);
}

DataBlock::DataBlock(unsigned char *inData) : data(NULL), dataSize(0),
nBytesToRead(0), header(NULL), outBlock(NULL), recoveryMode(false) {
  unsigned char in_header_data[HEADER_SIZE];
  memcpy(in_header_data, inData, HEADER_SIZE);

  header = new DataBlockHeader(in_header_data);
  dataSize = header->getEncodedDataSize();

  data = new dataT(dataSize);
  data->assign(inData + HEADER_SIZE, inData + HEADER_SIZE + dataSize);
}

DataBlock::~DataBlock() {
  if (header)
    delete header;

  if (outBlock)
    delete outBlock;

  if (data)
    delete data;
}

DataBlockHeader *
DataBlock::readRAW(QFile &in) {
  uint64_t offset = in.pos();
  data->resize(nBytesToRead);
  dataSize = static_cast<uint32_t> (in.read(reinterpret_cast<char*> (data->data()), nBytesToRead));
  if (!dataSize)
    return NULL;

  data->resize(dataSize);

  header->initRAW(offset, dataSize);
  recordCRC();

  return header;
}

JAA::FileIOResult
DataBlock::read(QFile &in) {
  ReaderDataBlockHeader readerHeader;

  switch (readerHeader.read(header, in, recoveryMode)) {
    case JAA::FileIOResult::FILE_END: return JAA::FileIOResult::FILE_END;
      break;
    case JAA::FileIOResult::FILE_TOO_SMALL: return JAA::FileIOResult::FILE_TOO_SMALL;
      break;
    case JAA::FileIOResult::FILE_BROKEN:
      recoveryMode = true;
      return JAA::FileIOResult::HEADER_CORRUPTED;
      break;
    default:;
  }

  data->clear();

  uint32_t origDataSize = header->getEncodedDataSize();

  data->resize(origDataSize);
  dataSize =
      static_cast<uint32_t> (in.read(reinterpret_cast<char*> (data->data()),
                                     origDataSize));

  if ((dataSize != origDataSize) || (checkCRC())) {

    return JAA::FileIOResult::FILE_BROKEN;
  }
  return JAA::FileIOResult::OK;
}

unsigned char *
DataBlock::getData() {
  return data->data();
}

void
DataBlock::setData(unsigned char* inData, unsigned int inDataSize) {
  dataSize = inDataSize;
  data->assign(inData, inData + dataSize);
}

void
DataBlock::setData(dataT* inData) {
  data->assign(inData->begin(), inData->end());
}

void
DataBlock::write(QFile &out) {
  recordCRC();
  getBlock();
  out.write(reinterpret_cast<char*> (outBlock->data()), outBlock->size());
}

DataBlockHeader *
DataBlock::getHeader() {
  return header;
}

dataT *
DataBlock::getBlock() {
  outBlock->assign(header->getData(), header->getData() + HEADER_SIZE);
  outBlock->insert(outBlock->end(), data->begin(), data->end());

  return outBlock;
}

void
DataBlock::setBlock(unsigned char* inBlock) {
  unsigned char in_header_data[HEADER_SIZE];
  memcpy(in_header_data, inBlock, HEADER_SIZE);

  header->setData(in_header_data);
  dataSize = header->getEncodedDataSize();
  data->assign(inBlock + HEADER_SIZE, inBlock + HEADER_SIZE + dataSize);
}

unsigned int
DataBlock::calcCRC() {
  unsigned int dataCRC = crc32(data->data(), dataSize);
  return dataCRC;
}

int
DataBlock::checkCRC() {
  if (calcCRC() != header->getDataCRC())
    return -1;
  return 0;
}

void
DataBlock::recordCRC() {
  header->setDataCRC(calcCRC());
  header->recordCRC();
}

JAA::FileIOResult
DataBlock::writeRAW() {
  char * oFileName = header ->getFileName();
  QFile fout(QString::fromUtf8(oFileName, static_cast<int> (strlen(oFileName))));

  if (!fout.open(QIODevice::ReadWrite))
    return JAA::FileIOResult::OUTPUT_ERROR;

  fout.seek(header->getOffset());

  fout.write(reinterpret_cast<char*> (data->data()), data->size());
  fout.close();

  return JAA::FileIOResult::OK;
}