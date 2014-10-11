/******************************************************************************
 * Copyright (c) 2011-2014 Artur Molchanov <artur.molchanov@gmail.com>        *
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

#ifndef FILELIST_H
#define FILELIST_H

#include "Compressor/FilesTable/filesTable.h"
#include "compressorThread.h"

#include <QTableWidget>
#include <QDir>

class FileList : public QTableWidget {
    Q_OBJECT

public:
    FileList();
    virtual ~FileList();
    void setFileList(const QStringList& fileList, QDir& basedir);

public slots:
    void init();

    void setCancelledFilesStatus(const QString& fileName, unsigned int id);
    void setCorruptedFileStatus(const QString& fileName, unsigned int id);
    void setFailFileStatus(const QString& fileName, unsigned int id);
    void setGoodFileStatus(const QString& fileName, unsigned int id);
    void setProceedFileStatus(const QString& fileName, unsigned int id);
    void setSuccessFileStatus(const QString& fileName, unsigned int id);

    void showInfo(CTCompressorStatus::ErrorCode error, QString fileName, unsigned int id);

private:
    void initTable(int rowCount, int columnCount);
    QTableWidgetItem* getItemById(int id);
};

inline QTableWidgetItem* FileList::getItemById(int id) {
    int index = id - 1;
    if (id > rowCount()) {
        setRowCount(id);

        setItem(index, 0, new QTableWidgetItem());
        setItem(index, 1, new QTableWidgetItem());
    }
    return item(index, 0);
}

#endif /* FILELIST_H */
