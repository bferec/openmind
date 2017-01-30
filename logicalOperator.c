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
/* 	^ operator (xor)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_XOR( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.type = BOOLEAN_EXPRESSION;

	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	operandResult[1] = expression( oneOperatorNode -> operands[1] );

	switch( operandResult[0].type )
	{
		case INTEGER_EXPRESSION:
		case FLOAT_EXPRESSION:
		case BOOLEAN_EXPRESSION:
		case CHAR_EXPRESSION:
			result.value.boolean_value = operandResult[0].value.boolean_value ^  operandResult[1].value.boolean_value;
		break;

		case STRING_EXPRESSION:
		case GUID_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply logical ^  to these operands\n" );
		break;

		default:
		break;
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

	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	operandResult[1] = expression( oneOperatorNode -> operands[1] );

	switch( operandResult[0].type )
	{
		case INTEGER_EXPRESSION:
		case FLOAT_EXPRESSION:
		case BOOLEAN_EXPRESSION:
		case CHAR_EXPRESSION:
			result.value.boolean_value = operandResult[0].value.boolean_value || operandResult[1].value.boolean_value;
		break;

		case STRING_EXPRESSION:
		case GUID_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply logical OR to these operands\n" );
		break;

		default:
		break;
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

	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	operandResult[1] = expression( oneOperatorNode -> operands[1] );

	switch( operandResult[0].type )
	{
		case INTEGER_EXPRESSION:
		case FLOAT_EXPRESSION:
		case BOOLEAN_EXPRESSION:
		case CHAR_EXPRESSION:
			result.value.boolean_value = operandResult[0].value.boolean_value && operandResult[1].value.boolean_value;
		break;

		case STRING_EXPRESSION:
		case GUID_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply logical OR to these operands\n" );
		break;

		default:
		break;
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
			case FLOAT_EXPRESSION:
			case CHAR_EXPRESSION:
			case BOOLEAN_EXPRESSION:
				result.value.boolean_value = ! operandResult.value.boolean_value;
			break;

			case STRING_EXPRESSION:
			case GUID_EXPRESSION:
			case ENTITY_EXPRESSION:
			case PROPERTY_EXPRESSION:
				yyerror( "Unable to apply logical OR to these operands\n" );
			break;

			default:
			break;
		}
	return result;
}



