/*
 * Semaphore.Group.c
 *
 *  Created on: 2019Äê4ÔÂ30ÈÕ
 *      Author: Master.HE
 */
#include "Master.Stdint.h"
#include "Define.h"
#include "Error.h"

#include "Event.Enum.h"
#include "Event/__Event.Enum.h"
#include "Event/Event.h"

#include "Semaphore.Group.Struct.h"
#include "Semaphore.Group.h"

#include "__Sys.API.h"

#include "Queue/Queue.h"

#include "Scheduling/Scheduling.h"
#include "Scheduling/Scheduling.Task.h"

int __Sys_Semaphore_Group_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type)
{
	int Handle;
	if(Option_Type>=Event_Queue_Option_End)
	{
		return Error_Invalid_Parameter;
	}

	Event_DATA_Node_Type *Temp_DATA_Node=(Event_DATA_Node_Type *)__Sys_Memory_Malloc(sizeof(Event_Semaphore_Group_Node_Type));

	if(Temp_DATA_Node==Null)
	{

		return Error_Allocation_Memory_Failed;
	}

	Temp_DATA_Node->Semaphore_Group.Option=Option_Type;

	Temp_DATA_Node->Semaphore_Group.Count=0;


	if((Handle=Event_Node_Add_Node(Name,Event_Pend_Semaphore_Group,Temp_DATA_Node))<Valid_Handle)
	{
		__Sys_Memory_Free(Temp_DATA_Node);
		return Handle;
	}
	return Handle;

}
int __Sys_Semaphore_Group_Delete(int Handle)
{
	if(Handle<Valid_Handle)return Error_Invalid_Handle;

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;

	if((Err=Event_Node_Delete_Node(Handle,Event_Pend_Semaphore_Group,&Temp_DATA_Node))!=Error_OK)
	{
		return Err;
	}

	if(Temp_DATA_Node!=Null)
	{
		__Sys_Memory_Free(Temp_DATA_Node);
	}
	if((Err=Event_Node_Delete_Task_Event_DATA(Handle))!=Error_OK)
	{
		return Err;
	}

	return Error_OK;

}
int __Sys_Semaphore_Group_Find_Handle(char *Name)
{
	if(Name==Null)
	{
		return Error_Invalid_Parameter;
	}

	return Event_Node_Name_Find_Node(Name,Event_Pend_Semaphore_Group);
}
int __Sys_Semaphore_Group_Wait(
		int Handle,
		bool Monopolize,
		int16_t Time_Out_MS)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	if(Monopolize>=bool_End || Time_Out_MS<Event_Time_Out_Query)
	{
		return Error_Invalid_Parameter;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Semaphore_Group,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}

	if(Time_Out_MS==Event_Time_Out_Query)
	{
		if((Monopolize==true && Temp_DATA_Node->Semaphore_Group.Count==0)
		|| (Monopolize==false && Temp_DATA_Node->Semaphore_Group.Count>=0))
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
		if((Monopolize==true && Temp_DATA_Node->Semaphore_Group.Count==0)
		|| (Monopolize==false && Temp_DATA_Node->Semaphore_Group.Count>=0))
		{
			if(Monopolize==true)
			{
				Temp_DATA_Node->Semaphore_Group.Count=-1;
			}
			else
			{
				Temp_DATA_Node->Semaphore_Group.Count++;
			}

			return Error_OK;
		}
		else
		{
			return Error_Dissatisfy;
		}

	}
	else
	{
		if((Monopolize==true && Temp_DATA_Node->Semaphore_Group.Count==0)
		|| (Monopolize==false && Temp_DATA_Node->Semaphore_Group.Count>=0))
		{
			if(Monopolize==true)
			{
				Temp_DATA_Node->Semaphore_Group.Count=-1;
			}
			else
			{
				Temp_DATA_Node->Semaphore_Group.Count++;
			}

			return Error_OK;
		}
		else
		{
			__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;
			if((Err=__Sys_Scheduling_GET_Current_TCB(&Temp_TCB))!=Error_OK)
			{
				return Err;
			}

			Task_Event_DATA_Type *Temp_DATA=Null;
			Err=Scheduling_Task_Event_List_Find_Node(Temp_TCB,Handle,&Temp_DATA);

			if(Err==Error_Invalid_Handle)
			{
				Temp_DATA=__Sys_Memory_Malloc(sizeof(Task_Event_DATA_Semaphore_Group_Type));

				if(Temp_DATA==Null)
				{
					return Error_Allocation_Memory_Failed;
				}

			}
			else if(Err==Error_OK)
			{

				if(Temp_DATA==Null)
				{
					return Error_Unknown;
				}
			}
			else
			{
				return Err;
			}

			Temp_DATA->Semaphore_Group.Semaphore_Group_Flag=Monopolize;

			if((Err=Queue_TCB_Add_Event_Node_Queue(Temp_Pend_Task_Queue,Temp_TCB,Temp_DATA_Node->Semaphore_Group.Option))!=Error_OK)
			{
				return Err;
			}

			int32_t RTimeOut=0;
			if((Err=__Sys_Scheduling_Context_Switch(Task_State_Pend_Semaphore_Group,Time_Out_MS,&RTimeOut))!=Error_OK)
			{
				return Err;
			}

			if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Semaphore_Group,Null,Null)!=Error_OK))
			{
				return Err;
			}

			if(RTimeOut==0)
			{

				return Error_Time_Out;
			}

			return Error_OK;

		}

	}

}
int __Sys_Semaphore_Group_Release(
		int Handle,
		bool Monopolize,
		int32_t *P_Previous_Count)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Monopolize>=bool_End)
	{
		return Error_Invalid_Parameter;
	}
	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Semaphore_Group,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}


	if(P_Previous_Count!=Null)
	{
		*P_Previous_Count=Temp_DATA_Node->Semaphore_Group.Count;
	}


	if(Monopolize==true)
	{
		if(Temp_DATA_Node->Semaphore_Group.Count<0)
		{
			Temp_DATA_Node->Semaphore_Group.Count=0;
		}
		else
		{
			return Error_Invalid_Parameter;
		}

	}
	else
	{
		if(Temp_DATA_Node->Semaphore_Group.Count>0)
		{
			Temp_DATA_Node->Semaphore_Group.Count--;
		}
		else
		{
			return Error_Invalid_Parameter;
		}
	}
	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;
	Task_Event_DATA_Type *Temp_DATA=Null;
	bool Try_Context_Switch=false;

	while(Queue_Read_Event_Node_Queue_First_TCB(Temp_Pend_Task_Queue,&Temp_TCB)==Error_OK)
	{
		if(Temp_TCB==Null)
		{
			return Error_Unknown;
		}

		Temp_DATA=Null;
		Err=Scheduling_Task_Event_List_Find_Node(Temp_TCB,Handle,&Temp_DATA);

		if(Err==Error_Invalid_Handle)
		{
			return Error_Unknown;
		}
		else if(Err==Error_OK)
		{
			if(Temp_DATA==Null)
			{
				return Error_Unknown;
			}
		}
		else
		{
			return Err;
		}


		if(Temp_DATA->Semaphore_Group.Semaphore_Group_Flag>=bool_End)
		{
			return Error_Unknown;
		}
		if((Temp_DATA->Semaphore_Group.Semaphore_Group_Flag==true && Temp_DATA_Node->Semaphore_Group.Count==0)
		|| (Temp_DATA->Semaphore_Group.Semaphore_Group_Flag==false && Temp_DATA_Node->Semaphore_Group.Count>=0))
		{
			if(Queue_TCB_Delete_Event_Node_Queue_First_TCB(Temp_Pend_Task_Queue,&Temp_TCB)==Error_OK)
			{
				Queue_TCB_Delete_Suspended_Queue(Temp_TCB);
				Queue_TCB_Add_Ready_Queue(Temp_TCB);
				Temp_TCB=Null;

				Try_Context_Switch=true;

				if(Temp_DATA->Semaphore_Group.Semaphore_Group_Flag==true)
				{
					Temp_DATA_Node->Semaphore_Group.Count=-1;

					break;
				}
				else
				{
					Temp_DATA_Node->Semaphore_Group.Count++;
				}

			}
			else
			{
				return Error_Unknown;
			}
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
