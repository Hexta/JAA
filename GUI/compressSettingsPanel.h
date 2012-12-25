/* 
 * File:   CompressSettingsPanel.h
 * Author: art
 *
 * Created on 20 Март 2011 г., 18:47
 */

#ifndef COMPRESSSETTINGSPANEL_H
#define	COMPRESSSETTINGSPANEL_H

#include <QWidget>
#include "Compressor/compressor.h"

class QSpinBox;
class QComboBox;

class CompressSettingsPanel : public QWidget {
  Q_OBJECT

public:
  CompressSettingsPanel();
  virtual ~CompressSettingsPanel();

public slots:
  void set(unsigned int blockSize, QList< Compressor::CoderTypes> compressSequence);

signals:
  void settingsChanged(unsigned int blockSize, QList< Compressor::CoderTypes> compressSequence);
  void resetToDefaults(void);

private:
  QSpinBox* blockSizeSpinBox;
  QComboBox *encoder1ComboBox;
  QComboBox *encoder2ComboBox;
  QComboBox *encoder3ComboBox;
  QComboBox *encoder4ComboBox;
  QComboBox *encoder5ComboBox;
  QComboBox *encoder6ComboBox;
  QComboBox *encoder7ComboBox;
  QComboBox *encoder8ComboBox;

  void setupWidgetsConnections();

private slots:
  void get();
  void disableEncoders();

};

#endif	/* COMPRESSSETTINGSPANEL_H */

