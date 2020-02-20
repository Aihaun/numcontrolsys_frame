#ifndef __ALGORITHM_H
#define __ALGORITHM_H
#include "bsplib.h"
typedef struct
{
	s32 x;
	s32 y;
	s32 z;
	s32 w;
	//float rad;
}PointDef;

typedef struct{
	s32 x;
	s32 y;
}mP2Def;

typedef struct
{
	u32 Vinit;
	u32 Tacc;
	u32 Vtar;
}VelocityDef;

extern s32 HZ_MultiAxMotion(void);
//extern s32 HZ_MultiAxSet(u8 Group,u8 AxNum,u8 Ax0,u8 Ax1,u8 Ax2,u8 Ax3);
//设置轴组的速度
extern s32 HZ_MultiAxSetVal(u8 Group,VelocityDef Vel);

//圆弧轴组运行 Pmid：圆弧中间点  Ptar：圆弧末点
extern s32 HZ_MultiAxMoveArc(u8 Group,u8 Num, PointDef Pmid, PointDef Ptar);

//整圆轴组运行 Pmid：圆弧中间点  Ptar: 圆弧末点 rot:圆方向
extern s32 HZ_MultiAxMoveCirc(u8 Group,u8 AxNum, PointDef Pmid, PointDef Ptar,u8 rot);

//extern s32 HZ_MultiAxMove(u8 Group,u8 AxNum, PointDef Ptar);
//获取轴组的插补状态，0空闲，1运行
extern s32 HZ_MultiAxStatus(u8 Group);

//设置直线插补轴组:Ax 组内的轴
extern s32 HZ_MultiAxSet(int Group,int Ax,...);

//插补轴组运行：Tar 组内轴的目标
extern s32 HZ_MultiAxMove(u8 Group,int Tar,...);

//插补轴组按比例获取弧长
extern mP2Def HZ_GetCircRatioPoint(u8 Group,float ratio);

//插补轴组获取中间点 默认rot写0 如果需要改变方向rot写1
extern mP2Def HZ_GetCircMiddlePoint(u8 Group,PointDef Pinit,PointDef Ptar,u8 rot);

//计算圆弧信息
extern s32 HZ_MultiAxCalcArc(u8 Group,u8 Num, PointDef Pinit,PointDef Pmid, PointDef Ptar);

//计算整圆信息
extern s32 HZ_MultiAxCalcCirc(u8 Group,u8 AxNum,PointDef Pinit, PointDef Pmid, PointDef Ptar,u8 rot);

//获取圆半径
extern float HZ_GetCircR(u8 Group);

//获取圆心X坐标
extern float HZ_GetCircRx(u8 Group);
	
//获取圆心Y坐标	
extern float HZ_GetCircRy(u8 Group);

//获取圆弧度
extern float HZ_GetCircArc(u8 Group);

//获取圆弧旋转方向
extern float HZ_GetCircRot(u8 Group);

#endif
