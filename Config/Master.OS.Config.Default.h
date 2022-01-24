/*
 * Master.OS.Config.Default.h
 *
 *  Created on: 2020年12月2日
 *      Author: Master.HE
 */

#ifndef MASTER_OS_CONFIG_DEFAULT_H_
#define MASTER_OS_CONFIG_DEFAULT_H_

//BSP
#define Master_OS_Config_BSP_System_Reset

#define Master_OS_Config_BSP_Wdog_Enable
#define Master_OS_Config_BSP_Wdog_Disable
#define Master_OS_Config_BSP_Wdog_Refresh


//Memory
#define Master_OS_Config_Memory_Size_Malloc
#define Master_OS_Config_Memory_Size_Free
#define Master_OS_Config_Memory_Malloc_Align
#define Master_OS_Config_Memory_Malloc
#define Master_OS_Config_Memory_Free
#define Master_OS_Config_UGC_Memory_Init
#define Master_OS_Config_UGC_Memory_Size_Malloc
#define Master_OS_Config_UGC_Memory_Size_Free
#define Master_OS_Config_UGC_Memory_Malloc
#define Master_OS_Config_UGC_Memory_Free


//Device-Legacy
#define Master_OS_Config_Device_Legacy_Open
#define Master_OS_Config_Device_Legacy_Close
#define Master_OS_Config_Device_Legacy_Read
#define Master_OS_Config_Device_Legacy_Write
#define Master_OS_Config_Device_Legacy_Control
#define Master_OS_Config_Device_Legacy_Info

//Device-Class-ETH
#define Master_OS_Config_Device_Class_ETH_Open
#define Master_OS_Config_Device_Class_ETH_Close
#define Master_OS_Config_Device_Class_ETH_Get_Enabled
#define Master_OS_Config_Device_Class_ETH_Set_Enabled
#define Master_OS_Config_Device_Class_ETH_Get_MAC_Address
#define Master_OS_Config_Device_Class_ETH_Set_MAC_Address
#define Master_OS_Config_Device_Class_ETH_Get_Interface
#define Master_OS_Config_Device_Class_ETH_Set_Interface
#define Master_OS_Config_Device_Class_ETH_Set_MAC_Address_Filter
#define Master_OS_Config_Device_Class_ETH_ReSet_MAC_Address_Filter
#define Master_OS_Config_Device_Class_ETH_Receive
#define Master_OS_Config_Device_Class_ETH_Send
#define Master_OS_Config_Device_Class_ETH_Send_Slice
#define Master_OS_Config_Device_Class_ETH_Get_MDIO
#define Master_OS_Config_Device_Class_ETH_Set_MDIO
#define Master_OS_Config_Device_Class_ETH_Get_Info

//IRQ
#define Master_OS_Config_IRQ_Enable
#define Master_OS_Config_IRQ_Disable
#define Master_OS_Config_IRQ_Set_Priority
#define Master_OS_Config_IRQ_All_Enable
#define Master_OS_Config_IRQ_All_Disable
#define Master_OS_Config_IRQ_Register_Hook
#define Master_OS_Config_IRQ_Delete_Hook


//Scheduling
#define Master_OS_Config_Scheduling_Create_Task
#define Master_OS_Config_Scheduling_Release_Task
#define Master_OS_Config_Scheduling_Exit_Task
#define Master_OS_Config_Scheduling_Sleep_Task
#define Master_OS_Config_Scheduling_Suspend_Task
#define Master_OS_Config_Scheduling_Resume_Task


//Event-Event_Flag
#define Master_OS_Config_Event_Flag_Create
#define Master_OS_Config_Event_Flag_Delete
#define Master_OS_Config_Event_Flag_Find_Handle
#define Master_OS_Config_Event_Flag_Wait
#define Master_OS_Config_Event_Flag_Clear
#define Master_OS_Config_Event_Flag_Set


//Event-Event_Flag_Group
#define Master_OS_Config_Event_Flag_Group_Create
#define Master_OS_Config_Event_Flag_Group_Create_8bit
#define Master_OS_Config_Event_Flag_Group_Create_16bit
#define Master_OS_Config_Event_Flag_Group_Create_32bit
#define Master_OS_Config_Event_Flag_Group_Delete
#define Master_OS_Config_Event_Flag_Group_Find_Handle
#define Master_OS_Config_Event_Flag_Group_Open
#define Master_OS_Config_Event_Flag_Group_Close
#define Master_OS_Config_Event_Flag_Group_Wait_And
#define Master_OS_Config_Event_Flag_Group_Wait_And_8bit
#define Master_OS_Config_Event_Flag_Group_Wait_And_16bit
#define Master_OS_Config_Event_Flag_Group_Wait_And_32bit
#define Master_OS_Config_Event_Flag_Group_Wait_Or
#define Master_OS_Config_Event_Flag_Group_Wait_Or_8bit
#define Master_OS_Config_Event_Flag_Group_Wait_Or_16bit
#define Master_OS_Config_Event_Flag_Group_Wait_Or_32bit
#define Master_OS_Config_Event_Flag_Group_Set
#define Master_OS_Config_Event_Flag_Group_Set_8bit
#define Master_OS_Config_Event_Flag_Group_Set_16bit
#define Master_OS_Config_Event_Flag_Group_Set_32bit



//Event-FIFO_Queue
#define Master_OS_Config_FIFO_Queue_Create
#define Master_OS_Config_FIFO_Queue_Delete
#define Master_OS_Config_FIFO_Queue_Find_Handle
#define Master_OS_Config_FIFO_Queue_Open
#define Master_OS_Config_FIFO_Queue_Close
#define Master_OS_Config_FIFO_Queue_Wait
#define Master_OS_Config_FIFO_Queue_Clear
#define Master_OS_Config_FIFO_Queue_Set



//Event-Message_Queue
#define Master_OS_Config_Message_Queue_Create
#define Master_OS_Config_Message_Queue_Delete
#define Master_OS_Config_Message_Queue_Find_Handle
#define Master_OS_Config_Message_Queue_Open
#define Master_OS_Config_Message_Queue_Close
#define Master_OS_Config_Message_Queue_Wait
#define Master_OS_Config_Message_Queue_Clear
#define Master_OS_Config_Message_Queue_Set


//Event-Mutex
#define Master_OS_Config_Mutex_Create
#define Master_OS_Config_Mutex_Delete
#define Master_OS_Config_Mutex_Find_Handle
#define Master_OS_Config_Mutex_Wait
#define Master_OS_Config_Mutex_Release


//Event-Semaphore
#define Master_OS_Config_Semaphore_Create
#define Master_OS_Config_Semaphore_Delete
#define Master_OS_Config_Semaphore_Find_Handle
#define Master_OS_Config_Semaphore_Wait
#define Master_OS_Config_Semaphore_Release


//Event-Semaphore-Group
#define Master_OS_Config_Semaphore_Group_Create
#define Master_OS_Config_Semaphore_Group_Delete
#define Master_OS_Config_Semaphore_Group_Find_Handle
#define Master_OS_Config_Semaphore_Group_Wait
#define Master_OS_Config_Semaphore_Group_Release


//Timer
#define Master_OS_Config_Timer_Enable
#define Master_OS_Config_Timer_Disable
#define Master_OS_Config_Timer_Register
#define Master_OS_Config_Timer_Register2
#define Master_OS_Config_Timer_Delete
#define Master_OS_Config_Timer_Start
#define Master_OS_Config_Timer_Stop
#define Master_OS_Config_Timer_Suspend
#define Master_OS_Config_Timer_Resume
#define Master_OS_Config_Timer_Reset
#define Master_OS_Config_Timer_Enabled

#endif /* MASTER_OS_CONFIG_DEFAULT_H_ */
