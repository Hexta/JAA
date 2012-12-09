/* 
 * File:   DataBlockHeader.cpp
 * Author: art
 * 
 * Created on 11 Март 2011 г., 17:00
 */

#include "dataBlockHeader.h"

DataBlockHeader::DataBlockHeader( ) : headerData( ) { }

DataBlockHeader::~DataBlockHeader( ) { }

DataBlockHeader::DataBlockHeader( unsigned char * in_header_data ) : headerData( )
{
	memcpy( &headerData, in_header_data, HEADER_SIZE );
}

void
DataBlockHeader::setCodecParams( uint32_t codec_params )
{
	headerData.codecParams = codec_params;
}

uint32_t
DataBlockHeader::getCodecParams( )
{
	return headerData.codecParams;
}

void
DataBlockHeader::setRAWDataSize( uint32_t RAWDataSize )
{
	headerData.rawDataSize = RAWDataSize;
}

uint32_t
DataBlockHeader::getRAWDataSize( ) const
{
	return headerData.rawDataSize;
}

void
DataBlockHeader::setEncodedDataSize( uint32_t encodedDataSize )
{
	headerData.encodedDataSize = encodedDataSize;
}

uint32_t
DataBlockHeader::getEncodedDataSize( ) const
{
	return headerData.encodedDataSize;
}

void
DataBlockHeader::setDecodedDataSize( uint32_t decodedDataSize )
{
	headerData.decodedDataSize = decodedDataSize;
}

uint32_t
DataBlockHeader::getDecodedDataSize( ) const
{
	return headerData.decodedDataSize;
}

void
DataBlockHeader::setId( uint64_t id )
{
	this->headerData.id = id;
}

uint64_t
DataBlockHeader::getId( ) const
{
	return headerData.id;
}

unsigned char *
DataBlockHeader::getData( )
{
	return ( unsigned char* ) &headerData;
}

void
DataBlockHeader::setData( unsigned char *inHeaderData )
{
	memcpy( &headerData, inHeaderData, HEADER_SIZE );
}

void
DataBlockHeader::clean( )
{
	memset( &headerData, 0, HEADER_SIZE );
}

void
DataBlockHeader::setDataCRC( uint32_t crc )
{
	headerData.encodedDataCRC = crc;
}

uint32_t
DataBlockHeader::getDataCRC( )
{
	return headerData.encodedDataCRC;
}

void
DataBlockHeader::recordCRC( )
{
	setHeaderCRC( calcCRC( ) );
}

int
DataBlockHeader::checkCRC( )
{
	if ( calcCRC( ) != getHeaderCRC( ) )
		return -1;
	return 0;
}

void
DataBlockHeader::setFileName( const char * fileName )
{
	strncpy( headerData.fileName, fileName, MAX_FILENAME_LENGTH );
}

char *
DataBlockHeader::getFileName( )
{
	return headerData.fileName;
}

void
DataBlockHeader::setPart( const uint32_t part )
{
	headerData.part = part;
}

uint32_t
DataBlockHeader::getPart( ) const
{
	return headerData.part;
}

void
DataBlockHeader::setPartsCount( const uint32_t partsCount )
{
	headerData.partsCount = partsCount;
}

uint32_t
DataBlockHeader::getPartsCount( ) const
{
	return headerData.partsCount;
}

uint32_t
DataBlockHeader::calcCRC( )
{
	getData( );
	uint32_t headerCRC = crc32( ( unsigned char * ) ( &headerData.offset ), HEADER_DATA_SIZE );
	return headerCRC;
}

void
DataBlockHeader::setHeaderCRC( uint32_t headerCRC )
{
	this->headerData.headerCRC = headerCRC;
}

uint32_t
DataBlockHeader::getHeaderCRC( ) const
{
	return headerData.headerCRC;
}

void
DataBlockHeader::setOffset( uint64_t offset )
{
	headerData.offset = offset;
}

uint64_t
DataBlockHeader::getOffset( )
{
	return headerData.offset;
}

void
DataBlockHeader::initRAW( uint64_t offset, const uint32_t rawDataSize )
{
	memset( &headerData, 0, HEADER_SIZE );
	headerData.id = RAW_ID;
	headerData.decodedDataSize = rawDataSize;
	headerData.encodedDataSize = rawDataSize; //входной и выходной размер равны
	headerData.offset = offset;
}