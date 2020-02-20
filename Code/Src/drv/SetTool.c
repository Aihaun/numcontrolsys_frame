#include "SetTool.h"

/*
* @author：nyh 
* @Date： 20200206
* @Description:	水平对刀
*/
static void SetLevelTool(struct SetToolConfigPara *p)
{
} 

/*
* @author：nyh 
* @Date： 20200206
* @Description:	垂直对刀
*/
static void SetVerticalTool(struct SetToolConfigPara *p)
{
} 

/*
* @author：nyh 
* @Date： 20200206
* @Description:	对刀
*/
static void SetTool(struct SetToolConfigPara *p)
{
} 

/*
* @author：nyh 
* @Date： 20200206
* @Description:	对刀
*/
s32 Run_SetLevelTool(struct SetToolConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	对刀
*/
s32 Run_SetVerticalTool(struct SetToolConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	对刀
*/
s32 Run_SetTool(struct SetToolConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	对刀
*/
s32 Get_SetLevelToolSta(struct SetToolConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	对刀
*/
s32 Get_SetVerticalToolSta(struct SetToolConfigPara *p)
{
	return 1;
}
/*
* @author：nyh 
* @Date： 20200206
* @Description:	对刀
*/
s32 Get_SetToolSta(struct SetToolConfigPara *p)
{
	return 1;
}

/**
* @author：nyh 
* @Date： 20200206
* @Description:	对刀函数轮询
*/
void SetToolLoop(struct SetToolConfigPara *p)
{
	SetLevelTool(p);
	SetVerticalTool(p);
	SetTool(p);
	
}
