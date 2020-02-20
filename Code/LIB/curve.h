#ifndef __CURVE_H
#define __CURVE_H

#include "curve.h"
#include "BSPlib.h"
//#include "cfg.h"


//定义轴速度类型
enum AxSpdStDef{
    
    ACCE_IDLE = 0,
    ACCE_INCR, //增加加速度
    ACCE_UNIF,     //匀加速
    ACCE_DECR,     //减少加速度
    ACCE_ZERO,     //匀速
    DECE_INCR,     //增加减速度
    DECE_UNIF,     //匀减速
    DECE_DECR      //减少减速度
};

//定义轴速度类型脉冲数
typedef struct{
    u32 Acce_Incr;   //加加速脉冲数
    u32 Acce_Unif;   //匀加速脉冲数
    u32 Acce_Decr;   //减加速脉冲数
    u32 Acce_Zero;   //匀速脉冲数
    u32 Dece_Incr;   //加减速脉冲数
    u32 Dece_Unif;   //匀加速脉冲数
    u32 Dece_Decr;   //减加速脉冲数
}AxPulsCalcParaDef;


//定义轴位置参数
typedef struct{    
    u32 Cur;    //当前脉冲数  从Ax获取
    u32 Tar;    //目标脉冲    从Ax获取
    u32 This;   //当前速度所需走步数
    u32 Next;   //下个速度所需走步数
    u32 Inc;    //位置增量
}AxPulsParaDef;

//定义轴速度输出参数
typedef struct{
    u32 This;
    u32 Next;
    u8 State;
}AxSpdParaDef;



/**************************************************************************/
#define LNTIMER     0.5f    //改速度时间间隔 单位： ms
#define ST          0.5f    //采样时间(ms)
#define VMAX        2e6     //上限速度       单位： pulse/s
#define ACCMAX      5e9     //上限加速度：   单位：pulse/(s^2)
#define JERKMAX     5e12    //上限加加速
#define SRATIO      0.4f    //S段时间比例    单位： 无量纲
#define UNIFRATIO   0.1f
#define TCURVE      0
#define SCURVE      1
#define SPDSECTION  7


#define SPD_INIT(n)           CurvePara[n].SpdInPara.Vinit
#define SPD_TAR(n)            CurvePara[n].SpdInPara.Vtar
#define SPD_END(n)            CurvePara[n].SpdInPara.Vend
#define SPD_ACCE(n)           CurvePara[n].SpdInPara.Acce
#define SPD_DECE(n)           CurvePara[n].SpdInPara.Dece
#define SPD_TACC(n)           CurvePara[n].SpdInPara.Tacc
#define SPD_TDEC(n)           CurvePara[n].SpdInPara.Tdec
#define SPD_TAA(n)            CurvePara[n].SpdInPara.Taa
#define SPD_TDD(n)            CurvePara[n].SpdInPara.Tdd
#define SPD_JERK(n)           CurvePara[n].SpdInPara.Jerk
#define SPD_DJERK(n)          CurvePara[n].SpdInPara.Djerk
#define SPD_ACCEVAR(n)        CurvePara[n].SpdMedPara.AcceVar 
#define SPD_DECEVAR(n)        CurvePara[n].SpdMedPara.DeceVar
#define SPD_VACCE1(n)         CurvePara[n].SpdMedPara.Vacce[0]
#define SPD_VACCE2(n)         CurvePara[n].SpdMedPara.Vacce[1]
#define SPD_VDECE1(n)         CurvePara[n].SpdMedPara.Vdece[0]
#define SPD_VDECE2(n)         CurvePara[n].SpdMedPara.Vdece[1]
#define SPD_CUR(n)            CurvePara[n].SpdOutPara.Cur
#define SPD_NEXT(n)           CurvePara[n].SpdOutPara.Next

#define PULS_CUR(n)           CurvePara[n].PulsPara.Cur
#define PULS_TAR(n)           CurvePara[n].PulsPara.Tar
#define PULS_NEXT(n)          CurvePara[n].PulsPara.Next
#define PULS_INCR(n)          CurvePara[n].PulsPara.Incr
#define PULS_ACCE_INCR(n)     CurvePara[n].PulsPara.Calc.Mem.Acce_Incr
#define PULS_ACCE_UNIF(n)     CurvePara[n].PulsPara.Calc.Mem.Acce_Unif
#define PULS_ACCE_DECR(n)     CurvePara[n].PulsPara.Calc.Mem.Acce_Decr
#define PULS_ACCE_ZREO(n)     CurvePara[n].PulsPara.Calc.Mem.Acce_Zero
#define PULS_DECE_INCR(n)     CurvePara[n].PulsPara.Calc.Mem.Dece_Incr
#define PULS_DECE_UNIF(n)     CurvePara[n].PulsPara.Calc.Mem.Dece_Unif
#define PULS_DECE_DECR(n)     CurvePara[n].PulsPara.Calc.Mem.Dece_Decr

#define CURVE_MODE(n)         CurvePara[n].Mode
#define CURVE_STATE(n)        CurvePara[n].State



typedef struct{
    u32   Vinit;          //初速度
    u32   Vtar;           //运行速度
    u32   Vend;           //停止速度
    u32   Acce;           //加速度
    u32   Dece;           //减速度
    u32   Tacc;           //加速时间
    u32   Tdec;           //减速时间
    float Taa;            //加加速时间
    float Tdd;            //减减速时间
    u32   Jerk;           //加加速度
    u32   Djerk;          //减减速度
}SpdInParaDef;

typedef struct{
    u32 AcceVar;        //运行过程的加速度
	u32 DeceVar;		//运行过程的减速度
    u32 Vacce[2];       //匀加速阶段启停速度
    u32 Vdece[2];       //匀减速阶段启停速度
}SpdMedParaDef;

typedef struct{
    u32 Cur;
    u32 Next;
}SpdOutParaDef;

typedef struct{
    u32 Cur;           //当前脉冲
    u32 Tar;           //目标脉冲
    u32 Next;          //下步脉冲
    u32 Incr;          //脉冲增量 
    union 
    {
        u32 Para[SPDSECTION];
        struct{
            u32 Acce_Incr;     //加加速脉冲数
            u32 Acce_Unif;     //匀加速脉冲数
            u32 Acce_Decr;     //减加速脉冲数
            u32 Acce_Zero;     //匀速脉冲数
            u32 Dece_Incr;     //加减速脉冲数
            u32 Dece_Unif;     //匀减速脉冲数
            u32 Dece_Decr;     //减减速脉冲数 
        }Mem;
    }Calc;
}PulsParadef;


typedef struct{ 
    u8 Mode;                     // 0:T型 / 1:S型
    u8 State;                    // 状态
    u8 Peak_Cut;                 // 0：重新规划无匀速段   1：重新规划有匀速段 
    u32 TestCnt;
    SpdInParaDef SpdInPara;      // 速度输入 
    SpdMedParaDef SpdMedPara;    // 速度中间变量
    SpdOutParaDef SpdOutPara;    // 速度输出 当前/下一个
    PulsParadef PulsPara;        // 脉冲参数     
}CurveParaDef;

typedef struct{
    u32 Spd;
    u32 Puls;
}PulsSpdParaDef;

typedef struct{
	u32 Acc;
	u32 Spd;
	u32 Puls;
}ASPParaDef;

/**************************************************************************/

extern u32 CurvesGetSpd(u8 AxNum);
extern u32 CurvesGetDecSteps(u8 AxNum);
extern u32 CurvesReset(u8 AxNum,u8 TorS,u32 Vinit,u32 Vtar,u32 Vend,u32 Pos,u32 Tacc,u32 Tdec);	

#endif
