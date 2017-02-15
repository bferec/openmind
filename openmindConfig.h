/* -----------------------------*/
/* openmindConfig.h		*/
/* -----------------------------*/

#define DEFAULT_CONFIG_NAME	"openmind.conf"
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

Configuration * loadConfig(char * filename);
char * getConfigValue(Configuration * c,  char * key );
