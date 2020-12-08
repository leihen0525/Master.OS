/*
 * Init.Main.c
 *
 *  Created on: 2019年9月17日
 *      Author: Master.HE
 */
//#include "Master.OS.Config.h"

#include "Error.h"
#include "Define.h"

#include "Memory/Memory.h"
#include "IRQ/IRQ.h"
#include "Event/Event.h"
#include "Device/Device.h"
#include "Timer/Timer.h"
#include "Queue/Queue.h"
#include "Scheduling/Scheduling.h"
#include "Shell/Shell.h"
#include "MPU/MPU.h"
#include "BSP/BSP.h"

#include "Init.Machine.h"
#include "Init.Main.h"
#include "Init.Module.h"

#include "Task/Task.h"

#include "__Sys.API.h"




Machine_Desc_Type *Machine_Desc=Null;

void Start_Kernel(void)
{

	//初始化BSP设备树
	if(Machine_Init(&Machine_Desc)!=Error_OK)
	{
		while(1);
	}

	//初始化BSP
	if(BSP_Init(Machine_Desc->System_Reset,&Machine_Desc->Wdog,&Machine_Desc->CPU)!=Error_OK)
	{
		while(1);
	}

	//MPU
#ifdef __MPU__
	if(MPU_Init(&Machine_Desc->MPU)!=Error_OK)
	{
		while(1);
	}
#endif

#ifdef Master_OS_Config_BSP_Wdog_Disable
	//关闭看门狗
	if(__Sys_BSP_Wdog_Disable()!=Error_OK)
	{
		while(1);
	}
#endif
	//初始化芯片
	if(BSP_Init_CPU()!=Error_OK)
	{
		while(1);
	}

	//更新时钟树
	if(__Sys_BSP_UpData_Clock_Tree(Null,Null)!=Error_OK)
	{
		while(1);
	}

	//动态内存初始化
	if(__Sys_Memory_Init()!=Error_OK)
	{
		while(1);
	}

	//初始化驱动设备控制
	if(Device_Init()!=Error_OK)
	{
		while(1);
	}


	//初始化内核事件机制
	if(Event_Init()!=Error_OK)
	{
		while(1);
	}


	//初始化IRQ
	if(IRQ_Init(&Machine_Desc->IRQ)!=Error_OK)
	{
		while(1);
	}

	//关闭所有中断
	if(__Sys_IRQ_All_Disable()!=Error_OK)
	{
		while(1);
	}

	//初始化定时器
	if(Timer_Init(&Machine_Desc->Timer)!=Error_OK)
	{
		while(1);
	}

	//初始化任务队列
	if(Queue_Init()!=Error_OK)
	{
		while(1);
	}

	//初始化调度器
	if(Scheduling_Init()!=Error_OK)
	{
		while(1);
	}

#ifdef Master_OS_Config_Shell
	//初始化Shell
	if(Shell_Init(&Machine_Desc->UART)!=Error_OK)
	{
		;
	}
#endif

	//创建一个空闲任务
	if(Scheduling_Create_Task_Idle("Idle",Priority_Task_Idle)<Error_OK)
	{
		while(1);
	}

	//创建任务
	if(Module_Init_Task()!=Error_OK)
	{
		while(1);
	}

	//初始化驱动模块
	if(Module_Init_Sys_Device()!=Error_OK)
	{
		while(1);
	}

	//
	if(Module_Init_Sys_Com()!=Error_OK)
	{
		while(1);
	}

	//打开所有中断
	if(__Sys_IRQ_All_Enable()!=Error_OK)
	{
		while(1);
	}

	//跳转到空闲任务
	Scheduling_Switch_To_Idle();

	//
	while(1)
	{


	}
}
