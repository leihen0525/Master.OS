/*
 * Event.Struct.h
 *
 *  Created on: 2019年4月29日
 *      Author: Master.HE
 */

#ifndef EVENT_STRUCT_H_
#define EVENT_STRUCT_H_

#include "Master.Stdint.h"

#include "Event/Event.Enum.h"
#include "__Event.Enum.h"
#include "Queue/Queue.Struct.h"

#include "Event.Flag/Event.Flag.Struct.h"
#include "Event.Flag.Group/Event.Flag.Group.Struct.h"
#include "FIFO.Queue/FIFO.Queue.Struct.h"
#include "Message.Queue/Message.Queue.Struct.h"
#include "Mutex/Mutex.Struct.h"
#include "Semaphore/Semaphore.Struct.h"
#include "Semaphore.Group/Semaphore.Group.Struct.h"

typedef union
{
	Event_Event_Flag_Node_Type Event_Flag;
	Event_Event_Flag_Group_Node_Type Event_Flag_Group;
	Event_FIFO_Queue_Node_Type FIFO_Queue;
	Event_Message_Queue_Node_Type Message_Queue;
	Event_Mutex_Node_Type Mutex;
	Event_Semaphore_Node_Type Semaphore;
	Event_Semaphore_Group_Node_Type Semaphore_Group;
}Event_DATA_Node_Type;


typedef struct Event_NODE
{
	int Handle;

	int8_t *Name;

	//等待队列
	Task_Queue_Type Pend_Task_Queue;

	struct Event_NODE *NEXT;

	Event_DATA_Node_Type *DATA_Node;

	Event_Pend_Type Event_Pend;

}Event_Node_Type;

typedef struct
{
	Event_Node_Type *Head;

	Event_Node_Type *End;

}Event_DATA_Type;

#endif /* EVENT_STRUCT_H_ */
