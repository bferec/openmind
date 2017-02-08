/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindlib.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/



#define KEYWORDS_COUNT 15		/* nombre de mots cles du langage			*/
#define GUID_LENGTH 33			/* longueur xhaine guid hors zero final			*/
#define BOOL int			/* type booleen						*/
#define TRUE	1
#define FALSE	0
#define MAXLENGTH_STRING 255		/* longueur maxi identificateurs et constantes texte	*/

/* -------------------------------------*/
/* type de nombres 			*/
/* -------------------------------------*/
typedef enum number_type { INTEGER_NUMBER_TYPE, FLOAT_NUMBER_TYPE } numberType;

void yyerror(const char* s);

void NewGuid( char * result );

char * strlwr( char * );
char * strupr( char * );
char * findkeyword( char * onekeyword );

void yyerror(const char* msg);





