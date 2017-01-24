/* -------------------------------------*/
/* -------------------------------------*/
/* 					*/
/* entity.h				*/
/* 					*/
/* -------------------------------------*/
/* -------------------------------------*/

/* -----------------------------------------------------*/
/* definition entite					*/
/* -----------------------------------------------------*/
typedef struct entity
{
	char guid[GUID_LENGTH];
	char name[ MAXLENGTH_STRING  + 1 ];
	BOOL unique_name;
	
}entity;

/* -----------------------------------------------------*/
/* definition propriete					*/
/* -----------------------------------------------------*/
typedef struct property
{
	char guid[GUID_LENGTH];
	char name[ MAXLENGTH_STRING  + 1 ];
	BOOL unique_name;
}property;

