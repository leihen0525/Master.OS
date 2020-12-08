/*
 * __Sys.API.h
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */

#ifndef __SYS_API_H_
#define __SYS_API_H_

#ifdef __cplusplus
extern "C" {
#endif

//#include "Master.OS.Config.h"
#include "Master.Stdint.h"
#include "Scheduling.Task.Enum.h"
#include "Scheduling.Task.Define.h"
#include "__Sys.Scheduling.Task.Struct.h"
#include "IRQ.Define.h"
#include "Event.Enum.h"
#include "Timer.Define.h"
#include "Timer.Enum.h"
#include "Event.Define.h"

int __Sys_Apply_Handle(void);

//BSP
int __Sys_BSP_UpData_Clock_Tree(
		void **Clock_Source,
		void **Clock_Tree);
#ifdef Master_OS_Config_BSP_System_Reset
int __Sys_BSP_System_Reset(void);
#endif
#ifdef Master_OS_Config_BSP_Wdog_Enable
int __Sys_BSP_Wdog_Enable(void);
#endif
#ifdef Master_OS_Config_BSP_Wdog_Disable
int __Sys_BSP_Wdog_Disable(void);
#endif
#ifdef Master_OS_Config_BSP_Wdog_Refresh
int __Sys_BSP_Wdog_Refresh(void);
#endif

//Memory
#ifdef Master_OS_Config_Memory_Size_Malloc
uint32_t __Sys_Memory_Size_Malloc(void);
#endif
#ifdef Master_OS_Config_Memory_Size_Free
uint32_t __Sys_Memory_Size_Free(void);
#endif
#ifdef Master_OS_Config_Memory_Malloc_Align
void *__Sys_Memory_Malloc_Align(uint32_t Size,uint32_t Align);
#endif
#ifdef Master_OS_Config_Memory_Malloc
void *__Sys_Memory_Malloc(uint32_t Size);
#endif
#ifdef Master_OS_Config_Memory_Free
void __Sys_Memory_Free(void *ap);
#endif

//IRQ
#ifdef Master_OS_Config_IRQ_Enable
int __Sys_IRQ_Enable(int IRQ_Index);
#endif
#ifdef Master_OS_Config_IRQ_Disable
int __Sys_IRQ_Disable(int IRQ_Index);
#endif
#ifdef Master_OS_Config_IRQ_Set_Priority
int __Sys_IRQ_Set_Priority(int IRQ_Index,int Priority);
#endif
#ifdef Master_OS_Config_IRQ_All_Enable
int __Sys_IRQ_All_Enable(void);
#endif
#ifdef Master_OS_Config_IRQ_All_Disable
int __Sys_IRQ_All_Disable(void);
#endif
#ifdef Master_OS_Config_IRQ_Register_Hook
int __Sys_IRQ_Register_Hook(int IRQ_Index,IRQ_Hook_Function Hook_Function,void *Args);
#endif
#ifdef Master_OS_Config_IRQ_Delete_Hook
int __Sys_IRQ_Delete_Hook(int IRQ_Index,int Handle);
#endif

//Device
#ifdef Master_OS_Config_Device_Open
int __Sys_Device_Open(const char *Device_Name,int Mode);
#endif
#ifdef Master_OS_Config_Device_Close
int __Sys_Device_Close(int Handle);
#endif
#ifdef Master_OS_Config_Device_Read
int __Sys_Device_Read(int Handle,long OffSet_Pos, void *Buffer, unsigned long Size,long TimeOut);
#endif
#ifdef Master_OS_Config_Device_Write
int __Sys_Device_Write(int Handle,long OffSet_Pos, const void *Buffer, unsigned long Size,long TimeOut);
#endif
#ifdef Master_OS_Config_Device_Control
int __Sys_Device_Control(int Handle,int Cmd, unsigned long Args);
#endif
#ifdef Master_OS_Config_Device_Info
int __Sys_Device_Info(int Handle,const char **P_Info);
#endif
/*
//Power
uint32_t __Sys_Power_GET_Core_Frequency(void);
uint32_t __Sys_Power_GET_Bus_Frequency(void);
uint32_t __Sys_Power_GET_Flash_Frequency(void);
uint32_t __Sys_Power_GET_External_Frequency(void);
*/

//Context_Switch

void __Sys_SET_CPU_SP(uint32_t Mode,uint32_t *SP);


#ifdef __UsrSP_SysSP__
void __Sys_Switch_To_Idle(uint32_t *Usr_SP_End,uint32_t *Usr_SP_Begin,Task_Enter_Function Task_Enter,uint32_t *Sys_SP_End);
#else
void __Sys_Switch_To_Idle(uint32_t *Usr_SP_End,uint32_t *Usr_SP_Begin,Task_Enter_Function Task_Enter);
#endif


#ifdef __UsrSP_SysSP__
void __Sys_Switch_To(uint32_t **Cur_TCB_Sys_SP,uint32_t **NEXT_TCB_Sys_SP,uint32_t **Cur_TCB_Usr_SP,uint32_t **NEXT_TCB_Usr_SP);
#else
void __Sys_Switch_To(uint32_t **Cur_TCB_SP,uint32_t **NEXT_TCB_SP);
#endif



//Scheduling
#ifdef Master_OS_Config_Scheduling_Create_Task
int __Sys_Scheduling_Create_Task(
		char *Name,
		Task_Enter_Function Task_Enter,
		void *Args,

		Task_Exit_Function Task_Exit,

		uint8_t Priority,
		uint32_t *Stack,
		uint32_t Stack_Size_4Byte,
		int Option
	);
#endif
#ifdef Master_OS_Config_Scheduling_Release_Task
int __Sys_Scheduling_Release_Task(int Handle);
#endif
#ifdef Master_OS_Config_Scheduling_Sleep_Task
int __Sys_Scheduling_Sleep_Task(int32_t TimeOut);
#endif
#ifdef Master_OS_Config_Scheduling_Suspend_Task
int __Sys_Scheduling_Suspend_Task(int Handle);
#endif
#ifdef Master_OS_Config_Scheduling_Resume_Task
int __Sys_Scheduling_Resume_Task(int Handle);
#endif

void __Sys_Scheduling_Try_Context_Switch(void);
int __Sys_Scheduling_Context_Switch(Task_State_Type CS_Task_State,int32_t TimeOut,int32_t *RTimeOut);
int __Sys_Scheduling_GET_Current_TCB(__Sys_Scheduling_Task_TCB_Type **Current_TCB);

//Event-Event_Flag
#ifdef Master_OS_Config_Event_Flag_Create
int __Sys_Event_Flag_Create(
		char *Name,
		bool Init_Flag);
#endif
#ifdef Master_OS_Config_Event_Flag_Delete
int __Sys_Event_Flag_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Event_Flag_Find_Handle
int __Sys_Event_Flag_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Event_Flag_Wait
int __Sys_Event_Flag_Wait(
		int Handle,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Clear
int __Sys_Event_Flag_Clear(int Handle);
#endif
#ifdef Master_OS_Config_Event_Flag_Set
int __Sys_Event_Flag_Set(int Handle);
#endif

//Event-Event_Flag_Group
#if (defined(Master_OS_Config_Event_Flag_Group_Create) || defined(Master_OS_Config_Event_Flag_Group_Create_8bit) || defined(Master_OS_Config_Event_Flag_Group_Create_16bit) || defined(Master_OS_Config_Event_Flag_Group_Create_32bit))
int __Sys_Event_Flag_Group_Create(
		char *Name,
		uint32_t Flag_Group_LEN);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_8bit
int __Sys_Event_Flag_Group_Create_8bit(char *Name);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_16bit
int __Sys_Event_Flag_Group_Create_16bit(char *Name);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_32bit
int __Sys_Event_Flag_Group_Create_32bit(char *Name);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Delete
int __Sys_Event_Flag_Group_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Find_Handle
int __Sys_Event_Flag_Group_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Open
int __Sys_Event_Flag_Group_Open(int Handle);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Close
int __Sys_Event_Flag_Group_Close(int Handle);
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Wait_And) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_8bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_16bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_And_32bit))
int __Sys_Event_Flag_Group_Wait_And(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t *Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_8bit
int __Sys_Event_Flag_Group_Wait_And_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_16bit
int __Sys_Event_Flag_Group_Wait_And_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT,
		uint16_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint16_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_32bit
int __Sys_Event_Flag_Group_Wait_And_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT,
		uint32_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint32_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Wait_Or) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_8bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_16bit) || defined(Master_OS_Config_Event_Flag_Group_Wait_Or_32bit))
int __Sys_Event_Flag_Group_Wait_Or(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t *Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_8bit
int __Sys_Event_Flag_Group_Wait_Or_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_16bit
int __Sys_Event_Flag_Group_Wait_Or_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT,
		uint16_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint16_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_32bit
int __Sys_Event_Flag_Group_Wait_Or_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT,
		uint32_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint32_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);
#endif
#if (defined(Master_OS_Config_Event_Flag_Group_Set) || defined(Master_OS_Config_Event_Flag_Group_Set_8bit) || defined(Master_OS_Config_Event_Flag_Group_Set_16bit) || defined(Master_OS_Config_Event_Flag_Group_Set_32bit))
int __Sys_Event_Flag_Group_Set(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_8bit
int __Sys_Event_Flag_Group_Set_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_16bit
int __Sys_Event_Flag_Group_Set_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT);
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_32bit
int __Sys_Event_Flag_Group_Set_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT);
#endif

//Event-FIFO_Queue
#ifdef Master_OS_Config_FIFO_Queue_Create
int __Sys_FIFO_Queue_Create(
		char *Name,
		uint32_t Max_FIFO_Size,
		uint32_t Max_FIFO_Queue_Length,
		__Sys_Event_FIFO_OverFlow_Function __Sys_OverFlow_Fun,
		void *__Sys_OverFlow_Args);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Delete
int __Sys_FIFO_Queue_Delete(int Handle);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Find_Handle
int __Sys_FIFO_Queue_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Open
int __Sys_FIFO_Queue_Open(int Handle);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Close
int __Sys_FIFO_Queue_Close(int Handle);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Wait
int __Sys_FIFO_Queue_Wait(
		int Handle,
		void *Read_FIFO_DATA,
		uint32_t Read_FIFO_Size,
		uint32_t *Return_Read_FIFO_Size,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Clear
int __Sys_FIFO_Queue_Clear(int Handle);
#endif
#ifdef Master_OS_Config_FIFO_Queue_Set
int __Sys_FIFO_Queue_Set(
		int Handle,
		void *Set_FIFO_DATA,
		uint32_t Set_FIFO_Size);
#endif

//Event-Message_Queue
#ifdef Master_OS_Config_Message_Queue_Create
int __Sys_Message_Queue_Create(
		char *Name,
		uint32_t Max_Message_Size,
		uint32_t Max_Message_Queue_Length);
#endif
#ifdef Master_OS_Config_Message_Queue_Delete
int __Sys_Message_Queue_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Message_Queue_Find_Handle
int __Sys_Message_Queue_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Message_Queue_Open
int __Sys_Message_Queue_Open(int Handle);
#endif
#ifdef Master_OS_Config_Message_Queue_Close
int __Sys_Message_Queue_Close(int Handle);
#endif
#ifdef Master_OS_Config_Message_Queue_Wait
int __Sys_Message_Queue_Wait(
		int Handle,
		void *Read_Message_DATA,
		uint32_t Read_Message_Size,
		uint32_t *Return_Read_Message_Size,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Message_Queue_Clear
int __Sys_Message_Queue_Clear(int Handle);
#endif
#ifdef Master_OS_Config_Message_Queue_Set
int __Sys_Message_Queue_Set(
		int Handle,
		void *Set_Message_DATA,
		uint32_t Set_Message_Size);
#endif

//Event-Mutex
#ifdef Master_OS_Config_Mutex_Create
int __Sys_Mutex_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type);
#endif
#ifdef Master_OS_Config_Mutex_Delete
int __Sys_Mutex_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Mutex_Find_Handle
int __Sys_Mutex_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Mutex_Wait
int __Sys_Mutex_Wait(
		int Handle,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Mutex_Release
int __Sys_Mutex_Release(int Handle);
#endif

//Event-Semaphore
#ifdef Master_OS_Config_Semaphore_Create
int __Sys_Semaphore_Create(
		char *Name,
		uint32_t Init_Count,
		uint32_t MAX_Count,
		Event_Queue_Option_Type Option_Type);
#endif
#ifdef Master_OS_Config_Semaphore_Delete
int __Sys_Semaphore_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Semaphore_Find_Handle
int __Sys_Semaphore_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Semaphore_Wait
int __Sys_Semaphore_Wait(
		int Handle,
		int32_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Semaphore_Release
int __Sys_Semaphore_Release(
		int Handle,
		uint32_t Release_Count,
		uint32_t *P_Previous_Count);
#endif

//Event-Semaphore-Group
#ifdef Master_OS_Config_Semaphore_Group_Create
int __Sys_Semaphore_Group_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type);
#endif
#ifdef Master_OS_Config_Semaphore_Group_Delete
int __Sys_Semaphore_Group_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Semaphore_Group_Find_Handle
int __Sys_Semaphore_Group_Find_Handle(char *Name);
#endif
#ifdef Master_OS_Config_Semaphore_Group_Wait
int __Sys_Semaphore_Group_Wait(
		int Handle,
		bool Monopolize,
		int16_t Time_Out_MS);
#endif
#ifdef Master_OS_Config_Semaphore_Group_Release
int __Sys_Semaphore_Group_Release(
		int Handle,
		bool Monopolize,
		int32_t *P_Previous_Count);
#endif

//Timer
int __Sys_Timer_GET_Counter(uint64_t *Counter_MS);
#ifdef Master_OS_Config_Timer_Enable
int __Sys_Timer_Enable(void);
#endif
#ifdef Master_OS_Config_Timer_Disable
int __Sys_Timer_Disable(void);
#endif
#ifdef Master_OS_Config_Timer_Register
int __Sys_Timer_Register(
		Timer_Enter_Function Timer_Function,
		void *Args);
#endif
#ifdef Master_OS_Config_Timer_Delete
int __Sys_Timer_Delete(int Handle);
#endif
#ifdef Master_OS_Config_Timer_Start
int __Sys_Timer_Start(
		int Handle,
		int32_t N_Time_Cycle,	//次数
		int32_t Cycle_Time_MS,	//周期
		Timer_Operation_Type Timer_Operation);
#endif
#ifdef Master_OS_Config_Timer_Stop
int __Sys_Timer_Stop(int Handle);
#endif
#ifdef Master_OS_Config_Timer_Suspend
int __Sys_Timer_Suspend(int Handle);//暂停
#endif
#ifdef Master_OS_Config_Timer_Resume
int __Sys_Timer_Resume(int Handle);//恢复
#endif
#ifdef Master_OS_Config_Timer_Reset
int __Sys_Timer_Reset(int Handle);//复位
#endif
#ifdef Master_OS_Config_Timer_Enabled
int __Sys_Timer_Enabled(uint8_t Enabled);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __SYS_API_H_ */
