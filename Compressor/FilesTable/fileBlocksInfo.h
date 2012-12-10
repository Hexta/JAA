/* 
 * File:   FileBlocksInfo.h
 * Author: art
 *
 * Created on 12 Март 2011 г., 11:12
 */

#ifndef FILEBLOCKSINFO_H
#define	FILEBLOCKSINFO_H

#include <string.h>
#include <stdint.h>
#include <boost/dynamic_bitset.hpp>
#include <vector>

using namespace std;

class FileBlocksInfo {
public:
  FileBlocksInfo(const FileBlocksInfo& orig);

  FileBlocksInfo(const uint32_t _totalBlocks, unsigned int _id = 0);

  virtual ~FileBlocksInfo();

  uint32_t getTotalBlocks();
  int setRecievedBlock(uint32_t blockN);
  vector<uint32_t> * getNonRecievedBlocksInfo();
  bool complete();
  unsigned int getId() const;

private:
  uint32_t blocksCount;
  boost::dynamic_bitset<> blocks; //array of block recieving status: false - recieved, true - not
  vector< uint32_t> nonRecievedblocks;
  unsigned int id; //file`s ID in archive

};

#endif	/* FILEBLOCKSINFO_H */
