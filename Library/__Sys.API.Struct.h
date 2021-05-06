/*
 * __Sys.API.Struct.h
 *
 *  Created on: 2021年5月6日
 *      Author: Master.HE
 */

#ifndef SYS_API_STRUCT_H_
#define SYS_API_STRUCT_H_

#include "Master.Stdint.h"


typedef struct __Sys_API_Handle_Node
{
	int Handle;
	struct __Sys_API_Handle_Node *NEXT;
}__Sys_API_Handle_Node_Type;


typedef struct
{
	int Count;
	__Sys_API_Handle_Node_Type *Head;
	__Sys_API_Handle_Node_Type *End;
}__Sys_API_Handle_DATA_Type;

#endif /* SYS_API_STRUCT_H_ */
