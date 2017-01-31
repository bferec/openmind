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
/*------------------------------------------------------*/
entity_node * find_Entity_Node(char * oneguid , char * oneName , BOOL oneUniqueFlag )
{
int compare;

entity_node * currentNode;

	currentNode = entity_list;
	while( currentNode != NULL )
	{
		compare = strcmp( strupr(oneguid) , strupr(currentNode-> e -> guid) );
		if( ! compare )  
		{
			break;
		}

		if( oneUniqueFlag )
		{
			compare = strcmp( strupr(oneName) , strupr(currentNode-> e -> name) );
			if( ! compare )  
			{
				break;
			}			
		}
			
		currentNode = currentNode -> next;
	}
	return currentNode;

}

/*------------------------------------------------------*/
/*------------------------------------------------------*/
entity * createEntity( char * oneguid , char * oneName , BOOL oneUniqueFlag )
{
entity * result ;
entity_node * new_entityNode;
	
	result = NULL;

	new_entityNode = find_Entity_Node(oneguid , oneName , oneUniqueFlag);

	if( new_entityNode == (entity_node *) NULL )
	{
		new_entityNode  = (entity_node *) malloc( sizeof( entity_node ) );
		if( new_entityNode == (entity_node *) NULL )
			yyerror( "Memory allocation for entity_node impossible\n");

		new_entityNode -> next = new_entityNode -> previous = NULL;
		new_entityNode -> e = allocMemEntity();
		strcpy( new_entityNode -> e -> guid , oneguid );
		strcpy( new_entityNode -> e -> name , oneName );
		new_entityNode -> e -> unique_name = oneUniqueFlag;
		new_entityNode -> e -> state = UNKNOWN;
		new_entityNode -> e  -> content = NULL;
		new_entityNode -> e  -> properties = NULL;
		addEntityNodeToList( new_entityNode );
		result = new_entityNode -> e;
	}
	return result;
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



