/* 
 * File:   Codec.h
 * Author: art
 *
 * Created on 5 Февраль 2011 г., 19:44
 */

#ifndef CODEC_H
#define	CODEC_H

#include "Codecs/BWT/codecBWT.h"
#include "Codecs/MTF/codecMTF.h"
#include "Codecs/RLE/codecRLE.h"
#include "Codecs/HUFF/codecHUFF.h"

class Codec : public virtual Codec_BWT, public virtual Codec_HUFF, public virtual Codec_MTF, public virtual Codec_RLE
{
public:
    Codec();
    virtual ~Codec();
private:

} ;

#endif	/* CODEC_H */
