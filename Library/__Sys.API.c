/*
 * __Sys.API.c
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */
#include "Error.h"
#include "__Sys.API.h"


int Sys_Handle=1;//0保留给Idle Task
int __Sys_Apply_Handle(void)
{
	if(Sys_Handle>=0x7FFFFFFF)
	{
		return Error_Allocation_Memory_Failed;
	}
	return Sys_Handle++;
}


//Event-Event_Flag_Group
int __Sys_Event_Flag_Group_Create_8bit(char *Name)
{
	return __Sys_Event_Flag_Group_Create(Name,sizeof(uint8_t));
}
int __Sys_Event_Flag_Group_Create_16bit(char *Name)
{
	return __Sys_Event_Flag_Group_Create(Name,sizeof(uint16_t));
}
int __Sys_Event_Flag_Group_Create_32bit(char *Name)
{
	return __Sys_Event_Flag_Group_Create(Name,sizeof(uint32_t));
}
int __Sys_Event_Flag_Group_Wait_And_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return __Sys_Event_Flag_Group_Wait_And(
			Handle,
			(uint8_t *)&Event_Flag_Group_Mask,
			(uint8_t *)&Event_Flag_Group_BIT,
			(uint8_t *)Read_Event_Flag_Group,
			Clear_Type,
			(uint8_t *)&Event_Flag_Group_Clear_BIT,
			Time_Out_MS);
}
int __Sys_Event_Flag_Group_Wait_And_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT,
		uint16_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint16_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return __Sys_Event_Flag_Group_Wait_And(
			Handle,
			(uint8_t *)&Event_Flag_Group_Mask,
			(uint8_t *)&Event_Flag_Group_BIT,
			(uint8_t *)Read_Event_Flag_Group,
			Clear_Type,
			(uint8_t *)&Event_Flag_Group_Clear_BIT,
			Time_Out_MS);
}
int __Sys_Event_Flag_Group_Wait_And_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT,
		uint32_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint32_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return __Sys_Event_Flag_Group_Wait_And(
			Handle,
			(uint8_t *)&Event_Flag_Group_Mask,
			(uint8_t *)&Event_Flag_Group_BIT,
			(uint8_t *)Read_Event_Flag_Group,
			Clear_Type,
			(uint8_t *)&Event_Flag_Group_Clear_BIT,
			Time_Out_MS);
}
int __Sys_Event_Flag_Group_Wait_Or_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT,
		uint8_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint8_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return __Sys_Event_Flag_Group_Wait_Or(
			Handle,
			(uint8_t *)&Event_Flag_Group_Mask,
			(uint8_t *)&Event_Flag_Group_BIT,
			(uint8_t *)Read_Event_Flag_Group,
			Clear_Type,
			(uint8_t *)&Event_Flag_Group_Clear_BIT,
			Time_Out_MS);
}
int __Sys_Event_Flag_Group_Wait_Or_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT,
		uint16_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint16_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return __Sys_Event_Flag_Group_Wait_Or(
			Handle,
			(uint8_t *)&Event_Flag_Group_Mask,
			(uint8_t *)&Event_Flag_Group_BIT,
			(uint8_t *)Read_Event_Flag_Group,
			Clear_Type,
			(uint8_t *)&Event_Flag_Group_Clear_BIT,
			Time_Out_MS);
}
int __Sys_Event_Flag_Group_Wait_Or_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT,
		uint32_t *Read_Event_Flag_Group,
		Event_Flag_Group_Clear_Type Clear_Type,
		uint32_t Event_Flag_Group_Clear_BIT,
		int32_t Time_Out_MS)
{
	return __Sys_Event_Flag_Group_Wait_Or(
			Handle,
			(uint8_t *)&Event_Flag_Group_Mask,
			(uint8_t *)&Event_Flag_Group_BIT,
			(uint8_t *)Read_Event_Flag_Group,
			Clear_Type,
			(uint8_t *)&Event_Flag_Group_Clear_BIT,
			Time_Out_MS);
}
int __Sys_Event_Flag_Group_Set_8bit(
		int Handle,
		uint8_t Event_Flag_Group_Mask,
		uint8_t Event_Flag_Group_BIT)
{
	return __Sys_Event_Flag_Group_Set(
			Handle,
			(uint8_t *)&Event_Flag_Group_Mask,
			(uint8_t *)&Event_Flag_Group_BIT);
}
int __Sys_Event_Flag_Group_Set_16bit(
		int Handle,
		uint16_t Event_Flag_Group_Mask,
		uint16_t Event_Flag_Group_BIT)
{
	return __Sys_Event_Flag_Group_Set(
			Handle,
			(uint8_t *)&Event_Flag_Group_Mask,
			(uint8_t *)&Event_Flag_Group_BIT);
}
int __Sys_Event_Flag_Group_Set_32bit(
		int Handle,
		uint32_t Event_Flag_Group_Mask,
		uint32_t Event_Flag_Group_BIT)
{
	return __Sys_Event_Flag_Group_Set(
			Handle,
			(uint8_t *)&Event_Flag_Group_Mask,
			(uint8_t *)&Event_Flag_Group_BIT);
}
