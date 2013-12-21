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

#ifndef CODEC_ABSTRACT_H
#define	CODEC_ABSTRACT_H

#include "../DataBlock/dataBlock.h"

#include <stdint.h>

using namespace std;

class DataBlockHeader;
class DataBlock;

class Codec_abstract {
public:
  Codec_abstract();
  virtual ~Codec_abstract() = 0;

protected:
  dataT buffer;
  unsigned char *data;
  unsigned int decodedDataSize;
  unsigned int encodedDataSize;
  uint32_t codecParams;

  void initDecoder(DataBlock * in_block);
  void initEncoder(DataBlock * in_block);
  void recordOutHeader(DataBlockHeader *outHeader, uint64_t id);

private:
  Codec_abstract(const Codec_abstract&);
  void operator=(const Codec_abstract&);
};

#endif	/* CODEC_ABSTRACT_H */
