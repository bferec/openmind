%{
/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmind.l				*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "openmindlib.h"
#include "entity.h"
#include "openmindvalue.h"
#include "openmindvarlist.h"
#include "openmindconstant.h"
#include "operator.h"
#include "syntaxtree.h"

#include "openmind.tab.h"

extern int lineNumber;
extern int charNumber;

extern int yychar;

extern char *  msgerror;

extern void yyerror(const char * msg);

char string_buffer[ MAXLENGTH_STRING + 1 ];
char * string_buffer_ptr;

BOOL err_check_ident;

void charCount()
{
	charNumber += strlen( yytext);
}

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
%x linecomment
%x string
%x caracter
%%

				
"//"			BEGIN (linecomment) ;	/* debut de commentaire	 ligne			*/
<linecomment>[^\n]*	{}			/* ignore tout jusqu'à fin de ligne 		*/
<linecomment>\n		{++ lineNumber  ; charNumber = 0; BEGIN( INITIAL );}


"/*"			BEGIN (comment) ;	/* debut de commentaire	multiligne		*/
<comment>[^*\n]*	{}			/* ignore tout ce qui n'est pas * 		*/
<comment>"*"+[^*/\n]*	{}			/* ignore tout ce qui n'est pas * suivi de /	*/

<comment>\n		{++ lineNumber  ; charNumber = 0; }
<comment><<EOF>>	{ yyerror("Unclosed Comment\n"); }
<comment>"*"+"/"	BEGIN( INITIAL );	/* fin de commentaire				*/
		

\" 			{ string_buffer_ptr = string_buffer; BEGIN (string ); }	/* debut constante texte	*/
<string>\"		{ 
				BEGIN(INITIAL); * string_buffer_ptr = '\0';  	/* fin constante texte		*/
				charCount();
				strcpy( yylval.string_value , string_buffer ) ;
				/* fprintf(stderr, "string lex : [%s]\n",  yylval.string_value); */
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

<INITIAL>\n		{ lineNumber ++ ;charNumber = 0;}

\'			{  string_buffer_ptr = string_buffer;  BEGIN (caracter ); }	/* debut constante caractere	*/
<caracter>\'		{ 
				BEGIN(INITIAL); string_buffer_ptr[1]= '\0';  	/* fin constante caractere		*/
				charCount();
				yylval.char_value = string_buffer[0] ;
				return T_CSTE_CHAR;				
			}
<caracter>[^\'\n\r\f\t\\]	{ string_buffer[0] = * yytext; }


<INITIAL>{spacetab}	{ charCount(); }



"+"			{charCount() ; return T_PLUS_SIGN;}
"-"			{charCount() ; return T_MINUS_SIGN;}
"*"			{charCount() ; return T_ASTERISK;}
"/"			{charCount() ; return T_SLASH;}

"++"			{charCount() ; return T_INCR;}
"--"			{charCount() ; return T_DECR;}

"+="			{charCount() ; return T_PLUS_EGAL_SIGN;}
"-="			{charCount() ; return T_MINUS_EGAL_SIGN;}
"*="			{charCount() ; return T_ASTERISK_EGAL;}
"/="			{charCount() ; return T_SLASH_EGAL;}


"{"			{charCount() ; return T_LEFT_BRACE;}
"}"			{charCount() ; return T_RIGHT_BRACE;}

"("			{charCount() ; return T_LEFT_BRACKET;}
")"			{charCount() ; return T_RIGHT_BRACKET;}

"["			{charCount() ; return T_LEFT_SQUARE_BRACKET;}
"]"			{charCount() ; return T_RIGHT_SQUARE_BRACKET;}

":"			{charCount() ; return T_COLON;}
";"			{charCount() ; return T_SEMICOLON;}
","			{charCount() ; return T_COMMA;}
"&"			{charCount() ; return T_AMPERSAND;}
"|"			{charCount() ; return T_VERTICAL_BAR;}


"||"			{charCount() ; return T_OR;}
"&&"			{charCount() ; return T_AND;}
"!"			{charCount() ; return T_NOT;}
"^"			{charCount() ; return T_XOR;}

"<"			{charCount() ; return T_LESS_THAN;}
">"			{charCount() ; return T_MORE_THAN;}
"<="			{charCount() ; return T_LESS_OR_EQUAL_THAN;}
">="			{charCount() ; return T_MORE_OR_EQUAL_THAN;}
"!="			{charCount() ; return T_DIFFERENT;}		
"=="			{charCount() ; return T_EQUAL;}
"=" 			{charCount() ; return T_ASSIGN;}

{integer}		{ 
				charCount() ; 
				yylval.number_value.integer_value = atoi( yytext ) ; 
				return T_INT ; 
			}
{float}			{
				charCount() ;
				yylval.number_value.float_value = atof( yytext ) ; 
				return T_FLOAT ; 
			}

{guid}			{ strcpy( yylval.guid_value , yytext ) ; charCount() ; return T_GUID;}

(?i:"True")		{yylval.boolean_value = True ;  charCount() ; return T_TRUE ; }
(?i:"False")		{yylval.boolean_value = False ; charCount() ; return T_FALSE ; }
 

{entity}		{charCount() ; return T_ENTITY;}
{property}		{charCount() ; return T_PROPERTY;}

(?i:"while")		{charCount() ; return T_WHILE;}
(?i:"do")		{charCount() ; return T_DO;}
(?i:"for")		{charCount() ; return T_FOR;}

(?i:"create")		{charCount() ; return T_CREATE;}

(?i:"identity")		{charCount() ; return T_IDENTITY;}
(?i:"auto")		{charCount() ; return T_AUTO;}
(?i:"name")		{charCount() ; return T_NAME;}
(?i:"unique")		{charCount() ; return T_UNIQUE;}
(?i:"echo")		{charCount() ; return T_ECHO;}
	
(?i:"exit")		{charCount() ; return T_QUIT;}
(?i:"quit")		{charCount() ; return T_QUIT;}

{ident}			{
				charCount();
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



