#include "fsm.h"

	

typedef struct
{
	char filname[10][16];	//10*4 1520 - 1599 
	char newfilename[16];	//1600-1607
	u32 workfilenum[4];		//1608-1615		//备用  [0]产品编号  [1]程序列表序号0~9
	
	u32 index;		//1616 当前编辑文件 的编号 0-9
	FileParaDef newFilePara;	//1618-1657
	
} ShapPara;	//最多20个类型


typedef struct ShapInterface
{
	int state;
	LogicParaDef task;
	int prv_state;
	int next_state;
//	void (*shap_funloop)(struct ShapInterface*);
//	void (*funstart)(struct ShapInterface*);
	ShapPara*   shappara;
	
}Shap_InterfaceType;

//Shap_InterfaceType shap_drv[2]=
//{
//	
//};





void Shap1LoopFun(struct ShapInterface* shapdrv)
{
	if(shapdrv->task.execute==1 && shapdrv->task.step == 0)
	{
		
	}
}

void Shap2LoopFun(struct ShapInterface* shapdrv)
{
	if(shapdrv->task.execute==1 && shapdrv->task.step == 0)
	{
		
	}
}

void Shap1Start(struct ShapInterface* shapdrv)
{
}

 
ShapPara pp;

//Shap_InterfaceType shap[1];



