#ifndef __FSM_H
#define __FSM_H

#include "Logic.h"
#include "reset.h"
#include "axismove.h"
#include "Teach.h"

typedef enum
{
    INIT,	//初始态
    STOP,       //停止态
    RUN	,       //运行态
    D_RESET,    //复位态
    SCRAM,      //急停态
    PAUSE,      //暂停态
    SIGSTEP,     //单步运行
    SIGRUN,		//单次运行
} RunStatus;

extern void FSM(void);

#endif

