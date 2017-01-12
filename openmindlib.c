/* parserlib.c	*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "openmindlib.h"


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







