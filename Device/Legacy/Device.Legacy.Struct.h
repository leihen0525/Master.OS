/*
 * Device.Legacy.Struct.h
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */

#ifndef DEVICE_LEGACY_STRUCT_H_
#define DEVICE_LEGACY_STRUCT_H_

#include "Device/Legacy/__Sys.Device.Legacy.Struct.h"

typedef struct Device_Legacy_NODE
{
	int Handle;

	const __Sys_Device_Legacy_OPS_Type *P_OPS;

	struct Device_Legacy_NODE *NEXT;
}Device_Legacy_Node_Type;

typedef struct
{
	int Count;
	Device_Legacy_Node_Type *Head;
	Device_Legacy_Node_Type *End;

}Device_Legacy_Node_List_Type;

typedef struct
{

	Device_Legacy_Node_List_Type Node_List;

}Device_Legacy_DATA_Type;

#endif /* DEVICE_LEGACY_STRUCT_H_ */
