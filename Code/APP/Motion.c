#include "Motion.h"

void Motion()
{
	u8 i;
	if(GUR.RunStatus == STOP || GUW.button.Data.Motion == 9)
	{
		switch(GUW.button.Data.Motion)
		{
			case 1://������ԭ��  �����Xλ��	
				if(AxGetsta(X_MOTOR) == 0)
				{
					AxRun(X_MOTOR, ABSMODE, GUS.BasicPara.MechanicalPara.moveFastSpd , GUS.BasicPara.CheckPara.Hinge.hingeKLenX);
				}
				break;
			
			case 2://����1���
				break;
			
			case 3://����2���
				break;
			
			case 4://���۵��
				break;
			
			case 5://�Զ����
				break;
			
			case 6://ˮƽ����ֱ�Ե� 				
				if(STC.Get_SetToolSta(&STC) == 0 && AxGetsta(X_MOTOR) == 0 && AxGetsta(Y_MOTOR) == 0 && AxGetsta(Z_MOTOR) == 0)
				{ 
					STC.Run_SetTool(&STC);
				}
				break;
			
			case 7://�Ե�ֹͣ
				for(i = 0; i<8; i++)
				{
					HZ_AxStop(i);
				}
				for(i = 0; i < GPO_NUM; i++)  //��ʼ�� �����
				{
					OutPut_SetSta(i, OFF);
				}
				
				PARAINIT(STC.TaskFunc.SetLevelTool);
				PARAINIT(STC.TaskFunc.SetVerticalTool);
				PARAINIT(STC.TaskFunc.SetTool);
				PARAINIT(SDC.TaskFunc.SetDoorWideAndThick);
				GUR.HaveToReset = 1;
				break;
			
			case 8://
				break;
			
			case 9://Y ��ԭ��
				if(LT.Y_GoHomeTask.execute == 0 && AxGetsta(Y_MOTOR) == 0 && STC.Get_SetToolSta(&STC) == 0 && LT.CluthManualTask.execute == 0)
				{
					LT.Y_GoHomeTask.execute = 1;
				}
				break;
				
		}
		GUW.button.Data.Motion = 0;
	}
	else
	{
		GUW.button.Data.Motion = 0;
	}
	

}


