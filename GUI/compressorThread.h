/* 
 * File:   CompressorThread.h
 * Author: art
 *
 * Created on 17 Март 2011 г., 16:41
 */

#ifndef COMPRESSORTHREAD_H
#define	COMPRESSORTHREAD_H

#include <QThread>
#include <QDir>
#include <QVector>

#include "Compressor/compressor.h"
#include "Compressor/FilesTable/filesTable.h"

class QProgressDialog;
class CompressorThread;

class CTCompressorStatus : public CompressorStatus {
public:
  CTCompressorStatus();
  void showProgress(float progress, const QString&, float speed);
  void showInfo(ErrorCode errorCode, const QString &currFileName = "", unsigned int id = 0);
  void setCompressorThread(CompressorThread *comprThread);

private:
  CompressorThread *comprThread;
};

class CompressorThread : public QThread {
  Q_OBJECT

public:
  CompressorThread();
  virtual ~CompressorThread();

  void run();
  void showProgress(float progress, const QString &fileName, float speed);
  void showInfo(CompressorStatus::ErrorCode errorCode, const QString &fileName, unsigned int id);
  void initCompress(const QStringList &iFileNames, const QString &destFileName, unsigned int blocksize, const QDir &compressBaseDir, const QList< Compressor::CoderTypes> &compressSequence);
  void initDecompress(const QString &iFileName, bool keepBroken = false);
  void initList(const QString &iFileName);
  void compress();
  void decompress();
  void list();

public slots:
  void stop();

signals:
  void progressChanged(int progress, QString fileName, float speed);
  void info(CTCompressorStatus::ErrorCode error, QString fileName, unsigned int id);
  void statInfo(Compressor::Stat stat);

private:
  QStringList iFileNames;
  QString iFileName;
  QString destFileName;
  unsigned int blocksize;
  QDir compressBaseDir;
  bool keepBroken;
  QList< Compressor::CoderTypes> compressSequence;
  CTCompressorStatus *status;

  enum Mode {
    NONE, COMPRESSING, DECOMPRESSING, LIST
  } runMode;
};

#endif	/* COMPRESSORTHREAD_H */

