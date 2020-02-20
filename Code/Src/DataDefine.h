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
/* �˴�֮���ϵͳ����������ģ��û�ֻ�ܸ����û�������		           */
/************************************************************************/

/************ҵ���߼�����***********************/

/***************�ļ�����********************/
//���ļ�	
//������(mode)  
//	0��		     1�Ͽڷ��� 	 2�Ͽ����  		3�¿ڷ���   			 4�¿����     5���ͽ���      6��շ���
//	7(1����      8(1��ϳԲ 	 9(1������  		10(2����    		11(2��ϳԲ     12(2������     13����
//	14Բ������ 	 15����       16Բ������	   17Բ����������������   18��1��Բ��    19��2��Բ��
//				
typedef struct
{
	float mode;			//1618  //4208 ������	
	float SizePara[19];//ԭ17��
} FileParaDef;	//ÿ������ռ18������



//�༭�ļ��ṹ(�������༭)
typedef struct
{
	char filname[10][16];	//10*4 1520 - 1599 
	char newfilename[16];	//1600-1607
	u32 workfilenum[4];		//1608-1615		//����  [0]��Ʒ���  [1]�����б����0~9
	
	u32 index;		//1616 ��ǰ�༭�ļ� �ı�� 0-9
	FileParaDef newFilePara;	//1618-1657
} FileDef;	//���20������


//��ǰ�ӹ��ļ�
typedef struct
{
	char workfilename[16];	//4200-4207
	FileParaDef File[20];	//4208-5006   400��
} WorkFileDef;

/***************�ļ�����********************/


/***********����������������**************/

//�Ե� ��������
typedef struct
{
	struct
	{
		float slotKnifeX;	//�۵��Ե�Xʵ��ֵ	4000
		float slotKnifeZ;	//�۵��Ե�Zʵ��ֵ
		float holeKnifeY;	//�׵��Ե������Yֵ
		float checkLumpH;	//У����߶�
		float slotKLenY;	//�۵���У����Y		4008
		float holeK1LenZ;	//�׵�1��У����Z
		float stairKLenY;	//�׵���У����Y
		float holeK2LenZ;	//�׵�2��У����Z
		float horizonLenY;	//ˮƽ�˵�У����Y
		float verticalLenZ;	//��ֱ�˵�У����Z
		float checkSpdFast;	//�Ե����ٶ�
		float checkSpdslow;	//�Ե����ٶ�
	}Check;	//�Ե�����
	struct
	{
		float cluthPosY;		//���λ��Y			4024
		float hingeKLenW;		//������W̨��ԭ��
		float hingeKLenX;		//������X����ԭ��
	}Hinge;	//�����ӹ��̶�λ��
	
	float res[10];
}CheckParaDef;	//25 �Ե�/��������

//�ӹ�����
typedef struct
{	
	HoleSoftDef  HoleSoftPara;
	SlotSoftDef  SlotSoftPara; 
	HingeSoftDef HingeSoftPara;
	float res[10];
}WorkParaDef;	//40 �ӹ�����

//��е����
typedef struct 
{	
	struct
	{
		float stairKOffset;	//�׵�Xƫ�Ʋ۵�		4110
		float holeK1Offset;	//��1��Xƫ�Ʋ۵�
		float holeKSpace;	//��1���Ϳ�2��X���
		float horizonOffset;//ˮƽ��Xƫ�Ʋ۵�
		float verticalOffset;//��ֱ��Xƫ�Ʋ۵�
	}X;	//X�ο�
	
	struct
	{
		float holeKLen;		//�׵�1��2����ˮƽ�������Y		4120
		float verticalLen;	//��ֱ�˾���ˮƽ�������Y
		float WbroadsideLen;//W���� ����ˮƽ�������Y
	}Y;	//Y�ο�
	
	struct
	{
		float slotKLen;		//�۵����ĵ�̨��Z		4126
		float stairKLen;	//�׵�Zƫ�Ʋ۵�
	}Z;	//Z�ο�
	
	float moveFastSpd;		//�ƶ����ٶ� 	4130		
	float DoorThick;		//�Ű��� 		4132
	float DoorWide;			//�Ű���		4134
	float checkLumpThick;	//У������Y	4136
	float verti_LenZ;		//��ֱ������㵽̨��Z		4138
	float HMI_DoorThick;	//�������趨�Ű��� 	4140
	float HMI_DoorWide;		//�������趨�Ű���		4142
	float MoveSpd;			//�ƶ����ٶ�
	float slotKLenX;		//X�ڹ�������0ʱ���۵��뿿ɽ����
	u32 AutoWideEnable;	//�Զ����ʹ��	4072
	float AutoThickEnable;	//�Զ����ʹ��
	float res[14];
	
}MechanicalParaDef; //35  ��е����

typedef struct
{
	CheckParaDef CheckPara;				//4000 - 4048
	WorkParaDef workPara;				//4050 - 4128
	MechanicalParaDef MechanicalPara;	//4130 - 4198	
	WorkFileDef WorkFile;				//4200 - 5006    808��
}BasicParaDef;	//��100������

//���ܲ���
typedef struct
{
	s32 NowAwayProduct;		//��ǰ����	4572
	s32 AtleProduct;		//�ܲ���		4574
	float OneWorkTime;		//������ʱ	4576
	float AllWorkTime;		//�ܹ�ʱ		4578
	
}ProductParaDef;


//*******************************************************************************//

typedef struct
{
    u8 hour;		//��Χ0-23
    u8 min;			//0-59
    u8 sec;			//0-59
    u8 ampm;		//���ֵû�ã���ֹʹ��
} Time;

typedef struct
{
    s32 StartSpeed;	//���ٶ�
    s32 Acctime;	   //����ʱ��
    s32 RunSpeed;	  //�㶯�ٶ�
    s32 Dectime;	   //����ʱ��
    s32 EndSpeed;	  //ĩ�ٶ�
    s32 HomeSpeedFast; //��ԭ������ٶ�
    s32 HomeSpeedSlow; //��ԭ�������ٶ�
    s32 HomeOffset;	//��ԭ��ƫ������
    s32 SoftMinLimit;  //����λ
    s32 SoftMaxLimit;  //������λ
} AxisDef;
typedef struct
{
    u32 PPR;	//ÿת������
    float MPR;	//ÿת����__����
} AxisConversion;
typedef struct
{
    u16 limitMode;		//��λģʽ��0 û��λ 1 �����λ 2 Ӳ����λ 3 ��Ӳ����
    u16 Poslimit;    	//��λ�ź�
    u16 Poslimitlev;    //��λ�źŵ�ƽ
    u16 Neglimit;       //��λ�ź�
    u16 Neglimitlev;    //��λ�źŵ�ƽ
    u16 OrgNum;         //ԭ���ź�
    u16 Orglev;			//ԭ���źŵ�ƽ
    u16 HomeMode;		//����ģʽ
    u16 alarmmode;		//�ᱨ����ƽ:0���͵�ƽ��Ч 1���ߵ�ƽ��Ч �������ᱨ����Ч
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
                    u32 HardWare_Ver[10];		  //0-19	Ӳ���汾
                    u32 SoftWare_Ver[10];		  //20-39	����汾
                    u32 res[5];                   //40-49
                    u16 AXSTA[MAXAXISNUM];		  //50-99	��״̬
                    float AxisUnitPos[MAXAXISNUM];  //100-199	�ᵱǰ�û���λλ��
                    s32 AxisPosition[MAXAXISNUM]; //200-299	�ᵱǰλ��
                    u32 AxisEncoder[5];			  //300-309	�ᵱǰ״̬
                    u32 InputStatus[40];		  //310-389	�����״̬
                    u32 ErrorCode[20];			  //390-	������
                    u32 ErrorLevel;				  //430-	����ȼ�
                    Time time;	//432	rtc ʱ��
                    Date date;	//434	rtc ����
                    u32 CID[2];	//436 438 �������ɵĿͻ������

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
					u32 IndicateShow;	//506  ����ָʾ��
					u16 StepShow[16];	//508-523  �ӹ�����״̬��ʾ	
					float SetDoorWide;    //524	�Զ����ſ�
					float SetDoorThick;	//526   �Զ����ź�
					u32 ChengerSta;		//528   ��Ƶ��״̬
					u32 OpenFileLimit;	//530   ���ļ�����	0�������	1����ֹ��
					u32 WorkWhich;		//532 	�ӹ����ĸ�
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
                    u32 res[10];		  	//1000-1019 ����
                    u32 OutputStatus[40]; 	//1020-1099	�����״̬
                    u32 FlashOperate;	 	//1100-	Flash����
                    u32 FilesOperate;	 	//1102-	�ļ�����
                    u32 FramOperate;	  	//1104-	�������
                    u32 JogMode;		  	//1106-	�㶯ģʽ
                    u32 JogPositionLevel; 	//1108-	�㶯�г̼���
                    u32 JogPosition;	  	//1110-	�㶯�趨�г�
                    u32 JogForward[2];		//1112-1115	����㶯
                    u32 JogBackward[2];   	//1116-1119	����㶯
                    u32 JogGohome[2];	 	//1120-1123	�㶯����
                    u32 JogStop[2];		  	//1124-1127	�㶯����ֹͣ
                    u32 jogSpd;			  	//1128  ��㶯�ٶ�
                    u32 ClearAlarm;		  	//1130-	�������
                    struct
                    {
                        u32 refreshId;	//	1132 �����ˢ��
                        s32 decode[4];	//1134 1136 1138 1140  4�������� *6���� һ��24����
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
							u32 MeasureAccSpd;	//1508  �Ե�����
							u32 ChangerManual;	//1510	��Ƶ�ֶ�
							u32 CluthCylMotion;	//1512  ������ײ���
                        } Data;
                    } button;//1500+20
					
					FileDef EditFile;		//1520-1656	�ӹ��ļ�
					
					union //1654-1672   ���µ�ַȫ��Ҫ����
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
                    AxisDef AxisData[MAXAXISNUM]; //2000-2999	50���ᣬÿ��ռ20���Ĵ���
                    AxisConversion Conversion[MAXAXISNUM]; //3000 -3199 ÿת������
                    AxisIOConfig AxIOconfig[MAXAXISNUM];   //3200 - 3699
                    lockdataflashsave LockDate;	//3700 �������õ���������
                } Data;
            } Sys;

            union //USER SAVE ADDR 4000-5999
            {
                u16 Data_16[USERSAVELEN / 2];
                struct
                {					
					BasicParaDef BasicPara; 	//4000-5006
					
					////���µ�ַȫ������
					s32 ChangerFlag;			//4568 0: ���� 1��æ
					s32 ChangerManuOFFIndx;		//4570 �ֶ��ر�Ƶ���
					ProductParaDef ProductPara; //4572-4578
					s32 StartOrStopButton;		//4580 ����/ֹͣ
					s32 ResetT;					//4582 ����
					s32 CheckPage;				//	   ����
					s32 StartCheckPage;			//4586 �����豸���Զ��л���ؽ�����
					s32 Debug;					//4588
					s32 ProdNum[100];			//4590-4688  ��Ʒ���̱����ʾ
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
