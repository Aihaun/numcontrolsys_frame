#include "SlotShape.h" 
#include "Logic.h"

extern struct SlotConfigPara SlC;
SlotDef NewSlot;
/**
* @author��nyh 
* @Date�� 20200206
* @Description:	����
*/
static void LockSlot(struct SlotConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author��nyh 
* @Date�� 20200206
* @Description:	����
*/
static void LockOrder(struct SlotConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author��nyh 
* @Date�� 20200206
* @Description:	Բ������
*/
static void LockArcSlot(struct SlotConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author��nyh 
* @Date�� 20200206
* @Description:	Բ������
*/
static void LockArcOrder(struct SlotConfigPara *p, BasicParaDef BasicPara)
{
}


/**
* @author��nyh 
* @Date�� 20200206
* @Description:	��������
*/
s32 Run_LockSlot(struct SlotConfigPara *p)
{
	return 1;
}

/**
* @author��nyh 
* @Date�� 20200206
* @Description:	��������
*/
s32 Run_LockOrder(struct SlotConfigPara *p)
{
	return 1;
}
/**
* @author��nyh 
* @Date�� 20200206
* @Description:	����Բ������
*/
s32 Run_LockArcSlot(struct SlotConfigPara *p)
{
	return 1;
}
/**
* @author��nyh 
* @Date�� 20200206
* @Description:	����Բ������
*/
s32 Run_LockArcOrder(struct SlotConfigPara *p)
{
	return 1;
}

/**
* @author��nyh 
* @Date�� 20200206
* @Description:	��ȡ����״̬
*/
s32 Get_LockSlotSta(struct SlotConfigPara *p)
{
	return 1;
}

/**
* @author��nyh 
* @Date�� 20200206
* @Description:	��ȡ����״̬
*/
s32 Get_LockOrderSta(struct SlotConfigPara *p)
{
	return 1;
}
/**
* @author��nyh 
* @Date�� 20200206
* @Description:	��ȡԲ������״̬
*/
s32 Get_LockArcSlotSta(struct SlotConfigPara *p)
{
	return 1;
}
/**
* @author��nyh 
* @Date�� 20200206
* @Description:	��ȡԲ������״̬
*/
s32 Get_LockArcOrderSta(struct SlotConfigPara *p)
{
	return 1;
}
/**
* @author��nyh 
* @Date�� 20200206
* @Description:	���۶���������ѯ
*/
void LockUserLoop (struct SlotConfigPara *p, BasicParaDef BasicPara)
{
	LockSlot(p, BasicPara);
	LockOrder(p, BasicPara);
    LockArcSlot(p, BasicPara);
    LockArcOrder(p, BasicPara);
}
/**
* @author��nyh 
* @Date�� 20200206
* @Description:	���۶���������ѯ
*/
void LockLoop (struct SlotConfigPara *p)
{	
	LockUserLoop(p, GUS.BasicPara);
//	LockOrder(p, BasicPara);
//    LockArcSlot(p, BasicPara);
//    LockArcOrder(p, BasicPara);
}

void StartLockSlot()
{
	SlC.Run_LockSlot(&SlC);
}	
void StartLockArcSlot()
{
	SlC.Run_LockArcSlot(&SlC);
}	
void StartLockOrder()
{
	SlC.Run_LockOrder(&SlC);
}	
void StartLockArcOrder()
{
	SlC.Run_LockArcOrder(&SlC);
}


s32 GetLockSlot()
{
	if(SlC.Get_LockSlotSta(&SlC) == 0)
	{
		return 0;
	}
	return -1;
}	
s32 GetLockArcSlot()
{
	if(SlC.Get_LockArcSlotSta(&SlC) == 0)
	{
		return 0;
	}
	return -1;
}	
s32 GetLockOrder()
{
	if(SlC.Get_LockOrderSta(&SlC) == 0)
	{
		return 0;
	}
	return -1;
}	
s32 GetLockArcOrder()
{
	if(SlC.Get_LockArcOrderSta(&SlC) == 0)
	{
		return 0;
	}
	return -1;
}

/**
* @author��nyh 
* @Date�� 20200206
* @Description:	������������
*/
void SlotConfig(struct SlotConfigPara *p, SlotSoftDef *ConfigSoftPara, 
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
					u32 I_OrderCylOrg  //��������ԭ��
               )
{
	p->ConfigSoftPara = ConfigSoftPara;
	p->Run_LockSlot = Run_LockSlot;  
	p->Run_LockOrder = Run_LockOrder;
	p->Run_LockArcSlot = Run_LockArcSlot;
	p->Run_LockArcSlot = Run_LockArcSlot;
	
	p->ConfigHardPara.Ax_X = Ax_X;
	p->ConfigHardPara.Ax_Y = Ax_Y;
	p->ConfigHardPara.Ax_Z = Ax_Z;
	
	p->ConfigHardPara.Q_SlotCyl = Q_SlotCyl;
	p->ConfigHardPara.Q_OrderCyl = Q_OrderCyl;
	p->ConfigHardPara.Q_FreSpd1 = Q_FreSpd1;
	p->ConfigHardPara.Q_FreSpd2 = Q_FreSpd2;
	p->ConfigHardPara.Q_FreSpd3 = Q_FreSpd3;
	p->ConfigHardPara.Q_FreSpd4 = Q_FreSpd4;
	p->ConfigHardPara.Q_SlotSW = Q_SlotSW;
	
	p->ConfigHardPara.I_XOrg = I_XOrg;
	p->ConfigHardPara.I_YOrg = I_YOrg;
	p->ConfigHardPara.I_ZOrg = I_ZOrg;
	p->ConfigHardPara.I_SlotCylOrg = I_SlotCylOrg;
	p->ConfigHardPara.I_OrderCylOrg = I_OrderCylOrg;
	
}

