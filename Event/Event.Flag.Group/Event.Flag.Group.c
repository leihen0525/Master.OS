/*
 * Event.Flag.Group.c
 *
 *  Created on: 2019年4月30日
 *      Author: Master.HE
 */
#include <string.h>

#include "Master.Stdint.h"
#include "Define.h"
#include "Error.h"

#include "Event.Enum.h"
#include "Event/__Event.Enum.h"
#include "Event/Event.h"

#include "Event.Flag.Group.Struct.h"
#include "Event.Flag.Group.h"

#include "__Sys.API.h"

#include "Queue/Queue.h"

#include "Scheduling/Scheduling.h"

#include "Scheduling/Scheduling.Task.h"

int __Sys_Event_Flag_Group_Create(
		char *Name,
		uint32_t Flag_Group_LEN)
{
	if(Flag_Group_LEN>Event_Flag_Group_Max_Len || Flag_Group_LEN==0)
	{
		return Error_Invalid_Parameter;
	}

	int Handle;

	Event_DATA_Node_Type *Temp_DATA_Node=(Event_DATA_Node_Type *)__Sys_Memory_Malloc(sizeof(Event_Event_Flag_Group_Node_Type));

	if(Temp_DATA_Node==Null)
	{

		return Error_Allocation_Memory_Failed;
	}

	Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN=Flag_Group_LEN;



	if((Handle=Event_Node_Add_Node(Name,Event_Pend_Event_Flag_Group,Temp_DATA_Node))<Valid_Handle)
	{

		__Sys_Memory_Free(Temp_DATA_Node);
		return Handle;
	}
	return Handle;

}
int __Sys_Event_Flag_Group_Delete(int Handle)
{
	if(Handle<Valid_Handle)return Error_Invalid_Handle;

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;

	if((Err=Event_Node_Delete_Node(Handle,Event_Pend_Event_Flag_Group,&Temp_DATA_Node))!=Error_OK)
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
int __Sys_Event_Flag_Group_Find_Handle(char *Name)
{
	if(Name==Null)
	{
		return Error_Invalid_Parameter;
	}

	return Event_Node_Name_Find_Node(Name,Event_Pend_Event_Flag_Group);
}
int __Sys_Event_Flag_Group_Open(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;

	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag_Group,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
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

	Task_Event_DATA_Type *Temp_DATA=__Sys_Memory_Malloc(sizeof(Task_Event_DATA_Event_Flag_Group_Type)*Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN);
	if(Temp_DATA==Null)
	{
		return Error_Allocation_Memory_Failed;
	}
	memset(Temp_DATA,0,sizeof(Task_Event_DATA_Event_Flag_Group_Type)*Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN);

	if((Err=Scheduling_Task_Event_List_Add_Node(Temp_TCB,Handle,Temp_DATA))!=Error_OK)
	{
		__Sys_Memory_Free(Temp_DATA);
		return Err;
	}
	return Error_OK;

}
int __Sys_Event_Flag_Group_Close(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag_Group,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
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

static bool Event_Flag_Group_Operation_And(
		Task_Event_DATA_Event_Flag_Group_Type *Event_Flag_Group,

		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,

		uint32_t Flag_Group_LEN)
{
	if(Event_Flag_Group==Null || Event_Flag_Group_Mask==Null || Event_Flag_Group_BIT==Null || Flag_Group_LEN==0)
	{
		return false;
	}

	for(int i=0;i<Flag_Group_LEN;i++)
	{

		if((Event_Flag_Group[i].DATA&Event_Flag_Group_Mask[i])!=(Event_Flag_Group_BIT[i]&Event_Flag_Group_Mask[i]))
		{
			return false;
		}
	}

	return true;

}
static bool Event_Flag_Group_Operation_And_R(
		Task_Event_DATA_Event_Flag_Group_Type *Event_Flag_Group,
		uint32_t Flag_Group_LEN)
{
	if(Event_Flag_Group==Null || Flag_Group_LEN==0)
	{
		return false;
	}

	for(int i=0;i<Flag_Group_LEN;i++)
	{

		if((Event_Flag_Group[i].DATA&Event_Flag_Group[i].Wait_Mask)!=(Event_Flag_Group[i].Wait_BIT&Event_Flag_Group[i].Wait_Mask))
		{
			return false;
		}
	}

	return true;

}
static bool Event_Flag_Group_Operation_Or(
		Task_Event_DATA_Event_Flag_Group_Type *Event_Flag_Group,

		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,

		uint32_t Flag_Group_LEN)
{
	if(Event_Flag_Group==Null || Event_Flag_Group_Mask==Null || Event_Flag_Group_BIT==Null || Flag_Group_LEN==0)
	{
		return false;
	}

	for(int i=0;i<Flag_Group_LEN;i++)
	{
		if(((~(Event_Flag_Group[i].DATA^(Event_Flag_Group_BIT[i]&Event_Flag_Group_Mask[i])))&Event_Flag_Group_Mask[i])!=0)
		{
			return true;
		}
	}

	return false;

}
static bool Event_Flag_Group_Operation_Or_R(
		Task_Event_DATA_Event_Flag_Group_Type *Event_Flag_Group,
		uint32_t Flag_Group_LEN)
{
	if(Event_Flag_Group==Null || Flag_Group_LEN==0)
	{
		return false;
	}

	for(int i=0;i<Flag_Group_LEN;i++)
	{
		if(((~(Event_Flag_Group[i].DATA^(Event_Flag_Group[i].Wait_BIT&Event_Flag_Group[i].Wait_Mask)))&Event_Flag_Group[i].Wait_Mask)!=0)
		{
			return true;
		}
	}

	return false;

}
static bool Event_Flag_Group_Operation_Clear_BIT(
		Task_Event_DATA_Event_Flag_Group_Type *Event_Flag_Group,

		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_Clear_BIT,

		uint32_t Flag_Group_LEN)
{
	if(Event_Flag_Group==Null || Event_Flag_Group_Mask==Null || Event_Flag_Group_Clear_BIT==Null || Flag_Group_LEN==0)
	{
		return false;
	}

	for(int i=0;i<Flag_Group_LEN;i++)
	{

		Event_Flag_Group[i].DATA=(Event_Flag_Group[i].DATA&(~Event_Flag_Group_Mask[i]))|(Event_Flag_Group_Clear_BIT[i]&Event_Flag_Group_Mask[i]);
	}

	return true;

}
int __Sys_Event_Flag_Group_Wait_And(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t *Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	//
	if(Event_Flag_Group_Mask==Null
	|| Event_Flag_Group_BIT==Null
	|| Clear_Type>=Event_Flag_Group_Clear_End
	|| Event_Flag_Group_Clear_BIT==Null
	|| Time_Out_MS<Event_Time_Out_Query)
	{
		return Error_Invalid_Parameter;
	}


	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag_Group,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
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

	if(Event_Flag_Group_Operation_And(Temp_DATA->Event_Flag_Group,Event_Flag_Group_Mask,Event_Flag_Group_BIT,Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN)==true)
	{
		Err=Error_OK;
	}
	else
	{
		Err=Error_Dissatisfy;
	}

	if(Err==Error_Dissatisfy && Time_Out_MS>Event_Time_Out_Occupy_Return_Back)
	{

		Temp_DATA->Event_Flag_Group[0].Wait_Type=Event_Flag_Group_Wait_Type_And;

		for(int i=0;i<Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN;i++)
		{

			Temp_DATA->Event_Flag_Group[i].Wait_Mask=Event_Flag_Group_Mask[i];

			Temp_DATA->Event_Flag_Group[i].Wait_BIT=Event_Flag_Group_BIT[i];


		}

		//被占用 挂起当前任务

		if((Err=Queue_TCB_Add_Event_Node_Queue(Temp_Pend_Task_Queue,Temp_TCB,Event_Queue_Option_FIFO))!=Error_OK)
		{
			return Err;
		}

		int32_t RTimeOut=0;
		if((Err=__Sys_Scheduling_Context_Switch(Task_State_Pend_Event_Flag_Group,Time_Out_MS,&RTimeOut))!=Error_OK)
		{
			return Err;
		}

		if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag_Group,Null,Null)!=Error_OK))
		{
			return Err;
		}

		if(RTimeOut==0)
		{
			Err=Error_Time_Out;
		}
		if(Event_Flag_Group_Operation_And(Temp_DATA->Event_Flag_Group,Event_Flag_Group_Mask,Event_Flag_Group_BIT,Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN)==true)
		{
			Err=Error_OK;
		}
		else
		{
			Err=Error_Dissatisfy;//????
		}
	}
	//清除
	if(Clear_Type==Event_Flag_Group_Clear_Any_Read_Clear
	||(Err==Error_OK && Clear_Type==Event_Flag_Group_Clear_Any_Read_Result_OK_Clear_Dissatisfy_Retain)
	||(Err==Error_Dissatisfy && Clear_Type==Event_Flag_Group_Clear_Any_Read_Result_OK_Retain_Dissatisfy_Clear)
	||(Err==Error_Time_Out))
	{

		Event_Flag_Group_Operation_Clear_BIT(Temp_DATA->Event_Flag_Group,Event_Flag_Group_Mask,Event_Flag_Group_Clear_BIT,Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN);
	}

	if(Read_Event_Flag_Group!=Null)
	{
		for(int i=0;i<Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN;i++)
		{
			Read_Event_Flag_Group[i]=Temp_DATA->Event_Flag_Group[i].DATA&Event_Flag_Group_Mask[i];
		}
	}

	return Err;


}
int __Sys_Event_Flag_Group_Wait_Or(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t *Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	//
	if(Event_Flag_Group_Mask==Null
	|| Event_Flag_Group_BIT==Null
	|| Clear_Type>=Event_Flag_Group_Clear_End
	|| Event_Flag_Group_Clear_BIT==Null
	|| Time_Out_MS<Event_Time_Out_Query)
	{
		return Error_Invalid_Parameter;
	}


	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag_Group,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
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

	if(Event_Flag_Group_Operation_Or(Temp_DATA->Event_Flag_Group,Event_Flag_Group_Mask,Event_Flag_Group_BIT,Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN)==true)
	{
		Err=Error_OK;
	}
	else
	{
		Err=Error_Dissatisfy;
	}

	if(Err==Error_Dissatisfy && Time_Out_MS>Event_Time_Out_Occupy_Return_Back)
	{

		Temp_DATA->Event_Flag_Group[0].Wait_Type=Event_Flag_Group_Wait_Type_And;

		for(int i=0;i<Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN;i++)
		{

			Temp_DATA->Event_Flag_Group[i].Wait_Mask=Event_Flag_Group_Mask[i];

			Temp_DATA->Event_Flag_Group[i].Wait_BIT=Event_Flag_Group_BIT[i];


		}

		//被占用 挂起当前任务

		if((Err=Queue_TCB_Add_Event_Node_Queue(Temp_Pend_Task_Queue,Temp_TCB,Event_Queue_Option_FIFO))!=Error_OK)
		{
			return Err;
		}

		int32_t RTimeOut=0;
		if((Err=__Sys_Scheduling_Context_Switch(Task_State_Pend_Event_Flag_Group,Time_Out_MS,&RTimeOut))!=Error_OK)
		{
			return Err;
		}

		if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag_Group,Null,Null)!=Error_OK))
		{
			return Err;
		}

		if(RTimeOut==0)
		{
			Err=Error_Time_Out;
		}
		if(Event_Flag_Group_Operation_Or(Temp_DATA->Event_Flag_Group,Event_Flag_Group_Mask,Event_Flag_Group_BIT,Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN)==true)
		{
			Err=Error_OK;
		}
		else
		{
			Err=Error_Dissatisfy;//????
		}
	}
	//清除
	if(Clear_Type==Event_Flag_Group_Clear_Any_Read_Clear
	||(Err==Error_OK && Clear_Type==Event_Flag_Group_Clear_Any_Read_Result_OK_Clear_Dissatisfy_Retain)
	||(Err==Error_Dissatisfy && Clear_Type==Event_Flag_Group_Clear_Any_Read_Result_OK_Retain_Dissatisfy_Clear)
	||(Err==Error_Time_Out))
	{

		Event_Flag_Group_Operation_Clear_BIT(Temp_DATA->Event_Flag_Group,Event_Flag_Group_Mask,Event_Flag_Group_Clear_BIT,Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN);
	}

	if(Read_Event_Flag_Group!=Null)
	{
		for(int i=0;i<Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN;i++)
		{
			Read_Event_Flag_Group[i]=Temp_DATA->Event_Flag_Group[i].DATA&Event_Flag_Group_Mask[i];
		}
	}

	return Err;
}

int __Sys_Event_Flag_Group_Set(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Event_Flag_Group_Mask==Null || Event_Flag_Group_BIT==0)
	{
		return Error_Invalid_Parameter;
	}

	int Err;
	Event_DATA_Node_Type *Temp_DATA_Node=Null;
	Task_Queue_Type *Temp_Pend_Task_Queue=Null;
	if((Err=Event_Node_Handle_Find_Node(Handle,Event_Pend_Event_Flag_Group,&Temp_DATA_Node,&Temp_Pend_Task_Queue)!=Error_OK))
	{
		return Err;
	}

	if(Temp_DATA_Node==Null)
	{
		return Error_Unknown;
	}

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
			for(int i=0;i<Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN;i++)
			{
				Temp_DATA->Event_Flag_Group[i].DATA=(Temp_DATA->Event_Flag_Group[i].DATA&(~Event_Flag_Group_Mask[i]))|(Event_Flag_Group_BIT[i]&Event_Flag_Group_Mask[i]);

			}
		}

		Temp_TCB=Temp_TCB->Queue.TCB_NEXT;
	}


	//将符合条件的等待的任务 放入准备运行队列
	Temp_TCB=Temp_Pend_Task_Queue->Begin;
	__Sys_Scheduling_Task_TCB_Type *Temp_TCB_NEXT=Null,*Temp_TCB_LAST=Null;

	bool Try_Context_Switch=false;
	while(Temp_TCB!=Null)
	{
		Temp_TCB_NEXT=Temp_TCB->Queue.Event_NEXT;

		if(Scheduling_Task_Event_List_Find_Node(Temp_TCB,Handle,&Temp_DATA)==Error_OK)
		{
			if(Temp_DATA==Null)
			{
				return Error_Unknown;
			}
			if(Temp_DATA->Event_Flag_Group[0].Wait_Type==Event_Flag_Group_Wait_Type_And)
			{
				if(Event_Flag_Group_Operation_And_R(Temp_DATA->Event_Flag_Group,Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN)==true)
				{
					Err=Error_OK;
				}
				else
				{
					Err=Error_Dissatisfy;
				}
			}
			else if(Temp_DATA->Event_Flag_Group[0].Wait_Type==Event_Flag_Group_Wait_Type_Or)
			{
				if(Event_Flag_Group_Operation_Or_R(Temp_DATA->Event_Flag_Group,Temp_DATA_Node->Event_Flag_Group.Flag_Group_LEN)==true)
				{
					Err=Error_OK;
				}
				else
				{
					Err=Error_Dissatisfy;
				}
			}

			if(Err==Error_OK)
			{
				Queue_TCB_Delete_Suspended_Queue(Temp_TCB);
				Queue_TCB_Add_Ready_Queue(Temp_TCB);

				Try_Context_Switch=true;

				Temp_TCB->Event.Event_Queue=Null;

				if(Temp_TCB_LAST==Null || Temp_TCB==Temp_Pend_Task_Queue->Begin)
				{
					Temp_Pend_Task_Queue->Begin=Temp_TCB->Queue.Event_NEXT;
					//Temp_TCB_NEXT=Temp_Pend_Task_Queue->Begin;
					Temp_TCB=Null;
					Temp_TCB_LAST=Null;
				}
				if(Temp_TCB_LAST!=Null || Temp_TCB_NEXT!=Null)
				{
					Temp_TCB_LAST->Queue.Event_NEXT=Temp_TCB_NEXT;

					//Temp_TCB_NEXT=Temp_TCB->Queue.Event_NEXT;

					Temp_TCB=Temp_TCB_LAST;
				}
				if(Temp_TCB_NEXT==Null || Temp_TCB==Temp_Pend_Task_Queue->End)
				{
					Temp_Pend_Task_Queue->End=Null;

					Temp_TCB_NEXT=Null;

				}
			}
			else
			{

			}
		}
		else
		{
			return Error_Unknown;
		}
		Temp_TCB_LAST=Temp_TCB;

		Temp_TCB=Temp_TCB_NEXT;
	}

	if(Try_Context_Switch==true)
	{
		__Sys_Scheduling_Try_Context_Switch();
	}

	return Error_OK;
}




