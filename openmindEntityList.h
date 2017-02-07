/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindEntityList.h			*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

extern entity_node * entity_list;

entity * allocMemEntity();
entity * createEntity( char * oneguid , char * oneName , BOOL oneUniqueFlag );
void addEntityNodeToList( entity_node * oneEntityNode );
void ClearEntityList();
