#ifndef _HINGESHAPE_H_
#define _HINGESHAPE_H_

#include "logicdata.h"

typedef struct 
{
	s32 Ax_X;           //X轴
	s32 Ax_Y;           //Y轴
	s32 Ax_W;           //W轴
	                    //
	s32 Q_HingeCyl;		//铰链刀气缸
	s32 Q_FreSpd1;		//变频器速度1
	s32 Q_FreSpd2;		//变频器速度2
	s32 Q_FreSpd3;		//变频器速度3
	s32 Q_FreSpd4;		//变频器速度4
	s32 Q_HingeSW;		//孔刀接触器
	                    //
	s32 I_XOrg;         //X轴原点
	s32 I_YOrg;         //Y轴原点
	s32 I_WOrg;         //W轴原点
	s32 I_HingeCylOrg1; //铰链刀气缸原位1
	s32 I_HingeCylOrg2; //铰链刀气缸原位2
	s32 I_HingeCylOrg3; //铰链刀气缸原位3
	s32 I_HingeCylOrg4; //铰链刀气缸原位4
}HingeHardDef;

typedef struct 
{
	float workSpd;		//加工速度		4050
	float knifeSpd;		//入刀速度
	float knifeSpdY;	//Y进刀速度
	float hingeKD;		//铰链刀直径
	float hingeKY;		//铰链刀(进)刚到边Y坐标
	float hingeKCyliTm;	//铰链刀(进)气缸行程时间
	float holeSpd;		//孔铰链转速
	float aa[3];		//预留 
}HingeSoftDef;

typedef struct
{
	int workNum;			//当前加工到第几个
	int KnifeNum;			//孔刀编号（哪把刀工作）	
	float HingeOrgX;		//铰链加工中心X 
	
}HingeVariDef;

typedef struct 
{
	LogicParaDef HingeArc;
	LogicParaDef HingeUpSide;
	LogicParaDef HingeUpDiffer;
	LogicParaDef HingeDownSide;
	LogicParaDef HingeDownDiffer;
	LogicParaDef HingeHole;
	LogicParaDef HingeCloseSide;
	
}HingeFuncDef;

typedef struct HingeConfigPara
{
	HingeFuncDef TaskFunc;
	HingeHardDef ConfigHardPara;
	HingeSoftDef *ConfigSoftPara;
	
	s32 (*Run_HingeArc)(struct HingeConfigPara *t);
	s32 (*Run_HingeUpSide)(struct HingeConfigPara *t);
	s32 (*Run_HingeUpDiffer)(struct HingeConfigPara *t);
	s32 (*Run_HingeDownSide)(struct HingeConfigPara *t);
	s32 (*Run_HingeDownDiffer)(struct HingeConfigPara *t);
	s32 (*Run_HingeHole)(struct HingeConfigPara *t);
	s32 (*Run_HingeCloseSide)(struct HingeConfigPara *t);
	
	s32 (*Get_HingeArcSta)(struct HingeConfigPara *t);
	s32 (*Get_HingeUpSideSta)(struct HingeConfigPara *t);
	s32 (*Get_HingeUpDifferSta)(struct HingeConfigPara *t);
	s32 (*Get_HingeDownSideSta)(struct HingeConfigPara *t);
	s32 (*Get_HingeDownDifferSta)(struct HingeConfigPara *t);
	s32 (*Get_HingeHoleSta)(struct HingeConfigPara *t);
	s32 (*Get_HingeCloseSideSta)(struct HingeConfigPara *t);
	
	void (*HingeLoop)(struct HingeConfigPara *t);
	
	
}HingeDef;

extern HingeDef NewHinge;


extern void StartHingeUpSide(void);	
extern void StartHingeUpDiffer(void);	
extern void StartHingeDownSide(void);	
extern void StartHingeDownDiffer(void)	;
extern void StartHingeHole(void)	;
extern void StartHingeCloseSide(void);	
extern void StartHingeArc(void);

extern s32 GetHingeUpSide(void);	
extern s32 GetHingeUpDiffer(void);	
extern s32 GetHingeDownSide(void);	
extern s32 GetHingeDownDiffer(void)	;
extern s32 GetHingeHole(void)	;
extern s32 GetHingeCloseSide(void);	
extern s32 GetHingeArc(void);

extern void HingeConfig(struct HingeConfigPara *p, HingeSoftDef *ConfigSoftPara,
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
                s32 I_HingeCylOrg4);

#endif 
