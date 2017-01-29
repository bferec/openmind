/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindvalue.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

/* -------------------------------------*/
/* type valeur pour constante ou var	*/
/* -------------------------------------*/
typedef	struct
{
	int integer_value;
	float float_value;
	char * string_value;
	char char_value;
	char * guid_value;
	int boolean_value;
	entity  * entity_value;
	property * property_value;
}value;

/* -------------------------------------*/
/* -------------------------------------*/
typedef union 
{
	int integer_value;
	float float_value;
}number;


