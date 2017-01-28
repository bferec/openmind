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
	CHAR_IDENTIFIER_TYPE, 
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
	struct variable_node * previous;
	struct variable_node * next;	
}variable_node;


variable * createVar( char * oneIdent );
variable * find_variable( char * oneIdent );
void ClearVarList( );

BOOL  check_ident( char * oneident );
void DumpVarList();

