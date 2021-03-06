/******************************************************************************
 * Copyright (c) 2011-2014 Artur Molchanov <artur.molchanov@gmail.com>        *
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

#include "divsuf/divsufsort.h"
#include "Compressor/Codec/codecAbstract.h"

class DataBlock;

class Codec_BWT : public virtual Codec_abstract {
public:
    Codec_BWT();
    ~Codec_BWT();

    void encode_BWT(DataBlock* inData);
    void decode_BWT(DataBlock* inData);

private:
    std::vector<int32_t> SA;
};
