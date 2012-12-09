/* 
 * File:   DataBlocksTable.cpp
 * Author: art
 * 
 * Created on 12 Март 2011 г., 9:10
 */

#include "filesTable.h"
#include "../DataBlock/dataBlockHeader.h"

FilesTable::FilesTable( ) : fileBlocksTable( ), brokenFiletable( ), brokenFilesNames( ), archiveContent( ) { }

FilesTable::~FilesTable( ) { }

int
FilesTable::add( DataBlockHeader * inHeader, unsigned int id )
{
	int result = 0;
	
	map< string, FileBlocksInfo >::iterator pos = fileBlocksTable.find( string( inHeader->getFileName( ) ) );

	if ( pos == fileBlocksTable.end( ) )
	{
		FileBlocksInfo blockInfo( inHeader->getPartsCount( ), id );

		result = FIRST_RECIEVED_BLOCK;

		switch ( blockInfo.setRecievedBlock( inHeader->getPart( ) ) )
		{
			case BLOCK_OUT_OF_RANGE:result = BLOCK_OUT_OF_RANGE;
				break;
			case ALL_BLOCKS_RECIEVED:result = ALL_BLOCKS_RECIEVED;
				break;
			case FIRST_AND_LAST_RECIEVED_BLOCK:result = FIRST_AND_LAST_RECIEVED_BLOCK;
				break;
			default:break;
		}

		fileBlocksTable.insert( map< string, FileBlocksInfo >::value_type( inHeader->getFileName( ), blockInfo ) );
	}
	else
	{
		switch ( pos->second.setRecievedBlock( inHeader->getPart( ) ) )
		{
			case BLOCK_OUT_OF_RANGE:result = BLOCK_OUT_OF_RANGE;
				break;
			case ALL_BLOCKS_RECIEVED:result = ALL_BLOCKS_RECIEVED;
				break;
			case FIRST_AND_LAST_RECIEVED_BLOCK:result = FIRST_AND_LAST_RECIEVED_BLOCK;
				break;
			default:break;
		}
	}

	return result;
}

void
FilesTable::clean( )
{
	fileBlocksTable.clear( );
}

unsigned int
FilesTable::getId( DataBlockHeader * inHeader ) const
{
	map< string, FileBlocksInfo >::const_iterator i = fileBlocksTable.find( string( inHeader->getFileName( ) ) );
	if ( i == fileBlocksTable.end( ) )
		return 0;
	return i->second.getId( );
}

unsigned int
FilesTable::getId( string fileName ) const
{
	map< string, FileBlocksInfo >::const_iterator i = fileBlocksTable.find( fileName );
	if ( i == fileBlocksTable.end( ) )
		return 0;
	return i->second.getId( );
}

void
FilesTable::remove( DataBlockHeader * inHeader )
{
	fileBlocksTable.erase( string( inHeader->getFileName( ) ) );
}

map< string, vector <uint32_t> > *
FilesTable::getNonCompleteFilesBlocksInfo( )
{
	brokenFiletable.clear( );
	for ( map< string, FileBlocksInfo >::iterator i = fileBlocksTable.begin( ), end = fileBlocksTable.end( ); i != end; ++i )
		if ( i->second.getNonRecievedBlocksInfo( ) )
			brokenFiletable.insert( make_pair( i->first, *( i->second.getNonRecievedBlocksInfo( ) ) ) );
	return &brokenFiletable;
}

vector<string> *
FilesTable::getNonCompleteFilesNames( )
{
	brokenFilesNames.clear( );

	for ( map< string, FileBlocksInfo >::iterator i = fileBlocksTable.begin( ), end = fileBlocksTable.end( ); i != end; ++i )
		if ( !i->second.complete( ) )
			brokenFilesNames.push_back( i->first );
	if ( brokenFilesNames.empty( ) )
		return NULL;

	return &brokenFilesNames;
}

vector<FilesTable::FileInfo>*
FilesTable::getArchiveContent( )
{
	archiveContent.clear( );
	for ( map< string, FileBlocksInfo >::iterator i = fileBlocksTable.begin( ), end = fileBlocksTable.end( ); i != end; ++i )
	{
		FileInfo info;
		info.fileName = i->first;
		if ( i->second.complete( ) )
			info.corrupted = false;
		else
			info.corrupted = true;
		archiveContent.push_back( info );
	}
	return &archiveContent;
}