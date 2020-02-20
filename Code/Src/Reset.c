#include "reset.h"

void Reset(LogicParaDef *t)
{
    if(GUR.RunStatus == D_RESET)
    {
		switch(it.step) 
		{
			
			case 0://先判断离合气缸状态，锁紧时Y轴要走到离合位置松开再回零,否则直接回零
//				Data.workNum  = 0;
				GUW.JogData.Data.Joglevel = 0;
				GUW.button.Data.MeasureAccSpd = 0;
				GUW.button.Data.ChangerManual = 0;
				GUW.button.Data.CluthCylMotion = 0;
				LT.CluthManualTask.done = 0; 
				GUS.ChangerFlag = 0;
				GUR.ChengerSta = 0;
				GUS.StartCheckPage = 0;
				GUS.StartOrStopButton = 0;
				GUR.OpenFileLimit = 0;
				GSW.ClearAlarm = 1;
			
				PARAINIT(LT);
			
				PARAINIT(GUR.StepShow);//加工步骤显示
				HZ_AxReset(X_MOTOR);
				HZ_AxReset(Y_MOTOR);
				HZ_AxReset(Z_MOTOR);
				HZ_AxReset(W_MOTOR);
				if(ExI_Get(0,I_CluthCon) == 0)
				{
					AxRun(Y_MOTOR, ABSMODE, GUS.BasicPara.MechanicalPara.moveFastSpd , GUS.BasicPara.CheckPara.Hinge.cluthPosY);
					it.step = 1;
				}
				else
				{
					it.step = 3;
				}
				break;
				
			case 1://离合气缸松开
				if(AxGetsta(Y_MOTOR) == 0)
				{
					Q_Set(Q_Cluth,OFF);
					TimerRst(it);
					it.step = 2;
				}
				break;
			
			case 2://判断离合气缸松开到位
				if(TimerCnt(it) <= 3000)
				{
					if(ExI_Get(0,I_CluthLos) == 0)
					{
						it.step = 3;
					}
				}
				else
				{
					AlarmSetBit(2,1,3);//离合气缸松开异常
					PARAINIT(it);
					GUW.button.Data.RunCommand = STOP;
				}
				break;
			
		case 3://所有输出复位
			for(int i = 0; i < GPO_NUM; i++) 
				OutPut_SetSta(i, OFF);
			TimerRst(it);
			it.step = 4;
			break;
		
		case 4://判断气缸到位
			if(TimerCnt(it) >= 2000)
			{
				if(ExI_Get(0,I_CluthLos) == 0 && I_Get(I_HingeK1Org) == 0 && I_Get(I_HingeK2Org) == 0 && I_Get(I_HingeK3Org) == 0
					  && I_Get(I_HoleK1Org) == 0 && I_Get(I_HoleK2Org) == 0 && ExI_Get(0,I_HingeK4Org) == 0)//&& ExI_Get(0,I_HingeK4Org) == 0
				{
					LT.XYZWRESETTask.execute = 1; 
					it.step = 5;
				}
				else
				{
					if(ExI_Get(0,I_CluthLos) == 1)
					{
						AlarmSetBit(2,1,3);//离合气缸松开异常
					}
					if(I_Get(I_HoleK1Org) == 1)
					{
						AlarmSetBit(2,1,4);//锁孔刀1上异常
					}
					if(I_Get(I_HoleK2Org) == 1)
					{
						AlarmSetBit(2,1,5);//锁孔刀2上异常
					}
					if(I_Get(I_HingeK1Org) == 1)
					{
						AlarmSetBit(2,1,6);//铰链刀1回原位异常
					}
					if(I_Get(I_HingeK2Org) == 1)
					{
						AlarmSetBit(2,1,7);//铰链刀2回原位异常
					}
					if(I_Get(I_HingeK3Org) == 1)
					{
						AlarmSetBit(2,1,8);//铰链刀3回原位异常
					}
					if(ExI_Get(0,I_HingeK4Org) == 1)
					{
						AlarmSetBit(2,1,9);//铰链刀4回原位异常
					}
					PARAINIT(it);
					GUW.button.Data.RunCommand = STOP;
				}
			}
			break;
			
		case 5://判断轴回零完成
			if(LT.XYZWRESETTask.execute == 0 && LT.XYZWRESETTask.done == 1)
			{
				it.step = 6;
			}
			break;
			
		case 6:
			PARAINIT(it);
			GSW.ClearAlarm = 1;	
			GUR.HaveToRepower = 0;
			GUR.HaveToReset = 0;
			
			GUW.button.Data.RunCommand = STOP;
			break;
		}
    }
}

/**
* @author： 20191226 nyh
* @Description:  xyzW复位
* @param --
* @param --
* @return --
*/
void XYZW_Reset(LogicParaDef *t)
{
   FUNC_ENTER
    switch(it.step)
    {
    case 1:
		LT.Ax_GoHomeTask[Z_MOTOR].execute = 1;
		it.step = 2;
        break;
	case 2:
		if(LT.Ax_GoHomeTask[Z_MOTOR].execute == 0)
		{
			LT.Ax_GoHomeTask[X_MOTOR].execute = 1;
			LT.Ax_GoHomeTask[Y_MOTOR].execute = 1;
//			LT.Ax_GoHomeTask[W_MOTOR].execute = 1;
			it.step = 3;
		}
		break;
	case 3:
		if(LT.Ax_GoHomeTask[X_MOTOR].execute == 0 && LT.Ax_GoHomeTask[Y_MOTOR].execute == 0 && LT.Ax_GoHomeTask[W_MOTOR].execute == 0)
		{
			it.step = 4;
		}
		break;
	case 4:
		if(Check_AxisStatu(4) == 0)
		{
			PARAINIT(it);
			it.done = 1;
		}
		break;

    }
}


