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

void * expression_Constante(syntaxTreeNode * oneNode,  constant * oneConstante )
{
	void * result;	
	fprintf( stderr, "constante\n" );
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
void * expression_Variable(syntaxTreeNode * oneNode , variable * oneVariable )
{
	void * result;	
	result = (void *) NULL;
	fprintf( stderr, "Variable\n" );

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
void echo(operator * oneOper) 
{
constant * constante;
variable  * currentVar;

	for( int i = 0 ; i < oneOper -> OperandsCount ; i ++ )
	{
		switch( oneOper->operands[i] -> type )
		{
			case CONSTANT_SYNTAXTREE_NODETYPE:
				
				constante =  & oneOper -> operands[i]-> cste;
				switch( constante -> type )
				{
					case 	INT_CONSTANT_TYPE:
						printf( "%d" , constante -> val.integer_value );
					break;

					case 	FLOAT_CONSTANT_TYPE:
						printf( "%f" , constante -> val.float_value );
					break;

					case	BOOLEEAN_CONSTANT_TYPE:
						printf( "%d" , constante -> val.boolean_value ? "True" : "False" );
					break;

					case 	GUID_CONSTANT_TYPE:
						printf( "%ds" , constante -> val.guid_value );
					break;

					case	STRING_CONSTANT_TYPE:
						printf( "%ds" , constante-> val.string_value );
					break;
				}
			break;

			case IDENTIFIER_SYNTAXTREE_NODETYPE:

				currentVar = & oneOper -> operands[i]-> var;
				switch( currentVar -> type )
				{
					case 	INTEGER_IDENTIFIER_TYPE:
						printf( "%d" , currentVar-> val.integer_value );
					break;

					case 	FLOAT_IDENTIFIER_TYPE:
						printf( "%f" , currentVar -> val.float_value );
					break;

					case	BOOLEAN_IDENTIFIER_TYPE:
						printf( "%d" , currentVar -> val.boolean_value ? "True" : "False" );
					break;

					case 	GUID_IDENTIFIER_TYPE:
						printf( "%ds" , currentVar -> val.guid_value );
					break;

					case	STRING_IDENTIFIER_TYPE:
						printf( "%ds" , currentVar -> val.string_value );
					break;
				}			
			break;
		}
	}
}

/* -------------------------------------*/
/* interpretation d'une operateur	*/
/* -------------------------------------*/
void * expression_Operator( syntaxTreeNode * oneNode )
{
void * result;	
char guid[GUID_LENGTH]; 

	result = (void *) NULL;
	operator * currentOper;
	fprintf( stderr, "Operateur\n" );
	currentOper = & oneNode-> oper;

	switch( currentOper -> type )
	{
		case T_ECHO:
			echo( currentOper );
		break;

		case T_AUTO:

		NewGuid( guid ); result = (void *) guid ;
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

	fprintf( stderr, "expression\n" );

	if( oneNode == (syntaxTreeNode *) NULL )
	{
		return result;	
	}	

	switch( oneNode -> type )
	{
		case CONSTANT_SYNTAXTREE_NODETYPE:
			return expression_Constante( oneNode , & oneNode -> cste );
		break;

		case IDENTIFIER_SYNTAXTREE_NODETYPE:
			return expression_Variable( oneNode , & oneNode -> var );
		break;

		case OPERATOR_SYNTAXTREE_NODETYPE:
			return expression_Operator( oneNode  );
		break;
	}
	return result;
}
