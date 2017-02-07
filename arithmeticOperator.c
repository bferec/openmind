/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* arithmeticOperator.c			*/
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


/*--------------------------------------*/
/* 	/ operator			*/
/*--------------------------------------*/
expression_Value expression_Operator_T_SLASH( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;
float resultNumber;


	if( oneOperatorNode -> OperandsCount < 2 )
		yyerror( "operands count invalid for * operator\n" );

	operandResult = (expression_Value *) calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.value.integer_value = result.value.float_value = resultNumber = 0;
	result.type = INTEGER_EXPRESSION;

	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	operandResult[1] = expression( oneOperatorNode -> operands[1] );



	switch( operandResult[0].type )
	{
		case INTEGER_EXPRESSION:
			result.type = INTEGER_EXPRESSION;
			resultNumber = (float) operandResult[0].value.integer_value;
		break;

		case FLOAT_EXPRESSION:
			result.type = FLOAT_EXPRESSION;
			resultNumber = operandResult[0].value.float_value;
		break;

		case STRING_EXPRESSION:
		case CHAR_EXPRESSION:
		case GUID_EXPRESSION:
		case BOOLEAN_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply / operator to these operands\n" );
		break;

		default:
		break;
	}

	switch( operandResult[1].type )
	{
		case INTEGER_EXPRESSION:
			if( operandResult[1].value.integer_value == 0 )
				yyerror( "Unable to divide by zero\n" );

			resultNumber /= (float) operandResult[1].value.integer_value;
		break;

		case FLOAT_EXPRESSION:
			if( operandResult[1].value.float_value == 0 )
				yyerror( "Unable tdivide by zero\n" );

			resultNumber /= operandResult[1].value.float_value;
		break;

		case STRING_EXPRESSION:
		case CHAR_EXPRESSION:
		case GUID_EXPRESSION:
		case BOOLEAN_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply / operator to these operands\n" );
		break;

		default:
		break;
	}

	if( result.type == INTEGER_EXPRESSION )	
	{
		result.value.integer_value = (int) resultNumber;
	}
	else if( result.type == FLOAT_EXPRESSION )	
	{
		result.value.float_value = resultNumber;
	}
	
	free( operandResult );

	return result;
}

/*--------------------------------------*/
/* 	* operator			*/
/*--------------------------------------*/
expression_Value expression_Operator_T_ASTERISK( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;
float resultNumber;


	if( oneOperatorNode -> OperandsCount < 2 )
		yyerror( "operands count invalid for * operator\n" );

	operandResult = (expression_Value *) calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );


	result.value.integer_value = result.value.float_value = resultNumber = 0;
	result.type = INTEGER_EXPRESSION;

	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	operandResult[1] = expression( oneOperatorNode -> operands[1] );


	switch( operandResult[0].type )
	{
		case INTEGER_EXPRESSION:
			result.type = INTEGER_EXPRESSION;
			resultNumber = (float) operandResult[0].value.integer_value;
		break;

		case FLOAT_EXPRESSION:
			result.type = FLOAT_EXPRESSION;
			resultNumber = operandResult[0].value.float_value;
		break;

		case STRING_EXPRESSION:
		case CHAR_EXPRESSION:
		case GUID_EXPRESSION:
		case BOOLEAN_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply * operator to these operands\n" );
		break;

		default:
		break;
	}

	switch( operandResult[1].type )
	{
		case INTEGER_EXPRESSION:
			resultNumber *= (float) operandResult[1].value.integer_value;
		break;

		case FLOAT_EXPRESSION:
			resultNumber *= operandResult[1].value.float_value;
		break;

		case STRING_EXPRESSION:
		case CHAR_EXPRESSION:
		case GUID_EXPRESSION:
		case BOOLEAN_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply * operator to these operands\n" );
		break;

		default:
		break;
	}

	if( result.type == INTEGER_EXPRESSION )	
	{
		result.value.integer_value = (int) resultNumber;
	}
	else if( result.type == FLOAT_EXPRESSION )	
	{
		result.value.float_value = resultNumber;
	}
	
	free( operandResult );

	return result;
}
/*--------------------------------------*/
/* 	+ operator			*/
/*--------------------------------------*/
expression_Value expression_Operator_T_PLUS_SIGN( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;
float resultNumber;

	operandResult = (expression_Value *) calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.value.integer_value = result.value.float_value = resultNumber = 0;
	result.type = INTEGER_EXPRESSION;

	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	if( oneOperatorNode -> OperandsCount > 1 )
	{
		operandResult[1] = expression( oneOperatorNode -> operands[1] );
	}

	switch( operandResult[0].type )
	{
		case INTEGER_EXPRESSION:
			resultNumber =  (float) operandResult[0].value.integer_value;
		break;

		case FLOAT_EXPRESSION:
			result.type = FLOAT_EXPRESSION;
			resultNumber =   operandResult[0].value.float_value;
		break;

		case STRING_EXPRESSION:
			if( oneOperatorNode -> OperandsCount < 2 )
				yyerror( "Unable to apply unary + operator to these operands\n" );
		break;

		case GUID_EXPRESSION:
		case BOOLEAN_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply + operator to these operands\n" );
		break;

		default:
		break;
	}
	if( oneOperatorNode -> OperandsCount > 1 )
	{			
		switch( operandResult[1].type )
		{
			case INTEGER_EXPRESSION:
				resultNumber +=  (float) operandResult[1].value.integer_value;
			break;

			case FLOAT_EXPRESSION:
				resultNumber +=  operandResult[1].value.float_value;
			break;

			case STRING_EXPRESSION:
				result.value.string_value = (char *) malloc( strlen( operandResult[0].value.string_value ) + strlen( operandResult[1].value.string_value )  + 1 );
				strcpy( result.value.string_value , operandResult[0].value.string_value );
				strcat( result.value.string_value , operandResult[1].value.string_value );
				result.type = STRING_EXPRESSION;
			break;

			case GUID_EXPRESSION:
			case BOOLEAN_EXPRESSION:
			case ENTITY_EXPRESSION:
			case PROPERTY_EXPRESSION:
				yyerror( "Unable to apply + operator to these operands\n" );
			break;

			default:
			break;
		}
	}
	if( result.type == INTEGER_EXPRESSION )	
	{
		result.value.integer_value = (int) resultNumber;
	}
	else if( result.type == FLOAT_EXPRESSION )	
	{
		result.value.float_value = resultNumber;
	}
	
	free( operandResult );

	return result;
}

/*--------------------------------------*/
/* 	- operator			*/
/*--------------------------------------*/
expression_Value expression_Operator_T_MINUS_SIGN( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;
float resultNumber;

	operandResult = (expression_Value *) calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.value.integer_value = result.value.float_value = resultNumber = 0;
	result.type = INTEGER_EXPRESSION;

	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	if( oneOperatorNode -> OperandsCount > 1 )
	{
		operandResult[1] = expression( oneOperatorNode -> operands[1] );
	}

	switch( operandResult[0].type )
	{
		case INTEGER_EXPRESSION:
			resultNumber =  (float) operandResult[0].value.integer_value;
			resultNumber = oneOperatorNode -> OperandsCount > 1 ? resultNumber : - resultNumber;
		break;

		case FLOAT_EXPRESSION:
			result.type = FLOAT_EXPRESSION;
			resultNumber =   operandResult[0].value.float_value;
			resultNumber = oneOperatorNode -> OperandsCount > 1 ? resultNumber : - resultNumber;
		break;

		case STRING_EXPRESSION:
		case GUID_EXPRESSION:
		case BOOLEAN_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply - operator to thse operands\n" );
		break;

		default:
		break;
	}
	if( oneOperatorNode -> OperandsCount > 1 )
	{			
		switch( operandResult[1].type )
		{
			case INTEGER_EXPRESSION:
				resultNumber -=  (float) operandResult[1].value.integer_value;
			break;

			case FLOAT_EXPRESSION:
				resultNumber -=  operandResult[1].value.float_value;
			break;

			case STRING_EXPRESSION:
			case GUID_EXPRESSION:
			case BOOLEAN_EXPRESSION:
			case ENTITY_EXPRESSION:
			case PROPERTY_EXPRESSION:
				yyerror( "Unable to apply - operator to these operands\n" );
			break;

			default:
			break;
		}
	}
	if( result.type == INTEGER_EXPRESSION )	
	{
		result.value.integer_value = (int) resultNumber;
	}
	else if( result.type == FLOAT_EXPRESSION )	
	{
		result.value.float_value = resultNumber;
	}
	
	free( operandResult );

	return result;
}
