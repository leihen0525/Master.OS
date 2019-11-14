/*
 * Scheduling.Task.Stack.h
 *
 *  Created on: 2019Äê4ÔÂ23ÈÕ
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
		uint32_t **SP,
		int Option);

#endif /* SCHEDULING_TASK_STACK_H_ */
