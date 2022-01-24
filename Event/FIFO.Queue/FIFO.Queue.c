/*
 * FIFO.Queue.c
 *
 *  Created on: 2019年5月5日
 *      Author: Master.HE
 */

#include <string.h>

#include "Master.Stdint.h"
#include "Define.h"
#include "Error.h"

#include "Event/Event.Enum.h"
#include "Event/__Event.Enum.h"
#include "Event/Event.h"

#include "FIFO.Queue.Struct.h"
#include "FIFO.Queue.h"

#include "__Sys.API.h"

#include "Queue/Queue.h"

#include "Scheduling/Scheduling.h"
#include "Scheduling/Scheduling.Task.h"

#ifdef Master_OS_Config_FIFO_Queue_Create
int __Sys_FIFO_Queue_Create(
		char *Name,
		uint32_t Max_FIFO_Size,
		uint32_t Max_FIFO_Queue_Length,
		__Sys_Event_FIFO_OverFlow_Function __Sys_OverFlow_Fun,
		void *__Sys_OverFlow_Args)
{
	int Err;
	if(Max_FIFO_Size==0
	|| Max_FIFO_Queue_Length==0)
	{
		return Error_Invalid_Parameter;
	}

	Event_DATA_Node_Type *Temp_DATA_Node=(Event_DATA_Node_Type *)__Sys_Memory_Malloc(sizeof(Event_FIFO_Queue_Node_Type));

	if(Temp_DATA_Node==Null)
	{
		Err=Error_Allocation_Memory_Failed;
		goto FIFO_Queue_Create_Exit1;
	}


	Temp_DATA_Node->FIFO_Queue.FIFO_DATA=__Sys_Memory_Malloc(Max_FIFO_Size*Max_FIFO_Queue_Length);

	if(Temp_DATA_Node->FIFO_Queue.FIFO_DATA==Null)
	{
		Err=Error_Allocation_Memory_Failed;
		goto FIFO_Queue_Create_Exit2;
	}

	Temp_DATA_Node->FIFO_Queue.FIFO_Size=(uint32_t *)__Sys_Memory_Malloc(sizeof(uint32_t*)*Max_FIFO_Queue_Length);

	if(Temp_DATA_Node->FIFO_Queue.FIFO_Size==Null)
	{
		Err=Error_Allocation_Memory_Failed;
		goto FIFO_Queue_Create_Exit3;
	}


	Temp_DATA_Node->FIFO_Queue.Index_In=0;
	Temp_DATA_Node->FIFO_Queue.Index_Out=0;
	Temp_DATA_Node->FIFO_Queue.Max_FIFO_Size=Max_FIFO_Size;
	Temp_DATA_Node->FIFO_Queue.Max_FIFO_Queue_Length=Max_FIFO_Queue_Length;
	Temp_DATA_Node->FIFO_Queue.Possess_TCB=Null;
	Temp_DATA_Node->FIFO_Queue.OverFlow_Fun=__Sys_OverFlow_Fun;
	Temp_DATA_Node->FIFO_Queue.OverFlow_Args=__Sys_OverFlow_Args;
	//Queue_Event_Node_Init(&Temp_DATA_Node->FIFO_Queue.Pend_Task_Queue);

	if((Err=Event_Node_Add_Node(Name,Event_Pend_FIFO_Queue,Temp_DATA_Node))<Valid_Handle)
	{
		goto FIFO_Queue_Create_Exit4;
	}
	return Err;

FIFO_Queue_Create_Exit4:
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(Temp_DATA_Node->FIFO_Queue.FIFO_Size);
#endif
FIFO_Queue_Create_Exit3:
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(Temp_DATA_Node->FIFO_Queue.FIFO_DATA);
#endif
FIFO_Queue_Create_Exit2:
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(Temp_DATA_Node);
#endif
FIFO_Queue_Create_Exit1:
	return Err;

}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Delete
int __Sys_FIFO_Queue_Delete(int Handle)
{
	if(Handle<Valid_Handle)return Error_Invalid_Handle;

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;

	if((Err=Event_Node_Delete_Node(Handle,Event_Pend_FIFO_Queue,&Temp_DATA_Node))!=Error_OK)
	{
		return Err;
	}

	if(Temp_DATA_Node!=Null)
	{
		__Sys_Memory_Free(Temp_DATA_Node->FIFO_Queue.FIFO_Size);
		__Sys_Memory_Free(Temp_DATA_Node->FIFO_Queue.FIFO_DATA);
		__Sys_Memory_Free(Temp_DATA_Node);
	}

	return Error_OK;

}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Find_Handle
int __Sys_FIFO_Queue_Find_Handle(char *Name)
{
	if(Name==Null)
	{
		return Error_Invalid_Parameter;
	}

	return Event_Node_Name_Find_Node(Name,Event_Pend_FIFO_Queue);
}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Open
int __Sys_FIFO_Queue_Open(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	//Task_Queue_Type *Temp_Pend_Task_Queue=Null;

	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_FIFO_Queue,&Temp_DATA_Node,Null)!=Error_OK))
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
	if(Temp_DATA_Node->FIFO_Queue.Possess_TCB!=Null)
	{
		if(Temp_DATA_Node->FIFO_Queue.Possess_TCB!=Temp_TCB)
		{
			return Error_Operation_Failed;
		}

	}
	Temp_DATA_Node->FIFO_Queue.Possess_TCB=Temp_TCB;
	return Error_OK;

}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Close
int __Sys_FIFO_Queue_Close(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	//Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_FIFO_Queue,&Temp_DATA_Node,Null)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}
	if(Temp_DATA_Node->FIFO_Queue.Possess_TCB==Null)
	{
		return Error_No_Open;
	}
	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;
	if((Err=__Sys_Scheduling_GET_Current_TCB(&Temp_TCB))!=Error_OK)
	{
		return Err;
	}
	if(Temp_DATA_Node->FIFO_Queue.Possess_TCB!=Temp_TCB)
	{
		return Error_Operation_Failed;
	}
	Temp_DATA_Node->FIFO_Queue.Possess_TCB=Null;

	return Error_OK;

}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Wait
int __Sys_FIFO_Queue_Wait(
		int Handle,
		void *Read_FIFO_DATA,
		uint32_t Read_FIFO_Size,
		uint32_t *Return_Read_FIFO_Size,
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

	if((Time_Out_MS!=Event_Time_Out_Query) && (Read_FIFO_DATA==Null || Read_FIFO_Size==0))
	{
		return Error_Invalid_Parameter;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_FIFO_Queue,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
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
	if(Temp_DATA_Node->FIFO_Queue.Possess_TCB!=Temp_TCB)
	{
		return Error_Operation_Failed;
	}

	//查询
	if(Time_Out_MS==Event_Time_Out_Query)
	{
		if(Temp_DATA_Node->FIFO_Queue.Index_In==Temp_DATA_Node->FIFO_Queue.Index_Out)
		{
			return Error_Dissatisfy;

		}
		else
		{
			return Error_OK;
		}
	}
	else
	{
		if(Temp_DATA_Node->FIFO_Queue.Max_FIFO_Size<Read_FIFO_Size)
		{
			return Error_Invalid_Parameter;
		}
		//尝试占用并立即返回
		if(Time_Out_MS==Event_Time_Out_Occupy_Return_Back)
		{
			if(Temp_DATA_Node->FIFO_Queue.Index_In==Temp_DATA_Node->FIFO_Queue.Index_Out)
			{
				return	Error_Dissatisfy;
			}
			else
			{

				void *P_FIFO_Data=FIFO_Queue_Void_Add(Temp_DATA_Node->FIFO_Queue.FIFO_DATA,Temp_DATA_Node->FIFO_Queue.Max_FIFO_Size*Temp_DATA_Node->FIFO_Queue.Index_Out);//&P_Node->P_FIFO[nn];
				uint32_t P_FIFO_Data_Size=Temp_DATA_Node->FIFO_Queue.FIFO_Size[Temp_DATA_Node->FIFO_Queue.Index_Out];

				if(P_FIFO_Data_Size>=Read_FIFO_Size)
				{
					memcpy(Read_FIFO_DATA,P_FIFO_Data,Read_FIFO_Size);

					if(Return_Read_FIFO_Size!=Null)*Return_Read_FIFO_Size=Read_FIFO_Size;
				}
				else
				{
					memcpy(Read_FIFO_DATA,P_FIFO_Data,P_FIFO_Data_Size);

					if(Return_Read_FIFO_Size!=Null)*Return_Read_FIFO_Size=P_FIFO_Data_Size;
				}


				Temp_DATA_Node->FIFO_Queue.Index_Out++;

				if(Temp_DATA_Node->FIFO_Queue.Max_FIFO_Queue_Length<=Temp_DATA_Node->FIFO_Queue.Index_Out)
				{
					Temp_DATA_Node->FIFO_Queue.Index_Out=0;
				}


				return	Error_OK;
			}
		}
		else//无限等待或者设置超时
		{
			if(Temp_DATA_Node->FIFO_Queue.Index_In==Temp_DATA_Node->FIFO_Queue.Index_Out)
			{

				if((Err=Queue_TCB_Add_Event_Node_Queue(Temp_Pend_Task_Queue,Temp_TCB,Event_Queue_Option_FIFO))!=Error_OK)
				{
					return Err;
				}

				int32_t RTimeOut=0;
				if((Err=__Sys_Scheduling_Context_Switch(Task_State_Pend_FIFO_Queue,Time_Out_MS,&RTimeOut))!=Error_OK)
				{
					return Err;
				}

				if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_FIFO_Queue,Null,Null)!=Error_OK))
				{
					return Err;
				}

				if(RTimeOut==0)
				{

					return Error_Time_Out;
				}

				if(Temp_DATA_Node->FIFO_Queue.Index_In==Temp_DATA_Node->FIFO_Queue.Index_Out)
				{
					return Error_Unknown;
				}
				else
				{
					void *P_FIFO_Data=FIFO_Queue_Void_Add(Temp_DATA_Node->FIFO_Queue.FIFO_DATA,Temp_DATA_Node->FIFO_Queue.Max_FIFO_Size*Temp_DATA_Node->FIFO_Queue.Index_Out);//&P_Node->P_FIFO[P_Node->Max_FIFO_Size*Temp_P_Node_TCB->Index_Out];
					uint32_t P_FIFO_Data_Size=Temp_DATA_Node->FIFO_Queue.FIFO_Size[Temp_DATA_Node->FIFO_Queue.Index_Out];

					if(P_FIFO_Data_Size>=Read_FIFO_Size)
					{
						memcpy(Read_FIFO_DATA,P_FIFO_Data,Read_FIFO_Size);

						if(Return_Read_FIFO_Size!=Null)*Return_Read_FIFO_Size=Read_FIFO_Size;
					}
					else
					{
						memcpy(Read_FIFO_DATA,P_FIFO_Data,P_FIFO_Data_Size);
						if(Return_Read_FIFO_Size!=Null)*Return_Read_FIFO_Size=P_FIFO_Data_Size;
					}

					Temp_DATA_Node->FIFO_Queue.Index_Out++;

					if(Temp_DATA_Node->FIFO_Queue.Max_FIFO_Queue_Length<=Temp_DATA_Node->FIFO_Queue.Index_Out)
					{
						Temp_DATA_Node->FIFO_Queue.Index_Out=0;
					}

					return	Error_OK;
				}

			}
			else
			{
				void *P_FIFO_Data=FIFO_Queue_Void_Add(Temp_DATA_Node->FIFO_Queue.FIFO_DATA,Temp_DATA_Node->FIFO_Queue.Max_FIFO_Size*Temp_DATA_Node->FIFO_Queue.Index_Out);//&P_Node->P_FIFO[P_Node->Max_FIFO_Size*Temp_P_Node_TCB->Index_Out];
				uint32_t P_FIFO_Data_Size=Temp_DATA_Node->FIFO_Queue.FIFO_Size[Temp_DATA_Node->FIFO_Queue.Index_Out];

				if(P_FIFO_Data_Size>=Read_FIFO_Size)
				{
					memcpy(Read_FIFO_DATA,P_FIFO_Data,Read_FIFO_Size);

					if(Return_Read_FIFO_Size!=Null)*Return_Read_FIFO_Size=Read_FIFO_Size;
				}
				else
				{
					memcpy(Read_FIFO_DATA,P_FIFO_Data,P_FIFO_Data_Size);
					if(Return_Read_FIFO_Size!=Null)*Return_Read_FIFO_Size=P_FIFO_Data_Size;
				}

				Temp_DATA_Node->FIFO_Queue.Index_Out++;

				if(Temp_DATA_Node->FIFO_Queue.Max_FIFO_Queue_Length<=Temp_DATA_Node->FIFO_Queue.Index_Out)
				{
					Temp_DATA_Node->FIFO_Queue.Index_Out=0;
				}

				return	Error_OK;
			}

		}

	}
}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Clear
int __Sys_FIFO_Queue_Clear(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	//Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_FIFO_Queue,&Temp_DATA_Node,Null)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}
	while(Temp_DATA_Node->FIFO_Queue.Index_Out!=Temp_DATA_Node->FIFO_Queue.Index_In)
	{
		void *P_FIFO_Data=FIFO_Queue_Void_Add(Temp_DATA_Node->FIFO_Queue.FIFO_DATA,Temp_DATA_Node->FIFO_Queue.Max_FIFO_Size*Temp_DATA_Node->FIFO_Queue.Index_Out);//&P_Node->P_FIFO[P_Node->Max_FIFO_Size*Temp_P_Node_TCB->Index_Out];

		Temp_DATA_Node->FIFO_Queue.OverFlow_Fun(Temp_DATA_Node->FIFO_Queue.OverFlow_Args,P_FIFO_Data,Temp_DATA_Node->FIFO_Queue.FIFO_Size[Temp_DATA_Node->FIFO_Queue.Index_Out]);

		Temp_DATA_Node->FIFO_Queue.Index_Out++;

		if(Temp_DATA_Node->FIFO_Queue.Max_FIFO_Queue_Length<=Temp_DATA_Node->FIFO_Queue.Index_Out)
		{
			Temp_DATA_Node->FIFO_Queue.Index_Out=0;
		}

	}
	//Temp_DATA_Node->FIFO_Queue.Index_Out=Temp_DATA_Node->FIFO_Queue.Index_In;

	return	Error_OK;

}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Set
int __Sys_FIFO_Queue_Set(
		int Handle,
		void *Set_FIFO_DATA,
		uint32_t Set_FIFO_Size,
		bool *Context_Switch)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Set_FIFO_DATA==Null
	|| Set_FIFO_Size==0
	|| Context_Switch==Null)
	{
		return Error_Invalid_Parameter;
	}
	if((*Context_Switch)>=bool_End)
	{
		return Error_Invalid_Parameter;
	}
	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_FIFO_Queue,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}


	if(Temp_DATA_Node->FIFO_Queue.Max_FIFO_Size<Set_FIFO_Size)
	{
		return Error_Invalid_Parameter;
	}

	void *P_FIFO_Data=FIFO_Queue_Void_Add(Temp_DATA_Node->FIFO_Queue.FIFO_DATA,Temp_DATA_Node->FIFO_Queue.Max_FIFO_Size*Temp_DATA_Node->FIFO_Queue.Index_In);//&P_Node->P_FIFO[P_Node->Max_FIFO_Size*P_Node->Index_In];
	Temp_DATA_Node->FIFO_Queue.FIFO_Size[Temp_DATA_Node->FIFO_Queue.Index_In]=Set_FIFO_Size;

	//消息复制
	memcpy(P_FIFO_Data,Set_FIFO_DATA,Set_FIFO_Size);

	Temp_DATA_Node->FIFO_Queue.Index_In++;

	if(Temp_DATA_Node->FIFO_Queue.Max_FIFO_Queue_Length<=Temp_DATA_Node->FIFO_Queue.Index_In)
	{
		Temp_DATA_Node->FIFO_Queue.Index_In=0;
	}

	//发生消息溢出
	if(Temp_DATA_Node->FIFO_Queue.Index_In==Temp_DATA_Node->FIFO_Queue.Index_Out)
	{
		P_FIFO_Data=FIFO_Queue_Void_Add(Temp_DATA_Node->FIFO_Queue.FIFO_DATA,Temp_DATA_Node->FIFO_Queue.Max_FIFO_Size*Temp_DATA_Node->FIFO_Queue.Index_Out);//&P_Node->P_FIFO[P_Node->Max_FIFO_Size*Temp_P_Node_TCB->Index_Out];

		if(Temp_DATA_Node->FIFO_Queue.OverFlow_Fun!=Null)
		{
			Temp_DATA_Node->FIFO_Queue.OverFlow_Fun(Temp_DATA_Node->FIFO_Queue.OverFlow_Args,P_FIFO_Data,Temp_DATA_Node->FIFO_Queue.FIFO_Size[Temp_DATA_Node->FIFO_Queue.Index_Out]);
		}

		Temp_DATA_Node->FIFO_Queue.Index_Out++;
		if(Temp_DATA_Node->FIFO_Queue.Max_FIFO_Queue_Length<=Temp_DATA_Node->FIFO_Queue.Index_Out)
		{
			Temp_DATA_Node->FIFO_Queue.Index_Out=0;
		}
	}

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

	if(Try_Context_Switch==true && (*Context_Switch)==true)
	{
		__Sys_Scheduling_Try_Context_Switch();
	}
	*Context_Switch=Try_Context_Switch;

	return Error_OK;
}
#endif
static void *FIFO_Queue_Void_Add(void* sou,uint32_t Index_Byte)
{
	uint8_t *P=(uint8_t*)sou;

	return (void *)&P[Index_Byte];
}
