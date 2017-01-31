/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* syntaxtree.h				*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/


/* -----------------------------------------------------*/
/* type de noeud dans l'arbre  syntaxique		*/
/* -----------------------------------------------------*/
typedef enum
{
	CONSTANT_SYNTAXTREE_NODETYPE, 
	IDENTIFIER_SYNTAXTREE_NODETYPE, 
	OPERATOR_SYNTAXTREE_NODETYPE ,
	ENTITY_SYNTAXTREE_NODETYPE ,
	PROPERTY_SYNTAXTREE_NODETYPE

} syntaxTreeNodeType;


/* -----------------------------------------------------*/
/* noeud de l'arbre syntaxique				*/
/* -----------------------------------------------------*/
typedef struct syntaxTreeNode_
{
	syntaxTreeNodeType type;
	struct
	{
		constant cste;
		variable * var;
		operator oper;
		entity * ent;
		property * prop;
		struct syntaxTreeNode_ * guidNode;
		struct syntaxTreeNode_ * nameNode;
		BOOL unique_name;
	};	
} syntaxTreeNode;



void  dumpSyntaxTreeNode(syntaxTreeNode * oneNode );
syntaxTreeNode * oper( int oneOper, int OperandsCount, ...);
syntaxTreeNode * Const( ConstantType oneType, void * oneconstantPtr );
syntaxTreeNode * Var( VarType oneType, variable * oneVarPtr );

syntaxTreeNode * Property( syntaxTreeNode * oneGuidNode ,  syntaxTreeNode * oneNameNode , BOOL oneUniqueName );
syntaxTreeNode * Entity( syntaxTreeNode * oneGuidNode ,  syntaxTreeNode * oneNameNode , BOOL oneUniqueName );

void Free_SyntaxTreeNode( syntaxTreeNode * oneNode );

