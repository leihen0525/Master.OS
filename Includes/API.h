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

#include "Versions.h"

#include "Error.h"
//#include "Master.OS.Config.h"
#include "Master.Stdint.h"
#include "Scheduling/Scheduling.Task.Define.h"
#include "IRQ/IRQ.Define.h"
#include "Timer/Timer.Define.h"
#include "Timer/Timer.Enum.h"
#include "Event/Event.Enum.h"
#include "Event/Event.Define.h"
#include "MPU/MPU.Define.h"
#include "Memory/Memory.Struct.h"
#include "Device/Device.h"


int Handle_New(void);//申请一个未使用的句柄
int Handle_Free(int Handle);

//BSP
int BSP_System_Reset(void);
int BSP_Wdog_Enable(void);
int BSP_Wdog_Disable(void);
int BSP_Wdog_Refresh(void);

//Memory

uint32_t Memory_Size_Malloc(void);

uint32_t Memory_Size_Free(void);

void *Memory_Malloc_Align(uint32_t Size,uint32_t Align);

void *Memory_Malloc(uint32_t Size);

void Memory_Free(void *ap);

//用户自定义

int UGC_Memory_Init(
		Memory_DATA_Type *P_Memory_DATA,
		uint8_t *HEAP,
		uint32_t Size);

uint32_t UGC_Memory_Size_Malloc(Memory_DATA_Type *P_Memory_DATA);

uint32_t UGC_Memory_Size_Free(Memory_DATA_Type *P_Memory_DATA);

void *UGC_Memory_Malloc(Memory_DATA_Type *P_Memory_DATA,uint32_t Size,uint32_t Align);

void UGC_Memory_Free(Memory_DATA_Type *P_Memory_DATA,void *ap);

//Device-Legacy

int Device_Legacy_Open(const char *Device_Name,int Mode);

int Device_Legacy_Close(int Handle);

int Device_Legacy_Read(int Handle,long OffSet_Pos, void *Buffer, unsigned long Size,long TimeOut);

int Device_Legacy_Write(int Handle,long OffSet_Pos, const void *Buffer, unsigned long Size,long TimeOut);

int Device_Legacy_Control(int Handle,int Cmd,...);

int Device_Legacy_Info(int Handle,const char **P_Info);


//

//Device-Class-ETH

int Device_Class_ETH_Open(const char *Device_Name,int Flag);

int Device_Class_ETH_Close(int Handle);

int Device_Class_ETH_Init(int Handle,int Flag);

int Device_Class_ETH_DeInit(int Handle);

int Device_Class_ETH_Get_Enabled(int Handle,bool *P_Module);

int Device_Class_ETH_Set_Enabled(int Handle,bool Module);

int Device_Class_ETH_Get_MAC_Address(int Handle,uint8_t *P_Address);

int Device_Class_ETH_Set_MAC_Address(int Handle,uint8_t *P_Address);

int Device_Class_ETH_Get_Interface(int Handle,Device_Class_ETH_Enum_Interface_xMII_Type *P_xMII,Device_Class_ETH_Enum_Interface_Speed_Type *P_Speed,bool *P_Full_Duplex);

int Device_Class_ETH_Set_Interface(int Handle,Device_Class_ETH_Enum_Interface_xMII_Type xMII,Device_Class_ETH_Enum_Interface_Speed_Type Speed,bool Full_Duplex);

int Device_Class_ETH_Set_MAC_Address_Filter(int Handle,uint8_t *P_Address);

int Device_Class_ETH_ReSet_MAC_Address_Filter(int Handle);

int Device_Class_ETH_Receive(int Handle,int Queue_Index,uint8_t *P_Buffer, uint32_t Size,uint32_t *P_Read_Size,uint32_t *P_Flag,uint32_t *P_Timestamp,int32_t TimeOut);

int Device_Class_ETH_Send(int Handle,int Queue_Index,const uint8_t *P_Buffer, uint32_t Size,uint32_t Flag,int32_t TimeOut);

int Device_Class_ETH_Send_Sync(int Handle,int Queue_Index,const uint8_t *P_Buffer, uint32_t Size,uint32_t Flag,uint32_t *P_Timestamp,int32_t TimeOut);

int Device_Class_ETH_Send_Slice(int Handle,int Queue_Index,const Device_Class_ETH_Send_Slice_Data_Type *P_Buffer, uint32_t Size,uint32_t Flag,int32_t TimeOut);

int Device_Class_ETH_Send_Slice_Sync(int Handle,int Queue_Index,const Device_Class_ETH_Send_Slice_Data_Type *P_Buffer, uint32_t Size,uint32_t Flag,uint32_t *P_Timestamp,int32_t TimeOut);

int Device_Class_ETH_Get_MDIO(int Handle,uint8_t Phy, uint8_t RegisterAddr, uint16_t *P_Value);

int Device_Class_ETH_Set_MDIO(int Handle,uint8_t Phy, uint8_t RegisterAddr, uint16_t Value);

int Device_Class_ETH_Get_Static_Cfg(int Handle,const Device_Class_ETH_Static_Cfg_Type **P_Static_Cfg);

int Device_Class_ETH_Get_Info(int Handle,const char **P_Info);

//IRQ

int IRQ_Enable(int IRQ_Index);

int IRQ_Disable(int IRQ_Index);

int IRQ_Set_Priority(int IRQ_Index,int Priority);

int IRQ_All_Enable(void);

int IRQ_All_Disable(void);

int IRQ_Register_Hook(int IRQ_Index,IRQ_Hook_Function Hook_Function,void *Args);

int IRQ_Delete_Hook(int IRQ_Index,int Handle);



//Scheduling

int Scheduling_Create_Task(
		char *Name,
		Task_Enter_Function Task_Enter,
		void *Args,
		uint8_t Priority,
		uint32_t *Stack,
		uint32_t Stack_Size_4Byte,
		int Option);

int Scheduling_Release_Task(int Handle);

void Scheduling_Exit_Task(void);

int Scheduling_Sleep_Task(int32_t TimeOut);

int Scheduling_Suspend_Task(int Handle);

int Scheduling_Resume_Task(int Handle);


//Event-Event_Flag

int Event_Flag_Create(
		char *Name,
		bool Init_Flag);

int Event_Flag_Delete(int Handle);

int Event_Flag_Find_Handle(char *Name);

int Event_Flag_Wait(
		int Handle,
		int32_t Time_Out_MS);

int Event_Flag_Clear(int Handle);

int Event_Flag_Set(int Handle);


//Event-Event_Flag_Group

int Event_Flag_Group_Create(
		char *Name,
		uint32_t Flag_Group_LEN);

int Event_Flag_Group_Create_8bit(char *Name);

int Event_Flag_Group_Create_16bit(char *Name);

int Event_Flag_Group_Create_32bit(char *Name);



int Event_Flag_Group_Delete(int Handle);

int Event_Flag_Group_Find_Handle(char *Name);

int Event_Flag_Group_Open(int Handle);

int Event_Flag_Group_Close(int Handle);

int Event_Flag_Group_Wait_And(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t *Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);

int Event_Flag_Group_Wait_And_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);

int Event_Flag_Group_Wait_And_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT,
		uint16_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint16_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);

int Event_Flag_Group_Wait_And_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT,
		uint32_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint32_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);



int Event_Flag_Group_Wait_Or(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t *Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);

int Event_Flag_Group_Wait_Or_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);

int Event_Flag_Group_Wait_Or_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT,
		uint16_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint16_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);

int Event_Flag_Group_Wait_Or_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT,
		uint32_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint32_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS);

int Event_Flag_Group_Set(
		int Handle,
		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT);

int Event_Flag_Group_Set_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT);

int Event_Flag_Group_Set_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT);

int Event_Flag_Group_Set_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT);


//Event-FIFO_Queue

int FIFO_Queue_Create(
		char *Name,
		uint32_t Max_FIFO_Size,
		uint32_t Max_FIFO_Queue_Length,
		__Sys_Event_FIFO_OverFlow_Function __Sys_OverFlow_Fun,
		void *__Sys_OverFlow_Args);

int FIFO_Queue_Delete(int Handle);

int FIFO_Queue_Find_Handle(char *Name);

int FIFO_Queue_Open(int Handle);

int FIFO_Queue_Close(int Handle);

int FIFO_Queue_Wait(
		int Handle,
		void *Read_FIFO_DATA,
		uint32_t Read_FIFO_Size,
		uint32_t *Return_Read_FIFO_Size,
		int32_t Time_Out_MS);

int FIFO_Queue_Clear(int Handle);

int FIFO_Queue_Set(
		int Handle,
		void *Set_FIFO_DATA,
		uint32_t Set_FIFO_Size);


//Event-Message_Queue

int Message_Queue_Create(
		char *Name,
		uint32_t Max_Message_Size,
		uint32_t Max_Message_Queue_Length);

int Message_Queue_Delete(int Handle);

int Message_Queue_Find_Handle(char *Name);

int Message_Queue_Open(int Handle);

int Message_Queue_Close(int Handle);

int Message_Queue_Wait(
		int Handle,
		void *Read_Message_DATA,
		uint32_t Read_Message_Size,
		uint32_t *Return_Read_Message_Size,
		int32_t Time_Out_MS);

int Message_Queue_Clear(int Handle);

int Message_Queue_Set(
		int Handle,
		void *Set_Message_DATA,
		uint32_t Set_Message_Size);


//Event-Mutex

int Mutex_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type);

int Mutex_Delete(int Handle);

int Mutex_Find_Handle(char *Name);

int Mutex_Wait(
		int Handle,
		int32_t Time_Out_MS);

int Mutex_Release(int Handle);


//Event-Semaphore

int Semaphore_Create(
		char *Name,
		uint32_t Init_Count,
		uint32_t MAX_Count,
		Event_Queue_Option_Type Option_Type);

int Semaphore_Delete(int Handle);

int Semaphore_Find_Handle(char *Name);

int Semaphore_Wait(
		int Handle,
		int32_t Time_Out_MS);

int Semaphore_Release(
		int Handle,
		uint32_t Release_Count,
		uint32_t *P_Previous_Count);


//Event-Semaphore-Group

int Semaphore_Group_Create(
		char *Name,
		Event_Queue_Option_Type Option_Type);

int Semaphore_Group_Delete(int Handle);

int Semaphore_Group_Find_Handle(char *Name);

int Semaphore_Group_Wait(
		int Handle,
		bool Monopolize,
		int16_t Time_Out_MS);

int Semaphore_Group_Release(
		int Handle,
		bool Monopolize,
		int32_t *P_Previous_Count);


//Timer
int Timer_GET_Counter(uint64_t *Counter_MS);

int Timer_Enable(void);

int Timer_Disable(void);

int Timer_Register(
		Timer_Enter_Function Timer_Function,
		void *Args);

int Timer_Register2(
		Timer_Enter_Function2 Timer_Function,
		void *Args1,
		void *Args2);

int Timer_Delete(int Handle);

int Timer_Start(
		int Handle,
		int32_t N_Time_Cycle,	//次数
		int32_t Cycle_Time_MS,	//周期
		Timer_Operation_Type Timer_Operation);

int Timer_Stop(int Handle);

int Timer_Suspend(int Handle);//暂停

int Timer_Resume(int Handle);//恢复

int Timer_Reset(int Handle);//复位

int Timer_Enabled(uint8_t Enabled);


#ifdef __cplusplus
}
#endif

#endif /* API_H_ */
