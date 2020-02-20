#ifndef _TOOL_H_
#define	_TOOL_H_

#include "DataDefine.h"
#include "bsplib.h"
#include "interlayer_config.h"
#include "Algorithm.h"


extern float ConvertToUserUnit(u32 num,s32 pulse);
extern s32 ConvertToMachineUnit(u32 num,float MM);
extern s32 Check_AxisStatu(u8 cnt);
extern s32 Check_xyzMotor(void);

#endif


