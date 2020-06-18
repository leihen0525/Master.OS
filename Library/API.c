/*
 * API.c
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */
#include <stdarg.h>

#include "SysCall.h"
#include "SysCall.Table.h"
#include "API.h"

//Memory
#ifdef Master_OS_Config_Memory_Size_Malloc
uint32_t Memory_Size_Malloc(void)
{
	return (uint32_t)SysCall(SysCall_Table_Memory_Size_Malloc);
}
#endif
#ifdef Master_OS_Config_Memory_Size_Free
uint32_t Memory_Size_Free(void)
{
	return (uint32_t)SysCall(SysCall_Table_Memory_Size_Free);
}
#endif
#ifdef Master_OS_Config_Memory_Malloc_Align
void *Memory_Malloc_Align(uint32_t Size,uint32_t Align)
{
	return (void *)SysCall(SysCall_Table_Memory_Malloc_Align,Size,Align);
}
#endif
#ifdef Master_OS_Config_Memory_Malloc
void *Memory_Malloc(uint32_t Size)
{
	return (void *)SysCall(SysCall_Table_Memory_Malloc,Size);
}
#endif
#ifdef Master_OS_Config_Memory_Free
void Memory_Free(void *ap)
{
	SysCall(SysCall_Table_Memory_Free,ap);
}
#endif
//用户自定义
#ifdef Master_OS_Config_UGC_Memory_Init
int UGC_Memory_Init(
		Memory_DATA_Type *P_Memory_DATA,
		uint8_t *HEAP,
		uint32_t Size)
{
	return SysCall(SysCall_Table_UGC_Memory_Init,P_Memory_DATA,HEAP,Size);
}
#endif
#ifdef Master_OS_Config_UGC_Memory_Size_Malloc
uint32_t UGC_Memory_Size_Malloc(Memory_DATA_Type *P_Memory_DATA)
{
	return (uint32_t)SysCall(SysCall_Table_UGC_Memory_Size_Malloc,P_Memory_DATA);
}
#endif
#ifdef Master_OS_Config_UGC_Memory_Size_Free
uint32_t UGC_Memory_Size_Free(Memory_DATA_Type *P_Memory_DATA)
{
	return (uint32_t)SysCall(SysCall_Table_UGC_Memory_Size_Free,P_Memory_DATA);
}
#endif
#ifdef Master_OS_Config_UGC_Memory_Malloc
void *UGC_Memory_Malloc(Memory_DATA_Type *P_Memory_DATA,uint32_t Size,uint32_t Align)
{
	return (void *)SysCall(SysCall_Table_UGC_Memory_Malloc,P_Memory_DATA,Size,Align);
}
#endif
#ifdef Master_OS_Config_UGC_Memory_Free
void UGC_Memory_Free(Memory_DATA_Type *P_Memory_DATA,void *ap)
{
	SysCall(SysCall_Table_UGC_Memory_Free,P_Memory_DATA,ap);
}
#endif
//Device
#ifdef Master_OS_Config_Device_Open
int Device_Open(const char *Device_Name,int Mode)
{
	return SysCall(SysCall_Table_Index_Device_Open,Device_Name,Mode);
}
#endif
#ifdef Master_OS_Config_Device_Close
int Device_Close(int Handle)
{
	return SysCall(SysCall_Table_Index_Device_Close,Handle);
}
#endif
#ifdef Master_OS_Config_Device_Read
int Device_Read(int Handle,long OffSet_Pos, void *Buffer, unsigned long Size,int TimeOut)
{
	return SysCall(SysCall_Table_Index_Device_Read,Handle,OffSet_Pos,Buffer,Size,TimeOut);
}
#endif
#ifdef Master_OS_Config_Device_Write
int Device_Write(int Handle,long OffSet_Pos, const void *Buffer, unsigned long Size,int TimeOut)
{
	return SysCall(SysCall_Table_Index_Device_Write,Handle,OffSet_Pos,Buffer,Size,TimeOut);
}
#endif
#ifdef Master_OS_Config_Device_Control
int Device_Control(int Handle,int Cmd,...)
{
	void *Arg;
	va_list ap;
	va_start (ap, Cmd);
	Arg = va_arg (ap, void *);

	return SysCall(SysCall_Table_Index_Device_Control,Handle,Cmd,Arg);
}
#endif
#ifdef Master_OS_Config_Device_Info
int Device_Info(int Handle,const char **P_Info)
{
	return SysCall(SysCall_Table_Index_Device_Info,Handle,P_Info);
}
#endif

//IRQ
#ifdef Master_OS_Config_IRQ_Enable
int IRQ_Enable(int IRQ_Index)
{
	return SysCall(SysCall_Table_Index_IRQ_Enable,IRQ_Index);
}
#endif
#ifdef Master_OS_Config_IRQ_Disable
int IRQ_Disable(int IRQ_Index)
{
	return SysCall(SysCall_Table_Index_IRQ_Disable,IRQ_Index);
}
#endif
#ifdef Master_OS_Config_IRQ_Set_Priority
int IRQ_Set_Priority(int IRQ_Index,int Priority)
{
	return SysCall(SysCall_Table_Index_IRQ_Set_Priority,IRQ_Index,Priority);
}
#endif
#ifdef Master_OS_Config_IRQ_All_Enable
int IRQ_All_Enable(void)
{
	return SysCall(SysCall_Table_Index_IRQ_All_Enable);
}
#endif
#ifdef Master_OS_Config_IRQ_All_Disable
int IRQ_All_Disable(void)
{
	return SysCall(SysCall_Table_Index_IRQ_All_Disable);
}
#endif
#ifdef Master_OS_Config_IRQ_Register_Hook
int IRQ_Register_Hook(int IRQ_Index,IRQ_Hook_Function Hook_Function,void *Args)
{
	return SysCall(SysCall_Table_Index_IRQ_Register_Hook,IRQ_Index,Hook_Function,Args);
}
#endif
#ifdef Master_OS_Config_IRQ_Delete_Hook
int IRQ_Delete_Hook(int IRQ_Index,int Handle)
{
	return SysCall(SysCall_Table_Index_IRQ_Delete_Hook,IRQ_Index,Handle);
}
#endif
/*
//Power
uint32_t Power_GET_Core_Frequency(void)
{
	return (uint32_t)SysCall(SysCall_Table_Index_Power_GET_Core_Frequency);
}
uint32_t Power_GET_Bus_Frequency(void)
{
	return (uint32_t)SysCall(SysCall_Table_Index_Power_GET_Bus_Frequency);
}
uint32_t Power_GET_Flash_Frequency(void)
{
	return (uint32_t)SysCall(SysCall_Table_Index_Power_GET_Flash_Frequency);
}
uint32_t Power_GET_External_Frequency(void)
{
	return (uint32_t)SysCall(SysCall_Table_Index_Power_GET_External_Frequency);
}
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
		int Option
		)
{
	return SysCall(
			SysCall_Table_Index_Scheduling_Create_Task,
			Name,
			Task_Enter,
			Args,
			Scheduling_Exit_Task,
			Priority,
			Stack,
			Stack_Size_4Byte,
			Option);
}
#endif
#ifdef Master_OS_Config_Scheduling_Release_Task
int Scheduling_Release_Task(int Handle)
{
	return SysCall(SysCall_Table_Index_Scheduling_Release_Task,Handle);
}
#endif
#ifdef Master_OS_Config_Scheduling_Exit_Task
void Scheduling_Exit_Task(void)
{
	Scheduling_Release_Task(0);
}
#endif
#ifdef Master_OS_Config_Scheduling_Sleep_Task
int Scheduling_Sleep_Task(int32_t TimeOut)
{
	return SysCall(SysCall_Table_Index_Scheduling_Sleep_Task,TimeOut);
}
#endif
#ifdef Master_OS_Config_Scheduling_Suspend_Task
int Scheduling_Suspend_Task(int Handle)
{
	return SysCall(SysCall_Table_Index_Scheduling_Suspend_Task,Handle);
}
#endif
#ifdef Master_OS_Config_Scheduling_Resume_Task
int Scheduling_Resume_Task(int Handle)
{
	return SysCall(SysCall_Table_Index_Scheduling_Resume_Task,Handle);
}
#endif

//Event-Event_Flag
#ifdef Master_OS_Config_Event_Flag_Create
int Event_Flag_Create(
		char *Name,
		bool Init_Flag)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Create,Name,Init_Flag);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Delete
int Event_Flag_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Delete,Handle);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Find_Handle
int Event_Flag_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Find_Handle,Name);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Wait
int Event_Flag_Wait(
		int Handle,
		int32_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Wait,Handle,Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Clear
int Event_Flag_Clear(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Clear,Handle);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Set
int Event_Flag_Set(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Set,Handle);
}
#endif

//Event-Event_Flag_Group
#ifdef Master_OS_Config_Event_Flag_Group_Create
int Event_Flag_Group_Create(
		char *Name,
		uint32_t Flag_Group_LEN)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Create,Name,Flag_Group_LEN);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_8bit
int Event_Flag_Group_Create_8bit(char *Name)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Create,Name,sizeof(uint8_t));
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_16bit
int Event_Flag_Group_Create_16bit(char *Name)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Create,Name,sizeof(uint16_t));
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_32bit
int Event_Flag_Group_Create_32bit(char *Name)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Create,Name,sizeof(uint32_t));
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Delete
int Event_Flag_Group_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Delete,Handle);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Find_Handle
int Event_Flag_Group_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Find_Handle,Name);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Open
int Event_Flag_Group_Open(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Open,Handle);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Close
int Event_Flag_Group_Close(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Close,Handle);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And
int Event_Flag_Group_Wait_And(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t *Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return SysCall(
				SysCall_Table_Index_Event_Flag_Group_Wait_And,
				Handle,
				Event_Flag_Group_Mask,
				Event_Flag_Group_BIT,
				Read_Event_Flag_Group,
				Clear_Type,
				Event_Flag_Group_Clear_BIT,
				Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_8bit
int Event_Flag_Group_Wait_And_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return SysCall(
				SysCall_Table_Index_Event_Flag_Group_Wait_And,
				Handle,
				(uint8_t *)&Event_Flag_Group_Mask,
				(uint8_t *)&Event_Flag_Group_BIT,
				(uint8_t *)Read_Event_Flag_Group,
				Clear_Type,
				(uint8_t *)&Event_Flag_Group_Clear_BIT,
				Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_16bit
int Event_Flag_Group_Wait_And_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT,
		uint16_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint16_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return SysCall(
				SysCall_Table_Index_Event_Flag_Group_Wait_And,
				Handle,
				(uint8_t *)&Event_Flag_Group_Mask,
				(uint8_t *)&Event_Flag_Group_BIT,
				(uint8_t *)Read_Event_Flag_Group,
				Clear_Type,
				(uint8_t *)&Event_Flag_Group_Clear_BIT,
				Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_32bit
int Event_Flag_Group_Wait_And_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT,
		uint32_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint32_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return SysCall(
				SysCall_Table_Index_Event_Flag_Group_Wait_And,
				Handle,
				(uint8_t *)&Event_Flag_Group_Mask,
				(uint8_t *)&Event_Flag_Group_BIT,
				(uint8_t *)Read_Event_Flag_Group,
				Clear_Type,
				(uint8_t *)&Event_Flag_Group_Clear_BIT,
				Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or
int Event_Flag_Group_Wait_Or(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t *Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return SysCall(
				SysCall_Table_Index_Event_Flag_Group_Wait_Or,
				Handle,
				Event_Flag_Group_Mask,
				Event_Flag_Group_BIT,
				Read_Event_Flag_Group,
				Clear_Type,
				Event_Flag_Group_Clear_BIT,
				Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_8bit
int Event_Flag_Group_Wait_Or_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return SysCall(
			SysCall_Table_Index_Event_Flag_Group_Wait_Or,
				Handle,
				(uint8_t *)&Event_Flag_Group_Mask,
				(uint8_t *)&Event_Flag_Group_BIT,
				(uint8_t *)Read_Event_Flag_Group,
				Clear_Type,
				(uint8_t *)&Event_Flag_Group_Clear_BIT,
				Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_16bit
int Event_Flag_Group_Wait_Or_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT,
		uint16_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint16_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return SysCall(
			SysCall_Table_Index_Event_Flag_Group_Wait_Or,
				Handle,
				(uint8_t *)&Event_Flag_Group_Mask,
				(uint8_t *)&Event_Flag_Group_BIT,
				(uint8_t *)Read_Event_Flag_Group,
				Clear_Type,
				(uint8_t *)&Event_Flag_Group_Clear_BIT,
				Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_32bit
int Event_Flag_Group_Wait_Or_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT,
		uint32_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint32_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return SysCall(
			SysCall_Table_Index_Event_Flag_Group_Wait_Or,
				Handle,
				(uint8_t *)&Event_Flag_Group_Mask,
				(uint8_t *)&Event_Flag_Group_BIT,
				(uint8_t *)Read_Event_Flag_Group,
				Clear_Type,
				(uint8_t *)&Event_Flag_Group_Clear_BIT,
				Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set
int Event_Flag_Group_Set(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT)
{
	return SysCall(
				SysCall_Table_Index_Event_Flag_Group_Set,
				Handle,
				Event_Flag_Group_Mask,
				Event_Flag_Group_BIT);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_8bit
int Event_Flag_Group_Set_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT)
{
	return SysCall(
				SysCall_Table_Index_Event_Flag_Group_Set,
				Handle,
				(uint8_t *)&Event_Flag_Group_Mask,
				(uint8_t *)&Event_Flag_Group_BIT);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_16bit
int Event_Flag_Group_Set_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT)
{
	return SysCall(
				SysCall_Table_Index_Event_Flag_Group_Set,
				Handle,
				(uint8_t *)&Event_Flag_Group_Mask,
				(uint8_t *)&Event_Flag_Group_BIT);
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_32bit
int Event_Flag_Group_Set_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT)
{
	return SysCall(
				SysCall_Table_Index_Event_Flag_Group_Set,
				Handle,
				(uint8_t *)&Event_Flag_Group_Mask,
				(uint8_t *)&Event_Flag_Group_BIT);
}
#endif

//Event-FIFO_Queue
#ifdef Master_OS_Config_FIFO_Queue_Create
int FIFO_Queue_Create(
		char *Name,
		uint32_t Max_FIFO_Size,
		uint32_t Max_FIFO_Queue_Length,
		__Sys_Event_FIFO_OverFlow_Function __Sys_OverFlow_Fun,
		void *__Sys_OverFlow_Args)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Create,Name,Max_FIFO_Size,Max_FIFO_Queue_Length,__Sys_OverFlow_Fun,__Sys_OverFlow_Args);
}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Delete
int FIFO_Queue_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Delete,Handle);
}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Find_Handle
int FIFO_Queue_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Find_Handle,Name);
}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Open
int FIFO_Queue_Open(int Handle)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Open,Handle);
}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Close
int FIFO_Queue_Close(int Handle)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Close,Handle);
}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Wait
int FIFO_Queue_Wait(
		int Handle,
		void *Read_FIFO_DATA,
		uint32_t Read_FIFO_Size,
		uint32_t *Return_Read_FIFO_Size,
		int32_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Wait,Handle,Read_FIFO_DATA,Read_FIFO_Size,Return_Read_FIFO_Size,Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Clear
int FIFO_Queue_Clear(int Handle)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Clear,Handle);
}
#endif
#ifdef Master_OS_Config_FIFO_Queue_Set
int FIFO_Queue_Set(
		int Handle,
		void *Set_FIFO_DATA,
		uint32_t Set_FIFO_Size)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Set,Handle,Set_FIFO_DATA,Set_FIFO_Size);
}
#endif

//Event-Message_Queue
#ifdef Master_OS_Config_Message_Queue_Create
int Message_Queue_Create(
		char *Name,
		uint32_t Max_Message_Size,
		uint32_t Max_Message_Queue_Length)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Create,Name,Max_Message_Size,Max_Message_Queue_Length);
}
#endif
#ifdef Master_OS_Config_Message_Queue_Delete
int Message_Queue_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Delete,Handle);
}
#endif
#ifdef Master_OS_Config_Message_Queue_Find_Handle
int Message_Queue_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Find_Handle,Name);
}
#endif
#ifdef Master_OS_Config_Message_Queue_Open
int Message_Queue_Open(int Handle)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Open,Handle);
}
#endif
#ifdef Master_OS_Config_Message_Queue_Close
int Message_Queue_Close(int Handle)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Close,Handle);
}
#endif
#ifdef Master_OS_Config_Message_Queue_Wait
int Message_Queue_Wait(
		int Handle,
		void *Read_Message_DATA,
		uint32_t Read_Message_Size,
		uint32_t *Return_Read_Message_Size,
		int32_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Wait,Handle,Read_Message_DATA,Read_Message_Size,Return_Read_Message_Size,Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Message_Queue_Clear
int Message_Queue_Clear(int Handle)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Clear,Handle);
}
#endif
#ifdef Master_OS_Config_Message_Queue_Set
int Message_Queue_Set(
		int Handle,
		void *Set_Message_DATA,
		uint32_t Set_Message_Size)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Set,Handle,Set_Message_DATA,Set_Message_Size);
}
#endif

//Event-Mutex
#ifdef Master_OS_Config_Mutex_Create
int Mutex_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type)
{
	return SysCall(SysCall_Table_Index_Mutex_Create,Name,Option_Type);
}
#endif
#ifdef Master_OS_Config_Mutex_Delete
int Mutex_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Mutex_Delete,Handle);
}
#endif
#ifdef Master_OS_Config_Mutex_Find_Handle
int Mutex_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Mutex_Find_Handle,Name);
}
#endif
#ifdef Master_OS_Config_Mutex_Wait
int Mutex_Wait(
		int Handle,
		int32_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_Mutex_Wait,Handle,Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Mutex_Release
int Mutex_Release(int Handle)
{
	return SysCall(SysCall_Table_Index_Mutex_Release,Handle);
}
#endif

//Event-Semaphore
#ifdef Master_OS_Config_Semaphore_Create
int Semaphore_Create(
		char *Name,
		uint32_t Init_Count,
		uint32_t MAX_Count,
		Event_Queue_Option_Type Option_Type)
{
	return SysCall(SysCall_Table_Index_Semaphore_Create,Name,Init_Count,MAX_Count,Option_Type);
}
#endif
#ifdef Master_OS_Config_Semaphore_Delete
int Semaphore_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Semaphore_Delete,Handle);
}
#endif
#ifdef Master_OS_Config_Semaphore_Find_Handle
int Semaphore_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Semaphore_Find_Handle,Name);
}
#endif
#ifdef Master_OS_Config_Semaphore_Wait
int Semaphore_Wait(
		int Handle,
		int32_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_Semaphore_Wait,Handle,Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Semaphore_Release
int Semaphore_Release(
		int Handle,
		uint32_t Release_Count,
		uint32_t *P_Previous_Count)
{
	return SysCall(SysCall_Table_Index_Semaphore_Release,Handle,Release_Count,P_Previous_Count);
}
#endif

//Event-Group
#ifdef Master_OS_Config_Semaphore_Group_Create
int Semaphore_Group_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type)
{
	return SysCall(SysCall_Table_Index_Semaphore_Group_Create,Name,Option_Type);
}
#endif
#ifdef Master_OS_Config_Semaphore_Group_Delete
int Semaphore_Group_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Semaphore_Group_Delete,Handle);
}
#endif
#ifdef Master_OS_Config_Semaphore_Group_Find_Handle
int Semaphore_Group_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Semaphore_Group_Find_Handle,Name);
}
#endif
#ifdef Master_OS_Config_Semaphore_Group_Wait
int Semaphore_Group_Wait(
		int Handle,
		bool Monopolize,
		int16_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_Semaphore_Group_Wait,Handle,Monopolize,Time_Out_MS);
}
#endif
#ifdef Master_OS_Config_Semaphore_Group_Release
int Semaphore_Group_Release(
		int Handle,
		bool Monopolize,
		int32_t *P_Previous_Count)
{
	return SysCall(SysCall_Table_Index_Semaphore_Group_Release,Handle,Monopolize,P_Previous_Count);
}
#endif

//Timer
#ifdef Master_OS_Config_Timer_Enable
int Timer_Enable(void)
{
	return SysCall(SysCall_Table_Index_Timer_Enable);
}
#endif
#ifdef Master_OS_Config_Timer_Disable
int Timer_Disable(void)
{
	return SysCall(SysCall_Table_Index_Timer_Disable);
}
#endif
#ifdef Master_OS_Config_Timer_Register
int Timer_Register(
		Timer_Enter_Function Timer_Function,
		void *Args)
{
	return SysCall(SysCall_Table_Index_Timer_Register,Timer_Function,Args);
}
#endif
#ifdef Master_OS_Config_Timer_Delete
int Timer_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Timer_Delete,Handle);
}
#endif
#ifdef Master_OS_Config_Timer_Start
int Timer_Start(
		int Handle,
		int32_t N_Time_Cycle,	//次数
		int32_t Cycle_Time_MS,	//周期
		Timer_Operation_Type Timer_Operation)
{
	return SysCall(SysCall_Table_Index_Timer_Start,Handle,N_Time_Cycle,Cycle_Time_MS,Timer_Operation);
}
#endif
#ifdef Master_OS_Config_Timer_Stop
int Timer_Stop(int Handle)
{
	return SysCall(SysCall_Table_Index_Timer_Stop,Handle);
}
#endif
#ifdef Master_OS_Config_Timer_Suspend
int Timer_Suspend(int Handle)//暂停
{
	return SysCall(SysCall_Table_Index_Timer_Suspend,Handle);
}
#endif
#ifdef Master_OS_Config_Timer_Resume
int Timer_Resume(int Handle)//恢复
{
	return SysCall(SysCall_Table_Index_Timer_Resume,Handle);
}
#endif
#ifdef Master_OS_Config_Timer_Reset
int Timer_Reset(int Handle)//复位
{
	return SysCall(SysCall_Table_Index_Timer_Reset,Handle);
}
#endif
#ifdef Master_OS_Config_Timer_Enabled
int Timer_Enabled(uint8_t Enabled)
{
	return SysCall(SysCall_Table_Index_Timer_Enabled,Enabled);
}
#endif
