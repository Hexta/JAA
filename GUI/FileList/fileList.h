/* 
 * File:   FileList.h
 * Author: art
 *
 * Created on 14 Март 2011 г., 18:38
 */

#ifndef FILELIST_H
#    define	FILELIST_H

#    include <QTableWidget>
#    include <QDir>

#    include "Compressor/FilesTable/filesTable.h"
#    include "../CompressorThread/compressorThread.h"

class FileList : public QTableWidget
{
    Q_OBJECT
public:
    FileList( );
    virtual ~ FileList( );
    void                setFileList( const QStringList & fileList, QDir & basedir );

public slots:
    void                init( );
    void                setProceedFileStatus( const QString &fileName, unsigned int id );
    void                setFailFileStatus( const QString &fileName, unsigned int id );
    void                setSuccessFileStatus( const QString &fileName, unsigned int id );
    void                setCancelledFilesStatus( const QString &fileName, unsigned int id  );
    void                setCorruptedFileStatus( const QString &fileName, unsigned int id  );
    void                setUnCorruptedFileStatus( const QString &fileName, unsigned int id  );

    void                showInfo( CTCompressorStatus::ErrorCode error, QString fileName, unsigned int id);
private:

    void				initTable( int rowCount, int columnCount );
    QTableWidgetItem*	getItemById( int id );

} ;

inline QTableWidgetItem*	FileList::getItemById( int id )
{
    int index = id - 1;
    if (id > rowCount( ))
        setRowCount( id );

    setItem( index, 0, new QTableWidgetItem( ) );
    setItem( index, 1, new QTableWidgetItem( ) );
    return item( index, 0 );
}

#endif	/* FILELIST_H */

