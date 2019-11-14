/*
 * __Sys.Scheduling.Task.Struct.h
 *
 *  Created on: 2019��4��23��
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


typedef struct Scheduling_Task_TCB
{

	struct
	{
		uint32_t *SP;
		uint32_t *SP_Head;
		uint32_t *SP_End;
	}Stack;


	struct
	{
		char *Name;

		int Handle;

		uint8_t Task_State;


		int32_t TimeOut;
		int32_t Time_Slice;

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

	struct//�������ȼ�
	{
		uint8_t Current;//��ǰ
		uint8_t Default;//Ĭ��
	}Priority;

	struct
	{
		struct Scheduling_Task_TCB *Queue_NEXT;//Ready Suspended

		struct Scheduling_Task_TCB *TCB_NEXT;//TCB

		struct Scheduling_Task_TCB *Event_NEXT;//Event
	}Queue;

}__Sys_Scheduling_Task_TCB_Type;

#endif /* SYS_SCHEDULING_TASK_STRUCT_H_ */