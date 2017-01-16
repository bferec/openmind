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
#define DEBUG 0 
#ifdef DEBUG
#define TRACE printf("reduce at line %d\n", __LINE__);
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


int lineNumber;	/* current line number */

void yyerror(const char* s);


%}
/* -------------------- */
/* bison declarations	*/
/* -------------------- */
%define parse.trace
%define parse.error verbose

%union 
{
	struct 
	{
        	float float_value;			/* float value					*/
	        int   integer_value;			/* integer value				*/
	} number_value;					/* numeric value				*/
	enum { False, True } boolean_value;		/* booleanvalue					*/
	char guid_value[ GUID_LENGTH ];			/* guid value identifier of entity or property	*/
	char string_value[ MAXLENGTH_STRING + 1 ] ;	/* string constant and vars.			*/
	variable * var;
} 


%token <number_value.integer_value> T_INT
%token <number_value.float_value> T_FLOAT

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


%token<var> T_IDENTIFIER
%token<boolean_value> T_TRUE
%token<boolean_value> T_FALSE

/* -------------------- */
/* keywords		*/
/* -------------------- */
%token T_CREATE
%token T_ENTITY
%token T_PROPERTY
%token T_IDENTITY
%token T_AUTO
%token T_NAME
%token T_UNIQUE
%token T_ECHO
%token T_QUIT

%token<guid_value> T_GUID
%token<string_value> T_CSTE_STRING

%token T_UNKNOWN

%type <guid_value> guid_expr
%type <number_value.float_value>  numeric_expr
%type <boolean_value>  boolean_expr
%type <string_value>  string_expr

%type <var>  lvalue

%type <var>  rvalue_var
%type <number_value.float_value> rvalue_number
%type <boolean_value> rvalue_boolean
%type <string_value> rvalue_string

/* -------------------- */
/* -------------------- */
/* Axiome		*/
/* -------------------- */
/* -------------------- */
%start instList

/* -------------------- */
/* Grammar rules	*/
/* -------------------- */
%%

/* -------------------- */
/* liste instructions	*/
/* -------------------- */
instList:
	%empty
	| T_SEMICOLON
	| stmt T_SEMICOLON 
	| instList stmt T_SEMICOLON
;

/* -------------------- */
/* instruction		*/
/* -------------------- */
stmt:
	expr 			{}
	| create_stmt		{}
	| echo_stmt		{}
	| assign_stmt		{}
	| T_QUIT		{exit (0);}
;

echo_stmt:
	T_ECHO numeric_expr		{fprintf(stdout, "%f" , $2); }
	| T_ECHO string_expr		{fprintf(stdout, "%s" , $2); }
	| T_ECHO boolean_expr		{fprintf(stdout, "%s" , $2 ? "True" : "False" ); }
;

/* -------------------- */
/* affectation		*/
/* -------------------- */
assign_stmt:
	  lvalue T_ASSIGN rvalue_var		{	
							char destIdent[256];
							strcpy( destIdent , $1 -> ident );	/* sauvegarder identifier variable	*/
							memcpy( (void *) $1 , (void *) $3 , sizeof(struct variable)  );		/* copier dest dans src	*/
							strcpy( $1 -> ident , destIdent );	/* restaurer identifier	*/
						}	
	| lvalue T_ASSIGN rvalue_number		{
							$1 -> type = FLOAT;
							$1 -> val.float_value  = $3;
						}
	| lvalue T_ASSIGN rvalue_boolean	{
							$1 -> type = BOOLEAN;
							$1 -> val.boolean_value  = $3;
						}
	| lvalue T_ASSIGN rvalue_string		
						{
							$1 -> type = STRING;
							strcpy( $1 -> val.string_value ,  $3 );
						}
;

rvalue_var:
	T_IDENTIFIER 	{$$ = yylval.var; }	
;
rvalue_number:
	numeric_expr 	{ $$ = $1; }
;
rvalue_boolean:
	boolean_expr 	{ $$ = $1; }
;
rvalue_string:
	string_expr 	{ strcpy( $$ , $1 );}
;
/* -------------------- */
/* ce qui peut être à	*/
/* gauche de =		*/
/* -------------------- */
lvalue:
	T_IDENTIFIER								{fprintf( stderr , "lvalue : [%s]\n" , $1 -> ident ); }
	| T_IDENTIFIER T_LEFT_SQUARE_BRACKET expr T_RIGHT_SQUARE_BRACKET	{fprintf( stderr , "lvalue: indicee [%s]\n" , $1 -> ident ); }
	| error T_SEMICOLON 		{YYABORT;}


;
/* -------------------- */
/* Create		*/
/* -------------------- */
create_stmt:
	create_entity_stmt		{fprintf(stderr, "create entity stmt, yytext: [%s] yychar : [%d]\n" , yytext , yychar );}
	| create_property_stmt		{fprintf(stderr, "create property stmt,yytext: [%s] yychar : [%d]\n" , yytext , yychar );}
;
/* -------------------- */
/* Create ENTITY	*/
/* -------------------- */
create_entity_stmt:
	T_CREATE T_ENTITY T_LEFT_BRACE entity_defs T_RIGHT_BRACE	{ }
;
/* -------------------- */
/* corps ENTITY		*/
/* -------------------- */
entity_defs:
	obj_defs
;
/* -------------------- */
/* Create Property	*/
/* -------------------- */
create_property_stmt:
	T_CREATE T_PROPERTY T_LEFT_BRACE property_defs T_RIGHT_BRACE	{ }
;
/* -------------------- */
/* corps property	*/
/* -------------------- */
property_defs:
	obj_defs
;
/* -------------------- */
/* corps property	*/
/* -------------------- */
obj_defs:
	 guid_defs T_SEMICOLON name_defs T_SEMICOLON
	| guid_defs T_SEMICOLON name_defs T_UNIQUE T_SEMICOLON	{}
;
/* -------------------- */
/* identity		*/
/* -------------------- */
guid_defs:
	T_IDENTITY T_LEFT_BRACE guid_expr T_RIGHT_BRACE
;
/* -------------------- */
/* name			*/
/* -------------------- */
name_defs:
	T_NAME T_LEFT_BRACE string_expr T_RIGHT_BRACE 
;

/* -------------------- */
/* Expression		*/
/* -------------------- */
expr:
	string_expr					
	| numeric_expr
	| boolean_expr
	| guid_expr
;
/* -------------------- */
/* Expression	Guid	*/
/* -------------------- */
guid_expr:
	T_AUTO		{ char guid[33]; NewGuid( guid ); strcpy( $$ , guid ); fprintf( stderr , "[Auto: %s]\n" , $$ ); }
	| T_GUID	{ strcpy( $$ ,  $1 );fprintf( stderr , "[Guid: %s]\n" , $$ ); }
;
/* -------------------- */
/* Expression numerique	*/
/* -------------------- */
numeric_expr:
	T_INT						{ $$ = (float) $1 ; }	
	| T_FLOAT					{ $$ = $1; }				
	| T_LEFT_BRACKET numeric_expr T_RIGHT_BRACKET	{ $$ = $2; }
	| T_MINUS_SIGN numeric_expr 			{ $$ = -$2; }
	| numeric_expr T_PLUS_SIGN numeric_expr		{ $$ = $1 + $3; }
	| numeric_expr T_MINUS_SIGN numeric_expr	{ $$ = $1 - $3; }
	| numeric_expr T_ASTERISK numeric_expr		{ $$ = $1 * $3; }
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
/* -------------------- */
/* Expression booleeene	*/
/* -------------------- */
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
/* -------------------- */
/* Expression chaine	*/
/* -------------------- */
string_expr:
	T_CSTE_STRING		{strcpy( $$ , $1); }
;

%%
/* -------------------- */
/* epilogue		*/
/* -------------------- */
void yyerror(const char* msg) 
{
	fprintf( stderr, "Erreur en ligne %3.3d : [%s]\n", lineNumber , msg  );
}

