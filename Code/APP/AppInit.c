/*
 * File: AppInit.c
 * File Created: Tuesday, 9th October 2018 2:43:29 pm
 * version:v1.1
 * Description:应用程序初始化配置
 * param:
 * Modified By:yang
 * -----
 * Copyright 2018 - 2018 <<hzzh>>, <<hzzh>>
 */

#include "AppInit.h" 

//变量声明
GlobalDataDef GlobalData = {0}; //定义用户通讯数据库
u8 uart_sendbuf[2][300];        //定义通讯接收和发送缓存
u8 uart_recvbuf[2][300];
u8 eth_txbuf[300];
u8 eth_rxbuf[300];
//u8	EXI_ID[EXINUM] = {0};     //扩展I板ID  
//u8	EXQ_ID[EXQNUM] = {1};     //扩展Q板ID
void ConfigInit()
{
//    u16 limitMode;		//限位模式：0 没限位 1 软件限位 2 硬件限位 3 软硬都限
//    u16 Poslimit;    		//正限位信号
//    u16 Poslimitlev;    	//正限位信号电平
//    u16 Neglimit;       	//负限位信号
//    u16 Neglimitlev;    	//负限限位信号电平
//    u16 OrgNum;         	//原点信号
//    u16 Orglev;			//原点信号电平
//    u16 HomeMode;			//回零模式
//    u16 alarmmode;		//轴报警电平:0：低电平有效 1：高电平有效 其他：轴报警无效
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
* @author：nyh 20200210
* @Description:	初始化逻辑函数配置
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
    //配置地址表完成modbus
    init_config(&GlobalData,GSR.ErrorCode,&GlobalData.SpaceType.Save,GLOBALDATALEN,USERWRITELEN,USERREADLEN,USERSAVELEN);
//    if(HZ_Data_Read() == 0)
//	{
//		HZ_BkData_Write();
//	}
//	else if(HZ_BkData_Read() !=0)
//	{
//		AlarmSetBit(5,0,1);//flash数据读错误
//	}
	
	//软件版本
	GSR.SoftWare_Ver[0] = 1;
	GSR.SoftWare_Ver[1]	= 2;
	GSR.SoftWare_Ver[2]	= 19;
	
    for(i = 0; i < GPO_NUM; i++)  //初始化 输出口
        OutPut_SetSta(i, OFF);
    for(i = 0; i < PULS_NUM; i++)  //轴口使能
        EN_SetSta(i, OFF);
				
	
    //初始化轴配置
    AxisConfig(GSS.AxisData,GSS.AxIOconfig);
	ConfigInit();
	
	//初始化逻辑函数配置
	ShapeConfigInit();
	
    GUR.HaveToReset = 1;
	
	GUW.JogData.Data.JogSpd = 1;//点动速度比例
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
