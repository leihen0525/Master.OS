/*
 * Event.Flag.c
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

#include "Event.Flag.Struct.h"
#include "Event.Flag.h"

#include "__Sys.API.h"

#include "Queue/Queue.h"

#include "Scheduling/Scheduling.h"

#ifdef Master_OS_Config_Event_Flag_Create
int __Sys_Event_Flag_Create(
		char *Name,
		bool Init_Flag)
{
	int Handle;
	if(Init_Flag>=bool_End)
	{
		return Error_Invalid_Parameter;
	}
	Event_DATA_Node_Type *Temp_DATA_Node=(Event_DATA_Node_Type *)__Sys_Memory_Malloc(sizeof(Event_Event_Flag_Node_Type));

	if(Temp_DATA_Node==Null)
	{

		return Error_Allocation_Memory_Failed;
	}

	Temp_DATA_Node->Event_Flag.Flag=Init_Flag;



	if((Handle=Event_Node_Add_Node(Name,Event_Pend_Event_Flag,Temp_DATA_Node))<Valid_Handle)
	{

		__Sys_Memory_Free(Temp_DATA_Node);
		return Handle;
	}
	return Handle;

}
#endif
#ifdef Master_OS_Config_Event_Flag_Delete
int __Sys_Event_Flag_Delete(int Handle)
{
	if(Handle<Valid_Handle)return Error_Invalid_Handle;

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;

	if((Err=Event_Node_Delete_Node(Handle,Event_Pend_Event_Flag,&Temp_DATA_Node))!=Error_OK)
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
#ifdef Master_OS_Config_Event_Flag_Find_Handle
int __Sys_Event_Flag_Find_Handle(char *Name)
{
	if(Name==Null)
	{
		return Error_Invalid_Parameter;
	}

	return Event_Node_Name_Find_Node(Name,Event_Pend_Event_Flag);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Wait
int __Sys_Event_Flag_Wait(
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
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}

	if(Time_Out_MS==Event_Time_Out_Query
	|| Time_Out_MS==Event_Time_Out_Occupy_Return_Back)
	{
		if(Temp_DATA_Node->Event_Flag.Flag==true)
		{
			return	Error_OK;

		}
		else
		{
			return	Error_Dissatisfy;
		}
	}
	else
	{
		if(Temp_DATA_Node->Event_Flag.Flag==true)
		{
			return	Error_OK;

		}
		else
		{
			__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;
			if((Err=__Sys_Scheduling_GET_Current_TCB(&Temp_TCB))!=Error_OK)
			{
				return Err;
			}

			if((Err=Queue_TCB_Add_Event_Node_Queue(Temp_Pend_Task_Queue,Temp_TCB,Event_Queue_Option_FIFO))!=Error_OK)
			{
				return Err;
			}

			int32_t RTimeOut=0;
			if((Err=__Sys_Scheduling_Context_Switch(Task_State_Pend_Event_Flag,Time_Out_MS,&RTimeOut))!=Error_OK)
			{
				return Err;
			}

			if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag,Null,Null)!=Error_OK))
			{
				return Err;
			}

			if(RTimeOut==0)
			{

				return Error_Time_Out;
			}
			if(Temp_DATA_Node->Event_Flag.Flag!=true)
			{
				return Error_Unknown;
			}
			return Error_OK;
		}
	}

}
#endif
#ifdef Master_OS_Config_Event_Flag_Clear
int __Sys_Event_Flag_Clear(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag,&Temp_DATA_Node,Null)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}
	Temp_DATA_Node->Event_Flag.Flag=false;

	return Error_OK;

}
#endif
#ifdef Master_OS_Config_Event_Flag_Set
int __Sys_Event_Flag_Set(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}
	Temp_DATA_Node->Event_Flag.Flag=true;

	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;

	bool Try_Context_Switch=false;

	//将等待的任务 放入准备运行队列
	while(Queue_TCB_Delete_Event_Node_Queue_First_TCB(Temp_Pend_Task_Queue,&Temp_TCB)==Error_OK)
	{
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
#endif
