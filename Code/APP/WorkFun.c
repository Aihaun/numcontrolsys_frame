#include "WorkFun.h"
#include "WorkShape.h"

VariData ddd;
//ShapeDef shap[20]=
//{
//	
//};


void (*shap_fun[20])(ShapeDef* shap, int KnifeNum)=
{
	KnifeHole, KnifeHoleCirc, KnifeLine, KnifeLevelArc ,
	KnifeStandArc, 
	

};

//void workLoop()
//{
//	shap[0].Basic = GUS.BasicPara;
//	shap[0].Para.execute = 1;
//	
//	for(int i=0;i<20;i++) 
//	{
//		for(int j=0; j<2; j++)
//		{
//			shap_fun[i](&shap[i], j);
//		}
//	}	
//}
