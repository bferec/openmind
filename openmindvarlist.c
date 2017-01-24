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
void dumpvarNode( variable_node * oneVariableNode) 
{
	if( oneVariableNode )
	{
		fprintf( stdout , "variable node %s\n" , oneVariableNode-> v -> ident );
	}
}

/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
void DumpVarList( )
{
	fprintf( stderr , "\nDUMP:\n");


variable_node * n;
	n = var_list;
	while( n )
	{
		dumpvarNode( n );
		n= n -> next;	
	}
	fprintf( stderr , "\nFIN DU DUMP:\n");
}

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
/* libartion memoire pour une variable			*/
/* -----------------------------------------------------*/
void FreeMemVar(variable * oneVariable)
{
	if( oneVariable != NULL )
	{
		if( oneVariable -> ident != NULL )
			free( oneVariable -> ident  );

		if( oneVariable -> val.guid_value != NULL )
			free( oneVariable -> val.guid_value  );

		if( oneVariable -> val.string_value != NULL )
			free( oneVariable -> val.string_value  );

		free( oneVariable );
	}
}


/* -----------------------------------------------------*/
/* ajout Variable Node dans la liste des variables	*/
/* -----------------------------------------------------*/
void addVarNodeToList( variable_node * oneVariableNode )
{
	if( var_list !=  (variable_node *) NULL )
	{	
		/* fprintf( stderr , "insertion de [%s] dans liste variable contenant [%s] ...\n" , oneVariableNode->v->ident , var_list->v->ident );  */
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
/* -----------------------------------------------------*/
void removeVarNodeFromList( variable_node * oneVariableNode )
{
variable_node * currentVarNode;

	if( oneVariableNode ==  var_list )
	{	
		var_list = var_list -> next;
		var_list -> previous = NULL;
	}
	else
	{	
		if( oneVariableNode -> next != NULL )
		{
			(oneVariableNode -> next) -> previous = oneVariableNode -> previous;
		}
		if( currentVarNode -> previous != NULL )
		{
			(oneVariableNode -> previous) -> next  = oneVariableNode -> next;
		}
		
	}
}
/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
void deleteVar( char * oneIdent )
{
variable_node * varNodeToDelete;

	varNodeToDelete = find_variable_node( oneIdent );
	if( varNodeToDelete != (variable_node *) NULL )
	{
		FreeMemVar(varNodeToDelete -> v );
		removeVarNodeFromList( varNodeToDelete );
	}
}

/* -----------------------------------------------------*/
/* ajout nouvel identificateur sans valeur/type		*/
/* dans l'arbre						*/
/* -----------------------------------------------------*/
variable * createVar( char * oneIdent )
{
variable * result ;
variable_node * new_VarNode;

/*
	DumpVarList( );
*/
	new_VarNode = find_variable_node( oneIdent );

	if( new_VarNode == (variable_node *) NULL )
	{
		/* fprintf( stderr , "non trouvee => creation ...\n"); */
		new_VarNode  = (variable_node *) malloc( sizeof( variable_node ) );

		if( new_VarNode == (variable_node *) NULL )
			yyerror( "Memory allocation for variable_node impossible\n");
		/* fprintf( stderr , "Allocation memoire de la variable dans le noeud ...\n"); */
		new_VarNode -> v = allocMemVar();
		/* fprintf( stderr , "mise en place identificateur [%s] de la variable dans le noeud ...\n" , oneIdent ); */
		strcpy( new_VarNode -> v -> ident  , oneIdent );	
		/* fprintf( stderr , "mise en place du type de la variable dans le noeud ...\n"); */
		new_VarNode -> v -> type =  UNKNOWN_IDENTIFIER_TYPE;
		/* fprintf( stderr , "ajout du noeud dans la liste...\n"); */
		addVarNodeToList( new_VarNode );
	}
	result = new_VarNode -> v;
	/* fprintf( stderr , "variable crée...\n"); */
return result;		
}




