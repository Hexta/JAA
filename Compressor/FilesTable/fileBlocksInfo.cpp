/* 
 * File:   FileBlocksInfo.cpp
 * Author: art
 * 
 * Created on 12 Март 2011 г., 11:12
 */

#include <iostream>
#include "fileBlocksInfo.h"
#include "../private/consts.h"

FileBlocksInfo::FileBlocksInfo(const FileBlocksInfo& orig) : blocksCount(0),
    blocks(), nonRecievedblocks(), id() {
  blocks.resize(orig.blocks.size());
  blocks = orig.blocks;
  blocksCount = orig.blocksCount;
  id = orig.id;
}

FileBlocksInfo::FileBlocksInfo(const uint32_t _totalBlocks, unsigned int _id)
    : blocksCount(_totalBlocks), blocks(), nonRecievedblocks(), id(_id) {
  blocks.resize(_totalBlocks, true);
  nonRecievedblocks.reserve(_totalBlocks);
}

FileBlocksInfo::~FileBlocksInfo() { }

bool
FileBlocksInfo::complete() {
  return blocks.none();
}

unsigned int
FileBlocksInfo::getId() const {
  return id;
}

uint32_t
FileBlocksInfo::getTotalBlocks() {
  return blocksCount;
}

int
FileBlocksInfo::setRecievedBlock(uint32_t blockN) {
  if (blockN > blocksCount)
    return BLOCK_OUT_OF_RANGE;
  if (!blocks[blockN])
    return BLOCK_ALREADY_RECIEVED;
  blocks[blockN] = false;

  if (blocksCount == 1)/* when first block is the last too*/
    return FIRST_AND_LAST_RECIEVED_BLOCK;

  if (complete())
    return ALL_BLOCKS_RECIEVED;
  return 0;
}

vector<uint32_t> *
FileBlocksInfo::getNonRecievedBlocksInfo() {
  nonRecievedblocks.clear();
  if (blocks.any()) {
    for (unsigned int i = 0; i < blocks.size(); ++i) {
      if (blocks[i])
        nonRecievedblocks.push_back(i);
    }
    return &nonRecievedblocks;
  }
  return NULL;
}
