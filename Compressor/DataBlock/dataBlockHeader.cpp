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

#include "dataBlockHeader.h"

#include <cstring>

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#elif defined(__GNUC__)
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

using JAA_header_constants::HEADER_SIZE;
using JAA_header_constants::HEADER_DATA_SIZE;
using JAA_header_constants::MAX_FILENAME_LENGTH;

struct DataBlockHeader::Private {
  Private() {}

  Private(unsigned char * inHeaderData) {
    memcpy(&headerData, inHeaderData, HEADER_SIZE);
  }

  void initRAW(uint64_t offset, const uint32_t rawDataSize) {
    memset(&headerData, 0, HEADER_SIZE);
    headerData.id = JAA::CodecID::RAW_ID;
    headerData.decodedDataSize = rawDataSize;
    // input size equal output
    headerData.encodedDataSize = rawDataSize;
    headerData.offset = offset;
  }

  PACK(
    struct HeaderDataType {
        uint64_t id;
        uint32_t headerCRC;
        uint64_t offset;
        uint32_t rawDataSize;
        uint32_t decodedDataSize;
        uint32_t encodedDataSize;
        uint32_t encodedDataCRC;
        uint32_t codecParams;
        char fileName[MAX_FILENAME_LENGTH];
        uint32_t part;
        uint32_t partsCount;
  }) headerData;
};

DataBlockHeader::DataBlockHeader() :
  d(new Private()) { }

DataBlockHeader::~DataBlockHeader() { }

DataBlockHeader::DataBlockHeader(unsigned char * in_header_data) :
  d(new Private(in_header_data)) {
}

void
DataBlockHeader::setCodecParams(uint32_t codec_params) {
  d->headerData.codecParams = codec_params;
}

uint32_t
DataBlockHeader::getCodecParams() {
  return d->headerData.codecParams;
}

void
DataBlockHeader::setRAWDataSize(uint32_t RAWDataSize) {
  d->headerData.rawDataSize = RAWDataSize;
}

uint32_t
DataBlockHeader::getRAWDataSize() const {
  return d->headerData.rawDataSize;
}

void
DataBlockHeader::setEncodedDataSize(uint32_t encodedDataSize) {
  d->headerData.encodedDataSize = encodedDataSize;
}

uint32_t
DataBlockHeader::getEncodedDataSize() const {
  return d->headerData.encodedDataSize;
}

void
DataBlockHeader::setDecodedDataSize(uint32_t decodedDataSize) {
  d->headerData.decodedDataSize = decodedDataSize;
}

uint32_t
DataBlockHeader::getDecodedDataSize() const {
  return d->headerData.decodedDataSize;
}

void
DataBlockHeader::setId(uint64_t id) {
  d->headerData.id = id;
}

uint64_t
DataBlockHeader::getId() const {
  return d->headerData.id;
}

unsigned char *
DataBlockHeader::getData() {
  return reinterpret_cast<unsigned char*> (&d->headerData);
}

void
DataBlockHeader::setData(unsigned char *inHeaderData) {
  memcpy(&d->headerData, inHeaderData, HEADER_SIZE);
}

void
DataBlockHeader::clean() {
  memset(&d->headerData, 0, HEADER_SIZE);
}

void
DataBlockHeader::setDataCRC(uint32_t crc) {
  d->headerData.encodedDataCRC = crc;
}

uint32_t
DataBlockHeader::getDataCRC() {
  return d->headerData.encodedDataCRC;
}

void
DataBlockHeader::recordCRC() {
  setHeaderCRC(calcCRC());
}

int
DataBlockHeader::checkCRC() {
  if (calcCRC() != getHeaderCRC())
    return -1;
  return 0;
}

void
DataBlockHeader::setFileName(const char * fileName) {
  strncpy(d->headerData.fileName, fileName, MAX_FILENAME_LENGTH);
}

char *
DataBlockHeader::getFileName() {
  return d->headerData.fileName;
}

void
DataBlockHeader::setPart(const uint32_t part) {
  d->headerData.part = part;
}

uint32_t
DataBlockHeader::getPart() const {
  return d->headerData.part;
}

void
DataBlockHeader::setPartsCount(const uint32_t partsCount) {
  d->headerData.partsCount = partsCount;
}

uint32_t
DataBlockHeader::getPartsCount() const {
  return d->headerData.partsCount;
}

uint32_t
DataBlockHeader::calcCRC() {
  getData();
  uint32_t headerCRC = crc32(reinterpret_cast<unsigned char *> (&d->headerData.offset),
    HEADER_DATA_SIZE);
  return headerCRC;
}

void
DataBlockHeader::setHeaderCRC(uint32_t headerCRC) {
  d->headerData.headerCRC = headerCRC;
}

uint32_t
DataBlockHeader::getHeaderCRC() const {
  return d->headerData.headerCRC;
}

void
DataBlockHeader::setOffset(uint64_t offset) {
  d->headerData.offset = offset;
}

uint64_t
DataBlockHeader::getOffset() {
  return d->headerData.offset;
}

void
DataBlockHeader::initRAW(uint64_t offset, const uint32_t rawDataSize) {
  return d->initRAW(offset, rawDataSize);
}
