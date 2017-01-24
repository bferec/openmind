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
#include "entity.h"
#include "openmindvalue.h"
#include "openmindvarlist.h"
#include "openmindconstant.h"
#include "operator.h"
#include "syntaxtree.h"

#include "expressions.h"

#include "openmind.tab.h"


/* -------------------------------------*/
/* interpretation d'une constante	*/
/* -------------------------------------*/

expression_Value expression_Constante(syntaxTreeNode * oneNode )
{
expression_Value result;	
constant * oneConstante;

	oneConstante = & oneNode -> cste ;

	/* fprintf( stderr, "constante\n" ); */

	switch( oneConstante -> type )
	{
		case INT_CONSTANT_TYPE:
			result.type = INTEGER_EXPRESSION;
			result.value.integer_value =  oneConstante -> val.integer_value ;
		break;

		case FLOAT_CONSTANT_TYPE:
			result.type = FLOAT_EXPRESSION;
			result.value.float_value =  oneConstante -> val.float_value ;
		break;

		case BOOLEEAN_CONSTANT_TYPE:
			result.type = BOOLEAN_EXPRESSION;
			result.value.boolean_value =  oneConstante -> val.boolean_value ;
		break;

		case GUID_CONSTANT_TYPE:
			result.type = GUID_EXPRESSION;
			result.value.guid_value = oneConstante -> val.guid_value  ;
		break;

		case STRING_CONSTANT_TYPE:
			result.type = STRING_EXPRESSION;
			result.value.string_value = oneConstante -> val.string_value  ;
		break;
	}

	return result;
}

/* -------------------------------------*/
/* interpretation d'une variable	*/
/* -------------------------------------*/
expression_Value  expression_Variable(syntaxTreeNode * oneNode )
{
expression_Value result;	
variable * oneVariable;

	oneVariable = oneNode -> var;

	switch( oneVariable -> type )
	{
		case UNKNOWN_IDENTIFIER_TYPE:		
		break;
		
		case INTEGER_IDENTIFIER_TYPE:
			result.type = INTEGER_EXPRESSION;
			result.value.integer_value =  oneVariable -> val.integer_value ;
		break;

		case FLOAT_IDENTIFIER_TYPE:
			result.type = FLOAT_EXPRESSION;
			result.value.float_value =  oneVariable -> val.float_value ;
		break;

		case BOOLEAN_IDENTIFIER_TYPE:
			result.type = BOOLEAN_EXPRESSION;
			result.value.boolean_value =  oneVariable -> val.boolean_value ;
		break;

		case GUID_IDENTIFIER_TYPE:
			result.type = GUID_EXPRESSION;
			result.value.guid_value = oneVariable -> val.guid_value;
		break;

		case STRING_IDENTIFIER_TYPE:
			result.type = STRING_EXPRESSION;
			result.value.string_value =  oneVariable -> val.string_value;
		break;

		case ENTITY_IDENTIFIER_TYPE:
		case PROPERTY_IDENTIFIER_TYPE:
		break;
	}

	return result;
}


/* -------------------------------------*/
/* interpretation d'une assignation	*/
/* -------------------------------------*/
void  assign(operator * oneOperatorNode) 
{
variable  * currentVar;
constant * constante;
variable * rvalue_var;

	currentVar = oneOperatorNode -> operands[0]-> var;

	switch( oneOperatorNode -> operands[1] -> type )
		{
			case CONSTANT_SYNTAXTREE_NODETYPE:
				constante =  & oneOperatorNode -> operands[1]-> cste;

				switch( constante -> type )
				{
					case 	INT_CONSTANT_TYPE:
						currentVar -> type = INTEGER_IDENTIFIER_TYPE;
						currentVar -> val.integer_value  =  constante -> val.integer_value;
						
					break;

					case 	FLOAT_CONSTANT_TYPE:
						currentVar -> type = FLOAT_IDENTIFIER_TYPE;
						currentVar -> val.float_value  = constante -> val.float_value;
					break;

					case	BOOLEEAN_CONSTANT_TYPE:
						currentVar -> type = BOOLEAN_IDENTIFIER_TYPE;
						currentVar -> val.boolean_value  = constante -> val.boolean_value;
					break;

					case 	GUID_CONSTANT_TYPE:
						currentVar -> type = GUID_IDENTIFIER_TYPE;
						currentVar -> val.guid_value = (char *) malloc( GUID_LENGTH + 1 );
						strcpy( currentVar -> val.guid_value , constante -> val.guid_value );

					break;

					case	STRING_CONSTANT_TYPE:
						if( currentVar == NULL )
						{
							yyerror( "Variable non definie\n" );
						}
						currentVar -> type = STRING_IDENTIFIER_TYPE;
						if( currentVar -> val.string_value != NULL )
							free( currentVar -> val.string_value );
						currentVar -> val.string_value = (char *) malloc( strlen( constante -> val.string_value ) + 1 );
						if( currentVar -> val.string_value == NULL )
							yyerror( "Memory allocation for variable string content impossible\n");
						strcpy( currentVar -> val.string_value , constante -> val.string_value );
						
					break;
				}
			break;

			case IDENTIFIER_SYNTAXTREE_NODETYPE:

				rvalue_var =  oneOperatorNode -> operands[1]-> var;

				switch( rvalue_var -> type )
				{
					case 	INTEGER_IDENTIFIER_TYPE:
						currentVar -> type = INTEGER_IDENTIFIER_TYPE;
						currentVar -> val.integer_value  =  rvalue_var -> val.integer_value;
					break;

					case 	FLOAT_IDENTIFIER_TYPE:
						currentVar -> type = FLOAT_IDENTIFIER_TYPE;
						currentVar -> val.float_value  =  rvalue_var -> val.float_value;
					break;

					case	BOOLEAN_IDENTIFIER_TYPE:
						currentVar -> type = BOOLEAN_IDENTIFIER_TYPE;
						currentVar -> val.boolean_value  = rvalue_var -> val.boolean_value;
					break;

					case 	GUID_IDENTIFIER_TYPE:
						currentVar -> type = GUID_IDENTIFIER_TYPE;
						strcpy( currentVar -> val.guid_value , rvalue_var -> val.guid_value );					
					break;

					case	STRING_IDENTIFIER_TYPE:
						currentVar -> type = STRING_IDENTIFIER_TYPE;
						if( currentVar -> val.string_value != NULL )
							free( currentVar -> val.string_value );
						currentVar -> val.string_value = (char *) malloc( strlen( rvalue_var -> val.string_value ) + 1 );
						strcpy( currentVar -> val.string_value , rvalue_var -> val.string_value );
					break;
				}			
			break;
		}	
	
}
/* -------------------------------------*/
/* echo operator			*/
/* -------------------------------------*/
void  echo(operator * oneOperatorNode ) 
{
constant * constante;
variable  * currentVar;
expression_Value * operandResult ;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(value ) );

	for( int i = 0 ; i < oneOperatorNode -> OperandsCount ; i ++ )
	{
		operandResult[i] = expression( oneOperatorNode -> operands[i] );
		switch( operandResult[i].type )
		{
			case INTEGER_EXPRESSION:
				printf( "%d" , operandResult-> value.integer_value );
			break;

			case FLOAT_EXPRESSION:
				printf( "%f" , operandResult-> value.float_value );
			break;

			case STRING_EXPRESSION:
				printf( "%s" , operandResult-> value.string_value );
			break;

			case GUID_EXPRESSION:
				printf( "%s" , operandResult-> value.guid_value );
			break;

			case BOOLEAN_EXPRESSION:
				printf( "%d" , operandResult -> value.boolean_value ? "True" : "False" );
			break;

			case ENTITY_EXPRESSION:
			case PROPERTY_EXPRESSION:
			break;

			default:
			break;
		}
	}

	free( operandResult );
}

/*--------------------------------------*/
/* + operator				*/
/*--------------------------------------*/
expression_Value expression_Operator_T_PLUS_SIGN( operator * oneOperatorNode  )
{
expression_Value result;
operator * currentOperator;
expression_Value * operandResult ;


	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(value ) );

	for( int i = 0 ; i < oneOperatorNode -> OperandsCount ; i ++ )
	{
		operandResult[i] = expression( oneOperatorNode -> operands[i] );
		switch( operandResult[i].type )
		{
			case INTEGER_EXPRESSION:
			result.type = INTEGER_EXPRESSION;
			result.value.integer_value +=  operandResult[i].value.integer_value;
			break;

			case FLOAT_EXPRESSION:
				result.type = FLOAT_EXPRESSION;
				result.value.float_value +=  operandResult[i].value.float_value;
			break;

			case STRING_EXPRESSION:
			break;

			case GUID_EXPRESSION:
			break
;
			case BOOLEAN_EXPRESSION:
			break;

			case ENTITY_EXPRESSION:
			break;

			case PROPERTY_EXPRESSION:
			break;

			default:
			break;
		}
	}
	
	free( operandResult );

	return result;
}

/*--------------------------------------*/
/* operateur interpretation 		*/
/* -------------------------------------*/
expression_Value expression_Operator( syntaxTreeNode * oneNode )
{
expression_Value result;	
char guid[GUID_LENGTH]; 

operator * currentOperator;
	
	/* fprintf( stderr, "Operateur\n" ); */

	currentOperator = & oneNode-> oper;

	switch( currentOperator -> type )
	{
		case T_PLUS_SIGN:
			result =  expression_Operator_T_PLUS_SIGN( currentOperator ) ; 
		break;

		case T_MINUS_SIGN:
			/* if( currentOper-> operandscount == 2 )
				return expression( currentOperator-> operands[0] ) -  expression( currentOperator-> operands[1] ) ;
			   else
				return - expression( currentOperator-> operands[0] ) ;
			*/
		break;

		case T_ASTERISK:
			/* return expression( currentOperator-> operands[0] ) *  expression( currentOperator-> operands[1] ) ; */
		break;

		case T_SLASH:
			/* return expression( currentOperator-> operands[0] ) /  expression( currentOperator-> operands[1] ) ; */
		break;

		case T_ECHO:
			echo( currentOperator );
		break;

		case T_ASSIGN:
			assign( currentOperator );
		break;

		case T_AUTO:
		NewGuid( guid); 
		strcpy( result.value.guid_value , guid );		
		break;
	}

	return result;
}


/* -------------------------------------*/
/* interpretation d'une expression	*/
/* -------------------------------------*/
expression_Value expression( syntaxTreeNode * oneNode )
{
expression_Value result;

	/* fprintf( stderr, "expression\n" ); */

	if( oneNode == (syntaxTreeNode *) NULL )
	{
		return result;	
	}	

	switch( oneNode -> type )
	{
		case CONSTANT_SYNTAXTREE_NODETYPE:
			result = expression_Constante( oneNode );
		break;

		case IDENTIFIER_SYNTAXTREE_NODETYPE:
			result =  expression_Variable( oneNode );
		break;

		case OPERATOR_SYNTAXTREE_NODETYPE:
			result = expression_Operator( oneNode  );
		break;
	}
	return result;
}
