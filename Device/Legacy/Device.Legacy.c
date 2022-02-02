/*
 * Device.Legacy.c
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */
#include "__Sys.API.h"
#include <string.h>

#include "Master.Stdint.h"
#include "Error.h"
#include "List.h"
#include "Define.h"

#include "Device.Legacy.h"


Device_Legacy_DATA_Type Device_Legacy_DATA;

int Device_Legacy_Init(void)
{
	Device_Legacy_DATA.Node_List.Count=0;
	Device_Legacy_DATA.Node_List.Head=Null;
	Device_Legacy_DATA.Node_List.End=Null;

	return Error_OK;
}

int __Sys_Device_Legacy_Register_Drivers(const __Sys_Device_Legacy_OPS_Type *P_OPS)
{
	if(P_OPS==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Legacy_Node_Type *P_Node=Null;
	if(P_OPS->Device_Name==Null)
	{
		return Error_Invalid_Parameter;
	}
	else
	{
		//
		List_Find_Node_From_Strcmp(Device_Legacy_DATA.Node_List.Head,NEXT,P_OPS->Device_Name,P_OPS->Device_Name,P_Node);
		if(P_Node!=Null)
		{
			return Error_Config;
		}
	}

	int Handle;
	Error_Args_Return(Handle,__Sys_Handle_New());


	P_Node=__Sys_Memory_Malloc(sizeof(Device_Legacy_Node_Type));
	if(P_Node==Null)
	{
		__Sys_Handle_Free(Handle);
		return Error_Allocation_Memory_Failed;
	}

	P_Node->Handle=Handle;
	P_Node->P_OPS=P_OPS;

	List_Add_Node_To_End(Device_Legacy_DATA.Node_List.Head,Device_Legacy_DATA.Node_List.End,NEXT,P_Node);
	Device_Legacy_DATA.Node_List.Count++;

	return Error_OK;

}

#ifdef Master_OS_Config_Device_Legacy_Open
int __Sys_Device_Legacy_Open(const char *Device_Name,int Mode)
{
	int Err;
	if(Device_Name==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Legacy_Node_Type *P_Node=Null;
	List_Find_Node_From_Strcmp(Device_Legacy_DATA.Node_List.Head,NEXT,P_OPS->Device_Name,Device_Name,P_Node);

	if(P_Node==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->Handle<Error_OK)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Open!=Null)
	{
		Error_NoArgs_Return(Err,P_Node->P_OPS->Open(P_Node->P_OPS->Device_Args,Mode));
	}

	return P_Node->Handle;
}
#endif
#ifdef Master_OS_Config_Device_Legacy_Close
int __Sys_Device_Legacy_Close(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	Device_Legacy_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Legacy_DATA.Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}


	if(P_Node->P_OPS->Close==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Close(P_Node->P_OPS->Device_Args);

}
#endif
#ifdef Master_OS_Config_Device_Legacy_Read
int __Sys_Device_Legacy_Read(int Handle,long OffSet_Pos, void *Buffer, unsigned long Size,long TimeOut)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	Device_Legacy_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Legacy_DATA.Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Read==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Read(P_Node->P_OPS->Device_Args,OffSet_Pos,Buffer,Size,TimeOut);
}
#endif
#ifdef Master_OS_Config_Device_Legacy_Write
int __Sys_Device_Legacy_Write(int Handle,long OffSet_Pos, const void *Buffer, unsigned long Size,long TimeOut)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	Device_Legacy_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Legacy_DATA.Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Write==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Write(P_Node->P_OPS->Device_Args,OffSet_Pos,Buffer,Size,TimeOut);
}
#endif
#ifdef Master_OS_Config_Device_Legacy_Control
int __Sys_Device_Legacy_Control(int Handle,int Cmd, unsigned long Args)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	Device_Legacy_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Legacy_DATA.Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Control==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Control(P_Node->P_OPS->Device_Args,Cmd, Args);
}
#endif
#ifdef Master_OS_Config_Device_Legacy_Info
int __Sys_Device_Legacy_Info(int Handle,const char **P_Info)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	if(P_Info==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Legacy_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Legacy_DATA.Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}
	*P_Info=P_Node->P_OPS->Info;

	return Error_OK;
}
#endif

