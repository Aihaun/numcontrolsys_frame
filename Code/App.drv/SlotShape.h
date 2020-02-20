#ifndef _SLOTSHAPE_H_
#define _SLOTSHAPE_H_

#include "logicdata.h"

typedef struct 
{
	u32 Ax_X;           //X轴
	u32 Ax_Y;           //Y轴
	u32 Ax_Z;           //Z轴
	                 //
	u32 Q_SlotCyl;		//锁槽气缸
	u32 Q_OrderCyl;		//锁槽气缸
	u32 Q_FreSpd1;		//变频器速度1
	u32 Q_FreSpd2;		//变频器速度2
	u32 Q_FreSpd3;		//变频器速度3
	u32 Q_FreSpd4;		//变频器速度4
	u32 Q_SlotSW;		//锁槽刀接触器
	                //
	u32 I_XOrg;         //X轴原点
	u32 I_YOrg;	        //Y轴原点
	u32 I_ZOrg;         //Z轴原点
	u32 I_SlotCylOrg;   //锁槽气缸原点
	u32 I_OrderCylOrg;  //锁阶气缸原点
}SlotHardDef;

typedef struct 
{
	float workSpd;		//加工速度		4064
	float knifeSpdY;	//Y进刀速度
	float slotKD;		//锁槽刀直径
	float stairKD;		//锁阶刀直径	
	float aa[6];		//预留 
}SlotSoftDef;

typedef struct
{
	int workNum;			//当前加工到第几个
	int KnifeNum;			//孔刀编号（哪把刀工作）
	float SlotKnifeX_D; 	//槽刀加工尺寸D
	float OrderKnifeX_D;	//阶刀加工尺寸D
	float Depth_Y;
	float Pos_Z;
	
}SlotVariDef;

typedef struct 
{
	LogicParaDef LockSlot;	
	LogicParaDef LockOrder;	
	LogicParaDef LockArcSlot;	
	LogicParaDef LockArcOrder;
		
}SlotFuncDef;

typedef struct SlotConfigPara
{
	SlotFuncDef TaskFunc;
	SlotHardDef ConfigHardPara;
	SlotSoftDef *ConfigSoftPara;
	
	s32 (*Run_LockSlot)(struct SlotConfigPara *t);
	s32 (*Run_LockOrder)(struct SlotConfigPara *t);
	s32 (*Run_LockArcSlot)(struct SlotConfigPara *t);
	s32 (*Run_LockArcOrder)(struct SlotConfigPara *t);
	
	s32 (*Get_LockSlotSta)(struct SlotConfigPara *t);
	s32 (*Get_LockOrderSta)(struct SlotConfigPara *t);
	s32 (*Get_LockArcSlotSta)(struct SlotConfigPara *t);
	s32 (*Get_LockArcOrderSta)(struct SlotConfigPara *t);
	
	void (*LockLoop)(struct SlotConfigPara *);
	
	
}SlotDef;

extern SlotDef NewSlot;

extern void StartLockSlot(void);
extern void StartLockArcSlot(void);
extern void StartLockOrder(void);
extern void StartLockArcOrder(void);

extern s32 GetLockSlot(void);
extern s32 GetLockArcSlot(void);
extern s32 GetLockOrder(void);
extern s32 GetLockArcOrder(void);
extern void SlotConfig(struct SlotConfigPara *p, SlotSoftDef *ConfigSoftPara,
					u32 Ax_X,           //X轴
					u32 Ax_Y,           //Y轴
					u32 Ax_Z,           //Z轴
									 //
					u32 Q_SlotCyl,		//锁槽气缸
					u32 Q_OrderCyl,		//锁槽气缸
					u32 Q_FreSpd1,		//变频器速度1
					u32 Q_FreSpd2,		//变频器速度2
					u32 Q_FreSpd3,		//变频器速度3
					u32 Q_FreSpd4,		//变频器速度4
					u32 Q_SlotSW,		//锁槽刀接触器
									//
					u32 I_XOrg,         //X轴原点
					u32 I_YOrg,	        //Y轴原点
					u32 I_ZOrg,         //Z轴原点
					u32 I_SlotCylOrg,   //锁槽气缸原点
					u32 I_OrderCylOrg   //锁阶气缸原点
               );
#endif 

