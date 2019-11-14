/*
 * Sys_Call_Table.s
 *
 *  Created on: 2019Äê4ÔÂ9ÈÕ
 *      Author: Master.HE
 */


	MODULE Sys_Call_Table

	SECTION .text:CODE(2)

	EXTERN __Sys_Memory_Size
	EXTERN __Sys_Memory_Malloc
	EXTERN __Sys_Memory_Free


	EXTERN __Sys_Device_Open
	EXTERN __Sys_Device_Close
	EXTERN __Sys_Device_Read
	EXTERN __Sys_Device_Write
	EXTERN __Sys_Device_Control
	EXTERN __Sys_Device_Info


	EXTERN __Sys_IRQ_Enable
	EXTERN __Sys_IRQ_Disable
	EXTERN __Sys_IRQ_Set_Priority
	EXTERN __Sys_IRQ_All_Enable
	EXTERN __Sys_IRQ_All_Disable
	EXTERN __Sys_IRQ_Register_Hook
	EXTERN __Sys_IRQ_Delete_Hook

/*
	EXTERN __Sys_Power_GET_Core_Frequency
	EXTERN __Sys_Power_GET_Bus_Frequency
	EXTERN __Sys_Power_GET_Flash_Frequency
	EXTERN __Sys_Power_GET_External_Frequency
*/
	EXTERN __Sys_Scheduling_Create_Task
	EXTERN __Sys_Scheduling_Release_Task
	EXTERN __Sys_Scheduling_Sleep_Task
	EXTERN __Sys_Scheduling_Suspend_Task
	EXTERN __Sys_Scheduling_Resume_Task

	EXTERN __Sys_Event_Flag_Create
	EXTERN __Sys_Event_Flag_Delete
	EXTERN __Sys_Event_Flag_Find_Handle
	EXTERN __Sys_Event_Flag_Wait
	EXTERN __Sys_Event_Flag_Clear
	EXTERN __Sys_Event_Flag_Set


	EXTERN __Sys_Event_Flag_Group_Create
	EXTERN __Sys_Event_Flag_Group_Delete
	EXTERN __Sys_Event_Flag_Group_Find_Handle
	EXTERN __Sys_Event_Flag_Group_Open
	EXTERN __Sys_Event_Flag_Group_Close
	EXTERN __Sys_Event_Flag_Group_Wait_And
	EXTERN __Sys_Event_Flag_Group_Wait_Or
	EXTERN __Sys_Event_Flag_Group_Set

	EXTERN __Sys_FIFO_Queue_Create
	EXTERN __Sys_FIFO_Queue_Delete
	EXTERN __Sys_FIFO_Queue_Find_Handle
	EXTERN __Sys_FIFO_Queue_Open
	EXTERN __Sys_FIFO_Queue_Close
	EXTERN __Sys_FIFO_Queue_Wait
	EXTERN __Sys_FIFO_Queue_Clear
	EXTERN __Sys_FIFO_Queue_Set

	EXTERN __Sys_Message_Queue_Create
	EXTERN __Sys_Message_Queue_Delete
	EXTERN __Sys_Message_Queue_Find_Handle
	EXTERN __Sys_Message_Queue_Open
	EXTERN __Sys_Message_Queue_Close
	EXTERN __Sys_Message_Queue_Wait
	EXTERN __Sys_Message_Queue_Clear
	EXTERN __Sys_Message_Queue_Set

	EXTERN __Sys_Mutex_Create
	EXTERN __Sys_Mutex_Delete
	EXTERN __Sys_Mutex_Find_Handle
	EXTERN __Sys_Mutex_Wait
	EXTERN __Sys_Mutex_Release

	EXTERN __Sys_Semaphore_Create
	EXTERN __Sys_Semaphore_Delete
	EXTERN __Sys_Semaphore_Find_Handle
	EXTERN __Sys_Semaphore_Wait
	EXTERN __Sys_Semaphore_Release

	EXTERN __Sys_Semaphore_Group_Create
	EXTERN __Sys_Semaphore_Group_Delete
	EXTERN __Sys_Semaphore_Group_Find_Handle
	EXTERN __Sys_Semaphore_Group_Wait
	EXTERN __Sys_Semaphore_Group_Release

	EXTERN __Sys_Timer_Enable
	EXTERN __Sys_Timer_Disable
	EXTERN __Sys_Timer_Register
	EXTERN __Sys_Timer_Delete
	EXTERN __Sys_Timer_Start
	EXTERN __Sys_Timer_Stop
	EXTERN __Sys_Timer_Suspend
	EXTERN __Sys_Timer_Resume
	EXTERN __Sys_Timer_Reset
	EXTERN __Sys_Timer_Enabled

	PUBLIC __SysCall_Table

	DATA

__SysCall_Table
	DCD 0

	DCD __Sys_Memory_Size
	DCD __Sys_Memory_Malloc
	DCD __Sys_Memory_Free

	DCD __Sys_Device_Open
	DCD __Sys_Device_Close
	DCD __Sys_Device_Read
	DCD __Sys_Device_Write
	DCD __Sys_Device_Control
	DCD __Sys_Device_Info

	DCD __Sys_IRQ_Enable
	DCD __Sys_IRQ_Disable
	DCD __Sys_IRQ_Set_Priority
	DCD __Sys_IRQ_All_Enable
	DCD __Sys_IRQ_All_Disable
	DCD __Sys_IRQ_Register_Hook
	DCD __Sys_IRQ_Delete_Hook
/*
	DCD __Sys_Power_GET_Core_Frequency
	DCD __Sys_Power_GET_Bus_Frequency
	DCD __Sys_Power_GET_Flash_Frequency
	DCD __Sys_Power_GET_External_Frequency
*/
	DCD __Sys_Scheduling_Create_Task
	DCD __Sys_Scheduling_Release_Task
	DCD __Sys_Scheduling_Sleep_Task
	DCD __Sys_Scheduling_Suspend_Task
	DCD __Sys_Scheduling_Resume_Task

	DCD __Sys_Event_Flag_Create
	DCD __Sys_Event_Flag_Delete
	DCD __Sys_Event_Flag_Find_Handle
	DCD __Sys_Event_Flag_Wait
	DCD __Sys_Event_Flag_Clear
	DCD __Sys_Event_Flag_Set

	DCD __Sys_Event_Flag_Group_Create
	DCD __Sys_Event_Flag_Group_Delete
	DCD __Sys_Event_Flag_Group_Find_Handle
	DCD __Sys_Event_Flag_Group_Open
	DCD __Sys_Event_Flag_Group_Close
	DCD __Sys_Event_Flag_Group_Wait_And
	DCD __Sys_Event_Flag_Group_Wait_Or
	DCD __Sys_Event_Flag_Group_Set

	DCD __Sys_FIFO_Queue_Create
	DCD __Sys_FIFO_Queue_Delete
	DCD __Sys_FIFO_Queue_Find_Handle
	DCD __Sys_FIFO_Queue_Open
	DCD __Sys_FIFO_Queue_Close
	DCD __Sys_FIFO_Queue_Wait
	DCD __Sys_FIFO_Queue_Clear
	DCD __Sys_FIFO_Queue_Set

	DCD __Sys_Message_Queue_Create
	DCD __Sys_Message_Queue_Delete
	DCD __Sys_Message_Queue_Find_Handle
	DCD __Sys_Message_Queue_Open
	DCD __Sys_Message_Queue_Close
	DCD __Sys_Message_Queue_Wait
	DCD __Sys_Message_Queue_Clear
	DCD __Sys_Message_Queue_Set

	DCD __Sys_Mutex_Create
	DCD __Sys_Mutex_Delete
	DCD __Sys_Mutex_Find_Handle
	DCD __Sys_Mutex_Wait
	DCD __Sys_Mutex_Release

	DCD __Sys_Semaphore_Create
	DCD __Sys_Semaphore_Delete
	DCD __Sys_Semaphore_Find_Handle
	DCD __Sys_Semaphore_Wait
	DCD __Sys_Semaphore_Release

	DCD __Sys_Semaphore_Group_Create
	DCD __Sys_Semaphore_Group_Delete
	DCD __Sys_Semaphore_Group_Find_Handle
	DCD __Sys_Semaphore_Group_Wait
	DCD __Sys_Semaphore_Group_Release

	DCD __Sys_Timer_Enable
	DCD __Sys_Timer_Disable
	DCD __Sys_Timer_Register
	DCD __Sys_Timer_Delete
	DCD __Sys_Timer_Start
	DCD __Sys_Timer_Stop
	DCD __Sys_Timer_Suspend
	DCD __Sys_Timer_Resume
	DCD __Sys_Timer_Reset
	DCD __Sys_Timer_Enabled

	END
