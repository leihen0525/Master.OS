/*
 * Sys_Call_Table.s
 *
 *  Created on: 2019年4月9日
 *      Author: Master.HE
 */
#include "Master.OS.Config.h"

	MODULE Sys_Call_Table

	SECTION .text:CODE:NOROOT(2)

#ifdef Master_OS_Config_Memory_Size_Malloc
	EXTERN __Usr_Memory_Size_Malloc
#endif
#ifdef Master_OS_Config_Memory_Size_Free
	EXTERN __Usr_Memory_Size_Free
#endif
#ifdef Master_OS_Config_Memory_Malloc_Align
	EXTERN __Usr_Memory_Malloc_Align
#endif
#ifdef Master_OS_Config_Memory_Malloc
	EXTERN __Usr_Memory_Malloc
#endif
#ifdef Master_OS_Config_Memory_Free
	EXTERN __Usr_Memory_Free
#endif

#ifdef Master_OS_Config_UGC_Memory_Init
	EXTERN __Memory_Init
#endif
#ifdef Master_OS_Config_UGC_Memory_Size_Malloc
	EXTERN __Memory_Size_Malloc
#endif
#ifdef Master_OS_Config_UGC_Memory_Size_Free
	EXTERN __Memory_Size_Free
#endif
#ifdef Master_OS_Config_UGC_Memory_Malloc
	EXTERN __Memory_Malloc
#endif
#ifdef Master_OS_Config_UGC_Memory_Free
	EXTERN __Memory_Free
#endif

#ifdef Master_OS_Config_Device_Open
	EXTERN __Sys_Device_Open
#endif
#ifdef Master_OS_Config_Device_Close
	EXTERN __Sys_Device_Close
#endif
#ifdef Master_OS_Config_Device_Read
	EXTERN __Sys_Device_Read
#endif
#ifdef Master_OS_Config_Device_Write
	EXTERN __Sys_Device_Write
#endif
#ifdef Master_OS_Config_Device_Control
	EXTERN __Sys_Device_Control
#endif
#ifdef Master_OS_Config_Device_Info
	EXTERN __Sys_Device_Info
#endif

#ifdef Master_OS_Config_IRQ_Enable
	EXTERN __Sys_IRQ_Enable
#endif
#ifdef Master_OS_Config_IRQ_Disable
	EXTERN __Sys_IRQ_Disable
#endif
#ifdef Master_OS_Config_IRQ_Set_Priority
	EXTERN __Sys_IRQ_Set_Priority
#endif
#ifdef Master_OS_Config_IRQ_All_Enable
	EXTERN __Sys_IRQ_All_Enable
#endif
#ifdef Master_OS_Config_IRQ_All_Disable
	EXTERN __Sys_IRQ_All_Disable
#endif
#ifdef Master_OS_Config_IRQ_Register_Hook
	EXTERN __Sys_IRQ_Register_Hook
#endif
#ifdef Master_OS_Config_IRQ_Delete_Hook
	EXTERN __Sys_IRQ_Delete_Hook
#endif

/*
	EXTERN __Sys_Power_GET_Core_Frequency
	EXTERN __Sys_Power_GET_Bus_Frequency
	EXTERN __Sys_Power_GET_Flash_Frequency
	EXTERN __Sys_Power_GET_External_Frequency
*/
#ifdef Master_OS_Config_Scheduling_Create_Task
	EXTERN __Sys_Scheduling_Create_Task
#endif
#ifdef Master_OS_Config_Scheduling_Release_Task
	EXTERN __Sys_Scheduling_Release_Task
#endif
#ifdef Master_OS_Config_Scheduling_Sleep_Task
	EXTERN __Sys_Scheduling_Sleep_Task
#endif
#ifdef Master_OS_Config_Scheduling_Suspend_Task
	EXTERN __Sys_Scheduling_Suspend_Task
#endif
#ifdef Master_OS_Config_Scheduling_Resume_Task
	EXTERN __Sys_Scheduling_Resume_Task
#endif

#ifdef Master_OS_Config_Event_Flag_Create
	EXTERN __Sys_Event_Flag_Create
#endif
#ifdef Master_OS_Config_Event_Flag_Delete
	EXTERN __Sys_Event_Flag_Delete
#endif
#ifdef Master_OS_Config_Event_Flag_Find_Handle
	EXTERN __Sys_Event_Flag_Find_Handle
#endif
#ifdef Master_OS_Config_Event_Flag_Wait
	EXTERN __Sys_Event_Flag_Wait
#endif
#ifdef Master_OS_Config_Event_Flag_Clear
	EXTERN __Sys_Event_Flag_Clear
#endif
#ifdef Master_OS_Config_Event_Flag_Set
	EXTERN __Sys_Event_Flag_Set
#endif

#if (defined(Master_OS_Config_Event_Flag_Group_Create) || defined(Master_OS_Config_Event_Flag_Group_Create_8bit) || defined(Master_OS_Config_Event_Flag_Group_Create_16bit) || defined(Master_OS_Config_Event_Flag_Group_Create_32bit))
	EXTERN __Sys_Event_Flag_Group_Create
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Delete
	EXTERN __Sys_Event_Flag_Group_Delete
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Find_Handle
	EXTERN __Sys_Event_Flag_Group_Find_Handle
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Open
	EXTERN __Sys_Event_Flag_Group_Open
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Close
	EXTERN __Sys_Event_Flag_Group_Close
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Wait_And) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_8bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_16bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_32bit))
	EXTERN __Sys_Event_Flag_Group_Wait_And
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Wait_Or) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_8bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_16bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_32bit))
	EXTERN __Sys_Event_Flag_Group_Wait_Or
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Set) || defined(Master_OS_Config_Event_Flag_Group_Set_8bit) || defined(Master_OS_Config_Event_Flag_Group_Set_16bit) || defined(Master_OS_Config_Event_Flag_Group_Set_32bit))
	EXTERN __Sys_Event_Flag_Group_Set
#endif

#ifdef Master_OS_Config_FIFO_Queue_Create
	EXTERN __Sys_FIFO_Queue_Create
#endif
#ifdef Master_OS_Config_FIFO_Queue_Delete
	EXTERN __Sys_FIFO_Queue_Delete
#endif
#ifdef Master_OS_Config_FIFO_Queue_Find_Handle
	EXTERN __Sys_FIFO_Queue_Find_Handle
#endif
#ifdef Master_OS_Config_FIFO_Queue_Open
	EXTERN __Sys_FIFO_Queue_Open
#endif
#ifdef Master_OS_Config_FIFO_Queue_Close
	EXTERN __Sys_FIFO_Queue_Close
#endif
#ifdef Master_OS_Config_FIFO_Queue_Wait
	EXTERN __Sys_FIFO_Queue_Wait
#endif
#ifdef Master_OS_Config_FIFO_Queue_Clear
	EXTERN __Sys_FIFO_Queue_Clear
#endif
#ifdef Master_OS_Config_FIFO_Queue_Set
	EXTERN __Sys_FIFO_Queue_Set
#endif

#ifdef Master_OS_Config_Message_Queue_Create
	EXTERN __Sys_Message_Queue_Create
#endif
#ifdef Master_OS_Config_Message_Queue_Delete
	EXTERN __Sys_Message_Queue_Delete
#endif
#ifdef Master_OS_Config_Message_Queue_Find_Handle
	EXTERN __Sys_Message_Queue_Find_Handle
#endif
#ifdef Master_OS_Config_Message_Queue_Open
	EXTERN __Sys_Message_Queue_Open
#endif
#ifdef Master_OS_Config_Message_Queue_Close
	EXTERN __Sys_Message_Queue_Close
#endif
#ifdef Master_OS_Config_Message_Queue_Wait
	EXTERN __Sys_Message_Queue_Wait
#endif
#ifdef Master_OS_Config_Message_Queue_Clear
	EXTERN __Sys_Message_Queue_Clear
#endif
#ifdef Master_OS_Config_Message_Queue_Set
	EXTERN __Sys_Message_Queue_Set
#endif

#ifdef Master_OS_Config_Mutex_Create
	EXTERN __Sys_Mutex_Create
#endif
#ifdef Master_OS_Config_Mutex_Delete
	EXTERN __Sys_Mutex_Delete
#endif
#ifdef Master_OS_Config_Mutex_Find_Handle
	EXTERN __Sys_Mutex_Find_Handle
#endif
#ifdef Master_OS_Config_Mutex_Wait
	EXTERN __Sys_Mutex_Wait
#endif
#ifdef Master_OS_Config_Mutex_Release
	EXTERN __Sys_Mutex_Release
#endif

#ifdef Master_OS_Config_Semaphore_Create
	EXTERN __Sys_Semaphore_Create
#endif
#ifdef Master_OS_Config_Semaphore_Delete
	EXTERN __Sys_Semaphore_Delete
#endif
#ifdef Master_OS_Config_Semaphore_Find_Handle
	EXTERN __Sys_Semaphore_Find_Handle
#endif
#ifdef Master_OS_Config_Semaphore_Wait
	EXTERN __Sys_Semaphore_Wait
#endif
#ifdef Master_OS_Config_Semaphore_Release
	EXTERN __Sys_Semaphore_Release
#endif

#ifdef Master_OS_Config_Semaphore_Group_Create
	EXTERN __Sys_Semaphore_Group_Create
#endif
#ifdef Master_OS_Config_Semaphore_Group_Delete
	EXTERN __Sys_Semaphore_Group_Delete
#endif
#ifdef Master_OS_Config_Semaphore_Group_Find_Handle
	EXTERN __Sys_Semaphore_Group_Find_Handle
#endif
#ifdef Master_OS_Config_Semaphore_Group_Wait
	EXTERN __Sys_Semaphore_Group_Wait
#endif
#ifdef Master_OS_Config_Semaphore_Group_Release
	EXTERN __Sys_Semaphore_Group_Release
#endif

#ifdef Master_OS_Config_Timer_Enable
	EXTERN __Sys_Timer_Enable
#endif
#ifdef Master_OS_Config_Timer_Disable
	EXTERN __Sys_Timer_Disable
#endif
#ifdef Master_OS_Config_Timer_Register
	EXTERN __Sys_Timer_Register
#endif
#ifdef Master_OS_Config_Timer_Delete
	EXTERN __Sys_Timer_Delete
#endif
#ifdef Master_OS_Config_Timer_Start
	EXTERN __Sys_Timer_Start
#endif
#ifdef Master_OS_Config_Timer_Stop
	EXTERN __Sys_Timer_Stop
#endif
#ifdef Master_OS_Config_Timer_Suspend
	EXTERN __Sys_Timer_Suspend
#endif
#ifdef Master_OS_Config_Timer_Resume
	EXTERN __Sys_Timer_Resume
#endif
#ifdef Master_OS_Config_Timer_Reset
	EXTERN __Sys_Timer_Reset
#endif
#ifdef Master_OS_Config_Timer_Enabled
	EXTERN __Sys_Timer_Enabled
#endif

	PUBLIC __Sys_Call_Table

	DATA

__Sys_Call_Table
	DCD 0

#ifdef Master_OS_Config_Memory_Size_Malloc
	DCD __Usr_Memory_Size_Malloc
#endif
#ifdef Master_OS_Config_Memory_Size_Free
	DCD __Usr_Memory_Size_Free
#endif
#ifdef Master_OS_Config_Memory_Malloc_Align
	DCD __Usr_Memory_Malloc_Align
#endif
#ifdef Master_OS_Config_Memory_Malloc
	DCD __Usr_Memory_Malloc
#endif
#ifdef Master_OS_Config_Memory_Free
	DCD __Usr_Memory_Free
#endif

#ifdef Master_OS_Config_UGC_Memory_Init
	DCD __Memory_Init
#endif
#ifdef Master_OS_Config_UGC_Memory_Size_Malloc
	DCD __Memory_Size_Malloc
#endif
#ifdef Master_OS_Config_UGC_Memory_Size_Free
	DCD __Memory_Size_Free
#endif
#ifdef Master_OS_Config_UGC_Memory_Malloc
	DCD __Memory_Malloc
#endif
#ifdef Master_OS_Config_UGC_Memory_Free
	DCD __Memory_Free
#endif

#ifdef Master_OS_Config_Device_Open
	DCD __Sys_Device_Open
#endif
#ifdef Master_OS_Config_Device_Close
	DCD __Sys_Device_Close
#endif
#ifdef Master_OS_Config_Device_Read
	DCD __Sys_Device_Read
#endif
#ifdef Master_OS_Config_Device_Write
	DCD __Sys_Device_Write
#endif
#ifdef Master_OS_Config_Device_Control
	DCD __Sys_Device_Control
#endif
#ifdef Master_OS_Config_Device_Info
	DCD __Sys_Device_Info
#endif

#ifdef Master_OS_Config_IRQ_Enable
	DCD __Sys_IRQ_Enable
#endif
#ifdef Master_OS_Config_IRQ_Disable
	DCD __Sys_IRQ_Disable
#endif
#ifdef Master_OS_Config_IRQ_Set_Priority
	DCD __Sys_IRQ_Set_Priority
#endif
#ifdef Master_OS_Config_IRQ_All_Enable
	DCD __Sys_IRQ_All_Enable
#endif
#ifdef Master_OS_Config_IRQ_All_Disable
	DCD __Sys_IRQ_All_Disable
#endif
#ifdef Master_OS_Config_IRQ_Register_Hook
	DCD __Sys_IRQ_Register_Hook
#endif
#ifdef Master_OS_Config_IRQ_Delete_Hook
	DCD __Sys_IRQ_Delete_Hook
#endif

/*
	DCD __Sys_Power_GET_Core_Frequency
	DCD __Sys_Power_GET_Bus_Frequency
	DCD __Sys_Power_GET_Flash_Frequency
	DCD __Sys_Power_GET_External_Frequency
*/
#ifdef Master_OS_Config_Scheduling_Create_Task
	DCD __Sys_Scheduling_Create_Task
#endif
#ifdef Master_OS_Config_Scheduling_Release_Task
	DCD __Sys_Scheduling_Release_Task
#endif
#ifdef Master_OS_Config_Scheduling_Sleep_Task
	DCD __Sys_Scheduling_Sleep_Task
#endif
#ifdef Master_OS_Config_Scheduling_Suspend_Task
	DCD __Sys_Scheduling_Suspend_Task
#endif
#ifdef Master_OS_Config_Scheduling_Resume_Task
	DCD __Sys_Scheduling_Resume_Task
#endif

#ifdef Master_OS_Config_Event_Flag_Create
	DCD __Sys_Event_Flag_Create
#endif
#ifdef Master_OS_Config_Event_Flag_Delete
	DCD __Sys_Event_Flag_Delete
#endif
#ifdef Master_OS_Config_Event_Flag_Find_Handle
	DCD __Sys_Event_Flag_Find_Handle
#endif
#ifdef Master_OS_Config_Event_Flag_Wait
	DCD __Sys_Event_Flag_Wait
#endif
#ifdef Master_OS_Config_Event_Flag_Clear
	DCD __Sys_Event_Flag_Clear
#endif
#ifdef Master_OS_Config_Event_Flag_Set
	DCD __Sys_Event_Flag_Set
#endif

#if (defined(Master_OS_Config_Event_Flag_Group_Create) || defined(Master_OS_Config_Event_Flag_Group_Create_8bit) || defined(Master_OS_Config_Event_Flag_Group_Create_16bit) || defined(Master_OS_Config_Event_Flag_Group_Create_32bit))
	DCD __Sys_Event_Flag_Group_Create
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Delete
	DCD __Sys_Event_Flag_Group_Delete
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Find_Handle
	DCD __Sys_Event_Flag_Group_Find_Handle
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Open
	DCD __Sys_Event_Flag_Group_Open
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Close
	DCD __Sys_Event_Flag_Group_Close
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Wait_And) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_8bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_16bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_32bit))
	DCD __Sys_Event_Flag_Group_Wait_And
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Wait_Or) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_8bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_16bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_32bit))
	DCD __Sys_Event_Flag_Group_Wait_Or
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Set) || defined(Master_OS_Config_Event_Flag_Group_Set_8bit) || defined(Master_OS_Config_Event_Flag_Group_Set_16bit) || defined(Master_OS_Config_Event_Flag_Group_Set_32bit))
	DCD __Sys_Event_Flag_Group_Set
#endif

#ifdef Master_OS_Config_FIFO_Queue_Create
	DCD __Sys_FIFO_Queue_Create
#endif
#ifdef Master_OS_Config_FIFO_Queue_Delete
	DCD __Sys_FIFO_Queue_Delete
#endif
#ifdef Master_OS_Config_FIFO_Queue_Find_Handle
	DCD __Sys_FIFO_Queue_Find_Handle
#endif
#ifdef Master_OS_Config_FIFO_Queue_Open
	DCD __Sys_FIFO_Queue_Open
#endif
#ifdef Master_OS_Config_FIFO_Queue_Close
	DCD __Sys_FIFO_Queue_Close
#endif
#ifdef Master_OS_Config_FIFO_Queue_Wait
	DCD __Sys_FIFO_Queue_Wait
#endif
#ifdef Master_OS_Config_FIFO_Queue_Clear
	DCD __Sys_FIFO_Queue_Clear
#endif
#ifdef Master_OS_Config_FIFO_Queue_Set
	DCD __Sys_FIFO_Queue_Set
#endif

#ifdef Master_OS_Config_Message_Queue_Create
	DCD __Sys_Message_Queue_Create
#endif
#ifdef Master_OS_Config_Message_Queue_Delete
	DCD __Sys_Message_Queue_Delete
#endif
#ifdef Master_OS_Config_Message_Queue_Find_Handle
	DCD __Sys_Message_Queue_Find_Handle
#endif
#ifdef Master_OS_Config_Message_Queue_Open
	DCD __Sys_Message_Queue_Open
#endif
#ifdef Master_OS_Config_Message_Queue_Close
	DCD __Sys_Message_Queue_Close
#endif
#ifdef Master_OS_Config_Message_Queue_Wait
	DCD __Sys_Message_Queue_Wait
#endif
#ifdef Master_OS_Config_Message_Queue_Clear
	DCD __Sys_Message_Queue_Clear
#endif
#ifdef Master_OS_Config_Message_Queue_Set
	DCD __Sys_Message_Queue_Set
#endif

#ifdef Master_OS_Config_Mutex_Create
	DCD __Sys_Mutex_Create
#endif
#ifdef Master_OS_Config_Mutex_Delete
	DCD __Sys_Mutex_Delete
#endif
#ifdef Master_OS_Config_Mutex_Find_Handle
	DCD __Sys_Mutex_Find_Handle
#endif
#ifdef Master_OS_Config_Mutex_Wait
	DCD __Sys_Mutex_Wait
#endif
#ifdef Master_OS_Config_Mutex_Release
	DCD __Sys_Mutex_Release
#endif

#ifdef Master_OS_Config_Semaphore_Create
	DCD __Sys_Semaphore_Create
#endif
#ifdef Master_OS_Config_Semaphore_Delete
	DCD __Sys_Semaphore_Delete
#endif
#ifdef Master_OS_Config_Semaphore_Find_Handle
	DCD __Sys_Semaphore_Find_Handle
#endif
#ifdef Master_OS_Config_Semaphore_Wait
	DCD __Sys_Semaphore_Wait
#endif
#ifdef Master_OS_Config_Semaphore_Release
	DCD __Sys_Semaphore_Release
#endif

#ifdef Master_OS_Config_Semaphore_Group_Create
	DCD __Sys_Semaphore_Group_Create
#endif
#ifdef Master_OS_Config_Semaphore_Group_Delete
	DCD __Sys_Semaphore_Group_Delete
#endif
#ifdef Master_OS_Config_Semaphore_Group_Find_Handle
	DCD __Sys_Semaphore_Group_Find_Handle
#endif
#ifdef Master_OS_Config_Semaphore_Group_Wait
	DCD __Sys_Semaphore_Group_Wait
#endif
#ifdef Master_OS_Config_Semaphore_Group_Release
	DCD __Sys_Semaphore_Group_Release
#endif

#ifdef Master_OS_Config_Timer_Enable
	DCD __Sys_Timer_Enable
#endif
#ifdef Master_OS_Config_Timer_Disable
	DCD __Sys_Timer_Disable
#endif
#ifdef Master_OS_Config_Timer_Register
	DCD __Sys_Timer_Register
#endif
#ifdef Master_OS_Config_Timer_Delete
	DCD __Sys_Timer_Delete
#endif
#ifdef Master_OS_Config_Timer_Start
	DCD __Sys_Timer_Start
#endif
#ifdef Master_OS_Config_Timer_Stop
	DCD __Sys_Timer_Stop
#endif
#ifdef Master_OS_Config_Timer_Suspend
	DCD __Sys_Timer_Suspend
#endif
#ifdef Master_OS_Config_Timer_Resume
	DCD __Sys_Timer_Resume
#endif
#ifdef Master_OS_Config_Timer_Reset
	DCD __Sys_Timer_Reset
#endif
#ifdef Master_OS_Config_Timer_Enabled
	DCD __Sys_Timer_Enabled
#endif

	END
