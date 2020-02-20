//#include "bsp.h"
#include "interlayer.h"     
#include "bsp_config.h"    
#include "appinit.h" 
#include "lock.h" 
#include "MainTask.h"

const unsigned char*HARD_VER = (unsigned char*)0X803f000;
const unsigned char*BOOT_VER = (unsigned char*)0X803f040;
const unsigned char UserDev_Inf[3][64] = 
{
	"F305_Ver.01.02.03_Beta",
	"A305_Ver.01.03.11_Beta",
	"__Debug__"
//	"_Release_"
};

int main()
{
//    sys_init();
	sys_init_IAP();
    bsp_init();
    bsp_exec();

    AppInit();
	while(HZ_ExCanNetStateGet() != 2)
	{
 //       InterLayer();
        bsp_exec();
	}

    while(1)
    {
        InterLayer();
        bsp_exec();
		MainTask();   
    }
}


int pwr_Task(void)
{
//    HZ_Data_Write();
    return 0;
}




