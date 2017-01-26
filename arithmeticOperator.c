/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* binaryOperator.c			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.value.integer_value = result.value.float_value = resultNumber = 0;
	result.type = INTEGER_EXPRESSION;


	for( int i = 0 ; i < oneOperatorNode -> OperandsCount ; i ++ )
	{
		operandResult[i] = expression( oneOperatorNode -> operands[i] );
		switch( operandResult[i].type )
		{
			case INTEGER_EXPRESSION:
				if(i == 0 )
					resultNumber = (float) operandResult[i].value.integer_value;
				else
				{
					if( operandResult[i].value.integer_value == 0 )
						yyerror("Divide by zero");
					resultNumber /= (float) operandResult[i].value.integer_value;
				}
			break;

			case FLOAT_EXPRESSION:
				result.type = FLOAT_EXPRESSION;
				if(i == 0 )
					resultNumber = operandResult[i].value.float_value;
				else
				{
					if( operandResult[i].value.float_value == 0 )
						yyerror("Divide by zero");

					resultNumber /= operandResult[i].value.float_value;
				}
			break;

			case STRING_EXPRESSION:
				result.type = INTEGER_EXPRESSION;
				yyerror( "Unable to multiply String\n" );
			break;

			case GUID_EXPRESSION:
				yyerror( "Unable to multiply Guid\n" );
			break;

			case BOOLEAN_EXPRESSION:
				yyerror( "Unable to multiply Boolean\n" );
			break;

			case ENTITY_EXPRESSION:
				yyerror( "Unable to multiply entity\n" );
			break;

			case PROPERTY_EXPRESSION:
				yyerror( "Unable to multiply Property\n" );
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
/* 	* operator			*/
/*--------------------------------------*/
expression_Value expression_Operator_T_ASTERISK( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;
float resultNumber;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.value.integer_value = result.value.float_value = resultNumber = 0;
	result.type = INTEGER_EXPRESSION;


	for( int i = 0 ; i < oneOperatorNode -> OperandsCount ; i ++ )
	{
		operandResult[i] = expression( oneOperatorNode -> operands[i] );
		switch( operandResult[i].type )
		{
			case INTEGER_EXPRESSION:
				if(i == 0 )
					resultNumber = (float) operandResult[i].value.integer_value;
				else
					resultNumber *= (float) operandResult[i].value.integer_value;
			break;

			case FLOAT_EXPRESSION:
				result.type = FLOAT_EXPRESSION;
				if(i == 0 )
					resultNumber = operandResult[i].value.float_value;
				else
					resultNumber *= operandResult[i].value.float_value;
			break;

			case STRING_EXPRESSION:
				result.type = INTEGER_EXPRESSION;
				yyerror( "Unable to multiply String\n" );
			break;

			case GUID_EXPRESSION:
				yyerror( "Unable to multiply Guid\n" );
			break;

			case BOOLEAN_EXPRESSION:
				yyerror( "Unable to multiply Boolean\n" );
			break;

			case ENTITY_EXPRESSION:
				yyerror( "Unable to multiply entity\n" );
			break;

			case PROPERTY_EXPRESSION:
				yyerror( "Unable to multiply Property\n" );
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
/* 	+ operator			*/
/*--------------------------------------*/
expression_Value expression_Operator_T_PLUS_SIGN( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;
float resultNumber;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.value.integer_value = result.value.float_value = resultNumber = 0;
	result.type = INTEGER_EXPRESSION;


	for( int i = 0 ; i < oneOperatorNode -> OperandsCount ; i ++ )
	{
		operandResult[i] = expression( oneOperatorNode -> operands[i] );
		switch( operandResult[i].type )
		{
			case INTEGER_EXPRESSION:
				resultNumber +=  operandResult[i].value.integer_value;
			break;

			case FLOAT_EXPRESSION:
				result.type = FLOAT_EXPRESSION;
				resultNumber +=  operandResult[i].value.float_value;
			break;

			case STRING_EXPRESSION:
				result.type = INTEGER_EXPRESSION;
				yyerror( "Unable to Add String\n" );
			break;

			case GUID_EXPRESSION:
				yyerror( "Unable to Add Guid\n" );
			break;

			case BOOLEAN_EXPRESSION:
				yyerror( "Unable to Add Boolean\n" );
			break;

			case ENTITY_EXPRESSION:
				yyerror( "Unable to Add entity\n" );
			break;

			case PROPERTY_EXPRESSION:
				yyerror( "Unable to Add Property\n" );
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

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.value.integer_value = result.value.float_value = resultNumber = 0;

	result.type = INTEGER_EXPRESSION;

	operandResult[0] = expression( oneOperatorNode -> operands[0] );
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
			yyerror( "Unable to substract String\n" );
		break;

		case GUID_EXPRESSION:
			yyerror( "Unable to substract Guid\n" );
		break;

		case BOOLEAN_EXPRESSION:
			yyerror( "Unable to substract Boolean\n" );
		break;

		case ENTITY_EXPRESSION:
			yyerror( "Unable to substract entity\n" );
		break;

		case PROPERTY_EXPRESSION:
			yyerror( "Unable to Add Property\n" );
		break;

		default:
		break;
	}
					
	for( int i = 1 ; i < oneOperatorNode -> OperandsCount ; i ++ )
	{
		operandResult[i] = expression( oneOperatorNode -> operands[i] );
		switch( operandResult[i].type )
		{
			case INTEGER_EXPRESSION:
				// fprintf(stderr , "soustraction de %d a %d \n", operandResult[i].value.integer_value , (int) resultNumber );
				resultNumber -=  (float) operandResult[i].value.integer_value;
			break;

			case FLOAT_EXPRESSION:
				// fprintf(stderr , "soustraction de %f a %f\n", operandResult[i].value.float_value, resultNumber );
				resultNumber -=  operandResult[i].value.float_value;
			break;

			case STRING_EXPRESSION:
				yyerror( "Unable to substract String\n" );
			break;

			case GUID_EXPRESSION:
				yyerror( "Unable to substract Guid\n" );
			break;

			case BOOLEAN_EXPRESSION:
				yyerror( "Unable to substract Boolean\n" );
			break;

			case ENTITY_EXPRESSION:
				yyerror( "Unable to substract entity\n" );
			break;

			case PROPERTY_EXPRESSION:
				yyerror( "Unable to substract Property\n" );
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
