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

#pragma once

#include "Compressor/Codec/Codecs/BWT/codecBWT.h"
#include "Compressor/Codec/Codecs/MTF/codecMTF.h"
#include "Compressor/Codec/Codecs/RLE/codecRLE.h"
#include "Compressor/Codec/Codecs/HUFF/codecHUFF.h"

class Codec : public virtual Codec_BWT, public virtual Codec_HUFF,
    public virtual Codec_MTF, public virtual Codec_RLE {

public:
  Codec();
  virtual ~Codec();

private:
};
