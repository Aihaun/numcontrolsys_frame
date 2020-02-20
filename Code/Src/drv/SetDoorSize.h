#ifndef _SETDOORSIZE_H_
#define _SETDOORSIZE_H_
#include "logicdata.h"

typedef struct
{
	s32 a;
}SetDoorSizeHardDef;

typedef struct
{
	s32 a;
}SetDoorSizeSoftDef;

typedef struct
{
	LogicParaDef SetDoorWideAndThick;
}SetDoorSizeFuncDef;

typedef struct SetDoorSizeConfigPara
{
	SetDoorSizeFuncDef TaskFunc;
	SetDoorSizeHardDef ConfigHardPara;
	SetDoorSizeSoftDef *ConfigSoftPara;
//	
	s32 (*Run_SetDoorWideAndThick)(struct SetDoorSizeConfigPara *t);
	
	s32 (*Get_SetDoorWideAndThickSta)(struct SetDoorSizeConfigPara *t);
	
	void (*SetDoorSizeLoop)(struct SetDoorSizeConfigPara *t);
	
	
}SetDoorSizeDef;

extern SetDoorSizeDef SDC;

#endif
