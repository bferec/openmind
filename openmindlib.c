/* openmindlib.c	*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "openmindlib.h"


int lineNumber;	/* current line number */
int charNumber;	/* current char number */

char msgerror[ MAXLENGTH_STRING + 1 ];

/* -------------------------------------------------------------*/
/* mots cles ne pouvant être utilises en tant que variable	*/
/* -------------------------------------------------------------*/
char keywords[KEYWORDS_COUNT] [256] = {"true","false","create","entity", "property","name","identity","auto","name","unique","exit","quit" };




/* -----------------------------------------------------*/
/* generation d'un nombre aletoire entre deux bornes	*/
/* -----------------------------------------------------*/
int randomize(int min, int max)
{
	int result;
	srand( (unsigned) clock() );
	result = rand()%(max-min) +min;

    return result;

}
/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
void yyerror(const char* msg) 
{
	fprintf( stderr, "Error line [%4.4d] :  %s\n", lineNumber , msg  );
}

/* -----------------------------------------------------*/
/* generation d'un guid à la mode microsoft		*/
/* -----------------------------------------------------*/
void NewGuid( char * result )
{
/* 8-4-4-4-8	*/
int n[5] ;

	n[0] = randomize(0,INT_MAX );
	n[1] = randomize(0,65535 );
	n[2] = randomize(0,65535 );
	n[3] = randomize(0,65535 );
	n[4] = randomize(0,INT_MAX );

	sprintf(result,"%8.8x-%x-%4.4x-%4.4x-%8.8x",n[0],n[1],n[2],n[3] ,n[4]);
}

/* -----------------------------------------------------*/
/* return string to  lowercase				ù/
/* -----------------------------------------------------*/
char * strlwr( char * s )
{
char * result;
char * begin;

	result  = strdup( s );
	begin = result;
	while( * begin )
	{
		if( isupper( * begin ) )
		{
			* begin = tolower( * begin );
		}
		begin ++;
	}
	return result;
}

/* -----------------------------------------------------*/
/* return string to  uppercase				ù/
/* -----------------------------------------------------*/
char * strupr( char * s )
{
char * result;
char * begin;

	result  = strdup( s );
	begin = result;
	while( * begin )
	{
		if( islower( * begin ) )
		{
			* begin = toupper( * begin );
		}
		begin ++;
	}
	return result;
}

/* -----------------------------------------------------*/
/* find a keyword of fdl in list			*/
/* -----------------------------------------------------*/
char * findkeyword( char * onekeyword )
{
char * result ;
int i;

	onekeyword = strlwr( onekeyword );

	result = (char *) NULL;

	for ( i = 0 ; i < KEYWORDS_COUNT ; i++ )
	{
		if( ! strcmp( onekeyword , keywords[i] ) )
		{
			result = keywords[i];
			break;
		}
	}
	return result;
	fprintf( stderr , "TROUVE MOT CLE : [%d]\n" , onekeyword == NULL );
}


