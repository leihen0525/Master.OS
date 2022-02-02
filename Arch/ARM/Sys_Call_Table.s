/*
 * Sys_Call_Table.s
 *
 *  Created on: 2019年4月9日
 *      Author: Master.HE
 */
//#include "Master.OS.Config.h"

	MODULE Sys_Call_Table

	SECTION .text:CODE:NOROOT(2)

	PUBWEAK __Sys_Handle_New
	PUBWEAK __Sys_Handle_Free

	PUBWEAK __Sys_BSP_System_Reset

	PUBWEAK __Sys_BSP_Wdog_Enable
	PUBWEAK __Sys_BSP_Wdog_Disable
	PUBWEAK __Sys_BSP_Wdog_Refresh


	PUBWEAK __Usr_Memory_Size_Malloc
	PUBWEAK __Usr_Memory_Size_Free
	PUBWEAK __Usr_Memory_Malloc_Align
	PUBWEAK __Usr_Memory_Malloc
	PUBWEAK __Usr_Memory_Free


	PUBWEAK __Memory_Init
	PUBWEAK __Memory_Size_Malloc
	PUBWEAK __Memory_Size_Free
	PUBWEAK __Memory_Malloc
	PUBWEAK __Memory_Free



	PUBWEAK __Sys_Device_Legacy_Open
	PUBWEAK __Sys_Device_Legacy_Close
	PUBWEAK __Sys_Device_Legacy_Read
	PUBWEAK __Sys_Device_Legacy_Write
	PUBWEAK __Sys_Device_Legacy_Control
	PUBWEAK __Sys_Device_Legacy_Info


	PUBWEAK __Sys_Device_Class_ETH_Open
	PUBWEAK __Sys_Device_Class_ETH_Close
	PUBWEAK __Sys_Device_Class_ETH_Init
	PUBWEAK __Sys_Device_Class_ETH_DeInit
	PUBWEAK __Sys_Device_Class_ETH_Get_Enabled
	PUBWEAK __Sys_Device_Class_ETH_Set_Enabled
	PUBWEAK __Sys_Device_Class_ETH_Get_MAC_Address
	PUBWEAK __Sys_Device_Class_ETH_Set_MAC_Address
	PUBWEAK __Sys_Device_Class_ETH_Get_Interface
	PUBWEAK __Sys_Device_Class_ETH_Set_Interface
	PUBWEAK __Sys_Device_Class_ETH_Set_MAC_Address_Filter
	PUBWEAK __Sys_Device_Class_ETH_ReSet_MAC_Address_Filter
	PUBWEAK __Sys_Device_Class_ETH_Receive
	PUBWEAK __Sys_Device_Class_ETH_Send
	PUBWEAK __Sys_Device_Class_ETH_Send_Sync
	PUBWEAK __Sys_Device_Class_ETH_Send_Slice
	PUBWEAK __Sys_Device_Class_ETH_Send_Slice_Sync
	PUBWEAK __Sys_Device_Class_ETH_Get_MDIO
	PUBWEAK __Sys_Device_Class_ETH_Set_MDIO
	PUBWEAK __Sys_Device_Class_ETH_Get_Static_Cfg
	PUBWEAK __Sys_Device_Class_ETH_Get_Info


	PUBWEAK __Sys_IRQ_Enable
	PUBWEAK __Sys_IRQ_Disable
	PUBWEAK __Sys_IRQ_Set_Priority
	PUBWEAK __Sys_IRQ_All_Enable
	PUBWEAK __Sys_IRQ_All_Disable
	PUBWEAK __Sys_IRQ_Register_Hook
	PUBWEAK __Sys_IRQ_Delete_Hook


	PUBWEAK __Sys_Scheduling_Create_Task
	PUBWEAK __Sys_Scheduling_Release_Task
	PUBWEAK __Sys_Scheduling_Sleep_Task
	PUBWEAK __Sys_Scheduling_Suspend_Task
	PUBWEAK __Sys_Scheduling_Resume_Task



	PUBWEAK __Sys_Event_Flag_Create
	PUBWEAK __Sys_Event_Flag_Delete
	PUBWEAK __Sys_Event_Flag_Find_Handle
	PUBWEAK __Sys_Event_Flag_Wait
	PUBWEAK __Sys_Event_Flag_Clear
	PUBWEAK __Sys_Event_Flag_Set


	PUBWEAK __Sys_Event_Flag_Group_Create
	PUBWEAK __Sys_Event_Flag_Group_Delete
	PUBWEAK __Sys_Event_Flag_Group_Find_Handle
	PUBWEAK __Sys_Event_Flag_Group_Open
	PUBWEAK __Sys_Event_Flag_Group_Close
	PUBWEAK __Sys_Event_Flag_Group_Wait_And
	PUBWEAK __Sys_Event_Flag_Group_Wait_Or
	PUBWEAK __Sys_Event_Flag_Group_Set



	PUBWEAK __Sys_FIFO_Queue_Create
	PUBWEAK __Sys_FIFO_Queue_Delete
	PUBWEAK __Sys_FIFO_Queue_Find_Handle
	PUBWEAK __Sys_FIFO_Queue_Open
	PUBWEAK __Sys_FIFO_Queue_Close
	PUBWEAK __Sys_FIFO_Queue_Wait
	PUBWEAK __Sys_FIFO_Queue_Clear
	PUBWEAK __Sys_FIFO_Queue_Set



	PUBWEAK __Sys_Message_Queue_Create
	PUBWEAK __Sys_Message_Queue_Delete
	PUBWEAK __Sys_Message_Queue_Find_Handle
	PUBWEAK __Sys_Message_Queue_Open
	PUBWEAK __Sys_Message_Queue_Close
	PUBWEAK __Sys_Message_Queue_Wait
	PUBWEAK __Sys_Message_Queue_Clear
	PUBWEAK __Sys_Message_Queue_Set



	PUBWEAK __Sys_Mutex_Create
	PUBWEAK __Sys_Mutex_Delete
	PUBWEAK __Sys_Mutex_Find_Handle
	PUBWEAK __Sys_Mutex_Wait
	PUBWEAK __Sys_Mutex_Release



	PUBWEAK __Sys_Semaphore_Create
	PUBWEAK __Sys_Semaphore_Delete
	PUBWEAK __Sys_Semaphore_Find_Handle
	PUBWEAK __Sys_Semaphore_Wait
	PUBWEAK __Sys_Semaphore_Release



	PUBWEAK __Sys_Semaphore_Group_Create
	PUBWEAK __Sys_Semaphore_Group_Delete
	PUBWEAK __Sys_Semaphore_Group_Find_Handle
	PUBWEAK __Sys_Semaphore_Group_Wait
	PUBWEAK __Sys_Semaphore_Group_Release


	PUBWEAK __Sys_Timer_GET_Counter
	PUBWEAK __Sys_Timer_Enable
	PUBWEAK __Sys_Timer_Disable
	PUBWEAK __Sys_Timer_Register
	PUBWEAK __Sys_Timer_Register2
	PUBWEAK __Sys_Timer_Delete
	PUBWEAK __Sys_Timer_Start
	PUBWEAK __Sys_Timer_Stop
	PUBWEAK __Sys_Timer_Suspend
	PUBWEAK __Sys_Timer_Resume
	PUBWEAK __Sys_Timer_Reset
	PUBWEAK __Sys_Timer_Enabled

__Sys_Handle_New
__Sys_Handle_Free

__Sys_BSP_System_Reset

__Sys_BSP_Wdog_Enable
__Sys_BSP_Wdog_Disable
__Sys_BSP_Wdog_Refresh


__Usr_Memory_Size_Malloc
__Usr_Memory_Size_Free
__Usr_Memory_Malloc_Align
__Usr_Memory_Malloc
__Usr_Memory_Free


__Memory_Init
__Memory_Size_Malloc
__Memory_Size_Free
__Memory_Malloc
__Memory_Free



__Sys_Device_Legacy_Open
__Sys_Device_Legacy_Close
__Sys_Device_Legacy_Read
__Sys_Device_Legacy_Write
__Sys_Device_Legacy_Control
__Sys_Device_Legacy_Info

__Sys_Device_Class_ETH_Open
__Sys_Device_Class_ETH_Close
__Sys_Device_Class_ETH_Init
__Sys_Device_Class_ETH_DeInit
__Sys_Device_Class_ETH_Get_Enabled
__Sys_Device_Class_ETH_Set_Enabled
__Sys_Device_Class_ETH_Get_MAC_Address
__Sys_Device_Class_ETH_Set_MAC_Address
__Sys_Device_Class_ETH_Get_Interface
__Sys_Device_Class_ETH_Set_Interface
__Sys_Device_Class_ETH_Set_MAC_Address_Filter
__Sys_Device_Class_ETH_ReSet_MAC_Address_Filter
__Sys_Device_Class_ETH_Receive
__Sys_Device_Class_ETH_Send
__Sys_Device_Class_ETH_Send_Sync
__Sys_Device_Class_ETH_Send_Slice
__Sys_Device_Class_ETH_Send_Slice_Sync
__Sys_Device_Class_ETH_Get_MDIO
__Sys_Device_Class_ETH_Set_MDIO
__Sys_Device_Class_ETH_Get_Static_Cfg
__Sys_Device_Class_ETH_Get_Info

__Sys_IRQ_Enable
__Sys_IRQ_Disable
__Sys_IRQ_Set_Priority
__Sys_IRQ_All_Enable
__Sys_IRQ_All_Disable
__Sys_IRQ_Register_Hook
__Sys_IRQ_Delete_Hook


__Sys_Scheduling_Create_Task
__Sys_Scheduling_Release_Task
__Sys_Scheduling_Sleep_Task
__Sys_Scheduling_Suspend_Task
__Sys_Scheduling_Resume_Task



__Sys_Event_Flag_Create
__Sys_Event_Flag_Delete
__Sys_Event_Flag_Find_Handle
__Sys_Event_Flag_Wait
__Sys_Event_Flag_Clear
__Sys_Event_Flag_Set


__Sys_Event_Flag_Group_Create
__Sys_Event_Flag_Group_Delete
__Sys_Event_Flag_Group_Find_Handle
__Sys_Event_Flag_Group_Open
__Sys_Event_Flag_Group_Close
__Sys_Event_Flag_Group_Wait_And
__Sys_Event_Flag_Group_Wait_Or
__Sys_Event_Flag_Group_Set



__Sys_FIFO_Queue_Create
__Sys_FIFO_Queue_Delete
__Sys_FIFO_Queue_Find_Handle
__Sys_FIFO_Queue_Open
__Sys_FIFO_Queue_Close
__Sys_FIFO_Queue_Wait
__Sys_FIFO_Queue_Clear
__Sys_FIFO_Queue_Set



__Sys_Message_Queue_Create
__Sys_Message_Queue_Delete
__Sys_Message_Queue_Find_Handle
__Sys_Message_Queue_Open
__Sys_Message_Queue_Close
__Sys_Message_Queue_Wait
__Sys_Message_Queue_Clear
__Sys_Message_Queue_Set



__Sys_Mutex_Create
__Sys_Mutex_Delete
__Sys_Mutex_Find_Handle
__Sys_Mutex_Wait
__Sys_Mutex_Release



__Sys_Semaphore_Create
__Sys_Semaphore_Delete
__Sys_Semaphore_Find_Handle
__Sys_Semaphore_Wait
__Sys_Semaphore_Release



__Sys_Semaphore_Group_Create
__Sys_Semaphore_Group_Delete
__Sys_Semaphore_Group_Find_Handle
__Sys_Semaphore_Group_Wait
__Sys_Semaphore_Group_Release


__Sys_Timer_GET_Counter
__Sys_Timer_Enable
__Sys_Timer_Disable
__Sys_Timer_Register
__Sys_Timer_Register2
__Sys_Timer_Delete
__Sys_Timer_Start
__Sys_Timer_Stop
__Sys_Timer_Suspend
__Sys_Timer_Resume
__Sys_Timer_Reset
__Sys_Timer_Enabled

	ldr r0,=-1
	bx lr


	PUBLIC __Sys_Call_Table
	SECTION .text:DATA:ROOT(2)
	DATA

__Sys_Call_Table
	DCD 0

	DCD __Sys_Handle_New

	DCD __Sys_Handle_Free

	DCD __Sys_BSP_System_Reset


	DCD __Sys_BSP_Wdog_Enable


	DCD __Sys_BSP_Wdog_Disable

	DCD __Sys_BSP_Wdog_Refresh



	DCD __Usr_Memory_Size_Malloc

	DCD __Usr_Memory_Size_Free

	DCD __Usr_Memory_Malloc_Align

	DCD __Usr_Memory_Malloc

	DCD __Usr_Memory_Free



	DCD __Memory_Init

	DCD __Memory_Size_Malloc

	DCD __Memory_Size_Free

	DCD __Memory_Malloc

	DCD __Memory_Free



	DCD __Sys_Device_Legacy_Open

	DCD __Sys_Device_Legacy_Close

	DCD __Sys_Device_Legacy_Read

	DCD __Sys_Device_Legacy_Write

	DCD __Sys_Device_Legacy_Control

	DCD __Sys_Device_Legacy_Info


	DCD __Sys_Device_Class_ETH_Open
	DCD __Sys_Device_Class_ETH_Close
	DCD __Sys_Device_Class_ETH_Init
	DCD __Sys_Device_Class_ETH_DeInit
	DCD __Sys_Device_Class_ETH_Get_Enabled
	DCD __Sys_Device_Class_ETH_Set_Enabled
	DCD __Sys_Device_Class_ETH_Get_MAC_Address
	DCD __Sys_Device_Class_ETH_Set_MAC_Address
	DCD __Sys_Device_Class_ETH_Get_Interface
	DCD __Sys_Device_Class_ETH_Set_Interface
	DCD __Sys_Device_Class_ETH_Set_MAC_Address_Filter
	DCD __Sys_Device_Class_ETH_ReSet_MAC_Address_Filter
	DCD __Sys_Device_Class_ETH_Receive
	DCD __Sys_Device_Class_ETH_Send
	DCD __Sys_Device_Class_ETH_Send_Sync
	DCD __Sys_Device_Class_ETH_Send_Slice
	DCD __Sys_Device_Class_ETH_Send_Slice_Sync
	DCD __Sys_Device_Class_ETH_Get_MDIO
	DCD __Sys_Device_Class_ETH_Set_MDIO
	DCD __Sys_Device_Class_ETH_Get_Static_Cfg
	DCD __Sys_Device_Class_ETH_Get_Info


	DCD __Sys_IRQ_Enable

	DCD __Sys_IRQ_Disable

	DCD __Sys_IRQ_Set_Priority

	DCD __Sys_IRQ_All_Enable

	DCD __Sys_IRQ_All_Disable

	DCD __Sys_IRQ_Register_Hook

	DCD __Sys_IRQ_Delete_Hook




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


	DCD __Sys_Timer_GET_Counter
	DCD __Sys_Timer_Enable
	DCD __Sys_Timer_Disable
	DCD __Sys_Timer_Register
	DCD __Sys_Timer_Register2
	DCD __Sys_Timer_Delete
	DCD __Sys_Timer_Start
	DCD __Sys_Timer_Stop
	DCD __Sys_Timer_Suspend
	DCD __Sys_Timer_Resume
	DCD __Sys_Timer_Reset
	DCD __Sys_Timer_Enabled


	END
