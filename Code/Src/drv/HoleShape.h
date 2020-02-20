#ifndef _HOLESHAPE_H_
#define _HOLESHAPE_H_

#include "logicdata.h"


typedef struct 
{
	s32 Ax_X;			//X轴
	s32 Ax_Y;           //Y轴
	s32 Ax_Z;           //Z轴
	
	s32 Q_HoleCyl;		//孔刀气缸
	s32 Q_FreSpd1;		//变频器速度1
	s32 Q_FreSpd2;		//变频器速度2
	s32 Q_FreSpd3;		//变频器速度3
	s32 Q_FreSpd4;		//变频器速度4
	s32 Q_HoleSW;		//孔刀接触器
	
	s32 I_XOrg;			//X轴原点
	s32 I_YOrg;         //Y轴原点
	s32 I_ZOrg;         //Z轴原点
	s32 I_HoleCylOrg;   //孔刀气缸原位
	
}HoleHardDef;

typedef struct 
{
	float holeSpd;		//打孔进刀速度	4080
	float riftSpd;		//破孔速度
	float lineSpd;		//铣折线插补速度
	float circSpd;		//铣圆孔插补速度
	float knife1Spd;	//1号刀转速
	float knife2Spd;	//2号刀转速
	float knife1KD;		//1号刀直径
	float knife2KD;		//2号刀直径
	float aa[2];		//预留 
}HoleSoftDef;

typedef struct
{
	s32 workNum;			//当前加工到第几个
	s32 KnifeNum;			//孔刀编号（哪把刀工作）
	float Hole1KnifeX_A;	//孔刀1到加工位置X向距离
	float Hole2KnifeX_A;	//孔刀2到加工位置X向距离
	float HoleKnifeY_B;		//孔刀到加工位Y向距离
	float Hole1KnifeZ;		//孔1刀到板面Z高度
	float Hole2KnifeZ;		//孔2刀到板面Z高度
	struct//函数内统一变量
	{
		float HoleKnifeZ;		//孔刀到板面Z高度
		float HoleKnifeX_A ;    //孔刀到加工位置X向距离
		float HoleKnifeOffset;  //孔刀X向偏移槽刀
		float knifeKD;          //孔刀直径
		float Depth_Z;          //孔刀Z深度
		float PerDepth_Z;       //孔刀Z每次进刀量
	}Hole[2];//两把孔刀
}HoleVariDef;

typedef struct 
{
	LogicParaDef KnifeHole;
	LogicParaDef KnifeCirc;	
	LogicParaDef KnifeLine;	
	LogicParaDef KnifeArc_Stand;
	LogicParaDef KnifeArc_Level;
	LogicParaDef HoleCountSize;
}HoleFuncDef;

typedef struct HoleConfigPara
{
	HoleFuncDef TaskFunc;
	HoleHardDef ConfigHardPara;
	HoleSoftDef *ConfigSoftPara;
	HoleVariDef HoleVari;
	
	s32 (*Run_KnifeHole)(struct HoleConfigPara *t, s32 WhichKnife);
	s32 (*Run_KnifeLine)(struct HoleConfigPara *t, s32 WhichKnife);
	s32 (*Run_KnifeCirc)(struct HoleConfigPara *t, s32 WhichKnife);
	s32 (*Run_KnifeArc_Level)(struct HoleConfigPara *t, s32 WhichKnife);
	s32 (*Run_KnifeArc_Stand)(struct HoleConfigPara *t, s32 WhichKnife);
	
	s32 (*Get_KnifeHoleSta)(struct HoleConfigPara *t, s32 WhichKnife);
	s32 (*Get_KnifeLineSta)(struct HoleConfigPara *t, s32 WhichKnife);
	s32 (*Get_KnifeCircSta)(struct HoleConfigPara *t, s32 WhichKnife);
	s32 (*Get_KnifeArc_LevelSta)(struct HoleConfigPara *t, s32 WhichKnife);
	s32 (*Get_KnifeArc_StandSta)(struct HoleConfigPara *t, s32 WhichKnife);
	
	void (*HoleLoop)(struct HoleConfigPara *t, u32 WorkWhich);
	
	
}HoleDef;

 
extern HoleDef NewHole;

extern void StartKnifeHole_one(void);
extern void StartKnifeLine_one(void);
extern void StartKnifeCirc_one(void);
extern void StartKnifeArc_Level_one(void);
extern void StartKnifeArc_Stand_one(void);

extern void StartKnifeHole_two(void);
extern void StartKnifeLine_two(void);
extern void StartKnifeCirc_two(void);
extern void StartKnifeArc_Level_two(void);
extern void StartKnifeArc_Stand_two(void);

extern s32 GetKnifeHole_one(void);
extern s32 GetKnifeLine_one(void);
extern s32 GetKnifeCirc_one(void);
extern s32 GetKnifeArc_Level_one(void);
extern s32 GetKnifeArc_Stand_one(void);
       
extern s32 GetKnifeHole_two(void);
extern s32 GetKnifeLine_two(void);
extern s32 GetKnifeCirc_two(void);
extern s32 GetKnifeArc_Level_two(void);
extern s32 GetKnifeArc_Stand_two(void);

extern void HoleConfig(struct HoleConfigPara *p, HoleSoftDef *ConfigSoftPara,
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
               );
	

#endif 


