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

#ifndef CODEC_HUFF_H
#define	CODEC_HUFF_H

#include "../../../DataBlock/dataBlock.h"
#include "../../codecAbstract.h"

class Codec_HUFF : public virtual Codec_abstract {
public:
  Codec_HUFF();
  virtual ~Codec_HUFF();

  void decode_HUFF(DataBlock* inData);
  void encode_HUFF(DataBlock* inData);

private:
};

#endif	/* CODEC_HUFF_H */
