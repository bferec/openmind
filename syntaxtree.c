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
#include <time.h>

#include "openmindlib.h"
#include "entity.h"
#include "openmindvalue.h"
#include "openmindvarlist.h"
#include "openmindEntityList.h"

#include "openmindconstant.h"
#include "operator.h"

#include "syntaxtree.h"
#include "debugTools.h"

#include "openmind.tab.h"

char buffer[MAXLENGTH_STRING + 1 ];


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
/* expression list create first element			*/
/* -----------------------------------------------------*/
syntaxTreeNode * NodeList( syntaxTreeNode * oneFirstNode )
{
syntaxTreeNode * resultNode;

	resultNode = syntaxTreeNodeAlloc();
	if( resultNode == (syntaxTreeNode *) NULL )
		yyerror("SyntaxtreeNode allocation : Out of Memory" );

	resultNode -> nodeList = (syntaxTreeNode * *) malloc( sizeof( syntaxTreeNode * ) );
	if( resultNode == (syntaxTreeNode *) NULL )
		yyerror("SyntaxtreeNode nodeList allocation : Out of Memory" );

	resultNode ->  type = LIST_SYNTAXTREE_NODETYPE;

	resultNode -> nodeList[ 0 ] = oneFirstNode;
	resultNode -> nodeListCount = 1;
	// fprintf(stderr , "Nodelist() :  %d\n" , resultNode -> nodeListCount );
	return resultNode;
}

/* -----------------------------------------------------*/
/* expression list add element				*/
/* -----------------------------------------------------*/
syntaxTreeNode * NodeAdd( syntaxTreeNode * oneListNode  ,syntaxTreeNode * oneNewNode )
{
	oneListNode -> nodeList = (syntaxTreeNode * *) realloc( oneListNode -> nodeList , (oneListNode -> nodeListCount + 1) * sizeof( syntaxTreeNode * ) );
	if( oneListNode -> nodeList == (syntaxTreeNode * *) NULL )
		yyerror("SyntaxtreeNode nodeList reallocation : Out of Memory" );

	oneListNode -> nodeList[ oneListNode -> nodeListCount ] = oneNewNode;
	oneListNode -> nodeListCount ++;
	// fprintf(stderr , "NodeAdd() :  %d\n" , oneListNode -> nodeListCount );
	return oneListNode;
}

/* -----------------------------------------------------*/
/* property creation Node				*/
/* -----------------------------------------------------*/
syntaxTreeNode * Property( syntaxTreeNode * oneGuidNode ,  syntaxTreeNode * oneNameNode , BOOL oneUniqueName )
{
syntaxTreeNode * resultNode;

	resultNode = syntaxTreeNodeAlloc();
	if( resultNode == (syntaxTreeNode *) NULL )
		yyerror("SyntaxtreeNode allocation : Out of Memory" );
	resultNode -> type = PROPERTY_SYNTAXTREE_NODETYPE;
	resultNode -> guidNode = oneGuidNode;
	resultNode -> nameNode = oneNameNode;
	resultNode -> unique_name = oneUniqueName;

	return resultNode;
}

/* -----------------------------------------------------*/
/* entity creation Node					*/
/* -----------------------------------------------------*/
syntaxTreeNode * Entity( syntaxTreeNode * oneGuidNode ,  syntaxTreeNode * oneNameNode , BOOL oneUniqueName )
{
syntaxTreeNode * resultNode;

	resultNode = syntaxTreeNodeAlloc();
	resultNode -> type = ENTITY_SYNTAXTREE_NODETYPE;
	resultNode -> guidNode = oneGuidNode;
	resultNode -> nameNode = oneNameNode;
	resultNode -> unique_name = oneUniqueName;
	return resultNode;

}

/* -----------------------------------------------------*/
/* creation de noeud constante				*/
/* -----------------------------------------------------*/
syntaxTreeNode * Const( ConstantType oneType, void * oneconstantPtr )
{
syntaxTreeNode * resultNode;

	//fprintf( stderr , "Const()\n" );

	resultNode = syntaxTreeNodeAlloc();
	resultNode -> type = CONSTANT_SYNTAXTREE_NODETYPE;
	resultNode -> cste.type = oneType;

	switch( oneType )
	{
		case 	INT_CONSTANT_TYPE:
			resultNode -> cste.val.integer_value = * (int *) oneconstantPtr;
			 // fprintf( stderr , "Const()  Integer  :[%d]\n" , resultNode -> cste.val.integer_value ); 
		break;

		case 	FLOAT_CONSTANT_TYPE:
			resultNode -> cste.val.float_value = * (float *) oneconstantPtr;
			 // fprintf( stderr , "Const()  Float  :[%f]\n" , resultNode -> cste.val.float_value ); 
		break;

		case	BOOLEEAN_CONSTANT_TYPE:
			resultNode -> cste.val.boolean_value = * (int *) oneconstantPtr;
			//fprintf( stderr , "Const()  Boolean : [%s]\n" , resultNode -> cste.val.boolean_value ? "True" : "False"  ); 
		break;

		case 	GUID_CONSTANT_TYPE:
			strcpy( resultNode -> cste.val.guid_value , (char *) oneconstantPtr );
			// fprintf( stderr , "Const()  guid : [%s]\n" , resultNode -> cste.val.guid_value); 
		break;

		case	CHAR_CONSTANT_TYPE:
			resultNode -> cste.val.char_value =  * ((char *) oneconstantPtr);
		break;

		case	STRING_CONSTANT_TYPE:
			resultNode -> cste.val.string_value =  (char *) malloc( MAXLENGTH_STRING  + 1);
			if( resultNode -> cste.val.string_value == NULL )
				yyerror("string value of constant allocation : Out of Memory" );
			strcpy( resultNode -> cste.val.string_value , (char *) oneconstantPtr );
			// fprintf( stderr , "Const() type string : [%s]\n" , resultNode -> cste.val.string_value); 
		break;

		case	ENTITY_CONSTANT_TYPE:
			resultNode -> cste.val.entity_value = allocMemEntity();
			if( resultNode -> cste.val.entity_value == NULL )
				yyerror("Entity value of constant allocation : Out of Memory" );
			syntaxTreeNode * guidNode;
			guidNode = (syntaxTreeNode *) oneconstantPtr;		
			strcpy( resultNode -> cste.val.entity_value -> guid , guidNode -> cste.val.guid_value);
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

	// fprintf( stderr , "var() ajout de d'une variable \n"); 
	resultNode = syntaxTreeNodeAlloc();

	resultNode -> type = IDENTIFIER_SYNTAXTREE_NODETYPE;

	if( oneVarPtr == NULL )
	{
		yyerror( "variable not found tu build Syntax Tree\n" );
	}
	resultNode-> var = oneVarPtr ;
	resultNode-> var -> type = oneType;

	return resultNode;
}

/* -----------------------------------------------------*/
/* creation de noeud operator				*/
/* -----------------------------------------------------*/
syntaxTreeNode * oper( int oneOperType, int OperandsCount, ...)
{
syntaxTreeNode * resultNode;
syntaxTreeNode * operandeNode;

	//fprintf( stderr , "oper() type :[%s] \n" , getOperatorLibelle( oneOperType ) );  
	resultNode = syntaxTreeNodeAlloc();
	va_list listOperands;
	
	resultNode = syntaxTreeNodeAlloc();
	resultNode -> type = OPERATOR_SYNTAXTREE_NODETYPE;
	resultNode -> oper.type = oneOperType;
	resultNode -> oper.OperandsCount = OperandsCount;

	/* operand_number; */
	if( OperandsCount > 0 )
	{
		// fprintf( stderr , "%d operands memory allocation\n" , OperandsCount ); 
		resultNode -> oper.operands = (struct syntaxTreeNode_ * *) calloc( OperandsCount , sizeof( syntaxTreeNode *) );
		if( resultNode -> oper.operands == (struct syntaxTreeNode_ * *) NULL )
			yyerror("operands of operator vector allocation : Out of Memory" );

		va_start( listOperands, OperandsCount );

		for( int i = 0 ; i < OperandsCount  ; i ++ )
		{
			resultNode -> oper.operands[i] = syntaxTreeNodeAlloc();
			if( resultNode -> oper.operands[i]  == (syntaxTreeNode *) NULL )
				yyerror("operands n of operator vector allocation : Out of Memory");

			operandeNode = va_arg( listOperands , syntaxTreeNode * );
			// fprintf( stderr, "operande No %d :  %s\n" , i , getOperandeTypeLibelle( operandeNode )  );  

			resultNode -> oper.operands[i] =  operandeNode;
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
			//free( oneNode -> cste.val.guid_value );
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
	if( oneNode != NULL )
	{
		free( oneNode );
	}
}
/* -----------------------------------------------------*/
/* suppression d'un noeud operateur			*/ 
/* -----------------------------------------------------*/
void Free_OperSyntaxTreeNode( syntaxTreeNode * oneNode  )
{
	if( oneNode != NULL )
	{
		for( int i = 0 ; i < oneNode -> oper.OperandsCount ; i ++ )
		{	if( oneNode -> oper.operands[i] != NULL )
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
		}

		if( oneNode -> oper.operands != NULL )
			free( oneNode -> oper.operands );

		free( oneNode );
	}
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

