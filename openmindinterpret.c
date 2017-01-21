/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindInterpret.c			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "openmindlib.h"
#include "openmind.tab.h"

/* -------------------------------------*/
/* interpretation d'une constante	*/
/* -------------------------------------*/

void * expression_Constante( constant * oneConstante )
{
	void * result;	
	switch( oneConstante -> type )
	{
		case INT_CONSTANT_TYPE:

			result = (void *) & oneConstante -> val.integer_value ;
		break;

		case FLOAT_CONSTANT_TYPE:
			result = (void *) & oneConstante -> val.float_value ;
		break;

		case BOOLEEAN_CONSTANT_TYPE:
			result = (void *) & oneConstante -> val.boolean_value ;
		break;

		case GUID_CONSTANT_TYPE:
			result = (void *) & oneConstante -> val.guid_value ;
		break;

		case STRING_CONSTANT_TYPE:
			result = (void *) & oneConstante -> val.string_value ;
		break;
	}

	return result;
}
/* -------------------------------------*/
/* interpretation d'une variable	*/
/* -------------------------------------*/
void * expression_Variable( variable * oneVariable )
{
	void * result;	
	result = (void *) NULL;

	switch( oneVariable -> type )
	{
		case UNKNOWN_IDENTIFIER_TYPE:
			result = (void *) & "#UNKNOWN#" ;
		break;
		
		case INTEGER_IDENTIFIER_TYPE:
			result = (void *) & oneVariable -> val.integer_value ;
		break;

		case FLOAT_IDENTIFIER_TYPE:
			result = (void *) & oneVariable -> val.float_value ;
		break;

		case BOOLEAN_IDENTIFIER_TYPE:
			result = (void *) & oneVariable -> val.boolean_value ;
		break;

		case GUID_IDENTIFIER_TYPE:
			result = (void *) & oneVariable -> val.guid_value ;
		break;

		case STRING_IDENTIFIER_TYPE:
			result = (void *) & oneVariable -> val.string_value ;
		break;

		case ENTITY_IDENTIFIER_TYPE:
		case PROPERTY_IDENTIFIER_TYPE:
		break;
	}

	return result;
}

/* -------------------------------------*/
/* interpretation d'une operateur	*/
/* -------------------------------------*/
void * expression_Operator( operator * oneOper )
{
void * result;	
	result = (void *) NULL;

	switch( oneOper -> type )
	{
		case T_ECHO:

		break;
	}

	return result;
}


/* -------------------------------------*/
/* interpretation d'une expression	*/
/* -------------------------------------*/
void * expression( syntaxTreeNode * oneNode )
{
void * result;

	result =  NULL;

	if( oneNode == (syntaxTreeNode *) NULL )
	{
		return result;	
	}	

	switch( oneNode -> type )
	{
		case CONSTANT_SYNTAXTREE_NODETYPE:
			return expression_Constante( & oneNode -> cste );
		break;

		case IDENTIFIER_SYNTAXTREE_NODETYPE:
			return expression_Variable( & oneNode -> var );
		break;

		case OPERATOR_SYNTAXTREE_NODETYPE:
			return expression_Operator( & oneNode -> oper );
		break;
	}
	return result;
}
