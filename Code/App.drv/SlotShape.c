#include "SlotShape.h" 
#include "Logic.h"

extern struct SlotConfigPara SlC;
SlotDef NewSlot;
/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	Ëø²Û
*/
static void LockSlot(struct SlotConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	Ëø½×
*/
static void LockOrder(struct SlotConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	Ô²»¡Ëø²Û
*/
static void LockArcSlot(struct SlotConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	Ô²»¡Ëø½×
*/
static void LockArcOrder(struct SlotConfigPara *p, BasicParaDef BasicPara)
{
}


/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	ÔËÐÐËø²Û
*/
s32 Run_LockSlot(struct SlotConfigPara *p)
{
	return 1;
}

/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	ÔËÐÐËø½×
*/
s32 Run_LockOrder(struct SlotConfigPara *p)
{
	return 1;
}
/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	ÔËÐÐÔ²»¡Ëø²Û
*/
s32 Run_LockArcSlot(struct SlotConfigPara *p)
{
	return 1;
}
/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	ÔËÐÐÔ²»¡Ëø½×
*/
s32 Run_LockArcOrder(struct SlotConfigPara *p)
{
	return 1;
}

/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	»ñÈ¡Ëø²Û×´Ì¬
*/
s32 Get_LockSlotSta(struct SlotConfigPara *p)
{
	return 1;
}

/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	»ñÈ¡Ëø½××´Ì¬
*/
s32 Get_LockOrderSta(struct SlotConfigPara *p)
{
	return 1;
}
/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	»ñÈ¡Ô²»¡Ëø²Û×´Ì¬
*/
s32 Get_LockArcSlotSta(struct SlotConfigPara *p)
{
	return 1;
}
/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	»ñÈ¡Ô²»¡Ëø½××´Ì¬
*/
s32 Get_LockArcOrderSta(struct SlotConfigPara *p)
{
	return 1;
}
/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	Ëø²Û¶¯×÷º¯ÊýÂÖÑ¯
*/
void LockUserLoop (struct SlotConfigPara *p, BasicParaDef BasicPara)
{
	LockSlot(p, BasicPara);
	LockOrder(p, BasicPara);
    LockArcSlot(p, BasicPara);
    LockArcOrder(p, BasicPara);
}
/**
* @author£ºnyh 
* @Date£º 20200206
* @Description:	Ëø²Û¶¯×÷º¯ÊýÂÖÑ¯
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
* @author£ºnyh 
* @Date£º 20200206
* @Description:	Ëø²ÛÀàÐÍÅäÖÃ
*/
void SlotConfig(struct SlotConfigPara *p, SlotSoftDef *ConfigSoftPara, 
					u32 Ax_X,           //XÖá
					u32 Ax_Y,           //YÖá
					u32 Ax_Z,           //ZÖá
									 //
					u32 Q_SlotCyl,		//Ëø²ÛÆø¸×
					u32 Q_OrderCyl,		//Ëø²ÛÆø¸×
					u32 Q_FreSpd1,		//±äÆµÆ÷ËÙ¶È1
					u32 Q_FreSpd2,		//±äÆµÆ÷ËÙ¶È2
					u32 Q_FreSpd3,		//±äÆµÆ÷ËÙ¶È3
					u32 Q_FreSpd4,		//±äÆµÆ÷ËÙ¶È4
					u32 Q_SlotSW,		//Ëø²Ûµ¶½Ó´¥Æ÷
									//
					u32 I_XOrg,         //XÖáÔ­µã
					u32 I_YOrg,	        //YÖáÔ­µã
					u32 I_ZOrg,         //ZÖáÔ­µã
					u32 I_SlotCylOrg,   //Ëø²ÛÆø¸×Ô­µã
					u32 I_OrderCylOrg  //Ëø½×Æø¸×Ô­µã
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

