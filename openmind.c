#include <stdio.h>
#include <string.h>

#include "openmindlib.h"

#define DEBUG 1

extern int yydebug;
extern int yyparse();
extern int yylex (void);
extern int lineNumber;
extern int charNumber;

extern FILE * yyin;


char debugFileName[ 256 ];

int main( int argc , char * * argv ) 
{

	if( DEBUG == 1 )
	{	
		fclose( stderr );
		sprintf( debugFileName , "%s.err.txt" , argv[0] );
		stderr = fopen(debugFileName, "w" );
	}

	

	/* yydebug = 1;	 */

	fprintf( stderr , "Fdl...\n");
	if(argc > 1 )
	{ 
		fprintf( stderr , "ouverture de %s...\n" , argv[1] );
		yyin=fopen(argv[1],"r");
	}
	else
	{
		yyin = stdin;
	}

	lineNumber=1;
	charNumber=0;


	do 
	{ 
		yyparse();
	} while( ! feof(yyin) );


	return 0;
}

