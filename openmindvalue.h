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
typedef	union
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
/* valeur et type d'un nombre		*/
/* -------------------------------------*/
typedef	struct 
	{
        	float float_value;			/* float value					*/
	        int   integer_value;			/* integer value				*/
		numberType number_type;			/* type de nombre, entier ou flottant		*/
	} numberValue;					/* numeric value				*/


