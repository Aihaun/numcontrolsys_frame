#ifndef __RESET__H
#define __RESET__H

#include "logic.h"
#include "fsm.h"

extern void Reset(LogicParaDef *T);

extern void XYZW_Reset(LogicParaDef* Task);
extern void Ax_GoHome(LogicParaDef Task[]);//������ƫ��ԭ��
#endif
