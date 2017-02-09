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
#include <time.h>

#include "openmindlib.h"

#include "entity.h"
#include "openmindEntityList.h"
#include "openmindPropertyList.h"
#include "openmindvalue.h"


#include "openmindvarlist.h"
#include "openmindconstant.h"
#include "operator.h"
#include "syntaxtree.h"
#include "expressions.h"
#include "arithmeticOperator.h"
#include "logicalOperator.h"
#include "comparaisonOperator.h"
#include "assignationOperator.h"
#include "IncrDecrOperator.h"
#include "iterOperator.h"
#include "binaryOperator.h"
#include "alternatOperator.h"

#include "openmind.tab.h"

char guid[ GUID_LENGTH + 1 ];

/* -------------------------------------*/
/* evaluation d'une constante		*/
/* -------------------------------------*/
expression_Value expression_Constante( syntaxTreeNode * oneNode )
{
expression_Value result;
constant * oneConstante;

	oneConstante = & oneNode -> cste ;

	switch( oneConstante -> type )
	{
		case INT_CONSTANT_TYPE:
			result.type = INTEGER_EXPRESSION;
			result.value.integer_value =  oneConstante -> val.integer_value ;
			result.value.boolean_value =  oneConstante -> val.integer_value != 0 ;
		break;

		case FLOAT_CONSTANT_TYPE:
			result.type = FLOAT_EXPRESSION;
			result.value.float_value =  oneConstante -> val.float_value ;
			result.value.boolean_value =  oneConstante -> val.float_value != 0 ;
		break;

		case BOOLEEAN_CONSTANT_TYPE:
			result.type = BOOLEAN_EXPRESSION;
			result.value.boolean_value =  oneConstante -> val.boolean_value ;
		break;

		case GUID_CONSTANT_TYPE:
			result.type = GUID_EXPRESSION;
			strcpy( result.value.guid_value , oneConstante -> val.guid_value  );
		break;

		case STRING_CONSTANT_TYPE:
			result.type = STRING_EXPRESSION;
			result.value.string_value = oneConstante -> val.string_value  ;
		break;

		case CHAR_CONSTANT_TYPE:
			result.type = CHAR_EXPRESSION;
			result.value.char_value = oneConstante -> val.char_value  ;
			result.value.boolean_value =  oneConstante -> val.char_value != 0 ;
		break;
	}

	return result;
}

/* -------------------------------------*/
/* evaluation d'une variable		*/
/* -------------------------------------*/
expression_Value expression_Variable(syntaxTreeNode * oneNode )
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
			result.value.boolean_value =  oneVariable -> val.integer_value != 0 ;
		break;

		case FLOAT_IDENTIFIER_TYPE:
			result.type = FLOAT_EXPRESSION;
			result.value.float_value =  oneVariable -> val.float_value ;
			result.value.boolean_value =  oneVariable -> val.float_value != 0 ;
		break;

		case BOOLEAN_IDENTIFIER_TYPE:
			result.type = BOOLEAN_EXPRESSION;
			result.value.boolean_value =  oneVariable -> val.boolean_value ;
		break;

		case GUID_IDENTIFIER_TYPE:
			result.type = GUID_EXPRESSION;
			strcpy( result.value.guid_value , oneVariable -> val.guid_value );
		break;

		case CHAR_IDENTIFIER_TYPE:
			result.type = CHAR_EXPRESSION;
			result.value.char_value = oneVariable -> val.char_value;
			result.value.boolean_value =  oneVariable -> val.char_value != 0 ;
		break;

		case STRING_IDENTIFIER_TYPE:
			result.type = STRING_EXPRESSION;
			result.value.string_value =  oneVariable -> val.string_value;
		break;

		case ENTITY_IDENTIFIER_TYPE:
		case PROPERTY_IDENTIFIER_TYPE:
		break;

		default:
		break;
	}
	return result;
}

/* -------------------------------------*/
/* -------------------------------------*/
void DoEcho( syntaxTreeNode * oneListNode )
{
expression_Value operandResult ;

	operandResult = expression( oneListNode );

	switch( operandResult.type )
	{
		case INTEGER_EXPRESSION:
			printf( "%d" , operandResult.value.integer_value );
		break;

		case FLOAT_EXPRESSION:
			printf( "%f" , operandResult.value.float_value );
		break;

		case STRING_EXPRESSION:
			printf( "%s" , operandResult.value.string_value );
		break;

		case CHAR_EXPRESSION:
			putchar( operandResult.value.char_value );
		break;

		case GUID_EXPRESSION:
			printf( "%s" , operandResult.value.guid_value );
		break;

		case BOOLEAN_EXPRESSION:
			printf( "%s" , operandResult.value.boolean_value ? "True" : "False" );
		break;

		case ENTITY_EXPRESSION:
			fprintf( stderr , "name :%s guid %s" , operandResult.value.entity_value-> name , operandResult.value.entity_value-> guid);
		break;

		case PROPERTY_EXPRESSION:
		break;

		default:
			fprintf( stderr , "Unknown expression !\n" );
		break;
	}
}

/* -------------------------------------*/
/* echo operator			*/
/* -------------------------------------*/
void  expression_Operator_ECHO(operator * oneOperatorNode ) 
{

expression_Value * operandResult ;
syntaxTreeNode * operand;


	operand = oneOperatorNode -> operands[0];

	if( operand -> type ==  LIST_SYNTAXTREE_NODETYPE )
	{
		for( int x = 0 ; x < operand -> nodeListCount ; x ++ )
		{
			DoEcho( operand -> nodeList[ x ]   );
		}
	}
	else
		DoEcho( operand );
}

/*--------------------------------------*/
/* AUTO operator	  		*/
/* -------------------------------------*/
expression_Value  expression_Operator_T_AUTO()
{
expression_Value result;

	result.type = GUID_EXPRESSION;

	NewGuid(guid); 
	strcpy( result.value.guid_value , guid );

	return result;
}

/*--------------------------------------*/
/* CREATE operator			*/
/*--------------------------------------*/
expression_Value  expression_Operator_T_CREATE( operator * oneOperatorNode )
{
expression_Value result;
expression_Value guidResult ;
expression_Value nameResult ;
syntaxTreeNode * operand;


	operand = oneOperatorNode -> operands[0];

	guidResult = expression( operand -> guidNode );
	nameResult = expression( operand -> nameNode );

	switch( operand -> type )
	{
		case ENTITY_SYNTAXTREE_NODETYPE:
			

			result.value.entity_value = createEntity( guidResult.value.guid_value , nameResult.value.string_value , operand -> unique_name );
			if( result.value.entity_value == NULL )
				yyerror( "unable to create Entity, existing !\n" );
			result.type = ENTITY_EXPRESSION;
		break;

		case PROPERTY_SYNTAXTREE_NODETYPE:
			result.value.property_value = createProperty( guidResult.value.guid_value, nameResult.value.string_value , operand -> unique_name);
			if( result.value.property_value == NULL )
				yyerror( "unable to create Property, existing !\n" );
			result.type = PROPERTY_EXPRESSION;
		break;

		default:
		break;
	}
	return result;
}

/*--------------------------------------*/
/* operateur interpretation 		*/
/* -------------------------------------*/
expression_Value expression_Operator( syntaxTreeNode * oneNode )
{

operator * currentOperator;
expression_Value result;
	
	currentOperator = & oneNode-> oper;

	switch( currentOperator -> type )
	{
		case T_ECHO:
			result.type = VOID_EXPRESSION;
			expression_Operator_ECHO( currentOperator );
		break;

		case T_PLUS_SIGN:
			result =  expression_Operator_T_PLUS_SIGN( currentOperator ) ; 
		break;

		case T_MINUS_SIGN:
			result =  expression_Operator_T_MINUS_SIGN( currentOperator ) ; 
		break;

		case T_ASTERISK:
			result =  expression_Operator_T_ASTERISK( currentOperator ) ; 
		break;

		case T_SLASH:
			result =  expression_Operator_T_SLASH( currentOperator ) ; 
		break;

		case T_PLUS_EGAL_SIGN:
			result =  expression_Operator_T_PLUS_EGAL_SIGN( currentOperator );
		break;

		case T_MINUS_EGAL_SIGN:
			result =  expression_Operator_T_MINUS_EGAL_SIGN( currentOperator );
		break;

		case T_ASTERISK_EGAL:
			result =  expression_Operator_T_ASTERISK_EGAL( currentOperator );
		break;

		case T_SLASH_EGAL:
			result =  expression_Operator_T_SLASH_EGAL( currentOperator );
		break;

		case T_ASSIGN:
			result =  expression_Operator_T_ASSIGN( currentOperator );
		break;

		case T_INCR:
			result =  expression_Operator_T_INCR( currentOperator );
		break;

		case T_DECR:
			result =  expression_Operator_T_DECR( currentOperator );
		break;

		case T_OR:
			result = expression_Operator_T_OR( currentOperator ) ; 
		break;

		case T_AND:
			result = expression_Operator_T_AND( currentOperator ) ; 
		break;

		case T_NOT:
			result = expression_Operator_T_NOT( currentOperator ) ; 
		break;

		case T_XOR:
			result = expression_Operator_T_XOR( currentOperator ) ; 
		break;

		case T_BINARY_OR:
			result = expression_Operator_T_BINARY_OR( currentOperator ) ; 
		break;

		case T_BINARY_AND:
			result = expression_Operator_T_BINARY_AND( currentOperator ) ; 
		break;

		case T_BINARY_COMPLEMENT:
			result = expression_Operator_T_BINARY_COMPLEMENT( currentOperator ) ; 
		break;

		case T_LEFT_SHIFT:
			result = expression_Operator_T_LEFT_SHIFT( currentOperator ) ; 
		break;


		case T_RIGHT_SHIFT:
			result = expression_Operator_T_RIGHT_SHIFT( currentOperator ) ; 
		break;

		case T_DIFFERENT:
			result = expression_Operator_T_DIFFERENT( currentOperator ) ; 
		break;

		case T_EQUAL:
			result = expression_Operator_T_EQUAL( currentOperator ) ; 
		break;

		case T_LESS_THAN:
			result = expression_Operator_T_LESS_THAN( currentOperator ) ; 
		break;

		case T_LESS_OR_EQUAL_THAN:
			result = expression_Operator_T_LESS_OR_EQUAL_THAN( currentOperator ) ; 
		break;

		case T_MORE_THAN:
			result = expression_Operator_T_MORE_THAN( currentOperator ) ; 
		break;

		case T_MORE_OR_EQUAL_THAN:
			result = expression_Operator_T_MORE_OR_EQUAL_THAN( currentOperator ) ; 
		break;

		case T_AUTO:
			result = expression_Operator_T_AUTO();		
		break;

		case T_CREATE:
			result = expression_Operator_T_CREATE(currentOperator);
		break;

		case T_WHILE:
			result.type = VOID_EXPRESSION;
			expression_Operator_T_WHILE(currentOperator);
		break;

		case T_DO:
			result.type = VOID_EXPRESSION;
			expression_Operator_T_DO(currentOperator);
		break;

		case T_FOR:
			result.type = VOID_EXPRESSION;
			expression_Operator_T_FOR(currentOperator);
		break;

		case T_IF:
			result.type = VOID_EXPRESSION;
			expression_Operator_T_IF(currentOperator);
		break;

		case T_QUESTION:
			result = expression_Operator_T_QUESTION( currentOperator ) ; 
		break;

		default:
			yyerror("unknown operator\n");
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


	if( oneNode == (syntaxTreeNode *) NULL )
	{
		yyerror( "NULL node expression \n" );
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

		case ENTITY_SYNTAXTREE_NODETYPE:
		case PROPERTY_SYNTAXTREE_NODETYPE:
		break;

		default:
		break;
	}
	return result;
}
