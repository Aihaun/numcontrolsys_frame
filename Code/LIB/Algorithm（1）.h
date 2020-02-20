#ifndef __ALGORITHM_H
#define __ALGORITHM_H
#include "bsplib.h"
typedef struct
{
	s32 x;
	s32 y;
	s32 z;
	s32 w;
	//float rad;
}PointDef;

typedef struct{
	s32 x;
	s32 y;
}mP2Def;

typedef struct
{
	u32 Vinit;
	u32 Tacc;
	u32 Vtar;
}VelocityDef;

extern s32 HZ_MultiAxMotion(void);
//extern s32 HZ_MultiAxSet(u8 Group,u8 AxNum,u8 Ax0,u8 Ax1,u8 Ax2,u8 Ax3);
//����������ٶ�
extern s32 HZ_MultiAxSetVal(u8 Group,VelocityDef Vel);

//Բ���������� Pmid��Բ���м��  Ptar��Բ��ĩ��
extern s32 HZ_MultiAxMoveArc(u8 Group,u8 Num, PointDef Pmid, PointDef Ptar);

//��Բ�������� Pmid��Բ���м��  Ptar: Բ��ĩ�� rot:Բ����
extern s32 HZ_MultiAxMoveCirc(u8 Group,u8 AxNum, PointDef Pmid, PointDef Ptar,u8 rot);

//extern s32 HZ_MultiAxMove(u8 Group,u8 AxNum, PointDef Ptar);
//��ȡ����Ĳ岹״̬��0���У�1����
extern s32 HZ_MultiAxStatus(u8 Group);

//����ֱ�߲岹����:Ax ���ڵ���
extern s32 HZ_MultiAxSet(int Group,int Ax,...);

//�岹�������У�Tar �������Ŀ��
extern s32 HZ_MultiAxMove(u8 Group,int Tar,...);

//�岹���鰴������ȡ����
extern mP2Def HZ_GetCircRatioPoint(u8 Group,float ratio);

//�岹�����ȡ�м�� Ĭ��rotд0 �����Ҫ�ı䷽��rotд1
extern mP2Def HZ_GetCircMiddlePoint(u8 Group,PointDef Pinit,PointDef Ptar,u8 rot);

//����Բ����Ϣ
extern s32 HZ_MultiAxCalcArc(u8 Group,u8 Num, PointDef Pinit,PointDef Pmid, PointDef Ptar);

//������Բ��Ϣ
extern s32 HZ_MultiAxCalcCirc(u8 Group,u8 AxNum,PointDef Pinit, PointDef Pmid, PointDef Ptar,u8 rot);

//��ȡԲ�뾶
extern float HZ_GetCircR(u8 Group);

//��ȡԲ��X����
extern float HZ_GetCircRx(u8 Group);
	
//��ȡԲ��Y����	
extern float HZ_GetCircRy(u8 Group);

//��ȡԲ����
extern float HZ_GetCircArc(u8 Group);

//��ȡԲ����ת����
extern float HZ_GetCircRot(u8 Group);

#endif
