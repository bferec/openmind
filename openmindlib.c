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

void yyerror(const char* msg) 
{
	fprintf( stderr, "Erreur ligne [%4.4d] : caractere [%4.4d] [%s]\n", lineNumber , charNumber , msg  );
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
/* find an identifier with ident			*/
/* -----------------------------------------------------*/
variable * find_variable( char * oneIdent )
{
variable * result;
variable_node * node ;


	result = (variable *) NULL;

	fprintf( stderr , "recherche variable...\n" );
	node = find_variable_node(  oneIdent ,  var_list );

	if( node != (variable_node *) NULL )
	{
		result = node -> v;
		fprintf( stderr , "variable trouvée\n" );
	}
	else
		fprintf( stderr , "variable non trouvée\n" );
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
variable_node * addVarNode( variable_node * oneNode , variable_node * current_NodeTree )
{
	if( current_NodeTree == NULL )
	{
		current_NodeTree = oneNode;
	}
	else if( strcmp(oneNode ->v -> ident , current_NodeTree -> v -> ident ) < 0 )
	{
		current_NodeTree -> left = addVarNode( oneNode , current_NodeTree -> left );
	}
	else
		current_NodeTree -> right = addVarNode( oneNode , current_NodeTree -> right );

	return current_NodeTree;
}

/* -----------------------------------------------------*/
/* ajout nouvel identificateur sans valeur/type		*/
/* dans l'arbre						*/
/* -----------------------------------------------------*/
variable * createVar( char * oneIdent )
{
variable * result ;
variable_node * new_VarNode;

	new_VarNode = find_variable_node( oneIdent ,  var_list);
	if( new_VarNode ==  (variable_node *) NULL )
	{
		new_VarNode  = (variable_node *) malloc( sizeof( variable_node ) );
		new_VarNode -> v = (variable *) malloc( sizeof( variable ) );
		new_VarNode -> v -> ident = malloc( strlen( oneIdent ) + 1 );
		strcpy( new_VarNode -> v -> ident  , oneIdent );	
		new_VarNode -> v -> type =  UNKNOWN_IDENTIFIER_TYPE;
		new_VarNode -> left = new_VarNode -> right = (variable_node *) NULL;
		var_list = addVarNode( new_VarNode , var_list );
	}
	result = new_VarNode -> v;
	
return result;		
}

/* -----------------------------------------------------*/
/* return float ou int value of identifier according	*/
/* to type						*/
/* -----------------------------------------------------*/
double getValueNumber( numberValue v )
{
double result;
	result = 0;
	switch( v.number_type )
	{
		case INTEGER_NUMBER_TYPE:
			result = (double) v.integer_value;
		break;

		case FLOAT_NUMBER_TYPE:
			result = (double) v.float_value;
		break;
	}

	return result;
}
