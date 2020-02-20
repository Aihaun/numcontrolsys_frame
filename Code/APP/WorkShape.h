#ifndef _WORKSHAPE_H_
#define _WORKSHAPE_H_

#include "logicdata.h"
#include "tool.h"
//#include "interlayer_config.h"
#include "DataDefine.h"
#include "Algorithm.h" 
#include "USERTOOL.H" 

#define TimerRstA(a)		 a.tm = SysTim_GetUser()		  //0.1 ms
#define TimerCntA(a)		((SysTim_GetUser()-a.tm)/10) 	//��ʱת��ms

#define	it	(*t)
#define	FUNC_ENTERA \
	if(it.execute == 1 && it.step == 0)\
	{\
		it.step = 1;\
		it.done = 0;\
		it.count = 0;\
	}
#define PARAINIT(a)  memset(&a,0,sizeof(a));

//�����Ӵ���				 
extern u32 Q_Contactor[5];
//��Ƶ���ٶ�			
extern u32 Q_FreSpd[4];
//�׵�����
extern u32 Q_HoleCyl[2];
//�׵�����ԭ��
extern u32 I_HoleKOrg[2]; 
//����
extern u8 AxNum[3];

typedef enum	//�ᶨ��
{
	X=0, 
	Y=1, 
	Z=2,

}motornum;

typedef struct
{
	int Ax_X;
	int Ax_Y;
	int Ax_Z;
}Ax_IO;

typedef struct 
{
	LogicParaDef Para;   //�����ڲ�ʹ�ñ���
	BasicParaDef Basic;  //��������
	WorkFileDef Size;    //�ߴ����
	int State;			//״̬
	int Over;			//������������
	int KnifeNum;		//�׵����  0:1��  1:2��
}ShapeDef;


 
typedef struct
{
	u32 workNum;			//��ǰ�ӹ����ڼ���	
	float Hole1KnifeX_A;	//�׵�1���ӹ�λ��X�����
	float Hole2KnifeX_A;	//�׵�2���ӹ�λ��X�����
	float HoleKnifeY_B;		//�׵����ӹ�λY�����
	float Hole1KnifeZ;		//��1��������Z�߶�
	float Hole2KnifeZ;		//��2��������Z�߶�
	
	float SlotKnifeX_D; 	//�۵��ӹ��ߴ�D
	float OrderKnifeX_D;	//�׵��ӹ��ߴ�D
	float HingeOrgX;		//�����ӹ�����X
}VariData;

typedef struct 
{
	LogicParaDef ChangerSpeed_ONTask;
	LogicParaDef ChangerSpeed_OFFTask;
} ParaTask;

extern ParaTask TK;

//Z��Y��ȫ����
#define  Safe_Z  30
#define  Safe_Y  30

//#define  Q_Set    OutPut_SetSta
//#define  ExQ_Set  HZ_ExOutPutSet
//#define  Q_Get    OutPut_GetSta
//#define  ExQ_Get  HZ_ExOutPutGet

//#define I_Get 	InPut_GetSta
//#define ExI_Get HZ_ExInPutGet

//#define En_Get  EN_GetSta

//#define AxGetsta  HZ_AxGetStatus

//*********************************************************************************************************************/
//ʹ��˵����                                                                                                              
//�ú�����ִ��ϳԲ����������Բ����Բ����һ���ϴ����Z��ȵ����½���Ȼ�����Բ����Բ������ѭ�����У�ֱ���������õĳߴ��С��       
//ʹ�õ�3���ᣨXYZ���������ж��壬��������ú�����Ӧ���ḳ����ţ�AxNum[0]ΪX�ᣬAxNum[1]ΪY�ᣬAxNum[2]ΪZ�᣻                
//IO����                                                                                                                 
//��Ҫ�ڱ���������BasicParaDef ����������WorkParaDef ����������WorkFileDef �ߴ������                                       
//                                                                                                                       
//                                                                                                                       
//*********************************************************************************************************************/
extern void KnifeHoleCirc(ShapeDef *t, int KnifeNum);
extern void KnifeHole(ShapeDef *t, int KnifeNum);
extern void KnifeLine(ShapeDef *t, int KnifeNum);
extern void KnifeLevelArc(ShapeDef *t, int KnifeNum);
extern void KnifeStandArc(ShapeDef *t, int KnifeNum);
//ϳԲ��ʼ
extern void MillCirc1_start(ShapeDef *t);
//ϳԲ��� return 0, δ��� return 1  ������-1
extern s32 MillCirc1_End(ShapeDef *t);//return 0 
//ϳԲ��ֹ
extern void MillCirc1_Over(ShapeDef *t);
#endif
