#include "ChangerOperate.h"

/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
static void ChangerSpeed_ON(struct ChangerConfigPara *p)
{
}

/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
static void ChangerSpeed_OFF(struct ChangerConfigPara *p)
{
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
static void ManuChangerSpeed_ON(struct ChangerConfigPara *p)
{
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
static void ManuChangerSpeed_OFF(struct ChangerConfigPara *p)
{
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
static void ChengerManu(struct ChangerConfigPara *p)
{
}

/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
s32 Run_ChangerSpeed_ON(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
s32 Run_ChangerSpeed_OFF(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
s32 Run_ManuChangerSpeed_ON(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
s32 Run_ManuChangerSpeed_OFF(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
s32 Run_ChengerManu(struct ChangerConfigPara *p)
{
	return 1;
}

/*
* @author：nyh 
* @Date： 20200206
* @Description:	获取
*/
s32 Get_ChangerSpeed_ONSta(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	获取
*/
s32 Get_ChangerSpeed_OFFSta(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	获取
*/
s32 Get_ManuChangerSpeed_ONSta(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	获取
*/
s32 Get_ManuChangerSpeed_OFFSta(struct ChangerConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	获取
*/
s32 Get_ChengerManuSta(struct ChangerConfigPara *p)
{
	return 1;
}

/**
* @author：nyh 
* @Date： 20200206
* @Description:	变频器操作函数轮询
*/
void ChangerOperateLoop(struct ChangerConfigPara *p)
{
	ChangerSpeed_ON(p);
	ChangerSpeed_OFF(p);
	ManuChangerSpeed_ON(p);
	ManuChangerSpeed_OFF(p);
	ChengerManu(p);
}
