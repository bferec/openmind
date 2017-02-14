/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindvarlist.c			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#include "openmindlib.h"
#include "entity.h"
#include "openmindvalue.h"


#include "openmindconstant.h"
#include "operator.h"

#include "openmindvarlist.h"
#include "syntaxtree.h"
#include "debugTools.h"


/* -----------------------------------------------------*/
/* liste des variables					*/
/* -----------------------------------------------------*/
variable_node * var_list ;

/* -----------------------------------------------------*/
/* liste des entites					*/
/* -----------------------------------------------------*/
entity_node * entity_list;
/* -----------------------------------------------------*/
/* liste des proprites					*/
/* -----------------------------------------------------*/
property_node * property_list;

/* -----------------------------------------------------*/
/* parcours recursif de l'arbre	des variables		*/
/* -----------------------------------------------------*/
variable_node * find_variable_node( char * oneIdent )
{
int compare;
variable_node * currentNode;

	currentNode = var_list;
	while( currentNode != NULL )
	{
		/* fprintf( stderr , "recherche : %s - trouvé : %s\n" ,  oneIdent , currentNode-> v -> ident ); */
		compare = strcmp( strupr(oneIdent) , strupr(currentNode-> v -> ident) );

		if( ! compare )  
		{
			break;
		}
		currentNode = currentNode -> next;
	}
	return currentNode;

}

/* -----------------------------------------------------*/
/* find an identifier with ident			*/
/* -----------------------------------------------------*/
variable * find_variable( char * oneIdent )
{
variable * result;
variable_node * node ;


	result = (variable *) NULL;

	node = find_variable_node(  oneIdent );

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
/* allocation memoire pour une variable			*/
/* -----------------------------------------------------*/
variable * allocMemVar()
{
variable * result;

	result = (variable *) malloc( sizeof( variable ) );
	if( result == NULL )
		yyerror( "Memory allocation for variable impossible\n");

	result -> ident = (char *) malloc( MAXLENGTH_STRING + 1 );
	if( result -> ident == NULL )
		yyerror( "Memory allocation for variable identifier impossible\n");

	return result;
}

/* -----------------------------------------------------*/
/* ajout Variable Node dans la liste des variables	*/
/* -----------------------------------------------------*/
void addVarNodeToList( variable_node * oneVariableNode )
{
	if( var_list !=  (variable_node *) NULL )
	{	
		var_list-> previous = oneVariableNode;
		oneVariableNode -> next = var_list ;
		var_list = oneVariableNode;
	}
	else
	{
		var_list = oneVariableNode;
		var_list-> next = var_list-> previous = (variable_node *) NULL;
	}
}

/* -----------------------------------------------------*/
/* liberation memoire pour une variable			*/
/* -----------------------------------------------------*/
void FreeMemVar(variable * oneVariable)
{
	if( oneVariable != NULL )
	{

		if( oneVariable -> ident != NULL )
			free( oneVariable -> ident  );

		if( oneVariable -> type == STRING_IDENTIFIER_TYPE )
		{
			if( oneVariable -> val.string_value != NULL )
				free( oneVariable -> val.string_value  );
		}
		free( oneVariable );
	}
}

/* -----------------------------------------------------*/
/* Delete all elements of a array var.			*/
/* -----------------------------------------------------*/
void ClearVarDimensions( variable * v )
{
variable_node * varNode;
variable_node * previous;
	for( int dim = 0 ; dim < v -> nbDimensions ; dim ++ )
	{
		previous = (variable_node *) NULL;
		varNode = v -> elements[dim];
		while( varNode )
		{
			FreeMemVar( varNode -> v );
			previous = varNode;
			varNode = varNode -> next;
		}

		varNode = previous;
	
		while( varNode )
		{
			free(varNode);
			varNode = varNode -> previous;
		}
	}
}

/* -----------------------------------------------------*/
/* Delete all vars.					*/
/* -----------------------------------------------------*/
void ClearVarList( )
{

variable_node * varNode;
variable_node * previous;


	previous = (variable_node *) NULL;
	varNode = var_list;
	
	while( varNode )
	{
		if( varNode -> v->type == ARRAY_IDENTIFIER_TYPE )
		{
			ClearVarDimensions( varNode -> v );
		}

		FreeMemVar( varNode -> v );
		previous = varNode;
		varNode = varNode -> next;
	}

	varNode = previous;
	
	while( varNode )
	{
		free(varNode);
		varNode = varNode -> previous;
	}
}


/* -----------------------------------------------------*/
/* ajout nouvel identificateur sans valeur/type		*/
/* dans l'arbre						*/
/* -----------------------------------------------------*/
variable * createVar( char * oneIdent )
{
variable_node * new_VarNode;


	new_VarNode = find_variable_node( oneIdent );

	if( new_VarNode == (variable_node *) NULL )
	{
		new_VarNode  = (variable_node *) malloc( sizeof( variable_node ) );

		if( new_VarNode == (variable_node *) NULL )
			yyerror( "Memory allocation for variable_node impossible\n");

		new_VarNode -> next = new_VarNode -> previous = NULL;
		new_VarNode -> v = allocMemVar();

		strcpy( new_VarNode -> v -> ident  , oneIdent );	

		new_VarNode -> v -> type =  UNKNOWN_IDENTIFIER_TYPE;
		new_VarNode -> v -> val.string_value = (char * ) NULL;
		new_VarNode -> v -> elements = (variable_node * *) NULL;
		new_VarNode -> v -> nbDimensions = 0;

		addVarNodeToList( new_VarNode );
	}

	return new_VarNode -> v;		
}



