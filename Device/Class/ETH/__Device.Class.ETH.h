/*
 * __Device.Class.ETH.h
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */

#ifndef __DEVICE_CLASS_ETH_H_
#define __DEVICE_CLASS_ETH_H_

#include "Master.Stdint.h"

#include "__Device.Class.ETH.Struct.h"

int Device_Class_ETH_Init(void);

int __Sys_Device_Class_ETH_Register_Drivers(const __Sys_Device_Class_ETH_OPS_Type *P_OPS);

#ifdef Master_OS_Config_Device_Class_ETH_Open
int __Sys_Device_Class_ETH_Open(const char *Device_Name,int Flag);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Close
int __Sys_Device_Class_ETH_Close(int Handle);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Get_Enabled
int __Sys_Device_Class_ETH_Get_Enabled(int Handle,bool *P_Module);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Set_Enabled
int __Sys_Device_Class_ETH_Set_Enabled(int Handle,bool Module);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Get_MAC_Address
int __Sys_Device_Class_ETH_Get_MAC_Address(int Handle,uint8_t *P_Address);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Set_MAC_Address
int __Sys_Device_Class_ETH_Set_MAC_Address(int Handle,uint8_t *P_Address);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Get_Interface
int __Sys_Device_Class_ETH_Get_Interface(int Handle,Device_Class_ETH_Enum_Interface_xMII_Type *P_xMII,Device_Class_ETH_Enum_Interface_Speed_Type *P_Speed,bool *P_Full_Duplex);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Set_Interface
int __Sys_Device_Class_ETH_Set_Interface(int Handle,Device_Class_ETH_Enum_Interface_xMII_Type xMII,Device_Class_ETH_Enum_Interface_Speed_Type Speed,bool Full_Duplex);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Set_MAC_Address_Filter
int __Sys_Device_Class_ETH_Set_MAC_Address_Filter(int Handle,uint8_t *P_Address);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_ReSet_MAC_Address_Filter
int __Sys_Device_Class_ETH_ReSet_MAC_Address_Filter(int Handle);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Receive
int __Sys_Device_Class_ETH_Receive(int Handle,uint8_t *P_Buffer, uint32_t Size,uint32_t *P_Flag,int32_t TimeOut);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Send
int __Sys_Device_Class_ETH_Send(int Handle,const uint8_t *P_Buffer, uint32_t Size,uint32_t Flag,int32_t TimeOut);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Send_Slice
int __Sys_Device_Class_ETH_Send_Slice(int Handle,const Device_Class_ETH_Send_Slice_Data_Type *P_Buffer, uint32_t Size,uint32_t Flag,int32_t TimeOut);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Get_MDIO
int __Sys_Device_Class_ETH_Get_MDIO(int Handle,uint8_t Phy, uint8_t RegisterAddr, uint16_t *P_Value);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Set_MDIO
int __Sys_Device_Class_ETH_Set_MDIO(int Handle,uint8_t Phy, uint8_t RegisterAddr, uint16_t Value);
#endif
#ifdef Master_OS_Config_Device_Class_ETH_Get_Info
int __Sys_Device_Class_ETH_Get_Info(int Handle,const char **P_Info);
#endif


#endif /* __DEVICE_CLASS_ETH_H_ */
