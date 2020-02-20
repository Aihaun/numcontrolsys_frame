#ifndef __IODEFINE_H
#define __IODEFINE_H
typedef enum	//����ڶ���
{
	Q_HingeRet,		//Y1	    //��������
	Q_HingeAdv,		//Y2	    //����ǰ������
	Q_Cluth,		//Y3		//�������
	Q_Leveling,		//Y4		//ˮƽ��������
	Q_Vertical,		//Y5		//��ֱ��������
	Q_HingeAir,		//Y6		//��������
	Q_Lube,			//Y7		//���ͱ�
	Q_FreSpd1,		//Y8		//��Ƶ���ٶ�1
	Q_FreSpd2,		//Y9		//��Ƶ���ٶ�2
	Q_FreSpd3,		//Y10		//��Ƶ���ٶ�3
	Q_FreSpd4,		//Y11		//��Ƶ���ٶ�4
	Q_SerFre,		//Y12		//�ŷ���Ƶ�� ����
	Q_Hinge,		//Y13		//�����Ӵ���
	Q_Slot,			//Y14		//���۽Ӵ���
	Q_Stair,		//Y15		//���׽Ӵ���
	Q_Hole1,		//Y16		//���׵�1�Ӵ���
	Q_Hole2,		//Y17		//���׵�2�Ӵ���
	Q_Hole1Cyl,		//Y18		//���׵�1����
	Q_Hole2Cyl,		//Y19		//���׵�2����
	Q_TableCyl,		//Y20		//����̨������
	Q_Fasten,		//Y21		//ѹ������
	Q_SetToolPower,	//Y22		//�Ե�0V�̵���
	Q_23,
	Q_24,
} OutNum;

typedef enum	//����ڶ���
{
    I_X = 0,		//Xԭ��
    I_Y,            //Yԭ��
	I_Z,            //Zԭ��
    I_W,            //Wԭ��
    I_Xpos,			//X����λ
    I_Ypos,			//Y����λ
    I_Zpos,			//Z����
	I_Wpos,         //W����
	I_Wneg,			//W����λ
	I_Leveling,		//ˮƽ����	9
	I_Vertical,		//��ֱ����
	I_Check,		//�Ե���Ӧ��
	I_Scram,		//��ͣ
	I_Air,			//��ѹ����
	I_HingePoleOrg,	//������ ԭλ
	I_HingeReady,	//������ ��λ
	I_HoleK1Org,	//���׵�1ԭ��
	I_HoleK2Org,	//���׵�2ԭ��
	I_Run,			//�Զ�/��ͣ��ť
	I_Clamp,    	//�н�/�ɿ���ť	19
	I_TableLift,	//����̨����
	I_HingeK1Org,	//������1ԭ��
	I_HingeK2Org,	//������2ԭ��
	I_HingeK3Org,	//������3ԭ��
} InPutNum;

typedef enum	//��չ����ڶ���
{
	I_HingeK4Org,	//������4ԭ��
	I_CluthLos,		//����ɿ�
	I_CluthCon,		//��Ϻ���
	I_HingeMotor1,	//�������1
	I_HingeMotor2,	//�������2
	I_HingeMotor3,	//�������3
	I_FreFault,		//��Ƶ������
	I_StairAlarm,	//�����ȼ̵���
	I_Hole1Alarm,	//����1�ȼ̵���
	I_Hole2Alarm,	//����2�ȼ̵���
	I_Lube,			//����Һλ
} EXInputNum;

#endif

