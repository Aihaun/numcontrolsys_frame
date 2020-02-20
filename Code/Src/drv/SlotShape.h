#ifndef _SLOTSHAPE_H_
#define _SLOTSHAPE_H_

#include "logicdata.h"

typedef struct 
{
	u32 Ax_X;           //X��
	u32 Ax_Y;           //Y��
	u32 Ax_Z;           //Z��
	                 //
	u32 Q_SlotCyl;		//��������
	u32 Q_OrderCyl;		//��������
	u32 Q_FreSpd1;		//��Ƶ���ٶ�1
	u32 Q_FreSpd2;		//��Ƶ���ٶ�2
	u32 Q_FreSpd3;		//��Ƶ���ٶ�3
	u32 Q_FreSpd4;		//��Ƶ���ٶ�4
	u32 Q_SlotSW;		//���۵��Ӵ���
	                //
	u32 I_XOrg;         //X��ԭ��
	u32 I_YOrg;	        //Y��ԭ��
	u32 I_ZOrg;         //Z��ԭ��
	u32 I_SlotCylOrg;   //��������ԭ��
	u32 I_OrderCylOrg;  //��������ԭ��
}SlotHardDef;

typedef struct 
{
	float workSpd;		//�ӹ��ٶ�		4064
	float knifeSpdY;	//Y�����ٶ�
	float slotKD;		//���۵�ֱ��
	float stairKD;		//���׵�ֱ��	
	float aa[6];		//Ԥ�� 
}SlotSoftDef;

typedef struct
{
	int workNum;			//��ǰ�ӹ����ڼ���
	int KnifeNum;			//�׵���ţ��İѵ�������
	float SlotKnifeX_D; 	//�۵��ӹ��ߴ�D
	float OrderKnifeX_D;	//�׵��ӹ��ߴ�D
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
					u32 Ax_X,           //X��
					u32 Ax_Y,           //Y��
					u32 Ax_Z,           //Z��
									 //
					u32 Q_SlotCyl,		//��������
					u32 Q_OrderCyl,		//��������
					u32 Q_FreSpd1,		//��Ƶ���ٶ�1
					u32 Q_FreSpd2,		//��Ƶ���ٶ�2
					u32 Q_FreSpd3,		//��Ƶ���ٶ�3
					u32 Q_FreSpd4,		//��Ƶ���ٶ�4
					u32 Q_SlotSW,		//���۵��Ӵ���
									//
					u32 I_XOrg,         //X��ԭ��
					u32 I_YOrg,	        //Y��ԭ��
					u32 I_ZOrg,         //Z��ԭ��
					u32 I_SlotCylOrg,   //��������ԭ��
					u32 I_OrderCylOrg   //��������ԭ��
               );
#endif 

