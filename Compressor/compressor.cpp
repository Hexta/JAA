/* 
 * File:   Compressor.cpp
 * Author: art
 * 
 * Created on 5 Февраль 2011 г., 20:56
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>
#include <QFile>
#include "compressor.h"

void
CompressorStatus::showProgress(float, const QString&, float) { }

void
CompressorStatus::showInfo(ErrorCode, const QString&, unsigned int) { }

Compressor::Compressor(CompressorStatus *status)
    : codec(), block(NULL), status(status), currReadBytesCount(0),
    decodedDataSize(0), encodedDataSize(0), totalProcessingTime(0),
    source_data_size(0), blocksTable(), defaultCompressSequence() {

  defaultCompressSequence.push_back(RLE);
  defaultCompressSequence.push_back(BWT);
  defaultCompressSequence.push_back(MTF);
  defaultCompressSequence.push_back(RLE);
  defaultCompressSequence.push_back(BWT);
  defaultCompressSequence.push_back(RLE);
  defaultCompressSequence.push_back(HUFFMAN);
}

Compressor::~Compressor() { }

/*
 * Encoding
 */

bool
Compressor::createEmptyFile(const char * fileName) {
  QFile fout(QString::fromUtf8(fileName, strlen(fileName)));
  if (!fout.open(QIODevice::Truncate | QIODevice::WriteOnly)) return false;
  fout.close();
  return true;
}

CompressorStatus::ErrorCode
Compressor::compress(
    const vector<QString> &iFileNames, const QString &oFileName,
    unsigned int blocksize, const list<CoderTypes> *compressSequence) {
  totalProcessingTime = 0;
  decodedDataSize = 0;
  currReadBytesCount = 0;
  encodedDataSize = 0;
  error = CompressorStatus::SUCCESS;

  vector<int> proceedFiles;

  const int iFilesCount = iFileNames.size();

  for (vector<QString>::const_iterator i = iFileNames.begin();
       i != iFileNames.end(); ++i) {

    const int fileId = i - iFileNames.begin();
    QFile fin(*i);

    if (!fin.open(QIODevice::ReadOnly)) {
      showInfo(CompressorStatus::INPUT_FILE_OPEN_ERROR, *i, fileId + 1);
      error = CompressorStatus::INPUT_FILE_OPEN_ERROR;
      continue;
    }
    fin.close();

    proceedFiles.push_back(fileId);
    decodedDataSize += fin.size();
  }

  block = new DataBlock(blocksize);
  DataBlockHeader * header = block->getHeader();

  QFile fout(oFileName);
  if (!fout.open(QIODevice::WriteOnly)) {
    showInfo(CompressorStatus::OUTPUT_FILE_WRITE_ERROR);
    return error = CompressorStatus::OUTPUT_FILE_WRITE_ERROR;
  }

  bool stop = false;
  for (vector<int>::iterator i = proceedFiles.begin();
       i != proceedFiles.end(); ++i) {
    showInfo(CompressorStatus::PROCEED, iFileNames[*i], *i + 1);

    QFile fin(iFileNames[*i]);
    if (!fin.open(QIODevice::ReadOnly)) {
      fout.close();
      showInfo(CompressorStatus::INPUT_FILE_OPEN_ERROR, iFileNames[*i], *i + 1);
      error = CompressorStatus::INPUT_FILE_OPEN_ERROR;
      continue;
    }

    uint32_t partsCount = ceil((float) fin.size() / blocksize);
    uint32_t part = 0;

    while (1) {
      if (status) {
        if (status->getRunStatus() == CompressorStatus::STOP) {
          stop = true;
          break;
        }
      }

      //compress current file
      if (!block->readRAW(fin)) break;

      source_data_size = header->getDecodedDataSize();
      currReadBytesCount += source_data_size;

      header->setFileName(iFileNames[*i].toUtf8().constData());
      header->setPart(part++);
      header->setPartsCount(partsCount);

      clock_t startTime = clock();

      compress(compressSequence);

      clock_t stoptTime = clock();
      totalProcessingTime += stoptTime - startTime;

      header->setFileName(iFileNames[*i].toUtf8().constData());
      encodedDataSize += header->getEncodedDataSize();
      header->setRAWDataSize(source_data_size);
      header->setPart(part - 1);
      header->setPartsCount(partsCount);
      block->write(fout);

      showEncodingProgress(iFileNames[*i],
          speed(source_data_size, stoptTime - startTime));
    }

    fin.close();

    if (!stop)
      showInfo(CompressorStatus::SUCCESS, iFileNames[*i], *i + 1);
    else {
      do {
        showInfo(CompressorStatus::CANCELLED, iFileNames[*i], *i + 1);
      } while (++i != proceedFiles.end());
      break;
    }
  }

  delete block;
  return error;
}

/*
 * Decoding
 */

CompressorStatus::ErrorCode
Compressor::decompress(const QString &iFileName,
    bool keepBroken) {
  blocksTable.clean();
  totalProcessingTime = 0;
  decodedDataSize = 0;
  currReadBytesCount = 0;
  encodedDataSize = 0;
  unsigned int nextId = 1;
  error = CompressorStatus::SUCCESS;

  QFile fin(iFileName);
  if (!fin.open(QIODevice::ReadOnly)) {
    showInfo(CompressorStatus::INPUT_FILE_OPEN_ERROR);
    return error = CompressorStatus::INPUT_FILE_OPEN_ERROR;
  }

  block = new DataBlock();
  DataBlockHeader * header = block->getHeader();

  encodedDataSize = fin.size();

  bool stop = false;
  while (!stop) {
    switch (block->read(fin)) {
    case FILE_END:
      stop = true;
      continue;

    case FILE_BROKEN:
    {
      error = CompressorStatus::INPUT_FILE_CORRUPTED;
      unsigned id = blocksTable.getId(header);
      id = id ? id : nextId++;
      showInfo(CompressorStatus::INPUT_FILE_CORRUPTED, header->getFileName(),
          id);
      continue;
    }
    case HEADER_CORRUPTED:
    {
      error = CompressorStatus::INPUT_FILE_CORRUPTED;
      showInfo(CompressorStatus::INPUT_FILE_CORRUPTED);
      continue;
    }
    case FILE_TOO_SMALL:
    {
      if (keepBroken == false) removeBrokenFiles();
      showInfo(CompressorStatus::INPUT_FILE_CORRUPTED);
      return error = CompressorStatus::INPUT_FILE_CORRUPTED;
    }
    default:
      break;
    }

    currReadBytesCount = fin.pos();

    clock_t startTime = clock();

    decompress();

    clock_t stoptTime = clock();
    totalProcessingTime += stoptTime - startTime;

    decodedDataSize += header->getDecodedDataSize();
    showDecodingProgress(header->getFileName(),
        speed(header->getEncodedDataSize(), stoptTime - startTime));

    if (block->checkCRC()) {
      delete block;
      fin.close();
      showInfo(CompressorStatus::DECOMPRESS_FAIL);
      return error = CompressorStatus::DECOMPRESS_FAIL;
    }

    switch (blocksTable.add(header, nextId)) {
    case FIRST_AND_LAST_RECIEVED_BLOCK:
      blocksTable.remove(header);
      if (!createEmptyFile(header->getFileName())) {
        showInfo(CompressorStatus::OUTPUT_FILE_WRITE_ERROR);
        return error = CompressorStatus::OUTPUT_FILE_WRITE_ERROR;
      }
      showInfo(CompressorStatus::SUCCESS, header->getFileName(), nextId++);
      break;

    case FIRST_RECIEVED_BLOCK:
      createEmptyFile(header->getFileName());
      showInfo(CompressorStatus::PROCEED, header->getFileName(), nextId++);
      break;

    case ALL_BLOCKS_RECIEVED:
      showInfo(CompressorStatus::SUCCESS, header->getFileName(),
          blocksTable.getId(header));
      blocksTable.remove(header);
      break;

    case BLOCK_OUT_OF_RANGE:
    case BLOCK_ALREADY_RECIEVED:
      showInfo(CompressorStatus::INPUT_FILE_CORRUPTED);
      return error = CompressorStatus::INPUT_FILE_CORRUPTED;
      break;

    default:
      break;
    }

    if (block->writeRAW()) {
      delete block;
      fin.close();
      showInfo(CompressorStatus::OUTPUT_FILE_WRITE_ERROR);
      return error = CompressorStatus::OUTPUT_FILE_WRITE_ERROR;
    }

    if (status->getRunStatus() == CompressorStatus::STOP) {
      stop = true;
      showInfo(CompressorStatus::CANCELLED, header->getFileName(),
          blocksTable.getId(header));
    }
  }

  //Check for broken files

  vector<string> * brokenFilesNames = blocksTable.getNonCompleteFilesNames();

  if (brokenFilesNames)
    for (vector<string>::iterator i = brokenFilesNames->begin();
         i != brokenFilesNames->end(); ++i) {
      showInfo(CompressorStatus::INPUT_FILE_CORRUPTED, i->c_str(),
          blocksTable.getId(*i));
      if (keepBroken == false) removeBrokenFiles();
    }

  fin.close();
  delete block;
  return error;
}

void
Compressor::getStat(Stat *stat) {
  vector<string> *nonCompleteFilesNames =
      blocksTable.getNonCompleteFilesNames();

  if (nonCompleteFilesNames) stat->brokenFilesNames = *nonCompleteFilesNames;
  stat->decodedSize = decodedDataSize;
  stat->encodedSize = encodedDataSize;
  stat->speed = speed(decodedDataSize, totalProcessingTime);
}

void
Compressor::removeBrokenFiles() {
  vector<string> *nonCompleteFilesNames =
      blocksTable.getNonCompleteFilesNames();

  if (nonCompleteFilesNames) {
    for (unsigned int i = 0; i < nonCompleteFilesNames->size(); ++i)
      QFile::remove(
        QString::fromUtf8((*nonCompleteFilesNames)[i].c_str(),
        strlen((*nonCompleteFilesNames)[i].c_str())));
  }
}

CompressorStatus::ErrorCode
Compressor::listArchiveContents(
    const QString &iFileName, vector<FilesTable::FileInfo> * const contents) {

  blocksTable.clean();
  unsigned int nextId = 1;

  if (contents) {
    contents->clear();
    contents->reserve(1000);
  }

  totalProcessingTime = 0;
  decodedDataSize = 0;
  currReadBytesCount = 0;
  encodedDataSize = 0;
  error = CompressorStatus::SUCCESS;

  QFile fin(iFileName);
  if (!fin.open(QIODevice::ReadOnly)) {
    error = CompressorStatus::INPUT_FILE_OPEN_ERROR;
    showInfo(error);
    return error;
  }

  block = new DataBlock();
  DataBlockHeader * header = block->getHeader();
  encodedDataSize = fin.size();

  bool stop = false;
  while (!stop) {
    if (status) {
      if (status->getRunStatus() == CompressorStatus::STOP) {
        stop = true;
      }
    }

    clock_t startTime = clock();
    switch (block->read(fin)) {
    case FILE_END:
      stop = true;
      continue;

    case FILE_BROKEN:
    {
      error = CompressorStatus::INPUT_FILE_CORRUPTED;

      unsigned id = blocksTable.getId(header);
      id = id ? id : nextId++;
      showInfo(error, header->getFileName(), id);

      if (contents) {
        //Add to archive contents broken 1-block-size file`s info
        FilesTable::FileInfo fileInfo;
        fileInfo.corrupted = true;
        fileInfo.fileName = header->getFileName();
        contents->push_back(fileInfo);
      }
      continue;
    }

    case HEADER_CORRUPTED:
    {
      error = CompressorStatus::INPUT_FILE_CORRUPTED;
      showInfo(error);
      continue;
    }

    case FILE_TOO_SMALL:
    {
      error = CompressorStatus::INPUT_FILE_CORRUPTED;
      showInfo(error);
      delete block;
      return error;
    }

    default:
      break;
    }

    currReadBytesCount += header->getEncodedDataSize() + HEADER_SIZE;

    clock_t stoptTime = clock();
    totalProcessingTime += stoptTime - startTime;

    showDecodingProgress(header->getFileName(),
        speed(header->getEncodedDataSize(), stoptTime - startTime));

    switch (blocksTable.add(header, nextId)) {
    case FIRST_AND_LAST_RECIEVED_BLOCK:
      blocksTable.remove(header);
      showInfo(CompressorStatus::INPUT_FILE_UNCORRUPTED,
          header->getFileName(), nextId++);
      break;

    case FIRST_RECIEVED_BLOCK:
      showInfo(CompressorStatus::PROCEED, header->getFileName(), nextId++);
      break;

    case ALL_BLOCKS_RECIEVED:
      showInfo(CompressorStatus::INPUT_FILE_UNCORRUPTED,
          header->getFileName(), blocksTable.getId(header));
      blocksTable.remove(header);
      break;

    case BLOCK_OUT_OF_RANGE:
    case BLOCK_ALREADY_RECIEVED:
      error = CompressorStatus::INPUT_FILE_CORRUPTED;
      showInfo(error);
      delete block;
      return error;
      break;

    default:
      break;
    }
  }

  fin.close();
  delete block;

  vector<string> * brokenFilesNames = blocksTable.getNonCompleteFilesNames();

  if (brokenFilesNames)
    for (vector<string>::iterator i = brokenFilesNames->begin();
         i != brokenFilesNames->end(); ++i) {
      showInfo(CompressorStatus::INPUT_FILE_CORRUPTED, i->c_str(),
          blocksTable.getId(*i));
    }

  if (contents) {
    vector<FilesTable::FileInfo> *partialArchiveContents =
        blocksTable.getArchiveContent();
    contents->insert(contents->end(), partialArchiveContents->begin(),
        partialArchiveContents->end());
  }

  return error;
}
