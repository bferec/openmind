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
#include "openmind.tab.h"

/* -------------------------------------*/
/* interpretation d'une constante	*/
/* -------------------------------------*/

value expression_Constante(syntaxTreeNode * oneNode,  constant * oneConstante )
{
value result;	

	fprintf( stderr, "constante\n" );
	switch( oneConstante -> type )
	{
		case INT_CONSTANT_TYPE:

			result.integer_value =  oneConstante -> val.integer_value ;
		break;

		case FLOAT_CONSTANT_TYPE:
			result.float_value =  oneConstante -> val.float_value ;
		break;

		case BOOLEEAN_CONSTANT_TYPE:
			result.boolean_value =  oneConstante -> val.boolean_value ;
		break;

		case GUID_CONSTANT_TYPE:
			strcpy( result.guid_value ,  oneConstante -> val.guid_value ) ;
		break;

		case STRING_CONSTANT_TYPE:
			strcpy( result.string_value ,  oneConstante -> val.string_value ) ;
		break;
	}

	return result;
}

/* -------------------------------------*/
/* interpretation d'une variable	*/
/* -------------------------------------*/
value  expression_Variable(syntaxTreeNode * oneNode , variable * oneVariable )
{
value result;	

	

	fprintf( stderr, "Variable\n" );

	switch( oneVariable -> type )
	{
		case UNKNOWN_IDENTIFIER_TYPE:		
		break;
		
		case INTEGER_IDENTIFIER_TYPE:
			result.integer_value =  oneVariable -> val.integer_value ;
		break;

		case FLOAT_IDENTIFIER_TYPE:
			result.float_value =  oneVariable -> val.float_value ;
		break;

		case BOOLEAN_IDENTIFIER_TYPE:
			result.boolean_value =  oneVariable -> val.boolean_value ;
		break;

		case GUID_IDENTIFIER_TYPE:
			strcpy( result.guid_value , oneVariable -> val.guid_value );
		break;

		case STRING_IDENTIFIER_TYPE:
			strcpy( result.string_value ,  oneVariable -> val.string_value ) ;
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
void  assign(operator * oneOperNode) 
{
variable  * currentVar;
	currentVar = & oneOperNode -> operands[0]-> var;
	
}
/* -------------------------------------*/
/* interpretation d'une operateur	*/
/* -------------------------------------*/
void  echo(operator * oneOperNode) 
{
constant * constante;
variable  * currentVar;

	for( int i = 0 ; i < oneOperNode -> OperandsCount ; i ++ )
	{
		switch( oneOperNode -> operands[i] -> type )
		{
			case CONSTANT_SYNTAXTREE_NODETYPE:
				
				constante =  & oneOperNode -> operands[i]-> cste;
				switch( constante -> type )
				{
					case 	INT_CONSTANT_TYPE:
						printf( "%d" , constante -> val.integer_value );
					break;

					case 	FLOAT_CONSTANT_TYPE:
						printf( "%f" , constante -> val.float_value );
					break;

					case	BOOLEEAN_CONSTANT_TYPE:
						printf( "%d" , constante -> val.boolean_value ? "True" : "False" );
					break;

					case 	GUID_CONSTANT_TYPE:
						printf( "%ds" , constante -> val.guid_value );
					break;

					case	STRING_CONSTANT_TYPE:
						printf( "%ds" , constante-> val.string_value );
					break;
				}
			break;

			case IDENTIFIER_SYNTAXTREE_NODETYPE:

				currentVar = & oneOperNode -> operands[i]-> var;
				switch( currentVar -> type )
				{
					case 	INTEGER_IDENTIFIER_TYPE:
						printf( "%d" , currentVar-> val.integer_value );
					break;

					case 	FLOAT_IDENTIFIER_TYPE:
						printf( "%f" , currentVar -> val.float_value );
					break;

					case	BOOLEAN_IDENTIFIER_TYPE:
						printf( "%d" , currentVar -> val.boolean_value ? "True" : "False" );
					break;

					case 	GUID_IDENTIFIER_TYPE:
						printf( "%ds" , currentVar -> val.guid_value );
					break;

					case	STRING_IDENTIFIER_TYPE:
						printf( "%ds" , currentVar -> val.string_value );
					break;
				}			
			break;
		}
	}
}

/* -------------------------------------*/
/* interpretation d'une operateur	*/
/* -------------------------------------*/
value expression_Operator( syntaxTreeNode * oneNode )
{
value result;	
char guid[GUID_LENGTH]; 

	operator * currentOper;
	fprintf( stderr, "Operateur\n" );

	currentOper = & oneNode-> oper;

	switch( currentOper -> type )
	{
		case T_PLUS_SIGN:
			/* return expression( currentOper-> operands[0] ) +  expression( currentOper-> operands[1] ) ; */
		break;

		case T_MINUS_SIGN:
			/* if( currentOper-> operandscount == 2 )
				return expression( currentOper-> operands[0] ) -  expression( currentOper-> operands[1] ) ;
			   else
				return - expression( currentOper-> operands[0] ) ;
			*/
		break;

		case T_ASTERISK:
			/* return expression( currentOper-> operands[0] ) *  expression( currentOper-> operands[1] ) ; */
		break;

		case T_SLASH:
			/* return expression( currentOper-> operands[0] ) /  expression( currentOper-> operands[1] ) ; */
		break;

		case T_ECHO:
			echo( currentOper );
		break;

		case T_ASSIGN:
			assign( currentOper );
		break;

		case T_AUTO:
		NewGuid( guid); 
		strcpy( result.guid_value , guid );		
		break;
	}

	return result;
}


/* -------------------------------------*/
/* interpretation d'une expression	*/
/* -------------------------------------*/
value expression( syntaxTreeNode * oneNode )
{
value result;

	fprintf( stderr, "expression\n" );

	if( oneNode == (syntaxTreeNode *) NULL )
	{
		return result;	
	}	

	switch( oneNode -> type )
	{
		case CONSTANT_SYNTAXTREE_NODETYPE:
			result = expression_Constante( oneNode , & oneNode -> cste );
		break;

		case IDENTIFIER_SYNTAXTREE_NODETYPE:
			result =  expression_Variable( oneNode , & oneNode -> var );
		break;

		case OPERATOR_SYNTAXTREE_NODETYPE:
			result = expression_Operator( oneNode  );
		break;
	}
	return result;
}
