/*
 * Scheduling.c
 *
 *  Created on: 2019年4月23日
 *      Author: Master.HE
 */
#include "Error.h"
#include "Define.h"
#include "Scheduling.Task.h"

#include "__Sys.API.h"

#include "Queue/Queue.h"

#include "Scheduling.Struct.h"

#include "Scheduling.h"

#include "IRQ/IRQ.h"

Scheduling_DATA_Type Scheduling_DATA;

uint32_t Temp_Stack[0x14];
uint32_t *P_Temp_Stack;

int Scheduling_Init(void)
{
	Scheduling_DATA.Current_TCB=Null;

	for(int i=0;i<20;i++)
	{
		Temp_Stack[i]=0xEFEFEFEF;
	}
	P_Temp_Stack=&Temp_Stack[10];
	return Error_OK;
}


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

	if((Err=Scheduling_Task_Create(&P_Task_TCB,Name,Task_Enter,Args,Task_Exit,Priority,Stack,Stack_Size_4Byte,Option))!=Error_OK)
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
	if((Err=__Sys_Apply_Handle())<Valid_Handle)
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
		Scheduling_DATA.Current_TCB=Null;
		if(Queue_Delete_Ready_Queue_First_TCB(&Scheduling_DATA.Current_TCB)!=Error_OK)
		{
			while(1);
		}

		Scheduling_DATA.Current_TCB->Info.Task_State=Task_State_Runing;
		Scheduling_DATA.Current_TCB->Info.Time_Slice=Task_Time_Slice_MS;


		Scheduling_Task_Release(P_Task_TCB);

		__Sys_Switch_To(Null,&Scheduling_DATA.Current_TCB->Stack.SP);


		return Error_OK;
	}
	else
	{
		return Error_Undefined;
	}



}

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
int __Sys_Scheduling_Suspend_Task(int Handle)
{
	return Error_Undefined;
}
int __Sys_Scheduling_Resume_Task(int Handle)
{
	return Error_Undefined;
}

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

#pragma section="CSTACK"
	P_Task_TCB->Stack.SP_Head=__section_begin("CSTACK");
	P_Task_TCB->Stack.SP_End=__section_end("CSTACK");

	P_Task_TCB->Info.Handle=Valid_Handle;//0保留给 空闲进程

	return P_Task_TCB->Info.Handle;


Exit1:
	Scheduling_Task_Release_Idle(P_Task_TCB);
	return Err;
}

void Scheduling_SysTick(void)
{
	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null,*Temp_TCB1=Null;

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
	}


	//检查Suspended队列是否有需要准备运行的任务
	if(Queue_TimeOut_1MS_AT_Suspended_Queue(&Temp_TCB)==Error_OK)
	{
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

	Temp_TCB1=Scheduling_DATA.Current_TCB;
	Scheduling_DATA.Current_TCB=Temp_TCB;

	//任务进行上下文切换
	__Sys_Switch_To(&Temp_TCB1->Stack.SP,&Scheduling_DATA.Current_TCB->Stack.SP);

}



void __Sys_Scheduling_Try_Context_Switch(void)
{
	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null,*Temp_TCB1=Null;

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

	Temp_TCB1=Scheduling_DATA.Current_TCB;
	Scheduling_DATA.Current_TCB=Temp_TCB;


	__Sys_Switch_To(&Temp_TCB1->Stack.SP,&Scheduling_DATA.Current_TCB->Stack.SP);

}

int __Sys_Scheduling_Context_Switch(Task_State_Type CS_Task_State,int32_t TimeOut,int32_t *RTimeOut)
{
	if(TimeOut<(-1))
	{
		return Error_Invalid_Parameter;
	}

	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null,*Temp_TCB1=Null;
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

	Temp_TCB1=Scheduling_DATA.Current_TCB;
	Scheduling_DATA.Current_TCB=Temp_TCB;

	__Sys_Switch_To(&Temp_TCB1->Stack.SP,&Scheduling_DATA.Current_TCB->Stack.SP);


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
