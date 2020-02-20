2018-12-12 八轴卡标准公司代码  杨福松
1.更新:interlayer 库更新接口和写法. 更新地址表地址.后期更新地址更灵活
  主要区别函数:init_config(&GlobalData,GSR.ErrorCode,&GlobalData.SpaceType.Save,GLOBALDATALEN,USERWRITELEN,USERREADLEN,USERSAVELEN);
  地址表区别:输入输出数组扩大,点动速度地址更改.所有设备状态,运行等地址全部移除,使用时在用户区自己定义.用户地址长度成为参数传入(系统地址长度已经固定,禁止修改)
2.interlayer.c 文件中添加了3个点动函数,方便项目中添加扩展卡后程序的更改.
  void JogGo(u8 axisnum,s32 pos,s8 dir,u8 spd)
  void jogstop(u32 axisnum)
  void joghome(u32 axisnum)
3.添加3个扩展卡io程序,方便扩展使用.
void ex_inputupdata()
void ex_outputstatusupdata()
void ex_outputupdata()
4.删除flash清零功能
5.待完善:
  本次更新善有很多tool.c中的函数需要提供,但本人项目有限,库中并没有提供.大家可以将以前工程中的函数自己移植进usertool.c中.
在1月31日之前,我会统计收集,做统一更新.

2019/03/01
添加锁机加密等函数。
流程写法改进，函数封装规则跟新。
工程样板脱离板卡型号，更改板卡时，在标准库中找到对应的库进行更新。
特别说明：输入状态显示的地址分配：[0][1]为主板i口资源 ；[2]前16位是报警口，后16位是报警输入；[3]前4位是ab相输入；

2019/03/13 
文件夹细分。将动作不相关的函数移出logic函数体。
地址表更新，轴配置相关跟新。添加轴移动接口函数给上位机统一使用。
其他工程写法跟新。单独培训。

2019/03/14
库跟新，将轴库和中间库合并，替换原来的LIB文件夹里的interlayer_config.h，删除axislib.h。现在只保留三个库文件：
curve.lib   bsplib.lib    interlayer.lib    头文件：bsplib.h    curve.h   interlayer_config.h   lock.h 
函数跟新：库中将轴报警输入口的报警写进轴口配置，在库中更改，增加HZ_AxSetAlm(u8 i,u32 lev) 函数，配置轴报警
口读取报警的电平。增加Z向回零模式,模式3正向找z向，模式4反向找z向。(需要更改部分：将tool文件夹下的AxisMove.c
和AxisMove.h替换。替换config文件夹Axisconfig.c)

2019/03/19
修改bsp_config.c函数。因为fpga板卡在使用时，此处需要多配置一项。给大家写了三种配置函数，大家选择使用，也可以
在自己文件中照着添加即可。

2019/04/01
增加运行中改变速度函数。回零函数更改.增加z向回零

2019/4/12
增加插补，增加插补轴状态获取。




