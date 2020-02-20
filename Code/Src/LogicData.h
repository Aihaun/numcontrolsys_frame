#ifndef __LOGICDATA_H
#define __LOGICDATA_H
#include "bsplib.h"



#define BC 		BasicPara.CheckPara		//�Ե�����
#define BM  	BasicPara.MechanicalPara   //��е����
#define PCBW  	p->ConfigSoftPara->BasicPara.workPara         //�ӹ�����
#define PCW  	BasicPara.WorkFile		//�ߴ��ļ�

typedef struct
{
    u8 execute;
    u8 step;
    u8 done;
	u8 mode;
    s32 count;
    s32 index;
	u32 Tms;
    u32 tm;
} LogicParaDef;

typedef struct
{
    u32 execute;
    u32 mode;
    s32 pos;
    u32 speed;
} GoPosPara;	//��λ�����˶��ӿ�


#endif
