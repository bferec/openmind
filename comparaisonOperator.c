/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* comparaisonOperator.c		*/
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
/*----------------------------------------------*/
/* 	>= operator (more or equal than)	*/
/*----------------------------------------------*/
expression_Value expression_Operator_T_MORE_OR_EQUAL_THAN( operator * oneOperatorNode  )
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
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value >= operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value >= (int) operandResult[1].value.float_value;
			break;

			case FLOAT_EXPRESSION:
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.float_value >= (float) operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value >=  operandResult[1].value.float_value;
			break;

			case STRING_EXPRESSION:
				if( operandResult[1].type == STRING_EXPRESSION  )
				{
					result.value.boolean_value = strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) >= 0 ;
				}
				else
					yyerror( "Unable to apply logical >= to heterogenous operands\n" );
			break;

			case GUID_EXPRESSION:
				if( operandResult[1].type == GUID_EXPRESSION  )
				{
					result.value.boolean_value = strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) >= 0 ;
				}
				else
					yyerror( "Unable to apply logical >= to heterogenous operands\n" );
			break;

			case BOOLEAN_EXPRESSION:
			case ENTITY_EXPRESSION:
			case PROPERTY_EXPRESSION:
					yyerror( "Unable to apply logical >= to boolean operands\n" );
			break;

			default:
			break;
		}

	return result;
}
/*--------------------------------------*/
/* 	> operator (more than)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_MORE_THAN( operator * oneOperatorNode  )
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
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value > operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value > (int) operandResult[1].value.float_value;
			break;

			case FLOAT_EXPRESSION:
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.float_value > (float) operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value >  operandResult[1].value.float_value;
			break;

			case STRING_EXPRESSION:
				if( operandResult[1].type == STRING_EXPRESSION  )
				{
					result.value.boolean_value = strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) > 0 ;
				}
				else
					yyerror( "Unable to apply logical > to heterogenous operands\n" );
			break;

			case GUID_EXPRESSION:
				if( operandResult[1].type == GUID_EXPRESSION  )
				{
					result.value.boolean_value = strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) > 0 ;
				}
				else
					yyerror( "Unable to apply logical > to heterogenous operands\n" );
			break;

			case BOOLEAN_EXPRESSION:
			case ENTITY_EXPRESSION:
			case PROPERTY_EXPRESSION:
					yyerror( "Unable to apply logical > to boolean operands\n" );
			break;

			default:
			break;
		}

	return result;
}
/*----------------------------------------------*/
/* 	<= operator (less or equal than)	*/
/*----------------------------------------------*/
expression_Value expression_Operator_T_LESS_OR_EQUAL_THAN( operator * oneOperatorNode  )
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
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value <= operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value <= (int) operandResult[1].value.float_value;
			break;

			case FLOAT_EXPRESSION:
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.float_value <= (float) operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value <=  operandResult[1].value.float_value;
			break;

			case STRING_EXPRESSION:
				if( operandResult[1].type == STRING_EXPRESSION  )
				{
					result.value.boolean_value = strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) <= 0 ;
				}
				else
					yyerror( "Unable to apply logical <= to heterogenous operands\n" );
			break;

			case GUID_EXPRESSION:
				if( operandResult[1].type == GUID_EXPRESSION  )
				{
					result.value.boolean_value = strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) <= 0 ;
				}
				else
					yyerror( "Unable to apply logical <= to heterogenous operands\n" );
			break;

			case BOOLEAN_EXPRESSION:
			case ENTITY_EXPRESSION:
			case PROPERTY_EXPRESSION:
					yyerror( "Unable to apply logical <= to boolean operands\n" );
			break;

			default:
			break;
		}

	return result;
}
/*--------------------------------------*/
/* 	< operator (less than)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_LESS_THAN( operator * oneOperatorNode  )
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
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value < operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value < (int) operandResult[1].value.float_value;
			break;

			case FLOAT_EXPRESSION:
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.float_value < (float) operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value <  operandResult[1].value.float_value;
			break;

			case STRING_EXPRESSION:
				if( operandResult[1].type == STRING_EXPRESSION  )
				{
					result.value.boolean_value = strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) < 0 ;
				}
				else
					yyerror( "Unable to apply logical < to heterogenous operands\n" );
			break;

			case GUID_EXPRESSION:
				if( operandResult[1].type == GUID_EXPRESSION  )
				{
					result.value.boolean_value = strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) < 0 ;
				}
				else
					yyerror( "Unable to apply logical < to heterogenous operands\n" );
			break;

			case BOOLEAN_EXPRESSION:
			case ENTITY_EXPRESSION:
			case PROPERTY_EXPRESSION:
					yyerror( "Unable to apply logical < to boolean operands\n" );
			break;

			default:
			break;
		}

	return result;
}

/*--------------------------------------*/
/* 	== operator (equal)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_EQUAL( operator * oneOperatorNode  )
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
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value == operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value == (int) operandResult[1].value.float_value;
			break;

			case FLOAT_EXPRESSION:
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.float_value == (float) operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value ==  operandResult[1].value.float_value;
			break;

			case STRING_EXPRESSION:
				if( operandResult[1].type == STRING_EXPRESSION  )
				{
					result.value.boolean_value = ! strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) != 0 ;
				}
				else
					yyerror( "Unable to apply logical == to heterogenous operands\n" );
			break;

			case GUID_EXPRESSION:
				if( operandResult[1].type == GUID_EXPRESSION  )
				{
					result.value.boolean_value = ! strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) != 0 ;
				}
				else
					yyerror( "Unable to apply logical == to heterogenous operands\n" );
			break;

			case BOOLEAN_EXPRESSION:
				if( operandResult[1].type == BOOLEAN_EXPRESSION  )
				{
					result.value.boolean_value = operandResult[0].value.boolean_value == operandResult[1].value.boolean_value ;
				}
				else
					yyerror( "Unable to apply logical == to heterogenous operands\n" );
			break;

			case ENTITY_EXPRESSION:
				yyerror( "Unable to apply logical == to entitys\n" );
			break;

			case PROPERTY_EXPRESSION:
				yyerror( "Unable to apply logical == to Propertys\n" );
			break;

			default:
			break;
		}

	return result;
}

/*--------------------------------------*/
/* 	!= operator (different)		*/
/*--------------------------------------*/
expression_Value expression_Operator_T_DIFFERENT( operator * oneOperatorNode  )
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
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value != operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value != (int) operandResult[1].value.float_value;
			break;

			case FLOAT_EXPRESSION:
				if( operandResult[1].type == INTEGER_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.float_value != (float) operandResult[1].value.integer_value;
				else if( operandResult[1].type == FLOAT_EXPRESSION )
					result.value.boolean_value = operandResult[0].value.integer_value != (int) operandResult[1].value.float_value;
			break;

			case STRING_EXPRESSION:
				if( operandResult[1].type == STRING_EXPRESSION  )
				{
					result.value.boolean_value = strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) != 0 ;
				}
				else
					yyerror( "Unable to apply logical != to heterogenous operands\n" );
			break;

			case GUID_EXPRESSION:
				if( operandResult[1].type == GUID_EXPRESSION  )
				{
					result.value.boolean_value = strcmp( operandResult[0].value.string_value , operandResult[1].value.string_value ) != 0 ;
				}
				else
					yyerror( "Unable to apply logical != to heterogenous operands\n" );
			break;

			case BOOLEAN_EXPRESSION:
				if( operandResult[1].type == BOOLEAN_EXPRESSION  )
				{
					result.value.boolean_value = operandResult[0].value.boolean_value != operandResult[1].value.boolean_value ;
				}
				else
					yyerror( "Unable to apply logical != to heterogenous operands\n" );
			break;

			case ENTITY_EXPRESSION:
				yyerror( "Unable to apply logical != to entitys\n" );
			break;

			case PROPERTY_EXPRESSION:
				yyerror( "Unable to apply logical != to Propertys\n" );
			break;

			default:
			break;
		}

	return result;
}

