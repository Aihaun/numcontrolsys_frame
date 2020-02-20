/*
 * File: Logic.c
 * File Created: Thursday, 6th February 2020 1:30:00 pm
 * version: v00.01.00 8��ײ�
 * Description:�û��߼�
 * Modified By:nyh
 * -----
 * Copyright 2020 - 2020, <<hzzh>>
 */
 
#include "Logic.h"       

/*ȫ�ֱ�����ͳһ����*/
Task LT = { 0 }; //ͳһ��������
//SysData Data= { 0 };   //ͳһ��������

 struct HoleConfigPara HoC;
 struct SlotConfigPara SlC;
 struct HingeConfigPara HiC;
 struct ChangerConfigPara ChC;
 struct SetDoorSizeConfigPara SDC;
 struct SetToolConfigPara STC;
		
u32 Q_Contactor[5] 	= {Q_Hinge, Q_Slot, Q_Stair, Q_Hole1, Q_Hole2};//�����Ӵ���				
u32 Q_FreSpd[4]    	= {Q_FreSpd1, Q_FreSpd2, Q_FreSpd3, Q_FreSpd4};//��Ƶ���ٶ�	
u32 Q_HoleCyl[2] 	= {Q_Hole1Cyl, Q_Hole2Cyl};//�׵�����
u32 I_HoleKOrg[2] 	= {I_HoleK1Org, I_HoleK2Org};//�׵�����ԭ��
u32 I_HingeOrg[4] 	= {I_HingeK1Org, I_HingeK2Org, I_HingeK3Org,I_HingeK4Org};//��������ԭ��

/**
* @author��nyh 20200210
* @Description:	����ָ������,Start���
*/
void (*StartFuncArr[19])() =
{                             //mode
	StartHingeUpSide,          //1	�Ͽڷ���
	StartHingeUpDiffer,        //2	�Ͽ����
	StartHingeDownSide,        //3	�¿ڷ���
	StartHingeDownDiffer,      //4	�¿����
	StartHingeHole,            //5	���ͽ���
	StartHingeCloseSide,       //6	��շ���
	
	StartKnifeHole_one,        //7	һ����
	StartKnifeCirc_one,        //8	һ��ϳԲ
	StartKnifeLine_one,        //9	һ������
	StartKnifeHole_two,        //10	������
	StartKnifeCirc_two,        //11	����ϳԲ
	StartKnifeLine_two,        //12	��������
	
	StartLockSlot,             //13	����
	StartLockArcSlot,          //14	Բ������
	StartLockOrder,            //15	����
	StartLockArcOrder,         //16	Բ������
	
	StartHingeArc,			   //17	������
	StartKnifeArc_Level_one,   //18	һ��Բ��
	StartKnifeArc_Level_two,   //19	����Բ��
};

/**
* @author��nyh 20200210
* @Description:	����ָ������,Get��ȡ״̬
*/
s32 (*GetFuncArrSta[19])() =
{                           //mode  
	GetHingeUpSide,          //1
	GetHingeUpDiffer,        //2
	GetHingeDownSide,        //3 
	GetHingeDownDiffer,      //4
	GetHingeHole,            //5
	GetHingeCloseSide,       //6
	
	GetKnifeHole_one,        //7
	GetKnifeCirc_one,        //8
	GetKnifeLine_one,        //9	
	GetKnifeHole_two,        //10
	GetKnifeCirc_two,        //11
	GetKnifeLine_two,        //12
	 
	GetLockSlot,             //13
	GetLockArcSlot,          //14
	GetLockOrder,            //15
	GetLockArcOrder,         //16
	 
	GetHingeArc,			 //17
	GetKnifeArc_Level_one,   //18	
	GetKnifeArc_Level_two,   //19		
};

/**
* @author��nyh 20200208
* @Description:	ȫ���߼���غ�����ѯ
* @param --
* @return --
*/
void RunMain() 
{		
	HoC.HoleLoop(&HoC, GUR.WorkWhich); 	//�׺�����ѯ
	SlC.LockLoop(&SlC); 			//���ۡ����׺�����ѯ
	HiC.HingeLoop(&HiC); 		//����������ѯ
	ChC.ChangerOperateLoop(&ChC);	//��Ƶ��������ѯ
	SDC.SetDoorSizeLoop(&SDC);		//�����Ű�ߴ���ѯ
	STC.SetToolLoop(&STC);			//�Ե���ѯ	
        
}
/**
* @author��nyh 20200210
* @Description:	������Ϣ
*/
void AppAlm()
{
	u8 i;
	for(i=0; i<5; i++)
	{
		if(ExI_Get(0,I_FreFault+i) == 1)
		{
			AlarmSetBit(4,0,2+i);//��Ƶ�����ϡ��ȼ�1���ס��ȼ�2����1���ȼ�3����2������Һλ
			WorkEnd();
		}
	}
	if(I_Get(I_Air) == 1)
	{
		AlarmSetBit(2,0,0);//��ѹ����
		WorkEnd();
	}
}
/**
* @author��nyh 20200210
* @Description:	�ӹ���ֹ
* @param --
* @return --
*/
void  WorkEnd()
{ 
	u8 i;
	for(i = 0; i<8; i++)
	{
		HZ_AxStop(i);
	}
	for(i = 0; i < GPO_NUM; i++)  //��ʼ�� �����
	{
		OutPut_SetSta(i, OFF);
	}
	//�������̽���
	PARAINIT(LT);	
	PARAINIT(HoC.TaskFunc);
	PARAINIT(SlC.TaskFunc);
	PARAINIT(HiC.TaskFunc);
	PARAINIT(STC.TaskFunc);
	PARAINIT(SDC.TaskFunc);
	PARAINIT(ChC.TaskFunc);
}
/**
* @author��nyh 20191203
* @Description:	Y���ԭ��
* @param --
* @return --
*/
void Y_GoHome(LogicParaDef *t)
{
	FUNC_ENTER
	switch(it.step)
	{
		case 1:
//			if(ExI_Get(0,I_CluthCon) == 0)
//			{
//				AxRun(Y_MOTOR, ABSMODE, BasicPara.MechanicalPara.MoveSpd , GUS.BasicPara.checkPara.Hinge.cluthPosY);
//				it.step = 2;
//			}
//			else
			{
				it.step = 4;
			}
			break;
			
		case 2://��������ɿ�
			if(AxGetsta(Y_MOTOR) == 0)
			{
				Q_Set(Q_Cluth,OFF);
				TimerRst(it);
				it.step = 3;
			}
			break;
		
		case 3://�ж���������ɿ���λ
			if(TimerCnt(it) <= 3000)
			{
				if(ExI_Get(0,I_CluthLos) == 0)
				{
					it.step = 4;
				}
			}
			else
			{
				AlarmSetBit(2,1,3);//��������ɿ��쳣
				PARAINIT(it);
			}
			break;
			
		case 4://Y������ƫ��3mm
			LT.Ax_GoHomeTask[Y_MOTOR].execute = 1;
			it.step = 5;
			break;
		
		case 5:
			if(LT.Ax_GoHomeTask[Y_MOTOR].execute == 0)
			{
				PARAINIT(it);
			}
			break;
	}
}

/**
* @author��nyh 20191025
* @Description:	��������
* @param --
* @return --
*/
void RunProcess(LogicParaDef *t, BasicParaDef BasicPara)
{
	u8 i;
	static u32 StepMode = 0;
	if(BasicPara.MechanicalPara.AutoWideEnable == 1)
	{   //�Զ������Ŀ���
		BasicPara.MechanicalPara.DoorThick = GUR.SetDoorThick;
		BasicPara.MechanicalPara.DoorWide  = GUR.SetDoorWide;
	}
	else
	{	//�˹����Ŀ���
		BasicPara.MechanicalPara.DoorThick = BasicPara.MechanicalPara.HMI_DoorThick;
		BasicPara.MechanicalPara.DoorWide  = BasicPara.MechanicalPara.HMI_DoorWide;
	}
	
	if(GUR.RunStatus == RUN)
	{
		LT.AutoRunTask.execute = 1;
	}
	if(it.execute == 1 && it.step == 0) 
	{ 
		for(i=0; i<4; i++)
		{
			Q_Set(Q_FreSpd[i],OFF);//��Ƶ�ٶȹ�
		}
		for(i=0; i<5; i++)
		{
			Q_Set(Q_Contactor[i],OFF);//�����Ӵ�����
		}
		
		PARAINIT(ChC.TaskFunc.ChengerManu); 
		GUW.button.Data.ChangerManual = 0;
		GUR.ChengerSta = 0;
		GUS.ChangerFlag = 0;
		it.index = 0;
		it.done = 0;	
		TimerRst(it);
		it.step = 0xa1;					
	}	
	switch(it.step)
	{
		case 0xa1://�ж��Ƿ��Զ�������
			if(BasicPara.MechanicalPara.AutoWideEnable == 1)
			{
				SDC.Run_SetDoorWideAndThick(&SDC);
				it.step = 0xa2;
			}
			else
			{
				it.step = 1;
			}
			break;
		
		case 0xa2:
			if(SDC.Get_SetDoorWideAndThickSta(&SDC) == 0)
			{
				it.step = 1;
			}
			break;
		
		case 1:			
			if(GUR.WorkWhich < 10)	//�ӹ������жϣ�0~9����
			{	
				PARAINIT(GUR.StepShow);//�ӹ�������ʾ
				GUR.StepShow[GUR.WorkWhich] = 1;
				StepMode = (u32)GUS.BasicPara.WorkFile.File[GUR.WorkWhich].mode; 
				if(StepMode < 19)
				{
					StartFuncArr[StepMode]();				
					it.step = 2;
				}
				else
				{
					it.step = 4;
				}				
			}
			else
			{
				it.step = 4;
			}
			break;
		case 2:	//�жϽ���
			if(GetFuncArrSta[StepMode]() == 0)
			{
				it.step = 3;
			}
			break;
			
		case 3://�����1
			if(GUR.RunStatus == RUN)
			{
				GUR.WorkWhich++;		
				it.step = 1;
			}
			break;
			
		case 4:
			if(AxGetsta(X_MOTOR) == 0 && AxGetsta(Y_MOTOR) == 0 && AxGetsta(Z_MOTOR) == 0 && AxGetsta(W_MOTOR) == 0)
			{
				AxRun(Z_MOTOR, ABSMODE, BasicPara.MechanicalPara.MoveSpd, 0);
				it.step = 5;
			}
			break;
			
		case 5:
			if(AxGetsta(Z_MOTOR) == 0)
			{
//				AxRun(W_MOTOR, ABSMODE, BasicPara.MechanicalPara.MoveSpd, 0);
				AxRun(X_MOTOR, ABSMODE, BasicPara.MechanicalPara.MoveSpd, 0);
				AxRun(Y_MOTOR, ABSMODE, BasicPara.MechanicalPara.MoveSpd, 0);
				it.step = 6;		
			}
			break;
		
		case 6:
			if(AxGetsta(X_MOTOR) == 0 && AxGetsta(Y_MOTOR) == 0 && AxGetsta(W_MOTOR) == 0)
			{
				it.step = 7;
			}
			break;
			
		case 7:
			if(LT.XYZWRESETTask.execute == 0)
			{
				Q_Set(Q_Fasten,OFF);
				GUR.WorkWhich = 0;
				
				GUR.ChengerSta = 0;
				GUS.ChangerFlag = 0;
				
				if(GUS.StartCheckPage != 0)GUS.StartCheckPage = 0;
								
				GUR.OpenFileLimit = 0;
				GUW.button.Data.RunCommand = STOP;
				GUS.ProductPara.OneWorkTime = TimerCnt(it)/60000.0;
				GUS.ProductPara.AllWorkTime = GUS.ProductPara.AllWorkTime + GUS.ProductPara.OneWorkTime;
				GUS.ProductPara.NowAwayProduct++;
				PARAINIT(GUR.StepShow);//�ӹ�������ʾ
				it.execute = 0;
				it.step = 0;				
			}
			break;
	}
}
	
void Logic()
{
//    /******���������߼�*******/
	for(u8 i=0; i<19; i++)
	{
		StartFuncArr[i]();//ִ�к�����ѯ
	}
	for(u8 i=0; i<19; i++)
	{
		GetFuncArrSta[i]();//��ȡ����״̬��ѯ
	}
	RunProcess(&LT.AutoRunTask,GUS.BasicPara);//���߼�
	RunMain();//�߼�������ѯ
	AppAlm();//����
	Y_GoHome(&LT.Y_GoHomeTask);//Y��ԭ��
	
			
}


