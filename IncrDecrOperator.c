/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* IncrDecrOperator.c			*/
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
/* -- interpretation			*/
/* -------------------------------------*/
expression_Value  expression_Operator_T_DECR(operator * oneOperatorNode)
{
variable  * currentVar;
expression_Value result ;


	currentVar = oneOperatorNode -> operands[0]-> var;
	result = expression( oneOperatorNode -> operands[0] );
	switch( result.type )
	{
		case INTEGER_EXPRESSION:
			currentVar -> val.integer_value --;
			result.value.integer_value = currentVar -> val.integer_value;
		break;

		case FLOAT_EXPRESSION:
			currentVar -> val.float_value -=1;
			result.value.float_value = currentVar -> val.float_value;
		break;

		case STRING_EXPRESSION:
			yyerror( "-- operator can't be applied to string type\n" );
		break;

		case CHAR_EXPRESSION:
			yyerror( "-- operator can't be applied to char type\n" );
		break;

		case GUID_EXPRESSION:
			yyerror( "-- operator can't be applied to Guid type\n" );
		break;

		case BOOLEAN_EXPRESSION:
			yyerror( "-- operator can't be applied to Boolean type\n" );
		break;

		case ENTITY_EXPRESSION:
			yyerror( "-- operator can't be applied to Entity type\n" );
		break;

		case PROPERTY_EXPRESSION:
			yyerror( "-- operator can't be applied to Property type\n" );

		break;

		default:
		break;
	}
	return result;	
}



/* -------------------------------------*/
/* ++ interpretation			*/
/* -------------------------------------*/
expression_Value  expression_Operator_T_INCR(operator * oneOperatorNode)
{
variable  * currentVar;
expression_Value result ;


	currentVar = oneOperatorNode -> operands[0]-> var;
	result = expression( oneOperatorNode -> operands[0] );
	switch( result.type )
	{
		case INTEGER_EXPRESSION:
			
			(currentVar -> val.integer_value) ++;			
			result.value.integer_value = currentVar -> val.integer_value;
		break;

		case FLOAT_EXPRESSION:
			(currentVar -> val.float_value) +=1.0 ;
			result.value.float_value = currentVar -> val.float_value;
		break;

		case STRING_EXPRESSION:
			yyerror( "++ operator can't be applied to string type\n" );
		break;

		case CHAR_EXPRESSION:
			yyerror( "++ operator can't be applied to char type\n" );
		break;

		case GUID_EXPRESSION:
			yyerror( "++ operator can't be applied to Guid type\n" );
		break;

		case BOOLEAN_EXPRESSION:
			yyerror( "++ operator can't be applied to Boolean type\n" );
		break;

		case ENTITY_EXPRESSION:
			yyerror( "++ operator can't be applied to Entity type\n" );
		break;

		case PROPERTY_EXPRESSION:
			yyerror( "++ operator can't be applied to Property type\n" );
		break;

		default:
		break;
	}
	return result;	
}

