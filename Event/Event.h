/*
 * Event.h
 *
 *  Created on: 2019Äê4ÔÂ29ÈÕ
 *      Author: Master.HE
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "Master.Stdint.h"
#include "Event.Enum.h"
#include "__Event.Enum.h"
#include "Event.Struct.h"

int Event_Init(void);

int Event_Node_Add_Node(
		char *Name,
		Event_Pend_Type Pend_Type,
		Event_DATA_Node_Type *DATA_Node);

int Event_Node_Delete_Node(
		int Handle,
		Event_Pend_Type Pend_Type,
		Event_DATA_Node_Type **DATA_Node);

//int Event_Node_Task_Queue_Delete_Task_TCB(__Sys_Scheduling_Task_TCB_Type *Delete_Task_TCB);

int Event_Node_Name_Find_Node(
		char *Name,
		Event_Pend_Type Pend_Type);

int Event_Node_Handle_Find_Node(
		int Handle,
		Event_Pend_Type Pend_Type,
		Event_DATA_Node_Type **DATA_Node,
		Task_Queue_Type **Pend_Task_Queue);

int Event_Node_Delete_Task_Event_DATA(int Handle);

#endif /* EVENT_H_ */
