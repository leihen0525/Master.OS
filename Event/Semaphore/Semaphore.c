/*
 * Semaphore.c
 *
 *  Created on: 2019年4月29日
 *      Author: Master.HE
 */
#include "Master.Stdint.h"
#include "Define.h"
#include "Error.h"

#include "Event.Enum.h"
#include "Event/__Event.Enum.h"
#include "Event/Event.h"

#include "Semaphore.Struct.h"
#include "Semaphore.h"

#include "__Sys.API.h"

#include "Queue/Queue.h"
#include "Scheduling/Scheduling.h"

#ifdef Master_OS_Config_Semaphore_Create
int __Sys_Semaphore_Create(
		char *Name,
		uint32_t Init_Count,
		uint32_t MAX_Count,
		Event_Queue_Option_Type Option_Type)
{
	int Handle;
	if(Option_Type>=Event_Queue_Option_End
	|| MAX_Count==0
	|| MAX_Count<Init_Count)
	{
		return Error_Invalid_Parameter;
	}

	Event_DATA_Node_Type *Temp_DATA_Node=(Event_DATA_Node_Type *)__Sys_Memory_Malloc(sizeof(Event_Semaphore_Node_Type));

	if(Temp_DATA_Node==Null)
	{

		return Error_Allocation_Memory_Failed;
	}

	Temp_DATA_Node->Semaphore.Option=Option_Type;

	Temp_DATA_Node->Semaphore.Count=Init_Count;
	Temp_DATA_Node->Semaphore.MAX_Count=MAX_Count;


	if((Handle=Event_Node_Add_Node(Name,Event_Pend_Semaphore,Temp_DATA_Node))<Valid_Handle)
	{
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(Temp_DATA_Node);
#endif
		return Handle;
	}
	return Handle;
}
#endif
#ifdef Master_OS_Config_Semaphore_Delete
int __Sys_Semaphore_Delete(int Handle)
{
	if(Handle<Valid_Handle)return Error_Invalid_Handle;

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;

	if((Err=Event_Node_Delete_Node(Handle,Event_Pend_Semaphore,&Temp_DATA_Node))!=Error_OK)
	{
		return Err;
	}

	if(Temp_DATA_Node!=Null)
	{
		__Sys_Memory_Free(Temp_DATA_Node);
	}
	return Error_OK;

}
#endif
#ifdef Master_OS_Config_Semaphore_Find_Handle
int __Sys_Semaphore_Find_Handle(char *Name)
{
	if(Name==Null)
	{
		return Error_Invalid_Parameter;
	}

	return Event_Node_Name_Find_Node(Name,Event_Pend_Semaphore);
}
#endif
#ifdef Master_OS_Config_Semaphore_Wait
int __Sys_Semaphore_Wait(
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
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Semaphore,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}

	if(Time_Out_MS==Event_Time_Out_Query)
	{
		if(Temp_DATA_Node->Semaphore.Count==0)
		{
			return Error_Dissatisfy;
		}
		else
		{
			return Error_OK;
		}
	}
	else if(Time_Out_MS==Event_Time_Out_Occupy_Return_Back)
	{
		if(Temp_DATA_Node->Semaphore.Count==0)
		{
			return Error_Dissatisfy;
		}
		else
		{
			Temp_DATA_Node->Semaphore.Count--;

			return Error_OK;
		}
	}
	else
	{
		if(Temp_DATA_Node->Semaphore.Count==0)
		{

			//被占用 挂起当前任务

			__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;
			if((Err=__Sys_Scheduling_GET_Current_TCB(&Temp_TCB))!=Error_OK)
			{
				return Err;
			}

			if((Err=Queue_TCB_Add_Event_Node_Queue(Temp_Pend_Task_Queue,Temp_TCB,Temp_DATA_Node->Semaphore.Option))!=Error_OK)
			{
				return Err;
			}

			int32_t RTimeOut=0;
			if((Err=__Sys_Scheduling_Context_Switch(Task_State_Pend_Semaphore,Time_Out_MS,&RTimeOut))!=Error_OK)
			{
				return Err;
			}

			if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Semaphore,Null,Null)!=Error_OK))
			{
				return Err;
			}
//			if(Temp_DATA_Node->Semaphore.Count>0)
//			{
//				Temp_DATA_Node->Semaphore.Count--;
//				return Error_OK;
//			}
			if(RTimeOut==0)
			{

				return Error_Time_Out;
			}

			return Error_OK;

		}
		else
		{
			Temp_DATA_Node->Semaphore.Count--;

			return Error_OK;
		}
	}

}
#endif
#ifdef Master_OS_Config_Semaphore_Release
int __Sys_Semaphore_Release(
		int Handle,
		uint32_t Release_Count,
		uint32_t *P_Previous_Count)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Release_Count==0)
	{
		return Error_Invalid_Parameter;
	}
	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Semaphore,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}

	if(P_Previous_Count!=Null)
	{
		*P_Previous_Count=Temp_DATA_Node->Semaphore.Count;
	}

	if(Temp_DATA_Node->Semaphore.MAX_Count<(Release_Count+Temp_DATA_Node->Semaphore.Count))
	{
		return Error_Invalid_Parameter;
	}

	Temp_DATA_Node->Semaphore.Count=Temp_DATA_Node->Semaphore.Count+Release_Count;

	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;

	bool Try_Context_Switch=false;

	while(Temp_DATA_Node->Semaphore.Count>0)
	{

		if(Queue_TCB_Delete_Event_Node_Queue_First_TCB(Temp_Pend_Task_Queue,&Temp_TCB)==Error_OK)
		{
			Temp_DATA_Node->Semaphore.Count--;

			Queue_TCB_Delete_Suspended_Queue(Temp_TCB);
			Queue_TCB_Add_Ready_Queue(Temp_TCB);
			Temp_TCB=Null;


			Try_Context_Switch=true;
		}
		else
		{
			break;
		}

	}

	if(Try_Context_Switch==true)
	{
		__Sys_Scheduling_Try_Context_Switch();
	}

	return Error_OK;
}
#endif
