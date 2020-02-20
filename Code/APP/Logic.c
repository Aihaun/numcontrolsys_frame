/*
 * File: Logic.c
 * File Created: Thursday, 6th February 2020 1:30:00 pm
 * version: v00.01.00 8轴底层
 * Description:用户逻辑
 * Modified By:nyh
 * -----
 * Copyright 2020 - 2020, <<hzzh>>
 */
 
#include "Logic.h"       

/*全局变量做统一处理*/
Task LT = { 0 }; //统一的任务类
//SysData Data= { 0 };   //统一的数据类

 struct HoleConfigPara HoC;
 struct SlotConfigPara SlC;
 struct HingeConfigPara HiC;
 struct ChangerConfigPara ChC;
 struct SetDoorSizeConfigPara SDC;
 struct SetToolConfigPara STC;
		
u32 Q_Contactor[5] 	= {Q_Hinge, Q_Slot, Q_Stair, Q_Hole1, Q_Hole2};//交流接触器				
u32 Q_FreSpd[4]    	= {Q_FreSpd1, Q_FreSpd2, Q_FreSpd3, Q_FreSpd4};//变频器速度	
u32 Q_HoleCyl[2] 	= {Q_Hole1Cyl, Q_Hole2Cyl};//孔刀气缸
u32 I_HoleKOrg[2] 	= {I_HoleK1Org, I_HoleK2Org};//孔刀气缸原点
u32 I_HingeOrg[4] 	= {I_HingeK1Org, I_HingeK2Org, I_HingeK3Org,I_HingeK4Org};//铰链气缸原点

/**
* @author：nyh 20200210
* @Description:	函数指针数组,Start入口
*/
void (*StartFuncArr[19])() =
{                             //mode
	StartHingeUpSide,          //1	上口方铰
	StartHingeUpDiffer,        //2	上口异铰
	StartHingeDownSide,        //3	下口方铰
	StartHingeDownDiffer,      //4	下口异铰
	StartHingeHole,            //5	孔型铰链
	StartHingeCloseSide,       //6	封闭方铰
	
	StartKnifeHole_one,        //7	一刀孔
	StartKnifeCirc_one,        //8	一刀铣圆
	StartKnifeLine_one,        //9	一刀折线
	StartKnifeHole_two,        //10	二刀孔
	StartKnifeCirc_two,        //11	二刀铣圆
	StartKnifeLine_two,        //12	二刀折线
	
	StartLockSlot,             //13	锁槽
	StartLockArcSlot,          //14	圆弧锁槽
	StartLockOrder,            //15	锁阶
	StartLockArcOrder,         //16	圆弧锁阶
	
	StartHingeArc,			   //17	暗铰链
	StartKnifeArc_Level_one,   //18	一刀圆弧
	StartKnifeArc_Level_two,   //19	二刀圆弧
};

/**
* @author：nyh 20200210
* @Description:	函数指针数组,Get获取状态
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
* @author：nyh 20200208
* @Description:	全部逻辑相关函数轮询
* @param --
* @return --
*/
void RunMain() 
{		
	HoC.HoleLoop(&HoC, GUR.WorkWhich); 	//孔函数轮询
	SlC.LockLoop(&SlC); 			//锁槽、锁阶函数轮询
	HiC.HingeLoop(&HiC); 		//铰链函数轮询
	ChC.ChangerOperateLoop(&ChC);	//变频器操作轮询
	SDC.SetDoorSizeLoop(&SDC);		//测量门板尺寸轮询
	STC.SetToolLoop(&STC);			//对刀轮询	
        
}
/**
* @author：nyh 20200210
* @Description:	报警信息
*/
void AppAlm()
{
	u8 i;
	for(i=0; i<5; i++)
	{
		if(ExI_Get(0,I_FreFault+i) == 1)
		{
			AlarmSetBit(4,0,2+i);//变频器故障、热继1锁阶、热继2锁孔1、热继3锁孔2、润滑油液位
			WorkEnd();
		}
	}
	if(I_Get(I_Air) == 1)
	{
		AlarmSetBit(2,0,0);//气压过低
		WorkEnd();
	}
}
/**
* @author：nyh 20200210
* @Description:	加工终止
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
	for(i = 0; i < GPO_NUM; i++)  //初始化 输出口
	{
		OutPut_SetSta(i, OFF);
	}
	//所有流程结束
	PARAINIT(LT);	
	PARAINIT(HoC.TaskFunc);
	PARAINIT(SlC.TaskFunc);
	PARAINIT(HiC.TaskFunc);
	PARAINIT(STC.TaskFunc);
	PARAINIT(SDC.TaskFunc);
	PARAINIT(ChC.TaskFunc);
}
/**
* @author：nyh 20191203
* @Description:	Y轴回原点
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
			
		case 2://离合气缸松开
			if(AxGetsta(Y_MOTOR) == 0)
			{
				Q_Set(Q_Cluth,OFF);
				TimerRst(it);
				it.step = 3;
			}
			break;
		
		case 3://判断离合气缸松开到位
			if(TimerCnt(it) <= 3000)
			{
				if(ExI_Get(0,I_CluthLos) == 0)
				{
					it.step = 4;
				}
			}
			else
			{
				AlarmSetBit(2,1,3);//离合气缸松开异常
				PARAINIT(it);
			}
			break;
			
		case 4://Y轴回零后偏移3mm
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
* @author：nyh 20191025
* @Description:	主调函数
* @param --
* @return --
*/
void RunProcess(LogicParaDef *t, BasicParaDef BasicPara)
{
	u8 i;
	static u32 StepMode = 0;
	if(BasicPara.MechanicalPara.AutoWideEnable == 1)
	{   //自动测量的宽、厚
		BasicPara.MechanicalPara.DoorThick = GUR.SetDoorThick;
		BasicPara.MechanicalPara.DoorWide  = GUR.SetDoorWide;
	}
	else
	{	//人工量的宽、厚
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
			Q_Set(Q_FreSpd[i],OFF);//变频速度关
		}
		for(i=0; i<5; i++)
		{
			Q_Set(Q_Contactor[i],OFF);//交流接触器关
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
		case 0xa1://判断是否自动测宽、测厚
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
			if(GUR.WorkWhich < 10)	//加工步骤判断，0~9结束
			{	
				PARAINIT(GUR.StepShow);//加工步骤显示
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
		case 2:	//判断结束
			if(GetFuncArrSta[StepMode]() == 0)
			{
				it.step = 3;
			}
			break;
			
		case 3://步骤加1
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
				PARAINIT(GUR.StepShow);//加工步骤显示
				it.execute = 0;
				it.step = 0;				
			}
			break;
	}
}
	
void Logic()
{
//    /******工程运行逻辑*******/
	for(u8 i=0; i<19; i++)
	{
		StartFuncArr[i]();//执行函数轮询
	}
	for(u8 i=0; i<19; i++)
	{
		GetFuncArrSta[i]();//获取函数状态轮询
	}
	RunProcess(&LT.AutoRunTask,GUS.BasicPara);//主逻辑
	RunMain();//逻辑函数轮询
	AppAlm();//报警
	Y_GoHome(&LT.Y_GoHomeTask);//Y回原点
	
			
}


