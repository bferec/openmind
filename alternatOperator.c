/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* alternatOperator.c			*/
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

extern void DoEcho( syntaxTreeNode * oneNode );

/* -------------------------------------*/
/* ? :  interpretation			*/
/* -------------------------------------*/
expression_Value expression_Operator_T_QUESTION( operator * oneOperatorNode  ) 
{
expression_Value conditionalResult;
expression_Value result;

	conditionalResult = expression( oneOperatorNode -> operands[0] );

	if( conditionalResult.value.boolean_value == TRUE )
	{
		result = expression( oneOperatorNode -> operands[1] );
	}
	else
	{
		result = expression( oneOperatorNode -> operands[2] );
	}

	return result;
}

/* -------------------------------------*/
/* IF interpretation			*/
/* -------------------------------------*/
void  expression_Operator_T_IF(operator * oneOperatorNode)
{
expression_Value conditionalResult;
expression_Value statementResult;
syntaxTreeNode * conditionNode;
syntaxTreeNode * statementTrueNode;
syntaxTreeNode * statementFalseNode;

	conditionNode = oneOperatorNode -> operands[0];
	statementTrueNode = oneOperatorNode -> operands[1];
	if( oneOperatorNode -> OperandsCount > 2 )
	{
		statementFalseNode = oneOperatorNode -> operands[2];
	}
	
	conditionalResult = expression( conditionNode );

	if( conditionalResult.value.boolean_value == TRUE )
	{
		if( statementTrueNode -> type == LIST_SYNTAXTREE_NODETYPE )
		{
			for( int x = 0 ;x < statementTrueNode -> nodeListCount ; x ++ )
			{
				statementResult = expression( statementTrueNode -> nodeList[x] );
			}
		}
		else
		{
			statementResult = expression( statementTrueNode  );
		}

	}
	else
	{
		if( statementFalseNode -> type == LIST_SYNTAXTREE_NODETYPE )
		{
			for( int x = 0 ;x < statementFalseNode -> nodeListCount ; x ++ )
			{
				statementResult = expression( statementFalseNode -> nodeList[x] );
			}
		}
		else
		{
			statementResult = expression( statementFalseNode  );
		}		
	}
}


