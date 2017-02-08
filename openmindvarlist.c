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

	result -> ident = malloc( MAXLENGTH_STRING + 1 );
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
/* librration memoire pour une variable			*/
/* -----------------------------------------------------*/
void FreeMemVar(variable * oneVariable)
{
	if( oneVariable != NULL )
	{
		// fprintf( stderr , "Free ident of Var [%s]\n" , oneVariable -> ident );
		if( oneVariable -> ident != NULL )
			free( oneVariable -> ident  );

		//if( oneVariable -> type == GUID_IDENTIFIER_TYPE )
		//{
			// fprintf( stderr , "Free guid var space\n" );
			//if( oneVariable -> val.guid_value != NULL )
				//free( oneVariable -> val.guid_value  );
		//}
		if( oneVariable -> type == STRING_IDENTIFIER_TYPE )
		{
			// fprintf( stderr , "Free string var space\n" );
			if( oneVariable -> val.string_value != NULL )
				free( oneVariable -> val.string_value  );
		}
		// fprintf( stderr , "liberation Var\n" );
		free( oneVariable );
	}
}

/* -----------------------------------------------------*/
/* Delete all elements of a array var.			*/
/* -----------------------------------------------------*/
void ClearVarElements( variable * v )
{
variable_node * n;
variable_node * previous;
	previous = (variable_node *) NULL;
	n = v -> elements;
	while( n )
	{
		FreeMemVar( n -> v );
		previous = n;
		n = n -> next;
	}

	n = previous;
	
	while( n )
	{
		free(n);
		n = n -> previous;
	}
}

/* -----------------------------------------------------*/
/* Delete all vars.					*/
/* -----------------------------------------------------*/
void ClearVarList( )
{

variable_node * n;
variable_node * previous;


	previous = (variable_node *) NULL;
	n = var_list;
	
	while( n )
	{
		if( n -> v->type == ARRAY_IDENTIFIER_TYPE )
		{
			ClearVarElements( n -> v );
		}

		FreeMemVar( n -> v );
		previous = n;
		n = n -> next;
	}

	n = previous;
	
	while( n )
	{
		free(n);
		n = n -> previous;
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
		/* fprintf( stderr , "non trouvee => creation ...\n"); */
		new_VarNode  = (variable_node *) malloc( sizeof( variable_node ) );

		if( new_VarNode == (variable_node *) NULL )
			yyerror( "Memory allocation for variable_node impossible\n");

		new_VarNode -> next = new_VarNode -> previous = NULL;

		/* fprintf( stderr , "Allocation memoire de la variable dans le noeud ...\n"); */
		new_VarNode -> v = allocMemVar();

		/* fprintf( stderr , "mise en place identificateur [%s] de la variable dans le noeud ...\n" , oneIdent ); */
		strcpy( new_VarNode -> v -> ident  , oneIdent );	

		/* fprintf( stderr , "mise en place du type de la variable dans le noeud ...\n"); */
		new_VarNode -> v -> type =  UNKNOWN_IDENTIFIER_TYPE;

		new_VarNode -> v -> val.string_value = (char * ) NULL;

		new_VarNode -> v -> elements = (variable_node *) NULL;

		/* fprintf( stderr , "ajout du noeud dans la liste...\n"); */
		addVarNodeToList( new_VarNode );
	}

return new_VarNode -> v;		
}



