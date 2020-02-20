/*
 * File: AppInit.c
 * File Created: Tuesday, 9th October 2018 2:43:29 pm
 * version:v1.1
 * Description:Ӧ�ó����ʼ������
 * param:
 * Modified By:yang
 * -----
 * Copyright 2018 - 2018 <<hzzh>>, <<hzzh>>
 */

#include "AppInit.h" 

//��������
GlobalDataDef GlobalData = {0}; //�����û�ͨѶ���ݿ�
u8 uart_sendbuf[2][300];        //����ͨѶ���պͷ��ͻ���
u8 uart_recvbuf[2][300];
u8 eth_txbuf[300];
u8 eth_rxbuf[300];
//u8	EXI_ID[EXINUM] = {0};     //��չI��ID  
//u8	EXQ_ID[EXQNUM] = {1};     //��չQ��ID
void ConfigInit()
{
//    u16 limitMode;		//��λģʽ��0 û��λ 1 �����λ 2 Ӳ����λ 3 ��Ӳ����
//    u16 Poslimit;    		//����λ�ź�
//    u16 Poslimitlev;    	//����λ�źŵ�ƽ
//    u16 Neglimit;       	//����λ�ź�
//    u16 Neglimitlev;    	//������λ�źŵ�ƽ
//    u16 OrgNum;         	//ԭ���ź�
//    u16 Orglev;			//ԭ���źŵ�ƽ
//    u16 HomeMode;			//����ģʽ
//    u16 alarmmode;		//�ᱨ����ƽ:0���͵�ƽ��Ч 1���ߵ�ƽ��Ч �������ᱨ����Ч
//	u8 i;
//	for(i=0; i<PULS_NUM; i++) //PULS_NUM = 8
//	{
//		GSS.AxIOconfig[i].limitMode = 2;
//		GSS.AxIOconfig[i].Poslimit = 0;  
//		GSS.AxIOconfig[i].Poslimitlev = 0;
//		GSS.AxIOconfig[i].Neglimit = 0;	
//		GSS.AxIOconfig[i].Neglimitlev = 0;
//		GSS.AxIOconfig[i].OrgNum = i;
//		GSS.AxIOconfig[i].Orglev = 0;
//		GSS.AxIOconfig[i].HomeMode = GOHOMETYPE1;
//		GSS.AxIOconfig[i].alarmmode = 2;
//		
//	}

		GSS.AxIOconfig[0].limitMode = 0;
		GSS.AxIOconfig[0].Poslimit = 4;  
		GSS.AxIOconfig[0].Poslimitlev = 0;
		GSS.AxIOconfig[0].Neglimit = 0;	
		GSS.AxIOconfig[0].Neglimitlev = 0;
		GSS.AxIOconfig[0].OrgNum = 0;
		GSS.AxIOconfig[0].Orglev = 0;
		GSS.AxIOconfig[0].HomeMode = GOHOMETYPE1;
		GSS.AxIOconfig[0].alarmmode = 2;
		
		GSS.AxIOconfig[1].limitMode = 0;
		GSS.AxIOconfig[1].Poslimit = 5;  
		GSS.AxIOconfig[1].Poslimitlev = 0;
		GSS.AxIOconfig[1].Neglimit = 1;	
		GSS.AxIOconfig[1].Neglimitlev = 0;
		GSS.AxIOconfig[1].OrgNum = 1;
		GSS.AxIOconfig[1].Orglev = 0;
		GSS.AxIOconfig[1].HomeMode = GOHOMETYPE1;
		GSS.AxIOconfig[1].alarmmode = 2;
		
		GSS.AxIOconfig[2].limitMode = 0;
		GSS.AxIOconfig[2].Poslimit = 6;  
		GSS.AxIOconfig[2].Poslimitlev = 0;
		GSS.AxIOconfig[2].Neglimit = 2;	
		GSS.AxIOconfig[2].Neglimitlev = 0;
		GSS.AxIOconfig[2].OrgNum = 2;
		GSS.AxIOconfig[2].Orglev = 0;
		GSS.AxIOconfig[2].HomeMode = GOHOMETYPE1;
		GSS.AxIOconfig[2].alarmmode = 2;
		
		GSS.AxIOconfig[3].limitMode = 0;
		GSS.AxIOconfig[3].Poslimit = 7;  
		GSS.AxIOconfig[3].Poslimitlev = 0;
		GSS.AxIOconfig[3].Neglimit = 8;	
		GSS.AxIOconfig[3].Neglimitlev = 0;
		GSS.AxIOconfig[3].OrgNum = 3;
		GSS.AxIOconfig[3].Orglev = 0;
		GSS.AxIOconfig[3].HomeMode = GOHOMETYPE1;
		GSS.AxIOconfig[3].alarmmode = 2;

}
/**
* @author��nyh 20200210
* @Description:	��ʼ���߼���������
*/
void ShapeConfigInit()
{ 
	HoleConfig(&NewHole, &GUS.BasicPara.workPara.HoleSoftPara,1,1,1,1,1,1,1,1,1,1,1,1,1); 
	SlotConfig(&NewSlot, &GUS.BasicPara.workPara.SlotSoftPara,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1); 
	HingeConfig(&NewHinge, &GUS.BasicPara.workPara.HingeSoftPara,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
}

void AppInit()
{
    u8 i;
    //���õ�ַ�����modbus
    init_config(&GlobalData,GSR.ErrorCode,&GlobalData.SpaceType.Save,GLOBALDATALEN,USERWRITELEN,USERREADLEN,USERSAVELEN);
//    if(HZ_Data_Read() == 0)
//	{
//		HZ_BkData_Write();
//	}
//	else if(HZ_BkData_Read() !=0)
//	{
//		AlarmSetBit(5,0,1);//flash���ݶ�����
//	}
	
	//����汾
	GSR.SoftWare_Ver[0] = 1;
	GSR.SoftWare_Ver[1]	= 2;
	GSR.SoftWare_Ver[2]	= 19;
	
    for(i = 0; i < GPO_NUM; i++)  //��ʼ�� �����
        OutPut_SetSta(i, OFF);
    for(i = 0; i < PULS_NUM; i++)  //���ʹ��
        EN_SetSta(i, OFF);
				
	
    //��ʼ��������
    AxisConfig(GSS.AxisData,GSS.AxIOconfig);
	ConfigInit();
	
	//��ʼ���߼���������
	ShapeConfigInit();
	
    GUR.HaveToReset = 1;
	
	GUW.JogData.Data.JogSpd = 1;//�㶯�ٶȱ���
	GUW.button.Data.MeasureAccSpd = 0;
	GUW.button.Data.ChangerManual = 0;
	GUS.StartCheckPage = 0;
	GUS.CheckPage = 0;
	GUS.BasicPara.MechanicalPara.AutoWideEnable = 0;
	GUS.ChangerFlag = 0;
	GUS.StartOrStopButton = 0;
	PARAINIT(GUR.StepShow);
	GUW.JogData.Data.Joglevel = 0;
}
