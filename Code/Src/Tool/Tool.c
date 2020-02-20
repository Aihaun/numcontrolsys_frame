#include "TOOL.H"
/********************************************************/

/**
* @author 19/02/19  yang
* @Description: 每小时产出
* @param -- 产量
* @param -- 时间 （毫秒）
* @return -- units per hour(通常使用时是要除1000，把单位变成k)
*/
float UPH(u32 time,u32 products)
{
    return (float)products * 1000 * 3600 / (float)time;
}
/**
* @author 19/02/19  yang
* @Description: 单位换算 毫米转脉冲
* @param -- num 轴号
* @param -- MM 毫米
* @return -- 脉冲数
*/
s32 ConvertToMachineUnit(u32 num,float MM)
{
	return   MM *GSS.Conversion[num].PPR / GSS.Conversion[num].MPR;
}
/**
* @author 19/02/19  yang
* @Description: 单位转换 脉冲转毫米
* @param --
* @param --
* @return --
*/
float ConvertToUserUnit(u32 num,s32 pulse)
{
    return (float)GSS.Conversion[num].MPR * pulse / (float)GSS.Conversion[num].PPR;
}
/**
* @author  yang 2019/3/8
* @Description: 速度换算
* @param -- 脉冲速度转成实际转速
* @param --
* @return --
*/

/*****************************************************************/

/**
* @author  yang 2019/3/11
* @Description: 检查轴到位 
* @param -- num 需要检查的轴数
* @param --
* @return --
*/
s32 Check_AxisStatu(u8 cnt)
{
    u8 i;
    for(i = 0; i<cnt; i++)
    {
        if(HZ_AxGetStatus(i)!=0)
        {
            return -1;
        }
    }
    return 0;
}


