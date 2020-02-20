#include "HingeShape.h"
#include "Logic.h"

extern  struct HingeConfigPara HiC;
HingeDef NewHinge;
/**
* @author：nyh 
* @Date： 20200206
* @Description:	圆弧铰链-暗铰链
*/
static void HingeArc(struct HingeConfigPara *p, BasicParaDef BasicPara)
{
	
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	上口方铰
*/
static void HingeUpSide(struct HingeConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	上口异铰
*/
static void HingeUpDiffer(struct HingeConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	下口方铰
*/
static void HingeDownSide(struct HingeConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	下口异铰
*/
static void HingeDownDiffer(struct HingeConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	孔铰链
*/
static void HingeHole(struct HingeConfigPara *p, BasicParaDef BasicPara)
{
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	封闭方铰
*/
static void HingeCloseSide(struct HingeConfigPara *p, BasicParaDef BasicPara)
{
}


/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行暗铰链
*/
s32 Run_HingeArc(struct HingeConfigPara *p)
{

	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行上口方铰
*/
s32 Run_HingeUpSide(struct HingeConfigPara *p)
{

	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行上口异铰
*/
s32 Run_HingeUpDiffer(struct HingeConfigPara *p)
{

	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行下口方铰
*/
s32 Run_HingeDownSide(struct HingeConfigPara *p)
{
	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行下口异铰
*/
s32 Run_HingeDownDiffer(struct HingeConfigPara *p)
{
	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行孔铰链
*/
s32 Run_HingeHole(struct HingeConfigPara *p)
{
	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行封闭方铰
*/
s32 Run_HingeClose(struct HingeConfigPara *p)
{
	return 1;
}

/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行暗铰链
*/
s32 Get_HingeArcSta(struct HingeConfigPara *p)
{

	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行上口方铰
*/
s32 Get_HingeUpSideSta(struct HingeConfigPara *p)
{

	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行上口异铰
*/
s32 Get_HingeUpDifferSta(struct HingeConfigPara *p)
{

	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行下口方铰
*/
s32 Get_HingeDownSideSta(struct HingeConfigPara *p)
{
	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行下口异铰
*/
s32 Get_HingeDownDifferSta(struct HingeConfigPara *p)
{
	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行孔铰链
*/
s32 Get_HingeHoleSta(struct HingeConfigPara *p)
{
	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行封闭方铰
*/
s32 Get_HingeCloseSta(struct HingeConfigPara *p)
{
	return 1;
}

/**
* @author：nyh 
* @Date： 20200206
* @Description:	铰链动作函数轮询
*/
void HingeUserLoop(struct HingeConfigPara *p, BasicParaDef BasicPara)
{
	HingeArc(p, BasicPara);
	HingeUpSide(p, BasicPara);
	HingeUpDiffer(p, BasicPara); 
	HingeDownSide(p, BasicPara);
	HingeDownDiffer(p, BasicPara);
	HingeHole(p, BasicPara);
	HingeCloseSide(p, BasicPara);
	
}

/**
* @author：nyh 
* @Date： 20200206
* @Description:	铰链动作函数轮询
*/
void HingeLoop(struct HingeConfigPara *p)
{
	HingeUserLoop(p, GUS.BasicPara);
//	HingeUpSide(p, BasicPara);
//	HingeUpDiffer(p, BasicPara);
//	HingeDownSide(p, BasicPara);
//	HingeDownDiffer(p, BasicPara);
//	HingeHole(p, BasicPara);
//	HingeCloseSide(p, BasicPara);
	
}



void StartHingeUpSide()
{
	HiC.Run_HingeUpSide(&HiC);
}	
void StartHingeUpDiffer()
{
	HiC.Run_HingeUpDiffer(&HiC);
}	
void StartHingeDownSide()
{
	HiC.Run_HingeDownSide(&HiC);
}	
void StartHingeDownDiffer()
{
	HiC.Run_HingeDownDiffer(&HiC);
}	
void StartHingeHole()
{
	HiC.Run_HingeHole(&HiC);
}	
void StartHingeCloseSide()
{
	HiC.Run_HingeCloseSide(&HiC);
}	
void StartHingeArc()
{
	HiC.Run_HingeArc(&HiC);
}
//****************************************************************//

s32 GetHingeUpSide()
{
	if(HiC.Get_HingeUpSideSta(&HiC) == 0)
	{
		return 0;
	}
	return -1;
}	
s32 GetHingeUpDiffer()
{
	if(HiC.Get_HingeUpDifferSta(&HiC) == 0)
	{
		return 0;
	}
	return -1;
}	
s32 GetHingeDownSide()
{
	if(HiC.Get_HingeDownSideSta(&HiC) == 0)
	{
		return 0;
	}
	return -1;
}	
s32 GetHingeDownDiffer()
{
	if(HiC.Get_HingeDownDifferSta(&HiC) == 0)
	{
		return 0;
	}
	return -1;
}	
s32 GetHingeHole()
{
	if(HiC.Get_HingeHoleSta(&HiC) == 0)
	{
		return 0;
	}
	return -1;
}	
s32 GetHingeCloseSide()
{
	if(HiC.Get_HingeCloseSideSta(&HiC) == 0)
	{
		return 0;
	}
	return -1;
}	
s32 GetHingeArc()
{
	if(HiC.Get_HingeArcSta(&HiC) == 0)
	{
		return 0;
	}
	return -1;
}

/**
* @author：nyh 
* @Date： 20200206
* @Description:	铰链配置
*/
void HingeConfig(struct HingeConfigPara *p, HingeSoftDef *ConfigSoftPara,
				s32 Ax_X, s32 Ax_Y, s32 Ax_W,  
				s32 Q_HingeCyl,		
                s32 Q_FreSpd1,		
                s32 Q_FreSpd2,		
                s32 Q_FreSpd3,		
                s32 Q_FreSpd4,		
                s32 Q_HingeSW,		
               
                s32 I_XOrg,
                s32 I_YOrg,
                s32 I_WOrg,
                s32 I_HingeCylOrg1,
                s32 I_HingeCylOrg2,
                s32 I_HingeCylOrg3,
                s32 I_HingeCylOrg4)
{
	p->ConfigSoftPara = ConfigSoftPara;
	p->ConfigHardPara.Ax_X = Ax_X;
	p->ConfigHardPara.Ax_Y = Ax_Y;
	p->ConfigHardPara.Ax_W = Ax_W;
	 
	p->Run_HingeUpSide = Run_HingeUpSide;
	p->Run_HingeUpDiffer = Run_HingeUpDiffer;
	p->Run_HingeDownSide = Run_HingeDownSide;
	p->Run_HingeDownDiffer = Run_HingeDownDiffer;
	p->Run_HingeArc = Run_HingeArc;
	p->Run_HingeHole = Run_HingeHole;
	p->Run_HingeCloseSide = Run_HingeClose;
	
	p->ConfigHardPara.Q_HingeCyl = Q_HingeCyl;
	p->ConfigHardPara.Q_FreSpd1 = Q_FreSpd1;
	p->ConfigHardPara.Q_FreSpd2 = Q_FreSpd2;
	p->ConfigHardPara.Q_FreSpd3 = Q_FreSpd3;
	p->ConfigHardPara.Q_FreSpd4 = Q_FreSpd4;
	p->ConfigHardPara.Q_HingeSW = Q_HingeSW;
	
	p->ConfigHardPara.I_XOrg = I_XOrg;
	p->ConfigHardPara.I_YOrg = I_YOrg;
	p->ConfigHardPara.I_WOrg = I_WOrg;
	p->ConfigHardPara.I_HingeCylOrg1 = I_HingeCylOrg1;
	p->ConfigHardPara.I_HingeCylOrg2 = I_HingeCylOrg2;
	p->ConfigHardPara.I_HingeCylOrg3 = I_HingeCylOrg3;
	p->ConfigHardPara.I_HingeCylOrg4 = I_HingeCylOrg4;
}

