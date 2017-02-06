/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* iterOperator.c			*/
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

/* -----------------------------*/
/* -----------------------------*/
BOOL for_continue_loop(syntaxTreeNode * oneNode )
{
BOOL result = TRUE;	/* if true continue loop	*/
expression_Value booleanResult;

	if( oneNode -> type == LIST_SYNTAXTREE_NODETYPE )
	{
		for( int x = 0 ; x < oneNode -> nodeListCount ; x ++ )
		{
			booleanResult = expression( oneNode -> nodeList[x]);
			if( booleanResult.value.boolean_value == FALSE )
			{
				result = FALSE;
				break;
			}
		}
	}
	else
	{
		booleanResult = expression( oneNode );
		result = booleanResult.value.boolean_value;
	}

	return result;
}

/* -------------------------------------*/
/* initial assignment  FOR( ; ;  )	*/
/* -------------------------------------*/
expression_Value for_initial_assigment( syntaxTreeNode * oneNode )
{
expression_Value result;

	if( oneNode -> type == LIST_SYNTAXTREE_NODETYPE )
	{
		for( int x = 0 ;x < oneNode -> nodeListCount ; x ++ )
		{
			result = expression( oneNode -> nodeList[x] );
		}
	}
	else
	{
		result = expression( oneNode  );
	}
	
return result;
}

/* -------------------------------------*/
/* compound instructions in FOR( ; ; )	*/
/* -------------------------------------*/
expression_Value for_Compound_Statement( syntaxTreeNode * oneNode )
{
expression_Value result;
	if( oneNode -> type == LIST_SYNTAXTREE_NODETYPE )
	{
		for( int x = 0 ;x < oneNode -> nodeListCount ; x ++ )
		{
			result = expression( oneNode -> nodeList[x] );
		}
	}
	else
	{
		result = expression( oneNode  );
	}
	return result;
}

/* -------------------------------------*/
/* assignment every loop of FOR( ; ;  )	*/
/* -------------------------------------*/
expression_Value for_assigment( syntaxTreeNode * oneNode )
{
expression_Value result;
	if( oneNode -> type == LIST_SYNTAXTREE_NODETYPE )
	{
		for( int x = 0 ;x < oneNode -> nodeListCount ; x ++ )
		{
			result = expression( oneNode -> nodeList[x] );
		}
	}
	else
	{
		result = expression( oneNode  );
	}
	return result;
}

/* -----------------------------*/
/* for( ; ; ) interpretation	*/
/* -----------------------------*/
// T_FOR T_LEFT_BRACKET assign_list T_SEMICOLON boolean_expr_list T_SEMICOLON  assign_list_stmt T_RIGHT_BRACKET compound_stmt	
void expression_Operator_T_FOR(operator * oneOperatorNode )
{

expression_Value result ;
syntaxTreeNode * assign_list_Node;
syntaxTreeNode * boolean_expr_list_Node;
syntaxTreeNode * assign_list_stmt_Node;
syntaxTreeNode * compound_stmt_Node;

BOOL continueLoop = TRUE;

	assign_list_Node = oneOperatorNode -> operands[0];
	boolean_expr_list_Node = oneOperatorNode -> operands[1];
	assign_list_stmt_Node = oneOperatorNode -> operands[2];
	compound_stmt_Node = oneOperatorNode -> operands[3];

	/* execute initial assigment	*/
	result = for_initial_assigment( assign_list_Node );
	/* test conditionnal loop first time	*/
	//continueLoop = for_continue_loop(boolean_expr_list_Node );

	while( continueLoop )
	{
		/* execute compound instructions	*/
		result = for_Compound_Statement(compound_stmt_Node );
		/* execute assignment instructions	*/
		result = for_assigment( assign_list_stmt_Node );
		/* test conditionnal loop continue	*/
		continueLoop = for_continue_loop(boolean_expr_list_Node );
	}

}


/* -----------------------------------
-*/
/* DO WHILE interpretation		*/
/* -------------------------------------*/
void  expression_Operator_T_DO(operator * oneOperatorNode)
{
expression_Value conditionalResult ;
expression_Value statementResult ;
syntaxTreeNode * conditionNode;
syntaxTreeNode * statementNode;

	conditionNode = oneOperatorNode -> operands[1];
	 //fprintf( stderr , "type noeud condition : %d\n\r" , conditionNode -> type );

	statementNode = oneOperatorNode -> operands[0];
	 //fprintf( stderr , "type noeud instructions : %d\n\r" , statementNode -> type );

	do{
		//fprintf(stderr , "iteration %d\n" , iter ++ );
		if( statementNode -> type == LIST_SYNTAXTREE_NODETYPE )
		{
			for( int x = 0 ;x < statementNode -> nodeListCount ; x ++ )
			{
				statementResult = expression( statementNode -> nodeList[x] );
				conditionalResult = expression( conditionNode );
			}
		}
		else
		{
			statementResult = expression( statementNode  );
			conditionalResult = expression( conditionNode );
		}
		//fprintf(stderr , "conditionalResult (fin boucle) %d\n" , conditionalResult.value.boolean_value );
	}while( conditionalResult.value.boolean_value );
}

/* -------------------------------------*/
/* WHILE interpretation			*/
/* -------------------------------------*/
void  expression_Operator_T_WHILE(operator * oneOperatorNode)
{
expression_Value conditionalResult ;
expression_Value statementResult ;
syntaxTreeNode * conditionNode;
syntaxTreeNode * statementNode;

	conditionNode = oneOperatorNode -> operands[0];
	 //fprintf( stderr , "type noeud condition : %d\n\r" , conditionNode -> type );

	statementNode = oneOperatorNode -> operands[1];
	 //fprintf( stderr , "type noeud instructions : %d\n\r" , statementNode -> type );

	conditionalResult = expression( conditionNode );
	//fprintf(stderr , "conditionalResult %d\n" , conditionalResult.value.boolean_value );

	while( conditionalResult.value.boolean_value )
	{
		//fprintf(stderr , "iteration %d\n" , iter ++ );
		if( statementNode -> type == LIST_SYNTAXTREE_NODETYPE )
		{
			for( int x = 0 ;x < statementNode -> nodeListCount ; x ++ )
			{
				statementResult = expression( statementNode -> nodeList[x] );
				conditionalResult = expression( conditionNode );
			}
		}
		else
		{
			statementResult = expression( statementNode  );
			conditionalResult = expression( conditionNode );
		}
		//fprintf(stderr , "conditionalResult (fin boucle) %d\n" , conditionalResult.value.boolean_value );
	}
}


