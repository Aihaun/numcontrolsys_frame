#ifndef __CURVE_H
#define __CURVE_H

#include "curve.h"
#include "BSPlib.h"
//#include "cfg.h"


//�������ٶ�����
enum AxSpdStDef{
    
    ACCE_IDLE = 0,
    ACCE_INCR, //���Ӽ��ٶ�
    ACCE_UNIF,     //�ȼ���
    ACCE_DECR,     //���ټ��ٶ�
    ACCE_ZERO,     //����
    DECE_INCR,     //���Ӽ��ٶ�
    DECE_UNIF,     //�ȼ���
    DECE_DECR      //���ټ��ٶ�
};

//�������ٶ�����������
typedef struct{
    u32 Acce_Incr;   //�Ӽ���������
    u32 Acce_Unif;   //�ȼ���������
    u32 Acce_Decr;   //������������
    u32 Acce_Zero;   //����������
    u32 Dece_Incr;   //�Ӽ���������
    u32 Dece_Unif;   //�ȼ���������
    u32 Dece_Decr;   //������������
}AxPulsCalcParaDef;


//������λ�ò���
typedef struct{    
    u32 Cur;    //��ǰ������  ��Ax��ȡ
    u32 Tar;    //Ŀ������    ��Ax��ȡ
    u32 This;   //��ǰ�ٶ������߲���
    u32 Next;   //�¸��ٶ������߲���
    u32 Inc;    //λ������
}AxPulsParaDef;

//�������ٶ��������
typedef struct{
    u32 This;
    u32 Next;
    u8 State;
}AxSpdParaDef;



/**************************************************************************/
#define LNTIMER     0.5f    //���ٶ�ʱ���� ��λ�� ms
#define ST          0.5f    //����ʱ��(ms)
#define VMAX        2e6     //�����ٶ�       ��λ�� pulse/s
#define ACCMAX      5e9     //���޼��ٶȣ�   ��λ��pulse/(s^2)
#define JERKMAX     5e12    //���޼Ӽ���
#define SRATIO      0.4f    //S��ʱ�����    ��λ�� ������
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
    u32   Vinit;          //���ٶ�
    u32   Vtar;           //�����ٶ�
    u32   Vend;           //ֹͣ�ٶ�
    u32   Acce;           //���ٶ�
    u32   Dece;           //���ٶ�
    u32   Tacc;           //����ʱ��
    u32   Tdec;           //����ʱ��
    float Taa;            //�Ӽ���ʱ��
    float Tdd;            //������ʱ��
    u32   Jerk;           //�Ӽ��ٶ�
    u32   Djerk;          //�����ٶ�
}SpdInParaDef;

typedef struct{
    u32 AcceVar;        //���й��̵ļ��ٶ�
	u32 DeceVar;		//���й��̵ļ��ٶ�
    u32 Vacce[2];       //�ȼ��ٽ׶���ͣ�ٶ�
    u32 Vdece[2];       //�ȼ��ٽ׶���ͣ�ٶ�
}SpdMedParaDef;

typedef struct{
    u32 Cur;
    u32 Next;
}SpdOutParaDef;

typedef struct{
    u32 Cur;           //��ǰ����
    u32 Tar;           //Ŀ������
    u32 Next;          //�²�����
    u32 Incr;          //�������� 
    union 
    {
        u32 Para[SPDSECTION];
        struct{
            u32 Acce_Incr;     //�Ӽ���������
            u32 Acce_Unif;     //�ȼ���������
            u32 Acce_Decr;     //������������
            u32 Acce_Zero;     //����������
            u32 Dece_Incr;     //�Ӽ���������
            u32 Dece_Unif;     //�ȼ���������
            u32 Dece_Decr;     //������������ 
        }Mem;
    }Calc;
}PulsParadef;


typedef struct{ 
    u8 Mode;                     // 0:T�� / 1:S��
    u8 State;                    // ״̬
    u8 Peak_Cut;                 // 0�����¹滮�����ٶ�   1�����¹滮�����ٶ� 
    u32 TestCnt;
    SpdInParaDef SpdInPara;      // �ٶ����� 
    SpdMedParaDef SpdMedPara;    // �ٶ��м����
    SpdOutParaDef SpdOutPara;    // �ٶ���� ��ǰ/��һ��
    PulsParadef PulsPara;        // �������     
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
