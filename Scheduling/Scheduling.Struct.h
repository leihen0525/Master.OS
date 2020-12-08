/*
 * Scheduling.Struct.h
 *
 *  Created on: 2019年4月23日
 *      Author: Master.HE
 */

#ifndef SCHEDULING_STRUCT_H_
#define SCHEDULING_STRUCT_H_

#include "Master.Stdint.h"

#include "__Sys.Scheduling.Task.Struct.h"

typedef struct
{
	uint16_t Count;
	uint16_t Count_Task_Idle;
	uint16_t CPU_Load;

	__Sys_Scheduling_Task_TCB_Type *Last_TCB;

	__Sys_Scheduling_Task_TCB_Type *Current_TCB;



}Scheduling_DATA_Type;



#endif /* SCHEDULING_STRUCT_H_ */
