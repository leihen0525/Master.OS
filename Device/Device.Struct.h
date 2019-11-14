/*
 * Device.Struct.h
 *
 *  Created on: 2019Äê4ÔÂ14ÈÕ
 *      Author: Master.HE
 */

#ifndef DEVICE_STRUCT_H_
#define DEVICE_STRUCT_H_

#include "Device\__Sys.Device.Struct.h"

typedef struct Device_Node_List
{
	int Handle;

	const __Sys_Device_OPS_Type *P_OPS;

	struct Device_Node_List *NEXT;
}Device_Node_Type;

typedef struct
{
	//int Handle_Index;

	struct
	{
		Device_Node_Type *Head;
		Device_Node_Type *End;
	}List_Node;

}Device_DATA_Type;

#endif /* DEVICE_STRUCT_H_ */
