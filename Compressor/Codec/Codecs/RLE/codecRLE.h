/* 
 * File:   Codec_RLE.h
 * Author: art
 *
 * Created on 31 Январь 2011 г., 14:24
 */

#ifndef CODEC_RLE_H
#define	CODEC_RLE_H

#include "../../../DataBlock/dataBlock.h"
#include "../../codecAbstract.h"

class Codec_RLE : public virtual Codec_abstract {
public:
  Codec_RLE();
  virtual ~Codec_RLE();

  void decode_RLE(DataBlock* inData);
  void encode_RLE(DataBlock* inData);

private:
};

#endif	/* CODEC_RLE_H */

