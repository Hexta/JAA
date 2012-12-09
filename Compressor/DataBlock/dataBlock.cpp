/* 
 * File:   dataBlock.cpp
 * Author: art
 * 
 * Created on 21 Январь 2011 г., 19:07
 */

#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include "dataBlock.h"
#include "dataBlockHeader.h"
#include "readerDataBlockHeader.h"

#define MIN_RAW_BLOCK_SIZE (100000)

using namespace std;

/*
 * TODO:setBlockSize*2 <-- !
 */
DataBlock::DataBlock( unsigned int setBlockSize ) : data( new dataT( setBlockSize * 2 ) ),
	dataSize( 0 ), nBytesToRead( setBlockSize ), header( new DataBlockHeader( ) ), outBlock( new dataT( setBlockSize * 2 ) ),
	recoveryMode( false ) { }

DataBlock::DataBlock( ) : data( new vector < unsigned char > ), dataSize( 0 ), nBytesToRead( 0 ),
	header( new DataBlockHeader( ) ), outBlock( NULL ), recoveryMode( false )
{
	data->reserve( MIN_RAW_BLOCK_SIZE );
}

DataBlock::DataBlock( unsigned char *inData ) : data( NULL ), dataSize( 0 ),
	nBytesToRead( 0 ), header( NULL ), outBlock( NULL ), recoveryMode( false )
{
	unsigned char in_header_data[HEADER_SIZE];
	memcpy( in_header_data, inData, HEADER_SIZE );

	header = new DataBlockHeader( in_header_data );
	dataSize = header->getEncodedDataSize( );

	data = new dataT( dataSize );
	data->assign( inData + HEADER_SIZE, inData + HEADER_SIZE + dataSize );
}

DataBlock::~DataBlock( )
{
	if ( header )
		delete header;

	if ( outBlock )
		delete outBlock;

	if ( data )
		delete data;
}

DataBlockHeader *
DataBlock::readRAW( QFile &in )
{
	uint64_t offset = in.pos( );
	data->resize( nBytesToRead );
	dataSize = in.read( ( char* ) data->data( ), nBytesToRead );
	if ( !dataSize )
		return NULL;

	data->resize( dataSize );

	header->initRAW( offset, dataSize );
	recordCRC( );

	return header;
}

int
DataBlock::read( QFile &in )
{
	ReaderDataBlockHeader readerHeader;

	switch ( readerHeader.read( header, in, recoveryMode ) )
	{
		case FILE_END: return FILE_END;
			break;
		case FILE_TOO_SMALL: return FILE_TOO_SMALL;
			break;
		case FILE_BROKEN:
			recoveryMode = true;
			return HEADER_CORRUPTED;
			break;
		default:;
	}

	data->clear( );

	uint32_t origDataSize = header->getEncodedDataSize( );

	data->resize( origDataSize );
	dataSize = in.read( ( char* ) data->data( ), origDataSize );

	if ( ( dataSize != origDataSize ) || ( checkCRC( ) ) )
	{

		return FILE_BROKEN;
	}
	return 0;
}

unsigned char *
DataBlock::getData( )
{
	return data->data( );
}

void
DataBlock::setData( unsigned char* inData, unsigned int inDataSize )
{
	dataSize = inDataSize;
	data->assign( inData, inData + dataSize );
}

void
DataBlock::setData( dataT* inData )
{
	data->assign( inData->begin( ), inData->end( ) );
}

void
DataBlock::write( QFile &out )
{
	recordCRC( );
	getBlock( );
	out.write( ( char* ) outBlock->data( ), outBlock->size( ) );
}

DataBlockHeader *
DataBlock::getHeader( )
{
	return header;
}

dataT *
DataBlock::getBlock( )
{
	outBlock->assign( header->getData( ), header->getData( ) + HEADER_SIZE );
	outBlock->insert( outBlock->end( ), data->begin( ), data->end( ) );

	return outBlock;
}

void
DataBlock::setBlock( unsigned char* inBlock )
{
	unsigned char in_header_data[HEADER_SIZE];
	memcpy( in_header_data, inBlock, HEADER_SIZE );

	header->setData( in_header_data );
	dataSize = header->getEncodedDataSize( );
	data->assign( inBlock + HEADER_SIZE, inBlock + HEADER_SIZE + dataSize );
}

unsigned int
DataBlock::calcCRC( )
{
	unsigned int dataCRC = crc32( data->data( ), dataSize );
	return dataCRC;
}

int
DataBlock::checkCRC( )
{
	if ( calcCRC( ) != header->getDataCRC( ) )
		return -1;
	return 0;
}

void
DataBlock::recordCRC( )
{
	header->setDataCRC( calcCRC( ) );
	header->recordCRC( );
}

int
DataBlock::writeRAW( )
{
	char * oFileName = header ->getFileName( );
	QFile fout( QString::fromUtf8( oFileName, strlen( oFileName ) ) );

	if ( !fout.open( QIODevice::ReadWrite ) )
		return OUTPUT_ERROR;

	fout.seek( header->getOffset( ) );

	fout.write( ( char* ) data->data( ), data->size( ) );
	fout.close( );

	return 0;
}