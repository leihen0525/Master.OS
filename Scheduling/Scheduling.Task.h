/*
 * Scheduling.Task.h
 *
 *  Created on: 2019Äê4ÔÂ23ÈÕ
 *      Author: Master.HE
 */

#ifndef SCHEDULING_TASK_H_
#define SCHEDULING_TASK_H_

#include "Master.Stdint.h"

#include "Scheduling.Task.Define.h"
#include "__Sys.Scheduling.Task.Struct.h"

int Scheduling_Task_Create(
		__Sys_Scheduling_Task_TCB_Type **P_Task_TCB,
		char *Name,
		Task_Enter_Function Task_Enter,
		void *Args,
		Task_Exit_Function Task_Exit,
		uint8_t Priority,
		uint32_t *Stack,
		uint32_t Stack_Size_4Byte,
		int Option
		);

int Scheduling_Task_Release(__Sys_Scheduling_Task_TCB_Type *P_Task_TCB);

int Scheduling_Task_Create_Idle(
		__Sys_Scheduling_Task_TCB_Type **P_Task_TCB,
		char *Name,
		uint8_t Priority);
int Scheduling_Task_Release_Idle(__Sys_Scheduling_Task_TCB_Type *P_Task_TCB);

//-----------------------------
int Scheduling_Task_Event_List_Init(__Sys_Scheduling_Task_TCB_Type *P_Task_TCB);
int Scheduling_Task_Event_List_Add_Node(
		__Sys_Scheduling_Task_TCB_Type *Task,
		int Handle,
		Task_Event_DATA_Type *DATA);
int Scheduling_Task_Event_List_Find_Node(
		__Sys_Scheduling_Task_TCB_Type *Task,
		int Handle,
		Task_Event_DATA_Type **DATA);
int Scheduling_Task_Event_List_Delete_Node(
		__Sys_Scheduling_Task_TCB_Type *Task,
		int Handle,
		Task_Event_DATA_Type **DATA);


#endif /* SCHEDULING_TASK_H_ */
