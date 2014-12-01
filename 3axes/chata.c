#include "chata.h"

unsigned short positive_chattering( int swi, int switc )
{
	static unsigned short sw[ 4 ][ 6 ] = {	{ OFF , OFF , OFF , OFF , OFF , OFF },
																	{ OFF , OFF , OFF , OFF , OFF , OFF },
																	{ OFF , OFF , OFF , OFF , OFF , OFF },
																	{ OFF , OFF , OFF , OFF , OFF , OFF },
																};

	sw[ switc ][ 5 ] = sw[ switc ][ 4 ];
	sw[ switc ][ 4 ] = sw[ switc ][ 3 ];
	sw[ switc ][ 3 ] = sw[ switc ][ 2 ];
	sw[ switc ][ 2 ] = sw[ switc ][ 1 ];
	sw[ switc ][ 1 ] = sw[ switc ][ 0 ];
	sw[ switc ][ 0 ] = swi;

	if ( sw[ switc ][ 0 ] == ON && sw[ switc ][ 1 ] == ON && sw[ switc ][ 2 ] == ON && sw[ switc ][ 3 ] == ON && sw[ switc ][ 4 ] == ON && sw[ switc ][ 5 ] == OFF ){
		return ( EDGE_UP );

	}else if( sw[ switc ][ 0 ] == OFF && sw[ switc ][ 1 ] == OFF && sw[ switc ][ 2 ] == OFF && sw[ switc ][ 3 ] == OFF && sw[ switc ][ 4 ] == OFF && sw[ switc ][ 5 ] == ON ){
		return ( EDGE_DOWN );
	}

	return 0;
}

unsigned short negative_chattering( int swi , int switc)
{
	static unsigned short sw[ 4 ][ 6 ] = {	{ ON , ON , ON , ON , ON , ON },
																{ ON , ON , ON , ON , ON , ON },
																{ ON , ON , ON , ON , ON , ON },
																{ ON , ON , ON , ON , ON , ON },
															};

	sw[ switc ][ 5 ] = sw[ switc ][ 4 ];
	sw[ switc ][ 4 ] = sw[ switc ][ 3 ];
	sw[ switc ][ 3 ] = sw[ switc ][ 2 ];
	sw[ switc ][ 2 ] = sw[ switc ][ 1 ];
	sw[ switc ][ 1 ] = sw[ switc ][ 0 ];
	sw[ switc ][ 0 ] = swi;

	if( sw[ switc ][ 0 ] == OFF && sw[ switc ][ 1 ] == OFF && sw[ switc ][ 2 ] == OFF && sw[ switc ][ 3 ] == OFF && sw[ switc ][ 4 ] == OFF && sw[ switc ][ 5 ] == ON ){
		return ( EDGE_DOWN );

	}else if( sw[ switc ][ 0 ] == ON && sw[ switc ][ 1 ] == ON && sw[ switc ][ 2 ] == ON && sw[ switc ][ 3 ] == ON && sw[ switc ][ 4 ] == ON && sw[ switc ][ 5 ] == OFF ){
		return ( EDGE_UP );
	}

	return 0;
}
