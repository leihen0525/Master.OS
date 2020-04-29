/*
 * Scheduling.Task.Stack.h
 *
 *  Created on: 2019年4月23日
 *      Author: Master.HE
 */

#ifndef SCHEDULING_TASK_STACK_H_
#define SCHEDULING_TASK_STACK_H_

#include "Scheduling.Task.Define.h"

#include "Scheduling.Task.Stack.Struct.h"

int Scheduling_Task_Stack_Init(
		Task_Enter_Function Task_Enter,
		void *Args,
		Task_Exit_Function Task_Exit,
#ifdef __MPU__
		uint32_t **Sys_SP,
		uint32_t **Usr_SP,
#else
		uint32_t **SP,
#endif
		int Option);

#endif /* SCHEDULING_TASK_STACK_H_ */
