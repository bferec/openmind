/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* assignationOperator.c		*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "openmindlib.h"
#include "entity.h"
#include "openmindvalue.h"
#include "openmindvarlist.h"
#include "openmindconstant.h"
#include "operator.h"
#include "syntaxtree.h"
#include "expressions.h"

#include "openmind.tab.h"


/* -------------------------------------*/
/* += interpretation			*/
/* -------------------------------------*/
expression_Value  expression_Operator_T_PLUS_EGAL_SIGN(operator * oneOperatorNode)
{
variable  * currentVar;
expression_Value result ;
expression_Value operandResult ;
float actualValue;

	currentVar = oneOperatorNode -> operands[0]-> var;
	operandResult = expression( oneOperatorNode -> operands[1] );

	if( currentVar -> type == FLOAT_IDENTIFIER_TYPE )
	{
		actualValue = currentVar -> val.float_value;
	}
	if( currentVar -> type == INTEGER_IDENTIFIER_TYPE )
	{
		actualValue =  (float) currentVar -> val.integer_value;
	}
	if( currentVar -> type != operandResult.type )
	{
		result.type = FLOAT_EXPRESSION;
		currentVar -> type = FLOAT_IDENTIFIER_TYPE;
	}
	else
	{	
		result.type = (currentVar -> type == INTEGER_IDENTIFIER_TYPE ? INTEGER_EXPRESSION : FLOAT_EXPRESSION) ;
		currentVar -> type = (currentVar -> type == INTEGER_IDENTIFIER_TYPE ? INTEGER_IDENTIFIER_TYPE : FLOAT_IDENTIFIER_TYPE) ;
	}

	switch( operandResult.type )
	{
		case INTEGER_EXPRESSION:
			actualValue  += (float) operandResult.value.integer_value;
			if( currentVar -> type == FLOAT_IDENTIFIER_TYPE ) 	currentVar -> val.float_value = actualValue;
			if( currentVar -> type == INTEGER_IDENTIFIER_TYPE ) 	currentVar -> val.integer_value = (int) actualValue;

			if( result.type == INTEGER_EXPRESSION )	result.value.integer_value = (int) actualValue;
			if( result.type == FLOAT_EXPRESSION ) 	result.value.float_value =  actualValue;
		break;

		case FLOAT_EXPRESSION:
			actualValue  +=  operandResult.value.float_value;
			if( currentVar -> type == FLOAT_IDENTIFIER_TYPE ) 	currentVar -> val.float_value = actualValue;
			if( currentVar -> type == INTEGER_IDENTIFIER_TYPE ) 	currentVar -> val.integer_value = (int) actualValue;

			if( result.type == INTEGER_EXPRESSION )	result.value.integer_value = (int) actualValue;
			if( result.type == FLOAT_EXPRESSION ) 	result.value.float_value =  actualValue;
		break;

		case STRING_EXPRESSION:
			if( currentVar -> val.string_value != (char *) NULL )	/* reallocation	*/
			{
				int newLength;
				newLength = strlen(currentVar -> val.string_value) + strlen( operandResult.value.string_value) + 1;
				currentVar -> val.string_value = (char *) realloc( currentVar -> val.string_value , newLength );
			}
			else
			{
				currentVar -> val.string_value = (char *) malloc( strlen( operandResult.value.string_value) + 1 );
			}

			if( currentVar -> val.string_value == NULL )
				yyerror( "Memory allocation for variable string content impossible\n");

			strcpy( currentVar -> val.string_value ,  strcat(currentVar -> val.string_value, operandResult.value.string_value ) );
			currentVar -> type = STRING_IDENTIFIER_TYPE;
			result.value.string_value =  currentVar -> val.string_value ;
			result.type = STRING_EXPRESSION;
		break;

		case CHAR_EXPRESSION:
			currentVar -> val.char_value  += (int) operandResult.value.char_value;
			currentVar -> type = CHAR_IDENTIFIER_TYPE;
			result.value.char_value =  currentVar -> val.char_value;
			result.type = CHAR_EXPRESSION;
		break;

		case GUID_EXPRESSION:
			yyerror( "+= operator can't be applied to Guid type\n" );
		break;

		case BOOLEAN_EXPRESSION:
			yyerror( "+= operator can't be applied to Boolean type\n" );
		break;

		case ENTITY_EXPRESSION:
			yyerror( "+= operator can't be applied to Entity type\n" );
		break;

		case PROPERTY_EXPRESSION:
			yyerror( "+= operator can't be applied to Property type\n" );

		break;

		default:
		break;
	}
	return result;	
}
/* -------------------------------------*/
/* -= interpretation			*/
/* -------------------------------------*/
expression_Value  expression_Operator_T_MINUS_EGAL_SIGN(operator * oneOperatorNode)
{
variable  * currentVar;
expression_Value result ;
expression_Value operandResult ;
float actualValue;

	currentVar = oneOperatorNode -> operands[0]-> var;
	operandResult = expression( oneOperatorNode -> operands[1] );

	if( currentVar -> type == FLOAT_IDENTIFIER_TYPE )
	{
		actualValue = currentVar -> val.float_value;
	}
	if( currentVar -> type == INTEGER_IDENTIFIER_TYPE )
	{
		actualValue =  (float) currentVar -> val.integer_value;
	}
	if( currentVar -> type != operandResult.type )
	{
		result.type = FLOAT_EXPRESSION;
		currentVar -> type = FLOAT_IDENTIFIER_TYPE;
	}
	else
	{	
		result.type = (currentVar -> type == INTEGER_IDENTIFIER_TYPE ? INTEGER_EXPRESSION : FLOAT_EXPRESSION) ;
		currentVar -> type = (currentVar -> type == INTEGER_IDENTIFIER_TYPE ? INTEGER_IDENTIFIER_TYPE : FLOAT_IDENTIFIER_TYPE) ;
	}

	switch( operandResult.type )
	{
		case INTEGER_EXPRESSION:
			actualValue  -= (float) operandResult.value.integer_value;
			if( currentVar -> type == FLOAT_IDENTIFIER_TYPE ) 	currentVar -> val.float_value = actualValue;
			if( currentVar -> type == INTEGER_IDENTIFIER_TYPE ) 	currentVar -> val.integer_value = (int) actualValue;

			if( result.type == INTEGER_EXPRESSION )	result.value.integer_value = (int) actualValue;
			if( result.type == FLOAT_EXPRESSION ) 	result.value.float_value =  actualValue;
		break;

		case FLOAT_EXPRESSION:
			actualValue  -=  operandResult.value.float_value;
			if( currentVar -> type == FLOAT_IDENTIFIER_TYPE ) 	currentVar -> val.float_value = actualValue;
			if( currentVar -> type == INTEGER_IDENTIFIER_TYPE ) 	currentVar -> val.integer_value = (int) actualValue;

			if( result.type == INTEGER_EXPRESSION )	result.value.integer_value = (int) actualValue;
			if( result.type == FLOAT_EXPRESSION ) 	result.value.float_value =  actualValue;
		break;

		case STRING_EXPRESSION:
			yyerror( "-= operator can't be applied to string type\n" );
		break;

		case CHAR_EXPRESSION:
			currentVar -> val.char_value  -= (int) operandResult.value.char_value;
			currentVar -> type = CHAR_IDENTIFIER_TYPE;
			result.value.char_value =  currentVar -> val.char_value;
			result.type = CHAR_EXPRESSION;
		break;

		case GUID_EXPRESSION:
			yyerror( "-= operator can't be applied to Guid type\n" );
		break;

		case BOOLEAN_EXPRESSION:
			yyerror( "-= operator can't be applied to Boolean type\n" );
		break;

		case ENTITY_EXPRESSION:
			yyerror( "-= operator can't be applied to Entity type\n" );
		break;

		case PROPERTY_EXPRESSION:
			yyerror( "-= operator can't be applied to Property type\n" );

		break;

		default:
		break;
	}
	return result;		
}
/* -------------------------------------*/
/* *= interpretation			*/
/* -------------------------------------*/
expression_Value  expression_Operator_T_ASTERISK_EGAL(operator * oneOperatorNode)
{
variable  * currentVar;
expression_Value result ;
expression_Value operandResult ;

	currentVar = oneOperatorNode -> operands[0]-> var;
	operandResult = expression( oneOperatorNode -> operands[1] );
	switch( operandResult.type )
	{
		case INTEGER_EXPRESSION:
			currentVar -> val.integer_value  *= operandResult.value.integer_value;
			currentVar -> type = INTEGER_IDENTIFIER_TYPE;
			result.value.integer_value =  currentVar -> val.integer_value;
			result.type = INTEGER_EXPRESSION;
		break;

		case FLOAT_EXPRESSION:
			currentVar -> val.float_value  *= operandResult.value.float_value;
			currentVar -> type = FLOAT_IDENTIFIER_TYPE;
			result.value.integer_value =  currentVar -> val.float_value;
			result.type = FLOAT_EXPRESSION;
		break;

		case STRING_EXPRESSION:
			yyerror( "*= operator can't be applied to string type\n" );
		break;

		case CHAR_EXPRESSION:
			currentVar -> val.char_value  *= (int) operandResult.value.char_value;
			currentVar -> type = CHAR_IDENTIFIER_TYPE;
			result.value.char_value =  currentVar -> val.char_value;
			result.type = CHAR_EXPRESSION;
		break;

		case GUID_EXPRESSION:
			yyerror( "*= operator can't be applied to Guid type\n" );
		break;

		case BOOLEAN_EXPRESSION:
			yyerror( "*= operator can't be applied to Boolean type\n" );
		break;

		case ENTITY_EXPRESSION:
			yyerror( "*= operator can't be applied to Entity type\n" );
		break;

		case PROPERTY_EXPRESSION:
			yyerror( "*= operator can't be applied to Property type\n" );

		break;

		default:
		break;
	}
	return result;	
}
/* -------------------------------------*/
/* /= interpretation			*/
/* -------------------------------------*/
expression_Value  expression_Operator_T_SLASH_EGAL(operator * oneOperatorNode)
{
variable  * currentVar;
expression_Value result ;
expression_Value operandResult ;

	currentVar = oneOperatorNode -> operands[0]-> var;
	operandResult = expression( oneOperatorNode -> operands[1] );
	switch( operandResult.type )
	{
		case INTEGER_EXPRESSION:
			if( operandResult.value.integer_value == 0 )
				yyerror( "Unable to divide by zero\n" );
			currentVar -> val.integer_value  /= operandResult.value.integer_value;
			currentVar -> type = INTEGER_IDENTIFIER_TYPE;
			result.value.integer_value =  currentVar -> val.integer_value;
			result.type = INTEGER_EXPRESSION;
		break;

		case FLOAT_EXPRESSION:
			if( operandResult.value.integer_value == 0 )
				yyerror( "Unable to divide by zero\n" );
			currentVar -> val.float_value  /= operandResult.value.float_value;
			currentVar -> type = FLOAT_IDENTIFIER_TYPE;
			result.value.integer_value =  currentVar -> val.float_value;
			result.type = FLOAT_EXPRESSION;
		break;

		case STRING_EXPRESSION:
			yyerror( "/= operator can't be applied to string type\n" );
		break;

		case CHAR_EXPRESSION:
			currentVar -> val.char_value  /= (int) operandResult.value.char_value;
			currentVar -> type = CHAR_IDENTIFIER_TYPE;
			result.value.char_value =  currentVar -> val.char_value;
			result.type = CHAR_EXPRESSION;
		break;

		case GUID_EXPRESSION:
			yyerror( "/= operator can't be applied to Guid type\n" );
		break;

		case BOOLEAN_EXPRESSION:
			yyerror( "/= operator can't be applied to Boolean type\n" );
		break;

		case ENTITY_EXPRESSION:
			yyerror( "*= operator can't be applied to Entity type\n" );
		break;

		case PROPERTY_EXPRESSION:
			yyerror( "/= operator can't be applied to Property type\n" );

		break;

		default:
		break;
	}
	return result;	
}


/* -------------------------------------*/
/* interpretation d'une assignation	*/
/* -------------------------------------*/
expression_Value  expression_Operator_T_ASSIGN(operator * oneOperatorNode) 
{
variable  * currentVar;
expression_Value result ;
expression_Value operandResult ;

	currentVar = oneOperatorNode -> operands[0]-> var;

	operandResult = expression( oneOperatorNode -> operands[1] );

	switch( operandResult.type )
	{
		case INTEGER_EXPRESSION:
			currentVar -> val.integer_value  = operandResult.value.integer_value;
			currentVar -> type = INTEGER_IDENTIFIER_TYPE;
			result.type = INTEGER_EXPRESSION;
			result.value.integer_value =  currentVar -> val.integer_value;
		break;

		case FLOAT_EXPRESSION:
			currentVar -> val.float_value  = operandResult.value.float_value;
			currentVar -> type = FLOAT_IDENTIFIER_TYPE;
			result.type = FLOAT_EXPRESSION;
			result.value.integer_value =  currentVar -> val.float_value;
		break;

		case STRING_EXPRESSION:
			if( currentVar -> val.string_value != (char *) NULL )	/* reallocation	*/
			{
				currentVar -> val.string_value = (char *) realloc( currentVar -> val.string_value, strlen( operandResult.value.string_value) + 1 );
			}
			else
			{
				currentVar -> val.string_value = (char *) malloc( strlen( operandResult.value.string_value) + 1 );
			}

			if( currentVar -> val.string_value == NULL )
				yyerror( "Memory allocation for variable string content impossible\n");

			// fprintf(stderr , "copy new string value\n" );
			strcpy( currentVar -> val.string_value ,  operandResult.value.string_value );
			currentVar -> type = STRING_IDENTIFIER_TYPE;
			result.type = STRING_EXPRESSION;
			// fprintf(stderr , "copy string value in expression result;\n" );
			result.value.string_value =  currentVar -> val.string_value ;
			// fprintf(stderr , "copied !\n" );
		break;

		case CHAR_EXPRESSION:
			currentVar -> val.char_value  = operandResult.value.char_value;
			currentVar -> type = CHAR_IDENTIFIER_TYPE;
			result.value.char_value =  currentVar -> val.char_value;
			result.type = CHAR_EXPRESSION;
		break;

		case GUID_EXPRESSION:
			strcpy( currentVar -> val.guid_value , operandResult.value.guid_value );
			currentVar -> type = GUID_IDENTIFIER_TYPE;
			strcpy( result.value.guid_value , currentVar -> val.guid_value );
			result.type = GUID_EXPRESSION;
		break;

		case BOOLEAN_EXPRESSION:
			currentVar -> val.boolean_value = operandResult.value.boolean_value;	
			currentVar -> type = BOOLEAN_IDENTIFIER_TYPE;		
			result.value.boolean_value = currentVar -> val.boolean_value;
			result.type = BOOLEAN_EXPRESSION;
		break;

		case ENTITY_EXPRESSION:
			yyerror( "= operator can't be applied to Entity type\n" );
		break;

		case PROPERTY_EXPRESSION:
			yyerror( "= operator can't be applied to Property type\n" );
		break;

		default:
		break;
	}

	return result;	
}
