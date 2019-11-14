/*
 * __Sys.Device.Struct.h
 *
 *  Created on: 2019Äê4ÔÂ12ÈÕ
 *      Author: Master.HE
 */

#ifndef __SYS_DEVICE_STRUCT_H_
#define __SYS_DEVICE_STRUCT_H_


typedef struct
{
	const char *Device_Name;
	const char *Info;

	int (*Open)   (int Mode);
	int (*Close)  (void);
	int (*Read)   (long OffSet_Pos, void *Buffer, unsigned long Size,int TimeOut);
	int (*Write)  (long OffSet_Pos, const void *Buffer, unsigned long Size,int TimeOut);
	int (*Control)(int Cmd, unsigned long Args);

}__Sys_Device_OPS_Type;

//-----------------------------------------------------------




#endif /* __SYS_DEVICE_STRUCT_H_ */
