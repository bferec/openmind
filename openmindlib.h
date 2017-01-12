/* openmindlib.h	*/

#define GUID_LENGTH 33
#define MAXLENGTH_STRING 255
#define BOOL int


void NewGuid( char * result );

enum var_type {INTEGER, FLOAT, STRING, BOOLEAN , GUID, ENTITY , PROPERTY};



/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
typedef struct entity
{
	char guid[GUID_LENGTH];
	char name[ MAXLENGTH_STRING  + 1 ];
	BOOL unique_name;
	
}entity;

/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
typedef struct property
{
	char guid[GUID_LENGTH];
	char name[ MAXLENGTH_STRING  + 1 ];
	BOOL unique_name;
}property;


/* -----------------------------------------------------*/
/* unec variable du programme				*/
/* -----------------------------------------------------*/
typedef struct variable
{
	enum	var_type type;
	union
	{
		int integer_value;
		float float_value;
		char * string_value;
		int boolean_value;
		entity  * entity_value;
		property * property_value;
	}u;
}variable;

