/*
 * Queue.Struct.h
 *
 *  Created on: 2019年4月23日
 *      Author: Master.HE
 */

#ifndef QUEUE_STRUCT_H_
#define QUEUE_STRUCT_H_

#include "Scheduling/__Sys.Scheduling.Task.Struct.h"

typedef struct
{
	__Sys_Scheduling_Task_TCB_Type *Begin;
	__Sys_Scheduling_Task_TCB_Type *End;

}Task_Queue_Type;


typedef struct
{
	Task_Queue_Type TCB_Queue;

	Task_Queue_Type Ready_Queue;

	Task_Queue_Type Suspended_Queue;

}Queue_DATA_Type;

#endif /* QUEUE_STRUCT_H_ */
