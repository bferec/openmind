/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindEntityList.c			*/
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
#include "openmindPropertyList.h"

#include "debugTools.h"

/* -----------------------------------------------------*/
/* liste des entites					*/
/* -----------------------------------------------------*/
entity_node * entity_list;


/* -----------------------------------------------------*/
/* Memry allocation for entity				*/
/* -----------------------------------------------------*/
entity * allocMemEntity()
{
entity * result;

	result = (entity *) malloc( sizeof( entity ) );
	if( result == NULL )
		yyerror( "Memory allocation for entity impossible\n");

	return result;
}

/* -----------------------------------------------------*/
/* Add entity to list					*/
/* -----------------------------------------------------*/
void addEntityNodeToList( entity_node * oneEntityNode )
{
	if( entity_list !=  (entity_node *) NULL )
	{	
		entity_list-> previous = oneEntityNode;
		oneEntityNode -> next = entity_list ;
		entity_list = oneEntityNode;
	}
	else
	{
		entity_list = oneEntityNode;
		entity_list -> next = entity_list -> previous = (entity_node *) NULL;
	}
}


/*------------------------------------------------------*/
/* free all  content of a given entity			*/
/*------------------------------------------------------*/
void FreeAllContent( entity_node * rootEntity )
{
entity_node * ent;
entity_node * previous;


	previous = (entity_node *) NULL;
	ent = rootEntity;
	
	while( ent )
	{
		previous = ent;
		ent = ent -> next;
	}

	ent = previous;
	
	while( ent )
	{
		free(ent);
		ent = ent -> previous;
	}
}

/*------------------------------------------------------*/
/* free memory of a given entity			*/
/*------------------------------------------------------*/
void FreeMemEntity( entity  * oneEntity )
{

	/* free content list	*/
	FreeAllContent(oneEntity -> content );
	
	/* free property list 	*/
	FreeAllProperties( oneEntity -> properties );

	free( oneEntity );
}



/*------------------------------------------------------*/
/* Delete all entity					*/
/*------------------------------------------------------*/
void ClearEntityList( )
{

entity_node * ent;
entity_node * previous;


	previous = (entity_node *) NULL;
	ent = entity_list;
	
	while( ent )
	{
		FreeMemEntity( ent -> e );
		previous = ent;
		ent = ent -> next;
	}

	ent = previous;
	
	while( ent )
	{
		free(ent);
		ent = ent -> previous;
	}
}



