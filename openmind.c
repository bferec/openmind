#include <stdio.h>
#include <string.h>

#include "openmindlib.h"

#define DEBUG 0

extern int yydebug;
extern int yyparse();
extern int yylex (void);
extern int lineNumber;
extern int charNumber;

extern FILE * yyin;


int main(int argc , char * * argv) 
{

	if( DEBUG == 0 )
	{	
		fclose( stderr );
		stderr = fopen("/dev/null", "w" );
	}

	

/*	yydebug = 1;	*/

	if(argc > 1 )
	{ 
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

