#ifndef _USERTOOL_H_
#define	_USERTOOL_H_

#include "DataDefine.h"
#include "bsplib.h"
#include "interlayer_config.h"


typedef enum	//轴动模式选择
{
    ABSM,//0
    RELM,//1
    SPDM,//2
    GOHOMEM,//3
    STOPM,	//4
} AxMode;


extern void AxisRun(s8 axnum, s8 mode, float spd, float pos);
extern s32 Get2AxSta(u8 num1, u8 num2);
extern s32 GetAxSta(u8 num1);
extern s32 MillCircPath(u8 Axnum1, u8 Axnum2,s32 x1, s32 y1, s32 x2, s32 y2, float spd);
#endif


