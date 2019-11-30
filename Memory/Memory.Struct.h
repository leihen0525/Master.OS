/*
 * Memory.Struct.h
 *
 *  Created on: 2019Äê4ÔÂ12ÈÕ
 *      Author: Master.HE
 */

#ifndef MEMORY_STRUCT_H_
#define MEMORY_STRUCT_H_

#include "Master.Stdint.h"


#pragma pack(1)
typedef struct Memory_Node
{
	uint32_t Size_Byte	:30;
	uint32_t Flag_Size	:1;
	uint32_t Flag_NEXT	:1;

	struct Memory_Node *NEXT;

}Memory_Node_Type;
#pragma pack()

typedef struct
{
	Memory_Node_Type *Begin;

	Memory_Node_Type *End;

	uint32_t Size_Byte;

}Memory_Node_List_Type;

typedef struct
{
	struct
	{
		uint32_t *Begin;
		uint32_t *End;
		uint32_t Size_Byte;
	}HEAP;

	Memory_Node_List_Type Malloc;

	Memory_Node_List_Type Free;

	union
	{
		uint8_t DATA;
		struct
		{
			uint8_t Malloc_Head_Err				:1;
			uint8_t Free_Head_Err				:1;
			uint8_t Null_Err					:1;
			uint8_t Unknown_Err					:1;
			uint8_t Free_Err					:1;
		};
	}Flag;

}Memory_DATA_Type;

#endif /* MEMORY_STRUCT_H_ */
