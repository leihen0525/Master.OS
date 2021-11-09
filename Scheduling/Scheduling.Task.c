/*
 * Scheduling.Task.c
 *
 *  Created on: 2019年4月23日
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
#ifdef Master_OS_Config_Scheduling_Exit_Task
		Task_Exit_Function Task_Exit,
#endif
		uint8_t Priority,
		uint32_t *Stack,
		uint32_t Stack_Size_4Byte,
		int Option)
{
	int Err;

	if(P_Task_TCB==Null
	|| Task_Enter==Null
#ifdef Master_OS_Config_Scheduling_Exit_Task
	|| Task_Exit==Null
#endif
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
	Temp_Task_TCB->Info.Option=Option;

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
		//字符串拷贝
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

#ifdef __UsrSP_SysSP__

	//初始化内核栈
	uint32_t Stack_Size_Sys_4Byte;

	Stack_Size_Sys_4Byte=Scheduling_Task_Stack_GET_Sys_Size_4Byte(Stack_Size_4Byte);
	extern uint32_t Stack_System_Default_Size_4Byte;
	if(Stack_Size_Sys_4Byte==0)
	{
		Stack_Size_Sys_4Byte=(uint32_t)&Stack_System_Default_Size_4Byte;
	}
	else
	{
		Stack_Size_Sys_4Byte=Stack_Size_Sys_4Byte;
	}

	//设置栈保护区域大小
	uint32_t Sys_Stack_Alignment_Byte=Stack_Alignment_Byte;
#ifdef __MPU__
	Temp_Task_TCB->Stack_System.Protection_Size=Stack_Default_Protection_Size;

	Sys_Stack_Alignment_Byte=Stack_Default_Protection_Size_Byte(Stack_Default_Protection_Size);
#endif
	Stack_Size_Sys_4Byte=Stack_Size_Sys_4Byte+8+Sys_Stack_Alignment_Byte/4;

	Temp_Task_TCB->Stack_System.SP_Head=__Sys_Memory_Malloc_Align(Stack_Size_Sys_4Byte*4+VFP_Nb,Sys_Stack_Alignment_Byte);

	if(Temp_Task_TCB->Stack_System.SP_Head==Null)
	{
		Err=Error_Allocation_Memory_Failed;
		goto Task_Create_Exit_3;
	}

	if(((uint32_t)Temp_Task_TCB->Stack_System.SP_Head&(Sys_Stack_Alignment_Byte-1))!=0)
	{
		Err=Error_Allocation_Memory_Failed;
		goto Task_Create_Exit_4;
	}

	Temp_Task_TCB->Stack_System.SP_End=&Temp_Task_TCB->Stack_System.SP_Head[(Stack_Size_Sys_4Byte+VFP_Nb/4)-1];

	memset(Temp_Task_TCB->Stack_System.SP_Head,0xEF,Stack_Size_Sys_4Byte*4+VFP_Nb);

	Temp_Task_TCB->Stack_System.SP=Temp_Task_TCB->Stack_System.SP_End;



	//初始化用户栈
	Stack_Size_4Byte=Scheduling_Task_Stack_Usr_Size_4Byte(Stack_Size_4Byte);
	uint32_t Usr_Stack_Alignment_Byte=Stack_Alignment_Byte;
#ifdef __MPU__
	Temp_Task_TCB->Stack_System.Count=0;
	//设置栈保护区域大小
	Temp_Task_TCB->Stack_User.Protection_Size=Scheduling_Task_Option_GET_Usr_Stack_Protection_Size(Temp_Task_TCB->Info.Option);
	if(Temp_Task_TCB->Stack_User.Protection_Size==0)
	{
		//没有设置保护大小，则默认大小
		Temp_Task_TCB->Stack_User.Protection_Size=Stack_Default_Protection_Size;
	}
	Usr_Stack_Alignment_Byte=Stack_Default_Protection_Size_Byte(Temp_Task_TCB->Stack_User.Protection_Size);
#endif
	if(Stack==Null)
	{
		Stack_Size_4Byte=Stack_Size_4Byte+8+Usr_Stack_Alignment_Byte/4;

		if((Temp_Task_TCB->Info.Option&Scheduling_Task_Option_System)!=0)
		{
			Temp_Task_TCB->Stack_User.SP_Head=__Sys_Memory_Malloc_Align(Stack_Size_4Byte*4,Usr_Stack_Alignment_Byte);
		}
		else
		{
			Temp_Task_TCB->Stack_User.SP_Head=__Usr_Memory_Malloc_Align(Stack_Size_4Byte*4,Usr_Stack_Alignment_Byte);
		}

		if(Temp_Task_TCB->Stack_User.SP_Head==Null)
		{
			Err=Error_Allocation_Memory_Failed;
			goto Task_Create_Exit_4;
		}

		if(((uint32_t)Temp_Task_TCB->Stack_User.SP_Head&(Usr_Stack_Alignment_Byte-1))!=0)
		{
			Err=Error_Allocation_Memory_Failed;
			goto Task_Create_Exit_5;
		}
	}
	else
	{
		Temp_Task_TCB->Stack_User.SP_Head=Stack;

		if(((uint32_t)Temp_Task_TCB->Stack_User.SP_Head&(Usr_Stack_Alignment_Byte-1))!=0)
		{
			Err=Error_Invalid_Parameter;
			goto Task_Create_Exit_4;
		}
	}



	Temp_Task_TCB->Stack_User.SP_End=&Temp_Task_TCB->Stack_User.SP_Head[(Stack_Size_4Byte)-1];

	memset(Temp_Task_TCB->Stack_User.SP_Head,0xEF,Stack_Size_4Byte*4);

	Temp_Task_TCB->Stack_User.SP=Temp_Task_TCB->Stack_User.SP_End;
#ifdef __MPU__
	Temp_Task_TCB->Stack_User.Count=0;
#endif
	if((Err=Scheduling_Task_Stack_Init(
			Task_Enter,
			Args,
#ifdef Master_OS_Config_Scheduling_Exit_Task
			Task_Exit,
#endif
			&Temp_Task_TCB->Stack_System.SP,
			&Temp_Task_TCB->Stack_User.SP,
			Option))!=Error_OK)
	{
		goto Task_Create_Exit_5;
	}

#else
	if(Stack==Null)
	{
		Temp_Task_TCB->Stack.SP_Head=__Usr_Memory_Malloc_Align(Stack_Size_4Byte*4+VFP_Nb,Stack_Alignment_Byte);
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

#endif

	Temp_Task_TCB->Priority.Default=Priority;
	Temp_Task_TCB->Priority.Current=Priority;
	Temp_Task_TCB->Info.TimeOut=-1;
	*P_Task_TCB=Temp_Task_TCB;

	Scheduling_Task_Event_List_Init(Temp_Task_TCB);

	return Error_OK;


#ifdef __UsrSP_SysSP__


Task_Create_Exit_5:

	if((Temp_Task_TCB->Info.Option&Scheduling_Task_Option_System)!=0)
	{
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(Temp_Task_TCB->Stack_User.SP_Head);
#endif
	}
	else
	{
#ifdef Master_OS_Config_Memory_Free
		__Usr_Memory_Free(Temp_Task_TCB->Stack_User.SP_Head);
#endif
	}

Task_Create_Exit_4:
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(Temp_Task_TCB->Stack_System.SP_Head);
#endif
#else
Task_Create_Exit_4:
	if(Stack==Null)
	{
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(Temp_Task_TCB->Stack.SP_Head);
#endif
	}

#endif

Task_Create_Exit_3:
	if(Temp_Task_TCB->Info.Name!=Null)
	{
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(Temp_Task_TCB->Info.Name);
#endif
	}
Task_Create_Exit_2:
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(Temp_Task_TCB);
#endif
Task_Create_Exit_1:
	return Err;
}
int Scheduling_Task_Release(__Sys_Scheduling_Task_TCB_Type *P_Task_TCB)
{
	if(P_Task_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
#ifdef __UsrSP_SysSP__
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(P_Task_TCB->Stack_System.SP_Head);
#endif
	if((P_Task_TCB->Info.Option&Scheduling_Task_Option_System)!=0)
	{
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(P_Task_TCB->Stack_User.SP_Head);
#endif
	}
	else
	{
#ifdef Master_OS_Config_Memory_Free
		__Usr_Memory_Free(P_Task_TCB->Stack_User.SP_Head);
#endif
	}
#else
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(P_Task_TCB->Stack.SP_Head);
#endif
#endif

	if(P_Task_TCB->Info.Name!=Null)
	{
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(P_Task_TCB->Info.Name);
#endif
	}
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(P_Task_TCB);
#endif
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
		//字符串拷贝
		strcpy(Temp_Task_TCB->Info.Name,Name);
	}


	Temp_Task_TCB->Priority.Default=Priority;
	Temp_Task_TCB->Priority.Current=Priority;
	Temp_Task_TCB->Info.TimeOut=-1;
	*P_Task_TCB=Temp_Task_TCB;

	Scheduling_Task_Event_List_Init(Temp_Task_TCB);
	return Error_OK;


Task_Create_Exit_2:
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(Temp_Task_TCB);
#endif
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
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(P_Task_TCB->Info.Name);
#endif
	}
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(P_Task_TCB);
#endif
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

	//分配空间失败
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

#ifdef Master_OS_Config_Memory_Free
			__Sys_Memory_Free(Temp_Node);
#endif
			return Error_OK;
		}

		Temp_Node_LAST=Temp_Node;
		Temp_Node=Temp_Node->NEXT;
	}

	return Error_Invalid_Handle;

}
