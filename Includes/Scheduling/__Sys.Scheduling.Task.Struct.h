/*
 * __Sys.Scheduling.Task.Struct.h
 *
 *  Created on: 2019年4月23日
 *      Author: Master.HE
 */

#ifndef SYS_SCHEDULING_TASK_STRUCT_H_
#define SYS_SCHEDULING_TASK_STRUCT_H_

#include "Master.Stdint.h"

#include "Define.h"

typedef struct
{
	uint8_t DATA;
	uint8_t Wait_Type;
	uint8_t Wait_Mask;
	uint8_t Wait_BIT;

}Task_Event_DATA_Event_Flag_Group_Type;

typedef struct
{
	uint32_t Index_Out;
}Task_Event_DATA_Message_Queue_Type;

typedef struct
{
	bool Semaphore_Group_Flag;
}Task_Event_DATA_Semaphore_Group_Type;



typedef union
{
	Task_Event_DATA_Event_Flag_Group_Type Event_Flag_Group[Event_Flag_Group_Max_Len];
	Task_Event_DATA_Message_Queue_Type Message_Queue;
	Task_Event_DATA_Semaphore_Group_Type Semaphore_Group;
}Task_Event_DATA_Type;

typedef struct Task_Event_LIST
{

	int Handle;

	Task_Event_DATA_Type *DATA;

	struct Task_Event_LIST *NEXT;

}Task_Event_List_Type;

typedef struct
{
	uint32_t *SP;
	uint32_t *SP_Head;
	uint32_t *SP_End;
#ifdef __MPU__
	uint32_t Count;
	uint32_t Protection_Size;
#endif
}Scheduling_Task_TCB_Stack_Type;

typedef struct Scheduling_Task_TCB
{
#ifdef __UsrSP_SysSP__

	Scheduling_Task_TCB_Stack_Type Stack_User;
	Scheduling_Task_TCB_Stack_Type Stack_System;

#else
	Scheduling_Task_TCB_Stack_Type Stack;
#endif

	struct
	{
		char *Name;

		int Handle;

		uint8_t Task_State;


		int32_t TimeOut;
		int32_t Time_Slice;

		int Option;
	}Info;

	struct
	{
		void *Event_Queue;

		struct
		{
			Task_Event_List_Type *Head;
			Task_Event_List_Type *End;
		}List;
	}Event;

	struct//任务优先级
	{
		uint8_t Current;//当前
		uint8_t Default;//默认
	}Priority;

	struct
	{
		struct Scheduling_Task_TCB *Queue_NEXT;//Ready Suspended

		struct Scheduling_Task_TCB *TCB_NEXT;//TCB

		struct Scheduling_Task_TCB *Event_NEXT;//Event
	}Queue;

}__Sys_Scheduling_Task_TCB_Type;

#endif /* SYS_SCHEDULING_TASK_STRUCT_H_ */
