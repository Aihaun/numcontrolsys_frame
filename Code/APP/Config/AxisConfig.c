#include "axisconfig.h"

void AxisConfig(AxisDef AxisSpeed[],
                AxisIOConfig ioconfig[])
{
    int i;
    for(i=0; i<PULS_NUM; i++)
    {
        switch(ioconfig[i].limitMode)
        {
        case 0: //没有限位
            HZ_AxSetAxiSig(i,1,ioconfig[i].OrgNum,ioconfig[i].Orglev,0,0,0,0,0,0);
            HZ_AxSetLimSoft(i,0,AxisSpeed[i].SoftMaxLimit,0,AxisSpeed[i].SoftMinLimit);
            break;
        case 1: //只有软件限位
            HZ_AxSetAxiSig(i,1,ioconfig[i].OrgNum,ioconfig[i].Orglev,0,0,0,0,0,0);
            HZ_AxSetLimSoft(i,1,AxisSpeed[i].SoftMaxLimit,1,AxisSpeed[i].SoftMinLimit);
            break;
        case 2:  //只有硬件限位
            HZ_AxSetAxiSig(i,1,ioconfig[i].OrgNum,ioconfig[i].Orglev,\
                           1,ioconfig[i].Poslimit,ioconfig[i].Poslimitlev,\
                           1,ioconfig[i].Neglimit,ioconfig[i].Neglimitlev);
            HZ_AxSetLimSoft(i,0,AxisSpeed[i].SoftMaxLimit,0,AxisSpeed[i].SoftMinLimit);
            break;
        case 3:  //两种限位都有效
            HZ_AxSetAxiSig(i,1,ioconfig[i].OrgNum,ioconfig[i].Orglev,\
                           1,ioconfig[i].Poslimit,ioconfig[i].Poslimitlev,\
                           1,ioconfig[i].Neglimit,ioconfig[i].Neglimitlev);
            HZ_AxSetLimSoft(i,1,AxisSpeed[i].SoftMaxLimit,1,AxisSpeed[i].SoftMinLimit);
            break;
        }
        HZ_AxSetHomMod(i,ioconfig[i].HomeMode);
		HZ_AxSetAlm(i,ioconfig[i].alarmmode);
		
//		HZ_AxSetPara(i, AxisSpeed[i].StartSpeed, AxisSpeed[i].Acctime, AxisSpeed[i].RunSpeed,
//                     AxisSpeed[i].Dectime, AxisSpeed[i].EndSpeed,
//                     AxisSpeed[i].HomeSpeedFast, AxisSpeed[i].HomeSpeedSlow,
//                     AxisSpeed[i].HomeOffset, 0, 0);
    }
}

