/*
 * Queue.h
 *
 *  Created on: 2019年4月23日
 *      Author: Master.HE
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "Scheduling.Task.Enum.h"
#include "Queue.Struct.h"

#include "Event.Enum.h"

int Queue_Init(void);

int Queue_Read_TCB_Queue(Task_Queue_Type **TCB_Queue);

int Queue_TCB_Add_TCB_Queue(__Sys_Scheduling_Task_TCB_Type *Add_TCB);

int Queue_TCB_Delete_TCB_Queue(
		__Sys_Scheduling_Task_TCB_Type **Delete_TCB,
		int Handle);

int Queue_Find_TCB_Queue(
		__Sys_Scheduling_Task_TCB_Type **Find_TCB,
		int Handle);

int Queue_TCB_Add_Ready_Queue(__Sys_Scheduling_Task_TCB_Type *Add_TCB);

int Queue_TCB_Add_Suspended_Queue(
		__Sys_Scheduling_Task_TCB_Type *Add_TCB,
		Task_State_Type Add_TCB_Task_State,
		int32_t TimeOut);

int Queue_TCB_Delete_Suspended_Queue(__Sys_Scheduling_Task_TCB_Type *Delete_TCB);

int Queue_TimeOut_1MS_AT_Suspended_Queue(__Sys_Scheduling_Task_TCB_Type **TimeOut_TCB,bool Sub);

int Queue_Read_Ready_Queue_First_TCB(__Sys_Scheduling_Task_TCB_Type **First_Ready_TCB);

int Queue_Delete_Ready_Queue_First_TCB(__Sys_Scheduling_Task_TCB_Type **Delet_First_Ready_TCB);

//-------------------------------------------------------
int Queue_Event_Node_Init(Task_Queue_Type *Event_Node_Queue);
int Queue_TCB_Add_Event_Node_Queue(
		Task_Queue_Type *Event_Node_Queue,
		__Sys_Scheduling_Task_TCB_Type *Add_TCB,
		Event_Queue_Option_Type Queue_Option);
int Queue_Read_Event_Node_Queue_First_TCB(
		Task_Queue_Type *Event_Node_Queue,
		__Sys_Scheduling_Task_TCB_Type **First_Event_TCB);
int Queue_TCB_Delete_Event_Node_Queue_First_TCB(
		Task_Queue_Type *Event_Node_Queue,
		__Sys_Scheduling_Task_TCB_Type **Delet_First_TCB);
int Queue_TCB_Delete_Event_Node_Queue(
		Task_Queue_Type *Event_Node_Queue,
		__Sys_Scheduling_Task_TCB_Type *Delet_TCB);


#endif /* QUEUE_H_ */
