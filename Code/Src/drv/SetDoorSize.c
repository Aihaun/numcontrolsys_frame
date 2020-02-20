#include "SetDoorSize.h"

/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
static void SetDoorWideAndThick(struct SetDoorSizeConfigPara *t)
{
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
s32 Run_SetDoorWideAndThick(struct SetDoorSizeConfigPara *t)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
s32 Get_SetDoorWideAndThickSta(struct SetDoorSizeConfigPara *t)
{
	return 1;
}


/**
* @author：nyh 
* @Date： 20200206
* @Description:	对刀函数轮询
*/
void SetDoorSizeLoop(struct SetDoorSizeConfigPara *t)
{
	SetDoorWideAndThick(t);
}

 
