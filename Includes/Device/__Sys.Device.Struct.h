/*
 * __Sys.Device.Struct.h
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */

#ifndef __SYS_DEVICE_STRUCT_H_
#define __SYS_DEVICE_STRUCT_H_


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

}__Sys_Device_OPS_Type;

//-----------------------------------------------------------




#endif /* __SYS_DEVICE_STRUCT_H_ */
