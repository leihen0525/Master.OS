/*
 * Device.c
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */
#include "__Sys.API.h"
#include <string.h>

#include "Master.Stdint.h"
#include "Error.h"

#include "Device\__Sys.Device.h"

#include "Device.h"

#include "Device.Define.h"

#include "Define.h"

Device_DATA_Type Device_DATA;

int Device_Init(void)
{
	//Device_DATA.Handle_Index=Valid_Handle;

	Device_DATA.List_Node.Head=Null;
	Device_DATA.List_Node.End=Null;

	return Error_OK;
}

int Device_Find_Node_To_Name(const char *Device_Name,Device_Node_Type **P_Node)
{
	if(Device_Name==Null || Device_Name=="")
	{
		return Error_Invalid_Parameter;
	}


	Device_Node_Type *Temp_Node=Null;

	Temp_Node=Device_DATA.List_Node.Head;

	while(Temp_Node!=Null)
	{
		if(Temp_Node->P_OPS==Null)
		{
			return Error_Undefined;
		}
		if(strcmp(Temp_Node->P_OPS->Device_Name,Device_Name)==0)
		{
			if(P_Node!=Null)
			{
				*P_Node=Temp_Node;
			}
			return Temp_Node->Handle;
		}
		Temp_Node=Temp_Node->NEXT;
	}
	return Error_Undefined;
}
int Device_Find_Node_To_Handle(int Handle,Device_Node_Type **P_Node)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(P_Node==Null)
	{
		return Error_Invalid_Parameter;
	}


	Device_Node_Type *Temp_Node=Device_DATA.List_Node.Head;

	while(Temp_Node!=Null)
	{

		if(Temp_Node->Handle==Handle)
		{
			*P_Node=Temp_Node;
			return Error_OK;
		}
		Temp_Node=Temp_Node->NEXT;
	}

	return Error_Invalid_Handle;
}

int Device_Add_Node(const __Sys_Device_OPS_Type *P_OPS)
{
	if(P_OPS==Null)
	{
		return Error_Invalid_Parameter;
	}

	int Handle=__Sys_Handle_New();
	if(Handle<Valid_Handle)
	{
		return Handle;
	}

	Device_Node_Type *Temp_Node=__Sys_Memory_Malloc(sizeof(Device_Node_Type));
	if(Temp_Node==Null)
	{
		__Sys_Handle_Free(Handle);
		return Error_Allocation_Memory_Failed;
	}

	Temp_Node->Handle=Handle;
	Temp_Node->P_OPS=P_OPS;


	if(Device_DATA.List_Node.End==Null)
	{
		Device_DATA.List_Node.Head=Temp_Node;
	}
	else
	{
		Device_DATA.List_Node.End->NEXT=Temp_Node;
	}
	Device_DATA.List_Node.End=Temp_Node;
	Temp_Node->NEXT=Null;

	return Error_OK;
}
int Device_Del_Node(int Handle)
{
	//TODO ?
	return -1;
}
int __Sys_Device_Register_Drivers(const __Sys_Device_OPS_Type *P_OPS)
{
	return Device_Add_Node(P_OPS);
}

#ifdef Master_OS_Config_Device_Open
int __Sys_Device_Open(const char *Device_Name,int Mode)
{
	if(Device_Name==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Node_Type *Temp_Node=Null;
	int Handle=Device_Find_Node_To_Name(Device_Name,&Temp_Node);

	if(Handle<Error_OK)
	{
		return Handle;
	}
	if(Temp_Node!=Null)
	{
		if(Temp_Node->P_OPS==Null)
		{
			return Error_Unknown;
		}
	}
	else
	{
		return Error_Unknown;
	}


	if(Temp_Node->P_OPS->Open!=Null)
	{
		int Re=Temp_Node->P_OPS->Open(Temp_Node->P_OPS->Device_Args,Mode);
		if(Re!=Error_OK)
		{
			return Re;
		}
	}

	return Handle;
}
#endif
#ifdef Master_OS_Config_Device_Close
int __Sys_Device_Close(int Handle)
{
	Device_Node_Type *Temp_Node=Null;
	int Re=Device_Find_Node_To_Handle(Handle,&Temp_Node);
	if(Re!=Error_OK)
	{
		return Re;
	}
	if(Temp_Node!=Null)
	{
		if(Temp_Node->P_OPS==Null)
		{
			return Error_Unknown;
		}
	}
	else
	{
		return Error_Unknown;
	}

	if(Temp_Node->P_OPS->Close==Null)
	{
		return Error_Undefined;
	}
	return Temp_Node->P_OPS->Close(Temp_Node->P_OPS->Device_Args);

}
#endif
#ifdef Master_OS_Config_Device_Read
int __Sys_Device_Read(int Handle,long OffSet_Pos, void *Buffer, unsigned long Size,long TimeOut)
{
	Device_Node_Type *Temp_Node=Null;
	int Re=Device_Find_Node_To_Handle(Handle,&Temp_Node);
	if(Re!=Error_OK)
	{
		return Re;
	}
	if(Temp_Node!=Null)
	{
		if(Temp_Node->P_OPS==Null)
		{
			return Error_Unknown;
		}
	}
	else
	{
		return Error_Unknown;
	}

	if(Temp_Node->P_OPS->Read==Null)
	{
		return Error_Undefined;
	}
	return Temp_Node->P_OPS->Read(Temp_Node->P_OPS->Device_Args,OffSet_Pos,Buffer,Size,TimeOut);
}
#endif
#ifdef Master_OS_Config_Device_Write
int __Sys_Device_Write(int Handle,long OffSet_Pos, const void *Buffer, unsigned long Size,long TimeOut)
{
	Device_Node_Type *Temp_Node=Null;
	int Re=Device_Find_Node_To_Handle(Handle,&Temp_Node);
	if(Re!=Error_OK)
	{
		return Re;
	}
	if(Temp_Node!=Null)
	{
		if(Temp_Node->P_OPS==Null)
		{
			return Error_Unknown;
		}
	}
	else
	{
		return Error_Unknown;
	}

	if(Temp_Node->P_OPS->Write==Null)
	{
		return Error_Undefined;
	}
	return Temp_Node->P_OPS->Write(Temp_Node->P_OPS->Device_Args,OffSet_Pos,Buffer,Size,TimeOut);
}
#endif
#ifdef Master_OS_Config_Device_Control
int __Sys_Device_Control(int Handle,int Cmd, unsigned long Args)
{
	Device_Node_Type *Temp_Node=Null;
	int Re=Device_Find_Node_To_Handle(Handle,&Temp_Node);
	if(Re!=Error_OK)
	{
		return Re;
	}
	if(Temp_Node!=Null)
	{
		if(Temp_Node->P_OPS==Null)
		{
			return Error_Unknown;
		}
	}
	else
	{
		return Error_Unknown;
	}

	if(Temp_Node->P_OPS->Control==Null)
	{
		return Error_Undefined;
	}
	return Temp_Node->P_OPS->Control(Temp_Node->P_OPS->Device_Args,Cmd, Args);
}
#endif
#ifdef Master_OS_Config_Device_Info
int __Sys_Device_Info(int Handle,const char **P_Info)
{
	if(P_Info==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Node_Type *Temp_Node=Null;
	int Re=Device_Find_Node_To_Handle(Handle,&Temp_Node);
	if(Re!=Error_OK)
	{
		return Re;
	}
	if(Temp_Node!=Null)
	{
		if(Temp_Node->P_OPS==Null)
		{
			return Error_Unknown;
		}
	}
	else
	{
		return Error_Unknown;
	}
	*P_Info=Temp_Node->P_OPS->Info;

	return Error_OK;
}
#endif
