/* 
 * File:   codec_BWT.h
 * Author: art
 *
 * Created on 23 Январь 2011 г., 12:47
 */

#ifndef CODEC_BWT_H
#    define	CODEC_BWT_H


#    include "divsuf/divsufsort.h"
#    include "../../../DataBlock/dataBlock.h"
#    include "../../codecAbstract.h"

class Codec_BWT : public virtual Codec_abstract
{
public:
    Codec_BWT( );
    ~ Codec_BWT( );

    void		encode_BWT( DataBlock* inData );
    void	    decode_BWT( DataBlock* inData );
private:
} ;


#endif	/* CODEC_BWT_H */

