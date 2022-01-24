/*
 * Device.Class.ETH.c
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */
#include "Error.h"
#include "Define.h"
#include "List.h"
#include "__Sys.API.h"

#include "__Device.Class.ETH.h"

Device_Class_ETH_DATA_Type Device_Class_ETH_DATA;

int Device_Class_ETH_Init(void)
{

	Device_Class_ETH_DATA.ETH_Node_List.Count=0;
	Device_Class_ETH_DATA.ETH_Node_List.Head=Null;
	Device_Class_ETH_DATA.ETH_Node_List.End=Null;

	return Error_OK;
}
int __Sys_Device_Class_ETH_Register_Drivers(const __Sys_Device_Class_ETH_OPS_Type *P_OPS)
{
	if(P_OPS==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	if(P_OPS->Device_Name==Null)
	{
		return Error_Invalid_Parameter;
	}
	else
	{
		//
		List_Find_Node_From_CharName(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,P_OPS->Device_Name,P_OPS->Device_Name,P_Node);
		if(P_Node!=Null)
		{
			return Error_Config;
		}
	}

	int Handle;
	Error_Args_Return(Handle,__Sys_Handle_New());


	P_Node=__Sys_Memory_Malloc(sizeof(Device_Class_ETH_Node_Type));
	if(P_Node==Null)
	{
		__Sys_Handle_Free(Handle);
		return Error_Allocation_Memory_Failed;
	}

	P_Node->Handle=Handle;
	P_Node->P_OPS=P_OPS;

	List_Add_Node_To_End(Device_Class_ETH_DATA.ETH_Node_List.Head,Device_Class_ETH_DATA.ETH_Node_List.End,NEXT,P_Node);
	Device_Class_ETH_DATA.ETH_Node_List.Count++;

	return Error_OK;

}
#ifdef Master_OS_Config_Device_Class_ETH_Open
int __Sys_Device_Class_ETH_Open(const char *Device_Name,int Flag)
{
	int Err;
	if(Device_Name==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_CharName(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,P_OPS->Device_Name,Device_Name,P_Node);

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
		Error_NoArgs_Return(Err,P_Node->P_OPS->Open(P_Node->P_OPS->Device_Args,Flag));
	}

	return P_Node->Handle;
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Close
int __Sys_Device_Class_ETH_Close(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
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
#ifdef Master_OS_Config_Device_Class_ETH_Get_Enabled
int __Sys_Device_Class_ETH_Get_Enabled(int Handle,bool *P_Module)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(P_Module==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Get_Enabled==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Get_Enabled(P_Node->P_OPS->Device_Args,P_Module);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Set_Enabled
int __Sys_Device_Class_ETH_Set_Enabled(int Handle,bool Module)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(Module>=bool_End)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Set_Enabled==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Set_Enabled(P_Node->P_OPS->Device_Args,Module);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Get_MAC_Address
int __Sys_Device_Class_ETH_Get_MAC_Address(int Handle,uint8_t *P_Address)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(P_Address==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Get_MAC_Address==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Get_MAC_Address(P_Node->P_OPS->Device_Args,P_Address);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Set_MAC_Address
int __Sys_Device_Class_ETH_Set_MAC_Address(int Handle,uint8_t *P_Address)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(P_Address==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Set_MAC_Address==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Set_MAC_Address(P_Node->P_OPS->Device_Args,P_Address);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Get_Interface
int __Sys_Device_Class_ETH_Get_Interface(int Handle,Device_Class_ETH_Enum_Interface_xMII_Type *P_xMII,Device_Class_ETH_Enum_Interface_Speed_Type *P_Speed,bool *P_Full_Duplex)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(P_xMII==Null && P_Speed==Null && P_Full_Duplex==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Get_Interface==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Get_Interface(P_Node->P_OPS->Device_Args,P_xMII,P_Speed,P_Full_Duplex);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Set_Interface
int __Sys_Device_Class_ETH_Set_Interface(int Handle,Device_Class_ETH_Enum_Interface_xMII_Type xMII,Device_Class_ETH_Enum_Interface_Speed_Type Speed,bool Full_Duplex)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(xMII>=Device_Class_ETH_Enum_Interface_xMII_End
	|| Speed>=Device_Class_ETH_Enum_Interface_Speed_End
	|| Full_Duplex>=bool_End)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Set_Interface==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Set_Interface(P_Node->P_OPS->Device_Args,xMII,Speed,Full_Duplex);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Set_MAC_Address_Filter
int __Sys_Device_Class_ETH_Set_MAC_Address_Filter(int Handle,uint8_t *P_Address)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(P_Address==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Set_MAC_Address_Filter==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Set_MAC_Address_Filter(P_Node->P_OPS->Device_Args,P_Address);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_ReSet_MAC_Address_Filter
int __Sys_Device_Class_ETH_ReSet_MAC_Address_Filter(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->ReSet_MAC_Address_Filter==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->ReSet_MAC_Address_Filter(P_Node->P_OPS->Device_Args);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Receive
int __Sys_Device_Class_ETH_Receive(int Handle,uint8_t *P_Buffer, uint32_t Size,uint32_t *P_Flag,int32_t TimeOut)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(P_Buffer==Null
	|| Size==0)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Receive==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Receive(P_Node->P_OPS->Device_Args,P_Buffer,Size,P_Flag,TimeOut);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Send
int __Sys_Device_Class_ETH_Send(int Handle,const uint8_t *P_Buffer, uint32_t Size,uint32_t Flag,int32_t TimeOut)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(P_Buffer==Null
	|| Size==0)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Send==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Send(P_Node->P_OPS->Device_Args,P_Buffer,Size,Flag,TimeOut);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Send_Slice
int __Sys_Device_Class_ETH_Send_Slice(int Handle,const Device_Class_ETH_Send_Slice_Data_Type *P_Buffer, uint32_t Size,uint32_t Flag,int32_t TimeOut)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(P_Buffer==Null
	|| Size==0)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Send_Slice==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Send_Slice(P_Node->P_OPS->Device_Args,P_Buffer,Size,Flag,TimeOut);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Get_MDIO
int __Sys_Device_Class_ETH_Get_MDIO(int Handle,uint8_t Phy, uint8_t RegisterAddr, uint16_t *P_Value)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if(P_Value==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Get_MDIO==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Get_MDIO(P_Node->P_OPS->Device_Args,Phy,RegisterAddr,P_Value);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Set_MDIO
int __Sys_Device_Class_ETH_Set_MDIO(int Handle,uint8_t Phy, uint8_t RegisterAddr, uint16_t Value)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
	if(P_Node==Null)
	{
		return Error_Invalid_Handle;
	}

	if(P_Node->P_OPS==Null)
	{
		return Error_Unknown;
	}

	if(P_Node->P_OPS->Set_MDIO==Null)
	{
		return Error_Undefined;
	}
	return P_Node->P_OPS->Set_MDIO(P_Node->P_OPS->Device_Args,Phy,RegisterAddr,Value);
}
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Get_Info
int __Sys_Device_Class_ETH_Get_Info(int Handle,const char **P_Info)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	if(P_Info==Null)
	{
		return Error_Invalid_Parameter;
	}
	Device_Class_ETH_Node_Type *P_Node=Null;
	List_Find_Node_From_Symbol(Device_Class_ETH_DATA.ETH_Node_List.Head,NEXT,Handle,Handle,P_Node);
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
