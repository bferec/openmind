/* symbol.h	*/

typedef struct 
{
	char * name;
	struct symbol * next;
} symbol;


extern symbol * putsymbol( char * onename );
extern symbol * getsymbol( char * onename );
