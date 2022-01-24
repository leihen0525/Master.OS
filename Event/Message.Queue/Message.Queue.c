/*
 * Message.Queue.c
 *
 *  Created on: 2019年4月30日
 *      Author: Master.HE
 */
#include <string.h>

#include "Master.Stdint.h"
#include "Define.h"
#include "Error.h"

#include "Event/Event.Enum.h"
#include "Event/__Event.Enum.h"
#include "Event/Event.h"

#include "Message.Queue.Struct.h"
#include "Message.Queue.h"

#include "__Sys.API.h"

#include "Queue/Queue.h"

#include "Scheduling/Scheduling.h"
#include "Scheduling/Scheduling.Task.h"

#ifdef Master_OS_Config_Message_Queue_Create
int __Sys_Message_Queue_Create(
		char *Name,
		uint32_t Max_Message_Size,
		uint32_t Max_Message_Queue_Length)
{
	int Err;
	if(Max_Message_Size==0
	|| Max_Message_Queue_Length==0)
	{
		return Error_Invalid_Parameter;
	}

	Event_DATA_Node_Type *Temp_DATA_Node=(Event_DATA_Node_Type *)__Sys_Memory_Malloc(sizeof(Event_Message_Queue_Node_Type));

	if(Temp_DATA_Node==Null)
	{
		Err=Error_Allocation_Memory_Failed;
		goto Message_Queue_Create_Exit1;
	}


	Temp_DATA_Node->Message_Queue.Message_DATA=__Sys_Memory_Malloc(Max_Message_Size*Max_Message_Queue_Length);

	if(Temp_DATA_Node->Message_Queue.Message_DATA==Null)
	{
		Err=Error_Allocation_Memory_Failed;
		goto Message_Queue_Create_Exit2;
	}

	Temp_DATA_Node->Message_Queue.Message_Size=(uint32_t *)__Sys_Memory_Malloc(sizeof(uint32_t*)*Max_Message_Queue_Length);

	if(Temp_DATA_Node->Message_Queue.Message_Size==Null)
	{
		Err=Error_Allocation_Memory_Failed;
		goto Message_Queue_Create_Exit3;
	}


	Temp_DATA_Node->Message_Queue.Index_In=0;

	Temp_DATA_Node->Message_Queue.Max_Message_Size=Max_Message_Size;
	Temp_DATA_Node->Message_Queue.Max_Message_Queue_Length=Max_Message_Queue_Length;



	if((Err=Event_Node_Add_Node(Name,Event_Pend_Message_Queue,Temp_DATA_Node))<Valid_Handle)
	{
		goto Message_Queue_Create_Exit4;
	}
	return Err;

Message_Queue_Create_Exit4:
	__Sys_Memory_Free(Temp_DATA_Node->Message_Queue.Message_Size);
Message_Queue_Create_Exit3:
	__Sys_Memory_Free(Temp_DATA_Node->Message_Queue.Message_DATA);
Message_Queue_Create_Exit2:
	__Sys_Memory_Free(Temp_DATA_Node);
Message_Queue_Create_Exit1:
	return Err;

}
#endif
#ifdef Master_OS_Config_Message_Queue_Delete
int __Sys_Message_Queue_Delete(int Handle)
{
	if(Handle<Valid_Handle)return Error_Invalid_Handle;

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;

	if((Err=Event_Node_Delete_Node(Handle,Event_Pend_Message_Queue,&Temp_DATA_Node))!=Error_OK)
	{
		return Err;
	}

	if(Temp_DATA_Node!=Null)
	{
		__Sys_Memory_Free(Temp_DATA_Node->Message_Queue.Message_Size);
		__Sys_Memory_Free(Temp_DATA_Node->Message_Queue.Message_DATA);
		__Sys_Memory_Free(Temp_DATA_Node);
	}
	if((Err=Event_Node_Delete_Task_Event_DATA(Handle))!=Error_OK)
	{
		return Err;
	}

	return Error_OK;

}
#endif
#ifdef Master_OS_Config_Message_Queue_Find_Handle
int __Sys_Message_Queue_Find_Handle(char *Name)
{
	if(Name==Null)
	{
		return Error_Invalid_Parameter;
	}

	return Event_Node_Name_Find_Node(Name,Event_Pend_Message_Queue);
}
#endif
#ifdef Master_OS_Config_Message_Queue_Open
int __Sys_Message_Queue_Open(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;

	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Message_Queue,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
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

	Err=Scheduling_Task_Event_List_Find_Node(Temp_TCB,Handle,Null);

	if(Err==Error_Invalid_Handle)
	{
		;
	}
	else if(Err==Error_OK)
	{
		return Error_OK;
	}
	else
	{
		return Err;
	}

	Task_Event_DATA_Type *Temp_DATA=__Sys_Memory_Malloc(sizeof(Task_Event_DATA_Message_Queue_Type));
	if(Temp_DATA==Null)
	{
		return Error_Allocation_Memory_Failed;
	}
	Temp_DATA->Message_Queue.Index_Out=Temp_DATA_Node->Message_Queue.Index_In;

	if((Err=Scheduling_Task_Event_List_Add_Node(Temp_TCB,Handle,Temp_DATA))!=Error_OK)
	{
		__Sys_Memory_Free(Temp_DATA);
		return Err;
	}
	return Error_OK;

}
#endif
#ifdef Master_OS_Config_Message_Queue_Close
int __Sys_Message_Queue_Close(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Message_Queue,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
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
	Task_Event_DATA_Type *Temp_DATA=Null;

	if((Err=Scheduling_Task_Event_List_Delete_Node(Temp_TCB,Handle,&Temp_DATA))!=Error_OK)
	{
		if(Err==Error_Invalid_Handle)
		{
			return Error_No_Open;
		}
		return Err;
	}


	if(Temp_DATA==Null)
	{
		return Error_Unknown;
	}
	__Sys_Memory_Free(Temp_DATA);

	return Error_OK;

}
#endif
#ifdef Master_OS_Config_Message_Queue_Wait
int __Sys_Message_Queue_Wait(
		int Handle,
		void *Read_Message_DATA,
		uint32_t Read_Message_Size,
		uint32_t *Return_Read_Message_Size,
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

	if((Time_Out_MS!=Event_Time_Out_Query) && (Read_Message_DATA==Null || Read_Message_Size==0))
	{
		return Error_Invalid_Parameter;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Message_Queue,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
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
	//检查当前task是否和当前事件关联，如果关联则导出task关于此事件参数表
	Task_Event_DATA_Type *Temp_DATA=Null;
	Err=Scheduling_Task_Event_List_Find_Node(Temp_TCB,Handle,&Temp_DATA);

	if(Err==Error_Invalid_Handle)
	{
		return Error_No_Open;
	}
	else if(Err==Error_OK)
	{
		;
	}
	else
	{
		return Err;
	}
	if(Temp_DATA==Null)
	{
		return Error_Unknown;
	}

	//查询
	if(Time_Out_MS==Event_Time_Out_Query)
	{
		if(Temp_DATA_Node->Message_Queue.Index_In==Temp_DATA->Message_Queue.Index_Out)
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
		if(Temp_DATA_Node->Message_Queue.Max_Message_Size<Read_Message_Size)
		{
			return Error_Invalid_Parameter;
		}
		//尝试占用并立即返回
		if(Time_Out_MS==Event_Time_Out_Occupy_Return_Back)
		{
			if(Temp_DATA_Node->Message_Queue.Index_In==Temp_DATA->Message_Queue.Index_Out)
			{
				return	Error_Dissatisfy;
			}
			else
			{

				void *P_Message_Data=Message_Queue_Void_Add(Temp_DATA_Node->Message_Queue.Message_DATA,Temp_DATA_Node->Message_Queue.Max_Message_Size*Temp_DATA->Message_Queue.Index_Out);//&P_Node->P_Message[nn];
				uint32_t P_Message_Data_Size=Temp_DATA_Node->Message_Queue.Message_Size[Temp_DATA->Message_Queue.Index_Out];

				if(P_Message_Data_Size>=Read_Message_Size)
				{
					memcpy(Read_Message_DATA,P_Message_Data,Read_Message_Size);

					if(Return_Read_Message_Size!=Null)*Return_Read_Message_Size=Read_Message_Size;
				}
				else
				{
					memcpy(Read_Message_DATA,P_Message_Data,P_Message_Data_Size);

					if(Return_Read_Message_Size!=Null)*Return_Read_Message_Size=P_Message_Data_Size;
				}


				Temp_DATA->Message_Queue.Index_Out++;

				if(Temp_DATA_Node->Message_Queue.Max_Message_Queue_Length<=Temp_DATA->Message_Queue.Index_Out)
				{
					Temp_DATA->Message_Queue.Index_Out=0;
				}


				return	Error_OK;
			}
		}
		else//无限等待或者设置超时
		{
			if(Temp_DATA_Node->Message_Queue.Index_In==Temp_DATA->Message_Queue.Index_Out)
			{

				if((Err=Queue_TCB_Add_Event_Node_Queue(Temp_Pend_Task_Queue,Temp_TCB,Event_Queue_Option_FIFO))!=Error_OK)
				{
					return Err;
				}

				int32_t RTimeOut=0;
				if((Err=__Sys_Scheduling_Context_Switch(Task_State_Pend_Message_Queue,Time_Out_MS,&RTimeOut))!=Error_OK)
				{
					return Err;
				}

				if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Message_Queue,Null,Null)!=Error_OK))
				{
					return Err;
				}

				if(RTimeOut==0)
				{

					return Error_Time_Out;
				}

				if(Temp_DATA_Node->Message_Queue.Index_In==Temp_DATA->Message_Queue.Index_Out)
				{
					return Error_Unknown;
				}
				else
				{
					void *P_Message_Data=Message_Queue_Void_Add(Temp_DATA_Node->Message_Queue.Message_DATA,Temp_DATA_Node->Message_Queue.Max_Message_Size*Temp_DATA->Message_Queue.Index_Out);//&P_Node->P_Message[P_Node->Max_Message_Size*Temp_P_Node_TCB->Index_Out];
					uint32_t P_Message_Data_Size=Temp_DATA_Node->Message_Queue.Message_Size[Temp_DATA->Message_Queue.Index_Out];

					if(P_Message_Data_Size>=Read_Message_Size)
					{
						memcpy(Read_Message_DATA,P_Message_Data,Read_Message_Size);

						if(Return_Read_Message_Size!=Null)*Return_Read_Message_Size=Read_Message_Size;
					}
					else
					{
						memcpy(Read_Message_DATA,P_Message_Data,P_Message_Data_Size);
						if(Return_Read_Message_Size!=Null)*Return_Read_Message_Size=P_Message_Data_Size;
					}

					Temp_DATA->Message_Queue.Index_Out++;

					if(Temp_DATA_Node->Message_Queue.Max_Message_Queue_Length<=Temp_DATA->Message_Queue.Index_Out)
					{
						Temp_DATA->Message_Queue.Index_Out=0;
					}

					return	Error_OK;
				}

			}
			else
			{
				void *P_Message_Data=Message_Queue_Void_Add(Temp_DATA_Node->Message_Queue.Message_DATA,Temp_DATA_Node->Message_Queue.Max_Message_Size*Temp_DATA->Message_Queue.Index_Out);//&P_Node->P_Message[P_Node->Max_Message_Size*Temp_P_Node_TCB->Index_Out];
				uint32_t P_Message_Data_Size=Temp_DATA_Node->Message_Queue.Message_Size[Temp_DATA->Message_Queue.Index_Out];

				if(P_Message_Data_Size>=Read_Message_Size)
				{
					memcpy(Read_Message_DATA,P_Message_Data,Read_Message_Size);

					if(Return_Read_Message_Size!=Null)*Return_Read_Message_Size=Read_Message_Size;
				}
				else
				{
					memcpy(Read_Message_DATA,P_Message_Data,P_Message_Data_Size);
					if(Return_Read_Message_Size!=Null)*Return_Read_Message_Size=P_Message_Data_Size;
				}

				Temp_DATA->Message_Queue.Index_Out++;

				if(Temp_DATA_Node->Message_Queue.Max_Message_Queue_Length<=Temp_DATA->Message_Queue.Index_Out)
				{
					Temp_DATA->Message_Queue.Index_Out=0;
				}

				return	Error_OK;
			}

		}

	}
}
#endif
#ifdef Master_OS_Config_Message_Queue_Clear
int __Sys_Message_Queue_Clear(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	//Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Message_Queue,&Temp_DATA_Node,Null)!=Error_OK))
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
	//检查当前task是否和当前事件关联，如果关联则导出task关于此事件参数表
	Task_Event_DATA_Type *Temp_DATA=Null;
	Err=Scheduling_Task_Event_List_Find_Node(Temp_TCB,Handle,&Temp_DATA);

	if(Err==Error_Invalid_Handle)
	{
		return Error_No_Open;
	}
	else if(Err==Error_OK)
	{
		;
	}
	else
	{
		return Err;
	}
	if(Temp_DATA==Null)
	{
		return Error_Unknown;
	}


	Temp_DATA->Message_Queue.Index_Out=Temp_DATA_Node->Message_Queue.Index_In;

	return	Error_OK;

}
#endif
#ifdef Master_OS_Config_Message_Queue_Set
int __Sys_Message_Queue_Set(
		int Handle,
		void *Set_Message_DATA,
		uint32_t Set_Message_Size)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Set_Message_DATA==Null || Set_Message_Size==0)
	{
		return Error_Invalid_Parameter;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Message_Queue,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}


	if(Temp_DATA_Node->Message_Queue.Max_Message_Size<Set_Message_Size)
	{
		return Error_Invalid_Parameter;
	}

	void *P_Message_Data=Message_Queue_Void_Add(Temp_DATA_Node->Message_Queue.Message_DATA,Temp_DATA_Node->Message_Queue.Max_Message_Size*Temp_DATA_Node->Message_Queue.Index_In);//&P_Node->P_Message[P_Node->Max_Message_Size*P_Node->Index_In];
	Temp_DATA_Node->Message_Queue.Message_Size[Temp_DATA_Node->Message_Queue.Index_In]=Set_Message_Size;

	//消息复制
	memcpy(P_Message_Data,Set_Message_DATA,Set_Message_Size);

	Temp_DATA_Node->Message_Queue.Index_In++;

	if(Temp_DATA_Node->Message_Queue.Max_Message_Queue_Length<=Temp_DATA_Node->Message_Queue.Index_In)
	{
		Temp_DATA_Node->Message_Queue.Index_In=0;
	}

	//通知所有绑定的任务
	Task_Queue_Type *TCB_Queue=Null;

	Queue_Read_TCB_Queue(&TCB_Queue);

	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=TCB_Queue->Begin;
	Task_Event_DATA_Type *Temp_DATA=Null;
	while(Temp_TCB!=Null)
	{

		if(Scheduling_Task_Event_List_Find_Node(Temp_TCB,Handle,&Temp_DATA)==Error_OK)
		{
			if(Temp_DATA==Null)
			{
				return Error_Unknown;
			}

			//发生消息溢出
			if(Temp_DATA_Node->Message_Queue.Index_In==Temp_DATA->Message_Queue.Index_Out)
			{
				Temp_DATA->Message_Queue.Index_Out++;
				if(Temp_DATA_Node->Message_Queue.Max_Message_Queue_Length<=Temp_DATA->Message_Queue.Index_Out)
				{
					Temp_DATA->Message_Queue.Index_Out=0;
				}
			}

		}

		Temp_TCB=Temp_TCB->Queue.TCB_NEXT;
	}

	Temp_TCB=Null;
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

	//增加额外的队列--事件组

//	Event_Group_Node_Type *Temp_Group_Node=Null;
//
//	Temp_Group_Node=P_Event_Group->List.Head;
//
//	while(Temp_Group_Node!=Null)
//	{
//
//		if(Event_Group_Node_Check_Node_List_Valid(Temp_Group_Node,P_Node)==true)
//		{
//
//			while((Temp_TCB=Task_Queue_Del_First_TCB_At_Task_FIFO_PRIO_Queue(&Temp_Group_Node->Pend_Task_Queue))!=Null)
//			{
//
//				//修正返回值
//				if(Temp_TCB->Task_Queue.Pend.Return_State!=Null)
//				{
//					P_Return_State=(uint8_t*)Temp_TCB->Task_Queue.Pend.Return_State;
//
//					*P_Return_State=Event_Return_OK;
//
//					Temp_TCB->Task_Queue.Pend.Return_State=Null;
//				}
//				if(Temp_TCB->Task_Queue.Pend.Return_Event_Group_Event_Node!=Null)
//				{
//					Event_Node_Type **P_Event_Group_Event_Node;
//					P_Event_Group_Event_Node=Temp_TCB->Task_Queue.Pend.Return_Event_Group_Event_Node;
//
//
//					*P_Event_Group_Event_Node=P_Node;
//
//					Temp_TCB->Task_Queue.Pend.Return_Event_Group_Event_Node=Null;
//				}
//				//Test1();
//				//从当前队列中删除
//				Task_Queue_Del_TCB_At_Task_Pend_Suspended_TimeOut_Queue(Pend_Suspended_TimeOut,Temp_TCB);
//
//				//加入准备运行队列
//				Task_Queue_Add_TCB_To_Task_Ready_Queue(Ready,Temp_TCB,true);
//
//
//				//Test1();
//
//
//			}
//		}
//
//		Temp_Group_Node=Temp_Group_Node->NEXT;
//	}

	return Error_OK;
}
#endif
static void *Message_Queue_Void_Add(void* sou,uint32_t Index_Byte)
{
	uint8_t *P=(uint8_t*)sou;

	return (void *)&P[Index_Byte];
}
