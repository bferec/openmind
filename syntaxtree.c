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



/* -----------------------------------------------------*/
/* racine de l'arbre syntaxique				*/
/* -----------------------------------------------------*/
syntaxTreeNode * syntaxTree;

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
		break;

		case 	FLOAT_CONSTANT_TYPE:
			resultNode -> cste.val.float_value = * (float *) oneconstantPtr;
		break;

		case	BOOLEEAN_CONSTANT_TYPE:
			resultNode -> cste.val.boolean_value = * (int *) oneconstantPtr;
		break;

		case 	GUID_CONSTANT_TYPE:
			resultNode -> cste.val.guid_value =  (char *) malloc( GUID_LENGTH + 1 );
			if( resultNode -> cste.val.guid_value == NULL )
				yyerror("Guid value of constant allocation : Out of Memory" );
			strcpy( resultNode -> cste.val.guid_value , (char *) oneconstantPtr );
		break;

		case	STRING_CONSTANT_TYPE:
			resultNode -> cste.val.string_value =  (char *) malloc( MAXLENGTH_STRING  + 1);
			if( resultNode -> cste.val.string_value == NULL )
				yyerror("string value of constant allocation : Out of Memory" );
			strcpy( resultNode -> cste.val.string_value , (char *) oneconstantPtr );
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

	resultNode -> var.type = oneType;

	switch( oneType )
	{
		case UNKNOWN_IDENTIFIER_TYPE:
		break;

		case INTEGER_IDENTIFIER_TYPE:
			resultNode -> var.val.integer_value = * (int *) oneVarPtr;
		break;

		case FLOAT_IDENTIFIER_TYPE:
			resultNode -> var.val.float_value = * (float *) oneVarPtr;
		break;

		case STRING_IDENTIFIER_TYPE: 
			resultNode -> var.val.string_value =  (char *) malloc( MAXLENGTH_STRING  + 1);
			if( resultNode -> var.val.string_value == NULL )
				yyerror("String value of identifier allocation : Out of Memory" );
			strcpy( resultNode -> var.val.string_value , (char *) oneVarPtr );
		break;

		case BOOLEAN_IDENTIFIER_TYPE:
			resultNode -> var.val.boolean_value = * (int *) oneVarPtr;
		break;

		case GUID_IDENTIFIER_TYPE:
			resultNode -> var.val.guid_value =  (char *) malloc( GUID_LENGTH + 1 );
			if( resultNode -> var.val.guid_value == NULL )
				yyerror("Guid value of identifier allocation : Out of Memory" );
			strcpy( resultNode -> var.val.guid_value , (char *) oneVarPtr );
		break;

		case ENTITY_IDENTIFIER_TYPE:
		break;

		case PROPERTY_IDENTIFIER_TYPE :
		break;
	}
	return resultNode;
}

/* -----------------------------------------------------*/
/* creation de noeud operateur				*/
/* -----------------------------------------------------*/
syntaxTreeNode * oper( int oneOper, int OperandsCount, ...)
{
	syntaxTreeNode * resultNode;
	resultNode = syntaxTreeNodeAlloc();
	va_list parametersInfos;
	
	resultNode = syntaxTreeNodeAlloc();
	resultNode -> type = OPERATOR_SYNTAXTREE_NODETYPE;
	resultNode -> oper.type = oneOper;
	resultNode -> oper.OperandsCount = OperandsCount;

	/* operand_number; */
	resultNode -> oper.operands = (struct syntaxTreeNode_ * *) calloc( OperandsCount , sizeof( struct syntaxTreeNode_ * ) );
	if( resultNode -> oper.operands == (struct syntaxTreeNode_ * *) NULL )
		yyerror("operands of operator vector allocation : Out of Memory" );
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
	switch( oneNode-> var.type  )
	{
		case 	GUID_IDENTIFIER_TYPE:
			free( oneNode -> var.val.guid_value );
		break;

		case	STRING_IDENTIFIER_TYPE:
			free( oneNode -> var.val.string_value );
		break;
	}	
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

