/*
 * SysCall.Table.h
 *
 *  Created on: 2019年4月9日
 *      Author: Master.HE
 */

#ifndef SYSCALL_TABLE_H_
#define SYSCALL_TABLE_H_

//#include "Master.OS.Config.h"

typedef enum
{
	SysCall_Table_Index_Null			=0,

	SysCall_Table_Index_Apply_Handle,

	SysCall_Table_Index_BSP_System_Reset,

	SysCall_Table_Index_BSP_Wdog_Enable,

	SysCall_Table_Index_BSP_Wdog_Disable,

	SysCall_Table_Index_BSP_Wdog_Refresh,



	SysCall_Table_Memory_Size_Malloc,

	SysCall_Table_Memory_Size_Free,

	SysCall_Table_Memory_Malloc_Align,

	SysCall_Table_Memory_Malloc,

	SysCall_Table_Memory_Free,



	SysCall_Table_UGC_Memory_Init,

	SysCall_Table_UGC_Memory_Size_Malloc,

	SysCall_Table_UGC_Memory_Size_Free,

	SysCall_Table_UGC_Memory_Malloc,

	SysCall_Table_UGC_Memory_Free,



	SysCall_Table_Index_Device_Open,

	SysCall_Table_Index_Device_Close,

	SysCall_Table_Index_Device_Read,

	SysCall_Table_Index_Device_Write,

	SysCall_Table_Index_Device_Control,

	SysCall_Table_Index_Device_Info,



	SysCall_Table_Index_IRQ_Enable,

	SysCall_Table_Index_IRQ_Disable,

	SysCall_Table_Index_IRQ_Set_Priority,

	SysCall_Table_Index_IRQ_All_Enable,

	SysCall_Table_Index_IRQ_All_Disable,

	SysCall_Table_Index_IRQ_Register_Hook,

	SysCall_Table_Index_IRQ_Delete_Hook,



	SysCall_Table_Index_Scheduling_Create_Task,

	SysCall_Table_Index_Scheduling_Release_Task,

	SysCall_Table_Index_Scheduling_Sleep_Task,

	SysCall_Table_Index_Scheduling_Suspend_Task,

	SysCall_Table_Index_Scheduling_Resume_Task,



	SysCall_Table_Index_Event_Flag_Create,

	SysCall_Table_Index_Event_Flag_Delete,

	SysCall_Table_Index_Event_Flag_Find_Handle,

	SysCall_Table_Index_Event_Flag_Wait,

	SysCall_Table_Index_Event_Flag_Clear,

	SysCall_Table_Index_Event_Flag_Set,



	SysCall_Table_Index_Event_Flag_Group_Create,

	SysCall_Table_Index_Event_Flag_Group_Delete,

	SysCall_Table_Index_Event_Flag_Group_Find_Handle,

	SysCall_Table_Index_Event_Flag_Group_Open,

	SysCall_Table_Index_Event_Flag_Group_Close,


	SysCall_Table_Index_Event_Flag_Group_Wait_And,

	SysCall_Table_Index_Event_Flag_Group_Wait_Or,

	SysCall_Table_Index_Event_Flag_Group_Set,



	SysCall_Table_Index_FIFO_Queue_Create,

	SysCall_Table_Index_FIFO_Queue_Delete,

	SysCall_Table_Index_FIFO_Queue_Find_Handle,

	SysCall_Table_Index_FIFO_Queue_Open,

	SysCall_Table_Index_FIFO_Queue_Close,

	SysCall_Table_Index_FIFO_Queue_Wait,

	SysCall_Table_Index_FIFO_Queue_Clear,

	SysCall_Table_Index_FIFO_Queue_Set,



	SysCall_Table_Index_Message_Queue_Create,

	SysCall_Table_Index_Message_Queue_Delete,

	SysCall_Table_Index_Message_Queue_Find_Handle,

	SysCall_Table_Index_Message_Queue_Open,

	SysCall_Table_Index_Message_Queue_Close,

	SysCall_Table_Index_Message_Queue_Wait,

	SysCall_Table_Index_Message_Queue_Clear,

	SysCall_Table_Index_Message_Queue_Set,



	SysCall_Table_Index_Mutex_Create,

	SysCall_Table_Index_Mutex_Delete,

	SysCall_Table_Index_Mutex_Find_Handle,

	SysCall_Table_Index_Mutex_Wait,

	SysCall_Table_Index_Mutex_Release,



	SysCall_Table_Index_Semaphore_Create,

	SysCall_Table_Index_Semaphore_Delete,

	SysCall_Table_Index_Semaphore_Find_Handle,

	SysCall_Table_Index_Semaphore_Wait,

	SysCall_Table_Index_Semaphore_Release,



	SysCall_Table_Index_Semaphore_Group_Create,

	SysCall_Table_Index_Semaphore_Group_Delete,

	SysCall_Table_Index_Semaphore_Group_Find_Handle,

	SysCall_Table_Index_Semaphore_Group_Wait,

	SysCall_Table_Index_Semaphore_Group_Release,


	SysCall_Table_Index_Timer_GET_Counter,

	SysCall_Table_Index_Timer_Enable,

	SysCall_Table_Index_Timer_Disable,

	SysCall_Table_Index_Timer_Register,

	SysCall_Table_Index_Timer_Delete,

	SysCall_Table_Index_Timer_Start,

	SysCall_Table_Index_Timer_Stop,

	SysCall_Table_Index_Timer_Suspend,

	SysCall_Table_Index_Timer_Resume,

	SysCall_Table_Index_Timer_Reset,

	SysCall_Table_Index_Timer_Enabled,


	SysCall_Table_Index_End,
}SysCall_Table_Index_Type;

#endif /* SYSCALL_TABLE_H_ */
