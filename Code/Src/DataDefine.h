#ifndef _DATADEFINE_H_
#define _DATADEFINE_H_
#include "interlayer_config.h"
#include "logicdata.h"   
#include "lock.h"

#include "JogClass.h"  
#include "HoleShape.h"   
#include "SlotShape.h" 
#include "HingeShape.h"

#define DATACHAECK 0x01237654
#define SYSREADLEN 1000
#define USERREADLEN 1000
#define READLEN (SYSREADLEN + USERREADLEN)

#define SYSWRITELEN 1000
#define USERWRITELEN 1000
#define WRITELEN (SYSWRITELEN + USERWRITELEN)

#define SYSSAVELEN 4000
#define USERSAVELEN 4000
#define SAVELEN (SYSSAVELEN + USERSAVELEN + 4)

#define GLOBALDATALEN (READLEN + WRITELEN + SAVELEN)

#define MAXAXISNUM 50
#define LOCALAXISNUM 12
#define INPUTSTARTADDR 310
#define INPUTENDADDR 389
#define OUTPUTSTARTADDR 1020
#define OUTPUTENDADDR 1099


/************************************************************************/
/* 此处之后的系统区不允许更改，用户只能更改用户区数据		           */
/************************************************************************/

/************业务逻辑参数***********************/

/***************文件定义********************/
//单文件	
//孔类型(mode)  
//	0无		     1上口方铰 	 2上口异铰  		3下口方铰   			 4下口异铰     5孔型铰链      6封闭方铰
//	7(1刀孔      8(1刀铣圆 	 9(1刀折线  		10(2刀孔    		11(2刀铣圆     12(2刀折线     13锁槽
//	14圆弧锁槽 	 15锁阶       16圆弧锁阶	   17圆弧铰链（暗铰链）   18（1刀圆弧    19（2刀圆弧
//				
typedef struct
{
	float mode;			//1618  //4208 孔类型	
	float SizePara[19];//原17个
} FileParaDef;	//每个类型占18个参数



//编辑文件结构(触摸屏编辑)
typedef struct
{
	char filname[10][16];	//10*4 1520 - 1599 
	char newfilename[16];	//1600-1607
	u32 workfilenum[4];		//1608-1615		//备用  [0]产品编号  [1]程序列表序号0~9
	
	u32 index;		//1616 当前编辑文件 的编号 0-9
	FileParaDef newFilePara;	//1618-1657
} FileDef;	//最多20个类型


//当前加工文件
typedef struct
{
	char workfilename[16];	//4200-4207
	FileParaDef File[20];	//4208-5006   400个
} WorkFileDef;

/***************文件定义********************/


/***********常量参数单独声明**************/

//对刀 铰链参数
typedef struct
{
	struct
	{
		float slotKnifeX;	//槽刀对刀X实际值	4000
		float slotKnifeZ;	//槽刀对刀Z实际值
		float holeKnifeY;	//孔刀对刀到板边Y值
		float checkLumpH;	//校刀块高度
		float slotKLenY;	//槽刀到校刀块Y		4008
		float holeK1LenZ;	//孔刀1到校刀块Z
		float stairKLenY;	//阶刀到校刀块Y
		float holeK2LenZ;	//孔刀2到校刀块Z
		float horizonLenY;	//水平杆到校刀块Y
		float verticalLenZ;	//垂直杆到校刀块Z
		float checkSpdFast;	//对刀快速度
		float checkSpdslow;	//对刀慢速度
	}Check;	//对刀参数
	struct
	{
		float cluthPosY;		//离合位置Y			4024
		float hingeKLenW;		//铰链刀W台面原点
		float hingeKLenX;		//铰链刀X工作原点
	}Hinge;	//铰链加工固定位置
	
	float res[10];
}CheckParaDef;	//25 对刀/铰链参数

//加工参数
typedef struct
{	
	HoleSoftDef  HoleSoftPara;
	SlotSoftDef  SlotSoftPara; 
	HingeSoftDef HingeSoftPara;
	float res[10];
}WorkParaDef;	//40 加工参数

//机械参数
typedef struct 
{	
	struct
	{
		float stairKOffset;	//阶刀X偏移槽刀		4110
		float holeK1Offset;	//孔1刀X偏移槽刀
		float holeKSpace;	//孔1到和孔2刀X间距
		float horizonOffset;//水平杆X偏移槽刀
		float verticalOffset;//垂直杆X偏移槽刀
	}X;	//X参考
	
	struct
	{
		float holeKLen;		//孔刀1、2距离水平杆伸出点Y		4120
		float verticalLen;	//垂直杆距离水平杆伸出点Y
		float WbroadsideLen;//W侧板边 距离水平杆伸出点Y
	}Y;	//Y参考
	
	struct
	{
		float slotKLen;		//槽刀中心到台面Z		4126
		float stairKLen;	//阶刀Z偏移槽刀
	}Z;	//Z参考
	
	float moveFastSpd;		//移动快速度 	4130		
	float DoorThick;		//门板厚度 		4132
	float DoorWide;			//门板宽度		4134
	float checkLumpThick;	//校刀块厚度Y	4136
	float verti_LenZ;		//垂直杆伸出点到台面Z		4138
	float HMI_DoorThick;	//触摸屏设定门板厚度 	4140
	float HMI_DoorWide;		//触摸屏设定门板宽度		4142
	float MoveSpd;			//移动快速度
	float slotKLenX;		//X在工件坐标0时，槽刀与靠山距离
	u32 AutoWideEnable;	//自动测宽使能	4072
	float AutoThickEnable;	//自动测厚使能
	float res[14];
	
}MechanicalParaDef; //35  机械参数

typedef struct
{
	CheckParaDef CheckPara;				//4000 - 4048
	WorkParaDef workPara;				//4050 - 4128
	MechanicalParaDef MechanicalPara;	//4130 - 4198	
	WorkFileDef WorkFile;				//4200 - 5006    808个
}BasicParaDef;	//共100个参数

//产能参数
typedef struct
{
	s32 NowAwayProduct;		//当前产量	4572
	s32 AtleProduct;		//总产量		4574
	float OneWorkTime;		//单个工时	4576
	float AllWorkTime;		//总工时		4578
	
}ProductParaDef;


//*******************************************************************************//

typedef struct
{
    u8 hour;		//范围0-23
    u8 min;			//0-59
    u8 sec;			//0-59
    u8 ampm;		//这个值没用，禁止使用
} Time;

typedef struct
{
    s32 StartSpeed;	//初速度
    s32 Acctime;	   //加速时间
    s32 RunSpeed;	  //点动速度
    s32 Dectime;	   //减速时间
    s32 EndSpeed;	  //末速度
    s32 HomeSpeedFast; //回原点快速速度
    s32 HomeSpeedSlow; //回原点慢速速度
    s32 HomeOffset;	//回原点偏移坐标
    s32 SoftMinLimit;  //软负限位
    s32 SoftMaxLimit;  //软正限位
} AxisDef;
typedef struct
{
    u32 PPR;	//每转脉冲数
    float MPR;	//每转毫米__导程
} AxisConversion;
typedef struct
{
    u16 limitMode;		//限位模式：0 没限位 1 软件限位 2 硬件限位 3 软硬都限
    u16 Poslimit;    	//限位信号
    u16 Poslimitlev;    //限位信号电平
    u16 Neglimit;       //限位信号
    u16 Neglimitlev;    //限位信号电平
    u16 OrgNum;         //原点信号
    u16 Orglev;			//原点信号电平
    u16 HomeMode;		//回零模式
    u16 alarmmode;		//轴报警电平:0：低电平有效 1：高电平有效 其他：轴报警无效
    u16 res;			//
} AxisIOConfig;

typedef union
{
    u8 Data_8[GLOBALDATALEN];
    u16 Data_16[GLOBALDATALEN / 2];
    struct
    {
        struct //READ ADDR 0-999
        {
            union //SYS READ ADDR 0-499
            {
                u16 Data_16[SYSREADLEN / 2];
                struct
                {
                    u32 HardWare_Ver[10];		  //0-19	硬件版本
                    u32 SoftWare_Ver[10];		  //20-39	软件版本
                    u32 res[5];                   //40-49
                    u16 AXSTA[MAXAXISNUM];		  //50-99	轴状态
                    float AxisUnitPos[MAXAXISNUM];  //100-199	轴当前用户单位位置
                    s32 AxisPosition[MAXAXISNUM]; //200-299	轴当前位置
                    u32 AxisEncoder[5];			  //300-309	轴当前状态
                    u32 InputStatus[40];		  //310-389	输入口状态
                    u32 ErrorCode[20];			  //390-	错误码
                    u32 ErrorLevel;				  //430-	错误等级
                    Time time;	//432	rtc 时间
                    Date date;	//434	rtc 日期
                    u32 CID[2];	//436 438 本机生成的客户随机码

                } Data;
            } Sys;

            union //USER READ ADDR 500-999
            {
                u16 Data_16[USERREADLEN / 2];
                struct
                {
                    u32 RunStatus; 		//500
                    u32 HaveToReset;	//502
                    u32 HaveToRepower;	//504
					u32 IndicateShow;	//506  报警指示灯
					u16 StepShow[16];	//508-523  加工步骤状态显示	
					float SetDoorWide;    //524	自动测门宽
					float SetDoorThick;	//526   自动测门厚
					u32 ChengerSta;		//528   变频器状态
					u32 OpenFileLimit;	//530   打开文件限制	0：允许打开	1：禁止打开
					u32 WorkWhich;		//532 	加工到哪个
				} Data;
            } User;
        } Read;

        struct //WRITE ADDR 1000-1999
        {
            union //SYS WRITE ADDR 1000-1499
            {
                u16 Data_16[SYSWRITELEN / 2];
                struct
                {
                    u32 res[10];		  	//1000-1019 保留
                    u32 OutputStatus[40]; 	//1020-1099	输出口状态
                    u32 FlashOperate;	 	//1100-	Flash操作
                    u32 FilesOperate;	 	//1102-	文件操作
                    u32 FramOperate;	  	//1104-	铁电操作
                    u32 JogMode;		  	//1106-	点动模式
                    u32 JogPositionLevel; 	//1108-	点动行程级别
                    u32 JogPosition;	  	//1110-	点动设定行程
                    u32 JogForward[2];		//1112-1115	正向点动
                    u32 JogBackward[2];   	//1116-1119	反向点动
                    u32 JogGohome[2];	 	//1120-1123	点动回零
                    u32 JogStop[2];		  	//1124-1127	点动立即停止
                    u32 jogSpd;			  	//1128  轴点动速度
                    u32 ClearAlarm;		  	//1130-	清除错误
                    struct
                    {
                        u32 refreshId;	//	1132 随机数刷新
                        s32 decode[4];	//1134 1136 1138 1140  4个解锁码 *6个数 一共24个数
                    } LockPara;
                    //end
                    GoPosPara AxisMove[PULS_NUM]; //1142
                } Data;
            } Sys;

            union //USER WRITE ADDR 1500-1999
            {
                u16 Data_16[USERWRITELEN / 2];
                struct
                {
                    union
                    {
                        u32 Data_32[10];
                        struct
                        {
                            u32 RunCommand;		//1500
							u32 TeachCMD;		//1502
							u32 page;			//1504
							u32 Motion;			//1506
							u32 MeasureAccSpd;	//1508  对刀加速
							u32 ChangerManual;	//1510	变频手动
							u32 CluthCylMotion;	//1512  离合气缸操作
                        } Data;
                    } button;//1500+20
					
					FileDef EditFile;		//1520-1656	加工文件
					
					union //1654-1672   以下地址全部要调整
					{
						u32 Data_32[10];
						struct
						{
							float	JogSpd;		//1654
							float	JogUnitPos;	//1656
							u32	JogForward;		//1658
							u32	JogBackward;	//1660
							u32	JogHome;		//1662
							u32	JogStop;		//1664
							u32 Joglevel;		//1666
							u16 JogContinuForward;		//1668
							u16 JogContinuBackward;		//1669
							u32 a[2];			//1670  1672
						}Data;
					}JogData;
					
                } Data;
            } User;
        } Write;

        struct //SAVE ADDR 2000-
        {
            union //SYS SAVE ADDR 2000-3999
            {
                u16 Data_16[SYSSAVELEN / 2];
                struct
                {
                    AxisDef AxisData[MAXAXISNUM]; //2000-2999	50个轴，每个占20个寄存器
                    AxisConversion Conversion[MAXAXISNUM]; //3000 -3199 每转脉冲数
                    AxisIOConfig AxIOconfig[MAXAXISNUM];   //3200 - 3699
                    lockdataflashsave LockDate;	//3700 保存设置的锁机日期
                } Data;
            } Sys;

            union //USER SAVE ADDR 4000-5999
            {
                u16 Data_16[USERSAVELEN / 2];
                struct
                {					
					BasicParaDef BasicPara; 	//4000-5006
					
					////以下地址全部调整
					s32 ChangerFlag;			//4568 0: 空闲 1：忙
					s32 ChangerManuOFFIndx;		//4570 手动关变频序号
					ProductParaDef ProductPara; //4572-4578
					s32 StartOrStopButton;		//4580 启动/停止
					s32 ResetT;					//4582 待用
					s32 CheckPage;				//	   待用
					s32 StartCheckPage;			//4586 启动设备后自动切换监控界面编号
					s32 Debug;					//4588
					s32 ProdNum[100];			//4590-4688  产品工程编号显示
                } Data;
            } User;
        } Save;
        u32 Check;
    } SpaceType;
} GlobalDataDef;
extern GlobalDataDef GlobalData;

#define GSR GlobalData.SpaceType.Read.Sys.Data
#define GSW GlobalData.SpaceType.Write.Sys.Data
#define GSS GlobalData.SpaceType.Save.Sys.Data
#define GUR GlobalData.SpaceType.Read.User.Data
#define GUW GlobalData.SpaceType.Write.User.Data
#define GUS GlobalData.SpaceType.Save.User.Data

#endif
