/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindlib.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/


#define GUID_LENGTH 33			/* longueur xhaine guid hors zero final			*/
#define MAXLENGTH_STRING 255		/* longueur maxi identificateurs et constantes texte	*/
#define BOOL int			/* type booleen						*/
#define KEYWORDS_COUNT 12		/* nombre de mots cles du langage			*/


/* -------------------------------------*/
/* type de variable possible dans fdl	*/
/* -------------------------------------*/
typedef enum  
{
	UNKNOWN_IDENTIFIER_TYPE , 

	/* basic types	*/
	INTEGER_IDENTIFIER_TYPE, 
	FLOAT_IDENTIFIER_TYPE, 
	BOOLEAN_IDENTIFIER_TYPE , 
	GUID_IDENTIFIER_TYPE, 
	STRING_IDENTIFIER_TYPE, 

	ENTITY_IDENTIFIER_TYPE , 
	PROPERTY_IDENTIFIER_TYPE 
} VarType;

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
/* definition entite					*/
/* -----------------------------------------------------*/
typedef struct entity
{
	char guid[GUID_LENGTH];
	char name[ MAXLENGTH_STRING  + 1 ];
	BOOL unique_name;
	
}entity;

/* -----------------------------------------------------*/
/* definition propriete					*/
/* -----------------------------------------------------*/
typedef struct property
{
	char guid[GUID_LENGTH];
	char name[ MAXLENGTH_STRING  + 1 ];
	BOOL unique_name;
}property;

/* -------------------------------------*/
/* type valeur pour constante ou var	*/
/* -------------------------------------*/
typedef	union
{
	int integer_value;
	float float_value;
	char * string_value;
	char * guid_value;
	int boolean_value;
	entity  * entity_value;
	property * property_value;
}value;

/* -----------------------------------------------------*/
/* une variable du programme				*/
/* -----------------------------------------------------*/
typedef struct variable
{
	VarType type;
	char * ident;
	value val;
}variable;

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
		variable var;
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


/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
typedef struct variable_node
{
	variable * v;
	struct variable_node * left;
	struct variable_node * right;	
}variable_node;

void yyerror(const char* s);

void NewGuid( char * result );
BOOL  check_ident( char * oneident );
variable * find_variable( char * oneIdent );
variable * createVar( char * oneIdent );


char * strlwr( char * );
char * strupr( char * );
double getValueNumber( numberValue v );
void yyerror(const char* msg);
void * expression( syntaxTreeNode * oneNode );

void  dumpSyntaxTreeNode(syntaxTreeNode * oneNode );
syntaxTreeNode * oper( int oneOper, int OperandsCount, ...);
syntaxTreeNode * Const( ConstantType oneType, void * oneconstantPtr );
syntaxTreeNode * Var( VarType oneType, variable * oneVarPtr );
void Free_SyntaxTreeNode( syntaxTreeNode * oneNode );

