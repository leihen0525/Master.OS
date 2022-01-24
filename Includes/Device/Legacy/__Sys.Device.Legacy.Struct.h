/*
 * __Sys.Device.Legacy.Struct.h
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */

#ifndef SYS_DEVICE_LEGACY_STRUCT_H_
#define SYS_DEVICE_LEGACY_STRUCT_H_


typedef struct
{
	const char *Device_Name;
	const char *Info;

	void *Device_Args;

	int (*Open)   (void *Device_Args,int Mode);
	int (*Close)  (void *Device_Args);
	int (*Read)   (void *Device_Args,long OffSet_Pos, void *Buffer, unsigned long Size,long TimeOut);
	int (*Write)  (void *Device_Args,long OffSet_Pos, const void *Buffer, unsigned long Size,long TimeOut);
	int (*Control)(void *Device_Args,int Cmd, unsigned long Args);

}__Sys_Device_Legacy_OPS_Type;

//-----------------------------------------------------------



#endif /* SYS_DEVICE_LEGACY_STRUCT_H_ */
