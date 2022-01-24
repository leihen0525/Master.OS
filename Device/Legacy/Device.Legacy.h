/*
 * Device.Legacy.h
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */

#ifndef DEVICE_LEGACY_H_
#define DEVICE_LEGACY_H_

//#include "Master.OS.Config.h"
#include "Device.Legacy.Struct.h"

int Device_Legacy_Init(void);

int __Sys_Device_Legacy_Register_Drivers(const __Sys_Device_Legacy_OPS_Type *P_OPS);

#ifdef Master_OS_Config_Device_Legacy_Open
int __Sys_Device_Legacy_Open(const char *Device_Name,int Mode);
#endif
#ifdef Master_OS_Config_Device_Legacy_Close
int __Sys_Device_Legacy_Close(int Handle);
#endif
#ifdef Master_OS_Config_Device_Legacy_Read
int __Sys_Device_Legacy_Read(int Handle,long OffSet_Pos, void *Buffer, unsigned long Size,long TimeOut);
#endif
#ifdef Master_OS_Config_Device_Legacy_Write
int __Sys_Device_Legacy_Write(int Handle,long OffSet_Pos, const void *Buffer, unsigned long Size,long TimeOut);
#endif
#ifdef Master_OS_Config_Device_Legacy_Control
int __Sys_Device_Legacy_Control(int Handle,int Cmd, unsigned long Args);
#endif
#ifdef Master_OS_Config_Device_Legacy_Info
int __Sys_Device_Legacy_Info(int Handle,const char **P_Info);
#endif

#endif /* DEVICE_LEGACY_H_ */
