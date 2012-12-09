/* 
 * File:   Codec_RLE.cpp
 * Author: art
 * 
 * Created on 31 Январь 2011 г., 14:24
 */

#include "codecRLE.h"

Codec_RLE::Codec_RLE( ) { }

Codec_RLE::~Codec_RLE( ) { }

void
Codec_RLE::decode_RLE( DataBlock* inData )
{
	initDecoder( inData );

	dataT buffer;
	buffer.reserve( decodedDataSize );

	int currChar, prevChar;
	prevChar = 0xFFFFFF;

	unsigned char count;

	unsigned int i = 0;
	while ( i < encodedDataSize )
	{
		currChar = data[i++];

		buffer.push_back( currChar );

		/* check for run */
		if ( currChar == prevChar )
		{
			count = data[i++];
			while ( count-- > 0 )
			{
				buffer.push_back( currChar );
			}

			prevChar = 0xFFFFFF;
		}
		else
		{
			/* no run */
			prevChar = currChar;
		}
	}

	inData->setBlock( buffer.data( ) );
}

void
Codec_RLE::encode_RLE( DataBlock* inData )
{
	initEncoder( inData );

	/*
	 * TODO:
	 * RLE overhead?!
	 */

	encodedDataSize = decodedDataSize * 2; //<---

	dataT buffer;
	buffer.reserve( encodedDataSize );

	int currChar = EOF, prevChar = EOF; /* current and previous characters */
	unsigned char count;
	count = 0;

	unsigned int index = 0;

	while ( index != decodedDataSize )
	{
		currChar = data[index++];
		buffer.push_back( currChar );

		/* check for run */
		if ( currChar == prevChar )
		{
			/* we have a run.  count run length */
			count = 0;

			while ( index != decodedDataSize )
			{
				currChar = data[index++];
				if ( currChar == prevChar )
				{
					++count;

					if ( count == UCHAR_MAX )
					{
						/* count is as long as it can get */
						buffer.push_back( count );

						/* force next char to be different */
						prevChar = EOF;
						break;
					}
				}
				else
				{
					/* run ended */
					buffer.push_back( count );
					buffer.push_back( currChar );

					prevChar = currChar;
					break;
				}
				if ( index == decodedDataSize )
				{
					buffer.push_back( count );
					break;
				}
			}
		}
		else
		{
			/* no run */
			prevChar = currChar;
		}
	}
	encodedDataSize = buffer.size( );
	inData->setData( buffer.data( ), buffer.size( ) );

	recordOutHeader( inData->getHeader( ), RLE_ID );
}
