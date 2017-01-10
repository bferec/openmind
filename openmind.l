%{
/* ------------ */
/* openmind.l	*/
/* ------------ */

#include <stdio.h>
#include <string.h>

#include "openmind.tab.h"


extern int lineNumber;

extern void yyerror(const char * msg);


%}

%option noyywrap

digit			[0-9]
hexadigit		{digit}|[a-fA-F]
hexanumber		{hexadigit}+
guid			{hexanumber}\-{hexanumber}\-{hexanumber}\-{hexanumber}\-{hexanumber}
integer			{digit}+
float			{digit}+\.{digit}+|\.{digit}+
ident			[a-zA-Z_][0-9a-zA-Z_]*	


%%

"/*"[^*]*"*/"|"/*"[^/]*"*/" ;
\/\/.* ;



[ \t]+			{ /* nothing */ }

"\n"			{ ++ lineNumber  ; }
'\r'			{ /* nothing */ }

"+"			{return T_PLUS_SIGN;}
"-"			{return T_MINUS_SIGN;}
"*"			{return T_ASTERISK;}
"/"			{return T_SLASH;}

"{"			{return T_LEFT_BRACE;}
"}"			{return T_RIGHT_BRACE;}

"("			{return T_LEFT_BRACKET;}
")"			{return T_RIGHT_BRACKET;}

”:=” 			{ return(T_ASSIGN); }

"."			{return T_DOT;}
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

{integer}		{ yylval.number_value.integer_value = atoi( yytext ) ; return T_INT ; }
{float}			{ yylval.number_value.float_value = atof( yytext )   ; return T_FLOAT ; }
{guid}			{ strcpy( yylval.string_value , yytext ) ; return T_GUID;}

"True"			{yylval.boolean_value = True ;  return T_TRUE ; }
"False"			{yylval.boolean_value = False ; return T_FALSE ; }

(?i:"create")		{return T_CREATE;}
(?i:"entity")		{return T_ENTITY;}
(?i:"property")		{return T_PROPERTY;}
(?i:"identity")		{return T_IDENTITY;}
(?i:"auto")		{return T_AUTO;}
			

(?i:"exit")		{return T_QUIT;}
(?i:"quit")		{return T_QUIT;}

{ident}			{ strcpy( yylval.string_value , yytext ) ; return T_IDENT;}

	
%%


