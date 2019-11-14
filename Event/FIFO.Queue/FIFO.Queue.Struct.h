/*
 * FIFO.Queue.Struct.h
 *
 *  Created on: 2019年5月5日
 *      Author: Master.HE
 */

#ifndef FIFO_QUEUE_STRUCT_H_
#define FIFO_QUEUE_STRUCT_H_

#include "Master.Stdint.h"
#include "__Sys.Scheduling.Task.Struct.h"
//#include "Queue.Struct.h"
#include "Event.Define.h"


typedef struct
{
	void *FIFO_DATA;
	uint32_t *FIFO_Size;

	uint32_t Index_In;
	uint32_t Index_Out;

	uint32_t Max_FIFO_Size;
	uint32_t Max_FIFO_Queue_Length;

	__Sys_Scheduling_Task_TCB_Type *Possess_TCB;

	//等待队列
	//Task_Queue_Type Pend_Task_Queue;

	__Sys_Event_FIFO_OverFlow_Function OverFlow_Fun;
	void *OverFlow_Args;

}Event_FIFO_Queue_Node_Type;

#endif /* FIFO_QUEUE_STRUCT_H_ */
