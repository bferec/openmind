/* -------------------------------------------------------------*/
/* openmindvarlist.c						*/
/* -------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "openmindlib.h"
#include "entity.h"
#include "openmindvalue.h"
#include "openmindvarlist.h"

/* -----------------------------------------------------*/
/* liste des variables					*/
/* -----------------------------------------------------*/
variable_node * var_list ;



/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
void dumpvarNode( variable_node * n) 
{
	if( n )
	{
		fprintf( stdout , "variable node %s\n" , n-> v -> ident );
		fprintf( stdout , "a gauche:\n");
		dumpvarNode( n -> left )  ;
		fprintf( stdout , "a droite:\n");
		dumpvarNode( n -> right )  ;
	}
}

/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
void DumpVarList( )
{
	dumpvarNode( var_list );
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
		{
			return oneNode;
			fprintf(stdout , "TROUVE:\n" , oneIdent );
		}

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

	node = find_variable_node(  oneIdent ,  var_list );

	if( node != (variable_node *) NULL )
	{
		result = node -> v;
	}
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
	else if( strcmp(oneNode -> v -> ident , current_NodeTree -> v -> ident ) < 0 )
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
	if( new_VarNode == (variable_node *) NULL )
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
