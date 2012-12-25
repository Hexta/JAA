/* 
 * File:   DecompressSetingsPanel.h
 * Author: art
 *
 * Created on 21 Март 2011 г., 13:10
 */

#ifndef DECOMPRESSSETTINGSPANEL_H
#define	DECOMPRESSSETTINGSPANEL_H

#include <QWidget>
#include "Compressor/compressor.h"

class QCheckBox;

class DecompressSettingsPanel : public QWidget {
  Q_OBJECT

public:
  DecompressSettingsPanel();
  virtual ~DecompressSettingsPanel();

public slots:
  void set(bool keepBroken);

signals:
  void settingsChanged(bool keepBroken);
  void resetToDefaults(void);

private:
  QCheckBox *keepBrokenFilesCheckbox;

  void setupWidgetsConnections();

private slots:
  void get();

};

#endif	/* DECOMPRESSSETTINGSPANEL_H */

