
/* symbol.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "symbol.h"


symbol * symbollist = (symbol *) NULL ;

symbol * putsymbol( char * onename )
{
	symbol * p;
	p = (symbol *) malloc( sizeof(symbol) );
	p -> name = (char *) malloc (strlen(onename) +1 );
	strcpy( p -> name , onename );

	p -> next = (struct symbol *) symbollist;

	symbollist = p;

	return p;
}

symbol * getsymbol(char * onename )
{
symbol * p;
	for( p = symbollist ; p != NULL ; p = (symbol *) p -> next )
	{
		if( ! strcmp( p -> name , onename ) )
			return p;
	}
	return ((symbol *) NULL);
}

