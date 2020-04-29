/*
 * Scheduling.Task.Enum.h
 *
 *  Created on: 2019年4月23日
 *      Author: Master.HE
 */

#ifndef SCHEDULING_TASK_ENUM_H_
#define SCHEDULING_TASK_ENUM_H_

typedef enum
{
	Task_State_Runing							=0,	//运行

	Task_State_Ready,								//准备

	Task_State_Pend_Event_Flag,

	Task_State_Pend_Event_Flag_Group,				//阻塞

	Task_State_Pend_FIFO_Queue,

	Task_State_Pend_Message_Mailboxes,

	Task_State_Pend_Message_Queue,

	Task_State_Pend_Mutex,

	Task_State_Pend_Semaphore,

	Task_State_Pend_Semaphore_Group,

	Task_State_Suspended,							//挂起

	Task_State_Event_Group,							//事件组

	//Task_State_Delete,								//删除

	Task_State_End,

}Task_State_Type;

#endif /* SCHEDULING_TASK_ENUM_H_ */
