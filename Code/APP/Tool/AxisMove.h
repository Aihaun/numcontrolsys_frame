#ifndef __AXISMOVE_H
#define __AXISMOVE_H
#include "logic.h"

#define AXIS_NUM 8

enum {
    GOHOMETYPE1 ,	    //ֱ�ӻ�ԭ��(ƽ��ģʽ)
    GOHOMETYPE2,		//�ȵ�����λ�ٻ�ԭ��
    GOHOMETYPE3,		//�Ȼ�����λ�ٻ�ԭ��
	GOHOMETYPE4,        //z����ԭ������
	GOHOMETYPE5,        //z����ԭ�㷴��
};

typedef enum
{
    AX_ERR_AX_ALM = (1 << 0),		//�ᱨ��
    AX_ERR_AX_TMOUT = (1 << 1),		//��ʱ����ԭ�㣩
    AX_ERR_UP_LIM_H = (1 << 8),		//Ӳ����λ
    AX_ERR_UP_LIM_S = (1 << 9),		//������λ
    AX_ERR_DW_LIM_H = (1 << 12),		//Ӳ����λ
    AX_ERR_DW_LIM_S = (1 << 13),		//������λ
} AxErrBitTp;

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

typedef enum	//��Ŷ���
{
    X_MOTOR,
    Y_MOTOR,
    Z_MOTOR,
	W_MOTOR,
} AxisNum;

typedef enum	//�ᶯģʽѡ��
{
    ABSMODE,//0
    RELMODE,//1
    SPDMODE,//2
    GOHOMEMODE,//3
    STOPMODE,	//4
} MoveMode;

extern void Move(GoPosPara Para[], LogicParaDef T[]);
extern s32 MotorMove(u32 num,u32 speed,s32 pos,u32 mode);
extern void SetAxisSpdRadio(u8 i,u8 spd);
extern s32 SetSpd(u8 i, u32 RunSpeed);
extern void SetSpdDefault(u8 i);

extern s32 MotorMoveMM(u32 num,u32 speed,s32 pos,u32 mode);
extern void AxRun(s8 axnum, s8 mode, float spd, float pos);

extern s32 MillLine(s32 x, s32 y, s32 z, float spd);
extern s32 MillCirc(s32 x1, s32 y1, s32 x2, s32 y2, float spd);
extern s32 MillArc(u8 Axnum1, u8 Axnum2, s32 x1, s32 y1,  s32 x2, s32 y2, float spd);
extern s32 MillArc_XZ(s32 x1, s32 Z1,  s32 x2, s32 z2, float spd);

#endif
