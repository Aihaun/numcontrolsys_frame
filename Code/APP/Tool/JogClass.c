#include "JogClass.h"

volatile float JogRoute[5] = {0.1, 1, 10, 50, 100};
extern u32 Limit_Pos[8];
extern u32 Limit_Neg[8];
void JogFunc(JogDataDef *p)
{
	u32	axnum,i;
	u32	mode;
	if(GUW.JogData.Data.Joglevel < 5)//�㶯���� 
	{
		p->JogUnitPos = JogRoute[GUW.JogData.Data.Joglevel];
		if(p->JogStop > 0 && p->JogStop <= PULS_NUM)
		{
			mode = STOPMODE;
			axnum = p->JogStop-1;
			AxRun(axnum,mode,p->JogSpd,p->JogUnitPos);
		}
		if(p->JogHome > 0 && p->JogHome <= PULS_NUM)
		{
			axnum = p->JogHome-1;
			if(AXSTA_ERRSTOP == HZ_AxGetStatus(axnum))//���޴���
			{
				HZ_AxReset(axnum);
			}
			mode = GOHOMEMODE;
			
//			AxRun(axnum,mode,p->JogSpd,p->JogUnitPos);
			LT.Ax_GoHomeTask[axnum].execute = 1;//�����ƫ��ԭ��
		}
		if(p->JogForward > 0 && p->JogForward <= PULS_NUM)
		{	
			mode = RELMODE;
			axnum = p->JogForward-1;
			if(AXSTA_ERRSTOP == HZ_AxGetStatus(axnum))//���޴���
			{			
				if(0 == (0x0fff & HZ_AxGetAxisErr(axnum)))
				{
					HZ_AxReset(axnum);
					//AxRunUnit(axnum,mode,p->JogSpd,p->JogUnitPos);
				}
			}
			else
			{
				AxRun(axnum,mode,p->JogSpd,p->JogUnitPos);
			}
		}
		if(p->JogBackward > 0 && p->JogBackward <= PULS_NUM)
		{
			mode = RELMODE;
			axnum = p->JogBackward-1;
			if(AXSTA_ERRSTOP == HZ_AxGetStatus(axnum))//���޴���
			{			
				if(0 == (0xf0ff & HZ_AxGetAxisErr(axnum)))
				{
					HZ_AxReset(axnum);
					//AxRunUnit(axnum,mode,p->JogSpd,-(p->JogUnitPos));
				}
			}
			else
			{
				AxRun(axnum,mode,p->JogSpd,-(p->JogUnitPos));
			}				
		}
		p->JogStop = 0;
		p->JogForward = 0;
		p->JogBackward = 0;
		p->JogHome = 0;
	}
	else//����
	{
		p->JogUnitPos = 0.5;//ÿ���ƶ�����
		
		for(i=0; i<PULS_NUM; i++)
		{
			if((p->JogStop > 0 && p->JogStop <= PULS_NUM) || I_Get(Limit_Neg[i]) == 0 || I_Get(Limit_Pos[i]) == 0)
			{
				p->JogStop = 0;
				mode = STOPMODE;
				axnum = p->JogStop-1;
				AxRun(axnum,mode,p->JogSpd,p->JogUnitPos);
			}
		}
		if(p->JogHome > 0 && p->JogHome <= PULS_NUM)
		{
//			p->JogHome = 0;
			axnum = p->JogHome-1;
			if(AXSTA_ERRSTOP == HZ_AxGetStatus(axnum))//���޴���
			{
				HZ_AxReset(axnum);
			}
			mode = GOHOMEMODE;
			
//			AxRun(axnum,mode,p->JogSpd,p->JogUnitPos);
			LT.Ax_GoHomeTask[axnum].execute = 1;//�����ƫ��ԭ��
		}
		for(i=0; i<PULS_NUM; i++)
		{
			if((GUW.JogData.Data.JogContinuForward & 1<<i) && I_Get(Limit_Pos[i]) == 1)
			{	
				mode = RELMODE;
				axnum = i;
				if(AXSTA_ERRSTOP == HZ_AxGetStatus(axnum))//���޴���
				{			
					if(0 == (0x0fff & HZ_AxGetAxisErr(axnum)))
					{
						HZ_AxReset(axnum);
						//AxRunUnit(axnum,mode,p->JogSpd,p->JogUnitPos);
					}
				}
				else
				{
					AxRun(axnum,mode,p->JogSpd,p->JogUnitPos);
				}
			}
			if((GUW.JogData.Data.JogContinuBackward & 1<<i) && I_Get(Limit_Neg[i]) == 1)
			{
				mode = RELMODE;
				axnum = i;
				if(AXSTA_ERRSTOP == HZ_AxGetStatus(axnum))//���޴���
				{			
					if(0 == (0xf0ff & HZ_AxGetAxisErr(axnum)))
					{
						HZ_AxReset(axnum);
						//AxRunUnit(axnum,mode,p->JogSpd,-(p->JogUnitPos));
					}
				}
				else
				{
					AxRun(axnum,mode,p->JogSpd,-(p->JogUnitPos));
				}				
			}
		}
		p->JogStop = 0;
		p->JogForward = 0;
		p->JogBackward = 0;
		p->JogHome = 0;
	}
}

/**
* @author��nyh 20191226
* @Description:	�����ԭ���ƫ��ԭ��
* @param --
* @return --
*/
void Ax_GoHome(LogicParaDef Task[])
{
	u8 i;
	for(i=0; i<PULS_NUM; i++)
	{
		if(Task[i].execute == 1 && Task[i].step == 0)
		{
			Task[i].done = 0;
			Task[i].step = 1;
		}
		switch(Task[i].step)
		{
			case 1:
				AxRun(i, GOHOMEMODE, 0, 0);
				Task[i].step = 2;
				break;
				
			case 2://ƫ��ԭ�����
				if(AxGetsta(i) == 0)
				{
					AxRun(i, ABSMODE, 0.5 , 3);
					Task[i].step = 3;
				}
				break;
								
			case 3:
				if(AxGetsta(i) == 0)
				{
					HZ_AxSetCurPos(i, 0);//��ǰλ����0
					PARAINIT(Task[i]);
					Task[i].done = 1;
				}
				break;
		}
	}
}

void AxLoop()
{
	JogFunc((JogDataDef *)&GUW.JogData.Data);
	Ax_GoHome(LT.Ax_GoHomeTask);//������ƫ��ԭ��
}
