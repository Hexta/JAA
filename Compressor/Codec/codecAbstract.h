/* 
 * File:   Codec_abstract.h
 * Author: art
 *
 * Created on 5 Февраль 2011 г., 19:16
 */

#ifndef CODEC_ABSTRACT_H
#define	CODEC_ABSTRACT_H
#include <stdint.h>

using namespace std;

class DataBlockHeader;
class DataBlock;

class Codec_abstract {
public:
  Codec_abstract();
  virtual ~Codec_abstract() = 0;

protected:
  unsigned char *data;
  unsigned int decodedDataSize;
  unsigned int encodedDataSize;
  uint32_t codecParams;

  void initDecoder(DataBlock * in_block);
  void initEncoder(DataBlock * in_block);
  void recordOutHeader(DataBlockHeader *outHeader, const uint64_t id);

private:
  Codec_abstract(const Codec_abstract&);
  void operator=(const Codec_abstract&);
};

#endif	/* CODEC_ABSTRACT_H */
