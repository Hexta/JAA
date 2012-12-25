/* 
 * File:   StatInfo.h
 * Author: art
 *
 * Created on 21 Март 2011 г., 14:04
 */

#ifndef STATINFOW_H
#define	STATINFOW_H

#include "QDialog"
#include "Compressor/compressor.h"

class QTableWidget;

class QLabel;

class StatInfoW : public QDialog {

  Q_OBJECT

public:
  struct StatInfo {
    QList< Compressor::CoderTypes> compressSequence;
    unsigned int blockSize;
    off_t inputSize;
    off_t outputSize;
    float speed;
  };
  StatInfoW(QWidget *parent = NULL);
  virtual ~StatInfoW();

public slots:
  void showInfo(StatInfo info);

private:
  QLabel *blockSizeLabel;
  QLabel *inputDataSizeLabel;
  QLabel *outputDataSizeLabel;
  QLabel *ratioLabel;
  QLabel *speedLabel;
  QLabel *encodingSequenceLabel;
  QLabel *encodingSequenceColumnLabel;
};

#endif	/* STATINFOW_H */

