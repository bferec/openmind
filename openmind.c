#include <stdio.h>

#include "openmindlib.h"

#define DEBUG 1

extern int yydebug;
extern int yyparse();
extern int yylex (void);
extern int lineNumber;

extern FILE * yyin;


int main(int argc , char * * argv) 
{

	#ifdef DEBUG
	#endif

	

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

	/* yydebug = 1; */

	do 
	{ 
		yyparse();
	} while( ! feof(yyin) );


	return 0;
}

