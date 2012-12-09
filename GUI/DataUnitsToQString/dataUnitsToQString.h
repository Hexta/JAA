/* 
 * File:   DataSizeToQString.h
 * Author: art
 *
 * Created on 22 Март 2011 г., 15:46
 */

#ifndef DATAUNITSTOQSTRING_H
#    define	DATAUNITSTOQSTRING_H

#    include <QString>

class DataUnitsToQString
{
public:
	DataUnitsToQString( );
	DataUnitsToQString( const DataUnitsToQString& orig );
	virtual ~ DataUnitsToQString( );
	static QString convertDataSize( off_t dataSize, int prec) ;
	static QString convertDataSpeed( int dataSpeed, int prec) ;
private:

} ;

#endif	/* DATAUNITSTOQSTRING_H */

