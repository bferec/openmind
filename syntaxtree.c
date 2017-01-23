/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
/* 							*/
/* syntaxtree.c						*/
/* 							*/
/* -----------------------------------------------------*/
/* -----------------------------------------------------*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "openmindlib.h"

#include "openmind.tab.h"


/* -----------------------------------------------------*/
/* dump noeud						*/
/* -----------------------------------------------------*/
void  dumpSyntaxTreeNode(syntaxTreeNode * oneNode )
{
char op;

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
			
			switch( oneNode -> oper.type )
			{
				case T_ASSIGN:
				op = '=';
				break;

				case T_PLUS_SIGN:
					op = '+';
				break;
				case T_MINUS_SIGN:
					op = '-';
				break;
				case T_ASTERISK:
					op = '*';
				break;
				case T_SLASH:
					op = '/';
				break;
			}
			fprintf( stderr , "Node operateur [ %c ] %d operandes \n", op , oneNode -> oper.OperandsCount );
			for( int i = 0 ; i < oneNode->oper.OperandsCount ; i ++ )
			{
				dumpSyntaxTreeNode(oneNode -> oper. operands[i] );
			}
		break;
	}
}



/* -----------------------------------------------------*/
/* allocation memoire pour un noeud 			*/
/* de l'arbre syntaxique 				*/
/* -----------------------------------------------------*/
syntaxTreeNode * syntaxTreeNodeAlloc()
{
	syntaxTreeNode * resultNode;
	resultNode = (syntaxTreeNode *) malloc( sizeof( syntaxTreeNode ) );
	if( resultNode == (syntaxTreeNode *) NULL )
		yyerror("SyntaxtreeNode allocation : Out of Memory" );
	return resultNode;
}


/* -----------------------------------------------------*/
/* creation de noeud constante				*/
/* -----------------------------------------------------*/
syntaxTreeNode * Const( ConstantType oneType, void * oneconstantPtr )
{
	syntaxTreeNode * resultNode;
	resultNode = syntaxTreeNodeAlloc();
	resultNode -> type = CONSTANT_SYNTAXTREE_NODETYPE;
	resultNode -> cste.type = oneType;

	switch( oneType )
	{
		case 	INT_CONSTANT_TYPE:
			resultNode -> cste.val.integer_value = * (int *) oneconstantPtr;
			/* fprintf( stderr , "Const()  Integer  :[%d]\n" , resultNode -> cste.val.integer_value ); */
		break;

		case 	FLOAT_CONSTANT_TYPE:
			resultNode -> cste.val.float_value = * (float *) oneconstantPtr;
			/* fprintf( stderr , "Const()  Float  :[%f]\n" , resultNode -> cste.val.float_value ); */
		break;

		case	BOOLEEAN_CONSTANT_TYPE:
			resultNode -> cste.val.boolean_value = * (int *) oneconstantPtr;
			/* fprintf( stderr , "Const()  Boolean : [%s]\n" , resultNode -> cste.val.boolean_value ? "#True" : "#False"  ); */
		break;

		case 	GUID_CONSTANT_TYPE:
			resultNode -> cste.val.guid_value =  (char *) malloc( GUID_LENGTH + 1 );
			if( resultNode -> cste.val.guid_value == NULL )
				yyerror("Guid value of constant allocation : Out of Memory" );
			strcpy( resultNode -> cste.val.guid_value , (char *) oneconstantPtr );
			/* fprintf( stderr , "Const()  guid : [%s]\n" , resultNode -> cste.val.guid_value); */
		break;

		case	STRING_CONSTANT_TYPE:
			resultNode -> cste.val.string_value =  (char *) malloc( MAXLENGTH_STRING  + 1);
			if( resultNode -> cste.val.string_value == NULL )
				yyerror("string value of constant allocation : Out of Memory" );
			strcpy( resultNode -> cste.val.string_value , (char *) oneconstantPtr );
			/* fprintf( stderr , "Const() type string : [%s]\n" , resultNode -> cste.val.string_value); */
		break;
	}

return resultNode;
}

/* -----------------------------------------------------*/
/* creation de noeud variable				*/
/* -----------------------------------------------------*/
syntaxTreeNode * Var( VarType oneType, variable * oneVarPtr )
{
syntaxTreeNode * resultNode;


	resultNode = syntaxTreeNodeAlloc();

	resultNode -> type = IDENTIFIER_SYNTAXTREE_NODETYPE;

	resultNode-> var = oneVarPtr ;
	resultNode-> var -> type = oneType;
	/* fprintf( stderr , "var() %s\n" , resultNode->var-> ident);  */
	return resultNode;
}

/* -----------------------------------------------------*/
/* creation de noeud operateur				*/
/* -----------------------------------------------------*/
syntaxTreeNode * oper( int oneOper, int OperandsCount, ...)
{
	syntaxTreeNode * resultNode;
	resultNode = syntaxTreeNodeAlloc();
	va_list listOperands;
	
	/* fprintf( stderr , "oper() type %d\n" , oneOper ); */
	resultNode = syntaxTreeNodeAlloc();
	resultNode -> type = OPERATOR_SYNTAXTREE_NODETYPE;
	resultNode -> oper.type = oneOper;
	resultNode -> oper.OperandsCount = OperandsCount;

	/* operand_number; */
	if( OperandsCount > 0 )
	{
		/* fprintf( stderr , "%d operands memory allocation\n" , OperandsCount ); */
		resultNode -> oper.operands = (struct syntaxTreeNode_ * *) calloc( OperandsCount , sizeof( syntaxTreeNode *) );

		if( resultNode -> oper.operands == (struct syntaxTreeNode_ * *) NULL )
			yyerror("operands of operator vector allocation : Out of Memory" );
		for( int i = 0 ; i < OperandsCount  ; i ++ )
		{
			resultNode -> oper.operands[i] = ( syntaxTreeNode *)  malloc( sizeof( syntaxTreeNode ) );
			if( resultNode -> oper.operands[i]  == (syntaxTreeNode *) NULL )
				yyerror("operands n of operator vector allocation : Out of Memory");
		}

		va_start( listOperands, OperandsCount );
		for( int i = 0 ; i < OperandsCount  ; i ++ )
		{
			/* fprintf(stderr , "affectation de l'operande %d\n" , i ); */
			memcpy( resultNode -> oper.operands[i] , va_arg( listOperands , syntaxTreeNode * ) , sizeof(syntaxTreeNode) );
		}
		va_end( listOperands );
	}
	return resultNode;
}


/* -----------------------------------------------------*/
/* suppression d'un noeud constante 			*/ 
/* -----------------------------------------------------*/
void Free_ConstantSyntaxTreeNode( syntaxTreeNode * oneNode  )
{
	
	switch( oneNode-> cste.type )
	{
		case 	GUID_CONSTANT_TYPE:
			free( oneNode -> cste.val.guid_value );
		break;

		case	STRING_CONSTANT_TYPE:
			free( oneNode -> cste.val.string_value );
		break;
	}	
	free( oneNode );
}
/* -----------------------------------------------------*/
/* suppression d'un noeud variable 			*/ 
/* -----------------------------------------------------*/
void Free_VarSyntaxTreeNode( syntaxTreeNode * oneNode  )
{
	switch( oneNode-> var -> type  )
	{
		case 	GUID_IDENTIFIER_TYPE:
			free( oneNode -> var-> val.guid_value );
		break;

		case	STRING_IDENTIFIER_TYPE:
			free( oneNode -> var -> val.string_value );
		break;
	}	
	fprintf( stderr , "liberation de la variable %s\n" , oneNode -> var -> ident);
	free( oneNode -> var -> ident );
	free( oneNode -> var );
	free( oneNode );
}
/* -----------------------------------------------------*/
/* suppression d'un noeud operateur			*/ 
/* -----------------------------------------------------*/
void Free_OperSyntaxTreeNode( syntaxTreeNode * oneNode  )
{
	for( int i = 0 ; i < oneNode -> oper.OperandsCount ; i ++ )
	{
		switch( oneNode -> oper.operands[i] -> type )
		{
			case CONSTANT_SYNTAXTREE_NODETYPE:
				Free_ConstantSyntaxTreeNode( oneNode -> oper.operands[i] );
			break;

			case IDENTIFIER_SYNTAXTREE_NODETYPE:
				Free_VarSyntaxTreeNode( oneNode -> oper.operands[i] );
			break;
		}
	}

	free( oneNode -> oper.operands );

	free( oneNode );
}

/* -----------------------------------------------------*/
/* suppression d'un noeud				*/
/* -----------------------------------------------------*/
void Free_SyntaxTreeNode( syntaxTreeNode * oneNode )
{
	switch( oneNode -> type )
	{
		case CONSTANT_SYNTAXTREE_NODETYPE:
			Free_ConstantSyntaxTreeNode( oneNode );
		break;

		case IDENTIFIER_SYNTAXTREE_NODETYPE:
			Free_VarSyntaxTreeNode( oneNode );
		break;

		case OPERATOR_SYNTAXTREE_NODETYPE:
			Free_OperSyntaxTreeNode( oneNode );
		break;
	}
}

