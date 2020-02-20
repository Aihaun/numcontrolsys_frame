#ifndef _HINGESHAPE_H_
#define _HINGESHAPE_H_

#include "logicdata.h"

typedef struct 
{
	s32 Ax_X;           //X��
	s32 Ax_Y;           //Y��
	s32 Ax_W;           //W��
	                    //
	s32 Q_HingeCyl;		//����������
	s32 Q_FreSpd1;		//��Ƶ���ٶ�1
	s32 Q_FreSpd2;		//��Ƶ���ٶ�2
	s32 Q_FreSpd3;		//��Ƶ���ٶ�3
	s32 Q_FreSpd4;		//��Ƶ���ٶ�4
	s32 Q_HingeSW;		//�׵��Ӵ���
	                    //
	s32 I_XOrg;         //X��ԭ��
	s32 I_YOrg;         //Y��ԭ��
	s32 I_WOrg;         //W��ԭ��
	s32 I_HingeCylOrg1; //����������ԭλ1
	s32 I_HingeCylOrg2; //����������ԭλ2
	s32 I_HingeCylOrg3; //����������ԭλ3
	s32 I_HingeCylOrg4; //����������ԭλ4
}HingeHardDef;

typedef struct 
{
	float workSpd;		//�ӹ��ٶ�		4050
	float knifeSpd;		//�뵶�ٶ�
	float knifeSpdY;	//Y�����ٶ�
	float hingeKD;		//������ֱ��
	float hingeKY;		//������(��)�յ���Y����
	float hingeKCyliTm;	//������(��)�����г�ʱ��
	float holeSpd;		//�׽���ת��
	float aa[3];		//Ԥ�� 
}HingeSoftDef;

typedef struct
{
	int workNum;			//��ǰ�ӹ����ڼ���
	int KnifeNum;			//�׵���ţ��İѵ�������	
	float HingeOrgX;		//�����ӹ�����X 
	
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
