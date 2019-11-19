/*
 * Scheduling.Task.c
 *
 *  Created on: 2019��4��23��
 *      Author: Master.HE
 */
#include <string.h>

#include "Error.h"
#include "Define.h"
#include "__Sys.API.h"
#include "Arch/Arm/Scheduling.Task.Stack.h"
#include "Scheduling.Task.h"
#include "Memory/Memory.h"


int Scheduling_Task_Create(
		__Sys_Scheduling_Task_TCB_Type **P_Task_TCB,
		char *Name,
		Task_Enter_Function Task_Enter,
		void *Args,
		Task_Exit_Function Task_Exit,
		uint8_t Priority,
		uint32_t *Stack,
		uint32_t Stack_Size_4Byte,
		int Option)
{
	int Err;

	if(P_Task_TCB==Null
	|| Task_Enter==Null
	|| Task_Exit==Null
	|| Stack_Size_4Byte==0)
	{
		return Error_Invalid_Parameter;
	}

	__Sys_Scheduling_Task_TCB_Type *Temp_Task_TCB=__Sys_Memory_Malloc(sizeof(__Sys_Scheduling_Task_TCB_Type));
	if(Temp_Task_TCB==Null)
	{
		Err=Error_Allocation_Memory_Failed;
		goto Task_Create_Exit_1;

	}

	if(Name==Null)
	{
		Temp_Task_TCB->Info.Name=Null;
	}
	else
	{
		Temp_Task_TCB->Info.Name=__Sys_Memory_Malloc(strlen(Name)+1);
		if(Temp_Task_TCB->Info.Name==Null)
		{
			Err=Error_Allocation_Memory_Failed;
			goto Task_Create_Exit_2;
		}
		//�ַ�������
		strcpy(Temp_Task_TCB->Info.Name,Name);
	}

	int VFP_Nb=0;
#ifdef __ARMVFP__
	if((Option&Scheduling_Task_Option_FPU_VFP)!=0)
	{
		VFP_Nb=sizeof(Scheduling_Task_Stack_VFP_Type);
	}
	else
	{
		VFP_Nb=0;
	}

#endif
	if(Stack==Null)
	{
		Temp_Task_TCB->Stack.SP_Head=__Usr_Memory_Malloc(Stack_Size_4Byte*4+VFP_Nb);
		if(Temp_Task_TCB->Stack.SP_Head==Null)
		{
			Err=Error_Allocation_Memory_Failed;
			goto Task_Create_Exit_3;
		}

	}
	else
	{
		Temp_Task_TCB->Stack.SP_Head=Stack;
	}

	Temp_Task_TCB->Stack.SP_End=&Temp_Task_TCB->Stack.SP_Head[(Stack_Size_4Byte+VFP_Nb/4)-1];

	memset(Temp_Task_TCB->Stack.SP_Head,0xEF,Stack_Size_4Byte*4+VFP_Nb);

	Temp_Task_TCB->Stack.SP=Temp_Task_TCB->Stack.SP_End;

	if((Err=Scheduling_Task_Stack_Init(Task_Enter,Args,Task_Exit,&Temp_Task_TCB->Stack.SP,Option))!=Error_OK)
	{
		goto Task_Create_Exit_4;
	}
	Temp_Task_TCB->Priority.Default=Priority;
	Temp_Task_TCB->Priority.Current=Priority;
	Temp_Task_TCB->Info.TimeOut=-1;
	*P_Task_TCB=Temp_Task_TCB;

	Scheduling_Task_Event_List_Init(Temp_Task_TCB);

	return Error_OK;

Task_Create_Exit_4:
	if(Stack==Null)
	{
		__Sys_Memory_Free(Temp_Task_TCB->Stack.SP_Head);
	}

Task_Create_Exit_3:
	if(Temp_Task_TCB->Info.Name!=Null)
	{
		__Sys_Memory_Free(Temp_Task_TCB->Info.Name);
	}
Task_Create_Exit_2:
	__Sys_Memory_Free(Temp_Task_TCB);
Task_Create_Exit_1:
	return Err;
}
int Scheduling_Task_Release(__Sys_Scheduling_Task_TCB_Type *P_Task_TCB)
{
	if(P_Task_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
	__Sys_Memory_Free(P_Task_TCB->Stack.SP_Head);
	if(P_Task_TCB->Info.Name!=Null)
	{
		__Sys_Memory_Free(P_Task_TCB->Info.Name);
	}
	__Sys_Memory_Free(P_Task_TCB);

	return Error_OK;
}
int Scheduling_Task_Create_Idle(
		__Sys_Scheduling_Task_TCB_Type **P_Task_TCB,
		char *Name,
		uint8_t Priority)
{
	int Err;

	if(P_Task_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}

	__Sys_Scheduling_Task_TCB_Type *Temp_Task_TCB=__Sys_Memory_Malloc(sizeof(__Sys_Scheduling_Task_TCB_Type));
	if(Temp_Task_TCB==Null)
	{
		Err=Error_Allocation_Memory_Failed;
		goto Task_Create_Exit_1;

	}

	if(Name==Null)
	{
		Temp_Task_TCB->Info.Name=Null;
	}
	else
	{
		Temp_Task_TCB->Info.Name=__Sys_Memory_Malloc(strlen(Name)+1);
		if(Temp_Task_TCB->Info.Name==Null)
		{
			Err=Error_Allocation_Memory_Failed;
			goto Task_Create_Exit_2;
		}
		//�ַ�������
		strcpy(Temp_Task_TCB->Info.Name,Name);
	}


	Temp_Task_TCB->Priority.Default=Priority;
	Temp_Task_TCB->Priority.Current=Priority;
	Temp_Task_TCB->Info.TimeOut=-1;
	*P_Task_TCB=Temp_Task_TCB;

	Scheduling_Task_Event_List_Init(Temp_Task_TCB);
	return Error_OK;


Task_Create_Exit_2:
	__Sys_Memory_Free(Temp_Task_TCB);
Task_Create_Exit_1:
	return Err;
}
int Scheduling_Task_Release_Idle(__Sys_Scheduling_Task_TCB_Type *P_Task_TCB)
{
	if(P_Task_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(P_Task_TCB->Info.Name!=Null)
	{
		__Sys_Memory_Free(P_Task_TCB->Info.Name);
	}
	__Sys_Memory_Free(P_Task_TCB);

	return Error_OK;
}
//-----------------------------------
int Scheduling_Task_Event_List_Init(__Sys_Scheduling_Task_TCB_Type *P_Task_TCB)
{
	if(P_Task_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
	P_Task_TCB->Event.List.Head=Null;
	P_Task_TCB->Event.List.End=Null;
	return Error_OK;
}
int Scheduling_Task_Event_List_Add_Node(
		__Sys_Scheduling_Task_TCB_Type *Task,
		int Handle,
		Task_Event_DATA_Type *DATA)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Task==Null || DATA==Null)
	{
		return Error_Invalid_Parameter;
	}
	Task_Event_List_Type *Temp_Node=Null;

	Temp_Node=(Task_Event_List_Type *)__Sys_Memory_Malloc(sizeof(Task_Event_List_Type));

	//����ռ�ʧ��
	if(Temp_Node==Null)
	{
		return Error_Allocation_Memory_Failed;
	}

	Temp_Node->Handle=Handle;
	Temp_Node->DATA=DATA;

	if(Task->Event.List.End==Null)
	{
		Task->Event.List.Head=Temp_Node;
	}
	else
	{
		Task->Event.List.End->NEXT=Temp_Node;
	}
	Task->Event.List.End=Temp_Node;

	Temp_Node->NEXT=Null;

	return Error_OK;
}
int Scheduling_Task_Event_List_Find_Node(
		__Sys_Scheduling_Task_TCB_Type *Task,
		int Handle,
		Task_Event_DATA_Type **DATA)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Task==Null)
	{
		return Error_Invalid_Parameter;
	}
	Task_Event_List_Type *Temp_Node=Null;

	Temp_Node=Task->Event.List.Head;

	while(Temp_Node!=Null)
	{
		if(Handle==Temp_Node->Handle)
		{
			if(DATA!=Null)
			{
				*DATA=Temp_Node->DATA;
			}

			return Error_OK;
		}
		Temp_Node=Temp_Node->NEXT;
	}
	return Error_Invalid_Handle;
}
int Scheduling_Task_Event_List_Delete_Node(
		__Sys_Scheduling_Task_TCB_Type *Task,
		int Handle,
		Task_Event_DATA_Type **DATA)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Task==Null || DATA==Null)
	{
		return Error_Invalid_Parameter;
	}

	Task_Event_List_Type *Temp_Node_LAST=Null,*Temp_Node=Null;

	Temp_Node=Task->Event.List.Head;

	while(Temp_Node!=Null)
	{
		if(Temp_Node->Handle==Handle)
		{

			if(Temp_Node_LAST==Null)
			{
				Task->Event.List.Head=Temp_Node->NEXT;
			}
			else
			{
				Temp_Node_LAST->NEXT=Temp_Node->NEXT;
			}
			if(Temp_Node==Task->Event.List.End || Temp_Node->NEXT==Null)
			{
				Task->Event.List.End=Temp_Node_LAST;
			}
			Temp_Node->NEXT=Null;

			*DATA=Temp_Node->DATA;

			__Sys_Memory_Free(Temp_Node);

			return Error_OK;
		}

		Temp_Node_LAST=Temp_Node;
		Temp_Node=Temp_Node->NEXT;
	}

	return Error_Invalid_Handle;

}
