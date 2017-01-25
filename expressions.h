/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* expressions.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

typedef enum
{
	VOID_EXPRESSION,
	INTEGER_EXPRESSION, 
	FLOAT_EXPRESSION, 
	STRING_EXPRESSION,
	GUID_EXPRESSION, 
	BOOLEAN_EXPRESSION, 
	ENTITY_EXPRESSION,
	PROPERTY_EXPRESSION	 
} expressionType;


typedef struct
{
	expressionType type;
	value value;	
}expression_Value;


expression_Value expression( syntaxTreeNode * oneNode );
