/*
 * SysCall.Table.h
 *
 *  Created on: 2019年4月9日
 *      Author: Master.HE
 */

#ifndef SYSCALL_TABLE_H_
#define SYSCALL_TABLE_H_

#include "Master.OS.Config.h"

typedef enum
{
	SysCall_Table_Index_Null			=0,
#ifdef Master_OS_Config_BSP_Wdog_Enable
	SysCall_Table_Index_BSP_Wdog_Enable,
#endif
#ifdef Master_OS_Config_BSP_Wdog_Disable
	SysCall_Table_Index_BSP_Wdog_Disable,
#endif
#ifdef Master_OS_Config_BSP_Wdog_Clear
	SysCall_Table_Index_BSP_Wdog_Clear,
#endif

#ifdef Master_OS_Config_Memory_Size_Malloc
	SysCall_Table_Memory_Size_Malloc,
#endif
#ifdef Master_OS_Config_Memory_Size_Free
	SysCall_Table_Memory_Size_Free,
#endif
#ifdef Master_OS_Config_Memory_Malloc_Align
	SysCall_Table_Memory_Malloc_Align,
#endif
#ifdef Master_OS_Config_Memory_Malloc
	SysCall_Table_Memory_Malloc,
#endif
#ifdef Master_OS_Config_Memory_Free
	SysCall_Table_Memory_Free,
#endif

#ifdef Master_OS_Config_UGC_Memory_Init
	SysCall_Table_UGC_Memory_Init,
#endif
#ifdef Master_OS_Config_UGC_Memory_Size_Malloc
	SysCall_Table_UGC_Memory_Size_Malloc,
#endif
#ifdef Master_OS_Config_UGC_Memory_Size_Free
	SysCall_Table_UGC_Memory_Size_Free,
#endif
#ifdef Master_OS_Config_UGC_Memory_Malloc
	SysCall_Table_UGC_Memory_Malloc,
#endif
#ifdef Master_OS_Config_UGC_Memory_Free
	SysCall_Table_UGC_Memory_Free,
#endif

#ifdef Master_OS_Config_Device_Open
	SysCall_Table_Index_Device_Open,
#endif
#ifdef Master_OS_Config_Device_Close
	SysCall_Table_Index_Device_Close,
#endif
#ifdef Master_OS_Config_Device_Read
	SysCall_Table_Index_Device_Read,
#endif
#ifdef Master_OS_Config_Device_Write
	SysCall_Table_Index_Device_Write,
#endif
#ifdef Master_OS_Config_Device_Control
	SysCall_Table_Index_Device_Control,
#endif
#ifdef Master_OS_Config_Device_Info
	SysCall_Table_Index_Device_Info,
#endif

#ifdef Master_OS_Config_IRQ_Enable
	SysCall_Table_Index_IRQ_Enable,
#endif
#ifdef Master_OS_Config_IRQ_Disable
	SysCall_Table_Index_IRQ_Disable,
#endif
#ifdef Master_OS_Config_IRQ_Set_Priority
	SysCall_Table_Index_IRQ_Set_Priority,
#endif
#ifdef Master_OS_Config_IRQ_All_Enable
	SysCall_Table_Index_IRQ_All_Enable,
#endif
#ifdef Master_OS_Config_IRQ_All_Disable
	SysCall_Table_Index_IRQ_All_Disable,
#endif
#ifdef Master_OS_Config_IRQ_Register_Hook
	SysCall_Table_Index_IRQ_Register_Hook,
#endif
#ifdef Master_OS_Config_IRQ_Delete_Hook
	SysCall_Table_Index_IRQ_Delete_Hook,
#endif

/*
	SysCall_Table_Index_Power_GET_Core_Frequency,
	SysCall_Table_Index_Power_GET_Bus_Frequency,
	SysCall_Table_Index_Power_GET_Flash_Frequency,
	SysCall_Table_Index_Power_GET_External_Frequency,
*/
#ifdef Master_OS_Config_Scheduling_Create_Task
	SysCall_Table_Index_Scheduling_Create_Task,
#endif
#ifdef Master_OS_Config_Scheduling_Release_Task
	SysCall_Table_Index_Scheduling_Release_Task,
#endif
#ifdef Master_OS_Config_Scheduling_Sleep_Task
	SysCall_Table_Index_Scheduling_Sleep_Task,
#endif
#ifdef Master_OS_Config_Scheduling_Suspend_Task
	SysCall_Table_Index_Scheduling_Suspend_Task,
#endif
#ifdef Master_OS_Config_Scheduling_Resume_Task
	SysCall_Table_Index_Scheduling_Resume_Task,
#endif

#ifdef Master_OS_Config_Event_Flag_Create
	SysCall_Table_Index_Event_Flag_Create,
#endif
#ifdef Master_OS_Config_Event_Flag_Delete
	SysCall_Table_Index_Event_Flag_Delete,
#endif
#ifdef Master_OS_Config_Event_Flag_Find_Handle
	SysCall_Table_Index_Event_Flag_Find_Handle,
#endif
#ifdef Master_OS_Config_Event_Flag_Wait
	SysCall_Table_Index_Event_Flag_Wait,
#endif
#ifdef Master_OS_Config_Event_Flag_Clear
	SysCall_Table_Index_Event_Flag_Clear,
#endif
#ifdef Master_OS_Config_Event_Flag_Set
	SysCall_Table_Index_Event_Flag_Set,
#endif

#if (defined(Master_OS_Config_Event_Flag_Group_Create) || defined(Master_OS_Config_Event_Flag_Group_Create_8bit) || defined(Master_OS_Config_Event_Flag_Group_Create_16bit) || defined(Master_OS_Config_Event_Flag_Group_Create_32bit))
	SysCall_Table_Index_Event_Flag_Group_Create,
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Delete
	SysCall_Table_Index_Event_Flag_Group_Delete,
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Find_Handle
	SysCall_Table_Index_Event_Flag_Group_Find_Handle,
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Open
	SysCall_Table_Index_Event_Flag_Group_Open,
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Close
	SysCall_Table_Index_Event_Flag_Group_Close,
#endif

#if (defined(Master_OS_Config_Event_Flag_Group_Wait_And) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_8bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_16bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_32bit))
	SysCall_Table_Index_Event_Flag_Group_Wait_And,
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Wait_Or) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_8bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_16bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_32bit))
	SysCall_Table_Index_Event_Flag_Group_Wait_Or,
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Set) || defined(Master_OS_Config_Event_Flag_Group_Set_8bit) || defined(Master_OS_Config_Event_Flag_Group_Set_16bit) || defined(Master_OS_Config_Event_Flag_Group_Set_32bit))
	SysCall_Table_Index_Event_Flag_Group_Set,
#endif

#ifdef Master_OS_Config_FIFO_Queue_Create
	SysCall_Table_Index_FIFO_Queue_Create,
#endif
#ifdef Master_OS_Config_FIFO_Queue_Delete
	SysCall_Table_Index_FIFO_Queue_Delete,
#endif
#ifdef Master_OS_Config_FIFO_Queue_Find_Handle
	SysCall_Table_Index_FIFO_Queue_Find_Handle,
#endif
#ifdef Master_OS_Config_FIFO_Queue_Open
	SysCall_Table_Index_FIFO_Queue_Open,
#endif
#ifdef Master_OS_Config_FIFO_Queue_Close
	SysCall_Table_Index_FIFO_Queue_Close,
#endif
#ifdef Master_OS_Config_FIFO_Queue_Wait
	SysCall_Table_Index_FIFO_Queue_Wait,
#endif
#ifdef Master_OS_Config_FIFO_Queue_Clear
	SysCall_Table_Index_FIFO_Queue_Clear,
#endif
#ifdef Master_OS_Config_FIFO_Queue_Set
	SysCall_Table_Index_FIFO_Queue_Set,
#endif

#ifdef Master_OS_Config_Message_Queue_Create
	SysCall_Table_Index_Message_Queue_Create,
#endif
#ifdef Master_OS_Config_Message_Queue_Delete
	SysCall_Table_Index_Message_Queue_Delete,
#endif
#ifdef Master_OS_Config_Message_Queue_Find_Handle
	SysCall_Table_Index_Message_Queue_Find_Handle,
#endif
#ifdef Master_OS_Config_Message_Queue_Open
	SysCall_Table_Index_Message_Queue_Open,
#endif
#ifdef Master_OS_Config_Message_Queue_Close
	SysCall_Table_Index_Message_Queue_Close,
#endif
#ifdef Master_OS_Config_Message_Queue_Wait
	SysCall_Table_Index_Message_Queue_Wait,
#endif
#ifdef Master_OS_Config_Message_Queue_Clear
	SysCall_Table_Index_Message_Queue_Clear,
#endif
#ifdef Master_OS_Config_Message_Queue_Set
	SysCall_Table_Index_Message_Queue_Set,
#endif

#ifdef Master_OS_Config_Mutex_Create
	SysCall_Table_Index_Mutex_Create,
#endif
#ifdef Master_OS_Config_Mutex_Delete
	SysCall_Table_Index_Mutex_Delete,
#endif
#ifdef Master_OS_Config_Mutex_Find_Handle
	SysCall_Table_Index_Mutex_Find_Handle,
#endif
#ifdef Master_OS_Config_Mutex_Wait
	SysCall_Table_Index_Mutex_Wait,
#endif
#ifdef Master_OS_Config_Mutex_Release
	SysCall_Table_Index_Mutex_Release,
#endif

#ifdef Master_OS_Config_Semaphore_Create
	SysCall_Table_Index_Semaphore_Create,
#endif
#ifdef Master_OS_Config_Semaphore_Delete
	SysCall_Table_Index_Semaphore_Delete,
#endif
#ifdef Master_OS_Config_Semaphore_Find_Handle
	SysCall_Table_Index_Semaphore_Find_Handle,
#endif
#ifdef Master_OS_Config_Semaphore_Wait
	SysCall_Table_Index_Semaphore_Wait,
#endif
#ifdef Master_OS_Config_Semaphore_Release
	SysCall_Table_Index_Semaphore_Release,
#endif

#ifdef Master_OS_Config_Semaphore_Group_Create
	SysCall_Table_Index_Semaphore_Group_Create,
#endif
#ifdef Master_OS_Config_Semaphore_Group_Delete
	SysCall_Table_Index_Semaphore_Group_Delete,
#endif
#ifdef Master_OS_Config_Semaphore_Group_Find_Handle
	SysCall_Table_Index_Semaphore_Group_Find_Handle,
#endif
#ifdef Master_OS_Config_Semaphore_Group_Wait
	SysCall_Table_Index_Semaphore_Group_Wait,
#endif
#ifdef Master_OS_Config_Semaphore_Group_Release
	SysCall_Table_Index_Semaphore_Group_Release,
#endif

#ifdef Master_OS_Config_Timer_Enable
	SysCall_Table_Index_Timer_Enable,
#endif
#ifdef Master_OS_Config_Timer_Disable
	SysCall_Table_Index_Timer_Disable,
#endif
#ifdef Master_OS_Config_Timer_Register
	SysCall_Table_Index_Timer_Register,
#endif
#ifdef Master_OS_Config_Timer_Delete
	SysCall_Table_Index_Timer_Delete,
#endif
#ifdef Master_OS_Config_Timer_Start
	SysCall_Table_Index_Timer_Start,
#endif
#ifdef Master_OS_Config_Timer_Stop
	SysCall_Table_Index_Timer_Stop,
#endif
#ifdef Master_OS_Config_Timer_Suspend
	SysCall_Table_Index_Timer_Suspend,
#endif
#ifdef Master_OS_Config_Timer_Resume
	SysCall_Table_Index_Timer_Resume,
#endif
#ifdef Master_OS_Config_Timer_Reset
	SysCall_Table_Index_Timer_Reset,
#endif
#ifdef Master_OS_Config_Timer_Enabled
	SysCall_Table_Index_Timer_Enabled,
#endif

	SysCall_Table_Index_End,
}SysCall_Table_Index_Type;

#endif /* SYSCALL_TABLE_H_ */
