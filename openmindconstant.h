/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindconstant.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

typedef enum constant_type 
{
	INT_CONSTANT_TYPE, 
	FLOAT_CONSTANT_TYPE, 
	BOOLEEAN_CONSTANT_TYPE,
	GUID_CONSTANT_TYPE,
	CHAR_CONSTANT_TYPE,
	STRING_CONSTANT_TYPE
} ConstantType;

/* -----------------------------------------------------*/
/* une constante du programme				*/
/* -----------------------------------------------------*/
typedef struct constant_
{
	ConstantType type;
	value val;
}constant;

