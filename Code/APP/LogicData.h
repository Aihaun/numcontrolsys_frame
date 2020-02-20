#ifndef __LOGICDATA_H
#define __LOGICDATA_H
#include "bsplib.h"



#define BC 		BasicPara.CheckPara		//对刀参数
#define BM  	BasicPara.MechanicalPara   //机械参数
#define PCBW  	p->ConfigSoftPara->BasicPara.workPara         //加工参数
#define PCW  	BasicPara.WorkFile		//尺寸文件

typedef struct
{
    u8 execute;
    u8 step;
    u8 done;
	u8 mode;
    s32 count;
    s32 index;
	u32 Tms;
    u32 tm;
} LogicParaDef;

typedef struct
{
    u32 execute;
    u32 mode;
    s32 pos;
    u32 speed;
} GoPosPara;	//上位机轴运动接口


#endif
