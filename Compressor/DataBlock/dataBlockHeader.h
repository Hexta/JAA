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

#ifndef DATABLOCKHEADER_H
#define	DATABLOCKHEADER_H

#include "../CRC/crc.h"
#include "../private/consts.h"

#include <stdint.h>
#include <cstring>

#define HEADER_SIZE (448)
#define HEADER_DATA_SIZE (436)//After Header-CRC data size
#define MAX_FILENAME_LENGTH (400)

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#elif defined(__GNUC__)
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

class DataBlockHeader {
public:
  DataBlockHeader();
  virtual ~DataBlockHeader();

  DataBlockHeader(unsigned char * in_header_data);

  void setCodecParams(uint32_t codec_params);
  uint32_t getCodecParams();

  void setRAWDataSize(uint32_t RAWDataSize);
  uint32_t getRAWDataSize() const;

  void setEncodedDataSize(uint32_t encodedDataSize);
  uint32_t getEncodedDataSize() const;

  void setDecodedDataSize(uint32_t decodedDataSize);
  uint32_t getDecodedDataSize() const;

  void setId(uint64_t id);
  uint64_t getId() const;

  void setData(unsigned char *inHeaderData);
  unsigned char * getData();

  void setDataCRC(uint32_t crc);
  uint32_t getDataCRC();

  uint32_t calcCRC();
  void recordCRC();
  int checkCRC();

  void setFileName(const char * fileName);
  char * getFileName();

  void setPart(const uint32_t part);
  uint32_t getPart() const;

  void setPartsCount(const uint32_t part);
  uint32_t getPartsCount() const;

  void setHeaderCRC(uint32_t headerCRC);
  uint32_t getHeaderCRC() const;

  void setOffset(uint64_t offset);
  uint64_t getOffset();

  void clean();
  /**
   * Init header of uncompressed data
   * @param offset offset of the begin current block in source file
   * @param in_data_size size of block
   */
  void
  initRAW(uint64_t offset, const uint32_t rawDataSize);

private:
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

  DataBlockHeader(const DataBlockHeader&);

};

#endif	/* DATABLOCKHEADER_H */

