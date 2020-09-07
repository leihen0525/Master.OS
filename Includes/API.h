/*
 * API.h
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */

#ifndef API_H_
#define API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Error.h"
#include "Master.OS.Config.h"
#include "Master.Stdint.h"
#include "Scheduling.Task.Define.h"
#include "IRQ.Define.h"
#include "Timer.Define.h"
#include "Timer.Enum.h"
#include "Event.Enum.h"
#include "Event.Define.h"
#include "MPU.Define.h"
#include "Memory.Struct.h"

int Apply_Handle(void);//申请一个未使用的句柄

//BSP
#ifdef Master_OS_Config_BSP_Wdog_Enable
int BSP_Wdog_Enable(void);
#endif
#ifdef Master_OS_Config_BSP_Wdog_Disable
int BSP_Wdog_Disable(void);
#endif
#ifdef Master_OS_Config_BSP_Wdog_Clear
int BSP_Wdog_Clear(void);
#endif

//Memory
#ifdef Master_OS_Config_Memory_Size_Malloc
uint32_t Memory_Size_Malloc(void);
#endif
#ifdef Master_OS_Config_Memory_Size_Free
uint32_t Memory_Size_Free(void);
#endif
#ifdef Master_OS_Config_Memory_Malloc_Align
void *Memory_Malloc_Align(uint32_t Size,uint32_t Align);
#endif
#ifdef Master_OS_Config_Memory_Malloc
void *Memory_Malloc(uint32_t Size);
#endif
#ifdef Master_OS_Config_Memory_Free
void Memory_Free(void *ap);
#endif
//用户自定义
#ifdef Master_OS_Config_UGC_Memory_Init
int UGC_Memory_Init(
		Memory_DATA_Type *P_Memory_DATA,
		uint8_t *HEAP,
		uint32_t Size);
#endif
#ifdef Master_OS_Config_UGC_Memory_Size_Malloc
uint32_t UGC_Memory_Size_Malloc(Memory_DATA_Type *P_Memory_DATA);
#endif
#ifdef Master_OS_Config_UGC_Memory_Size_Free
uint32_t UGC_Memory_Size_Free(Memory_DATA_Type *P_Memory_DATA);
#endif
#ifdef Master_OS_Config_UGC_Memory_Malloc
void *UGC_Memory_Malloc(Memory_DATA_Type *P_Memory_DATA,uint32_t Size,uint32_t Align);
#endif
#ifdef Master_OS_Config_UGC_Memory_Free
void UGC_Memory_Free(Memory_DATA_Type *P_Memory_DATA,void *ap);
#endif
//Device
#ifdef Master_OS_Config_Device_Open
int Device_Open(const char *Device_Name,int Mode);
#endif
#ifdef Master_OS_Config_Device_Close
int Device_Close(int Handle);
#endif
#ifdef Master_OS_Config_Device_Read
int Device_Read(int Handle,long OffSet_Pos, void *Buffer, unsigned long Size,long TimeOut);
#endif
#ifdef Master_OS_Config_Device_Write
int Device_Write(int Handle,long OffSet_Pos, const void *Buffer, unsigned long Size,long TimeOut);
#endif
#ifdef Master_OS_Config_Device_Control
int Device_Control(int Handle,int Cmd,...);
#endif
#ifdef Master_OS_Config_Device_Info
int Device_Info(int Handle,const char **P_Info);
#endif

//IRQ
#ifdef Master_OS_Config_IRQ_Enable
int IRQ_Enable(int IRQ_Index);
#endif
#ifdef Master_OS_Config_IRQ_Disable
int IRQ_Disable(int IRQ_Index);
#endif
#ifdef Master_OS_Config_IRQ_Set_Priority
int IRQ_Set_Priority(int IRQ_Index,int Priority);
#endif
#ifdef Master_OS_Config_IRQ_All_Enable
int IRQ_All_Enable(void);
#endif
#ifdef Master_OS_Config_IRQ_All_Disable
int IRQ_All_Disable(void);
#endif
#ifdef Master_OS_Config_IRQ_Register_Hook
int IRQ_Register_Hook(int IRQ_Index,IRQ_Hook_Function Hook_Function,void *Args);
#endif
#ifdef Master_OS_Config_IRQ_Delete_Hook
int IRQ_Delete_Hook(int IRQ_Index,int Handle);
#endif
/*
//Power
uint32_t Power_GET_Core_Frequency(void);
uint32_t Power_GET_Bus_Frequency(void);
uint32_t Power_GET_Flash_Frequency(void);
uint32_t Power_GET_External_Frequency(void);
*/

//Scheduling
#ifdef Master_OS_Config_Scheduling_Create_Task
int Scheduling_Create_Task(
		char *Name,
		Task_Enter_Function Task_Enter,
		void *Args,
		uint8_t Priority,
		uint32_t *Stack,
		uint32_t Stack_Size_4Byte,
		int Option);
#endif
#ifdef Master_OS_Config_Scheduling_Release_Task
int Scheduling_Release_Task(int Handle);
#endif
#ifdef Master_OS_Config_Scheduling_Exit_Task
void Scheduling_Exit_Task(void);
#endif
#ifdef Master_OS_Config_Scheduling_Sleep_Task
int Scheduling_Sleep_Task(int32_t TimeOut);
#endif
#ifdef Master_OS_Config_Scheduling_Suspend_Task
int Scheduling_Suspend_Task(int Handle);
#endif
#ifdef Master_OS_Config_Scheduling_Resume_Task
int Scheduling_Resume_Task(int Handle);
#endif

//Event-Event_Flag
#ifdef Master_OS_Config_Event_Flag_Create
int Event_Flag_Create(
		char *Name,
		bool Init_Flag);
#endif
#ifdef Master_OS_Config_Event_Flag_Delete
int Event_Flag_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Event_Flag_Find_Handle
int Event_Flag_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Event_Flag_Wait
int Event_Flag_Wait(
		int Handle,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Clear
int Event_Flag_Clear(int Handle);
#endif
#ifdef Master_OS_Config_Event_Flag_Set
int Event_Flag_Set(int Handle);
#endif

//Event-Event_Flag_Group
#ifdef Master_OS_Config_Event_Flag_Group_Create
int Event_Flag_Group_Create(
		char *Name,
		uint32_t Flag_Group_LEN);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_8bit
int Event_Flag_Group_Create_8bit(char *Name);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_16bit
int Event_Flag_Group_Create_16bit(char *Name);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_32bit
int Event_Flag_Group_Create_32bit(char *Name);
#endif

#ifdef Master_OS_Config_Event_Flag_Group_Delete
int Event_Flag_Group_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Find_Handle
int Event_Flag_Group_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Open
int Event_Flag_Group_Open(int Handle);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Close
int Event_Flag_Group_Close(int Handle);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And
int Event_Flag_Group_Wait_And(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t *Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_8bit
int Event_Flag_Group_Wait_And_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_16bit
int Event_Flag_Group_Wait_And_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT,
		uint16_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint16_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_32bit
int Event_Flag_Group_Wait_And_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT,
		uint32_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint32_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif

#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or
int Event_Flag_Group_Wait_Or(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t *Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_8bit
int Event_Flag_Group_Wait_Or_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_16bit
int Event_Flag_Group_Wait_Or_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT,
		uint16_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint16_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_32bit
int Event_Flag_Group_Wait_Or_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT,
		uint32_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint32_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set
int Event_Flag_Group_Set(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_8bit
int Event_Flag_Group_Set_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_16bit
int Event_Flag_Group_Set_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_32bit
int Event_Flag_Group_Set_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT);
#endif

//Event-FIFO_Queue
#ifdef Master_OS_Config_FIFO_Queue_Create
int FIFO_Queue_Create(
		char *Name,
		uint32_t Max_FIFO_Size,
		uint32_t Max_FIFO_Queue_Length,
		__Sys_Event_FIFO_OverFlow_Function __Sys_OverFlow_Fun,
		void *__Sys_OverFlow_Args);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Delete
int FIFO_Queue_Delete(int Handle);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Find_Handle
int FIFO_Queue_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Open
int FIFO_Queue_Open(int Handle);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Close
int FIFO_Queue_Close(int Handle);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Wait
int FIFO_Queue_Wait(
		int Handle,
		void *Read_FIFO_DATA,
		uint32_t Read_FIFO_Size,
		uint32_t *Return_Read_FIFO_Size,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Clear
int FIFO_Queue_Clear(int Handle);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Set
int FIFO_Queue_Set(
		int Handle,
		void *Set_FIFO_DATA,
		uint32_t Set_FIFO_Size);
#endif

//Event-Message_Queue
#ifdef Master_OS_Config_Message_Queue_Create
int Message_Queue_Create(
		char *Name,
		uint32_t Max_Message_Size,
		uint32_t Max_Message_Queue_Length);
#endif
#ifdef Master_OS_Config_Message_Queue_Delete
int Message_Queue_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Message_Queue_Find_Handle
int Message_Queue_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Message_Queue_Open
int Message_Queue_Open(int Handle);
#endif
#ifdef Master_OS_Config_Message_Queue_Close
int Message_Queue_Close(int Handle);
#endif
#ifdef Master_OS_Config_Message_Queue_Wait
int Message_Queue_Wait(
		int Handle,
		void *Read_Message_DATA,
		uint32_t Read_Message_Size,
		uint32_t *Return_Read_Message_Size,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Message_Queue_Clear
int Message_Queue_Clear(int Handle);
#endif
#ifdef Master_OS_Config_Message_Queue_Set
int Message_Queue_Set(
		int Handle,
		void *Set_Message_DATA,
		uint32_t Set_Message_Size);
#endif

//Event-Mutex
#ifdef Master_OS_Config_Mutex_Create
int Mutex_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type);
#endif
#ifdef Master_OS_Config_Mutex_Delete
int Mutex_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Mutex_Find_Handle
int Mutex_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Mutex_Wait
int Mutex_Wait(
		int Handle,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Mutex_Release
int Mutex_Release(int Handle);
#endif

//Event-Semaphore
#ifdef Master_OS_Config_Semaphore_Create
int Semaphore_Create(
		char *Name,
		uint32_t Init_Count,
		uint32_t MAX_Count,
		Event_Queue_Option_Type Option_Type);
#endif
#ifdef Master_OS_Config_Semaphore_Delete
int Semaphore_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Semaphore_Find_Handle
int Semaphore_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Semaphore_Wait
int Semaphore_Wait(
		int Handle,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Semaphore_Release
int Semaphore_Release(
		int Handle,
		uint32_t Release_Count,
		uint32_t *P_Previous_Count);
#endif

//Event-Semaphore-Group
#ifdef Master_OS_Config_Semaphore_Group_Create
int Semaphore_Group_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type);
#endif
#ifdef Master_OS_Config_Semaphore_Group_Delete
int Semaphore_Group_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Semaphore_Group_Find_Handle
int Semaphore_Group_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Semaphore_Group_Wait
int Semaphore_Group_Wait(
		int Handle,
		bool Monopolize,
		int16_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Semaphore_Group_Release
int Semaphore_Group_Release(
		int Handle,
		bool Monopolize,
		int32_t *P_Previous_Count);
#endif

//Timer
#ifdef Master_OS_Config_Timer_Enable
int Timer_Enable(void);
#endif
#ifdef Master_OS_Config_Timer_Disable
int Timer_Disable(void);
#endif
#ifdef Master_OS_Config_Timer_Register
int Timer_Register(
		Timer_Enter_Function Timer_Function,
		void *Args);
#endif
#ifdef Master_OS_Config_Timer_Delete
int Timer_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Timer_Start
int Timer_Start(
		int Handle,
		int32_t N_Time_Cycle,	//次数
		int32_t Cycle_Time_MS,	//周期
		Timer_Operation_Type Timer_Operation);
#endif
#ifdef Master_OS_Config_Timer_Stop
int Timer_Stop(int Handle);
#endif
#ifdef Master_OS_Config_Timer_Suspend
int Timer_Suspend(int Handle);//暂停
#endif
#ifdef Master_OS_Config_Timer_Resume
int Timer_Resume(int Handle);//恢复
#endif
#ifdef Master_OS_Config_Timer_Reset
int Timer_Reset(int Handle);//复位
#endif
#ifdef Master_OS_Config_Timer_Enabled
int Timer_Enabled(uint8_t Enabled);
#endif

#ifdef __cplusplus
}
#endif

#endif /* API_H_ */
