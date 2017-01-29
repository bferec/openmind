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

#include "openmindlib.h"
#include "entity.h"
#include "openmindvalue.h"
#include "openmindvarlist.h"

#include "openmindconstant.h"
#include "operator.h"

#include "syntaxtree.h"

#include "openmind.tab.h"

char buffer[MAXLENGTH_STRING + 1 ];


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


