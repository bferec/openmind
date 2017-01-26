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
/* dump contenu  expression				*/
/* -------------------------------------*/
void dumpExpressionValue( expression_Value ev )
{
	fprintf( stderr , "\ndebut DUMP expression\n" );
	switch( ev.type )
	{
		case INTEGER_EXPRESSION:
			fprintf( stderr , "value integer: \n" );
			fprintf( stderr , "value integer: [%d]\n" , ev.value.integer_value  );
		break;

		case FLOAT_EXPRESSION:
			fprintf( stderr , "value float: \n");
			fprintf( stderr , "value float: [%f]\n" , ev.value.float_value  );
		break;

		case BOOLEAN_EXPRESSION:
			fprintf( stderr , "value boolan: \n");
			fprintf( stderr, "value boolean [%d]\n" , ev.value.boolean_value ? "True" : "False" );
		break;

		case GUID_EXPRESSION:
			fprintf( stderr , "value Guid: \n");
			if( ev.value.guid_value != NULL )
				fprintf( stderr, "value guid [%s]\n" , ev.value.guid_value );
			else
				fprintf( stderr, "value guid non presente]\n" );
		break;

		case STRING_EXPRESSION:
			fprintf( stderr , "value string: \n");
			if( ev.value.string_value != NULL )
				fprintf( stderr, "value string [%s]\n" , ev.value.string_value );
			else
				fprintf( stderr, "value string non presente \n" );
		break;

		case VOID_EXPRESSION:
			fprintf( stderr, "Void expression\n" );
		break;

		default:
		fprintf( stderr, "Type expression inconnu\n");
		break;
	}
	fprintf( stderr , "fin DUMP expression\n" );

}

/* -------------------------------------*/
/* evaluation d'une constante		*/
/* -------------------------------------*/
expression_Value expression_Constante( syntaxTreeNode * oneNode )
{
expression_Value result;
constant * oneConstante;

	/* dumpSyntaxTreeNode(oneNode ); */
	oneConstante = & oneNode -> cste ;

	switch( oneConstante -> type )
	{
		case INT_CONSTANT_TYPE:
			result.type = INTEGER_EXPRESSION;
			result.value.integer_value =  oneConstante -> val.integer_value ;
			// fprintf( stderr, "retour expression constante ,  type integer , valeur : [%d]\n" , result.value.integer_value); 

		break;

		case FLOAT_CONSTANT_TYPE:
			result.type = FLOAT_EXPRESSION;
			result.value.float_value =  oneConstante -> val.float_value ;
			// fprintf( stderr, "retour expression constante ,  type float , valeur : [%f]\n" ,  result.value.float_value ); 
		break;

		case BOOLEEAN_CONSTANT_TYPE:
			result.type = BOOLEAN_EXPRESSION;
			result.value.boolean_value =  oneConstante -> val.boolean_value ;
			// fprintf( stderr, "retour expression constante ,  type Boolean : [%s]\n",  result.value.boolean_value ? "True" : "False" ); 
		break;

		case GUID_CONSTANT_TYPE:
			result.type = GUID_EXPRESSION;
			result.value.guid_value = oneConstante -> val.guid_value  ;
			// fprintf( stderr, "retour expression constante ,  type guid : [%s]\n" , result.value.guid_value ); 
		break;

		case STRING_CONSTANT_TYPE:
			result.type = STRING_EXPRESSION;
			result.value.string_value = oneConstante -> val.string_value  ;
			// fprintf( stderr, "retour expression constante ,  type string : [%s]\n"  , result.value.string_value  ); 
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
			// fprintf( stderr, "retour expression Variable ,  type integer , valeur : [%d]\n" , result.value.integer_value); 
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

	//dumpExpressionValue( result );

	return result;
}

/* -------------------------------------*/
/* interpretation d'une assignation	*/
/* -------------------------------------*/
expression_Value  expression_Operator_Assign(operator * oneOperatorNode) 
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
			if( currentVar -> val.string_value != NULL );	/* reallocation	*/
				free( currentVar -> val.string_value );

			currentVar -> val.string_value = (char *) malloc( strlen( operandResult.value.string_value) + 1 );
			if( currentVar -> val.string_value == NULL )
				yyerror( "Memory allocation for variable string content impossible\n");

			strcpy( currentVar -> val.string_value ,  operandResult.value.string_value );
			currentVar -> type = STRING_IDENTIFIER_TYPE;
			result.type = STRING_EXPRESSION;
			result.value.string_value =  currentVar -> val.string_value ;
		break;

		case GUID_EXPRESSION:
			currentVar -> type = GUID_IDENTIFIER_TYPE;
			if( currentVar -> val.guid_value == NULL );
			currentVar -> val.guid_value = (char *) malloc( GUID_LENGTH + 1 );

			if( currentVar -> val.guid_value == NULL )
				yyerror( "Memory allocation for variable Guid content impossible\n");

			strcpy( currentVar -> val.guid_value , operandResult.value.guid_value );
			currentVar -> type = GUID_IDENTIFIER_TYPE;
			result.type = GUID_EXPRESSION;
			result.value.guid_value = currentVar -> val.guid_value;
		break;

		case BOOLEAN_EXPRESSION:
			currentVar -> val.boolean_value = operandResult.value.boolean_value;	
			currentVar -> type = BOOLEAN_IDENTIFIER_TYPE;		
			result.type = BOOLEAN_EXPRESSION;
			result.value.boolean_value = currentVar -> val.boolean_value;
		break;

		case ENTITY_EXPRESSION:
			result.type = ENTITY_EXPRESSION;

		case PROPERTY_EXPRESSION:
			result.type = PROPERTY_EXPRESSION;
		break;

		default:
		break;
	}

	return result;
	
}
/* -------------------------------------*/
/* echo operator			*/
/* -------------------------------------*/
void  expression_Operator_ECHO(operator * oneOperatorNode ) 
{
constant * constante;
variable  * currentVar;
expression_Value * operandResult ;


	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value  ) );

	// fprintf( stderr , "echo %d operandes\n" , oneOperatorNode -> OperandsCount);

	for( int i = 0 ; i < oneOperatorNode -> OperandsCount ; i ++ )
	{
		// fprintf( stderr, "OPERATOR=ECHO - eval de  l'operande %d/%d\n" , i+1, oneOperatorNode -> OperandsCount ); 
		// dumpSyntaxTreeNode( oneOperatorNode -> operands[i] ); 

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

expressionType typeRetour;
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
/* - operator				*/
/*--------------------------------------*/
expression_Value expression_Operator_T_MINUS_SIGN( operator * oneOperatorNode  )
{
expression_Value result;
operator * currentOperator;
expression_Value * operandResult ;

expressionType typeRetour;
float resultNumber;

	operandResult = calloc( oneOperatorNode -> OperandsCount , sizeof(expression_Value ) );

	result.value.integer_value = result.value.float_value = resultNumber = 0;

	result.type = INTEGER_EXPRESSION;

	if( oneOperatorNode -> OperandsCount == 1 )
	{
		switch( operandResult[0].type )
		{
			case INTEGER_EXPRESSION:
				resultNumber = - operandResult[0].value.integer_value;
			break;

			case FLOAT_EXPRESSION:
				result.type = FLOAT_EXPRESSION;
				resultNumber =  - operandResult[1].value.float_value;
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
	}		
	else
	{

		for( int i = 1 ; i < oneOperatorNode -> OperandsCount ; i ++ )
		{
			operandResult[i] = expression( oneOperatorNode -> operands[i] );
			switch( operandResult[i].type )
			{
				case INTEGER_EXPRESSION:
					if( i > 0 )
						resultNumber -=  operandResult[i].value.integer_value;
					else 
						resultNumber =  operandResult[i].value.integer_value;
				break;

				case FLOAT_EXPRESSION:
					result.type = FLOAT_EXPRESSION;
					if( i > 0 )
						resultNumber -=  operandResult[i].value.float_value;
					else 
						resultNumber =  operandResult[i].value.float_value;
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
/* operateur interpretation 		*/
/* -------------------------------------*/
expression_Value expression_Operator( syntaxTreeNode * oneNode )
{
expression_Value result;
	
char guid[GUID_LENGTH]; 

operator * currentOperator;
	
	currentOperator = & oneNode-> oper;

	switch( currentOperator -> type )
	{
		case T_PLUS_SIGN:
			//fprintf( stderr, "expression_Operator_T_PLUS_SIGN()\n" ); 

			result =  expression_Operator_T_PLUS_SIGN( currentOperator ) ; 

			//fprintf( stderr, "Fin expression_Operator_T_PLUS_SIGN()\n" ); 
		break;

		case T_MINUS_SIGN:
			result =  expression_Operator_T_MINUS_SIGN( currentOperator ) ; 

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
			/* fprintf( stderr, "Operator_ECHO()\n" ); */
			result.type = VOID_EXPRESSION;
			expression_Operator_ECHO( currentOperator );
			/* fprintf( stderr, "Fin Operator_ECHO()\n" ); */
		break;

		case T_ASSIGN:
			/* fprintf( stderr, "Operator_Assign()\n" ); */
			result =  expression_Operator_Assign( currentOperator );
			/* fprintf( stderr, "Fin Operator_Assign()\n" ); */
		break;

		case T_AUTO:
		result.type = GUID_EXPRESSION;
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

	/* fprintf( stderr, "expression()\n" ); */

	if( oneNode == (syntaxTreeNode *) NULL )
	{
		yyerror( "NULL node expression \n" );
	}	

	switch( oneNode -> type )
	{
		case CONSTANT_SYNTAXTREE_NODETYPE:
			/* fprintf( stderr, "expression_Constante()\n" ); */
			result = expression_Constante( oneNode );
			/* fprintf( stderr, "Fin expression_Constante()\n" );  */
		break;

		case IDENTIFIER_SYNTAXTREE_NODETYPE:
			/* fprintf( stderr, "expression variable()\n" );  */
			result =  expression_Variable( oneNode );
			/* fprintf( stderr, "fin expression variable()\n" );  */
		break;

		case OPERATOR_SYNTAXTREE_NODETYPE:
			/* fprintf( stderr, "\nexpression_Operator()\n" );  */
			result = expression_Operator( oneNode  );
			/* fprintf( stderr, "FIN expression_Operator()\n" );  */
		break;
	}
	/* fprintf( stderr, "Fin expression()\n" ); */

	/* DumpVarList( ); */

	return result;
}
