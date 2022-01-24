/*
 * Scheduling.c
 *
 *  Created on: 2019年4月23日
 *      Author: Master.HE
 */
#include <string.h>

#include "Error.h"
#include "Define.h"
#include "Scheduling.Task.h"

#include "__Sys.API.h"

#include "Queue/Queue.h"

#include "Scheduling.Struct.h"

#include "Scheduling.h"

#include "IRQ/IRQ.h"

#include "Task/Task.h"

#include "MPU/MPU.h"

#include "Memory/Memory.h"

Scheduling_DATA_Type Scheduling_DATA;

uint32_t Temp_Stack[0x14];
uint32_t *P_Temp_Stack;

int Scheduling_Init(void)
{
	Scheduling_DATA.Count=0;
	Scheduling_DATA.Count_Task_Idle=0;
	Scheduling_DATA.CPU_Load=0;

	Scheduling_DATA.Last_TCB=Null;
	Scheduling_DATA.Current_TCB=Null;

	for(int i=0;i<20;i++)
	{
		Temp_Stack[i]=0xEFEFEFEF;
	}
	P_Temp_Stack=&Temp_Stack[10];
	return Error_OK;
}

#ifdef Master_OS_Config_Scheduling_Create_Task
int __Sys_Scheduling_Create_Task(
		char *Name,
		Task_Enter_Function Task_Enter,
		void *Args,

		Task_Exit_Function Task_Exit,

		uint8_t Priority,
		uint32_t *Stack,
		uint32_t Stack_Size_4Byte,
		int Option
		)
{
	int Err;

	if(Task_Enter==Null

	|| Task_Exit==Null

	|| Stack_Size_4Byte==0)
	{
		return Error_Invalid_Parameter;
	}

	__Sys_Scheduling_Task_TCB_Type *P_Task_TCB;

	if((Err=Scheduling_Task_Create(
			&P_Task_TCB,
			Name,
			Task_Enter,
			Args,
#ifdef Master_OS_Config_Scheduling_Exit_Task
			Task_Exit,
#endif
			Priority,
			Stack,
			Stack_Size_4Byte,
			Option))!=Error_OK)
	{
		return Err;
	}
	if(P_Task_TCB==Null)
	{
		return Error_Unknown;
	}

	//
	if((Err=Queue_TCB_Add_TCB_Queue(P_Task_TCB))!=Error_OK)
	{
		goto Exit1;
	}

	if((Err=Queue_TCB_Add_Ready_Queue(P_Task_TCB))!=Error_OK)
	{
		goto Exit2;
	}
	if((Err=__Sys_Handle_New())<Valid_Handle)
	{
		goto Exit2;
	}

	P_Task_TCB->Info.Handle=Err;
	P_Task_TCB->Info.Time_Slice=Task_Time_Slice_MS;
	P_Task_TCB->Info.TimeOut=-1;
	P_Task_TCB->Event.Event_Queue=Null;
	P_Task_TCB->Queue.Event_NEXT=Null;

	return P_Task_TCB->Info.Handle;

Exit2:
	Queue_TCB_Delete_TCB_Queue(&P_Task_TCB,0);
Exit1:
	Scheduling_Task_Release(P_Task_TCB);
	return Err;
}
#endif
#ifdef Master_OS_Config_Scheduling_Release_Task
int __Sys_Scheduling_Release_Task(int Handle)
{

	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Parameter;
	}
	else if(Handle==0)
	{
		if(Scheduling_DATA.Current_TCB==Null)
		{
			return Error_Invalid_Parameter;
		}
		//这个地方做特殊处理，因为任务有独立的内核栈，当任务被释放的时候，被释放的内核栈会被占用，故此增加临时内核栈，

#if ((__ARM_ARCH == 6) || (__ARM_ARCH == 7)) && (__ARM_ARCH_PROFILE == 'M')
		asm("MSR  MSP,%0"
					: "+r"(P_Temp_Stack)
						);
#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R')
		asm("mov  SP,%0"
					: "+r"(P_Temp_Stack)
						);

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'A')


#else

#error "123"

#endif

		__Sys_Scheduling_Task_TCB_Type *P_Task_TCB=Null;

		if(Queue_TCB_Delete_TCB_Queue(&P_Task_TCB,Scheduling_DATA.Current_TCB->Info.Handle)!=Error_OK)
		{
			while(1);
		}
		Scheduling_DATA.Last_TCB=Null;
		Scheduling_DATA.Current_TCB=Null;
		if(Queue_Delete_Ready_Queue_First_TCB(&Scheduling_DATA.Current_TCB)!=Error_OK)
		{
			while(1);
		}

		Scheduling_DATA.Current_TCB->Info.Task_State=Task_State_Runing;
		Scheduling_DATA.Current_TCB->Info.Time_Slice=Task_Time_Slice_MS;


		__Sys_Handle_Free(P_Task_TCB->Info.Handle);
		Scheduling_Task_Release(P_Task_TCB);

#ifdef __UsrSP_SysSP__
		__Sys_Switch_To(Null,&Scheduling_DATA.Current_TCB->Stack_System.SP,Null,&Scheduling_DATA.Current_TCB->Stack_User.SP);
#else
		__Sys_Switch_To(Null,&Scheduling_DATA.Current_TCB->Stack.SP);
#endif

		return Error_OK;
	}
	else
	{
		return Error_Undefined;
	}



}
#endif
#ifdef Master_OS_Config_Scheduling_Sleep_Task
int __Sys_Scheduling_Sleep_Task(int32_t TimeOut)
{
	int Err;
	int32_t RTimeOut;

	if(TimeOut<=0)
	{
		return Error_Invalid_Parameter;
	}

	if((Err=__Sys_Scheduling_Context_Switch(Task_State_Suspended,TimeOut,&RTimeOut))!=Error_OK)
	{
		return Err;
	}
	if(RTimeOut==0)
	{
		return Error_OK;
	}
	else
	{
		return Error_Unknown;
	}
}
#endif
#ifdef Master_OS_Config_Scheduling_Suspend_Task
int __Sys_Scheduling_Suspend_Task(int Handle)
{
	return Error_Undefined;
}
#endif
#ifdef Master_OS_Config_Scheduling_Resume_Task
int __Sys_Scheduling_Resume_Task(int Handle)
{
	return Error_Undefined;
}
#endif
//--------------------------------------------------------------
int Scheduling_Create_Task_Idle(
		char *Name,
		uint8_t Priority)
{
	int Err;

	__Sys_Scheduling_Task_TCB_Type *P_Task_TCB;

	if((Err=Scheduling_Task_Create_Idle(&P_Task_TCB,Name,Priority))!=Error_OK)
	{
		return Err;
	}
	if(P_Task_TCB==Null)
	{
		return Error_Unknown;
	}

	//
	if((Err=Queue_TCB_Add_TCB_Queue(P_Task_TCB))!=Error_OK)
	{
		goto Exit1;
	}


	Scheduling_DATA.Current_TCB=P_Task_TCB;
	P_Task_TCB->Info.Task_State=Task_State_Runing;
	P_Task_TCB->Info.Time_Slice=Task_Time_Slice_MS;
	P_Task_TCB->Info.TimeOut=-1;

#ifdef __UsrSP_SysSP__
	extern uint32_t Stack_System_Default_Size_4Byte;

	uint32_t Stack_System_Size_4Byte=((uint32_t)&Stack_System_Default_Size_4Byte)+8;
	uint32_t Sys_Stack_Alignment_Byte=Stack_Alignment_Byte;
#ifdef __MPU__
	P_Task_TCB->Stack_System.Protection_Size=Stack_Default_Protection_Size;

	Sys_Stack_Alignment_Byte=Stack_Default_Protection_Size_Byte(Stack_Default_Protection_Size);
#endif
	Stack_System_Size_4Byte=Stack_System_Size_4Byte+Sys_Stack_Alignment_Byte/4;


	P_Task_TCB->Stack_System.SP_Head=__Sys_Memory_Malloc_Align(Stack_System_Size_4Byte*4,Sys_Stack_Alignment_Byte);

	if(P_Task_TCB->Stack_System.SP_Head==Null)
	{
		Err=Error_Allocation_Memory_Failed;
		goto Exit1;
	}

	if(((uint32_t)P_Task_TCB->Stack_System.SP_Head&(Sys_Stack_Alignment_Byte-1))!=0)
	{
		Err=Error_Allocation_Memory_Failed;
		goto Exit2;
	}

	P_Task_TCB->Stack_System.SP_End=&P_Task_TCB->Stack_System.SP_Head[(Stack_System_Size_4Byte)-1];

	memset(P_Task_TCB->Stack_System.SP_Head,0xEF,Stack_System_Size_4Byte*4);

	P_Task_TCB->Stack_System.SP=P_Task_TCB->Stack_System.SP_End;

#ifdef __MPU__
	P_Task_TCB->Stack_System.Count=0;
#endif

#pragma section="CSTACK"
	P_Task_TCB->Stack_User.SP_Head=__section_begin("CSTACK");
	P_Task_TCB->Stack_User.SP_End=__section_end("CSTACK");

#ifdef __MPU__
	P_Task_TCB->Stack_User.Protection_Size=Stack_Default_Protection_Size;
	P_Task_TCB->Stack_User.Count=0;
#endif


#else

#pragma section="CSTACK"
	P_Task_TCB->Stack.SP_Head=__section_begin("CSTACK");
	P_Task_TCB->Stack.SP_End=__section_end("CSTACK");

#endif


	P_Task_TCB->Info.Handle=Valid_Handle;//0保留给 空闲进程

	return P_Task_TCB->Info.Handle;

#ifdef __UsrSP_SysSP__
Exit2:
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(P_Task_TCB->Stack_System.SP_Head);
#endif
#endif

Exit1:
	Scheduling_Task_Release_Idle(P_Task_TCB);
	return Err;
}

void Scheduling_Switch_To_Idle(void)
{
#ifdef __UsrSP_SysSP__
	__Sys_Switch_To_Idle(Scheduling_DATA.Current_TCB->Stack_User.SP_End,Scheduling_DATA.Current_TCB->Stack_User.SP_Head,Task_Idle,Scheduling_DATA.Current_TCB->Stack_System.SP_End);
#else
	__Sys_Switch_To_Idle(Scheduling_DATA.Current_TCB->Stack.SP_End,Scheduling_DATA.Current_TCB->Stack.SP_Head,Task_Idle);
#endif
}

void Scheduling_SysTick(void)
{
	Scheduling_DATA.Count++;


	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;

	//当前任务时间片减一
	if(Scheduling_DATA.Current_TCB!=Null)
	{
		if(Scheduling_DATA.Current_TCB->Info.Time_Slice>0)
		{
			Scheduling_DATA.Current_TCB->Info.Time_Slice--;
		}

		//当前任务时间片已经用完
		if(Scheduling_DATA.Current_TCB->Info.Time_Slice==0)
		{
			;
		}
		if(Scheduling_DATA.Current_TCB->Info.Handle==0)
		{
			Scheduling_DATA.Count_Task_Idle++;
		}
	}
	if(Scheduling_DATA.Count>=1000)
	{
		Scheduling_DATA.Count=0;
		Scheduling_DATA.CPU_Load=1000-Scheduling_DATA.Count_Task_Idle;
		Scheduling_DATA.Count_Task_Idle=0;
	}


	bool Sub=true;

Find_Next_Suspended_Ready_TCB:
	//检查Suspended队列是否有需要准备运行的任务
	if(Queue_TimeOut_1MS_AT_Suspended_Queue(&Temp_TCB,Sub)==Error_OK)
	{
		Sub=false;

		//当前任务在事件队列中
		if(Temp_TCB->Event.Event_Queue!=Null)
		{
			//删除 事件等待队列 中的任务
			if(Queue_TCB_Delete_Event_Node_Queue(Temp_TCB->Event.Event_Queue,Temp_TCB)!=Error_OK)
			{
				while(1);
			}
		}

		//将准备运行的任务放到 准备运行队列
		if(Queue_TCB_Add_Ready_Queue(Temp_TCB)!=Error_OK)
		{
			while(1);
		}
		Temp_TCB=Null;
		goto Find_Next_Suspended_Ready_TCB;
	}

	Temp_TCB=Null;


	//找出准备运行队列中 优先级最高的任务
	if(Queue_Read_Ready_Queue_First_TCB(&Temp_TCB)!=Error_OK)
	{
		//当前准备队列中 没有准备运行的任务
		if(Scheduling_DATA.Current_TCB!=Null)
		{
			if(Scheduling_DATA.Current_TCB->Info.Time_Slice==0)
			{
				Scheduling_DATA.Current_TCB->Info.Time_Slice=Task_Time_Slice_MS;
			}
		}
		return ;
	}

	//
	if(Temp_TCB==Null || Scheduling_DATA.Current_TCB==Null)
	{
		while(1);
	}

	//当前任务比准备运行队列中任务优先级大
	if(Scheduling_DATA.Current_TCB->Priority.Current<Temp_TCB->Priority.Current)
	{
		if(Scheduling_DATA.Current_TCB->Info.Time_Slice==0)
		{
			Scheduling_DATA.Current_TCB->Info.Time_Slice=Task_Time_Slice_MS;
		}
		return ;
	}
	//当前任务和准备运行任务优先级一致
	else if(Scheduling_DATA.Current_TCB->Priority.Current==Temp_TCB->Priority.Current)
	{
		if(Scheduling_DATA.Current_TCB->Info.Time_Slice!=0)
		{
			return ;
		}
	}
	//当前任务优先级比准备运行优先级小
	else
	{

	}
	//从准备运行队列中提取准备运行的任务
	if(Queue_Delete_Ready_Queue_First_TCB(&Temp_TCB)!=Error_OK)
	{
		while(1);
	}

	//将当前任务放到准备运行队列中
	if(Queue_TCB_Add_Ready_Queue(Scheduling_DATA.Current_TCB)!=Error_OK)
	{
		while(1);
	}

	//
	Temp_TCB->Info.Task_State=Task_State_Runing;
	Temp_TCB->Info.Time_Slice=Task_Time_Slice_MS;

	Scheduling_DATA.Last_TCB=Scheduling_DATA.Current_TCB;
	Scheduling_DATA.Current_TCB=Temp_TCB;

	//任务进行上下文切换
#ifdef __UsrSP_SysSP__
	__Sys_Switch_To(&Scheduling_DATA.Last_TCB->Stack_System.SP,&Scheduling_DATA.Current_TCB->Stack_System.SP,&Scheduling_DATA.Last_TCB->Stack_User.SP,&Scheduling_DATA.Current_TCB->Stack_User.SP);
#else
	__Sys_Switch_To(&Scheduling_DATA.Last_TCB->Stack.SP,&Scheduling_DATA.Current_TCB->Stack.SP);
#endif
}



void __Sys_Scheduling_Try_Context_Switch(void)
{
	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;

	//找出准备运行队列中 优先级最高的任务
	if(Queue_Read_Ready_Queue_First_TCB(&Temp_TCB)!=Error_OK)
	{
		return ;
	}

	if(Temp_TCB==Null || Scheduling_DATA.Current_TCB==Null)
	{
		while(1);
	}

	if(Scheduling_DATA.Current_TCB->Priority.Current<=Temp_TCB->Priority.Current)
	{
		return ;
	}


	if(Queue_Delete_Ready_Queue_First_TCB(&Temp_TCB)!=Error_OK)
	{
		while(1);
	}

	if(Queue_TCB_Add_Ready_Queue(Scheduling_DATA.Current_TCB)!=Error_OK)
	{
		while(1);
	}

	Temp_TCB->Info.Task_State=Task_State_Runing;
	Temp_TCB->Info.Time_Slice=Task_Time_Slice_MS;

	Scheduling_DATA.Last_TCB=Scheduling_DATA.Current_TCB;
	Scheduling_DATA.Current_TCB=Temp_TCB;

#ifdef __UsrSP_SysSP__
	__Sys_Switch_To(&Scheduling_DATA.Last_TCB->Stack_System.SP,&Scheduling_DATA.Current_TCB->Stack_System.SP,&Scheduling_DATA.Last_TCB->Stack_User.SP,&Scheduling_DATA.Current_TCB->Stack_User.SP);
#else
	__Sys_Switch_To(&Scheduling_DATA.Last_TCB->Stack.SP,&Scheduling_DATA.Current_TCB->Stack.SP);
#endif
}

int __Sys_Scheduling_Context_Switch(Task_State_Type CS_Task_State,int32_t TimeOut,int32_t *RTimeOut)
{
	if(TimeOut<(-1))
	{
		return Error_Invalid_Parameter;
	}

	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;
	int Err;
	if((Err=Queue_Delete_Ready_Queue_First_TCB(&Temp_TCB))!=Error_OK)
	{
		return Err;

	}

	if((Err=Queue_TCB_Add_Suspended_Queue(Scheduling_DATA.Current_TCB,CS_Task_State,TimeOut))!=Error_OK)
	{
		Queue_TCB_Add_Ready_Queue(Temp_TCB);
		return Err;
	}

	Temp_TCB->Info.Task_State=Task_State_Runing;
	Temp_TCB->Info.Time_Slice=Task_Time_Slice_MS;

	Scheduling_DATA.Last_TCB=Scheduling_DATA.Current_TCB;
	Scheduling_DATA.Current_TCB=Temp_TCB;

#ifdef __UsrSP_SysSP__
	__Sys_Switch_To(&Scheduling_DATA.Last_TCB->Stack_System.SP,&Scheduling_DATA.Current_TCB->Stack_System.SP,&Scheduling_DATA.Last_TCB->Stack_User.SP,&Scheduling_DATA.Current_TCB->Stack_User.SP);
#else
	__Sys_Switch_To(&Scheduling_DATA.Last_TCB->Stack.SP,&Scheduling_DATA.Current_TCB->Stack.SP);
#endif

	if(RTimeOut!=Null)
	{
		*RTimeOut=Scheduling_DATA.Current_TCB->Info.TimeOut;
	}
	return Error_OK;
}
int __Sys_Scheduling_GET_Current_TCB(__Sys_Scheduling_Task_TCB_Type **Current_TCB)
{
	if(Current_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(Scheduling_DATA.Current_TCB==Null)
	{
		return Error_Unknown;
	}
	*Current_TCB=Scheduling_DATA.Current_TCB;

	return Error_OK;
}
#ifdef __UsrSP_SysSP__

uint32_t **__Sys_Scheduling_GET_System_SP_End(void)
{
	return &Scheduling_DATA.Current_TCB->Stack_System.SP_End;
}
uint32_t **__Sys_Scheduling_GET_User_SP(void)
{
	return &Scheduling_DATA.Current_TCB->Stack_User.SP;
}
#endif
#ifdef __MPU__
void __Sys_Scheduling_MPU_SET_Current_Task(void)
{
	if(MPU_SET(
			(uint32_t)Scheduling_DATA.Current_TCB->Stack_System.SP_Head,
			Scheduling_DATA.Current_TCB->Stack_System.Protection_Size,
			(uint32_t)Scheduling_DATA.Current_TCB->Stack_User.SP_Head,
			Scheduling_DATA.Current_TCB->Stack_User.Protection_Size)!=Error_OK)
	{
		while(1);
	}
}
void __Sys_Scheduling_MPU_SET_LAST_Task(void)
{
	if(MPU_SET(
			(uint32_t)Scheduling_DATA.Last_TCB->Stack_System.SP_Head,
			Scheduling_DATA.Last_TCB->Stack_System.Protection_Size,
			(uint32_t)Scheduling_DATA.Last_TCB->Stack_User.SP_Head,
			Scheduling_DATA.Last_TCB->Stack_User.Protection_Size)!=Error_OK)
	{
		while(1);
	}
}
int __Sys_Scheduling_MPU_Add_Stack(uint32_t Mode,uint32_t *Fault_SP,uint32_t Fault_Address)
{
	if(Fault_SP==Null)
	{
		return Error_Invalid_Parameter;
	}

	//


	//这个地方检查两个任务的栈，因为可能发生在任务上下文切换阶段或者任意阶段，所有都不能有遗漏
	if(Scheduling_DATA.Current_TCB!=Null)
	{
		//先检查当前任务的栈
		//出错地址在当前任务的用户栈中
		if((uint32_t)Scheduling_DATA.Current_TCB->Stack_User.SP_Head<=Fault_Address
		&& Fault_Address<=(uint32_t)Scheduling_DATA.Current_TCB->Stack_User.SP_End)
		{
			//在检查一次当前SP指针是否在当前任务栈中
			if((uint32_t)Scheduling_DATA.Current_TCB->Stack_User.SP_Head<=(uint32_t)Fault_SP
			&& (uint32_t)Fault_SP<=(uint32_t)Scheduling_DATA.Current_TCB->Stack_User.SP_End)
			{
				//初步确认出错位置

				//在检查一次是否出错位置在保护区域
				if((Fault_Address-(uint32_t)Scheduling_DATA.Current_TCB->Stack_User.SP_Head)<=Stack_Default_Protection_Size_Byte(Scheduling_DATA.Current_TCB->Stack_User.Protection_Size))
				{
					int Err;
					bool Sys_Memory;
					if((Scheduling_DATA.Current_TCB->Info.Option&Scheduling_Task_Option_System)!=0)
					{
						Sys_Memory=true;
					}
					else
					{
						Sys_Memory=false;
					}
					if((Err=__Sys_Scheduling_MPU_Add_Stack_Malloc(Sys_Memory,&Scheduling_DATA.Current_TCB->Stack_User,Mode,Fault_SP,Fault_Address))!=Error_OK)
					{
						return Err;
					}
					__Sys_Scheduling_MPU_SET_Current_Task();
					return Error_OK;

				}

			}

		}
		//出错任务在当前任务的内核栈中
		if((uint32_t)Scheduling_DATA.Current_TCB->Stack_System.SP_Head<=Fault_Address
		&& Fault_Address<=(uint32_t)Scheduling_DATA.Current_TCB->Stack_System.SP_End)
		{
			//在检查一次当前SP指针是否在当前任务栈中
			if((uint32_t)Scheduling_DATA.Current_TCB->Stack_System.SP_Head<=(uint32_t)Fault_SP
			&& (uint32_t)Fault_SP<=(uint32_t)Scheduling_DATA.Current_TCB->Stack_System.SP_End)
			{
				//初步确认出错位置

				//在检查一次是否出错位置在保护区域
				if((Fault_Address-(uint32_t)Scheduling_DATA.Current_TCB->Stack_System.SP_Head)<=Stack_Default_Protection_Size_Byte(Scheduling_DATA.Current_TCB->Stack_System.Protection_Size))
				{
					//
					int Err;

					if((Err=__Sys_Scheduling_MPU_Add_Stack_Malloc(true,&Scheduling_DATA.Current_TCB->Stack_System,Mode,Fault_SP,Fault_Address))!=Error_OK)
					{
						return Err;
					}
					__Sys_Scheduling_MPU_SET_Current_Task();
					return Error_OK;
				}

			}

		}
	}
	//出错任务在上一个任务的用户栈中
	if(Scheduling_DATA.Last_TCB!=Null)
	{
		//出错地址在上一个任务的用户栈中
		if((uint32_t)Scheduling_DATA.Last_TCB->Stack_User.SP_Head<=Fault_Address
		&& Fault_Address<=(uint32_t)Scheduling_DATA.Last_TCB->Stack_User.SP_End)
		{
			//在检查一次当前SP指针是否在上一个任务栈中
			if((uint32_t)Scheduling_DATA.Last_TCB->Stack_User.SP_Head<=(uint32_t)Fault_SP
			&& (uint32_t)Fault_SP<=(uint32_t)Scheduling_DATA.Last_TCB->Stack_User.SP_End)
			{
				//初步确认出错位置

				//在检查一次是否出错位置在保护区域
				if((Fault_Address-(uint32_t)Scheduling_DATA.Last_TCB->Stack_User.SP_Head)<=Stack_Default_Protection_Size_Byte(Scheduling_DATA.Last_TCB->Stack_User.Protection_Size))
				{
					//
					int Err;
					bool Sys_Memory;
					if((Scheduling_DATA.Last_TCB->Info.Option&Scheduling_Task_Option_System)!=0)
					{
						Sys_Memory=true;
					}
					else
					{
						Sys_Memory=false;
					}
					if((Err=__Sys_Scheduling_MPU_Add_Stack_Malloc(Sys_Memory,&Scheduling_DATA.Last_TCB->Stack_User,Mode,Fault_SP,Fault_Address))!=Error_OK)
					{
						return Err;
					}
					__Sys_Scheduling_MPU_SET_LAST_Task();
					return Error_OK;
				}

			}

		}
		//出错任务在上一个任务的内核栈中
		if((uint32_t)Scheduling_DATA.Last_TCB->Stack_System.SP_Head<=Fault_Address
		&& Fault_Address<=(uint32_t)Scheduling_DATA.Last_TCB->Stack_System.SP_End)
		{
			//在检查一次当前SP指针是否在上一个任务栈中
			if((uint32_t)Scheduling_DATA.Last_TCB->Stack_System.SP_Head<=(uint32_t)Fault_SP
			&& (uint32_t)Fault_SP<=(uint32_t)Scheduling_DATA.Last_TCB->Stack_System.SP_End)
			{
				//初步确认出错位置

				//在检查一次是否出错位置在保护区域
				if((Fault_Address-(uint32_t)Scheduling_DATA.Last_TCB->Stack_System.SP_Head)<=Stack_Default_Protection_Size_Byte(Scheduling_DATA.Last_TCB->Stack_System.Protection_Size))
				{
					//
					int Err;
					if((Err=__Sys_Scheduling_MPU_Add_Stack_Malloc(true,&Scheduling_DATA.Last_TCB->Stack_System,Mode,Fault_SP,Fault_Address))!=Error_OK)
					{
						return Err;
					}
					__Sys_Scheduling_MPU_SET_LAST_Task();
					return Error_OK;
				}

			}

		}
	}



	return Error_Unknown;
}

int __Sys_Scheduling_MPU_Add_Stack_Malloc(bool Sys_Memory,Scheduling_Task_TCB_Stack_Type *P_TCB_Stack,uint32_t Mode,uint32_t *Fault_SP,uint32_t Fault_Address)
{
	if(P_TCB_Stack==Null || Fault_SP==Null || Sys_Memory>=bool_End)
	{
		return Error_Invalid_Parameter;
	}

	uint32_t New_Stack_Size_4Byte=((uint32_t)P_TCB_Stack->SP_End-(uint32_t)P_TCB_Stack->SP_Head)/4;

	//这个地方还要特别注意一个关键问题，就是溢出的长度需要计算出来，然后新的区域还必须要超过这个区域



	uint32_t Protection_Size_Byte=Stack_Default_Protection_Size_Byte(P_TCB_Stack->Protection_Size);

	uint32_t Unused=0;
	if((uint32_t)Fault_SP<Fault_Address)
	{
		Unused=(uint32_t)Fault_SP-(uint32_t)P_TCB_Stack->SP_Head;
	}
	else
	{
		Unused=Fault_Address-(uint32_t)P_TCB_Stack->SP_Head;
	}

	uint32_t Used=Protection_Size_Byte-Unused;

	New_Stack_Size_4Byte=New_Stack_Size_4Byte+Stack_Add_Size_4Byte+Used/4;


	uint32_t *New_Stack=Null;

	//申请一个新的栈空间
	if(Sys_Memory==true)
	{
		New_Stack=__Sys_Memory_Malloc_Align(New_Stack_Size_4Byte*4,Protection_Size_Byte);

		if(New_Stack==Null)
		{
			return Error_Allocation_Memory_Failed;
		}
		if(((uint32_t)New_Stack&(Protection_Size_Byte-1))!=0)
		{
			__Sys_Memory_Free(New_Stack);
			return Error_Allocation_Memory_Failed;
		}
	}
	else
	{
		New_Stack=__Usr_Memory_Malloc_Align(New_Stack_Size_4Byte*4,Protection_Size_Byte);

		if(New_Stack==Null)
		{
			return Error_Allocation_Memory_Failed;
		}
		if(((uint32_t)New_Stack&(Protection_Size_Byte-1))!=0)
		{
			__Usr_Memory_Free(New_Stack);
			return Error_Allocation_Memory_Failed;
		}

	}

	memset(New_Stack,0xEF,New_Stack_Size_4Byte*4);

	uint32_t *New_Stack_End=&New_Stack[New_Stack_Size_4Byte-1];

	uint32_t *New_Stack_SP=New_Stack_End;

	uint32_t *Old_Stack_SP=P_TCB_Stack->SP_End;

	//先关闭保护区域，等复制完成后，重新设置新的保护地址
	if(MPU_SET_Region_Disable()!=Error_OK)
	{
		while(1);
	}
	//
	while(1)
	{
		(*New_Stack_SP)=(*Old_Stack_SP);

		if(Old_Stack_SP==Fault_SP)
		{
			break;
		}

		New_Stack_SP--;
		Old_Stack_SP--;

	}
	//释放掉溢出的栈空间
	if(Sys_Memory==true)
	{
		__Sys_Memory_Free(P_TCB_Stack->SP_Head);
	}
	else
	{
		__Usr_Memory_Free(P_TCB_Stack->SP_Head);
	}
	
	P_TCB_Stack->SP_Head=New_Stack;
	P_TCB_Stack->SP_End=New_Stack_End;
	P_TCB_Stack->SP=New_Stack_SP;

	if(P_TCB_Stack->Count<0xFFFFFFFF)
	{
		P_TCB_Stack->Count++;
	}

	//设置CPU溢出的SP指针
	__Sys_SET_CPU_SP(Mode,P_TCB_Stack->SP);

	//while(1);

	return Error_OK;
}

#endif
