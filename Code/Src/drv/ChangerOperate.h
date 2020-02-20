#ifndef _CHANGEROPERATE_H_
#define _CHANGEROPERATE_H_
#include "logic.h"

typedef struct
{
	s32 a;
}ChangerHardDef;

typedef struct
{
	s32 a;
}ChangerSoftDef;

typedef struct
{
	LogicParaDef ChangerSpeed_ON;
	LogicParaDef ChangerSpeed_OFF;
	
	LogicParaDef ManuChangerSpeed_ON;
	LogicParaDef ManuChangerSpeed_OFF;
	LogicParaDef ChengerManu;
	
}ChangerFuncDef;

typedef struct ChangerConfigPara
{
	ChangerFuncDef TaskFunc;
	ChangerHardDef ConfigHardPara;
	ChangerSoftDef *ConfigSoftPara;
	
	s32 (*Run_ChangerSpeed_ON)(struct ChangerConfigPara *t);
	s32 (*Run_ChangerSpeed_OFF)(struct ChangerConfigPara *t);
	s32 (*Run_ManuChangerSpeed_ON)(struct ChangerConfigPara *t);
	s32 (*Run_ManuChangerSpeed_OFF)(struct ChangerConfigPara *t);
	s32 (*Run_ChengerManu)(struct ChangerConfigPara *t);
	
	s32 (*Get_ChangerSpeed_ONSta)(struct ChangerConfigPara *t);
	s32 (*Get_ChangerSpeed_OFFSta)(struct ChangerConfigPara *t);
	s32 (*Get_ManuChangerSpeed_ONSta)(struct ChangerConfigPara *t);
	s32 (*Get_ManuChangerSpeed_OFFSta)(struct ChangerConfigPara *t);
	s32 (*Get_ChengerManuSta)(struct ChangerConfigPara *t);
	
	void (*ChangerOperateLoop)(struct ChangerConfigPara *t);
	
	
}ChangerDef;


extern ChangerDef ChC;

#endif
