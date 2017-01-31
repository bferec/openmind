/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* openmindPropertyList.h		*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

extern property_node * property_list;
void FreeAllProperties( property_node * rootProperty );
void addpropertyNodeToList( property_node * onePropertyNode );
property * createProperty( char * oneguid , char * oneName , BOOL oneUniqueFlag );
void ClearPropertyList();

