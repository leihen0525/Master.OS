/*
 * Mutex.Struct.h
 *
 *  Created on: 2019年4月30日
 *      Author: Master.HE
 */

#ifndef MUTEX_STRUCT_H_
#define MUTEX_STRUCT_H_

#include "Master.Stdint.h"
#include "__Sys.Scheduling.Task.Struct.h"

#include "Event.Enum.h"

typedef struct
{

	Event_Queue_Option_Type Option;
	__Sys_Scheduling_Task_TCB_Type *Possess_TCB;

}Event_Mutex_Node_Type;

#endif /* MUTEX_STRUCT_H_ */
