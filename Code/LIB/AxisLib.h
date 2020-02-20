#ifndef __AXISLIB_H
#define __AXISLIB_H
#include "bsplib.h"

#define AXIS_NUM PULS_NUM


#define AX_SPD_MAX	(200*1000)
#define AX_SPD_MIN	(20)
typedef enum 
{
	AXSTA_READY = 0,	//就绪状态
	AXSTA_STOP,			//停止状态
	AXSTA_STOPDEC,		//停止状态(减速停)
	AXSTA_DISCRETE,		//普通运动状态
	AXSTA_CONTINUOUS,	//连续运动
	AXSTA_HOMING,		//正在回原点
	AXSTA_DISABLE,		//未激活状态
	AXSTA_ERRSTOP,		//错误停
	AXSTA_SYNC,			//轴同步状态
}AxStateTp;


//对外接口
//01绝对定位
extern s32 HZ_AxMoveAbs(u8 AxNum,s32 pos);
//02相对定位
extern s32 HZ_AxMoveRel(u8 AxNum,s32 pos);
//03叠加定位
extern s32 HZ_AxMoveAdd(u8 AxNum,s32 pos);
//重新定位
//extern s32 HZ_AxMoveSuperImposed();
//恒速运行()
//AxNum :轴号，从0开始
//pos	:大于0正向，小于0反向 0：错误
extern s32 HZ_AxMoveVelocity(u8 AxNum,s32 pos);
extern s32 HZ_AxChSpd(u8 AxNum,u32 Spd);
//停止轴
extern s32 HZ_AxStop(u8 AxNum);

//////*****//////////////
//减速停
extern s32 HZ_AxStopDec(u8 AxNum);
//回原点
extern s32 HZ_AxHome(u8 AxNum);


//复位轴(复位错误及把轴状态归为就绪)
extern s32 HZ_AxReset(u8 AxNum);
//读轴状态
extern s32 HZ_AxGetStatus(u8 AxNum);
//读轴错误
extern s32 HZ_AxGetAxisErr(u8 AxNum);
//读当前位置
extern s32 HZ_AxGetCurPos(u8 AxNum);
//写当前位置
extern s32 HZ_AxSetCurPos(u8 AxNum,s32 pos);
//设置参数
extern s32 HZ_AxSetPara(u8 AxNum,\
				u32 Start,u32 TAcc,u32 Run,u32 TDec,u32 End,\
				u32 HomFast,u32 HomSlow,u32 HomOffset,\
				u32 TorS,u32 HomTimeOut);
//设置轴信号参数
extern s32 HZ_AxSetAxiSig(u8 AxNum,\
					u8 HomSigEn,u8 HomSigNum,u8 HomSigLev,\
					u8 UpSigEn,u8 UpSigNum,u8 UpSigLev,\
					u8 DwSigEn,u8 DwSigNum,u8 DwSigLev);
//设置上下软限位
extern s32 HZ_AxSetLimSoft(u8 AxNum,\
					u8 UpEn,s32 UpPos,\
					u8 DwEn,s32 DwPos);
//设置回原点模式
//AxNum :轴号
//Mod	:模式
//		0：反向找原点
//		1：先正向找上限位，再反向找原点
//		2：先反向找下限位，再正向找原点
extern s32 HZ_AxSetHomMod(u8 AxNum,u8 Mod);

#endif
