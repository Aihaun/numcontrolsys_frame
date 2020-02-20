#include "Teach.h"
#include "string.h"
#include "stdio.h"
#include "logic.h"

//extern SysData Data;


//static void getnamenum(char* scr)
//{
//    int j = 0;
//	memset(Data.namenum, 0, sizeof(Data.namenum));
//    for(int i=0;; i++)
//    {
//        if(scr[i] == '\r')
//        {
//            Data.namenum[j]=i;
//            j++;
//        }
//        if(scr[i]==0)	
//            break;
//    }
//}
//static void catname(char* scr)
//{
//    int i;
//	memset(Data.name, 0, sizeof(Data.name));
//    for(i=0;; i++)
//    {
//        if(Data.namenum[i]>0)
//        {
//            memset(Data.name[i],0,20);
//            if(i==0)
//            {
//                strncpy(Data.name[i],scr,Data.namenum[0]);
//            }
//            else
//            {
//                strncpy(Data.name[i], scr+Data.namenum[i-1]+2, Data.namenum[i]-Data.namenum[i-1]-2);
//            }
//        }
//        else
//            break;
//    }
//}
//static void setdata(int index)
//{
//	
//    for(int i= 0; i < 10; i++)
//    {
//        strcpy(GUW.EditFile.filname[i],Data.name[i + index * 10]);
//    }
//}


void Teach()
{
	u32 i;
	s32 Datadef[100]={-1};
	u32 Flag;
//    char res;
//    char path[100] = {0};
	switch(GUW.button.Data.TeachCMD)	//1502
	{
	case 1:	//文件初始化
//        memset(GUW.EditFile.filname, 0, sizeof(GUW.EditFile.filname));
//		Data.flname = NULL;
//		Data.flname = File_List("teach");
//        getnamenum(Data.flname);
//        catname(Data.flname); 
//        setdata(GUW.button.Data.page);
		GUW.button.Data.TeachCMD = 0;
		break;
	case 2:	//保存程序文件
//        sprintf(path,"teach/%s", GUS.WorkFile.workfilename);
//        res = File_Write(path,&GUS.WorkFile.File,0,sizeof(GUS.WorkFile.File),0);
//        if(res)
//        {
//            AlarmSetBit(1,1,res);	//0：写成功，其他：写失败
//        }
		GUW.button.Data.TeachCMD = 0;
		break;
	case 3:	//新建文件名页面  确定按钮	
//		for(int i = 0; i < 400; i++)	//查询文件是否重名
//		{
//			if(strlen(Data.name[i]) == 0)	//没有重名文件
//			{
//				memset(&GUS.WorkFile, 0, sizeof(GUS.WorkFile));
//				memcpy(GUS.WorkFile.workfilename, GUW.EditFile.newfilename, sizeof(GUS.WorkFile.workfilename));
//				memset(&GUW.EditFile.newfilename, 0, sizeof(GUW.EditFile.newFilePara));
//				break;
//			}else if(strcmp(Data.name[i], GUW.EditFile.newfilename) == 0)
//			{	
//				AlarmSetBit(1, 0, 2);	//文件重名
//				break;
//			}
//		}
		GUW.button.Data.TeachCMD = 0;
		break;
	case 4:	//新建文件名页面  取消按钮
//		memset(&GUW.EditFile.newFilePara, 0, sizeof(FileParaDef));
		GUW.button.Data.TeachCMD = 0;
		break;
//	case 5:	//打开孔类型页面  index要先发送
//		memset(GUW.EditFile.newFilePara, 0, sizeof(FileParaDef));
//		memcpy(GUW.EditFile.newFilePara, GUS.WorkFile.File[GUW.EditFile.index], sizeof(FileParaDef));
//		GUW.button.Data.TeachCMD = 0;
//		break;
	case 6:	//孔类型页面 保存退出
		memset(&GUS.BasicPara.WorkFile.File[GUW.EditFile.index], 0, sizeof(FileParaDef));
		memcpy(&GUS.BasicPara.WorkFile.File[GUW.EditFile.index], &GUW.EditFile.newFilePara, sizeof(FileParaDef));
		memset(&GUW.EditFile.newFilePara, 0, sizeof(FileParaDef));
		GUW.button.Data.TeachCMD = 0;
		break;
	case 7:	//孔类型页面 清除
//		memset(&GUW.EditFile.newFilePara, 0, sizeof(GUW.EditFile.newFilePara));
		GUW.button.Data.TeachCMD = 0;
		break;
	case 8:	//选择文件页面 打开选择文件  
		GUW.button.Data.TeachCMD = 0;
//		memset(&GUS.WorkFile.File, 0, sizeof(GUS.WorkFile.File));
//        if(strlen(GUS.WorkFile.workfilename) == 0)
//        {
//            AlarmSetBit(1,0,4); //打开的文件是空
//            break;
//        } else {
//            sprintf(path,"teach/%s",GUS.WorkFile.workfilename);
//            File_Read(path,&GUS.WorkFile.File,0,sizeof(GUS.WorkFile.File),0);
//        }
		break;
	case 9:	//选择文件页面 删除选择文件  
		GUW.button.Data.TeachCMD = 0;
//		sprintf(path,"teach/%s",GUS.WorkFile.workfilename);
//		res = File_Delete(path,0);
//		if(res)
//		{
//			AlarmSetBit(1,1,res);//0：成功，其他：失败
//			break;
//		}
//		memset(&GUS.WorkFile, 0, sizeof(GUS.WorkFile));
//		GUW.button.Data.TeachCMD = 1;	//删除成功后，重新读取文件
		break;
		
	case 10://清产能
		PARAINIT(GUS.ProductPara);
		GUW.button.Data.TeachCMD = 0;
		break;
	
	case 11://写Flash保存
		GSW.FlashOperate = 2;
		GUW.button.Data.TeachCMD = 0;
		break;
	
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	
	case 20://新建文件编号
		for(u8 i=0; i<100; i++)
		{
			if(GUS.ProdNum[i] == GUW.EditFile.workfilenum[0])//GUS.ProdNum[i]  初始化都为 -1
			{
				Flag = 1;				
				break;
			}
		}
		if(Flag != 1)
		{			
			for(u8 i=0; i<100; i++)
			{
				if(GUS.ProdNum[i] == -1)
				{
					GUS.ProdNum[i] = GUW.EditFile.workfilenum[0];
					break;
				}
			}
			Flag = 0;
		}
		else
		{
			//产品编号重名
			AlarmSetBit(1, 0, 2);	//文件重名
		}
		memset(&GUS.BasicPara.WorkFile, 0, sizeof(GUS.BasicPara.WorkFile));
		memcpy(GUS.BasicPara.WorkFile.workfilename, GUW.EditFile.newfilename, sizeof(GUS.BasicPara.WorkFile.workfilename));
		memset(&GUW.EditFile.newfilename, 0, sizeof(GUW.EditFile.newFilePara));
		GUW.button.Data.TeachCMD = 0;
		break;
	
	case 21://删除文件,编号数据后面往前移动
		for(i=GUW.button.Data.page*10 + GUW.EditFile.workfilenum[1]; i<100; i++)
		{
			Datadef[i] = GUS.ProdNum[i+1];
		}
		for(i=GUW.button.Data.page*10 + GUW.EditFile.workfilenum[1]; i<100; i++)
		{
			GUS.ProdNum[i] = Datadef[i];
		}
		GUW.button.Data.TeachCMD = 0;
		break;
		
		
	}
}

