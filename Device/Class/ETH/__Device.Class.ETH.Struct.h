/*
 * __Device.Class.ETH.Struct.h
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */

#ifndef __DEVICE_CLASS_ETH_STRUCT_H_
#define __DEVICE_CLASS_ETH_STRUCT_H_

#include "Device/Class/ETH/__Sys.Device.Class.ETH.Struct.h"

typedef struct Device_Class_ETH_NODE
{
	int Handle;

	const __Sys_Device_Class_ETH_OPS_Type *P_OPS;

	struct Device_Class_ETH_NODE *NEXT;
}Device_Class_ETH_Node_Type;

typedef struct
{
	int Count;
	Device_Class_ETH_Node_Type *Head;
	Device_Class_ETH_Node_Type *End;
}Device_Class_ETH_Node_List_Type;

typedef struct
{
	Device_Class_ETH_Node_List_Type ETH_Node_List;

}Device_Class_ETH_DATA_Type;

#endif /* __DEVICE_CLASS_ETH_STRUCT_H_ */
