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

/* -------------------------------------*/
/* -- interpretation			*/
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


