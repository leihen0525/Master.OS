/*
 * Event.c
 *
 *  Created on: 2019年4月29日
 *      Author: Master.HE
 */
#include <string.h>

#include "Error.h"
#include "Define.h"

#include "Event.h"
#include "Queue/Queue.h"

#include "__Sys.API.h"

#include "Scheduling/Scheduling.h"

#include "Scheduling/Scheduling.Task.h"

Event_DATA_Type Event_DATA;

int Event_Init(void)
{
	Event_DATA.Head=Null;
	Event_DATA.End=Null;


	return Error_OK;
}

int Event_Node_Add_Node(
		char *Name,
		Event_Pend_Type Pend_Type,
		Event_DATA_Node_Type *DATA_Node)
{
	int Err;
	if(Pend_Type>=Event_Pend_End)
	{
		return Error_Invalid_Parameter;
	}

	Event_Node_Type *Temp_Node=Null;


	Temp_Node=(Event_Node_Type *)__Sys_Memory_Malloc(sizeof(Event_Node_Type));

	//分配空间失败
	if(Temp_Node==Null)
	{
		return Error_Allocation_Memory_Failed;
	}

	if(Name==Null)
	{
		Temp_Node->Name=Null;
	}
	else
	{
		Temp_Node->Name=(int8_t *)__Sys_Memory_Malloc(strlen(Name)+1);

		//分配空间失败
		if(Temp_Node->Name==Null)
		{

			Err=Error_Allocation_Memory_Failed;
			goto Event_Add_Node_Exit1;
		}

		//字符串拷贝
		strcpy(Temp_Node->Name,Name);

	}

	Queue_Event_Node_Init(&Temp_Node->Pend_Task_Queue);

	Temp_Node->Event_Pend=Pend_Type;

	Temp_Node->DATA_Node=DATA_Node;


	if((Err=__Sys_Apply_Handle())<Valid_Handle)
	{
		goto Event_Add_Node_Exit2;
	}

	Temp_Node->Handle=Err;

	if(Event_DATA.End==Null)
	{
		Event_DATA.Head=Temp_Node;
	}
	else
	{
		Event_DATA.End->NEXT=Temp_Node;
	}
	Event_DATA.End=Temp_Node;

	Temp_Node->NEXT=Null;



	return Temp_Node->Handle;

Event_Add_Node_Exit2:
	if(Temp_Node->Name!=Null)
	{
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(Temp_Node->Name);
#endif
	}
Event_Add_Node_Exit1:
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(Temp_Node);
#endif
	return Err;
}
int Event_Node_Delete_Node(
		int Handle,
		Event_Pend_Type Pend_Type,
		Event_DATA_Node_Type **DATA_Node)
{
	if(Handle<Valid_Handle || Pend_Type>=Event_Pend_End)
	{
		return Error_Invalid_Parameter;
	}

	Event_Node_Type *Temp_Node_LAST=Null,*Temp_Node=Null;

	Temp_Node=Event_DATA.Head;

	while(Temp_Node!=Null)
	{
		if(Temp_Node->Handle==Handle && Temp_Node->Event_Pend==Pend_Type)
		{

			if(Temp_Node_LAST==Null)
			{
				Event_DATA.Head=Temp_Node->NEXT;
			}
			else
			{
				Temp_Node_LAST->NEXT=Temp_Node->NEXT;
			}
			if(Temp_Node==Event_DATA.End || Temp_Node->NEXT==Null)
			{
				Event_DATA.End=Temp_Node_LAST;
			}
			Temp_Node->NEXT=Null;


			if(Temp_Node->Name!=Null)
			{
#ifdef Master_OS_Config_Memory_Free
				__Sys_Memory_Free(Temp_Node->Name);
#endif
			}

			if(DATA_Node!=Null)
			{
				*DATA_Node=Temp_Node->DATA_Node;
			}

			//清除等待队列
			__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;
			bool Try_Context_Switch=false;

			while(Queue_TCB_Delete_Event_Node_Queue_First_TCB(&Temp_Node->Pend_Task_Queue,&Temp_TCB)==Error_OK)
			{
				Queue_TCB_Delete_Suspended_Queue(Temp_TCB);
				Queue_TCB_Add_Ready_Queue(Temp_TCB);
				Temp_TCB=Null;

				Try_Context_Switch=true;
			}
#ifdef Master_OS_Config_Memory_Free
			__Sys_Memory_Free(Temp_Node);
#endif
			if(Try_Context_Switch==true)
			{
				__Sys_Scheduling_Try_Context_Switch();
			}

			return Error_OK;
		}


		Temp_Node_LAST=Temp_Node;
		Temp_Node=Temp_Node->NEXT;
	}

	return Error_Invalid_Handle;

}
int Event_Node_Name_Find_Node(
		char *Name,
		Event_Pend_Type Pend_Type)
{
	if(Name==Null || Pend_Type>=Event_Pend_End)
	{
		return Error_Invalid_Parameter;
	}
	Event_Node_Type *Temp_Node=Null;

	Temp_Node=Event_DATA.Head;

	while(Temp_Node!=Null)
	{
		if(strcmp(Temp_Node->Name,Name)==0 && Temp_Node->Event_Pend==Pend_Type)
		{
			return Temp_Node->Handle;
		}
		Temp_Node=Temp_Node->NEXT;
	}
	return Error_Invalid_Parameter;
}
int Event_Node_Handle_Find_Node(
		int Handle,
		Event_Pend_Type Pend_Type,
		Event_DATA_Node_Type **DATA_Node,
		Task_Queue_Type **Pend_Task_Queue)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Pend_Type>=Event_Pend_End)
	{
		return Error_Invalid_Parameter;
	}
	Event_Node_Type *Temp_Node=Null;

	Temp_Node=Event_DATA.Head;

	while(Temp_Node!=Null)
	{
		if(Temp_Node->Handle==Handle && Temp_Node->Event_Pend==Pend_Type)
		{
			if(DATA_Node!=Null)
			{
				*DATA_Node=Temp_Node->DATA_Node;
			}
			if(Pend_Task_Queue!=Null)
			{
				*Pend_Task_Queue=&Temp_Node->Pend_Task_Queue;
			}
			return Error_OK;
		}
		Temp_Node=Temp_Node->NEXT;
	}
	return Error_Invalid_Handle;
}

int Event_Node_Delete_Task_Event_DATA(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Parameter;
	}
	Task_Queue_Type *P_TCB_Queue=Null;

	int Err;
	if((Err=Queue_Read_TCB_Queue(&P_TCB_Queue))!=Error_OK)
	{
		return Err;
	}
	if(P_TCB_Queue==Null)
	{
		return Error_Unknown;
	}

	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=P_TCB_Queue->Begin;

	Task_Event_DATA_Type *DATA=Null;
	while(Temp_TCB!=Null)
	{
		if(Scheduling_Task_Event_List_Delete_Node(Temp_TCB,Handle,&DATA)==Error_OK)
		{
			if(DATA==Null)
			{
				return Error_Unknown;
			}
#ifdef Master_OS_Config_Memory_Free
			__Sys_Memory_Free(DATA);
#endif
			DATA=Null;
		}
		Temp_TCB=Temp_TCB->Queue.TCB_NEXT;
	}
	return Error_OK;
}
