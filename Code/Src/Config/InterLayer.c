#include "InterLayer.h"
#include "can_master.h"

u32 ExIN_Get[4][32] = {0};

void Axis_pos(void);

//ÿ����ѯ�Ľӿں���
void InterLayer()
{
    //��ȡrtcʱ��
    RTC_Get_Time(&GSR.time.hour, &GSR.time.min, &GSR.time.sec, &GSR.time.ampm);	
	//ÿ�θ��������
	AxisConfig(GSS.AxisData,GSS.AxIOconfig);
    //�ײ��ᶯ����
    HZ_AxMotion();
    //modbusͨѶ����
    HZ_ModBus(uart_485, 1);
//    HZ_ModBus(uart_232, 1);
    HZ_ModBus(eth, 1);
    //�����ʱ��
    HZ_TimerThread();
    //��ϵ�ַ���е�flash����
    HZ_FlashOperate();
    //�ײ�㶯����
    HZ_JogOperate(8);
	//���ö���岹
	HZ_MultiAxMotion();
    //��ַ���еı�������
    HZ_Alarm();
    //��ȡ�ᵱǰ״̬
    Axis_pos();
  
}
/**
* @author  yang
* @Description: ��ȡ�ᵱǰ״̬
* @param -- �û��Լ������ڲ���Ҫ��ȡ������
* @param --
* @return --
*/
void Axis_pos()
{
    int i;
    for(i=0; i<PULS_NUM; i++)
    {
        GSR.AxisPosition[i]= HZ_AxGetCurPos(i); 
		
		//���ᵱǰλ������תmm
		GSR.AxisUnitPos[i] = ConvertToUserUnit(i,GSR.AxisPosition[i]);
    }
    for(i = 0; i < 4; i++)
    {
        GSR.AxisEncoder[i] = EnCode_Get32(i);
    }
    for(i = 0; i<PULS_NUM; i++)
    {
        GSR.AXSTA[i] = HZ_AxGetStatus(i);
    }
}

/**
* @author  yang
* @Description: �Դ��㶯���ú�������ִ�е㶯ʱ����
* @param --
* @param --
* @return --
*/
void JogGo(u8 axisnum,s32 pos,u32 spd)
{
    //SetAxisSpdRadio(axisnum,spd);
	SetSpd(axisnum, spd);
	
    if(axisnum<PULS_NUM)	//ֻ���������ֵ㶯����
    {
        if(pos > 0)	//����㶯
        {
			if(GSS.AxIOconfig[axisnum].limitMode == 1||GSS.AxIOconfig[axisnum].limitMode == 3)
			{
				//����ֻ�ܵ�����λ��
				if( HZ_AxGetCurPos(axisnum) + pos > GSS.AxisData[axisnum].SoftMaxLimit)
					pos = GSS.AxisData[axisnum].SoftMaxLimit - HZ_AxGetCurPos(axisnum);
			}
			
            if(AXSTA_ERRSTOP == HZ_AxGetStatus(axisnum))
            {
                //ֻ�����޴���
                if(0 == (0x0fff & HZ_AxGetAxisErr(axisnum)))
                {
                    HZ_AxReset(axisnum);
                    HZ_AxMoveRel(axisnum,pos);
                }
            } else {
                //û�б���,�����˶�
                HZ_AxMoveRel(axisnum,pos);
            }
        }
        else	//����㶯
        {
			if(GSS.AxIOconfig[axisnum].limitMode == 1||GSS.AxIOconfig[axisnum].limitMode == 3)
			{
				//����ֻ���ߵ�0
				if(HZ_AxGetCurPos(axisnum) + pos < 0)
					pos = -HZ_AxGetCurPos(axisnum);
			}
			
            if(AXSTA_ERRSTOP == HZ_AxGetStatus(axisnum))
            {
                //ֻ�����޴���
                if(0 == (0xf0ff & HZ_AxGetAxisErr(axisnum)))
                {
                    HZ_AxReset(axisnum);
                    HZ_AxMoveRel(axisnum,pos);
                }
            } else {
                //û�б���,�����˶�
                HZ_AxMoveRel(axisnum,pos);
            }
        }
    }
}
//ϵͳ�㶯ֹͣ���ú���
void jogstop(u32 axisnum)
{
    HZ_AxStop(axisnum);
}
//ϵͳ������ú���
void joghome(u32 axisnum)
{
    HZ_AxReset(axisnum);
    HZ_AxHome(axisnum);
}
/**
* @author  yang
* @Description: ��չ���������״̬��Modbus���£���Modbus��ѯ��ָ����ַ�����
* @param --
* @param --
* @return --
*/
void ex_inputupdata()
{
    u8 i;
    //��չ��1
    GSR.InputStatus[4] = 0;
    GSR.InputStatus[5] = 0;
    GSR.InputStatus[6] = 0;
    GSR.InputStatus[7] = 0;
    for(i=0; i<32; i++)
    {
       GSR.InputStatus[4] |=(u32) HZ_ExInPutGet(0, i) <<i;
		ExIN_Get[0][i] =  HZ_ExInPutGet(0, i);
    }
    //��չ��2
    GSR.InputStatus[8] = 0;
    GSR.InputStatus[9] = 0;
    GSR.InputStatus[10] = 0;
    GSR.InputStatus[11] = 0;
    for(i=0; i<32; i++)
    {
       GSR.InputStatus[8] |=(u32) HZ_ExInPutGet(1, i) <<i;
		ExIN_Get[1][i] = HZ_ExInPutGet(0, i);
    }
    //��չ��3
    GSR.InputStatus[12] = 0;
    GSR.InputStatus[13] = 0;
    GSR.InputStatus[14] = 0;
    GSR.InputStatus[15] = 0;
    for(i=0; i<32; i++)
    {
       GSR.InputStatus[12] |=(u32) HZ_ExInPutGet(2, i) <<i;
		ExIN_Get[2][i] = HZ_ExInPutGet(0, i);
    }
}

void ex_outputstatusupdata()
{
    u8 i;
    //��չ�����1
    GSW.OutputStatus[4] = 0;
    for(i = 0; i < 32; i ++)
        GSW.OutputStatus[4]	|= (u32) HZ_ExOutPutGet(0,i)<<	i;
    //��չ�����2
    GSW.OutputStatus[8] = 0;
    for(i = 0; i < 32; i ++)
        GSW.OutputStatus[8]	|= (u32) HZ_ExOutPutGet(0, i) << i;
}

void ex_outputupdata()
{
    u8 i;
    //��չ�����1
    for(i = 0; i < 32; i ++)
		HZ_ExOutPutSet(0, i, (GSW.OutputStatus[4]>>i&1));
    //��չ�����2
    for(i = 0; i < 32; i ++)
		HZ_ExOutPutSet(1, i, (GSW.OutputStatus[8]>>i&1));
}

