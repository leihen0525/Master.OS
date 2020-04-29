/*
 * __Event.Enum.h
 *
 *  Created on: 2019年5月6日
 *      Author: Master.HE
 */

#ifndef __EVENT_ENUM_H_
#define __EVENT_ENUM_H_

typedef enum
{

	Event_Pend_Event_Flag=0,

	Event_Pend_Event_Flag_Group,				//阻塞

	Event_Pend_FIFO_Queue,

	Event_Pend_Message_Mailboxes,

	Event_Pend_Message_Queue,

	Event_Pend_Mutex,

	Event_Pend_Semaphore,

	Event_Pend_Semaphore_Group,

	Event_Pend_End,
}Event_Pend_Type;

typedef enum
{
	Event_Flag_Group_Wait_Type_And=0,
	Event_Flag_Group_Wait_Type_Or,

	Event_Flag_Group_Wait_Type_End,

}Event_Flag_Group_Wait_Type;

#endif /* __EVENT_ENUM_H_ */
