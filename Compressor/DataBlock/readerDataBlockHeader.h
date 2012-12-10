/* 
 * File:   ReaderDataBlockHeader.h
 * Author: art
 *
 * Created on 12 Март 2011 г., 17:35
 */

#ifndef READERDATABLOCKHEADER_H
#define	READERDATABLOCKHEADER_H

#include <fstream>
#include "QFile"

class DataBlockHeader;

class ReaderDataBlockHeader {
public:
  ReaderDataBlockHeader();

  ReaderDataBlockHeader(const ReaderDataBlockHeader& orig);

  virtual ~ReaderDataBlockHeader();

  int read(DataBlockHeader * outHeader, QFile &in, bool searchHeader = false);

private:
  bool find(DataBlockHeader *outHeader, QFile &fin);
};

#endif	/* READERDATABLOCKHEADER_H */

