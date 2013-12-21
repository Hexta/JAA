/******************************************************************************
 * Copyright (c) 2011-2013 Artur Molchanov <artur.molchanov@gmail.com>        *
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

#include "fileList.h"
#include "Compressor/FilesTable/filesTable.h"
#include "Compressor/compressor.h"

FileList::FileList() {
  init();
  setColumnWidth(0, 320);
  setColumnWidth(1, 90);
}

FileList::~FileList() { }

void
FileList::init() {
  QTableWidget::clear();
  initTable(0, 2);
}

void
FileList::initTable(int rowCount, int columnCount) {
  setRowCount(rowCount);
  setColumnCount(columnCount);
  setHorizontalHeaderLabels(QStringList() << "File Name" << "Status");
}

void
FileList::setFileList(const QStringList & fileList, QDir & basedir) {
  initTable(fileList.count(), 2);

  for (int i = 0; i < rowCount(); ++i) {
    setItem(i, 0, new QTableWidgetItem(basedir.relativeFilePath(fileList[i])));
    setItem(i, 1, new QTableWidgetItem());
  }
}

void
FileList::setFailFileStatus(const QString &fileName, unsigned int id) {
  QTableWidgetItem *failedFileCell = getItemById(id);

  failedFileCell->setBackgroundColor(Qt::red);
  failedFileCell->setText(fileName);
  item(failedFileCell->row(), failedFileCell->column() + 1)->setBackgroundColor(Qt::red);
  item(failedFileCell->row(), failedFileCell->column() + 1)->setText("Fail!");
}

void
FileList::setProceedFileStatus(const QString &fileName, unsigned int id) {
  QTableWidgetItem *proceedFileCell = getItemById(id);

  proceedFileCell->setBackgroundColor(Qt::yellow);
  proceedFileCell->setText(fileName);
  item(proceedFileCell->row(), proceedFileCell->column() + 1)->setBackgroundColor(Qt::yellow);
  item(proceedFileCell->row(), proceedFileCell->column() + 1)->setText("Proceed...");
}

void
FileList::setSuccessFileStatus(const QString &fileName, unsigned int id) {
  QTableWidgetItem *succesedFileCell = getItemById(id);

  succesedFileCell->setBackgroundColor(Qt::green);
  succesedFileCell->setText(fileName);
  item(succesedFileCell->row(), succesedFileCell->column() + 1)->setBackgroundColor(Qt::green);
  item(succesedFileCell->row(), succesedFileCell->column() + 1)->setText("Success");
}

void
FileList::setCancelledFilesStatus(const QString &fileName, unsigned int id) {
  QTableWidgetItem *cancelledFileCell = getItemById(id);

  cancelledFileCell->setText(fileName);
  cancelledFileCell->setBackgroundColor(Qt::red);
  item(cancelledFileCell->row(), cancelledFileCell->column() + 1)->setBackgroundColor(Qt::red);
  item(cancelledFileCell->row(), cancelledFileCell->column() + 1)->setText("Cancelled");
}

void
FileList::setCorruptedFileStatus(const QString &fileName, unsigned int id) {
  QTableWidgetItem *corruptedFileCell = getItemById(id);

  corruptedFileCell->setText(fileName);
  corruptedFileCell->setBackgroundColor(Qt::red);
  item(corruptedFileCell->row(), corruptedFileCell->column() + 1)->setBackgroundColor(Qt::red);
  item(corruptedFileCell->row(), corruptedFileCell->column() + 1)->setText("Corrupted!");
}

void
FileList::setGoodFileStatus(const QString &fileName, unsigned int id) {
  QTableWidgetItem *corruptedFileCell = getItemById(id);

  corruptedFileCell->setText(fileName);
  corruptedFileCell->setBackgroundColor(Qt::green);
  item(corruptedFileCell->row(), corruptedFileCell->column() + 1)->setBackgroundColor(Qt::green);
  item(corruptedFileCell->row(), corruptedFileCell->column() + 1)->setText("Good");
}

void
FileList::showInfo(CTCompressorStatus::ErrorCode error, QString fileName,
    unsigned int id) {
  if (fileName.isEmpty())
    return;

  switch (error) {
  case CTCompressorStatus::INPUT_FILE_OPEN_ERROR:
    setFailFileStatus(fileName, id);
    break;
  case CTCompressorStatus::SUCCESS:
    setSuccessFileStatus(fileName, id);
    break;
  case CTCompressorStatus::PROCEED:
    setProceedFileStatus(fileName, id);
    break;
  case CTCompressorStatus::INPUT_FILE_CORRUPTED:
    setCorruptedFileStatus(fileName, id);
    break;
  case CTCompressorStatus::INPUT_FILE_UNCORRUPTED:
    setGoodFileStatus(fileName, id);
    break;
  case CTCompressorStatus::CANCELLED:
    setCancelledFilesStatus(fileName, id);
    break;
  default: break;
  }
}
