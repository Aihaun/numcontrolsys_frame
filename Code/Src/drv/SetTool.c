#include "SetTool.h"

/*
* @author��nyh 
* @Date�� 20200206
* @Description:	ˮƽ�Ե�
*/
static void SetLevelTool(struct SetToolConfigPara *p)
{
} 

/*
* @author��nyh 
* @Date�� 20200206
* @Description:	��ֱ�Ե�
*/
static void SetVerticalTool(struct SetToolConfigPara *p)
{
} 

/*
* @author��nyh 
* @Date�� 20200206
* @Description:	�Ե�
*/
static void SetTool(struct SetToolConfigPara *p)
{
} 

/*
* @author��nyh 
* @Date�� 20200206
* @Description:	�Ե�
*/
s32 Run_SetLevelTool(struct SetToolConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	�Ե�
*/
s32 Run_SetVerticalTool(struct SetToolConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	�Ե�
*/
s32 Run_SetTool(struct SetToolConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	�Ե�
*/
s32 Get_SetLevelToolSta(struct SetToolConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	�Ե�
*/
s32 Get_SetVerticalToolSta(struct SetToolConfigPara *p)
{
	return 1;
}
/*
* @author��nyh 
* @Date�� 20200206
* @Description:	�Ե�
*/
s32 Get_SetToolSta(struct SetToolConfigPara *p)
{
	return 1;
}

/**
* @author��nyh 
* @Date�� 20200206
* @Description:	�Ե�������ѯ
*/
void SetToolLoop(struct SetToolConfigPara *p)
{
	SetLevelTool(p);
	SetVerticalTool(p);
	SetTool(p);
	
}
