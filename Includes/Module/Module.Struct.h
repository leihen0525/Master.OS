/*
 * Module.Struct.h
 *
 *  Created on: 2019Äê9ÔÂ27ÈÕ
 *      Author: Master.HE
 */

#ifndef MODULE_STRUCT_H_
#define MODULE_STRUCT_H_

#include "Master.Stdint.h"

#include "Scheduling.Task.Define.h"

typedef struct
{
	char *Name;
	Task_Enter_Function Task_Enter;
	void *Args;
	uint8_t Priority;
	uint32_t *Stack;
	uint32_t Stack_Size_4Byte;
	int Option;
}__Module_Init_Task_Type;


#endif /* MODULE_STRUCT_H_ */
