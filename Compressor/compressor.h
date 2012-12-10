/* 
 * File:   Compressor.h
 * Author: art
 *
 * Created on 5 Февраль 2011 г., 20:56
 */

#ifndef COMPRESSOR_H
#define	COMPRESSOR_H

#include <list>
#include "./Codec/codec.h"
#include "FilesTable/filesTable.h"
#include "DataBlock/dataBlockHeader.h"

class CompressorStatus {
public:

  CompressorStatus()
      : runStatus(RUN) { };

  enum RunStatus {
    RUN, STOP
  };

  enum ErrorCode {
    SUCCESS,
    INPUT_FILE_OPEN_ERROR,
    OUTPUT_FILE_WRITE_ERROR,
    INPUT_FILE_CORRUPTED,
    INPUT_FILE_UNCORRUPTED,
    DECOMPRESS_FAIL,
    PROCEED,
    CANCELLED
  };

  void
  setRunStatus(RunStatus status) {
    runStatus = status;
  }

  RunStatus
  getRunStatus() const {
    return runStatus;
  }

  virtual void showProgress(float progress, const QString &fileName,
      float speed);
  virtual void showInfo(ErrorCode errorCode, const QString &fileName,
      unsigned int id);

private:
  RunStatus runStatus;
};

class Compressor {
public:
  Compressor(CompressorStatus *status);
  virtual
  ~Compressor();

  struct Stat {
    off_t decodedSize;
    off_t encodedSize;
    float speed; //enc-/dec- speed (mb/s)
    vector<string> brokenFilesNames;
  };

  enum CoderTypes {
    NONE, RLE, BWT, MTF, HUFFMAN
  };

  /**
   * Compress multiply files
   * @param iFileNames	array with input file names
   * @param iFilesCount	number of input files
   * @param oFileName		output file name
   * @param blocksize		block size
   * @return				error code
   */
  CompressorStatus::ErrorCode compress(const vector<QString> &iFileNames,
      const QString &oFileName, unsigned int blocksize,
      const list<CoderTypes> *compressSequence = NULL);
  /**
   * Decompress archive
   * @param iFileName		archive filename
   * @param keepBroken	keep broken files
   * @return				error code
   */
  CompressorStatus::ErrorCode decompress(const QString &iFileName,
      bool keepBroken = false);
  /**
   * Get statistical info
   * @param stat	point to info structure
   */
  void getStat(Stat *stat);

  /**
   * List archive contents
   * @param iFileName	archive filename
   * @param contents	point to output vector with archive contents
   * @return			error code
   */
  CompressorStatus::ErrorCode listArchiveContents(const QString &iFileName,
      vector<FilesTable::FileInfo> * const contents = NULL);

private:
  Codec codec;
  DataBlock *block;
  CompressorStatus *status;
  off_t currReadBytesCount;
  off_t decodedDataSize;
  off_t encodedDataSize;
  uint32_t totalProcessingTime;
  unsigned int source_data_size;
  FilesTable blocksTable;
  CompressorStatus::ErrorCode error;
  vector<FilesTable::FileInfo> contents;
  list<CoderTypes> defaultCompressSequence;

  void showEncodingProgress(const QString &currFileName, float speed);
  void showDecodingProgress(const char * currFileName, float speed);
  void showInfo(CompressorStatus::ErrorCode errorCode,
      const QString &currFileName = "", unsigned int id = 0);
  void showInfo(CompressorStatus::ErrorCode errorCode,
      const char * currFileName, unsigned int id = 0);

  void compress(const list<CoderTypes> *compressSequence = NULL);
  bool decompress();

  bool createEmptyFile(const char * fileName);
  void removeBrokenFiles();
  float speed(unsigned int nBytes, clock_t elapsedTime);

};

class Encoder {
public:

  Encoder(DataBlock * block, Codec *codec) {
    this->block = block;
    this->codec = codec;
  }

  virtual
  ~Encoder() { }
  ;

  void operator()(Compressor::CoderTypes coderType) {
    switch (coderType) {
    case Compressor::BWT:
      codec->encode_BWT(block);
      break;
    case Compressor::RLE:
      codec->encode_RLE(block);
      break;
    case Compressor::MTF:
      codec->encode_MTF(block);
      break;
    case Compressor::HUFFMAN:
      codec->encode_HUFF(block);
      break;
    default:
      break;
    }
  }
private:

  DataBlock *block;
  Codec *codec;

};

void inline
Compressor::compress(const list<CoderTypes> *compressSequence) {
  Encoder encoder(block, &codec);
  const list<CoderTypes> *sequence =
      compressSequence ? compressSequence : &defaultCompressSequence;
  std::for_each(sequence->begin(), sequence->end(), encoder);
}

bool inline
Compressor::decompress() {
  uint64_t id;
  while ((id = block->getHeader()->getId()) != RAW_ID) {
    switch (id) {
    case HUFF_ID:
      codec.decode_HUFF(block);
      break;
    case RLE_ID:
      codec.decode_RLE(block);
      break;
    case BWT_ID:
      codec.decode_BWT(block);
      break;
    case MTF_ID:
      codec.decode_MTF(block);
      break;
    default:
      return -1;
    }
  }
  return 0;
}

void inline
Compressor::showDecodingProgress(const char * currFileName,
    float speed) {
  if (status)
    status->showProgress(
      (encodedDataSize) ? (float) currReadBytesCount / encodedDataSize : 0,
      QString::fromUtf8(currFileName, strlen(currFileName)), speed);
}

void inline
Compressor::showEncodingProgress(const QString &currFileName,
    const float speed) {
  if (status)
    status->showProgress(
      (decodedDataSize) ? (float) currReadBytesCount / decodedDataSize : 0,
      currFileName, speed);
}

float inline
Compressor::speed(unsigned int nBytes, clock_t elapsedTime) {
  return (elapsedTime) ? nBytes / ((double) elapsedTime / CLOCKS_PER_SEC) : 0;
}

void inline
Compressor::showInfo(CompressorStatus::ErrorCode errorCode,
    const QString &currFileName, unsigned int id) {
  if (status) status->showInfo(errorCode, currFileName, id);
}

void inline
Compressor::showInfo(CompressorStatus::ErrorCode errorCode,
    const char * currFileName, unsigned int id) {
  QString fileName;
  if (!currFileName)
    fileName = "";
  else
    fileName = QString::fromUtf8(currFileName, strlen(currFileName));
  if (status) status->showInfo(errorCode, fileName, id);
}

#endif	/* COMPRESSOR_H */
