/* 
 * File:   CompressorThread.cpp
 * Author: art
 * 
 * Created on 17 Март 2011 г., 16:41
 */

#include "compressorThread.h"

CompressorThread::CompressorThread( )
{
	runMode = NONE;
}

CompressorThread::~CompressorThread( ) { }

void
CompressorThread::showProgress( float progress, const QString &fileName, float speed )
{
	emit progressChanged( progress * 100, fileName, speed );
}

void
CompressorThread::compress( )
{
	bool fail;

	status = new CTCompressorStatus;
	status->setCompressorThread( this );
	Compressor compressor( status );

	QStringList relIFileNames;

	for ( QStringList::Iterator i = iFileNames.begin( ); i != iFileNames.end( ); ++i )
		relIFileNames << compressBaseDir.relativeFilePath( *i );

	std::list<Compressor::CoderTypes> sequence = compressSequence.toStdList( );
	switch ( compressor.compress( relIFileNames, iFileNames.count( ), destFileName, blocksize, &sequence ) )
	{
		case CompressorStatus::OUTPUT_FILE_WRITE_ERROR:fail = true;
			break;
		default: fail = false;
			break;
	}

	Compressor::Stat stat;
	compressor.getStat( &stat );

	if ( !fail ) emit statInfo( stat );

	delete status;
}

void
CompressorThread::decompress( )
{
	bool fail;

	status = new CTCompressorStatus;
	status->setCompressorThread( this );
	Compressor compressor( status );

	switch ( compressor.decompress( iFileName, keepBroken ) )
	{
		case CompressorStatus::OUTPUT_FILE_WRITE_ERROR:
		case CompressorStatus::INPUT_FILE_OPEN_ERROR: fail = true;
			break;
		default: fail = false;
			break;
	}

	Compressor::Stat stat;
	compressor.getStat( &stat );
	if ( !fail ) emit statInfo( stat );

	delete status;
}

void
CompressorThread::initCompress( const QStringList &iFileNames, const QString &destFileName, unsigned int blocksize, const QDir &compressBaseDir, const QList< Compressor::CoderTypes> &compressSequence )
{
	this->iFileNames = iFileNames;
	this->destFileName = destFileName;
	this->blocksize = blocksize;
	this->compressBaseDir = compressBaseDir;
	this->compressSequence = compressSequence;

	runMode = COMPRESSING;
}

void
CompressorThread::initDecompress( const QString &iFileName, bool keepBroken )
{
	this->iFileName = iFileName;
	this->keepBroken = keepBroken;

	runMode = DECOMPRESSING;
}

void
CompressorThread::initList( const QString &iFileName )
{
	this->iFileName = iFileName;

	runMode = LIST;
}

void
CompressorThread::list( )
{
	status = new CTCompressorStatus;
	status->setCompressorThread( this );
	Compressor compressor( status );

	compressor.listArchiveContents( iFileName );

	delete status;
}

void
CompressorThread::run( )
{
	switch ( runMode )
	{
		case COMPRESSING: compress( );
			break;
		case DECOMPRESSING: decompress( );
			break;
		case LIST: list( );
			break;
		default:break;
	}
}

void
CompressorThread::showInfo( CompressorStatus::ErrorCode errorCode, const QString &fileName, unsigned int id )
{
	emit info( errorCode, fileName, id );
}

void
CompressorThread::stop( )
{
	status->setRunStatus( CompressorStatus::STOP );
}

/*
 * CompressorThreadCompressorStatus
 */

CTCompressorStatus::CTCompressorStatus( ) : comprThread( NULL ) { }

void
CTCompressorStatus::setCompressorThread( CompressorThread *comprThread )
{
	this->comprThread = comprThread;
}

void
CTCompressorStatus::showProgress( float progress, const QString &fileName, float speed )
{
	comprThread->showProgress( progress, fileName, speed );
}

void
CTCompressorStatus::showInfo( ErrorCode errorCode, const QString &fileName, unsigned int id )
{
	comprThread->showInfo( errorCode, fileName, id );
}