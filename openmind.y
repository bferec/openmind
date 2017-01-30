/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmind.y				*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

/* -------------------------------------*/
/* prologue				*/
/* -------------------------------------*/
%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "openmindlib.h"
#include "entity.h"
#include "openmindvalue.h"
#include "openmindvarlist.h"

#include "openmindconstant.h"
#include "operator.h"
#include "syntaxtree.h"
#include "expressions.h"

#define YYDEBUG 0  /* For debugging */
#define DEBUG 0 
#ifdef DEBUG
	#define TRACE printf("reduit en ligne %d\n", __LINE__);
#else
	#define TRACE
#endif


extern int yylex( void );
extern int yyparse();

extern int main( int argc, char ** argv );

extern char *  msgerror;

extern FILE * yyin;
extern char * yytext;
extern int yychar;


%}
/* -------------------- */
/* bison declarations	*/
/* -------------------- */
%union 
{
	number number_value;				/* float or integer				*/
	enum { False, True } boolean_value;		/* boolean value				*/
	char guid_value[ GUID_LENGTH ];			/* guid value identifier of entity or property	*/
	char char_value;				/* caracter value				*/
	char string_value[ MAXLENGTH_STRING + 1 ] ;	/* string constant 				*/
	variable * var;					/* variable					*/
	obj_defs obj_base;
	entity * entity;				/* entity					*/
	property * property;				/* property					*/
	syntaxTreeNode * node;
} 

%token <number_value> T_INT
%token <number_value> T_FLOAT

%token T_PLUS_SIGN T_MINUS_SIGN
%left T_PLUS_SIGN T_MINUS_SIGN


%token T_ASTERISK 
%token T_SLASH 
%left T_ASTERISK T_SLASH

%token T_LEFT_BRACE T_RIGHT_BRACE
%token T_LEFT_BRACKET T_RIGHT_BRACKET
%token T_LEFT_SQUARE_BRACKET T_RIGHT_SQUARE_BRACKET

%token T_ASSIGN
%right T_ASSIGN

%token T_AMPERSAND
%token T_VERTICAL_BAR
%token T_DOT
%token T_COMMA
%token T_COLON
%token T_SEMICOLON

%token T_OR
%left T_OR

%token T_AND
%left T_AND

%token T_XOR
%left T_XOR

%token T_NOT 
%right T_NOT

%token T_LESS_THAN
%token T_MORE_THAN
%token T_LESS_OR_EQUAL_THAN
%token T_MORE_OR_EQUAL_THAN
%nonassoc T_LESS_THAN T_LESS_OR_EQUAL_THAN T_MORE_THAN T_MORE_OR_EQUAL_THAN

%token T_DIFFERENT
%token T_EQUAL
%nonassoc T_DIFFERENT T_EQUAL 

%token<boolean_value> T_TRUE
%token<boolean_value>  T_FALSE
%token<guid_value>  T_GUID
%token<string_value> T_CSTE_STRING
%token<char_value> T_CSTE_CHAR

%token<var> T_IDENTIFIER

/* -------------------------------------*/
/* keywords				*/
/* -------------------------------------*/
%token T_CREATE
%token<entity> T_ENTITY
%token<property> T_PROPERTY
%token<guid_value> T_IDENTITY
%token<guid_value> T_AUTO
%token<string_value> T_NAME
%token T_UNIQUE
%token T_ECHO
%token T_QUIT

%token T_UNKNOWN

%type<node> stmtList stmt create_stmt echo_stmt assign_stmt create_entity_stmt create_property_stmt
%type<node> expr char_expr string_expr numeric_expr boolean_expr guid_expr lvalue obj_defs property_defs entity_defs

%type<node>  name_defs
%type<node>  guid_defs

/* -------------------- */
/* -------------------- */
/* Axiome		*/
/* -------------------- */
/* -------------------- */
%start stmtList

/* -------------------- */
/* Grammar rules	*/
/* -------------------- */
%%

/* -------------------- */
/* liste instructions	*/
/* -------------------- */
stmtList:
	stmt T_SEMICOLON 	
					{ expression( $1 ) ; Free_SyntaxTreeNode( $1 ); }
	| stmtList stmt T_SEMICOLON	{ expression( $2 ) ; Free_SyntaxTreeNode( $1 ); }
;
/* -------------------- */
/* instruction		*/
/* -------------------- */
stmt:
	expr 			{ $$ = $1; }
	| create_stmt		{ $$ = $1; }
	| echo_stmt		{ $$ = $1; }
	| assign_stmt		{ $$ = $1; }
	| T_QUIT		{ exit (0);}
;
/* -------------------- */
/* affichage		*/
/* -------------------- */
echo_stmt:
	T_ECHO expr		{$$  = oper( T_ECHO , 1 , $2 ); }
;
/* -------------------- */
/* affectation		*/
/* -------------------- */
assign_stmt:
	  lvalue T_ASSIGN expr	{$$  = oper( T_ASSIGN , 2 , $1, $3 );}
;
/* -------------------- */
/* ce qui peut être à	*/
/* gauche de =		*/
/* -------------------- */
lvalue:
	T_IDENTIFIER			{ $$ = Var( $1 -> type , $1 ); }
	| T_IDENTIFIER T_LEFT_SQUARE_BRACKET expr T_RIGHT_SQUARE_BRACKET	{ /* variable tableau */ }
	| error T_SEMICOLON 		{YYABORT;}
;
/* -------------------- */
/* Create		*/
/* -------------------- */
create_stmt:
	create_entity_stmt		{}
	| create_property_stmt		{}
;
/* -------------------- */
/* Create ENTITY	*/
/* -------------------- */
create_entity_stmt:
	T_CREATE entity_defs	{$$  = oper( T_CREATE , 1 , $2 ); }
;
/* -------------------- */
/* corps ENTITY		*/
/* -------------------- */
entity_defs:
	T_ENTITY T_LEFT_BRACE obj_defs	T_RIGHT_BRACE	{$$  = oper( T_ENTITY , 1 , & $3 );   }
;
/* -------------------- */
/* Create Property	*/
/* -------------------- */
create_property_stmt:
	T_CREATE property_defs	{$$  = oper( T_CREATE , 1 , $2 ); }
;
/* -------------------- */
/* corps property	*/
/* -------------------- */
property_defs:
	T_PROPERTY T_LEFT_BRACE obj_defs T_RIGHT_BRACE 	{ $$  = oper( T_PROPERTY , 1 , & $3 ); }
;
/* -------------------- */
/* corps property	*/
/* -------------------- */
obj_defs:
	 guid_defs T_SEMICOLON name_defs T_SEMICOLON			{ $$ = ObjDefs( $1 , $3 , 0 ); }
	| guid_defs T_SEMICOLON name_defs T_UNIQUE T_SEMICOLON		{ $$ = ObjDefs( $1 , $3 , 1 ); } 
;
/* -------------------- */
/* identity		*/
/* -------------------- */
guid_defs:
	T_IDENTITY T_LEFT_BRACE guid_expr T_RIGHT_BRACE	{ $$ = $3 ; } 
;
/* -------------------- */
/* name			*/
/* -------------------- */
name_defs:
	T_NAME T_LEFT_BRACE string_expr T_RIGHT_BRACE 	{ $$ = $3 ; } 
;
/* -------------------- */
/* Expression		*/
/* -------------------- */
expr:
	numeric_expr
	| string_expr
	| char_expr				
	| boolean_expr
	| guid_expr
	| T_LEFT_BRACKET expr T_RIGHT_BRACKET	{ $$ = $2;}
	| T_IDENTIFIER	{ $$ = Var( $1 -> type , $1 ); }
;
/* -------------------- */
/* Expression	Guid	*/
/* -------------------- */
guid_expr:
	T_AUTO		{ $$ = oper( T_AUTO , 0 );  }
	| T_GUID	{ $$ = Const( GUID_CONSTANT_TYPE , $1 );}
;
/* -------------------- */
/* Expression numerique	*/
/* -------------------- */
numeric_expr:
	T_INT 				{ $$ = Const( INT_CONSTANT_TYPE   , (void *) & $1.integer_value ); }
	| T_FLOAT			{ $$ = Const( FLOAT_CONSTANT_TYPE , (void *) & $1.float_value); }
	| T_MINUS_SIGN expr 		{ $$ = oper( T_MINUS_SIGN , 1 , $2 ) ; }
	| T_PLUS_SIGN expr 		{ $$ = oper( T_PLUS_SIGN , 1 , $2 ) ; }
	| expr T_PLUS_SIGN expr		{ $$ = oper( T_PLUS_SIGN  , 2 , $1 , $3 ) ; }	
	| expr T_MINUS_SIGN expr 	{ $$ = oper( T_MINUS_SIGN , 2 , $1 , $3 ) ; }	
	| expr T_ASTERISK expr 		{ $$ = oper( T_ASTERISK   , 2 , $1 , $3 ) ; }		
	| expr T_SLASH expr		{ $$ = oper( T_SLASH 	  , 2 , $1 , $3 ) ; }		
;
/* -------------------- */
/* Expression booleeene	*/
/* -------------------- */
boolean_expr:	
	T_TRUE					{ $$ = Const( BOOLEEAN_CONSTANT_TYPE ,  & $1); }
	|T_FALSE				{ $$ = Const( BOOLEEAN_CONSTANT_TYPE ,  & $1); }

	| T_NOT expr				{ $$ = oper( T_NOT , 1, $2 ); }
	| expr T_OR expr			{ $$ = oper( T_OR  , 2, $1 , $3 ); }
	| expr T_AND expr			{ $$ = oper( T_AND , 2, $1 , $3 ); }
	| expr T_XOR expr			{ $$ = oper( T_XOR , 2, $1 , $3 ); }

	| expr T_DIFFERENT  expr		{ $$ = oper( T_DIFFERENT , 2, $1 , $3 ); }
	| expr T_EQUAL      expr		{ $$ = oper( T_EQUAL 	 , 2, $1 , $3 ); }	
	| expr T_LESS_THAN  expr		{ $$ = oper( T_LESS_THAN , 2, $1 , $3 ); }	
	| expr T_MORE_THAN  expr		{ $$ = oper( T_MORE_THAN , 2, $1 , $3 ); }	
	| expr T_LESS_OR_EQUAL_THAN  expr	{ $$ = oper( T_LESS_OR_EQUAL_THAN , 2, $1 , $3 ); }	
	| expr T_MORE_OR_EQUAL_THAN  expr	{ $$ = oper( T_MORE_OR_EQUAL_THAN , 2, $1 , $3 ); }		
;
/* -------------------- */
/* Expression caractere	*/
/* -------------------- */
char_expr:
	T_CSTE_CHAR				{ $$ = Const( CHAR_CONSTANT_TYPE , & $1 ); }
;
/* -------------------- */
/* Expression chaine	*/
/* -------------------- */
string_expr:
	T_CSTE_STRING				{ $$ = Const( STRING_CONSTANT_TYPE , $1 ); }
;

%%
/* -------------------- */
/* epilogue		*/
/* -------------------- */


