/*
 * __Sys.API.c
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */
#include "Define.h"
#include "List.h"
#include "Error.h"
#include "__Sys.API.h"
#include "__Sys.API.Struct.h"

__Sys_API_Handle_DATA_Type __Sys_API_Handle_DATA=
{
	.Count=0,
	.Head=Null,
	.End=Null
};

//int Sys_Handle=1;//0保留给Idle Task
int __Sys_Handle_New(void)
{
	__Sys_API_Handle_Node_Type *Temp_Node_Add=__Sys_Memory_Malloc(sizeof(__Sys_API_Handle_Node_Type));
	if(Temp_Node_Add==Null)
	{
		return Error_Allocation_Memory_Failed;
	}

	Temp_Node_Add->Handle=1;

	//if(__Sys_API_Handle_DATA.Head==Null || __Sys_API_Handle_DATA.End==Null)
	{

		//List_Add_Node_To_End(__Sys_API_Handle_DATA.Head,__Sys_API_Handle_DATA.End,NEXT,Temp_Node_Add);
		//__Sys_API_Handle_DATA.Count++;
	}
	//else
	{
		__Sys_API_Handle_Node_Type *Temp_Node=__Sys_API_Handle_DATA.Head;
		__Sys_API_Handle_Node_Type *LAST_Temp_Node=Null;
		//__Sys_API_Handle_Node_Type *NEXT_Temp_Node=Null;

		while(1)
		{
			//NEXT_Temp_Node=Temp_Node->NEXT;

			if(Temp_Node!=Null)
			{
				if(Temp_Node_Add->Handle==Temp_Node->Handle)
				{
					Temp_Node_Add->Handle++;
					if(Temp_Node_Add->Handle>=0x7FFFFFFF)
					{
						__Sys_Memory_Free(Temp_Node_Add);
						return Error_Allocation_Memory_Failed;
					}
				}
				else
				{
					if(LAST_Temp_Node==Null || Temp_Node==__Sys_API_Handle_DATA.Head)
					{
						Temp_Node_Add->NEXT=Temp_Node;
						__Sys_API_Handle_DATA.Head=Temp_Node_Add;
					}
					else if(Temp_Node==__Sys_API_Handle_DATA.End || Temp_Node->NEXT==Null)
					{
						Temp_Node->NEXT=Temp_Node_Add;
						Temp_Node_Add->NEXT=Null;
						__Sys_API_Handle_DATA.End=Temp_Node_Add;
					}
					else
					{
						LAST_Temp_Node->NEXT=Temp_Node_Add;
						Temp_Node_Add->NEXT=Temp_Node;
					}
					break;
				}

			}
			else
			{
				List_Add_Node_To_End(__Sys_API_Handle_DATA.Head,__Sys_API_Handle_DATA.End,NEXT,Temp_Node_Add);
				break;
			}
			LAST_Temp_Node=Temp_Node;
			Temp_Node=Temp_Node->NEXT;
		}

	}

	__Sys_API_Handle_DATA.Count++;
	return Temp_Node_Add->Handle;
}
int __Sys_Handle_Free(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	__Sys_API_Handle_Node_Type *Temp_Node_Del=Null;
	List_Del_Node_From_Symbol(Handle1,__Sys_API_Handle_Node_Type,__Sys_API_Handle_DATA.Head,__Sys_API_Handle_DATA.End,NEXT,Handle,Handle,Temp_Node_Del);
	if(Temp_Node_Del==Null)
	{
		return Error_Invalid_Handle;
	}
	__Sys_Memory_Free(Temp_Node_Del);
	__Sys_API_Handle_DATA.Count--;

	return Error_OK;
}

//Event-Event_Flag_Group
#ifdef Master_OS_Config_Event_Flag_Group_Create_8bit
int __Sys_Event_Flag_Group_Create_8bit(char *Name)
{
	return __Sys_Event_Flag_Group_Create(Name,sizeof(uint8_t));
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_16bit
int __Sys_Event_Flag_Group_Create_16bit(char *Name)
{
	return __Sys_Event_Flag_Group_Create(Name,sizeof(uint16_t));
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Create_32bit
int __Sys_Event_Flag_Group_Create_32bit(char *Name)
{
	return __Sys_Event_Flag_Group_Create(Name,sizeof(uint32_t));
}
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_8bit
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
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_16bit
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
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_And_32bit
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
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_8bit
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
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_16bit
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
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Wait_Or_32bit
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
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_8bit
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
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_16bit
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
#endif
#ifdef Master_OS_Config_Event_Flag_Group_Set_32bit
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
#endif
