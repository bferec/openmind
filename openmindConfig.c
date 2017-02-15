/* -----------------------------*/
/* -----------------------------*/
/* 	openmindConfig.c	*/
/* -----------------------------*/
/* -----------------------------*/
#include <stdio.h>
#include <string.h>

#include "openmindConfig.h"



Configuration config;
char configFileName[ MAXLINELENGTH ];

/* -----------------------------*/
/* -----------------------------*/
Configuration * loadConfig(char * filename) 
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

/* -----------------------------*/
/* -----------------------------*/
char * getConfigValue(Configuration * c,  char * key )
{
char * result = NULL;

	for( int x = 0 ; x < c -> nbKeys ; x ++ )
	{
		if( ! strcmp( key , c-> items[x].key ) )
		{
			result = strdup( c-> items[x].value );
			break;
		}
	}
	return result;
}


