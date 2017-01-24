/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* expressions.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

typedef enum
{
	INTEGER_EXPRESSION, 
	FLOAT_EXPRESSION, 
	STRING_EXPRESSION,
	GUID_EXPRESSION, 
	BOOLEAN_EXPRESSION, 
	ENTITY_EXPRESSION,
	PROPERTY_EXPRESSION	 
} expressionType;


typedef union
{
	value value;	
	expressionType type;
}expression_Value;


expression_Value expression( syntaxTreeNode * oneNode );
