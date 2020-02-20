#include "WorkShape.h"     

ParaTask TK ={0};

static VariData Data;

u8 AxNum[3];// = {X,Y,Z};
//孔刀气缸
u32 Q_HoleCyl[2] = {Q_Hole1Cyl, Q_Hole2Cyl};
static float RecordPos1[10] = {0};
static s32 MMToPul_Circ1[10] = {0};
static s32 MMToPul_Circ2[10] = {0};
static s32 MMToPul_Line1[20] = {0};//mm转换脉冲
static s32 MMToPul_Line2[20] = {0};//mm转换脉冲
static s32 MMToPul_Arc1[10] = {0};
static s32 MMToPul_Arc2[10] = {0};


static s32 MMToPul_KnifeArc1[10] = {0};
static s32 MMToPul_KnifeArc2[10] = {0};

static s32 MMToPul_HingeArc1[10] = {0};
static s32 MMToPul_HingeArc2[10] = {0};
static s32 MMToPul_HingeArc3[10] = {0};
static s32 MMToPul_HingeArc4[10] = {0};

void setVaDate(int a,int b)
{
	Data.HingeOrgX = a;
}

/**
* @author：nyh 20191025
* @Description:	刀孔(1刀2刀工 共用)
* @param --
* @return --
*/
void KnifeHole(ShapeDef *t, int KnifeNum) 
{	
	static float HoleKnifeZ = 0;
	static float HoleKnifeX_A = 0;
	static float HoleKnifeOffset = 0;
	//过程中遇到故障时终结该动作，轴停，气缸、铣刀关闭
	if(HZ_AxGetStatus(AxNum[X]) == AX_ERR_AX_ALM || HZ_AxGetStatus(AxNum[Y]) == AX_ERR_AX_ALM || HZ_AxGetStatus(AxNum[Z]) == AX_ERR_AX_ALM
		|| HZ_AxGetStatus(AxNum[X]) == AXSTA_ERRSTOP || HZ_AxGetStatus(AxNum[Y]) == AXSTA_ERRSTOP || HZ_AxGetStatus(AxNum[Z]) == AXSTA_ERRSTOP)
	{
		PARAINIT(it.Para);
		for(u8 i=0; i<2; i++)
		{
			HZ_AxStop(AxNum[i]);
		}
		return;
	}
	if(it.Para.execute == 1 && it.Para.step == 0)
	{
		it.Para.step = 1;
	}
	switch(it.Para.step)
	{
		case 1://Z回零位
			if(KnifeNum == 0)
			{	//1刀
				HoleKnifeZ = Data.Hole1KnifeZ;
				HoleKnifeX_A = Data.Hole1KnifeX_A;
				HoleKnifeOffset = it.Basic.mechanicalPara.X.holeK1Offset;
			}
			else//2刀
			{
				HoleKnifeZ =  Data.Hole2KnifeZ;
				HoleKnifeX_A = Data.Hole2KnifeX_A;
				HoleKnifeOffset = it.Basic.mechanicalPara.X.holeKSpace + it.Basic.mechanicalPara.X.holeK1Offset;
			}
			it.Para.step = 2;
			break;
		
		case 2://XY 到下刀位
			if(AxGetsta(Z_MOTOR) == 0)
			{
				if(it.Para.index == 0)//X -> 2*i
				{					  //Y -> 2*i+1
					if(it.Size.File[Data.workNum].SizePara[2*it.Para.index] != 0 && it.Size.File[Data.workNum].SizePara[2*it.Para.index+1] != 0)
					{
						AxRun(X_MOTOR, ABSMODE, it.Basic.workPara.MoveSpd , HoleKnifeX_A);
						AxRun(Y_MOTOR, ABSMODE, it.Basic.workPara.MoveSpd ,Data.HoleKnifeY_B);
						it.Para.step = 3;
					}
					else
					{
						it.Para.step = 7;
					}
				}
				else
				{
					if(it.Size.File[Data.workNum].SizePara[2*it.Para.index] != 0 && it.Size.File[Data.workNum].SizePara[2*it.Para.index+1] != 0)
					{
						AxRun(X_MOTOR, ABSMODE, it.Basic.workPara.MoveSpd , 
								it.Basic.workPara.Slot_Stair.slotKLenX - it.Size.File[Data.workNum].SizePara[2*it.Para.index] + HoleKnifeOffset);
						AxRun(Y_MOTOR, ABSMODE, it.Basic.workPara.MoveSpd ,
								it.Basic.checkPara.Check.horizonLenY - it.Basic.mechanicalPara.Y.holeKLen + it.Basic.mechanicalPara.checkLumpThick + it.Size.File[Data.workNum].SizePara[2*it.Para.index+1]);
						it.Para.step = 3;
					}
					else
					{
						it.Para.step = 7;
					}
				}
			}
			break;
		
		case 3://开变频，气缸下降
			if(AxGetsta(X_MOTOR) == 0 && AxGetsta(Y_MOTOR) == 0)
			{
				if(it.Para.index == 0)
				{
					if(KnifeNum>1)return ;
					Q_Set(Q_HoleCyl[KnifeNum],ON);
					TimerRst(it.Para);
					it.Para.step = 4;
				}
				else
				{
					AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.MoveSpd , HoleKnifeZ);//it.Basic.checkPara.Check.checkLumpH	校刀高度
					it.Para.step = 5;
				}
			}
			break;
			
		case 4://等待气缸下降延时，Z走到板面
			if(TimerCnt(it.Para) >= 1000 || it.Para.index == 0)
			{
				AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.MoveSpd , HoleKnifeZ);//it.Basic.checkPara.Check.checkLumpH	校刀高度
				it.Para.step = 5;
			}
			break;
			
		case 5://Z下刀钻孔，孔深,R=0为通孔
			if(AxGetsta(Z_MOTOR) == 0 && LT.ChangerSpeed_ONTask.execute == 0)
			{																																						//门厚							
				if(it.Size.File[Data.workNum].SizePara[R] > it.Basic.mechanicalPara.DoorThick+4) it.Size.File[Data.workNum].SizePara[R] = it.Basic.mechanicalPara.DoorThick+4;
				
				if(it.Size.File[Data.workNum].SizePara[R] == 0)
				{																	//孔刀1到门板高度							
					AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.holeSpd , HoleKnifeZ + it.Basic.mechanicalPara.DoorThick - 2);
					it.Para.step = 6;
				}
				else  
				{																	//孔刀1到板面																		
					AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.holeSpd , HoleKnifeZ + it.Size.File[Data.workNum].SizePara[R]-2);
					it.Para.step = 0xa1;
				}								
			}
			break;
			
		case 6:
			if(AxGetsta(Z_MOTOR) == 0)
			{
				AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.riftSpd , HoleKnifeZ + it.Basic.mechanicalPara.DoorThick);
				it.Para.step = 7;
			}
			break;
			
		case 0xa1:
			if(AxGetsta(Z_MOTOR) == 0)
			{
				AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.riftSpd , HoleKnifeZ + it.Size.File[Data.workNum].SizePara[R]);
				it.Para.step = 7;
			}
			break;
			
		case 7://等待延时，Z回安全高度
			if(AxGetsta(Z_MOTOR) == 0)
			{
				AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.MoveSpd , HoleKnifeZ - Safe_Z);
				it.Para.step = 8;
			}
			break;
			
		case 8://Z 回到安全高度时可以进行下一步动作
			if(AxGetsta(Z_MOTOR) == 0)
			{
				if(it.Para.index < 8)
				{
					it.Para.index++;
					it.Para.step = 2;
				}
				else
				{
					PARAINIT(it.Para);
				}
			}
			break;
	}	
}


/**
* @author：nyh 20200110
* @Description:	孔刀铣圆（1刀2刀共用）
* @param --
* @return --
*/
void KnifeHoleCirc(ShapeDef *t , int KnifeNum)
{
	static float Z_CirDepth = 0;//Z 进刀量
	static float HoleKnifeZ = 0;
	static float HoleKnifeX_A = 0;
	//过程中遇到故障时终结该动作，轴停，气缸、铣刀关闭
	if(it.Over == 1 || HZ_AxGetStatus(AxNum[X]) == AX_ERR_AX_ALM || HZ_AxGetStatus(AxNum[Y]) == AX_ERR_AX_ALM || HZ_AxGetStatus(AxNum[Z]) == AX_ERR_AX_ALM
		|| HZ_AxGetStatus(AxNum[X]) == AXSTA_ERRSTOP || HZ_AxGetStatus(AxNum[Y]) == AXSTA_ERRSTOP || HZ_AxGetStatus(AxNum[Z]) == AXSTA_ERRSTOP)
	{
		PARAINIT(it.Para);
		for(u8 i=0; i<2; i++)
		{
			HZ_AxStop(AxNum[i]);
		}
		return;
	}
	if(it.Para.execute == 1 && it.Para.step == 0)
	{
		it.Para.step = 1;
	}	
	switch(it.Para.step)
	{
		case 1://判断Z进刀量D和总深度E
			if(KnifeNum == 0)
			{	//1刀
				HoleKnifeZ = HoleKnifeZ;
				HoleKnifeX_A = Data.Hole1KnifeX_A;
			}
			else//2刀
			{
				HoleKnifeZ =  Data.Hole2KnifeZ;
				HoleKnifeX_A = Data.Hole2KnifeX_A;
			}
			Z_CirDepth = it.Size.File[Data.workNum].SizePara[D];
			if(Z_CirDepth > it.Size.File[Data.workNum].SizePara[E])
			{
				Z_CirDepth = it.Size.File[Data.workNum].SizePara[E];
			}
			it.Para.count++;
			it.Para.step = 2;
			break;
			
		case 2://记录XY当前位置，Z下降到进刀量 
			if(GetAxSta(AxNum[Z]) == 0) 
			{
				RecordPos1[6] = GSR.AxisPosition[AxNum[X]];//记录当前脉冲位置
				RecordPos1[7] = GSR.AxisPosition[AxNum[Y]];
				if(it.Para.count*Z_CirDepth < it.Size.File[Data.workNum].SizePara[E])
				{										//打孔进刀速度
					AxisRun(AxNum[Z], ABSM, it.Basic.workPara.hole.holeSpd , HoleKnifeZ + it.Para.count*Z_CirDepth);
					it.Para.step = 4; 
				}
				else if(it.Para.count*Z_CirDepth == it.Size.File[Data.workNum].SizePara[E])
				{										//打孔破孔速度,最后2mm
					AxisRun(AxNum[Z], ABSM, it.Basic.workPara.hole.holeSpd , HoleKnifeZ + it.Para.count*Z_CirDepth-2);					
					it.Para.step = 3;
				}
				else
				{
					it.Para.step = 4;
				}
			}
			break;
			
		case 3:
			if( GetAxSta(AxNum[Z]) == 0)
			{
				AxisRun(AxNum[Z], ABSM, it.Basic.workPara.hole.riftSpd , HoleKnifeZ + it.Para.count*Z_CirDepth);				
				it.Para.step = 4;
			}
			break;
		
		case 4://XY铣圆，把mm转换脉冲
			if( GetAxSta(AxNum[X]) == 0 && GetAxSta(AxNum[Y]) == 0 && GetAxSta(AxNum[Z]) == 0)
			{

				MMToPul_Circ1[0] =  ConvertToMachineUnit(AxNum[X], HoleKnifeX_A - it.Size.File[Data.workNum].SizePara[C]);								
				MMToPul_Circ1[1] =  ConvertToMachineUnit(AxNum[Y], Data.HoleKnifeY_B );				
				MMToPul_Circ1[2] =  ConvertToMachineUnit(AxNum[X], HoleKnifeX_A);
				MMToPul_Circ1[3] =  ConvertToMachineUnit(AxNum[Y], Data.HoleKnifeY_B + it.Size.File[Data.workNum].SizePara[C]);					
				MillCircPath(AxNum[X],AxNum[X],MMToPul_Circ1[0], MMToPul_Circ1[1], MMToPul_Circ1[2], MMToPul_Circ1[3], it.Basic.workPara.hole.circSpd);
				it.Para.step = 5;
			} 
			break; 
		
		case 5://判断XY铣圆完成，判断Z进刀量是否到达总深度
			if(HZ_AxGetCurPos(AxNum[X]) == RecordPos1[6] && GetAxSta(AxNum[X]) == 0 
				&& HZ_AxGetCurPos(AxNum[Y]) == RecordPos1[7] && GetAxSta(AxNum[Y]) == 0 )				
			{
				if(it.Para.count*Z_CirDepth < it.Size.File[Data.workNum].SizePara[E])
				{
					if((it.Para.count+1)*Z_CirDepth <= it.Size.File[Data.workNum].SizePara[E])
					{
						it.Para.count++;
						it.Para.step = 2;
					}
					else
					{
						RecordPos1[6] = GSR.AxisPosition[AxNum[X]];//记录当前脉冲位置
						RecordPos1[7] = GSR.AxisPosition[AxNum[Y]];
						AxisRun(AxNum[Z], ABSM, it.Basic.workPara.hole.riftSpd , GSR.AxisUnitPos[AxNum[Z]] + it.Size.File[Data.workNum].SizePara[E] - it.Para.count*Z_CirDepth);
						it.Para.count++;
						it.Para.step = 4;
					}
				}
				else
				{
					it.Para.step = 6;
				}					
			}
			break;       
			
		case 6://气缸1起来，关变频
			if(GetAxSta(AxNum[Z]) == 0)
			{				
				PARAINIT(it.Para); 
			}
			break;
	}
	
}

/**
* @author：nyh 20200112
* @Description:	孔刀折线(1刀2刀共用)
* @param --
* @return --
*/
void KnifeLine(ShapeDef *t, int KnifeNum)
{
	static float Z_LineDepth = 0;
	static float HoleKnifeZ = 0;
	static float HoleKnifeX_A = 0;
	static float HoleKnifeOffset = 0;
	//过程中遇到故障时终结该动作，轴停，气缸、铣刀关闭
	if(HZ_AxGetStatus(AxNum[X]) == AX_ERR_AX_ALM || HZ_AxGetStatus(AxNum[Y]) == AX_ERR_AX_ALM || HZ_AxGetStatus(AxNum[Z]) == AX_ERR_AX_ALM
		|| HZ_AxGetStatus(AxNum[X]) == AXSTA_ERRSTOP || HZ_AxGetStatus(AxNum[Y]) == AXSTA_ERRSTOP || HZ_AxGetStatus(AxNum[Z]) == AXSTA_ERRSTOP)
	{
		PARAINIT(it.Para);
		for(u8 i=0; i<2; i++)
		{
			HZ_AxStop(AxNum[i]);
		}
		return;
	}
	if(it.Para.execute == 1 && it.Para.step == 0)
	{
		it.Para.step =1;
	}
	switch(it.Para.step)
	{
		case 1://Z 
			if(KnifeNum == 0)
			{	//1刀
				HoleKnifeZ = HoleKnifeZ;
				HoleKnifeX_A = Data.Hole1KnifeX_A;
				HoleKnifeOffset = it.Basic.mechanicalPara.X.holeK1Offset;
			}
			else//2刀
			{
				HoleKnifeZ =  Data.Hole2KnifeZ;
				HoleKnifeX_A = Data.Hole2KnifeX_A;
				HoleKnifeOffset = it.Basic.mechanicalPara.X.holeKSpace + it.Basic.mechanicalPara.X.holeK1Offset;
			}	
			it.Para.step = 2;
			break;
		
		case 2:////XY到加工位置
			it.Para.step = 3;
			break;
		
		case 3://判断进刀量与总深度的大小、孔刀 1气缸、变频开
			if(AxGetsta(X_MOTOR) == 0 && AxGetsta(Y_MOTOR) == 0)
			{									
				Z_LineDepth = it.Size.File[Data.workNum].SizePara[K];
				if(Z_LineDepth > it.Size.File[Data.workNum].SizePara[L])
				{
					Z_LineDepth = it.Size.File[Data.workNum].SizePara[L]/3;
				}
				it.Para.count++;
				TimerRst(it.Para);
				it.Para.step = 4;
			}
			break;
							
		case 4://Z快速下降到加工高度，进一刀
			if(AxGetsta(Z_MOTOR) == 0)
			{
				if(it.Para.count*Z_LineDepth < it.Size.File[Data.workNum].SizePara[L])
				{
					AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.holeSpd , HoleKnifeZ + it.Para.count*Z_LineDepth);
					it.Para.step = 5;
				}
				else if(it.Para.count*Z_LineDepth == it.Size.File[Data.workNum].SizePara[L])
				{
					AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.holeSpd , HoleKnifeZ + it.Para.count*Z_LineDepth-2);
					it.Para.step = 0xa3;
				}
				else
				{
					it.Para.step = 5;
				}
			}
			break;
			
		case 0xa3://破孔速度,最后2mm
			if( AxGetsta(Z_MOTOR) == 0)
			{
				AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.riftSpd , HoleKnifeZ + it.Para.count*Z_LineDepth);
				it.Para.step = 5;
			}
			break;
			
		case 5:
			if(AxGetsta(Z_MOTOR) == 0)
			{
//				TimerRst(it);
				it.Para.step = 6;
			}
			break;
			
		case 6://铣直线，第1点 -> 第2点
//			if(TimerCnt(it) >= 500)
			{	
				if(it.Size.File[Data.workNum].SizePara[C] != 0 && it.Size.File[Data.workNum].SizePara[D] != 0)
				{
					//XY目标位置
					MMToPul_Line1[0] =  ConvertToMachineUnit(X_MOTOR, HoleKnifeX_A + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[C]));
					MMToPul_Line1[1] =  ConvertToMachineUnit(Y_MOTOR, Data.HoleKnifeY_B + it.Size.File[Data.workNum].SizePara[D] - it.Size.File[Data.workNum].SizePara[B]);
					//Z深度
					if(it.Para.count*Z_LineDepth <= it.Size.File[Data.workNum].SizePara[L])
					{
						MMToPul_Line1[2] =  ConvertToMachineUnit(Z_MOTOR, HoleKnifeZ + it.Para.count*Z_LineDepth);
					}					
					MillLine(MMToPul_Line1[0], MMToPul_Line1[1], MMToPul_Line1[2], it.Basic.workPara.hole.lineSpd);//走直线
					it.Para.step = 7;
				}
				else
				{
					MMToPul_Line1[0] = GSR.AxisPosition[X_MOTOR];
					MMToPul_Line1[1] = GSR.AxisPosition[Y_MOTOR];
					it.Para.step = 7;
				}
			}
			break;
			
		case 7://第2点 -> 第3点
			if(HZ_AxGetCurPos(X_MOTOR) == MMToPul_Line1[0] && AxGetsta(X_MOTOR) == 0 
				&& HZ_AxGetCurPos(Y_MOTOR) == MMToPul_Line1[1]  && AxGetsta(Y_MOTOR) == 0 )				
			{
				if(it.Size.File[Data.workNum].SizePara[E] != 0 && it.Size.File[Data.workNum].SizePara[F] != 0)
				{
					MMToPul_Line1[3] =  ConvertToMachineUnit(X_MOTOR, HoleKnifeX_A + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[E]));
					MMToPul_Line1[4] = ConvertToMachineUnit(Y_MOTOR, Data.HoleKnifeY_B + it.Size.File[Data.workNum].SizePara[F] - it.Size.File[Data.workNum].SizePara[B]);
					if(it.Para.count*Z_LineDepth <= it.Size.File[Data.workNum].SizePara[L])
					{
						MMToPul_Line1[5] = ConvertToMachineUnit(Z_MOTOR, HoleKnifeZ + it.Para.count*Z_LineDepth);
					}
					MillLine(MMToPul_Line1[3], MMToPul_Line1[4], MMToPul_Line1[5], it.Basic.workPara.hole.lineSpd);//走直线					
					it.Para.step = 8;
				}
				else
				{
					MMToPul_Line1[3] = GSR.AxisPosition[X_MOTOR];
					MMToPul_Line1[4] = GSR.AxisPosition[Y_MOTOR];
					it.Para.step = 8;
				}
			}
			break;
			
		case 8://第3点 -> 第4点
			if(HZ_AxGetCurPos(X_MOTOR) == MMToPul_Line1[3] && AxGetsta(X_MOTOR) == 0 
				&& HZ_AxGetCurPos(Y_MOTOR) == MMToPul_Line1[4]  && AxGetsta(Y_MOTOR) == 0 )				
			{
				if(it.Size.File[Data.workNum].SizePara[G] != 0 && it.Size.File[Data.workNum].SizePara[H] != 0)
				{
					MMToPul_Line1[6] =  ConvertToMachineUnit(X_MOTOR, HoleKnifeX_A + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[G]));
					MMToPul_Line1[7] = ConvertToMachineUnit(Y_MOTOR, Data.HoleKnifeY_B - (it.Size.File[Data.workNum].SizePara[B] - it.Size.File[Data.workNum].SizePara[H]));
					if(it.Para.count*Z_LineDepth <= it.Size.File[Data.workNum].SizePara[L])
					{
						MMToPul_Line1[8] = ConvertToMachineUnit(Z_MOTOR, HoleKnifeZ + it.Para.count*Z_LineDepth);
					}
					MillLine(MMToPul_Line1[6], MMToPul_Line1[7], MMToPul_Line1[8], it.Basic.workPara.hole.lineSpd);//走直线				
					it.Para.step = 9;//
				}
				else
				{
					MMToPul_Line1[6] = GSR.AxisPosition[X_MOTOR];
					MMToPul_Line1[7] = GSR.AxisPosition[Y_MOTOR];
					it.Para.step = 9;
				}
			}
			break;
			
		case 9://第4点 -> 第5点
			if(HZ_AxGetCurPos(X_MOTOR) == MMToPul_Line1[6] && AxGetsta(X_MOTOR) == 0 
				&& HZ_AxGetCurPos(Y_MOTOR) == MMToPul_Line1[7]  && AxGetsta(Y_MOTOR) == 0 )				
			{
				if(it.Size.File[Data.workNum].SizePara[I] != 0 && it.Size.File[Data.workNum].SizePara[J] != 0)
				{
					MMToPul_Line1[9] =  ConvertToMachineUnit(X_MOTOR,  HoleKnifeX_A + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[I]));
					MMToPul_Line1[10] = ConvertToMachineUnit(Y_MOTOR, Data.HoleKnifeY_B - (it.Size.File[Data.workNum].SizePara[B] - it.Size.File[Data.workNum].SizePara[J]));
					if(it.Para.count*Z_LineDepth <= it.Size.File[Data.workNum].SizePara[L])
					{
						MMToPul_Line1[11] = ConvertToMachineUnit(Z_MOTOR, HoleKnifeZ + it.Para.count*Z_LineDepth);
					}				
					MillLine(MMToPul_Line1[9], MMToPul_Line1[10], MMToPul_Line1[11], it.Basic.workPara.hole.lineSpd);//走直线
					it.Para.step = 10;//
				}
				else
				{
					MMToPul_Line1[9] = GSR.AxisPosition[X_MOTOR];
					MMToPul_Line1[10] = GSR.AxisPosition[Y_MOTOR];
					it.Para.step = 10;
				}
			}
			break;
			
		case 10://第5点 -> 第1点
			if(HZ_AxGetCurPos(X_MOTOR) == MMToPul_Line1[9] && AxGetsta(X_MOTOR) == 0 
				&& HZ_AxGetCurPos(Y_MOTOR) == MMToPul_Line1[10]  && AxGetsta(Y_MOTOR) == 0 )				
			{
				MMToPul_Line1[12] =  ConvertToMachineUnit(X_MOTOR,  HoleKnifeX_A);
				MMToPul_Line1[13] = ConvertToMachineUnit(Y_MOTOR, Data.HoleKnifeY_B);
				if(it.Para.count*Z_LineDepth <= it.Size.File[Data.workNum].SizePara[L])
				{
					MMToPul_Line1[14] = ConvertToMachineUnit(Z_MOTOR, HoleKnifeZ + it.Para.count*Z_LineDepth);
				}
				MillLine(MMToPul_Line1[12], MMToPul_Line1[13], MMToPul_Line1[14], it.Basic.workPara.hole.lineSpd);//走直线
				it.Para.step = 11;//
			}
			break;
			
		case 11://判断进刀量是否到达总深度
			if(HZ_AxGetCurPos(X_MOTOR) == MMToPul_Line1[12] && AxGetsta(X_MOTOR) == 0 
				&& HZ_AxGetCurPos(Y_MOTOR) == MMToPul_Line1[13]  && AxGetsta(Y_MOTOR) == 0 )				
			{
				if(it.Para.count*Z_LineDepth < it.Size.File[Data.workNum].SizePara[L])
				{
					if((it.Para.count+1)*Z_LineDepth <= it.Size.File[Data.workNum].SizePara[L])
					{
						it.Para.count++;
						it.Para.step = 4;
					}
					else
					{						
						AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.riftSpd , GSR.AxisUnitPos[Z_MOTOR] + it.Size.File[Data.workNum].SizePara[L] - it.Para.count*Z_LineDepth);						
						MMToPul_Line1[2] = ConvertToMachineUnit(Z_MOTOR, GSR.AxisUnitPos[Z_MOTOR] + it.Size.File[Data.workNum].SizePara[L] - it.Para.count*Z_LineDepth);
						MMToPul_Line1[5] = MMToPul_Line1[2];
						MMToPul_Line1[8] = MMToPul_Line1[2];
						MMToPul_Line1[11] = MMToPul_Line1[2];
						MMToPul_Line1[14] = MMToPul_Line1[2];
						it.Para.count++;
						TimerRst(it.Para);
						it.Para.step = 5;
					}
				}
				else
				{
					it.Para.step = 12;
				}
			}
			break;
			
		case 12://铣折线完成，Z回安全位置
			if(AxGetsta(Z_MOTOR) == 0)
			{
				PARAINIT(it.Para);
			}
			break;
	}
}

/**
* @author：nyh 20200112
* @Description:	孔刀水平圆弧(1刀2刀共用)
* @param --
* @return --
*/
void KnifeLevelArc(ShapeDef *t, int KnifeNum)
{	
	u8 i;
	static float Door_Y1 = 0;
	static float Door_X1 = 0;
	static float Z_KnifArc1Depth = 0;
	
	static float ArcPos_Move1 = 0;
	static float ArcEndMove1 = 0;
	static u8 EndFlag1 = 0;
	
	static float HoleKnifeZ = 0;
	static float HoleKnifeX_A = 0;
	static float HoleKnifeOffset = 0;
	static float knifeKD = 0;
	switch(it.Para.step)
	{			
		case 1://
			if(KnifeNum == 0)
			{	//1刀
				HoleKnifeZ = HoleKnifeZ;
				HoleKnifeX_A = Data.Hole1KnifeX_A;
				HoleKnifeOffset = it.Basic.mechanicalPara.X.holeK1Offset;
				knifeKD = it.Basic.workPara.hole.knife1KD;
			}
			else//2刀
			{
				HoleKnifeZ =  Data.Hole2KnifeZ;
				HoleKnifeX_A = Data.Hole2KnifeX_A;
				HoleKnifeOffset = it.Basic.mechanicalPara.X.holeKSpace + it.Basic.mechanicalPara.X.holeK1Offset;
				knifeKD = it.Basic.workPara.hole.knife2KD;
			}
						
			if(it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2 >= 2*knifeKD/2)
			{
				ArcPos_Move1 = (it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2)/ (knifeKD/2);
			}
			else if(it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2 >= knifeKD/2)
			{
				ArcPos_Move1 = (it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2)/ (knifeKD/4);
			}
			else
			{
				ArcPos_Move1 = (it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2)/ (knifeKD/6);
			}
			Z_KnifArc1Depth = it.Size.File[Data.workNum].SizePara[F];
			if(Z_KnifArc1Depth > it.Size.File[Data.workNum].SizePara[E])
			{
				if(it.Size.File[Data.workNum].SizePara[E] >= 100)
				{
					Z_KnifArc1Depth = it.Size.File[Data.workNum].SizePara[E]/30;
				}
				else if(it.Size.File[Data.workNum].SizePara[E] > 50)
				{
					Z_KnifArc1Depth = it.Size.File[Data.workNum].SizePara[E]/20;
				}
				else if(it.Size.File[Data.workNum].SizePara[E] > 30)
				{
					Z_KnifArc1Depth = it.Size.File[Data.workNum].SizePara[E]/10;
				}
				else if(it.Size.File[Data.workNum].SizePara[E] > 10)
				{
					Z_KnifArc1Depth = it.Size.File[Data.workNum].SizePara[E]/6;
				}
				else 
				{
					Z_KnifArc1Depth = it.Size.File[Data.workNum].SizePara[E]/2;
				}
			}	
			Door_X1 = it.Basic.workPara.Slot_Stair.slotKLenX - it.Size.File[Data.workNum].SizePara[D] + HoleKnifeOffset;
			Door_Y1 = it.Basic.checkPara.Check.horizonLenY - it.Basic.mechanicalPara.Y.holeKLen + it.Basic.mechanicalPara.checkLumpThick;
			it.Para.count++;
			it.Para.step = 2;
			break;
			
		case 2://Z下刀
			if(AxGetsta(Z_MOTOR) == 0 && LT.ChangerSpeed_ONTask.execute == 0)
			{		
				AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.holeSpd , HoleKnifeZ + it.Para.count*Z_KnifArc1Depth);							
				it.Para.step = 3;
			}
			break;
			
		case 3:
			if(AxGetsta(Z_MOTOR) == 0)
			{		
				if(it.Para.index*ArcPos_Move1 < it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2)
				{	
					AxRun(X_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_X1 + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
				
					if((it.Para.index+1)*ArcPos_Move1 <= it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2)//判读宽度是否到达
					{		
						EndFlag1 = 0;
						it.Para.index++;						
						AxRun(Y_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_Y1 + it.Size.File[Data.workNum].SizePara[C] + it.Para.index*ArcPos_Move1);
						it.Para.step = 4;
					}
					else
					{	
						EndFlag1 = 1;
						ArcEndMove1 = it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2 - it.Para.index*ArcPos_Move1;
						AxRun(Y_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_Y1 + it.Size.File[Data.workNum].SizePara[C] + it.Para.index*ArcPos_Move1 + ArcEndMove1);
						it.Para.index++;
						it.Para.step = 4;
					}
				}
				else//XY 递进结束
				{
//					it.Para.index--;
					it.Para.step = 9;//
				}
			}
			break;
									
		case 4://X 铣长度
			if(AxGetsta(Z_MOTOR) == 0 && AxGetsta(X_MOTOR) == 0 && AxGetsta(Y_MOTOR) == 0)
			{
				AxRun(X_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_X1 - (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
				it.Para.step = 5;
			}
			break;
			
		case 5:// 逆时针走圆弧  2->3->4
			if(AxGetsta(X_MOTOR) == 0)
			{
				//mm转换脉冲
				//3
				if(EndFlag1 == 1)
				{
					MMToPul_KnifeArc1[0] = ConvertToMachineUnit(X_MOTOR, Door_X1 - (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2 - ((it.Para.index-1) * ArcPos_Move1+ArcEndMove1));
					MMToPul_KnifeArc1[3] = ConvertToMachineUnit(Y_MOTOR, Door_Y1 + it.Size.File[Data.workNum].SizePara[C] - ((it.Para.index-1) * ArcPos_Move1+ArcEndMove1));
				}
				else
				{
					MMToPul_KnifeArc1[0] = ConvertToMachineUnit(X_MOTOR, Door_X1 - (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2 - it.Para.index * ArcPos_Move1);
					MMToPul_KnifeArc1[3] = ConvertToMachineUnit(Y_MOTOR, Door_Y1 + it.Size.File[Data.workNum].SizePara[C] - it.Para.index * ArcPos_Move1);
				}
				
				MMToPul_KnifeArc1[1] = ConvertToMachineUnit(Y_MOTOR, Door_Y1 + it.Size.File[Data.workNum].SizePara[C]);
				//4			    
				MMToPul_KnifeArc1[2] = ConvertToMachineUnit(X_MOTOR, Door_X1 - (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
							
				MillArc(X_MOTOR, Y_MOTOR, MMToPul_KnifeArc1[0], MMToPul_KnifeArc1[1], MMToPul_KnifeArc1[2], MMToPul_KnifeArc1[3], it.Basic.workPara.hole.circSpd);				
				it.Para.step = 6;
			}
			break;
			
		case 6://1刀右铣X长度  4—>5
			if(HZ_AxGetCurPos(X_MOTOR) == MMToPul_KnifeArc1[2] && AxGetsta(X_MOTOR) == 0 
				&& HZ_AxGetCurPos(Y_MOTOR) == MMToPul_KnifeArc1[3] && AxGetsta(Y_MOTOR) == 0 )
			{
				AxRun(X_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_X1 + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
				it.Para.step = 7;
			}
			break;
			
		case 7://铣圆弧  5->6->1
			if(AxGetsta(X_MOTOR) == 0)
			{	//6  
				if(EndFlag1 == 1)
				{
					MMToPul_KnifeArc1[4] = ConvertToMachineUnit(X_MOTOR, Door_X1 + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2 + ((it.Para.index-1) * ArcPos_Move1+ArcEndMove1));
					MMToPul_KnifeArc1[7] = ConvertToMachineUnit(Y_MOTOR, Door_Y1 + it.Size.File[Data.workNum].SizePara[C] + ((it.Para.index-1) *ArcPos_Move1+ArcEndMove1));
				}
				else
				{
					MMToPul_KnifeArc1[4] = ConvertToMachineUnit(X_MOTOR, Door_X1 + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2 + it.Para.index * ArcPos_Move1);
					MMToPul_KnifeArc1[7] = ConvertToMachineUnit(Y_MOTOR, Door_Y1 + it.Size.File[Data.workNum].SizePara[C] + it.Para.index *ArcPos_Move1);
				}
				
				MMToPul_KnifeArc1[5] = ConvertToMachineUnit(Y_MOTOR, Door_Y1 + it.Size.File[Data.workNum].SizePara[C]);
				//1				
				MMToPul_KnifeArc1[6] = ConvertToMachineUnit(X_MOTOR, Door_X1 + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
								
				MillArc(X_MOTOR, Y_MOTOR, MMToPul_KnifeArc1[4], MMToPul_KnifeArc1[5], MMToPul_KnifeArc1[6], MMToPul_KnifeArc1[7], it.Basic.workPara.hole.circSpd);
				it.Para.step = 8;
			}
			break;
						
		case 8://XY 递进次数改变
			if(HZ_AxGetCurPos(X_MOTOR) == MMToPul_KnifeArc1[6] && AxGetsta(X_MOTOR) == 0 
				&& HZ_AxGetCurPos(Y_MOTOR) == MMToPul_KnifeArc1[7] && AxGetsta(Y_MOTOR) == 0 )
			{
				if(it.Para.count%2 != 0)//进刀单数
				{
//					it.Para.index++;
					it.Para.step = 3;
				}
				else//双数
				{
					if(it.Para.index > 1)
					{
						it.Para.index--;
						it.Para.step = 10;
					}
					else
					{
						it.Para.step = 9;
					}
				}
			}
			break;
			
		case 9://判断进刀深度E
			if(AxGetsta(Y_MOTOR) == 0)
			{
				if(it.Para.count* Z_KnifArc1Depth< it.Size.File[Data.workNum].SizePara[E])
				{
					if((it.Para.count+1)*Z_KnifArc1Depth <= it.Size.File[Data.workNum].SizePara[E])
					{						
						it.Para.count++;
						if(it.Para.count*Z_KnifArc1Depth < it.Size.File[Data.workNum].SizePara[E])
						{
							AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.holeSpd , HoleKnifeZ + it.Para.count*Z_KnifArc1Depth);
							it.Para.step = 4;							
						}
						else if(it.Para.count*Z_KnifArc1Depth == it.Size.File[Data.workNum].SizePara[E])
						{
							AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.holeSpd , HoleKnifeZ + it.Para.count*Z_KnifArc1Depth-2);	
							it.Para.step = 0xa3;
						}						
					}
					else
					{
						AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.riftSpd , GSR.AxisUnitPos[Z_MOTOR] + it.Size.File[Data.workNum].SizePara[E] - it.Para.count*Z_KnifArc1Depth);
						it.Para.count++;
						it.Para.step = 4;
					}
				}
				else
				{
					it.Para.step = 11;
				}
			}
			break;
			
		case 0xa3://最后2mm破孔速度
			if(AxGetsta(Z_MOTOR) == 0)
			{
				AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.riftSpd , HoleKnifeZ + it.Para.count*Z_KnifArc1Depth);	
				it.Para.step = 4;
			}
			break;
		
		case 10://XY 递进
			if(AxGetsta(Y_MOTOR) == 0)
			{		
				if(EndFlag1 == 1)
				{
					AxRun(Y_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_Y1 + it.Size.File[Data.workNum].SizePara[C] + it.Para.index*ArcPos_Move1 + ArcEndMove1);
				}
				else
				{
					AxRun(Y_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_Y1 + it.Size.File[Data.workNum].SizePara[C] + it.Para.index*ArcPos_Move1);
				}				
				AxRun(X_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_X1 - (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
				it.Para.step = 4;
			}			
			break;	
			
		case 11://等待延时，Z回安全高度
			if(AxGetsta(Z_MOTOR) == 0)
			{
				PARAINIT(it.Para);
			}
			break;
	}	
}

/**
* @author：nyh 20191025
* @Description:	竖立圆弧(1刀2刀共用)
* @param --
* @return --
*/
void KnifeStandArc(ShapeDef *t, int KnifeNum)
{
	u8 i;
	static float Door_Y2 = 0;
	static float Door_X2 = 0;
	static float Z_KnifArc2Depth = 0;
	static float Len_Move2 = 0;
	static float ArcPos_Move2 = 0;
	static float ArcEndMove2 = 0;
	static u8 EndFlag2 = 0;
	
	static float HoleKnifeZ = 0;
	static float HoleKnifeX_A = 0;
	static float HoleKnifeOffset = 0;
	static float knifeKD = 0;
	if(it.Para.execute == 1 && it.Para.step == 0)
	{
		it.Para.step = 1;
	}
	switch(it.Para.step)
	{			
		case 1://
			if(KnifeNum == 0)
			{	//1刀
				HoleKnifeZ = HoleKnifeZ;
				HoleKnifeX_A = Data.Hole1KnifeX_A;
				HoleKnifeOffset = it.Basic.mechanicalPara.X.holeK1Offset;
				knifeKD = it.Basic.workPara.hole.knife1KD;
			}
			else//2刀
			{
				HoleKnifeZ =  Data.Hole2KnifeZ;
				HoleKnifeX_A = Data.Hole2KnifeX_A;
				HoleKnifeOffset = it.Basic.mechanicalPara.X.holeKSpace + it.Basic.mechanicalPara.X.holeK1Offset;
				knifeKD = it.Basic.workPara.hole.knife2KD;
			}			
			
			if(it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2 >= 2*knifeKD/2)
			{
				ArcPos_Move2 = (it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2)/ (knifeKD/2);
			}
			else if(it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2 >= knifeKD/2)
			{
				ArcPos_Move2 = (it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2)/ (knifeKD/4);
			}
			else
			{
				ArcPos_Move2 = (it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2)/ (knifeKD/6);
			}
			Z_KnifArc2Depth = it.Size.File[Data.workNum].SizePara[F];
			if(Z_KnifArc2Depth > it.Size.File[Data.workNum].SizePara[E])
			{
				Z_KnifArc2Depth = it.Size.File[Data.workNum].SizePara[E];
			}
			Door_X2 = it.Basic.workPara.Slot_Stair.slotKLenX - it.Size.File[Data.workNum].SizePara[D] + HoleKnifeOffset;
			Door_Y2 = it.Basic.checkPara.Check.horizonLenY - it.Basic.mechanicalPara.Y.holeKLen + it.Basic.mechanicalPara.checkLumpThick;
			it.Para.step = 2;
			break;
			
		case 2:
			if(AxGetsta(Z_MOTOR) == 0)
			{				
				it.Para.count++;
				it.Para.step = 5;
			}
			break;
			
		case 5://Z下刀
			if(AxGetsta(Z_MOTOR) == 0)
			{		
				AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.holeSpd , Data.Hole1KnifeZ + it.Para.count*Z_KnifArc2Depth);							
				it.Para.step = 6;
			}
			break;
			
		case 6:
			if(AxGetsta(Z_MOTOR) == 0)
			{				
				if(it.Para.index*ArcPos_Move2 < it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2)
				{	
					AxRun(Y_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_Y2 + it.Size.File[Data.workNum].SizePara[C] + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
				
					if((it.Para.index+1)*ArcPos_Move2 <= it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2)//判读宽度是否到达
					{		
						EndFlag2 = 0;
						it.Para.index++;						
						AxRun(X_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_X2 - it.Para.index*ArcPos_Move2);
						it.Para.step = 7;
					}
					else
					{	
						EndFlag2 = 1;
						ArcEndMove2 = it.Size.File[Data.workNum].SizePara[B]/2 - knifeKD/2 - it.Para.index*ArcPos_Move2;
						AxRun(X_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_X2 - (it.Para.index*ArcPos_Move2 + ArcEndMove2));
						it.Para.index++;
						it.Para.step = 7;
					}
				}
				else//XY 递进结束
				{
//					it.Para.index--;
					it.Para.step = 12;//
				}
			}
			break;
									
		case 7://X 铣长度
			if(AxGetsta(Z_MOTOR) == 0 && AxGetsta(X_MOTOR) == 0 && AxGetsta(Y_MOTOR) == 0)
			{
				AxRun(Y_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_Y2 + it.Size.File[Data.workNum].SizePara[C] - (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
				it.Para.step = 8;
			}
			break;
			
		case 8:// 逆时针走圆弧  2->3->4
			if(AxGetsta(Y_MOTOR) == 0)
			{
				//mm转换脉冲
				//3
				if(EndFlag2 == 1)
				{
					MMToPul_KnifeArc1[1] = ConvertToMachineUnit(Y_MOTOR, Door_Y2 + it.Size.File[Data.workNum].SizePara[C] 
																- (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2 - ((it.Para.index-1) * ArcPos_Move2+ArcEndMove2));
					MMToPul_KnifeArc1[2] = ConvertToMachineUnit(X_MOTOR, Door_X2 + ((it.Para.index-1) * ArcPos_Move2+ArcEndMove2));
				}
				else
				{
					MMToPul_KnifeArc1[1] = ConvertToMachineUnit(Y_MOTOR, Door_Y2 + it.Size.File[Data.workNum].SizePara[C] 
																- (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2 - it.Para.index * ArcPos_Move2);
					MMToPul_KnifeArc1[2] = ConvertToMachineUnit(X_MOTOR, Door_X2 + it.Para.index * ArcPos_Move2);
				}
				MMToPul_KnifeArc1[0] = ConvertToMachineUnit(X_MOTOR, Door_X2);
				//4			    				
				MMToPul_KnifeArc1[3] = ConvertToMachineUnit(Y_MOTOR, Door_Y2 + it.Size.File[Data.workNum].SizePara[C] - (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
				
				MillArc(X_MOTOR, Y_MOTOR, MMToPul_KnifeArc1[0], MMToPul_KnifeArc1[1], MMToPul_KnifeArc1[2], MMToPul_KnifeArc1[3], it.Basic.workPara.hole.circSpd);				
				it.Para.step = 9;
			}
			break;
			
		case 9://1刀右铣X长度  4—>5
			if(HZ_AxGetCurPos(X_MOTOR) == MMToPul_KnifeArc1[2] && AxGetsta(X_MOTOR) == 0 
				&& HZ_AxGetCurPos(Y_MOTOR) == MMToPul_KnifeArc1[3] && AxGetsta(Y_MOTOR) == 0 )
			{
				AxRun(Y_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_Y2 + it.Size.File[Data.workNum].SizePara[C] + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
				it.Para.step = 10;
			}
			break;
			
		case 10://铣圆弧  5->6->1
			if(AxGetsta(Y_MOTOR) == 0)
			{	//6 
				if(EndFlag2 == 1)
				{
					MMToPul_KnifeArc1[5] = ConvertToMachineUnit(Y_MOTOR, Door_Y2 + it.Size.File[Data.workNum].SizePara[C] + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2+ ((it.Para.index-1) *ArcPos_Move2+ArcEndMove2));
					MMToPul_KnifeArc1[6] = ConvertToMachineUnit(X_MOTOR, Door_X2 - ((it.Para.index-1) *ArcPos_Move2+ArcEndMove2));
				}
				else
				{
					MMToPul_KnifeArc1[5] = ConvertToMachineUnit(Y_MOTOR, Door_Y2 + it.Size.File[Data.workNum].SizePara[C] + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2+ it.Para.index *ArcPos_Move2);
					MMToPul_KnifeArc1[6] = ConvertToMachineUnit(X_MOTOR, Door_X2 - it.Para.index *ArcPos_Move2);
				}
				MMToPul_KnifeArc1[4] = ConvertToMachineUnit(X_MOTOR, Door_X2 );		
				//1								
				MMToPul_KnifeArc1[7] = ConvertToMachineUnit(Y_MOTOR, Door_Y2 + it.Size.File[Data.workNum].SizePara[C] + (it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);
				
				MillArc(X_MOTOR, Y_MOTOR, MMToPul_KnifeArc1[4], MMToPul_KnifeArc1[5], MMToPul_KnifeArc1[6], MMToPul_KnifeArc1[7], it.Basic.workPara.hole.circSpd);
				it.Para.step = 11;
			}
			break;
						
		case 11://XY 递进次数改变
			if(HZ_AxGetCurPos(X_MOTOR) == MMToPul_KnifeArc1[6] && AxGetsta(X_MOTOR) == 0 
				&& HZ_AxGetCurPos(Y_MOTOR) == MMToPul_KnifeArc1[7] && AxGetsta(Y_MOTOR) == 0 )
			{
				if(it.Para.count%2 != 0)//进刀单数
				{
//					it.Para.index++;
					it.Para.step = 6;
				}
				else//双数
				{
					if(it.Para.index > 1)
					{
						it.Para.index--;
						it.Para.step = 13;
					}
					else
					{
						it.Para.step = 12;
					}
				}
			}
			break;
			
		case 12://判断进刀深度E
			if(AxGetsta(Y_MOTOR) == 0)
			{
				if(it.Para.count* Z_KnifArc2Depth< it.Size.File[Data.workNum].SizePara[E])
				{
					if((it.Para.count+1)*Z_KnifArc2Depth <= it.Size.File[Data.workNum].SizePara[E])
					{						
						it.Para.count++;
						if(it.Para.count*Z_KnifArc2Depth < it.Size.File[Data.workNum].SizePara[E])
						{
							AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.holeSpd , Data.Hole1KnifeZ + it.Para.count*Z_KnifArc2Depth);
							it.Para.step = 7;
						}
						else if(it.Para.count*Z_KnifArc2Depth == it.Size.File[Data.workNum].SizePara[E])
						{
							AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.holeSpd , Data.Hole1KnifeZ + it.Para.count*Z_KnifArc2Depth-2);
							it.Para.step = 0xa3;
						}							
					}
					else
					{
						AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.riftSpd , GSR.AxisUnitPos[Z_MOTOR] + it.Size.File[Data.workNum].SizePara[E] - it.Para.count*Z_KnifArc2Depth);
						it.Para.count++;
						it.Para.step = 7;
					}
				}
				else
				{
					it.Para.step = 14;
				}
			}
			break;
			
		case 0xa3://最后2mm破孔速度
			if(AxGetsta(Z_MOTOR) == 0)
			{
				AxRun(Z_MOTOR, ABSMODE, it.Basic.workPara.hole.riftSpd , Data.Hole1KnifeZ + it.Para.count*Z_KnifArc2Depth);	
				it.Para.step = 7;
			}
			break;
		
		case 13://XY 递进
			if(AxGetsta(Y_MOTOR) == 0)
			{	
				if(EndFlag2 == 1)
				{
					AxRun(X_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_X2 - (it.Para.index*ArcPos_Move2 + ArcEndMove2));
				}
				else
				{
					AxRun(X_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_X2 - it.Para.index*ArcPos_Move2);
				}
				AxRun(Y_MOTOR, ABSMODE, it.Basic.workPara.hole.lineSpd , Door_Y2 + it.Size.File[Data.workNum].SizePara[C] +(it.Size.File[Data.workNum].SizePara[A] - it.Size.File[Data.workNum].SizePara[B])/2);				
				it.Para.step = 7;
			}			
			break;	
			
		case 14:
			if(AxGetsta(Z_MOTOR) == 0)
			{
				PARAINIT(it.Para);
			}
			break;
	}	
}

////铣圆开始
//void MillCirc1_start(ShapeDef *t) 
//{
//	it.Para.execute = 1;
//}
////铣圆完成
//s32 MillCirc1_End(ShapeDef *t)
//{
//	if(it.Para.execute == 0)
//	{
//		if(it.Para.done == 1)
//			return 0;
//		else
//			return 1;
//	}
//	else
//		return -1;
//}

////铣圆终止
//void MillCirc1_Over(ShapeDef *t) 
//{
//	it.Over = 1;
//}
