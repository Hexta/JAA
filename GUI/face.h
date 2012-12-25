/* 
 * File:   face.h
 * Author: art
 *
 * Created on 7 Март 2011 г., 22:17
 */

#ifndef _FACE_H
#define	_FACE_H

#include <QFileDialog>
#include "compressorThread.h"

#include <QMainWindow>

class FileList;
class QProgressDialog;
class CompressSettingsPanel;
class DecompressSettingsPanel;
class StatInfoW;

namespace Ui {

class face;
}

class Face : public QMainWindow {
  Q_OBJECT
public:

  Face();
  virtual ~Face();

public slots:
  void about();
  void selectFilesToCompress();
  void selectFileToDecompress();
  void compress();
  void decompress();
  void listArchiveContents();
  void displayCompressStatus(int progress, QString fileName, float speed);
  void displayDecompressStatus(int progress, QString fileName, float speed);
  void displayListStatus(int progress, QString fileName, float speed);
  void showInfo(CTCompressorStatus::ErrorCode error, QString fileName);
  void showCompressStatInfo(Compressor::Stat stat);
  void showDecompressStatInfo(Compressor::Stat stat);
  void setCompressSettings(unsigned int blockSize, QList< Compressor::CoderTypes> compressSequence);
  void setDecompressSettings(bool keepBrokenFiles);

private:
  CompressSettingsPanel *compressSettingsPanel;
  DecompressSettingsPanel *decompressSettingsPanel;

  StatInfoW *statInfoW;

  CompressorThread *compressThread;
  CompressorThread *decompressThread;
  CompressorThread *listArchiveThread;
  Ui::face *widget;
  Compressor *compressor;

  QToolBar *actionToolBar;

  FileList *filelist;

  QStringList sourceFileNames;
  QStringList encodedfileNames;

  QString destFileName;
  QString destDirName;

  QDir compressBaseDir;
  QDir decompressBaseDir;

  QDockWidget *compressSettingsDock;
  QDockWidget *decompressSettingsDock;

  QAction *selectFilesToCompressAction;
  QAction *selectFileToDecompressAction;
  QAction *compressAction;
  QAction *decompressAction;
  QAction *exitAction;
  QAction *aboutAction;
  QAction *aboutQtAction;

  QMenu *fileMenu;
  QMenu *helpMenu;

  QProgressDialog *compressingProgressDialog;
  QProgressDialog *decompressingProgressDialog;
  QProgressDialog *listArchiveContentsProgressDialog;

  bool brokenFileWarningShown;

  QList< Compressor::CoderTypes> compressSequence;
  unsigned int blockSize;
  bool keepBrokenFiles;

  void createActions();
  void createToolBars();
  void createMenus();
  void setupWidgetsConnections();
  void activateCompressMode();
  void activateDecompressMode();

private slots:
  void initSettings();
};


#endif	/* _FACE_H */
