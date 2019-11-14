/*
 * Task.c
 *
 *  Created on: 2019年9月30日
 *      Author: Master.HE
 */

#include "Module/Module.h"
#include "Timer/Timer.h"
#include "API.h"
#include "Define.h"
#include "Task.h"
#include "Init/Init.Module.h"


uint32_t Stack_Task[Stack_Task_Task_4Byte];


__task void Task_Idle(void *Args)
{

	//打开定时器
	if(Timer_Enable()!=Error_OK)
	{
		while(1);
	}
	
	while(1)
	{

	}

}


__task void Task_Task(void *Args)
{

	if(Module_Init_Com()!=Error_OK)
	{
		while(1);
	}

	if(Module_Init_Application()!=Error_OK)
	{
		while(1);
	}

	__Timer_Task();
}


__Sys_Module_Init_Task("Task.Task",Task_Task,Null,Priority_Task_Task,Stack_Task,Stack_Task_Task_4Byte,Scheduling_Task_Option_User);

