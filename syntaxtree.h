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
	OBJDEFS_SYNTAXTREE_NODETYPE,

} syntaxTreeNodeType;

/* -----------------------------------------------------*/
/* noeud de l'arbre syntaxique				*/
/* -----------------------------------------------------*/
typedef struct syntaxTreeNode_
{
	syntaxTreeNodeType type;
	union
	{
		constant cste;
		variable * var;
		entity * ent;
		property * prop;
		obj_defs objdefs;
		operator oper;
	};	
} syntaxTreeNode;

void  dumpSyntaxTreeNode(syntaxTreeNode * oneNode );
syntaxTreeNode * oper( int oneOper, int OperandsCount, ...);
syntaxTreeNode * Const( ConstantType oneType, void * oneconstantPtr );
syntaxTreeNode * Var( VarType oneType, variable * oneVarPtr );

syntaxTreeNode * ObjDefs( char * oneGuid , char * oneName , BOOL oneUniqueFlag );

void Free_SyntaxTreeNode( syntaxTreeNode * oneNode );

