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

#include "fileBlocksInfo.h"
#include "../private/consts.h"

#include <boost/dynamic_bitset.hpp>

#include <iostream>

using JAA::FileBlockResult;

struct FileBlocksInfo::Private {
public:
    Private() {
    };
    boost::dynamic_bitset<> blocks; // array of block receive status: false - received successfully, true - not
};

FileBlocksInfo::FileBlocksInfo(const FileBlocksInfo& orig) :
    blocksCount(0),
    nonRecievedblocks(),
    id(),
    d(new Private()) {
    d->blocks.resize(orig.d->blocks.size());
    d->blocks = orig.d->blocks;
    blocksCount = orig.blocksCount;
    id = orig.id;
}

FileBlocksInfo::FileBlocksInfo(const uint32_t _totalBlocks, unsigned int _id) :
    blocksCount(_totalBlocks),
    nonRecievedblocks(),
    id(_id),
    d(new Private()) {
    d->blocks.resize(_totalBlocks, true);
    nonRecievedblocks.reserve(_totalBlocks);
}

FileBlocksInfo::~FileBlocksInfo() {
}

bool FileBlocksInfo::complete() {
    return d->blocks.none();
}

unsigned int FileBlocksInfo::getId() const {
    return id;
}

uint32_t FileBlocksInfo::getTotalBlocks() {
    return blocksCount;
}

JAA::FileBlockResult FileBlocksInfo::setRecievedBlock(uint32_t blockN) {
    if (blockN > blocksCount)
        return FileBlockResult::BLOCK_OUT_OF_RANGE;
    if (!d->blocks[blockN])
        return FileBlockResult::BLOCK_ALREADY_RECIEVED;
    d->blocks[blockN] = false;

    if (blocksCount == 1) /* when first block is the last too*/
        return FileBlockResult::FIRST_AND_LAST_RECIEVED_BLOCK;

    if (complete())
        return FileBlockResult::ALL_BLOCKS_RECIEVED;
    return FileBlockResult::OK;
}

vector<uint32_t>& FileBlocksInfo::getNonRecievedBlocksInfo() {
    nonRecievedblocks.clear();
    if (d->blocks.any()) {
        for (unsigned int i = 0; i < d->blocks.size(); ++i) {
            if (d->blocks[i])
                nonRecievedblocks.push_back(i);
        }
    }

    return nonRecievedblocks;
}
