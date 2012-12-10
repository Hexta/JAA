/* 
 * File:   dataBlock.h
 * Author: art
 *
 * Created on 21 Январь 2011 г., 19:07
 */

#ifndef DATABLOCK_H
#define	DATABLOCK_H

#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <stdint.h>
#include <QFile>
#include "../private/consts.h"
#include "../CRC/crc.h"


using namespace std;

typedef vector < unsigned char > dataT;

class DataBlockHeader;

class DataBlock {
private:
  DataBlock(const DataBlock&);
  void operator=(const DataBlock&);

public:
  DataBlock();
  DataBlock(uint32_t block_size);
  DataBlock(unsigned char *inData);
  virtual ~DataBlock();

  /*read-write*/
  DataBlockHeader * readRAW(QFile &in);
  int read(QFile &in);
  int writeRAW();
  void write(QFile &out);

  /*data get*/
  DataBlockHeader * getHeader();
  unsigned char * getData();
  void setData(unsigned char* inData, uint32_t inDataSize);
  void setData(dataT* inData);
  dataT *getBlock();
  void setBlock(unsigned char* inBlock);

  /*Integrity check*/
  int checkCRC();
  void recordCRC();

private:
  dataT *data;
  uint32_t dataSize;
  uint32_t nBytesToRead;
  DataBlockHeader *header;
  dataT *outBlock;
  bool recoveryMode;

  uint32_t calcCRC();

};

#endif	/* DATABLOCK_H */
