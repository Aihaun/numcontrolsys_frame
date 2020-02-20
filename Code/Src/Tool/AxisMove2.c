#include "axismove.h"
/**
* @author 19/02/25  yang
* @Description: 上位机轴移动接口
* @param -- Para 移动参数
* @param -- T 任务名
* @return --
*/
void Move(GoPosPara Para[], LogicParaDef T[])
{
    for (int i = 0; i < AXIS_NUM; i++)
    {
        if (Para[i].execute == 1&&Para[i].mode != STOPMODE) //该轴运动
        {
            T[i].execute = 1;
        }
        if(Para[i].execute == 1&& Para[i].mode == STOPMODE)  //立即停轴
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
* @Description: 轴移动接口
* @param -- 轴号 速度 位置 模式
* @param --
* @return --
*/
s32 MotorMove(u32 num,u32 speed,s32 pos,u32 mode)
{
    if(num>PULS_NUM)
        return -1;
    SetSpd(num, speed);	//设置速度
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
        //回零模式下速度为回零快速
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


//直线插补
s32 CloseLine(s32 x, s32 y, u32 spd)
{
	VelocityDef Vel;
	if(Check_AxisStatu(3) == 0)
	{
		Vel.Tacc = GSS.AxisData[XMOTOR].Acctime;
		if(spd > 1000)
			Vel.Vinit = 1000;
		else
			Vel.Vinit = spd - 1;
		Vel.Vtar = spd;
		
		if((HZ_AxGetCurPos(XMOTOR)-x)!=0||(HZ_AxGetCurPos(YMOTOR)-y)!=0)
		{
			HZ_MultiAxSet(0, 2, XMOTOR, YMOTOR);
			HZ_MultiAxSetVal(0, Vel);
			HZ_MultiAxMove(0, 2, x, y);
		}
			
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
	spd = RunSpeed * 100.0 / 60 * GSS.Conversion[i].PPR / GSS.Conversion[i].MPR;	//转换成脉冲速度
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

//mm移动	spd 0.1m/min		pos 0.1mm
s32 MotorMoveMM(u32 num,u32 speed,s32 pos,u32 mode)
{
    if(num>PULS_NUM)
        return -1;
    SetSpdMM(num, speed);	//设置速度
	s32 pos1;
	pos1 = pos / 10.0 * GSS.Conversion[num].PPR / GSS.Conversion[num].MPR;	//转换成脉冲坐标
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


