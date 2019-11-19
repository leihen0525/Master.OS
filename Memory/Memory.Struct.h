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
	uint16_t NEXT_Index;

	uint16_t Size		:15;
	uint16_t Free		:1;
}Memory_Node_Type;
#pragma pack()


typedef struct
{

	uint32_t *HEAP_Begin;
	uint32_t *HEAP_End;
	uint32_t HEAP_Size;

	uint32_t Size_Byte;

}Memory_DATA_Type;

#endif /* MEMORY_STRUCT_H_ */
