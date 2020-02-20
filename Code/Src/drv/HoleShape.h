#ifndef _HOLESHAPE_H_
#define _HOLESHAPE_H_

#include "logicdata.h"


typedef struct 
{
	s32 Ax_X;			//X��
	s32 Ax_Y;           //Y��
	s32 Ax_Z;           //Z��
	
	s32 Q_HoleCyl;		//�׵�����
	s32 Q_FreSpd1;		//��Ƶ���ٶ�1
	s32 Q_FreSpd2;		//��Ƶ���ٶ�2
	s32 Q_FreSpd3;		//��Ƶ���ٶ�3
	s32 Q_FreSpd4;		//��Ƶ���ٶ�4
	s32 Q_HoleSW;		//�׵��Ӵ���
	
	s32 I_XOrg;			//X��ԭ��
	s32 I_YOrg;         //Y��ԭ��
	s32 I_ZOrg;         //Z��ԭ��
	s32 I_HoleCylOrg;   //�׵�����ԭλ
	
}HoleHardDef;

typedef struct 
{
	float holeSpd;		//��׽����ٶ�	4080
	float riftSpd;		//�ƿ��ٶ�
	float lineSpd;		//ϳ���߲岹�ٶ�
	float circSpd;		//ϳԲ�ײ岹�ٶ�
	float knife1Spd;	//1�ŵ�ת��
	float knife2Spd;	//2�ŵ�ת��
	float knife1KD;		//1�ŵ�ֱ��
	float knife2KD;		//2�ŵ�ֱ��
	float aa[2];		//Ԥ�� 
}HoleSoftDef;

typedef struct
{
	s32 workNum;			//��ǰ�ӹ����ڼ���
	s32 KnifeNum;			//�׵���ţ��İѵ�������
	float Hole1KnifeX_A;	//�׵�1���ӹ�λ��X�����
	float Hole2KnifeX_A;	//�׵�2���ӹ�λ��X�����
	float HoleKnifeY_B;		//�׵����ӹ�λY�����
	float Hole1KnifeZ;		//��1��������Z�߶�
	float Hole2KnifeZ;		//��2��������Z�߶�
	struct//������ͳһ����
	{
		float HoleKnifeZ;		//�׵�������Z�߶�
		float HoleKnifeX_A ;    //�׵����ӹ�λ��X�����
		float HoleKnifeOffset;  //�׵�X��ƫ�Ʋ۵�
		float knifeKD;          //�׵�ֱ��
		float Depth_Z;          //�׵�Z���
		float PerDepth_Z;       //�׵�Zÿ�ν�����
	}Hole[2];//���ѿ׵�
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


