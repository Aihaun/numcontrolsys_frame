#ifndef __IODEFINE_H
#define __IODEFINE_H
typedef enum	//输出口定义
{
	Q_HingeRet,		//Y1	    //铰链后退
	Q_HingeAdv,		//Y2	    //铰链前进气缸
	Q_Cluth,		//Y3		//离合气缸
	Q_Leveling,		//Y4		//水平测量气缸
	Q_Vertical,		//Y5		//垂直测量气缸
	Q_HingeAir,		//Y6		//铰链吹气
	Q_Lube,			//Y7		//润滑油泵
	Q_FreSpd1,		//Y8		//变频器速度1
	Q_FreSpd2,		//Y9		//变频器速度2
	Q_FreSpd3,		//Y10		//变频器速度3
	Q_FreSpd4,		//Y11		//变频器速度4
	Q_SerFre,		//Y12		//伺服变频器 供电
	Q_Hinge,		//Y13		//铰链接触器
	Q_Slot,			//Y14		//锁槽接触器
	Q_Stair,		//Y15		//锁阶接触器
	Q_Hole1,		//Y16		//锁孔刀1接触器
	Q_Hole2,		//Y17		//锁孔刀2接触器
	Q_Hole1Cyl,		//Y18		//锁孔刀1气缸
	Q_Hole2Cyl,		//Y19		//锁孔刀2气缸
	Q_TableCyl,		//Y20		//工作台升气缸
	Q_Fasten,		//Y21		//压料气缸
	Q_SetToolPower,	//Y22		//对刀0V继电器
	Q_23,
	Q_24,
} OutNum;

typedef enum	//输入口定义
{
    I_X = 0,		//X原点
    I_Y,            //Y原点
	I_Z,            //Z原点
    I_W,            //W原点
    I_Xpos,			//X正限位
    I_Ypos,			//Y正限位
    I_Zpos,			//Z正限
	I_Wpos,         //W正限
	I_Wneg,			//W负限位
	I_Leveling,		//水平测量	9
	I_Vertical,		//垂直测量
	I_Check,		//对刀感应点
	I_Scram,		//急停
	I_Air,			//气压开关
	I_HingePoleOrg,	//铰链杆 原位
	I_HingeReady,	//铰链杆 进位
	I_HoleK1Org,	//锁孔刀1原点
	I_HoleK2Org,	//锁孔刀2原点
	I_Run,			//自动/暂停按钮
	I_Clamp,    	//夹紧/松开按钮	19
	I_TableLift,	//工作台升降
	I_HingeK1Org,	//铰链刀1原点
	I_HingeK2Org,	//铰链刀2原点
	I_HingeK3Org,	//铰链刀3原点
} InPutNum;

typedef enum	//扩展输入口定义
{
	I_HingeK4Org,	//铰链刀4原点
	I_CluthLos,		//离合松开
	I_CluthCon,		//离合合上
	I_HingeMotor1,	//铰链电机1
	I_HingeMotor2,	//铰链电机2
	I_HingeMotor3,	//铰链电机3
	I_FreFault,		//变频器故障
	I_StairAlarm,	//锁阶热继电器
	I_Hole1Alarm,	//锁孔1热继电器
	I_Hole2Alarm,	//锁孔2热继电器
	I_Lube,			//润滑油液位
} EXInputNum;

#endif

