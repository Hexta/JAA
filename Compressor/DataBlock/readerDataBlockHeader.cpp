/* 
 * File:   ReaderDataBlockHeader.cpp
 * Author: art
 * 
 * Created on 12 Март 2011 г., 17:35
 */

#include "readerDataBlockHeader.h"
#include  "dataBlockHeader.h"

#include <algorithm>

#define BUFFER_SIZE (100000)

ReaderDataBlockHeader::ReaderDataBlockHeader() { }

ReaderDataBlockHeader::~ReaderDataBlockHeader() { }

int
ReaderDataBlockHeader::read(DataBlockHeader * outHeader, QFile &in, bool recoverMode) {
  if (recoverMode) {
    if (find(outHeader, in)) {
      return FILE_END;
    }
  } else {
    unsigned char in_header_data[HEADER_SIZE];
    unsigned int receivedBytesCount = in.read((char*) in_header_data, HEADER_SIZE);

    if (receivedBytesCount == 0)
      return FILE_END;

    else if (receivedBytesCount < HEADER_SIZE)
      return FILE_TOO_SMALL;

    outHeader->setData(in_header_data);

    if (outHeader->checkCRC())
      return FILE_BROKEN;
  }

  return 0;
}

bool
ReaderDataBlockHeader::find(DataBlockHeader *outHeader, QFile &fin) {
  unsigned char buffer[BUFFER_SIZE];

  unsigned int nReadBytes;

  while ((nReadBytes = fin.read((char*) buffer, BUFFER_SIZE)) > HEADER_SIZE) {
    unsigned char * findPos =
        std::search(buffer, buffer + nReadBytes + 1, ARCHIVER_ID, ARCHIVER_ID + 7);

    if (findPos == buffer + nReadBytes + 1) {
      fin.seek(-(std::streamoff) (HEADER_SIZE - 1) + fin.pos());
    } else {
      //found at findPos

      if ((BUFFER_SIZE - (findPos - buffer)) > HEADER_SIZE) {
        //enough space in buffer

        outHeader->setData(findPos);

        if (!outHeader->checkCRC()) {
          //valid CRC
          fin.seek(-(std::streamoff)(nReadBytes - (findPos - buffer) - HEADER_SIZE) + fin.pos());
          return 0;
        } else {
          //not valid CRC may be not header?
          fin.seek(-(std::streamoff)(nReadBytes - (findPos - buffer) - 2) + fin.pos());
          //try again with offset
        }
      } else {
        //not enough space
        fin.seek(-(nReadBytes - (findPos - buffer) - 1) + fin.pos());
      }
    }
  }

  return -1;
}