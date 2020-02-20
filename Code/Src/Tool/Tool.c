#include "TOOL.H"
/********************************************************/

/**
* @author 19/02/19  yang
* @Description: ÿСʱ����
* @param -- ����
* @param -- ʱ�� �����룩
* @return -- units per hour(ͨ��ʹ��ʱ��Ҫ��1000���ѵ�λ���k)
*/
float UPH(u32 time,u32 products)
{
    return (float)products * 1000 * 3600 / (float)time;
}
/**
* @author 19/02/19  yang
* @Description: ��λ���� ����ת����
* @param -- num ���
* @param -- MM ����
* @return -- ������
*/
s32 ConvertToMachineUnit(u32 num,float MM)
{
	return   MM *GSS.Conversion[num].PPR / GSS.Conversion[num].MPR;
}
/**
* @author 19/02/19  yang
* @Description: ��λת�� ����ת����
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
* @Description: �ٶȻ���
* @param -- �����ٶ�ת��ʵ��ת��
* @param --
* @return --
*/

/*****************************************************************/

/**
* @author  yang 2019/3/11
* @Description: ����ᵽλ 
* @param -- num ��Ҫ��������
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


