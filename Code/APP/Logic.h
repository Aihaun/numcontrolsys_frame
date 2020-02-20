#ifndef _LOGIC_H_
#define	_LOGIC_H_

#include "DataDefine.h"    
//#include "bsplib.h"
#include "interlayer_config.h"
#include "FSM.h"
#include "can_master.h"
#include "tool.h"
#include "string.h"
#include "logicdata.h"
#include "iodefine.h"
#include "AxisMove.h"
#include "Motion.h"
#include "JogClass.h"

#include "HoleShape.h"   
#include "SlotShape.h" 
#include "HingeShape.h"
#include "ChangerOperate.h"
#include "SetTool.h"
#include "SetDoorSize.h"


#define TimerRst(a)		 a.tm = SysTim_GetUser()		  //0.1 ms
#define TimerCnt(a)		((SysTim_GetUser()-a.tm)/10) 	//计时转成ms

#define	ON	0
#define	OFF	1

//Z向、Y向安全距离
#define  Safe_Z  30
#define  Safe_Y  30

#define PARAINIT(a)  memset(&a,0,sizeof(a));
#define INITTASK(a) if(a.execute==1&&a.step==0){a.step = 1;}
#define	it	(*t)
#define	FUNC_ENTER \
	if(it.execute == 1 && it.step == 0)\
	{\
		it.step = 1;\
		it.done = 0;\
		it.count = 0;\
	} 

#define CHECK_NUM 1
#define	VACUUM_NUM 1
#define	DOWN_NUM 1

#define	NORMALMODE	0		//正常模式
#define	AGINGMODE	1		//老化模式
#define	STEPMODE	2		//单步调试
#define AXISDELAY	5		//停轴延时
#define ENDCASE     0xff	//最后一个case

#define SmallNum 100   //小数位数


#define	Q_ON	0
#define	Q_OFF	1
	
typedef struct//系统任务队列
{
    LogicParaDef AxisMoveTask[PULS_NUM];
    LogicParaDef XYZWRESETTask;
	LogicParaDef ResetTask;
	LogicParaDef AutoRunTask;
		
	LogicParaDef CluthManualTask;
	LogicParaDef Y_GoHomeTask;
	LogicParaDef Ax_GoHomeTask[PULS_NUM];
	LogicParaDef IndicateTask;
//	LogicParaDef KnifeArc1Task;
//	LogicParaDef KnifeArc1Task;
//	LogicParaDef KnifeArc1Task;
//	LogicParaDef KnifeArc1Task;
//	LogicParaDef KnifeArc1Task;
//	LogicParaDef KnifeArc1Task;
	
} Task;
//extern Task LogicTask;

extern Task LT;

typedef enum	//触发器编号定义
{
	Tg0,Tg1,Tg2,Tg3,Tg4,Tg5,Tg6,Tg7,Tg8,Tg9,
	Tg10,Tg11,Tg12,Tg13,Tg14,Tg15,Tg16,Tg17,Tg18,//Tg19,
	//Tg20,Tg21,Tg22,Tg23,Tg24,Tg25,Tg26,Tg27,//Tg28,Tg29,
}TgNum;

typedef enum	//定时器编号定义
{
  Ut0,Ut1,Ut2,Ut3,Ut22,

}UtmNum;


typedef enum	//加工尺寸标识
{
	A=0, 
	B=1, 
	C=2,
	D=3,
	E=4, 
	F=5,
	G=6,
	H=7,
	I=8,
	J=9,
	K=10,
	L=11, 
	M=12,
	N=13,
	P=14,
	Q=15,
	R=16,
}WorkSize;

#define Q_Set    OutPut_SetSta
#define ExQ_Set  HZ_ExOutPutSet
#define Q_Get    OutPut_GetSta
#define ExQ_Get  HZ_ExOutPutGet

#define I_Get 	InPut_GetSta
#define ExI_Get HZ_ExInPutGet

#define En_Get  EN_GetSta

#define AxGetsta  HZ_AxGetStatus

extern void Logic(void);

extern void WorkEnd(void);

#endif


