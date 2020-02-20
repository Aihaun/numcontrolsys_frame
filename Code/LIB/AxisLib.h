#ifndef __AXISLIB_H
#define __AXISLIB_H
#include "bsplib.h"

#define AXIS_NUM PULS_NUM


#define AX_SPD_MAX	(200*1000)
#define AX_SPD_MIN	(20)
typedef enum 
{
	AXSTA_READY = 0,	//����״̬
	AXSTA_STOP,			//ֹͣ״̬
	AXSTA_STOPDEC,		//ֹͣ״̬(����ͣ)
	AXSTA_DISCRETE,		//��ͨ�˶�״̬
	AXSTA_CONTINUOUS,	//�����˶�
	AXSTA_HOMING,		//���ڻ�ԭ��
	AXSTA_DISABLE,		//δ����״̬
	AXSTA_ERRSTOP,		//����ͣ
	AXSTA_SYNC,			//��ͬ��״̬
}AxStateTp;


//����ӿ�
//01���Զ�λ
extern s32 HZ_AxMoveAbs(u8 AxNum,s32 pos);
//02��Զ�λ
extern s32 HZ_AxMoveRel(u8 AxNum,s32 pos);
//03���Ӷ�λ
extern s32 HZ_AxMoveAdd(u8 AxNum,s32 pos);
//���¶�λ
//extern s32 HZ_AxMoveSuperImposed();
//��������()
//AxNum :��ţ���0��ʼ
//pos	:����0����С��0���� 0������
extern s32 HZ_AxMoveVelocity(u8 AxNum,s32 pos);
extern s32 HZ_AxChSpd(u8 AxNum,u32 Spd);
//ֹͣ��
extern s32 HZ_AxStop(u8 AxNum);

//////*****//////////////
//����ͣ
extern s32 HZ_AxStopDec(u8 AxNum);
//��ԭ��
extern s32 HZ_AxHome(u8 AxNum);


//��λ��(��λ���󼰰���״̬��Ϊ����)
extern s32 HZ_AxReset(u8 AxNum);
//����״̬
extern s32 HZ_AxGetStatus(u8 AxNum);
//�������
extern s32 HZ_AxGetAxisErr(u8 AxNum);
//����ǰλ��
extern s32 HZ_AxGetCurPos(u8 AxNum);
//д��ǰλ��
extern s32 HZ_AxSetCurPos(u8 AxNum,s32 pos);
//���ò���
extern s32 HZ_AxSetPara(u8 AxNum,\
				u32 Start,u32 TAcc,u32 Run,u32 TDec,u32 End,\
				u32 HomFast,u32 HomSlow,u32 HomOffset,\
				u32 TorS,u32 HomTimeOut);
//�������źŲ���
extern s32 HZ_AxSetAxiSig(u8 AxNum,\
					u8 HomSigEn,u8 HomSigNum,u8 HomSigLev,\
					u8 UpSigEn,u8 UpSigNum,u8 UpSigLev,\
					u8 DwSigEn,u8 DwSigNum,u8 DwSigLev);
//������������λ
extern s32 HZ_AxSetLimSoft(u8 AxNum,\
					u8 UpEn,s32 UpPos,\
					u8 DwEn,s32 DwPos);
//���û�ԭ��ģʽ
//AxNum :���
//Mod	:ģʽ
//		0��������ԭ��
//		1��������������λ���ٷ�����ԭ��
//		2���ȷ���������λ����������ԭ��
extern s32 HZ_AxSetHomMod(u8 AxNum,u8 Mod);

#endif
