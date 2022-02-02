/*
 * __Sys.Device.Class.ETH.Struct.h
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */

#ifndef SYS_DEVICE_CLASS_ETH_STRUCT_H_
#define SYS_DEVICE_CLASS_ETH_STRUCT_H_

#include "Master.Stdint.h"

#include "Device.Class.ETH.Enum.h"
#include "Device.Class.ETH.Struct.h"

typedef struct
{
	const char *Device_Name;
	const char *Info;

	void *Device_Args;

	const Device_Class_ETH_Static_Cfg_Type *P_Static_Cfg;

	int (*Open)(void *Device_Args,int Flag);
	int (*Close)(void *Device_Args);

	int (*Init)(void *Device_Args,int Flag);
	int (*DeInit)(void *Device_Args);

	int (*Get_Enabled)(void *Device_Args,bool *P_Module);
	int (*Set_Enabled)(void *Device_Args,bool Module);

	int (*Get_MAC_Address)(void *Device_Args,uint8_t *P_Address);
	int (*Set_MAC_Address)(void *Device_Args,uint8_t *P_Address);

	int (*Get_Interface)(void *Device_Args,Device_Class_ETH_Enum_Interface_xMII_Type *P_xMII,Device_Class_ETH_Enum_Interface_Speed_Type *P_Speed,bool *P_Full_Duplex);
	int (*Set_Interface)(void *Device_Args,Device_Class_ETH_Enum_Interface_xMII_Type xMII,Device_Class_ETH_Enum_Interface_Speed_Type Speed,bool Full_Duplex);

	int (*Set_MAC_Address_Filter)(void *Device_Args,uint8_t *P_Address);
	int (*ReSet_MAC_Address_Filter)(void *Device_Args);

	int (*Receive)(void *Device_Args,int Queue_Index,uint8_t *P_Buffer, uint32_t Size,uint32_t *P_Read_Size,uint32_t *P_Flag,uint32_t *P_Timestamp,int32_t TimeOut);

	int (*Send)(void *Device_Args,int Queue_Index,const uint8_t *P_Buffer, uint32_t Size,uint32_t Flag,int32_t TimeOut);

	int (*Send_Sync)(void *Device_Args,int Queue_Index,const uint8_t *P_Buffer, uint32_t Size,uint32_t Flag,uint32_t *P_Timestamp,int32_t TimeOut);

	int (*Send_Slice)(void *Device_Args,int Queue_Index,const Device_Class_ETH_Send_Slice_Data_Type *P_Buffer, uint32_t Size,uint32_t Flag,int32_t TimeOut);

	int (*Send_Slice_Sync)(void *Device_Args,int Queue_Index,const Device_Class_ETH_Send_Slice_Data_Type *P_Buffer, uint32_t Size,uint32_t Flag,uint32_t *P_Timestamp,int32_t TimeOut);

	int (*Get_MDIO)(void *Device_Args,uint8_t Phy, uint8_t RegisterAddr, uint16_t *P_Value);
	int (*Set_MDIO)(void *Device_Args,uint8_t Phy, uint8_t RegisterAddr, uint16_t Value);

}__Sys_Device_Class_ETH_OPS_Type;

#endif /* SYS_DEVICE_CLASS_ETH_STRUCT_H_ */
