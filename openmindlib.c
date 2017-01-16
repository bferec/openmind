/* parserlib.c	*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "openmindlib.h"

#define KEYWORDS_COUNT 12

char msgerror[ 256 ];

/* -------------------------------------------------------------*/
/* mots cles ne pouvant être utilises en tant que variable	*/
/* -------------------------------------------------------------*/
char keywords[KEYWORDS_COUNT] [256] = {"true","false","create","entity", "property","name","identity","auto","name","unique","exit","quit" };


/* -----------------------------------------------------*/
/* liste des variables					*/
/* -----------------------------------------------------*/
variable_node * var_list ;

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

/* -----------------------------------------------------*/
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



/* -----------------------------------------------------*/
/* parcours recursif de l'arbre	des variables		*/
/* -----------------------------------------------------*/
variable_node * find_variable_node( char * oneIdent ,  variable_node * oneNode )
{
int compare;


	if( oneNode != NULL )
	{
		compare = strcmp( oneIdent , oneNode-> v -> ident);

		if( ! compare )  
			return oneNode;

		if( compare < 0 )
			return find_variable_node(oneIdent , oneNode -> left );

		return find_variable_node(oneIdent , oneNode -> right );
	}

	return oneNode;

}

/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
variable * find_variable( char * oneIdent )
{
variable * result;
variable_node * node ;


	result = (variable *) NULL;

	node = find_variable_node(  oneIdent ,  var_list );

	if( node != (variable_node *) NULL )
		result = node -> v;

	return result;
}

/* -----------------------------------------------------*/
/* return 1 if identifier = fdl keyword 		*/
/* -----------------------------------------------------*/
BOOL  check_ident( char * oneident )
{
BOOL invalid_result;

	invalid_result =  findkeyword( oneident ) != NULL ;

return invalid_result;
}

/* -----------------------------------------------------*/
/* ajout nouveau noeud 					*/
/* dans l'arbre	des identifiers				*/
/* ident inférieur à gauche				*/
/* ident superieur à droite				*/
/* -----------------------------------------------------*/
void addVarNode( variable_node * oneNode , variable_node * tree )
{
	if( tree == NULL )
	{
		tree = 	oneNode;
	}
	else if( strcmp(oneNode ->v -> ident , tree -> v -> ident ) < 0 )
	{
		tree -> left  = oneNode;
	}
	else
		tree -> right = oneNode;
}

/* -----------------------------------------------------*/
/* ajout nouvel identificateur sans valeur/type		*/
/* dans l'arbre						*/
/* -----------------------------------------------------*/
variable * createVar( char * oneIdent )
{
variable * result ;
variable_node * newvarnode;

	newvarnode = find_variable_node( oneIdent ,  var_list);
	if( newvarnode ==  (variable_node *) NULL )
	{
		newvarnode  = (variable_node *) malloc( sizeof( variable_node ) );
		newvarnode -> v = (variable *) malloc( sizeof( variable ) );
		newvarnode -> v -> ident = malloc( strlen( oneIdent ) + 1 );
		strcpy( newvarnode -> v -> ident  , oneIdent );	
		newvarnode -> v -> type =  UNKNOWN;
		newvarnode -> left = newvarnode -> right = (variable_node *) NULL;
		addVarNode( newvarnode , var_list );
	}
	result  = newvarnode -> v;
	
return result;		
}



