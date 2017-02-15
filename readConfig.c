/* -----------------------------*/
/* -----------------------------*/
/* 	readConfig.c		*/
/* -----------------------------*/
/* -----------------------------*/
#include <stdio.h>
#include <string.h>


#define DEFAULT_CONFIG_NAME	"fdl.conf"
#define DELIMITER 		'='

#define MAXLINELENGTH 		256 
#define MAXKEY 			256 


typedef struct _configItem
{
   char key[MAXLINELENGTH];
   char value[MAXLINELENGTH];
}ConfigItem;

typedef struct _config
{
	ConfigItem items[MAXKEY];
	int nbKeys;
}Configuration;


Configuration config;
char configFileName[ MAXLINELENGTH ];

/* -----------------------------*/
/* -----------------------------*/
Configuration * getConfig(char * filename) 
{

FILE * file;
char line[MAXLINELENGTH];
char key[MAXLINELENGTH];
char value[MAXLINELENGTH];
char * result;
char * s, * d;

	if( !  strlen( filename )  )
	{
		strcpy( configFileName, DEFAULT_CONFIG_NAME );
	}
	else
	{
		strcpy( configFileName, filename );		
	}

        file = fopen (configFileName, "r");
	
        if (file != NULL)
        { 		
		config.nbKeys=0;

                while( ! feof( file ) )
                {
			
			result = fgets( line, MAXLINELENGTH , file );

			if( result == NULL )
				break;
		
			s = line ;
			d = key;
			do
			{
				if( * s == '\n') 
				{ 
					* d = '\0'; 
					break; 
				}
				if( * s != ' ' &&  * s != '\t' &&  * s != DELIMITER  )  
				{ 
					* d = * s; 
					d ++ ; 
				}
				if( * s == DELIMITER )
				{
					* d = '\0';
					d = value;
				}
				s ++;
				
			}while( 1 );

			strcpy( config.items[config.nbKeys].key , key );
			strcpy( config.items[config.nbKeys].value , value );
			config.nbKeys ++;
                }

                fclose(file);
        }
        return & config;

}

void main(int argc , char * * argv )
{
Configuration *c;
	c = getConfig("");

	printf( "Nombre de cles : %d\n" , c -> nbKeys );

	for( int x = 0 ; x < c -> nbKeys ; x ++ )
	{
		printf( "key: [%s] value: [%s]\n" , c-> items[x].key , c-> items[x].value );
	}
}

