#include "axismove.h"
#include "Algorithm.h"
/**
* @author 19/02/25  yang
* @Description: ��λ�����ƶ��ӿ�
* @param -- Para �ƶ�����
* @param -- T ������
* @return --
*/
void Move(GoPosPara Para[], LogicParaDef T[])
{
    for (int i = 0; i < AXIS_NUM; i++)
    {
        if (Para[i].execute == 1&&Para[i].mode != STOPMODE) //�����˶�
        {
            T[i].execute = 1;
        }
        if(Para[i].execute == 1&& Para[i].mode == STOPMODE)  //����ͣ��
        {
            PARAINIT(T[i]);
            PARAINIT(Para[i]);
            HZ_AxStop(i);
        }
        INITTASK(T[i])
        switch (T[i].step)
        {
        case 1:
            if (HZ_AxGetStatus(i) == AXSTA_READY)
            {
                MotorMove(i, Para[i].speed, Para[i].pos, Para[i].mode);
            }
            T[i].step = 2;
            break;
        case 2:
            if (HZ_AxGetStatus(i) == AXSTA_READY||HZ_AxGetStatus(i)==AXSTA_ERRSTOP)
            {
                PARAINIT(T[i]);
                PARAINIT(Para[i]);
            }
            break;
        default:
            break;
        }
    }
}
/**
* @author 19/02/19  yang
* @Description: ���ƶ��ӿ�
* @param -- ��� �ٶ� λ�� ģʽ
* @param --
* @return --
*/
s32 MotorMove(u32 num,u32 speed,s32 pos,u32 mode)
{
    if(num>PULS_NUM)
        return -1;
    SetSpd(num, speed);	//�����ٶ�
    switch(mode)
    {
    case ABSMODE:
        HZ_AxMoveAbs(num, pos);
        break;
    case RELMODE:
        HZ_AxMoveRel(num, pos);
        break;
    case SPDMODE:
        HZ_AxMoveVelocity(num, pos);
        break;
    case GOHOMEMODE:
        //����ģʽ���ٶ�Ϊ�������
        GSS.AxisData[num].RunSpeed = speed;
        HZ_AxSetPara(num, GSS.AxisData[num].StartSpeed, GSS.AxisData[num].Acctime,
                     GSS.AxisData[num].StartSpeed ,
                     GSS.AxisData[num].Dectime, GSS.AxisData[num].EndSpeed,
                     GSS.AxisData[num].RunSpeed, GSS.AxisData[num].HomeSpeedSlow,
                     GSS.AxisData[num].HomeOffset, 0, 0);
        HZ_AxHome(num);
        break;
    default:
        break;
    }
    return 0;
}
/*
 * Created: 11/16
 * Description:
 * param:
 * Modified By:yang
 */
void SetAxisSpdRadio(u8 i,u8 spd)
{
    if(spd>=100||spd<=0)
    {
        spd = 100;
    }
//	if (GSS.AxisData[i].StartSpeed + __fabs(GSS.AxisData[i].RunSpeed - GSS.AxisData[i].StartSpeed)*spd / 100 <= GSS.AxisData[i].StartSpeed)
//    {
//        GSS.AxisData[i].StartSpeed = GSS.AxisData[i].StartSpeed + __fabs(GSS.AxisData[i].RunSpeed - GSS.AxisData[i].StartSpeed)*spd / 100 -1;
//    }
//	if (GSS.AxisData[i].StartSpeed + __fabs(GSS.AxisData[i].RunSpeed - GSS.AxisData[i].StartSpeed)*spd / 100 <= GSS.AxisData[i].EndSpeed)
//    {
//        GSS.AxisData[i].EndSpeed = GSS.AxisData[i].StartSpeed + __fabs(GSS.AxisData[i].RunSpeed - GSS.AxisData[i].StartSpeed)*spd / 100 -1;
//    }
//	
//	if (GSS.AxisData[i].HomeSpeedFast <= GSS.AxisData[i].StartSpeed)
//    {
//        GSS.AxisData[i].StartSpeed = GSS.AxisData[i].HomeSpeedFast -1;
//    }
//	if (GSS.AxisData[i].HomeSpeedFast <= GSS.AxisData[i].EndSpeed)
//    {
//        GSS.AxisData[i].EndSpeed = GSS.AxisData[i].HomeSpeedFast -1;
//    }
//	
    HZ_AxSetPara(i, GSS.AxisData[i].StartSpeed, GSS.AxisData[i].Acctime,
                 GSS.AxisData[i].StartSpeed + __fabs(GSS.AxisData[i].RunSpeed - GSS.AxisData[i].StartSpeed)*spd / 100,
                 GSS.AxisData[i].Dectime, GSS.AxisData[i].EndSpeed,
                 GSS.AxisData[i].HomeSpeedFast, GSS.AxisData[i].HomeSpeedSlow,
                 GSS.AxisData[i].HomeOffset, 0, 0);
}

s32 SetSpd(u8 i, u32 RunSpeed)
{
     if (i > PULS_NUM)
    {
        return -1;
    }
    if (RunSpeed < GSS.AxisData[i].StartSpeed)
    {
        RunSpeed = GSS.AxisData[i].StartSpeed + 1;
    }
    if (HZ_AxSetPara(i, GSS.AxisData[i].StartSpeed, GSS.AxisData[i].Acctime, RunSpeed,
                     GSS.AxisData[i].Dectime, GSS.AxisData[i].EndSpeed,
                     GSS.AxisData[i].HomeSpeedFast, GSS.AxisData[i].HomeSpeedSlow,
                     GSS.AxisData[i].HomeOffset, 0, 0) == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}


//Բ���岹,���XY
//x1 y1 Բ���е����꣬ x2 y2Բ��ĩ������   spd �岹�ٶ�		Բ����һ����Ϊ��ǰλ��
s32 MillArc(u8 Axnum1, u8 Axnum2, s32 x1, s32 y1,  s32 x2, s32 y2, float spd)
{
	VelocityDef Vel;
	PointDef Pmid;
	PointDef Ptar; 
	
	u32 RunSped;
	RunSped = spd * 1000 * GSS.Conversion[Axnum1].PPR / GSS.Conversion[Axnum1].MPR / 60;
	
	if(Check_AxisStatu(3) == 0)
	{
		Vel.Tacc = 200;
		if(RunSped > 3000)
			Vel.Vinit = 3000;
		else
			Vel.Vinit = RunSped - 1;
		Vel.Vtar = RunSped;
		
		Pmid.x = x1;
		Pmid.y = y1;
		
		Ptar.x = x2;
		Ptar.y = y2;
		
		HZ_MultiAxSet(1, 2, Axnum1, Axnum2);
		HZ_MultiAxSetVal(1, Vel);
		
		HZ_MultiAxMoveArc(1, 2, Pmid, Ptar);
		
		return 0;
	}
	return -1;
}

//Բ���岹,���XZ
//x1 z1 Բ���е����꣬ x2 z2Բ��ĩ������   spd �岹�ٶ�		Բ����һ����Ϊ��ǰλ��
s32 MillArc_XZ(s32 x1, s32 z1,  s32 x2, s32 z2, float spd)
{
	VelocityDef Vel;
	PointDef Pmid;
	PointDef Ptar;
	
	u32 RunSped;
	RunSped = spd * 1000 * GSS.Conversion[X_MOTOR].PPR / GSS.Conversion[X_MOTOR].MPR / 60;
	
	if(Check_AxisStatu(3) == 0)
	{
		Vel.Tacc = 200;
		if(RunSped > 3000)
			Vel.Vinit = 3000;
		else
			Vel.Vinit = RunSped - 1;
		Vel.Vtar = RunSped;
		
		Pmid.x = x1;
		Pmid.y = z1;
		
		Ptar.x = x2;
		Ptar.y = z2;
		
		HZ_MultiAxSet(1, 2, X_MOTOR, Z_MOTOR);
		HZ_MultiAxSetVal(1, Vel);
		
		HZ_MultiAxMoveArc(1, 2, Pmid, Ptar);
		
		return 0;
	}
	return -1;
}

//ֱ�߲岹
//x y ֱ��ĩ������  spd �岹�ٶ�
s32 MillLine(s32 x, s32 y, s32 z, float spd)
{
	VelocityDef Vel;
	
	u32 RunSped;
	RunSped = spd * 1000 * GSS.Conversion[X_MOTOR].PPR / GSS.Conversion[X_MOTOR].MPR / 60;
	
	if(Check_AxisStatu(3) == 0)
	{
		if((HZ_AxGetCurPos(X_MOTOR)-x)!=0||(HZ_AxGetCurPos(Y_MOTOR)-y)!=0)
		{
			Vel.Tacc = 200;
			if(RunSped > 3000)
				Vel.Vinit = 3000;
			else
				Vel.Vinit = RunSped - 1;
			Vel.Vtar = RunSped;
			
			HZ_MultiAxSet(0, 3, X_MOTOR, Y_MOTOR, Z_MOTOR);
			HZ_MultiAxSetVal(0, Vel);
			
			HZ_MultiAxMove(0, 3, x, y, z);
		}else
		{
			MotorMove(Z_MOTOR,RunSped,z,ABSMODE);
		}
		return 0;
	}
	return -1;
}

//��Բ
//x1 y1 Բ�ڶ��������꣬ x2 y2Բ������������   spd �岹�ٶ�		Բ��һ����Ϊ��ǰλ��
s32 MillCirc(s32 x1, s32 y1, s32 x2, s32 y2, float spd)
{
	VelocityDef Vel;  
	PointDef Pmid;
	PointDef Ptar;
	
	u32 RunSped;
	RunSped = spd * 1000 * GSS.Conversion[X_MOTOR].PPR / GSS.Conversion[X_MOTOR].MPR / 60;
	
	if(Check_AxisStatu(3) == 0)
	{
		Vel.Tacc = 100;
		if(RunSped > 1000)
			Vel.Vinit = 1000;
		else
			Vel.Vinit = RunSped - 1;
		Vel.Vtar = RunSped;
		
		Pmid.x = x1;
		Pmid.y = y1;
		
		Ptar.x = x2;
		Ptar.y = y2;
		
		HZ_MultiAxSet(1, 2, X_MOTOR, Y_MOTOR);
		HZ_MultiAxSetVal(1, Vel);
		
		HZ_MultiAxMoveCirc(1, 2, Pmid, Ptar, 0);
		
		return 0;
	}
	return -1;
}

//mm				0.1m/min
s32 SetSpdMM(u8 i, u32 RunSpeed)
{
    if (i > PULS_NUM)
    {
        return -1;
    }
	u32 spd;
	
	spd = RunSpeed * 100.0 / 60 * GSS.Conversion[i].PPR / GSS.Conversion[i].MPR;	//ת���������ٶ�
    if (spd < GSS.AxisData[i].StartSpeed)
    {
        spd = GSS.AxisData[i].StartSpeed + 1;
    }
    if (HZ_AxSetPara(i, GSS.AxisData[i].StartSpeed, GSS.AxisData[i].Acctime, spd,
                     GSS.AxisData[i].Dectime, GSS.AxisData[i].EndSpeed,
                     GSS.AxisData[i].HomeSpeedFast, GSS.AxisData[i].HomeSpeedSlow,
                     GSS.AxisData[i].HomeOffset, 0, 0) == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

//mm�ƶ�	spd 0.1m/min		pos 0.1mm
s32 MotorMoveMM(u32 num,u32 speed,s32 pos,u32 mode)
{
    if(num>PULS_NUM)
        return -1;
    SetSpdMM(num, speed);	//�����ٶ�
	s32 pos1;
	pos1 = pos / 10.0 * GSS.Conversion[num].PPR / GSS.Conversion[num].MPR;	//ת������������
    switch(mode)
    {
    case ABSMODE:
        HZ_AxMoveAbs(num, pos1);
        break;
    case RELMODE:
        HZ_AxMoveRel(num, pos1);
        break;
    case SPDMODE:
        HZ_AxMoveVelocity(num, pos1);
        break;
    default:
        break;
    }
    return 0;
}

void AxSetSpdRatio(s8 axnum, float spd)
{
	u32 StarSped,RunSped, EndSped;
    if(spd>10||spd<=0)
    {
        spd = 0.1;
    }
	if (spd <= (float)GSS.AxisData[axnum].StartSpeed/100)
    {
        spd = GSS.AxisData[axnum].StartSpeed + 0.01;
    }
	if (spd <= (float)GSS.AxisData[axnum].EndSpeed/100)
    {
        spd = GSS.AxisData[axnum].EndSpeed + 0.01;
    }
	//ת���������ٶ�,   ����/s
	StarSped = GSS.AxisData[axnum].StartSpeed * 1000 * GSS.Conversion[axnum].PPR / GSS.Conversion[axnum].MPR / 60;
	RunSped = spd * 1000 * GSS.Conversion[axnum].PPR / GSS.Conversion[axnum].MPR / 60;
	EndSped = GSS.AxisData[axnum].EndSpeed * 1000 * GSS.Conversion[axnum].PPR / GSS.Conversion[axnum].MPR / 60 ;	

    HZ_AxSetPara(axnum, StarSped,\
						GSS.AxisData[axnum].Acctime,\
						RunSped,\
						GSS.AxisData[axnum].Dectime,\
						EndSped,\
						GSS.AxisData[axnum].HomeSpeedFast,\
						GSS.AxisData[axnum].HomeSpeedSlow,\
					GSS.AxisData[axnum].HomeOffset, 0, 0);
	
//	if(spd>100||spd<=0)
//    {
//        spd = 1;
//    }
//	
//    HZ_AxSetPara(axnum, GSS.AxisData[axnum].StartSpeed *spd / 100, GSS.AxisData[axnum].Acctime,
//                 GSS.AxisData[axnum].StartSpeed + __fabs(GSS.AxisData[axnum].RunSpeed - GSS.AxisData[axnum].StartSpeed)*spd / 100,
//                 GSS.AxisData[axnum].Dectime, GSS.AxisData[axnum].EndSpeed *spd / 100,
//                 GSS.AxisData[axnum].HomeSpeedFast, GSS.AxisData[axnum].HomeSpeedSlow,
//                 GSS.AxisData[axnum].HomeOffset, 0, 0);
}
void AxRun(s8 axnum, s8 mode, float spd, float pos) 
{
	if(axnum >= PULS_NUM)return;
	AxSetSpdRatio(axnum,spd);
	switch(mode)
	{
		case ABSMODE:
			HZ_AxMoveAbs(axnum,ConvertToMachineUnit(axnum,pos));
			break;
		
		case RELMODE:
			HZ_AxMoveRel(axnum,ConvertToMachineUnit(axnum,pos));
			break;
				
		case GOHOMEMODE:
			HZ_AxHome(axnum);
			break;
		
		case STOPMODE:
			HZ_AxStop(axnum);
			break;
	}
}



