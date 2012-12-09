/* 
 * File:   codec_MTF.h
 * Author: art
 *
 * Created on 23 Январь 2011 г., 20:50
 */

#ifndef CODEC_MTF_H
#    define	CODEC_MTF_H

#    include "../../../DataBlock/dataBlock.h"
#    include "../../codecAbstract.h"

class Codec_MTF : public virtual Codec_abstract
{
public:
    Codec_MTF( );
    virtual ~ Codec_MTF( );

    void		decode_MTF( DataBlock* inData );
    void		encode_MTF( DataBlock* inData );
private:
    int			mtf( int c );
    int			get_mtf_c( int i );
    
    typedef struct  mtf_list
	{
		int c;
		struct mtf_list *prev;
		struct mtf_list *next;
	} mtf_list_t;

	mtf_list_t	*p, *head, *tail, *table;

	void	    init_mtf( int tsize );

} ;

inline int
Codec_MTF::mtf( int c )
{
    int i = 0;

    /* find c. */
    p = head;
    while ( p->c != c )
    {
        ++ i;
        p = p->next;
    }
    /* move-to-front. */
    if ( p->prev )
    {
        if ( p->next )
        {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        else
        {
            p->prev->next = NULL;
            tail = p->prev;
        }
        p->prev = NULL;
        p->next = head;
        head->prev = p;
        head = p;
    } /* front, don't MTF! */

    return i;
}

inline int
Codec_MTF::get_mtf_c( int i )
{
    /* find c. */
    p = head;
    while ( i -- )
    {
        p = p->next;
    }
    /* move-to-front. */
    if ( p->prev )
    {
        if ( p->next )
        {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        else
        {
            p->prev->next = NULL;
            tail = p->prev;
        }
        p->prev = NULL;
        p->next = head;
        head->prev = p;
        head = p;
    }
    return p->c;
}

#endif	/* CODEC_MTF_H */

