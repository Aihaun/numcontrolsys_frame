#include "FSM.h"
/*!
* @file  FSM.c
* @brief ��̨״̬����ͨ������̬��ֹ̬ͣ����λ̬����̬ͣ����̬ͣ��״̬�����ƻ�̨��ȫ���С�
* @version 1.1 bsp.lib 1.1 int.lib
* @author  yfs
* @date 2018/08/29
*/

void Button()
{
	if(Triger(Tg0,0,I_Get(I_Run),200) || Triger(Tg4,1,GUS.StartOrStopButton,200))    
	{ 
		if(GUR.RunStatus == STOP)
		{
			if(Q_Get(Q_Fasten) == ON)
			{
				GUW.button.Data.RunCommand = RUN;
				GUR.OpenFileLimit = 1;
				GUS.StartCheckPage = 43;
			}
			else
			{
				AlarmSetBit(2,0,1);//ѹ������δѹ��
			}
			GUS.StartOrStopButton = 0;
		}
		else if(GUR.RunStatus == RUN)
		{
			GUW.button.Data.RunCommand = STOP;
			GUS.StartCheckPage = 0;
			GUR.OpenFileLimit = 0;
			GUS.StartOrStopButton = 0;
		}
	}
	if(Triger(Tg1,0,I_Get(I_Clamp),200))
	{		
		if(GUR.RunStatus != RUN && LT.AutoRunTask.execute == 0)
		{
			if(Q_Get(Q_Fasten) == ON)
			{
				Q_Set(Q_Fasten,OFF);
			}
			else
			{
				Q_Set(Q_Fasten,ON);
			}
		}
	}
	if(Triger(Tg2,0,I_Get(I_TableLift),200))
	{		
		if(GUR.RunStatus != RUN && LT.AutoRunTask.execute == 0)
		{
			if(Q_Get(Q_TableCyl) == ON)
			{
				Q_Set(Q_TableCyl,OFF);
			}
			else
			{
				Q_Set(Q_TableCyl,ON);
			}
		}
	}
	if(GSR.ErrorLevel > 3 || I_Get(I_Scram) == 1)
	{
		GUW.button.Data.RunCommand = SCRAM;
		if(I_Get(I_Scram) == 1)
		{			
			AlarmSetBit(3,0,1);//��ͣ���ر����£�
		}
	}
	if(Triger(Tg3,0,I_Get(I_Scram),0))
	{
		GUS.StartCheckPage = 0;
		GUR.OpenFileLimit = 0;
		GUW.button.Data.RunCommand = STOP;
	}
	if(GUR.RunStatus == STOP && GSR.ErrorLevel > 1)
	{
		GUR.OpenFileLimit = 0;
	}
}

void AxSpdInit()
{
	if(0)
	{
		for(u8 i=0; i<PULS_NUM; i++)
		{
			GSS.AxisData[i].StartSpeed = 10;
			GSS.AxisData[i].Acctime = 100;
			GSS.AxisData[i].RunSpeed = 1000;
			GSS.AxisData[i].Dectime = 100;
			GSS.AxisData[i].EndSpeed = 10;
			GSS.AxisData[i].HomeSpeedFast = 10;
			
			GSS.AxisData[i].HomeOffset = 0;
			
			GSS.AxisData[i].SoftMinLimit = -99998;
			GSS.AxisData[i].SoftMaxLimit = 99998;
			
			GSS.Conversion[i].PPR = 1;
			GSS.Conversion[i].MPR = 1;			
		}
	}
	for(u8 i=0; i<PULS_NUM; i++)
	{
//		GSS.AxisData[i].StartSpeed = 1;
//		GSS.AxisData[i].Acctime = 200;
//		GSS.AxisData[i].RunSpeed = 2;
//		GSS.AxisData[i].Dectime = 200;
//		GSS.AxisData[i].EndSpeed = 1;
//		GSS.AxisData[i].HomeSpeedFast = 6000;
		GSS.AxisData[i].HomeSpeedSlow = 500;
		GSS.AxisData[i].HomeOffset = 0;
		
		GSS.Conversion[i].PPR = 2500;
		GSS.Conversion[i].MPR = 10;
	}
}

void Indicate(LogicParaDef *t)
{
	if(GSR.ErrorLevel > 0)
	{
		LT.IndicateTask.execute = 1;
	}
	else
	{
		GUR.IndicateShow = 0;
	}
	FUNC_ENTER
	switch(it.step)
	{
		case 1:
			GUR.IndicateShow = 1;
			TimerRst(it);
			it.step = 2;
			break;
		
		case 2:
			if(TimerCnt(it) >= 300)
			{
				GUR.IndicateShow = 0;
				TimerRst(it);
				it.step = 3;
			}
			break;
			
		case 3:
			if(TimerCnt(it) >= 300)
			{
				PARAINIT(it);
			}
			break;
	}
}

//����ı���״̬
u32 Limit_Pos[8] = {I_Xpos, I_Ypos, I_Zpos, I_Wpos };//����λ
	u32 Limit_Neg[8] = {I_X, I_Y, I_Z, I_Wneg};//����λ
	s32 fangx[4] = {0};
void AxisErro()
{
    u8 i;
	
	if(GUR.RunStatus != D_RESET)
	{
		TrigerFlag[Tg10] = 1;
		if(Triger(Tg10, 0, I_Get(Limit_Neg[3]), 20) && AxGetsta(W_MOTOR) != 0 && Dir_GetSta(i) == 0)//0����1����
		{
			AlarmSetBit(2,2,3);//����λ
//			WorkEnd();

		}
		for(i=0; i<4; i++)
		{
			fangx[i] = Dir_GetSta(i);
			
			TrigerFlag[Tg11+i] = 1;
			if(Triger(Tg11+i,0,I_Get(Limit_Neg[i]),20) && AxGetsta(i) != 0 && AxGetsta(i) != AXSTA_HOMING && Dir_GetSta(i) == 0)//0����1����
			{
                AlarmSetBit(2,2,i);//����λ
				HZ_AxStop(i);
				if(GUR.RunStatus == RUN)
				{
//					WorkEnd();
				}
			}
			TrigerFlag[Tg15+i] = 1;
			if(Triger(Tg15+i,0,I_Get(Limit_Pos[i]),20) && AxGetsta(i) != 0 && AxGetsta(i) != AXSTA_HOMING && Dir_GetSta(i) == 1)//0����1����
			{
				AlarmSetBit(2,3,i);//����λ
				HZ_AxStop(i);
				if(GUR.RunStatus == RUN)
				{
//					WorkEnd();
				}
			}	
		}
	}
	if(SysTim_GetUser() >= 60000)
	{
		for(i=0; i<4; i++)
		{
			if(ALM_GetSta(i) == 1)//��Ҫ1��Ч
			{
				AlarmSetBit(4,1,i);//i�ᱨ��
//				WorkEnd();
			}
		}
	}
}
//״̬��
void FSM()
{
    u8 i;
    if(GSR.ErrorLevel > 0)//
    {
        if(GUR.RunStatus == RUN)
        {
            GUW.button.Data.RunCommand = STOP;
        }
    }
    if(GSR.ErrorLevel > 3)//
    {
        GUR.HaveToRepower = 1;
    }
    else
    {
        if(GSR.ErrorLevel == 3)//
        {
            GUR.HaveToReset = 1;
        }
    }
    if(GUR.HaveToReset == 1)
    {
        AlarmSetBit(3,0,0);//
    }
    if(GUR.HaveToRepower == 1)
    {
        AlarmSetBit(4,0,0);//
    }
    switch(GUW.button.Data.RunCommand)
    {
    case RUN:
        if(GUR.HaveToRepower == 0 && GUR.HaveToReset == 0 &&
                (GUR.RunStatus == STOP ||GUR.RunStatus == PAUSE)&& GSR.ErrorLevel < 2)
        {
		
            GUR.RunStatus = RUN;
        }
        else
        {
            GUW.button.Data.RunCommand = GUR.RunStatus;
        }
        break;

    case STOP:
        if(GUR.RunStatus != INIT)
        {
			if(GUR.RunStatus != STOP)
			{
				
			}
		
            GUR.RunStatus = STOP;
        }
        else
        {
            GUW.button.Data.RunCommand = GUR.RunStatus;
        }
        break;
    case PAUSE:
        if(GUR.RunStatus == RUN)
        {
            GUR.RunStatus = PAUSE;
        }
        else
        {
            GUW.button.Data.RunCommand = GUR.RunStatus;
        }
        break;
    case D_RESET:
        if( (GUR.RunStatus != RUN) && (GUR.RunStatus != PAUSE) )
        {
			if(GUR.RunStatus != D_RESET)
				PARAINIT(LT.ResetTask);
            GUR.RunStatus = D_RESET;
        }
        else
        {
            GUW.button.Data.RunCommand = GUR.RunStatus;
        }
        break;

    case SCRAM:
        GUR.RunStatus = SCRAM;
        break;
    case SIGSTEP:	//����
        if(GUR.HaveToRepower == 0 && GUR.HaveToReset == 0 &&
                (GUR.RunStatus == STOP ||GUR.RunStatus == PAUSE)&& GSR.ErrorLevel < 2)
        {
            GUR.RunStatus = SIGSTEP;

        }
        else
        {
            GUW.button.Data.RunCommand = GUR.RunStatus;
        }
        break;
    case SIGRUN:    //��������
        if(GUR.HaveToRepower == 0 && GUR.HaveToReset == 0 &&
                (GUR.RunStatus == STOP ||GUR.RunStatus == PAUSE)&& GSR.ErrorLevel < 2)
        {
            GUR.RunStatus = SIGRUN;

        }
        else
        {
            GUW.button.Data.RunCommand = GUR.RunStatus;
        }
        break;

    }

    switch(GUR.RunStatus)
    {
    case INIT:
		if(I_Get(I_Air) == 1)
		{
			AlarmSetBit(2,0,0);//��ѹ����
		}
        //��ʼִ̬�к���
        Logic();
		Motion();
        break; 
    case RUN: 
        //����ִ̬�к���
        Logic();
        break;
    case PAUSE:
        //��ִͣ�к���
        Logic();
        break;
    case STOP:
        //ִֹͣ�к���
        Logic();
		Motion();
        break;
    case D_RESET:
        //��λִ�к���
//		Ax_GoHome(LT.Ax_GoHomeTask);//������ƫ��ԭ��
        Reset(&LT.ResetTask);
        break;
    case SCRAM:
        //��ͣ����
        for(i = 0; i<8; i++)
        {
            HZ_AxStop(i);
        }
		OutPut_SetSta(0, OFF);
		OutPut_SetSta(1, OFF);
		for(i = 3; i < GPO_NUM; i++)  //��ʼ�� �����
		{
			OutPut_SetSta(i, OFF);
		}
        PARAINIT(LT);	//�����������
        GUR.HaveToReset = 1;
        break;
    }

//����ʲô״̬��ʹ�õĺ���
	Teach();

    //��λxyzƽ̨
    XYZW_Reset(&LT.XYZWRESETTask); 
    //�������
    Button();
    //��λ�ƶ��ӿ�
    Move(GSW.AxisMove,LT.AxisMoveTask);
    //�ᱨ������
    AxisErro();

	AxSpdInit();
	
	Indicate(&LT.IndicateTask);
	
	//�㶯����
	if(GUR.RunStatus == INIT || GUR.RunStatus == STOP)
	{
		AxLoop();
	}
	
	
	
}


