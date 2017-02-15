/* -----------------------------*/
/* testopenmindConfig.c		*/
/* -----------------------------*/

#include <stdio.h>
#include <string.h>
#include "openmindConfig.h"

void main(int argc , char * * argv )
{
Configuration *c;
	c = loadConfig("");

	printf( "Nombre de cles : %d\n" , c -> nbKeys );

	for( int x = 0 ; x < c -> nbKeys ; x ++ )
	{
		printf( "key: [%s] value: [%s]\n" , c-> items[x].key , c-> items[x].value );
	}
	printf( "bymessage : %s\n" , getConfigValue( c ,  "bymessage" ) );
}

