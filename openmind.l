%{
/* ------------ */
/* openmind.l	*/
/* ------------ */

#include <stdio.h>
#include <string.h>

#include "openmindlib.h"

#include "openmind.tab.h"


extern int lineNumber;

extern void yyerror(const char * msg);
char msgerror[ 256 ];

BOOL err_check_ident;

%}

%option noyywrap

digit			[0-9]
hexadigit		{digit}|[a-fA-F]
hexanumber		{hexadigit}+
guid			{hexanumber}\-{hexanumber}\-{hexanumber}\-{hexanumber}\-{hexanumber}
integer			{digit}+
float			{digit}+\.{digit}+|\.{digit}+
ident			[a-zA-Z_][0-9a-zA-Z_]*	
string			\"[^"]*\"
spacetab		[ \t\r]+

%%

"/*"[^*]*"*/"|"/*"[^/]*"*/" ;
\/\/.* ;



{spacetab}		{ /* nothing */ }

"\n"			{ ++ lineNumber  ; }

"+"			{return T_PLUS_SIGN;}
"-"			{return T_MINUS_SIGN;}
"*"			{return T_ASTERISK;}
"/"			{return T_SLASH;}

"{"			{return T_LEFT_BRACE;}
"}"			{return T_RIGHT_BRACE;}

"("			{return T_LEFT_BRACKET;}
")"			{return T_RIGHT_BRACKET;}

"["			{return T_LEFT_SQUARE_BRACKET;}
"]"			{return T_RIGHT_SQUARE_BRACKET;}

":"			{return T_COLON;}
";"			{return T_SEMICOLON;}
","			{return T_COMMA;}
"&"			{return T_AMPERSAND;}
"|"			{return T_VERTICAL_BAR;}


"||"			{return T_OR;}
"&&"			{return T_AND;}
"!"			{return T_NOT;}

"<"			{return T_LESS_THAN;}
">"			{return T_MORE_THAN;}
"<="			{return T_LESS_OR_EQUAL_THAN;}
">="			{return T_MORE_OR_EQUAL_THAN;}
"!="			{return T_DIFFERENT;}		
"=="			{return T_EQUAL;}
"=" 			{return T_ASSIGN;}

{integer}		{ yylval.number_value.integer_value = atoi( yytext ) ; return T_INT ; }
{float}			{ yylval.number_value.float_value = atof( yytext )   ; return T_FLOAT ; }
{guid}			{ strcpy( yylval.string_value , yytext ) ; return T_GUID;}
{string}		{ strcpy( yylval.string_value , yytext ) ; return T_CSTE_STRING;}

"True"			{yylval.boolean_value = True ;  return T_TRUE ; }
"False"			{yylval.boolean_value = False ; return T_FALSE ; }

(?i:"create")		{return T_CREATE;}
(?i:"entity")		{return T_ENTITY;}
(?i:"property")		{return T_PROPERTY;}
(?i:"identity")		{return T_IDENTITY;}
(?i:"auto")		{return T_AUTO;}
(?i:"name")		{return T_NAME;}
(?i:"unique")		{return T_UNIQUE;}
	
(?i:"exit")		{return T_QUIT;}
(?i:"quit")		{return T_QUIT;}


{ident}			{err_check_ident = check_ident( strdup(yytext)  );
			 if( ! err_check_ident  )  
			{
				strcpy( yylval.string_value , yytext ); 
			}
			else 
			{
				sprintf( msgerror, "Mot cle interdit comme identificateur : [%s] ", yytext  );
				yyerror(msgerror);
			}
			
			return T_IDENTIFIER;
			}



.			{ sprintf( msgerror, "caractere inconnu : [%s] ", yytext  ); yyerror(msgerror) ; return T_UNKNOWN;}

%%


