#ifndef _SETTOOL_H_
#define _SETTOOL_H_
#include "logicdata.h"

typedef struct
{
	s32 a;
}SetToolHardDef;

typedef struct
{
	s32 a;
}SetToolSoftDef;

typedef struct
{
	LogicParaDef SetLevelTool;
	LogicParaDef SetVerticalTool;
	LogicParaDef SetTool;
}SetToolFuncDef;

typedef struct SetToolConfigPara
{

	SetToolFuncDef TaskFunc;
	SetToolHardDef ConfigHardPara;
	SetToolSoftDef *ConfigSoftPara;
	
	s32 (*Run_SetLevelTool)(struct SetToolConfigPara *t);
	s32 (*Run_SetVerticalTool)(struct SetToolConfigPara *t);
	s32 (*Run_SetTool)(struct SetToolConfigPara *t);
	
	s32 (*Get_SetLevelToolSta)(struct SetToolConfigPara *t);
	s32 (*Get_SetVerticalToolSta)(struct SetToolConfigPara *t);
	s32 (*Get_SetToolSta)(struct SetToolConfigPara *t);
	
	void (*SetToolLoop)(struct SetToolConfigPara *t);
	
	
}SetToolDef;

extern SetToolDef STC;
#endif
