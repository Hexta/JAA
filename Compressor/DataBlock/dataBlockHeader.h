/* 
 * File:   DataBlockHeader.h
 * Author: art
 *
 * Created on 11 Март 2011 г., 17:00
 */

#ifndef DATABLOCKHEADER_H
#    define	DATABLOCKHEADER_H

#    include <stdint.h>
#    include <cstring>
#    include "../CRC/crc.h"
#    include "../private/consts.h"

#    define HEADER_SIZE (448)
#    define HEADER_DATA_SIZE (436)//After Header-CRC data size
#    define MAX_FILENAME_LENGTH (400)

class DataBlockHeader
{
public:
    DataBlockHeader( );
    virtual ~ DataBlockHeader( );

    DataBlockHeader( unsigned char * in_header_data );

    void		setCodecParams( uint32_t codec_params );
    uint32_t	getCodecParams( );

    void		setRAWDataSize( uint32_t RAWDataSize );
    uint32_t	getRAWDataSize( ) const;

    void		setEncodedDataSize( uint32_t encodedDataSize );
    uint32_t	getEncodedDataSize( ) const;

    void		setDecodedDataSize( uint32_t decodedDataSize );
    uint32_t	getDecodedDataSize( ) const;

    void		setId( uint64_t id );
    uint64_t	getId( ) const;

    void		setData( unsigned char *inHeaderData );
    unsigned char * getData( );

    void		setDataCRC( uint32_t crc );
    uint32_t	getDataCRC( );

    uint32_t	calcCRC( );
    void		recordCRC( );
    int			checkCRC( );

    void		setFileName ( const char * fileName );
    char *		getFileName ( );

    void		setPart( const uint32_t part );
    uint32_t	getPart( ) const;

    void		setPartsCount( const uint32_t part );
    uint32_t	getPartsCount( ) const;

    void		setHeaderCRC( uint32_t headerCRC );
    uint32_t	getHeaderCRC( ) const;

    void		setOffset( uint64_t offset );
    uint64_t	getOffset( );

    void		clean( );
    /**
     * Init header of uncompressed data
     * @param offset offset of the begin current block in source file
     * @param in_data_size size of block
     */
    void		initRAW( uint64_t offset, const uint32_t rawDataSize );

private:

    struct HeaderDataType
    {
        uint64_t id;
        uint32_t headerCRC;
        uint64_t offset;
        uint32_t rawDataSize;
        uint32_t decodedDataSize;
        uint32_t encodedDataSize;
        uint32_t encodedDataCRC;
        uint32_t codecParams;
        char	fileName[MAX_FILENAME_LENGTH];
        uint32_t part;
        uint32_t partsCount;

    } __attribute__( ( packed ) ) headerData;

    DataBlockHeader( const DataBlockHeader& );

} ;

#endif	/* DATABLOCKHEADER_H */

