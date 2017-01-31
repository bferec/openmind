/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
/* 							*/
/* debugTools.c						*/
/* 							*/
/* -----------------------------------------------------*/
/* -----------------------------------------------------*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
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

char buffer[MAXLENGTH_STRING + 1 ];

extern variable_node * var_list ;


/* -------------------------------------*/
/* dump contenu  expression		*/
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

/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
void dumpvarNode( variable_node * oneVariableNode) 
{
	if( oneVariableNode )
	{
		fprintf( stderr , "variable node %s\n" , oneVariableNode-> v -> ident );
	}
}

/* -----------------------------------------------------*/
/* affichage de toutes les variables			*/
/* -----------------------------------------------------*/
void DumpVarList( )
{
	fprintf( stderr , "\nDUMP:\n");


variable_node * n;
	n = var_list;
	while( n )
	{
		dumpvarNode( n );
		n= n -> next;	
	}
	fprintf( stderr , "\nFIN DU DUMP:\n");
}

char * getOperandeTypeLibelle( syntaxTreeNode * oneNode )
{
	switch( oneNode -> type )
	{
		case CONSTANT_SYNTAXTREE_NODETYPE:
		strcpy( buffer , "constant type" );
		break;
		case IDENTIFIER_SYNTAXTREE_NODETYPE:
		strcpy( buffer , "Variable type" );
		break;
		case OPERATOR_SYNTAXTREE_NODETYPE:
		strcpy( buffer , "operator Type" );
		break;
		case ENTITY_SYNTAXTREE_NODETYPE:
		strcpy( buffer , "Entity Type" );
		break;
		case PROPERTY_SYNTAXTREE_NODETYPE:
		strcpy( buffer , "Property Type" );
		break;
	}
	return buffer;
}

/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
char *  getOperatorLibelle( int oneOperatorType )
{

	switch( oneOperatorType )
	{
		case T_ASSIGN:
		strcpy( buffer , "=" );
		break;
		case T_PLUS_SIGN:
			strcpy( buffer , "+" );
		break;
		case T_MINUS_SIGN:
			strcpy( buffer , "-" );
		break;
		case T_ASTERISK:
			strcpy( buffer , "*" );
		break;
		case T_SLASH:
			strcpy( buffer , "/" );
		break;
		case T_ECHO:
			strcpy( buffer , "echo" );
		break;
	}
return buffer;
}

/* -----------------------------------------------------*/
/* dump noeud						*/
/* -----------------------------------------------------*/
void  dumpSyntaxTreeNode(syntaxTreeNode * oneNode )
{

	fprintf( stderr , "\nDEBUT dumpSyntaxTreeNode\n" );
	switch( oneNode -> type )
	{
		case CONSTANT_SYNTAXTREE_NODETYPE:
			switch( oneNode->cste.type  )
			{
				case 	INT_CONSTANT_TYPE:
					 fprintf( stderr , "Node constante Integer  :[%d]\n" , oneNode -> cste.val.integer_value ); 
				break;

				case 	FLOAT_CONSTANT_TYPE:
					 fprintf( stderr , "Node constante  Float  :[%f]\n" , oneNode -> cste.val.float_value ); 
				break;

				case	BOOLEEAN_CONSTANT_TYPE:
					 fprintf( stderr , "Node constante  Boolean : [%s]\n" , oneNode -> cste.val.boolean_value ? "#True" : "#False"  ); 
				break;

				case 	GUID_CONSTANT_TYPE:
					 fprintf( stderr , "Node constante  guid : [%s]\n" , oneNode -> cste.val.guid_value); 
				break;

				case	STRING_CONSTANT_TYPE:
					 fprintf( stderr , "Node constante  string : [%s]\n" , oneNode -> cste.val.string_value); 
				break;
		}
		break;

		case IDENTIFIER_SYNTAXTREE_NODETYPE:
			 fprintf( stderr , "Node Identifier: %s\n", oneNode->var -> ident  );  
		break;

		case OPERATOR_SYNTAXTREE_NODETYPE:
			 fprintf( stderr , "Node operateur:[%s] comportant %d operandes \n", getOperatorLibelle(oneNode -> oper.type ), oneNode -> oper.OperandsCount ); 
		break;
	}
	fprintf( stderr , "FIN dumpSyntaxTreeNode\n" );
}


