/* 
 * File:   codec_HUFF.h
 * Author: art
 *
 * Created on 24 Январь 2011 г., 20:32
 */

#ifndef CODEC_HUFF_H
#    define	CODEC_HUFF_H

#    include "../../../DataBlock/dataBlock.h"
#    include "../../codecAbstract.h"

class Codec_HUFF : public virtual Codec_abstract
{
public:
    Codec_HUFF( );
    virtual ~ Codec_HUFF( );

    void        decode_HUFF( DataBlock* inData );
    void		encode_HUFF( DataBlock* inData );
private:

} ;

#endif	/* CODEC_HUFF_H */

