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
uint32_t Memory_Size(void)
{
	return (uint32_t)SysCall(SysCall_Table_Memory_Size);
}
void *Memory_Malloc(unsigned int Size)
{
	return (void *)SysCall(SysCall_Table_Memory_Malloc,Size);
}
void Memory_Free(void *ap)
{
	SysCall(SysCall_Table_Memory_Free,ap);
}

//Device
int Device_Open(const char *Device_Name,int Mode)
{
	return SysCall(SysCall_Table_Index_Device_Open,Device_Name,Mode);
}
int Device_Close(int Handle)
{
	return SysCall(SysCall_Table_Index_Device_Close,Handle);
}
int Device_Read(int Handle,long OffSet_Pos, void *Buffer, unsigned long Size,int TimeOut)
{
	return SysCall(SysCall_Table_Index_Device_Read,Handle,OffSet_Pos,Buffer,Size,TimeOut);
}
int Device_Write(int Handle,long OffSet_Pos, const void *Buffer, unsigned long Size,int TimeOut)
{
	return SysCall(SysCall_Table_Index_Device_Write,Handle,OffSet_Pos,Buffer,Size,TimeOut);
}
int Device_Control(int Handle,int Cmd,...)
{
	void *Arg;
	va_list ap;
	va_start (ap, Cmd);
	Arg = va_arg (ap, void *);

	return SysCall(SysCall_Table_Index_Device_Control,Handle,Cmd,Arg);
}
int Device_Info(int Handle,const char **P_Info)
{
	return SysCall(SysCall_Table_Index_Device_Info,Handle,P_Info);
}

//IRQ
int IRQ_Enable(int IRQ_Index)
{
	return SysCall(SysCall_Table_Index_IRQ_Enable,IRQ_Index);
}
int IRQ_Disable(int IRQ_Index)
{
	return SysCall(SysCall_Table_Index_IRQ_Disable,IRQ_Index);
}
int IRQ_Set_Priority(int IRQ_Index,int Priority)
{
	return SysCall(SysCall_Table_Index_IRQ_Set_Priority,IRQ_Index,Priority);
}
int IRQ_All_Enable(void)
{
	return SysCall(SysCall_Table_Index_IRQ_All_Enable);
}
int IRQ_All_Disable(void)
{
	return SysCall(SysCall_Table_Index_IRQ_All_Enable);
}
int IRQ_Register_Hook(int IRQ_Index,IRQ_Hook_Function Hook_Function,void *Args)
{
	return SysCall(SysCall_Table_Index_IRQ_Register_Hook,IRQ_Index,Hook_Function,Args);
}
int IRQ_Delete_Hook(int IRQ_Index,int Handle)
{
	return SysCall(SysCall_Table_Index_IRQ_Delete_Hook,IRQ_Index,Handle);
}

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
int Scheduling_Release_Task(int Handle)
{
	return SysCall(SysCall_Table_Index_Scheduling_Release_Task,Handle);
}
void Scheduling_Exit_Task(void)
{
	Scheduling_Release_Task(0);
}
int Scheduling_Sleep_Task(int32_t TimeOut)
{
	return SysCall(SysCall_Table_Index_Scheduling_Sleep_Task,TimeOut);
}
int Scheduling_Suspend_Task(int Handle)
{
	return SysCall(SysCall_Table_Index_Scheduling_Suspend_Task,Handle);
}
int Scheduling_Resume_Task(int Handle)
{
	return SysCall(SysCall_Table_Index_Scheduling_Resume_Task,Handle);
}

//Event-Event_Flag
int Event_Flag_Create(
		char *Name,
		bool Init_Flag)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Create,Name,Init_Flag);
}
int Event_Flag_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Delete,Handle);
}
int Event_Flag_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Find_Handle,Name);
}
int Event_Flag_Wait(
		int Handle,
		int32_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Wait,Handle,Time_Out_MS);
}
int Event_Flag_Clear(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Clear,Handle);
}
int Event_Flag_Set(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Set,Handle);
}

//Event-Event_Flag_Group
int Event_Flag_Group_Create(
		char *Name,
		uint32_t Flag_Group_LEN)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Create,Name,Flag_Group_LEN);
}

int Event_Flag_Group_Create_8bit(char *Name)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Create,Name,sizeof(uint8_t));
}
int Event_Flag_Group_Create_16bit(char *Name)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Create,Name,sizeof(uint16_t));
}
int Event_Flag_Group_Create_32bit(char *Name)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Create,Name,sizeof(uint32_t));
}

int Event_Flag_Group_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Delete,Handle);
}
int Event_Flag_Group_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Find_Handle,Name);
}
int Event_Flag_Group_Open(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Open,Handle);
}
int Event_Flag_Group_Close(int Handle)
{
	return SysCall(SysCall_Table_Index_Event_Flag_Group_Close,Handle);
}

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

//Event-FIFO_Queue
int FIFO_Queue_Create(
		char *Name,
		uint32_t Max_FIFO_Size,
		uint32_t Max_FIFO_Queue_Length,
		__Sys_Event_FIFO_OverFlow_Function __Sys_OverFlow_Fun,
		void *__Sys_OverFlow_Args)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Create,Name,Max_FIFO_Size,Max_FIFO_Queue_Length,__Sys_OverFlow_Fun,__Sys_OverFlow_Args);
}
int FIFO_Queue_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Delete,Handle);
}
int FIFO_Queue_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Find_Handle,Name);
}
int FIFO_Queue_Open(int Handle)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Open,Handle);
}
int FIFO_Queue_Close(int Handle)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Close,Handle);
}
int FIFO_Queue_Wait(
		int Handle,
		void *Read_FIFO_DATA,
		uint32_t Read_FIFO_Size,
		uint32_t *Return_Read_FIFO_Size,
		int32_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Wait,Handle,Read_FIFO_DATA,Read_FIFO_Size,Return_Read_FIFO_Size,Time_Out_MS);
}
int FIFO_Queue_Clear(int Handle)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Clear,Handle);
}
int FIFO_Queue_Set(
		int Handle,
		void *Set_FIFO_DATA,
		uint32_t Set_FIFO_Size)
{
	return SysCall(SysCall_Table_Index_FIFO_Queue_Set,Handle,Set_FIFO_DATA,Set_FIFO_Size);
}

//Event-Message_Queue
int Message_Queue_Create(
		char *Name,
		uint32_t Max_Message_Size,
		uint32_t Max_Message_Queue_Length)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Create,Name,Max_Message_Size,Max_Message_Queue_Length);
}
int Message_Queue_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Delete,Handle);
}
int Message_Queue_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Find_Handle,Name);
}
int Message_Queue_Open(int Handle)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Open,Handle);
}
int Message_Queue_Close(int Handle)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Close,Handle);
}
int Message_Queue_Wait(
		int Handle,
		void *Read_Message_DATA,
		uint32_t Read_Message_Size,
		uint32_t *Return_Read_Message_Size,
		int32_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Wait,Handle,Read_Message_DATA,Read_Message_Size,Return_Read_Message_Size,Time_Out_MS);
}
int Message_Queue_Clear(int Handle)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Clear,Handle);
}
int Message_Queue_Set(
		int Handle,
		void *Set_Message_DATA,
		uint32_t Set_Message_Size)
{
	return SysCall(SysCall_Table_Index_Message_Queue_Set,Handle,Set_Message_DATA,Set_Message_Size);
}

//Event-Mutex
int Mutex_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type)
{
	return SysCall(SysCall_Table_Index_Mutex_Create,Name,Option_Type);
}
int Mutex_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Mutex_Delete,Handle);
}
int Mutex_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Mutex_Find_Handle,Name);
}
int Mutex_Wait(
		int Handle,
		int32_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_Mutex_Wait,Handle,Time_Out_MS);
}
int Mutex_Release(int Handle)
{
	return SysCall(SysCall_Table_Index_Mutex_Release,Handle);
}

//Event-Semaphore
int Semaphore_Create(
		char *Name,
		uint32_t Init_Count,
		uint32_t MAX_Count,
		Event_Queue_Option_Type Option_Type)
{
	return SysCall(SysCall_Table_Index_Semaphore_Create,Name,Init_Count,MAX_Count,Option_Type);
}
int Semaphore_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Semaphore_Delete,Handle);
}
int Semaphore_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Semaphore_Find_Handle,Name);
}
int Semaphore_Wait(
		int Handle,
		int32_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_Semaphore_Wait,Handle,Time_Out_MS);
}
int Semaphore_Release(
		int Handle,
		uint32_t Release_Count,
		uint32_t *P_Previous_Count)
{
	return SysCall(SysCall_Table_Index_Semaphore_Release,Handle,Release_Count,P_Previous_Count);
}

//Event-Group
int Semaphore_Group_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type)
{
	return SysCall(SysCall_Table_Index_Semaphore_Group_Create,Name,Option_Type);
}
int Semaphore_Group_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Semaphore_Group_Delete,Handle);
}
int Semaphore_Group_Find_Handle(char *Name)
{
	return SysCall(SysCall_Table_Index_Semaphore_Group_Find_Handle,Name);
}
int Semaphore_Group_Wait(
		int Handle,
		bool Monopolize,
		int16_t Time_Out_MS)
{
	return SysCall(SysCall_Table_Index_Semaphore_Group_Wait,Handle,Monopolize,Time_Out_MS);
}
int Semaphore_Group_Release(
		int Handle,
		bool Monopolize,
		int32_t *P_Previous_Count)
{
	return SysCall(SysCall_Table_Index_Semaphore_Group_Release,Handle,Monopolize,P_Previous_Count);
}

//Timer
int Timer_Enable(void)
{
	return SysCall(SysCall_Table_Index_Timer_Enable);
}
int Timer_Disable(void)
{
	return SysCall(SysCall_Table_Index_Timer_Disable);
}
int Timer_Register(
		Timer_Enter_Function Timer_Function,
		void *Args)
{
	return SysCall(SysCall_Table_Index_Timer_Register,Timer_Function,Args);
}
int Timer_Delete(int Handle)
{
	return SysCall(SysCall_Table_Index_Timer_Delete,Handle);
}
int Timer_Start(
		int Handle,
		int32_t N_Time_Cycle,	//次数
		int32_t Cycle_Time_MS,	//周期
		Timer_Operation_Type Timer_Operation)
{
	return SysCall(SysCall_Table_Index_Timer_Start,Handle,N_Time_Cycle,Cycle_Time_MS,Timer_Operation);
}
int Timer_Stop(int Handle)
{
	return SysCall(SysCall_Table_Index_Timer_Stop,Handle);
}
int Timer_Suspend(int Handle)//暂停
{
	return SysCall(SysCall_Table_Index_Timer_Suspend,Handle);
}
int Timer_Resume(int Handle)//恢复
{
	return SysCall(SysCall_Table_Index_Timer_Resume,Handle);
}
int Timer_Reset(int Handle)//复位
{
	return SysCall(SysCall_Table_Index_Timer_Reset,Handle);
}
int Timer_Enabled(uint8_t Enabled)
{
	return SysCall(SysCall_Table_Index_Timer_Enabled,Enabled);
}

