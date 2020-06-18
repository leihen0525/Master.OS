/*
 * Device.h
 *
 *  Created on: 2019年4月14日
 *      Author: Master.HE
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include "Master.OS.Config.h"
#include "Device.Struct.h"

int Device_Init(void);

int Device_Find_Node_To_Name(const char *Device_Name,Device_Node_Type **P_Node);
int Device_Find_Node_To_Handle(int Handle,Device_Node_Type **P_Node);
int Device_Add_Node(const __Sys_Device_OPS_Type *P_OPS);
int Device_Del_Node(int Handle);




#endif /* DEVICE_H_ */
