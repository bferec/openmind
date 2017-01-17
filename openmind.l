%{
/* ------------ */
/* openmind.l	*/
/* ------------ */

#include <stdio.h>
#include <string.h>

#include "openmindlib.h"

#include "openmind.tab.h"

extern int lineNumber;
extern int charNumber;

extern int yychar;

extern char *  msgerror;

extern void yyerror(const char * msg);

char string_buffer[ MAXLENGTH_STRING + 1 ];
char * string_buffer_ptr;

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
escape			\n|\r|\f|\b\|\t
spacetab		[ \t]+

entity			(?i:"entity")
property		(?i:"property")

%x comment
%x string

%%

				


"/*"			BEGIN (comment) ;	/* debut de commentaire				*/
<comment>[^*\n]*	{}			/* ignore tout ce qui n'est pas * 		*/
<comment>"*"+[^*/\n]*	{}			/* ignore tout ce qui n'est pas * suivi de /	*/

<comment>\n		{++ lineNumber  ; charNumber = 0; }
<comment>"*"+"/"	BEGIN( INITIAL );	/* fin de commentaire				*/
		

\" 			{ string_buffer_ptr = string_buffer; BEGIN (string ); }	/* debut constante texte	*/
<string>\"		{ 
				BEGIN(INITIAL); * string_buffer_ptr = '\0';  	/* fin constante texte		*/
				strcpy( yylval.string_value , string_buffer ) ;
				return T_CSTE_STRING;				
			}

<string>\\n		{ * string_buffer_ptr ++ = '\n'; }
<string>\\t		{ * string_buffer_ptr ++ = '\t'; }
<string>\\r		{ * string_buffer_ptr ++ = '\r'; }
<string>\\f		{ * string_buffer_ptr ++ = '\f'; }
<string>\\\\		{ * string_buffer_ptr ++ = '\\'; }

<string>[^\"\n\r\f\t\\]	{ 
			  * string_buffer_ptr ++ = * yytext;
			}

<INITIAL>\n		{ lineNumber ++ ;}

<INITIAL>{spacetab}	{ /* nothing */ }



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

"True"			{yylval.boolean_value = True ;  return T_TRUE ; }
"False"			{yylval.boolean_value = False ; return T_FALSE ; }


{entity}		{return T_ENTITY;}
{property}		{return T_PROPERTY;}

(?i:"create")		{return T_CREATE;}

(?i:"identity")		{return T_IDENTITY;}
(?i:"auto")		{return T_AUTO;}
(?i:"name")		{return T_NAME;}
(?i:"unique")		{return T_UNIQUE;}
(?i:"echo")		{return T_ECHO;}
	
(?i:"exit")		{return T_QUIT;}
(?i:"quit")		{return T_QUIT;}

{ident}			{
				if( check_ident( yytext ) ) 
				 {
					sprintf(msgerror, "utilisation d'un mot reservé comme variable : [%s]\n",yytext);
					yyerror(msgerror);
				 }				
				else
				{
					yylval.var = createVar( yytext );
					return T_IDENTIFIER;
				}
			}

.			{ charNumber ++; sprintf( msgerror, "caractere inconnu : [%s] ", yytext  ); yyerror(msgerror) ; return T_UNKNOWN;}

%%


