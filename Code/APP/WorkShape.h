#ifndef _WORKSHAPE_H_
#define _WORKSHAPE_H_

#include "logicdata.h"
#include "tool.h"
//#include "interlayer_config.h"
#include "DataDefine.h"
#include "Algorithm.h" 
#include "USERTOOL.H" 

#define TimerRstA(a)		 a.tm = SysTim_GetUser()		  //0.1 ms
#define TimerCntA(a)		((SysTim_GetUser()-a.tm)/10) 	//计时转成ms

#define	it	(*t)
#define	FUNC_ENTERA \
	if(it.execute == 1 && it.step == 0)\
	{\
		it.step = 1;\
		it.done = 0;\
		it.count = 0;\
	}
#define PARAINIT(a)  memset(&a,0,sizeof(a));

//交流接触器				 
extern u32 Q_Contactor[5];
//变频器速度			
extern u32 Q_FreSpd[4];
//孔刀气缸
extern u32 Q_HoleCyl[2];
//孔刀气缸原点
extern u32 I_HoleKOrg[2]; 
//轴编号
extern u8 AxNum[3];

typedef enum	//轴定义
{
	X=0, 
	Y=1, 
	Z=2,

}motornum;

typedef struct
{
	int Ax_X;
	int Ax_Y;
	int Ax_Z;
}Ax_IO;

typedef struct 
{
	LogicParaDef Para;   //函数内部使用变量
	BasicParaDef Basic;  //基础参数
	WorkFileDef Size;    //尺寸参数
	int State;			//状态
	int Over;			//函数结束运行
	int KnifeNum;		//孔刀编号  0:1刀  1:2刀
}ShapeDef;


 
typedef struct
{
	u32 workNum;			//当前加工到第几个	
	float Hole1KnifeX_A;	//孔刀1到加工位置X向距离
	float Hole2KnifeX_A;	//孔刀2到加工位置X向距离
	float HoleKnifeY_B;		//孔刀到加工位Y向距离
	float Hole1KnifeZ;		//孔1刀到板面Z高度
	float Hole2KnifeZ;		//孔2刀到板面Z高度
	
	float SlotKnifeX_D; 	//槽刀加工尺寸D
	float OrderKnifeX_D;	//阶刀加工尺寸D
	float HingeOrgX;		//铰链加工中心X
}VariData;

typedef struct 
{
	LogicParaDef ChangerSpeed_ONTask;
	LogicParaDef ChangerSpeed_OFFTask;
} ParaTask;

extern ParaTask TK;

//Z向、Y向安全距离
#define  Safe_Z  30
#define  Safe_Y  30

//#define  Q_Set    OutPut_SetSta
//#define  ExQ_Set  HZ_ExOutPutSet
//#define  Q_Get    OutPut_GetSta
//#define  ExQ_Get  HZ_ExOutPutGet

//#define I_Get 	InPut_GetSta
//#define ExI_Get HZ_ExInPutGet

//#define En_Get  EN_GetSta

//#define AxGetsta  HZ_AxGetStatus

//*********************************************************************************************************************/
//使用说明：                                                                                                              
//该函数是执行铣圆动作，从内圆往外圆扩，一层层洗掉，Z深度递增下降，然后从外圆往内圆收缩，循环进行，直到到达设置的尺寸大小；       
//使用到3个轴（XYZ），可自行定义，但必须给该函数对应的轴赋予轴号，AxNum[0]为X轴，AxNum[1]为Y轴，AxNum[2]为Z轴；                
//IO定义                                                                                                                 
//需要在保存区定义BasicParaDef 基础参数、WorkParaDef 工作参数、WorkFileDef 尺寸参数；                                       
//                                                                                                                       
//                                                                                                                       
//*********************************************************************************************************************/
extern void KnifeHoleCirc(ShapeDef *t, int KnifeNum);
extern void KnifeHole(ShapeDef *t, int KnifeNum);
extern void KnifeLine(ShapeDef *t, int KnifeNum);
extern void KnifeLevelArc(ShapeDef *t, int KnifeNum);
extern void KnifeStandArc(ShapeDef *t, int KnifeNum);
//铣圆开始
extern void MillCirc1_start(ShapeDef *t);
//铣圆完成 return 0, 未完成 return 1  ，其他-1
extern s32 MillCirc1_End(ShapeDef *t);//return 0 
//铣圆终止
extern void MillCirc1_Over(ShapeDef *t);
#endif
