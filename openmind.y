/* -------------------- */
/* openmind.y		*/
/* -------------------- */

/* -------------------- */
/* prologue		*/
/* -------------------- */
%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "openmindlib.h"



#define YYDEBUG 0  /* For debugging */



extern int yylex(void);
extern int yyparse();
extern int main(int argc, char ** argv);

extern FILE* yyin;
extern char * yytext;

int lineNumber;

void yyerror(const char* s);


%}
/* -------------------- */
/* bison declarations	*/
/* -------------------- */
%union 
{
	struct 
	{
        	float float_value;
	        int   integer_value;
	} number_value;
	enum { False, True } boolean_value;
	char guid_value[ 33 ];
	char string_value[ 256 ] ;
}


%token <number_value.integer_value> T_INT
%token <number_value.float_value> T_FLOAT

%token T_PLUS_SIGN T_MINUS_SIGN
%left T_PLUS T_MINUS

%token T_ASTERISK 
%token T_SLASH 
%left T_ASTERISK T_SLASH

%token T_LEFT_BRACE T_RIGHT_BRACE
%token T_LEFT_BRACKET T_RIGHT_BRACKET

%token T_ASSIGN

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

%token T_NOT 
%right T_NOT

%token T_LESS_THAN
%token T_MORE_THAN
%token T_LESS_OR_EQUAL_THAN
%token T_MORE_OR_EQUAL_THAN

%token T_DIFFERENT
%token T_EQUAL



%token <string_value> T_IDENT

%token<boolean_value> T_TRUE
%token<boolean_value> T_FALSE

%token T_CREATE
%token T_ENTITY
%token T_PROPERTY
%token T_IDENTITY
%token T_AUTO
%token T_NAME
%token T_UNIQUE

%token<guid_value> T_GUID
%token<string_value> T_CSTE_STRING

%token T_UNKNOWN
%token T_QUIT

%type <guid_value> guid_expr
%type <number_value.float_value>  numeric_expr
%type <boolean_value>  boolean_expr
%type <string_value>  string_expr


%start instList
/* -------------------- */
/* Grammar rules	*/
/* -------------------- */
%%

instList:
	%empty
	| T_SEMICOLON
	| stmt T_SEMICOLON 
	| instList stmt T_SEMICOLON
;
stmt:
	expr 
	| create_stmt
	| error T_SEMICOLON	{yyerrok;}
	| T_QUIT	{exit (0);}
;


;
create_stmt:
	create_entity_stmt
	|create_property_stmt
;
create_entity_stmt:
	T_CREATE T_ENTITY T_LEFT_BRACE entity_defs T_RIGHT_BRACE	{}
;

entity_defs:
	obj_defs
;


create_property_stmt:
	T_CREATE T_PROPERTY T_LEFT_BRACE property_defs T_RIGHT_BRACE
;

property_defs:
	obj_defs
;

obj_defs:
	 guid_defs T_SEMICOLON name_defs T_SEMICOLON
	| guid_defs T_SEMICOLON name_defs T_UNIQUE T_SEMICOLON	{fprintf( stderr , "[Unique]\n"  );}
;


guid_defs:
	T_IDENTITY T_LEFT_BRACE guid_expr T_RIGHT_BRACE
;

name_defs:
	T_NAME T_LEFT_BRACE string_expr T_RIGHT_BRACE 
;


expr:
	string_expr					
	| numeric_expr
	| boolean_expr
	| guid_expr
;


guid_expr:
	T_AUTO		{ char guid[33]; NewGuid( guid ); strcpy( $$ , guid ); fprintf( stderr , "Auto: %s\n" , $$ ); }
	| T_GUID	{ strcpy( $$ ,  $1 );fprintf( stderr , "Guid: %s\n" , $$ ); }
;

numeric_expr:	
	T_INT						{ $$ = (float) $1 ; }	
	| T_FLOAT					{}				
	| T_LEFT_BRACKET numeric_expr T_RIGHT_BRACKET	{ $$ = $2; }
	| T_MINUS_SIGN numeric_expr 			{ $$ = -$2; fprintf( stderr , "%f\n" , $$ ); }
	| numeric_expr T_PLUS_SIGN numeric_expr		{ $$ = $1 + $3; fprintf( stderr , "%f\n" , $$ ); }
	| numeric_expr T_MINUS_SIGN numeric_expr	{ $$ = $1 - $3; fprintf( stderr , "%f\n" , $$ ); }
	| numeric_expr T_ASTERISK numeric_expr		{ $$ = $1 * $3; fprintf( stderr , "%f\n" , $$ ); }
	| numeric_expr T_SLASH numeric_expr		{ if($3 == 0) 
							  {
								yyerror("division par zero"); 
								yyerrok;
							  }	
							  else
							  {
								$$ = $1 / $3; fprintf( stderr , "%f\n" , $$ ); 
							  }
							}
;


boolean_expr:	
	T_TRUE							{ $$ = 1 ; }
	| T_FALSE						{ $$ = 0 ; }
	| T_NOT boolean_expr					{ $$ = (! $2) ; fprintf( stderr , "not %d => %d\n" ,$2, $$ );}
	| boolean_expr T_OR boolean_expr			{ $$ = ($1 || $3) ; fprintf( stderr , "%d OU %d => %d\n" ,$1, $3, $$ );}
	| boolean_expr T_AND boolean_expr			{ $$ = ($1 && $3) ; fprintf( stderr , "%d ET %d => %d\n" ,$1, $3, $$ );}
	| T_LEFT_BRACKET boolean_expr T_RIGHT_BRACKET		{ $$ = $2; fprintf( stderr , "(%d) => %d\n" ,$2, $$ );}

	| string_expr T_DIFFERENT  string_expr			{ $$ = strcmp( $1 , $3 ) != 0 ; fprintf( stderr , "%s != %s => %d\n" ,$1,$3, $$ );}
	| string_expr T_EQUAL  string_expr			{ $$ = strcmp( $1 , $3 ) == 0 ; fprintf( stderr , "%s == %s => %d\n" ,$1,$3, $$ );}	
	| string_expr T_LESS_THAN  string_expr			{ $$ = strcmp( $1 , $3 ) < 0 ; fprintf( stderr , "%s < %s => %d\n" , $1,$3,$$ );}
	| string_expr T_MORE_THAN  string_expr			{ $$ = strcmp( $1 , $3 ) > 0  ; fprintf( stderr , "%s > %s => %d\n" , $1,$3,$$ );}
	

	| guid_expr T_DIFFERENT  guid_expr			{ $$ = ! strcmp( $1 , $3 ) ; fprintf( stderr , "%s != %s => %d\n" ,$1,$3, $$ );}
	| guid_expr T_EQUAL  guid_expr				{ $$ = strcmp( $1 , $3 ) ; fprintf( stderr , "%s == %s => %d\n" ,$1,$3, $$ );}	

	| numeric_expr T_DIFFERENT  numeric_expr		{ $$ = ($1 != $3) ; fprintf( stderr , "%d != %d => %d\n" ,$1,$3, $$ );}
	| numeric_expr T_EQUAL  numeric_expr			{ $$ = ($1 == $3) ; fprintf( stderr , "%d == %d => %d\n" ,$1,$3, $$ );}

	| numeric_expr T_LESS_THAN  numeric_expr		{ $$ = ($1 < $3) ; fprintf( stderr , "%d < %d => %d\n" , $1,$3,$$ );}
	| numeric_expr T_MORE_THAN  numeric_expr		{ $$ = ($1 > $3) ; fprintf( stderr , "%d > %d => %d\n" , $1,$3,$$ );}
	| numeric_expr T_LESS_OR_EQUAL_THAN  numeric_expr	{ $$ = ($1 <= $3) ; fprintf( stderr , "%d <= %d => %d\n" , $1,$3,$$ );}
	| numeric_expr T_MORE_OR_EQUAL_THAN  numeric_expr	{ $$ = ($1 >= $3) ; fprintf( stderr , "%d >= %d => %d\n" , $1,$3,$$ );}
;

string_expr:
	T_CSTE_STRING		{strcpy( $$ , $1); printf( "[constante texte :%s]\n" , $1 ); }
;

%%
/* -------------------- */
/* epilogue		*/
/* -------------------- */
void yyerror(const char* msg) 
{
	fprintf( stderr, "ligne %d [%s] [%s]\n", lineNumber , msg, yytext );
}

