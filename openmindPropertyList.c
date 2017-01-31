/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindPropertyList.c		*/
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
/* liste des proprietes					*/
/* -----------------------------------------------------*/
property_node * property_list;


/* -----------------------------------------------------*/
/* Memry allocation for property			*/
/* -----------------------------------------------------*/
property * allocMemProperty()
{
property * result;

	result = (property *) malloc( sizeof( property ) );
	if( result == NULL )
		yyerror( "Memory allocation for property impossible\n");

	return result;
}


/* -----------------------------------------------------*/
/* Add property to list					*/
/* -----------------------------------------------------*/
void addpropertyNodeToList( property_node * onePropertyNode )
{
	if( property_list !=  (property_node *) NULL )
	{	
		property_list-> previous = onePropertyNode;
		onePropertyNode -> next = property_list ;
		property_list = onePropertyNode;
	}
	else
	{
		property_list = onePropertyNode;
		property_list -> next = property_list -> previous = (property_node *) NULL;
	}
}

/*------------------------------------------------------*/
/*------------------------------------------------------*/
property_node * find_property_Node(char * oneguid , char * oneName , BOOL oneUniqueFlag )
{
int compare;

property_node * currentNode;

	currentNode = property_list;
	while( currentNode != NULL )
	{
		compare = strcmp( strupr(oneguid) , strupr(currentNode-> p -> guid) );
		if( ! compare )  
		{
			break;
		}

		if( oneUniqueFlag )
		{
			compare = strcmp( strupr(oneName) , strupr(currentNode-> p -> name) );
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
property * createProperty( char * oneguid , char * oneName , BOOL oneUniqueFlag )
{
property_node * new_propertyNode;
	
	new_propertyNode = find_property_Node(oneguid , oneName , oneUniqueFlag);

	if( new_propertyNode == (property_node *) NULL )
	{
		new_propertyNode  = (property_node *) malloc( sizeof( property_node ) );
		if( new_propertyNode == (property_node *) NULL )
			yyerror( "Memory allocation for property_node impossible\n");

		new_propertyNode -> next = new_propertyNode -> previous = NULL;
		new_propertyNode -> p = allocMemProperty();
		strcpy( new_propertyNode -> p -> guid , oneguid );
		strcpy( new_propertyNode -> p -> name , oneName );
		new_propertyNode -> p -> unique_name = oneUniqueFlag;
		addpropertyNodeToList( new_propertyNode );
	}
	return new_propertyNode -> p;
}
/*------------------------------------------------------*/
/* free memory of a given property			*/
/*------------------------------------------------------*/
void FreeMemProperty( property  * oneProperty )
{
	if( oneProperty -> type == STRING_PROPERTY_TYPE )
	{
		if( oneProperty -> val.string_value != NULL )
			free( oneProperty -> val.string_value  );
	}
	if( oneProperty -> type == DATETIME_PROPERTY_TYPE )
	{
		if( oneProperty -> val.datetime_value != NULL )
			free( oneProperty -> val.datetime_value  );
	}
	free( oneProperty );
}


/*------------------------------------------------------*/
/* free all properties of an property			*/
/*------------------------------------------------------*/
void FreeAllProperties( property_node * rootProperty )
{
property_node * prop;
property_node * previous;

	previous = (property_node *) NULL;
	prop = rootProperty;
	
	while( prop )
	{
		previous = prop;
		prop = prop -> next;
	}

	prop = previous;
	
	while( prop )
	{
		free(prop);
		prop = prop -> previous;
	}
}


/*------------------------------------------------------*/
/* Delete all property					*/
/*------------------------------------------------------*/
void ClearPropertyList()
{
property_node * prop;
property_node * previous;


	previous = (property_node *) NULL;
	prop = property_list;
	
	while( prop )
	{
		FreeMemProperty( prop -> p );
		previous = prop;
		prop = prop -> next;
	}

	prop = previous;
	
	while( prop )
	{
		free(prop);
		prop = prop -> previous;
	}
}



