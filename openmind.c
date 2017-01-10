#include <stdio.h>

#include "openmindlib.h"


extern int yydebug;
extern int yyparse();
extern int yylex (void);
extern int lineNumber;

extern FILE * yyin;


int main(int argc , char * * argv) 
{
char guid[33];

	if(argc>1)
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

