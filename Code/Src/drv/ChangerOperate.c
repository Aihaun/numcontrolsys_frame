#include "ChangerOperate.h"

/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
static void ChangerSpeed_ON(struct ChangerConfigPara *p)
{
}

/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
static void ChangerSpeed_OFF(struct ChangerConfigPara *p)
{
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
static void ManuChangerSpeed_ON(struct ChangerConfigPara *p)
{
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
static void ManuChangerSpeed_OFF(struct ChangerConfigPara *p)
{
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
static void ChengerManu(struct ChangerConfigPara *p)
{
}

/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
s32 Run_ChangerSpeed_ON(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
s32 Run_ChangerSpeed_OFF(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
s32 Run_ManuChangerSpeed_ON(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
s32 Run_ManuChangerSpeed_OFF(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
s32 Run_ChengerManu(struct ChangerConfigPara *p)
{
	return 1;
}

/*
* @author��nyh 
* @Date�� 20200206
* @Description:	��ȡ
*/
s32 Get_ChangerSpeed_ONSta(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	��ȡ
*/
s32 Get_ChangerSpeed_OFFSta(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	��ȡ
*/
s32 Get_ManuChangerSpeed_ONSta(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	��ȡ
*/
s32 Get_ManuChangerSpeed_OFFSta(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	��ȡ
*/
s32 Get_ChengerManuSta(struct ChangerConfigPara *p)
{
	return 1;
}

/**
* @author��nyh 
* @Date�� 20200206
* @Description:	��Ƶ������������ѯ
*/
void ChangerOperateLoop(struct ChangerConfigPara *p)
{
	ChangerSpeed_ON(p);
	ChangerSpeed_OFF(p);
	ManuChangerSpeed_ON(p);
	ManuChangerSpeed_OFF(p);
	ChengerManu(p);
}
