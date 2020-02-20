#include "Holeshape.h"   
#include "logic.h"
extern struct HoleConfigPara HoC;

HoleDef NewHole;

 /**   
* @author：nyh  
* @Date： 20200206
* @Description:	1、2刀具机械距离计算(1刀2刀 共用) 
*/
static void HoleCountSize(struct HoleConfigPara *p, BasicParaDef BasicPara, u32 WorkWhich) 
{	//校刀块Y向宽度
	BM.checkLumpThick = BM.Y.WbroadsideLen - BM.DoorWide - BC.Check.horizonLenY;     
	//1刀开始加工X向距离
	p->HoleVari.Hole1KnifeX_A =BM.slotKLenX - PCW.File[WorkWhich].SizePara[A] + BM.X.holeK1Offset;
	//2刀开始加工X向距离
	p->HoleVari.Hole2KnifeX_A = BM.slotKLenX - PCW.File[WorkWhich].SizePara[A] + BM.X.holeKSpace + BM.X.holeK1Offset;
	//加工尺寸 Y_B =  水平杆伸出点到校刀块Y距离 -                 孔刀1、2距离水平杆伸出点Y + 校刀块厚度 + 尺寸B
	p->HoleVari.HoleKnifeY_B = BC.Check.horizonLenY - BM.Y.holeKLen + BM.checkLumpThick + PCW.File[WorkWhich].SizePara[B];
	//1刀到板面Z向高度			//孔刀1到校刀块Z				//门厚     		//校刀块高度
	p->HoleVari.Hole1KnifeZ = BC.Check.holeK1LenZ - (BM.DoorThick - BC.Check.checkLumpH);
	//2刀到板面Z向高度
	p->HoleVari.Hole2KnifeZ = BC.Check.holeK2LenZ - (BM.DoorThick - BC.Check.checkLumpH);
}	
  
/**   
* @author：nyh  
* @Date： 20200206
* @Description:	刀孔(1刀2刀 共用)
*/
static void KnifeHole(struct HoleConfigPara *p, BasicParaDef BasicPara, u32 WorkWhich)
{
	LogicParaDef *t = &(p->TaskFunc.KnifeHole);
	FUNC_ENTER
	switch(it.step)
	{
		case 1:
			AxRun(Z_MOTOR, ABSMODE, BM.MoveSpd , p->HoleVari.Hole1KnifeZ - Safe_Z);
			it.mode = 1;
			if(WorkWhich > 0)
			{//上一次不是使用1刀
				if(BasicPara.WorkFile.File[WorkWhich-1].mode != 7 && BasicPara.WorkFile.File[WorkWhich-1].mode != 8 && BasicPara.WorkFile.File[WorkWhich-1].mode != 9 && BasicPara.WorkFile.File[WorkWhich-1].mode != 18 )
				{
					it.mode = 1;
				}
				else
				{//上一次使用1刀
					it.mode = 0;
				}
			}
			it.step = 2;
			break;
		
		case 2:
			break;
		
		case 3:
			break;
		
		case 4:
			break;
		
		case 5:
			break;
		
		case 6:
			break;
		
		case 7:
			break;
		
		case 8:
			break;
		
		case 9:
			break;
		
		case 10:
			break;
	}
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	折线(1刀2刀 共用)
*/
static void KnifeLine(struct HoleConfigPara *p, u32 WorkWhich)
{
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	铣圆(1刀2刀 共用)
*/
static void KnifeCirc(struct HoleConfigPara *p, u32 WorkWhich)
{
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	横向圆弧(1刀2刀 共用)
*/
static void KnifeArc_Level(struct HoleConfigPara *p, u32 WorkWhich)
{
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	竖向圆弧(1刀2刀 共用)
*/
static void KnifeArc_Stand(struct HoleConfigPara *p, u32 WorkWhich)
{
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行刀孔(1刀2刀 共用)
*/
s32 Run_KnifeHole(struct HoleConfigPara *p, s32 WhichKnife)
{
	if(p->TaskFunc.KnifeHole.execute == 0)
	{		
		p->HoleVari.KnifeNum = WhichKnife;
		p->TaskFunc.KnifeHole.execute = 1;
		return 1;
	}
	return -1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行折线(1刀2刀 共用)
*/
s32 Run_KnifeLine(struct HoleConfigPara *p, s32 WhichKnife)
{

	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行铣圆(1刀2刀 共用)
*/
s32 Run_KnifeCirc(struct HoleConfigPara *p, s32 WhichKnife)
{

	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行横向圆弧(1刀2刀共用)
*/
s32 Run_KnifeArc_Level(struct HoleConfigPara *p, s32 WhichKnife)
{
	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	运行竖向圆弧(1刀2刀 共用)
*/
s32 Run_KnifeArc_Stand(struct HoleConfigPara *p, s32 WhichKnife)
{
	return 1;
}

/**
* @author：nyh 
* @Date： 20200206
* @Description:	获取刀孔状态(1刀2刀 共用)
*/
s32 Get_KnifeHoleSta(struct HoleConfigPara *p, s32 WhichKnife)
{
	if(p->TaskFunc.KnifeHole.execute == 0)
	{
		return 0;
	}
	return -1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	获取折线状态(1刀2刀 共用)
*/
s32 Get_KnifeLineSta(struct HoleConfigPara *p, s32 WhichKnife)
{

	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	获取铣圆状态(1刀2刀 共用)
*/
s32 Get_KnifeCircSta(struct HoleConfigPara *p, s32 WhichKnife)
{

	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	获取横向圆弧状态(1刀2刀 共用)
*/
s32 Get_KnifeArc_LevelSta(struct HoleConfigPara *p, s32 WhichKnife)
{
	return 1;
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	获取竖向圆弧状态(1刀2刀 共用)
*/
s32 Get_KnifeArc_StandSta(struct HoleConfigPara *p, s32 WhichKnife)
{
	return 1;
}

void HoleUserLoop(struct HoleConfigPara *p, BasicParaDef BasicPara, u32 WorkWhich)
{
	HoleCountSize(p, BasicPara, WorkWhich);
	KnifeHole(p, BasicPara, WorkWhich);
	KnifeLine(p,WorkWhich);
	KnifeCirc(p, WorkWhich);
	KnifeArc_Level(p, WorkWhich);
	KnifeArc_Stand(p, WorkWhich);
}
/**
* @author：nyh 
* @Date： 20200206
* @Description:	孔动作函数轮询
*/
void HoleLoop(struct HoleConfigPara *p, u32 WorkWhich)
{
	HoleUserLoop(p, GUS.BasicPara, WorkWhich);
//	HoleCountSize(p, BasicPara, WorkWhich);
//	KnifeHole(p, BasicPara, WorkWhich);
//	KnifeLine(p,WorkWhich);
//	KnifeCirc(p, WorkWhich);
//	KnifeArc_Level(p, WorkWhich);
//	KnifeArc_Stand(p, WorkWhich);
}

//***********************开始函数执行*******************************//
void StartKnifeHole_one()
{
	HoC.Run_KnifeHole(&HoC, 0);  
}
void StartKnifeLine_one()
{
	HoC.Run_KnifeLine(&HoC, 0);  
}
void StartKnifeCirc_one()
{
	HoC.Run_KnifeCirc(&HoC, 0);  
}
void StartKnifeArc_Level_one()
{
	HoC.Run_KnifeArc_Level(&HoC, 0);  
}
void StartKnifeArc_Stand_one()
{
	HoC.Run_KnifeArc_Stand(&HoC, 0);  
}

void StartKnifeHole_two()
{
	HoC.Run_KnifeHole(&HoC, 1);  
}
void StartKnifeLine_two()
{
	HoC.Run_KnifeLine(&HoC, 1);  
}
void StartKnifeCirc_two()
{
	HoC.Run_KnifeCirc(&HoC, 1);  
}
void StartKnifeArc_Level_two()
{
	HoC.Run_KnifeArc_Level(&HoC, 1);  
}
void StartKnifeArc_Stand_two()
{
	HoC.Run_KnifeArc_Stand(&HoC, 1);  
}
//*****************************************************************//

//***********************获取函数状态*******************************//
s32 GetKnifeHole_one()
{
	if(HoC.Get_KnifeHoleSta(&HoC, 0) == 0)
	{
		return 0;
	}
	return -1;	
}
s32 GetKnifeLine_one()
{
	if(HoC.Get_KnifeLineSta(&HoC, 0) == 0)
	{
		return 0;
	}
	return -1;	
}
s32 GetKnifeCirc_one()
{
	if(HoC.Get_KnifeCircSta(&HoC, 0) == 0)
	{
		return 0;
	}
	return -1;	
}
s32 GetKnifeArc_Level_one()
{
	if(HoC.Get_KnifeArc_LevelSta(&HoC, 0) == 0)
	{
		return 0;
	}
	return -1;		
}
s32 GetKnifeArc_Stand_one()
{
	if(HoC.Get_KnifeArc_StandSta(&HoC, 0) == 0)
	{
		return 0;
	}
	return -1;		
}

s32 GetKnifeHole_two()
{
	if(HoC.Get_KnifeHoleSta(&HoC, 0) == 0)
	{
		return 0;
	}
	return -1;		
}
s32 GetKnifeLine_two()
{
	if(HoC.Get_KnifeLineSta(&HoC, 1) == 0)
	{
		return 0;
	}
	return -1;		
}
s32 GetKnifeCirc_two()
{
	if(HoC.Get_KnifeCircSta(&HoC, 1) == 0)
	{
		return 0;
	}
	return -1;		
}
s32 GetKnifeArc_Level_two()
{
	if(HoC.Get_KnifeArc_LevelSta(&HoC, 1) == 0)
	{
		return 0;
	}
	return -1;		
}
s32 GetKnifeArc_Stand_two()
{
	if(HoC.Get_KnifeArc_StandSta(&HoC, 1) == 0)
	{
		return 0;
	}
	return -1;		
}
//*****************************************************************//

/**
* @author：nyh 
* @Date： 20200206
* @Description:	孔类型配置
*/
void HoleConfig(struct HoleConfigPara *p, HoleSoftDef *ConfigSoftPara,
					s32 Ax_X, s32 Ax_Y, s32 Ax_Z,  
					s32 Q_HoleCyl, 
					s32 Q_FreSpd1,		
					s32 Q_FreSpd2,		
					s32 Q_FreSpd3,		
					s32 Q_FreSpd4,		
					s32 Q_HoleSW,		
               
					s32 I_XOrg,
					s32 I_YOrg,
					s32 I_ZOrg,
					s32 I_HoleCylOrg
               )
{
	p->ConfigSoftPara = ConfigSoftPara;
	p->Run_KnifeArc_Level = Run_KnifeArc_Level;  
	p->Run_KnifeHole = Run_KnifeHole;
	p->Run_KnifeCirc = Run_KnifeCirc;
	p->Run_KnifeLine = Run_KnifeLine;
		
	p->ConfigHardPara.Ax_X = Ax_X;
	p->ConfigHardPara.Ax_Y = Ax_Y;
	p->ConfigHardPara.Ax_Z = Ax_Z;
	
	p->ConfigHardPara.Q_HoleCyl = Q_HoleCyl;
	p->ConfigHardPara.Q_FreSpd1 = Q_FreSpd1;
	p->ConfigHardPara.Q_FreSpd2 = Q_FreSpd2;
	p->ConfigHardPara.Q_FreSpd3 = Q_FreSpd3;
	p->ConfigHardPara.Q_FreSpd4 = Q_FreSpd4;
	p->ConfigHardPara.Q_HoleSW = Q_HoleSW;
	
	p->ConfigHardPara.I_XOrg = I_XOrg;
	p->ConfigHardPara.I_YOrg = I_YOrg;
	p->ConfigHardPara.I_ZOrg = I_ZOrg;
	p->ConfigHardPara.I_HoleCylOrg = I_HoleCylOrg;
}
