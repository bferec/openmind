/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* logicalOperator.c			*/
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
/* 	^ operator (xor)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_XOR( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.type = BOOLEAN_EXPRESSION;
	result.value.boolean_value = 1;	/* neutral for logical XOR */

	for( int i = 0 ; i < oneOperatorNode -> OperandsCount ; i ++ )
	{
		operandResult[i] = expression( oneOperatorNode -> operands[i] );

		switch( operandResult[i].type )
		{
			case INTEGER_EXPRESSION:
				yyerror( "Unable to apply logical XOR to integer  numbers\n" );
			break;

			case FLOAT_EXPRESSION:
				yyerror( "Unable to apply logical XOR to float numbers\n" );
			break;

			case STRING_EXPRESSION:
				result.type = INTEGER_EXPRESSION;
				yyerror( "Unable to apply logical XOR to Strings\n" );
			break;

			case GUID_EXPRESSION:
				yyerror( "Unable to apply logical XOR to guids\n" );
			break;

			case BOOLEAN_EXPRESSION:
				if( i == 0 )
					result.value.boolean_value = operandResult[i].value.boolean_value;
				else
					result.value.boolean_value = result.value.boolean_value != operandResult[i].value.boolean_value;
			break;

			case ENTITY_EXPRESSION:
				yyerror( "Unable to apply logical XOR to entitys\n" );
			break;

			case PROPERTY_EXPRESSION:
				yyerror( "Unable to apply logical XOR to Propertys\n" );
			break;

			default:
			break;
		}
	}


	return result;
}

/*--------------------------------------*/
/* 	|| operator (or)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_OR( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.type = BOOLEAN_EXPRESSION;
	result.value.boolean_value = 0;	/* neutral for logical OR */

	for( int i = 0 ; i < oneOperatorNode -> OperandsCount ; i ++ )
	{
		operandResult[i] = expression( oneOperatorNode -> operands[i] );

		switch( operandResult[i].type )
		{
			case INTEGER_EXPRESSION:
				yyerror( "Unable to apply logical OR to integer  numbers\n" );
			break;

			case FLOAT_EXPRESSION:
				yyerror( "Unable to apply logical OR to float numbers\n" );
			break;

			case STRING_EXPRESSION:
				result.type = INTEGER_EXPRESSION;
				yyerror( "Unable to apply logical OR to Strings\n" );
			break;

			case GUID_EXPRESSION:
				yyerror( "Unable to apply logical OR to guids\n" );
			break;

			case BOOLEAN_EXPRESSION:
				result.value.boolean_value |= operandResult[i].value.boolean_value;
			break;

			case ENTITY_EXPRESSION:
				yyerror( "Unable to apply logical OR to entitys\n" );
			break;

			case PROPERTY_EXPRESSION:
				yyerror( "Unable to apply logical OR to Propertys\n" );
			break;

			default:
			break;
		}
	}


	return result;
}
/*--------------------------------------*/
/* 	&& operator (and)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_AND( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.type = BOOLEAN_EXPRESSION;
	result.value.boolean_value = 1;	/* neutral for logical AND */

	for( int i = 0 ; i < oneOperatorNode -> OperandsCount ; i ++ )
	{
		operandResult[i] = expression( oneOperatorNode -> operands[i] );

		switch( operandResult[i].type )
		{
			case INTEGER_EXPRESSION:
				yyerror( "Unable to apply logical OR to integer  numbers\n" );
			break;

			case FLOAT_EXPRESSION:
				yyerror( "Unable to apply logical OR to float numbers\n" );
			break;

			case STRING_EXPRESSION:
				result.type = INTEGER_EXPRESSION;
				yyerror( "Unable to apply logical OR to Strings\n" );
			break;

			case GUID_EXPRESSION:
				yyerror( "Unable to apply logical OR to guids\n" );
			break;

			case BOOLEAN_EXPRESSION:
				result.value.boolean_value &= operandResult[i].value.boolean_value;
			break;

			case ENTITY_EXPRESSION:
				yyerror( "Unable to apply logical OR to entitys\n" );
			break;

			case PROPERTY_EXPRESSION:
				yyerror( "Unable to apply logical OR to Propertys\n" );
			break;

			default:
			break;
		}
	}


	return result;
}
/*--------------------------------------*/
/* 	! operator (not)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_NOT( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value operandResult ;

	result.type = BOOLEAN_EXPRESSION;
	operandResult = expression( oneOperatorNode -> operands[0] );
	switch( operandResult.type )
		{
			case INTEGER_EXPRESSION:
				yyerror( "Unable to apply logical NOT to integer  numbers\n" );
			break;

			case FLOAT_EXPRESSION:
				yyerror( "Unable to apply logical NOT to float numbers\n" );
			break;

			case STRING_EXPRESSION:
				yyerror( "Unable to apply logical NOT to Strings\n" );
			break;

			case GUID_EXPRESSION:
				yyerror( "Unable to apply logical NOT to guids\n" );
			break;

			case BOOLEAN_EXPRESSION:
				result.value.boolean_value = ! operandResult.value.boolean_value;
			break;

			case ENTITY_EXPRESSION:
				yyerror( "Unable to apply logical NOT to entitys\n" );
			break;

			case PROPERTY_EXPRESSION:
				yyerror( "Unable to apply logical NOT to Propertys\n" );
			break;

			default:
			break;
		}
	return result;
}



