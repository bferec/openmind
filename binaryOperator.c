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
/* 	>> operator (right shift)	*/
/*--------------------------------------*/
expression_Value expression_Operator_T_RIGHT_SHIFT( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );



	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	operandResult[1] = expression( oneOperatorNode -> operands[1] );

	switch( operandResult[0].type  )
	{
		case INTEGER_EXPRESSION:
			if( operandResult[1].type == INTEGER_EXPRESSION )
				result.value.integer_value = operandResult[0].value.integer_value >> operandResult[1].value.integer_value;
			else if( operandResult[1].type == CHAR_EXPRESSION )
				result.value.integer_value = operandResult[0].value.integer_value >> operandResult[1].value.char_value;
			else
				yyerror( "Unable to apply logical & to these heterogenous operands\n" );

			result.type = INTEGER_EXPRESSION;		
		break;

		case CHAR_EXPRESSION:
			if( operandResult[1].type == CHAR_EXPRESSION )
				result.value.char_value = operandResult[0].value.char_value >> operandResult[1].value.char_value;
		else if( operandResult[1].type == INTEGER_EXPRESSION )
				result.value.char_value = operandResult[0].value.char_value >> operandResult[1].value.integer_value;
			else
				yyerror( "Unable to apply logical & to these heterogenous operands\n" );
			result.type = CHAR_EXPRESSION;
		break;

		case BOOLEAN_EXPRESSION:
		case FLOAT_EXPRESSION:
		case STRING_EXPRESSION:
		case GUID_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply logical & to these operands\n" );
		break;

		default:
		break;
	}
	return result;
}


/*--------------------------------------*/
/* 	<< operator (left shift)	*/
/*--------------------------------------*/
expression_Value expression_Operator_T_LEFT_SHIFT( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );



	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	operandResult[1] = expression( oneOperatorNode -> operands[1] );

	switch( operandResult[0].type  )
	{
		case INTEGER_EXPRESSION:
			if( operandResult[1].type == INTEGER_EXPRESSION )
				result.value.integer_value = operandResult[0].value.integer_value << operandResult[1].value.integer_value;
			else if( operandResult[1].type == CHAR_EXPRESSION )
				result.value.integer_value = operandResult[0].value.integer_value << operandResult[1].value.char_value;
			else
				yyerror( "Unable to apply logical & to these heterogenous operands\n" );

			result.type = INTEGER_EXPRESSION;		
		break;

		case CHAR_EXPRESSION:
			if( operandResult[1].type == CHAR_EXPRESSION )
				result.value.char_value = operandResult[0].value.char_value << operandResult[1].value.char_value;
		else if( operandResult[1].type == INTEGER_EXPRESSION )
				result.value.char_value = operandResult[0].value.char_value << operandResult[1].value.integer_value;
			else
				yyerror( "Unable to apply logical & to these heterogenous operands\n" );
			result.type = CHAR_EXPRESSION;
		break;

		case BOOLEAN_EXPRESSION:
		case FLOAT_EXPRESSION:
		case STRING_EXPRESSION:
		case GUID_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply logical & to these operands\n" );
		break;

		default:
		break;
	}
	return result;
}

/*--------------------------------------*/
/* 	~ operator (complement à 1)	*/
/*--------------------------------------*/
expression_Value expression_Operator_T_BINARY_COMPLEMENT( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;

	operandResult = (expression_Value * ) malloc( sizeof(expression_Value ) );

	operandResult[0] = expression( oneOperatorNode -> operands[0] );

	switch( operandResult[0].type  )
	{
		case INTEGER_EXPRESSION:
			result.value.integer_value = ~ operandResult[0].value.integer_value ;
			result.type = INTEGER_EXPRESSION;		
		break;

		case CHAR_EXPRESSION:
			result.value.char_value = ~ operandResult[0].value.char_value;
			result.type = CHAR_EXPRESSION;
		break;

		case BOOLEAN_EXPRESSION:
		case FLOAT_EXPRESSION:
		case STRING_EXPRESSION:
		case GUID_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply logical & to these operands\n" );
		break;

		default:
		break;
	}
	return result;
}

/*--------------------------------------*/
/* 	| operator (binary or)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_BINARY_OR( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );



	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	operandResult[1] = expression( oneOperatorNode -> operands[1] );

	switch( operandResult[0].type  )
	{
		case INTEGER_EXPRESSION:
			if( operandResult[1].type == INTEGER_EXPRESSION )
				result.value.integer_value = operandResult[0].value.integer_value | operandResult[1].value.integer_value;
			else if( operandResult[1].type == CHAR_EXPRESSION )
				result.value.integer_value = operandResult[0].value.integer_value | operandResult[1].value.char_value;
			else
				yyerror( "Unable to apply logical & to these heterogenous operands\n" );

			result.type = INTEGER_EXPRESSION;		
		break;

		case CHAR_EXPRESSION:
			if( operandResult[1].type == CHAR_EXPRESSION )
				result.value.char_value = operandResult[0].value.char_value | operandResult[1].value.char_value;
		else if( operandResult[1].type == INTEGER_EXPRESSION )
				result.value.char_value = operandResult[0].value.char_value | operandResult[1].value.integer_value;
			else
				yyerror( "Unable to apply logical & to these heterogenous operands\n" );
			result.type = CHAR_EXPRESSION;
		break;

		case BOOLEAN_EXPRESSION:
		case FLOAT_EXPRESSION:
		case STRING_EXPRESSION:
		case GUID_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply logical & to these operands\n" );
		break;

		default:
		break;
	}
	return result;
}

/*--------------------------------------*/
/* 	& operator (binary and)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_BINARY_AND( operator * oneOperatorNode  )
{
expression_Value result;
expression_Value * operandResult ;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	operandResult[0] = expression( oneOperatorNode -> operands[0] );
	operandResult[1] = expression( oneOperatorNode -> operands[1] );

	switch( operandResult[0].type  )
	{
		case INTEGER_EXPRESSION:
			if( operandResult[1].type == INTEGER_EXPRESSION )
				result.value.integer_value = operandResult[0].value.integer_value & operandResult[1].value.integer_value;
			else if( operandResult[1].type == CHAR_EXPRESSION )
				result.value.integer_value = operandResult[0].value.integer_value & operandResult[1].value.char_value;
			else
				yyerror( "Unable to apply logical & to these heterogenous operands\n" );

			result.type = INTEGER_EXPRESSION;		
		break;

		case CHAR_EXPRESSION:
			if( operandResult[1].type == CHAR_EXPRESSION )
				result.value.char_value = operandResult[0].value.char_value & operandResult[1].value.char_value;
		else if( operandResult[1].type == INTEGER_EXPRESSION )
				result.value.char_value = operandResult[0].value.char_value & operandResult[1].value.integer_value;
			else
				yyerror( "Unable to apply logical & to these heterogenous operands\n" );
			result.type = CHAR_EXPRESSION;
		break;

		case BOOLEAN_EXPRESSION:
		case FLOAT_EXPRESSION:
		case STRING_EXPRESSION:
		case GUID_EXPRESSION:
		case ENTITY_EXPRESSION:
		case PROPERTY_EXPRESSION:
			yyerror( "Unable to apply logical & to these operands\n" );
		break;

		default:
		break;
	}
	return result;
}


