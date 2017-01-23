/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindlib.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/



#define KEYWORDS_COUNT 12		/* nombre de mots cles du langage			*/


/* -------------------------------------*/
/* type de nombres 			*/
/* -------------------------------------*/
typedef enum number_type { INTEGER_NUMBER_TYPE, FLOAT_NUMBER_TYPE } numberType;

typedef enum constant_type 
{
	INT_CONSTANT_TYPE, 
	FLOAT_CONSTANT_TYPE, 
	BOOLEEAN_CONSTANT_TYPE,
	GUID_CONSTANT_TYPE,
	STRING_CONSTANT_TYPE
} ConstantType;

/* -----------------------------------------------------*/
/* une constante du programme				*/
/* -----------------------------------------------------*/
typedef struct constant_
{
	ConstantType type;
	value val;
}constant;

/* -----------------------------------------------------*/
/* type de noeud dans l'arbre  syntaxique		*/
/* -----------------------------------------------------*/
typedef enum
{
	CONSTANT_SYNTAXTREE_NODETYPE, 
	IDENTIFIER_SYNTAXTREE_NODETYPE, 
	OPERATOR_SYNTAXTREE_NODETYPE 
} syntaxTreeNodeType;

/* -----------------------------------------------------*/
/* un operateur						*/
/* -----------------------------------------------------*/
typedef struct 
{
	int type;
	int OperandsCount;
	struct syntaxTreeNode_ * * operands;

} operator;

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
		operator oper;
	};	
} syntaxTreeNode;

/* -------------------------------------*/
/* valeur et type d'un nombre		*/
/* -------------------------------------*/
typedef	struct 
	{
        	float float_value;			/* float value					*/
	        int   integer_value;			/* integer value				*/
		numberType number_type;			/* type de nombre, entier ou flottant		*/
	} numberValue;					/* numeric value				*/


void yyerror(const char* s);

void NewGuid( char * result );
BOOL  check_ident( char * oneident );



char * strlwr( char * );
char * strupr( char * );
double getValueNumber( numberValue v );
void yyerror(const char* msg);

value  expression( syntaxTreeNode * oneNode );

void  dumpSyntaxTreeNode(syntaxTreeNode * oneNode );
syntaxTreeNode * oper( int oneOper, int OperandsCount, ...);
syntaxTreeNode * Const( ConstantType oneType, void * oneconstantPtr );
syntaxTreeNode * Var( VarType oneType, variable * oneVarPtr );
void Free_SyntaxTreeNode( syntaxTreeNode * oneNode );
void DumpVarList();

