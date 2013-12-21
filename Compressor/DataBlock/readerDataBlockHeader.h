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

#ifndef READERDATABLOCKHEADER_H
#define	READERDATABLOCKHEADER_H

#include "../private/consts.h"

#include <QFile>

#include <fstream>

class DataBlockHeader;

class ReaderDataBlockHeader {
public:
  ReaderDataBlockHeader();

  ReaderDataBlockHeader(const ReaderDataBlockHeader& orig);

  virtual ~ReaderDataBlockHeader();

  JAA::FileIOResult read(DataBlockHeader * outHeader, QFile &in, bool searchHeader = false);

private:
  bool find(DataBlockHeader *outHeader, QFile &fin);
};

#endif	/* READERDATABLOCKHEADER_H */

