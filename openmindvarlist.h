/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindvarlist.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

/* -------------------------------------*/
/* possible type of variable  fdl	*/
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
	PROPERTY_IDENTIFIER_TYPE ,
	ARRAY_IDENTIFIER_TYPE		/* array var.	*/
} VarType;



/* -----------------------------------------------------*/
/* fdl variable.					*/
/* -----------------------------------------------------*/
typedef struct variable
{
	VarType type;
	char * ident;
	value val;
	struct variable_node  * * elements;	/* elements of n dimension array	*/
	int nbDimensions;			/* array dimensions count		*/
}variable;


/* -----------------------------------------------------*/
/* variable list item					*/
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


