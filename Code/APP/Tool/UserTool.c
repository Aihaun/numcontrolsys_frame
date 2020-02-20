#include "USERTOOL.H"
/********************************************************/

static void SetSpdRatio(s8 axnum, float spd) 
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
	//m/min 转换成脉冲速度,   脉冲/s
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
	
}
/**
* @author：nyh 20200102
* @Description:	轴运行
* @param --axnum 轴号，mode 运行模式, spd 速度(m/min)， 距离（mm） 
* @param --   
* @return --
*/
 void AxisRun(s8 axnum, s8 mode, float spd, float pos)  
{
	if(axnum >= PULS_NUM)return;
	SetSpdRatio(axnum,spd);
	switch(mode)
	{
		case ABSM: 
			HZ_AxMoveAbs(axnum,ConvertToMachineUnit(axnum,pos));
			break;
		
		case RELM: 
			HZ_AxMoveRel(axnum,ConvertToMachineUnit(axnum,pos));
			break;
				
		case GOHOMEM:
			HZ_AxHome(axnum);
			break;
		
		case STOPM:
			HZ_AxStop(axnum);
			break;
	}
}

//获取轴状态
s32 GetAxSta(u8 num1)
{
	if(HZ_AxGetStatus(num1)!=0)
	{
		return -1;
	}
    return 0;
}
//获取2轴状态
s32 Get2AxSta(u8 num1, u8 num2) 
{
	if(HZ_AxGetStatus(num1)!=0 || HZ_AxGetStatus(num2)!=0)
	{
		return -1;
	}
    return 0;
}

//整圆
//Axnum1 轴1,  Axnum2  轴2
//x1 y1 圆第二个点坐标， x2 y2圆第三个点坐标   spd 插补速度		圆第一个点为当前位置
s32 MillCircPath(u8 Axnum1, u8 Axnum2,s32 x1, s32 y1, s32 x2, s32 y2, float spd)
{
	VelocityDef Vel;  
	PointDef Pmid;
	PointDef Ptar;
	
	u32 RunSped;
	RunSped = spd * 1000 * GSS.Conversion[Axnum1].PPR / GSS.Conversion[Axnum1].MPR / 60;
	
	if(Get2AxSta(Axnum1,Axnum2) == 0)
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
		
		HZ_MultiAxSet(1, 2, Axnum1, Axnum2); 
		HZ_MultiAxSetVal(1, Vel);
		
		HZ_MultiAxMoveCirc(1, 2, Pmid, Ptar, 0);
		
		return 0;
	}
	return -1;
}

/*****************************************************************/



