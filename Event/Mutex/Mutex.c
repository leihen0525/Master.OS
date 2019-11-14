/*
 * Mutex.c
 *
 *  Created on: 2019年4月30日
 *      Author: Master.HE
 */
#include "Master.Stdint.h"
#include "Define.h"
#include "Error.h"

#include "Event.Enum.h"
#include "Event/__Event.Enum.h"
#include "Event/Event.h"

#include "Mutex.Struct.h"
#include "Mutex.h"

#include "__Sys.API.h"

#include "Queue/Queue.h"

#include "Scheduling/Scheduling.h"

int __Sys_Mutex_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type)
{
	int Handle;
	if(Option_Type>=Event_Queue_Option_End)
	{
		return Error_Invalid_Parameter;
	}

	Event_DATA_Node_Type *Temp_DATA_Node=(Event_DATA_Node_Type *)__Sys_Memory_Malloc(sizeof(Event_Mutex_Node_Type));

	if(Temp_DATA_Node==Null)
	{

		return Error_Allocation_Memory_Failed;
	}

	Temp_DATA_Node->Mutex.Option=Option_Type;

	Temp_DATA_Node->Mutex.Possess_TCB=Null;



	if((Handle=Event_Node_Add_Node(Name,Event_Pend_Mutex,Temp_DATA_Node))<Valid_Handle)
	{

		__Sys_Memory_Free(Temp_DATA_Node);
		return Handle;
	}
	return Handle;

}

int __Sys_Mutex_Delete(int Handle)
{
	if(Handle<Valid_Handle)return Error_Invalid_Handle;

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;

	if((Err=Event_Node_Delete_Node(Handle,Event_Pend_Mutex,&Temp_DATA_Node))!=Error_OK)
	{
		return Err;
	}

	if(Temp_DATA_Node!=Null)
	{
		__Sys_Memory_Free(Temp_DATA_Node);
	}
	return Error_OK;

}

int __Sys_Mutex_Find_Handle(char *Name)
{
	if(Name==Null)
	{
		return Error_Invalid_Parameter;
	}

	return Event_Node_Name_Find_Node(Name,Event_Pend_Mutex);
}

int __Sys_Mutex_Wait(
		int Handle,
		int32_t Time_Out_MS)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Time_Out_MS<Event_Time_Out_Query)
	{
		return Error_Invalid_Parameter;
	}
	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Mutex,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}
	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;

	if((Err=__Sys_Scheduling_GET_Current_TCB(&Temp_TCB))!=Error_OK)
	{
		return Err;
	}

	if(Time_Out_MS==Event_Time_Out_Query)
	{

		if(Temp_DATA_Node->Mutex.Possess_TCB==Null			//当前未被占用
		|| Temp_DATA_Node->Mutex.Possess_TCB==Temp_TCB)	//当前占用的是自己
		{
			return Error_OK;
		}
		else
		{
			return Error_Dissatisfy;
		}
	}
	else if(Time_Out_MS==Event_Time_Out_Occupy_Return_Back)
	{
		if(Temp_DATA_Node->Mutex.Possess_TCB==Null			//当前未被占用
		|| Temp_DATA_Node->Mutex.Possess_TCB==Temp_TCB)	//当前占用的是自己
		{

			Temp_DATA_Node->Mutex.Possess_TCB=Temp_TCB;

			//调整优先级
			Temp_TCB->Priority.Current=Priority_Task_Mutex;

			return Error_OK;
		}
		else
		{
			return Error_Dissatisfy;
		}
	}
	else
	{
		if(Temp_DATA_Node->Mutex.Possess_TCB==Null			//当前未被占用
		|| Temp_DATA_Node->Mutex.Possess_TCB==Temp_TCB)	//当前占用的是自己
		{

			Temp_DATA_Node->Mutex.Possess_TCB=Temp_TCB;

			//调整优先级
			Temp_TCB->Priority.Current=Priority_Task_Mutex;

			return Error_OK;
		}
		else
		{

			//被占用 挂起当前任务
			if((Err=Queue_TCB_Add_Event_Node_Queue(Temp_Pend_Task_Queue,Temp_TCB,Temp_DATA_Node->Mutex.Option))!=Error_OK)
			{
				return Err;
			}

			int32_t RTimeOut=0;
			if((Err=__Sys_Scheduling_Context_Switch(Task_State_Pend_Mutex,Time_Out_MS,&RTimeOut))!=Error_OK)
			{
				return Err;
			}

			if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Mutex,Null,Null)!=Error_OK))
			{
				return Err;
			}

			if(RTimeOut==0)
			{
				return Error_Time_Out;
			}
			if(Temp_DATA_Node->Mutex.Possess_TCB!=Temp_TCB)
			{
				return Error_Unknown;
			}
			return Error_OK;
		}
	}



}


int __Sys_Mutex_Release(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Mutex,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}

	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;

	if((Err=__Sys_Scheduling_GET_Current_TCB(&Temp_TCB))!=Error_OK)
	{
		return Err;
	}
	if(Temp_DATA_Node->Mutex.Possess_TCB!=Temp_TCB)
	{
		return Error_Illegal;
	}
	Temp_DATA_Node->Mutex.Possess_TCB=Null;


	//恢复当前优先级
	Temp_TCB->Priority.Current=Temp_TCB->Priority.Default;

	Temp_TCB=Null;

	bool Try_Context_Switch=false;

	if(Queue_TCB_Delete_Event_Node_Queue_First_TCB(Temp_Pend_Task_Queue,&Temp_TCB)==Error_OK)
	{
		Temp_DATA_Node->Mutex.Possess_TCB=Temp_TCB;
		Temp_TCB->Priority.Current=Priority_Task_Mutex;

		Queue_TCB_Delete_Suspended_Queue(Temp_TCB);
		Queue_TCB_Add_Ready_Queue(Temp_TCB);
		Temp_TCB=Null;


		Try_Context_Switch=true;
	}

	if(Try_Context_Switch==true)
	{
		__Sys_Scheduling_Try_Context_Switch();
	}

	return Error_OK;
}



