/* -------------------------------------*/
/* -------------------------------------*/
/* openmindlib.h			*/
/* -------------------------------------*/
/* -------------------------------------*/

#define GUID_LENGTH 33
#define MAXLENGTH_STRING 255
#define BOOL int


/* -------------------------------------*/
/* type de variable possible dans fdl	*/
/* -------------------------------------*/
typedef enum var_type { UNKNOWN , INTEGER, FLOAT, STRING, BOOLEAN , GUID, ENTITY , PROPERTY } VarType;


/* -------------------------------------*/
/* test de validite d'un identificateur */
/* -------------------------------------*/


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


/* -----------------------------------------------------*/
/* une variable du programme				*/
/* -----------------------------------------------------*/
typedef struct variable
{
	VarType type;
	char * ident;
	union
	{
		int integer_value;
		float float_value;
		char * string_value;
		int boolean_value;
		entity  * entity_value;
		property * property_value;
	}val;
}variable;

/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
typedef struct variable_node
{
	variable * v;
	struct variable_node * left;
	struct variable_node * right;	
}variable_node;




void NewGuid( char * result );
BOOL  check_ident( char * oneident );
variable * find_variable( char * oneIdent );
char * strlwr( char * );
char * strupr( char * );



