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
	//m/min ת���������ٶ�,   ����/s
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
* @author��nyh 20200102
* @Description:	������
* @param --axnum ��ţ�mode ����ģʽ, spd �ٶ�(m/min)�� ���루mm�� 
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

//��ȡ��״̬
s32 GetAxSta(u8 num1)
{
	if(HZ_AxGetStatus(num1)!=0)
	{
		return -1;
	}
    return 0;
}
//��ȡ2��״̬
s32 Get2AxSta(u8 num1, u8 num2) 
{
	if(HZ_AxGetStatus(num1)!=0 || HZ_AxGetStatus(num2)!=0)
	{
		return -1;
	}
    return 0;
}

//��Բ
//Axnum1 ��1,  Axnum2  ��2
//x1 y1 Բ�ڶ��������꣬ x2 y2Բ������������   spd �岹�ٶ�		Բ��һ����Ϊ��ǰλ��
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



