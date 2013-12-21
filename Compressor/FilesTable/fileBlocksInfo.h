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

#ifndef FILEBLOCKSINFO_H
#define	FILEBLOCKSINFO_H

#include "../private/consts.h"

#include <boost/dynamic_bitset.hpp>

#include <string.h>
#include <stdint.h>
#include <vector>

using namespace std;

class FileBlocksInfo {
public:
    FileBlocksInfo(const FileBlocksInfo& orig);

    FileBlocksInfo(const uint32_t _totalBlocks, unsigned int _id = 0);

    virtual ~FileBlocksInfo();

    uint32_t getTotalBlocks();
    JAA::FileBlockResult setRecievedBlock(uint32_t blockN);
    vector<uint32_t>& getNonRecievedBlocksInfo();
    bool complete();
    unsigned int getId() const;

private:
    uint32_t blocksCount;
    boost::dynamic_bitset<> blocks; //array of block recieving status: false - recieved, true - not
    vector< uint32_t> nonRecievedblocks;
    unsigned int id; //file`s ID in archive

};

#endif	/* FILEBLOCKSINFO_H */
