/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindvarlist.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

#define GUID_LENGTH 33			/* longueur xhaine guid hors zero final			*/
#define BOOL int			/* type booleen						*/
#define MAXLENGTH_STRING 255		/* longueur maxi identificateurs et constantes texte	*/


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
/* -----------------------------------------------------*/
typedef struct variable_node
{
	variable * v;
	struct variable_node * left;
	struct variable_node * right;	
}variable_node;


variable * find_variable( char * oneIdent );
variable * createVar( char * oneIdent );
