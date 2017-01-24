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
		dumpvarNode( n -> next )  ;
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

variable_node * currentNode;

	currentNode = oneNode;
	while( currentNode != NULL )
	{
		
		compare = strcmp( oneIdent , currentNode-> v -> ident);

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
		new_VarNode -> v -> ident = malloc( MAXLENGTH_STRING + 1 );
		strcpy( new_VarNode -> v -> ident  , oneIdent );	
		new_VarNode -> v -> type =  UNKNOWN_IDENTIFIER_TYPE;

		new_VarNode -> next = var_list-> next ;
		if( var_list-> next  != NULL)
			 ( var_list-> next ) -> previous = new_VarNode;
		var_list = new_VarNode;
	}
	result = new_VarNode -> v;
	
return result;		
}




