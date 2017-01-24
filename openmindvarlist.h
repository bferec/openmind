/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindvarlist.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/




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
/* -----------------------------------------------------*/
typedef struct variable_node
{
	variable * v;
	struct variable_node * left;
	struct variable_node * right;	
}variable_node;

double getValueNumber( numberValue v );
variable * find_variable( char * oneIdent );
variable * createVar( char * oneIdent );
BOOL  check_ident( char * oneident );
void DumpVarList();

