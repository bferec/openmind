/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* entity.h				*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

/* -----------------------------------------------------*/
/* entity state						*/
/* -----------------------------------------------------*/
typedef enum
{
	UNKNOWN, OK, ERROR
} entityState; 


typedef enum
{
	BOOLEAN_PROPERTY_TYPE , CHAR_PROPERTY_TYPE , INTEGER_PROPERTY_TYPE , FLOAT_PROPERTY_TYPE, DATETIME_PROPERTY_TYPE , STRING_PROPERTY_TYPE
} propertyType; 

/* -----------------------------------------------------*/
/* possible value of a property				*/
/* -----------------------------------------------------*/
typedef	struct
{
	int boolean_value;
	char char_value;
	int integer_value;
	float float_value;
	struct tm * datetime_value;
	char * string_value;

}property_Value;


/* -----------------------------------------------------*/
/* definition propriete					*/
/* -----------------------------------------------------*/
typedef struct property_
{
	char guid[GUID_LENGTH + 1];
	char name[ MAXLENGTH_STRING  + 1 ];
	BOOL unique_name;
	propertyType type;
	property_Value val;
}property;

/* -----------------------------------------------------*/
/* -----------------------------------------------------*/
typedef struct obj_defs_
{
	char guid[GUID_LENGTH + 1];
	char name[ MAXLENGTH_STRING  + 1 ];
	BOOL unique_name;	
}obj_defs;

/* -----------------------------------------------------*/
/* noeud propriete					*/
/* -----------------------------------------------------*/
typedef struct property_node_
{
	property * p;
	struct property_node_ * previous;
	struct property_node_ * next;	
}property_node;

/* -----------------------------------------------------*/
/* definition entite					*/
/* -----------------------------------------------------*/
typedef struct entity_
{
	char guid[GUID_LENGTH +1];
	char name[ MAXLENGTH_STRING  + 1 ];
	BOOL unique_name;
	entityState state;
	struct entity_node_ * content;
	struct property_node_ * properties;
	
}entity;

/* -----------------------------------------------------*/
/* noeud  entite					*/
/* -----------------------------------------------------*/
typedef struct entity_node_
{
	entity * e;
	struct entity_node_ * previous;
	struct entity_node_ * next;	
}entity_node;







