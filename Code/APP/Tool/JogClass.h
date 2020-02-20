#ifndef _JOGCLASS_H_
#define	_JOGCLASS_H_

#include "axismove.h"
#include "datadefine.h"
#include "Logic.h"

	typedef struct
	{
		float	JogSpd;
		float	JogUnitPos;
		u32	JogForward;
		u32	JogBackward;
		u32	JogHome;
		u32	JogStop;
	}JogDataDef;
	
	extern void AxLoop(void);
	extern void JogFunc(JogDataDef *p);
	
#endif

