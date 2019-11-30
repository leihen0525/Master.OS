/*
 * Memory.h
 *
 *  Created on: 2019Äê4ÔÂ12ÈÕ
 *      Author: Master.HE
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "Master.Stdint.h"

#include "Memory.Struct.h"

int __Sys_Memory_Init(void);

uint32_t __Sys_Memory_Size_Malloc(void);
uint32_t __Sys_Memory_Size_Free(void);
void *__Sys_Memory_Malloc_Align(uint32_t Size,uint32_t Align);
void *__Sys_Memory_Malloc(uint32_t Size);

void __Sys_Memory_Free(void *ap);

uint32_t __Usr_Memory_Size_Malloc(void);
uint32_t __Usr_Memory_Size_Free(void);
void *__Usr_Memory_Malloc_Align(uint32_t Size,uint32_t Align);
void *__Usr_Memory_Malloc(uint32_t Size);

void __Usr_Memory_Free(void *ap);

int __Memory_Init(
		Memory_DATA_Type *P_Memory_DATA,
		uint32_t *HEAP_Begin,
		uint32_t *HEAP_End,
		uint32_t HEAP_Size);

uint32_t __Memory_Size_Malloc(Memory_DATA_Type *P_Memory_DATA);
uint32_t __Memory_Size_Free(Memory_DATA_Type *P_Memory_DATA);
void *__Memory_Malloc(Memory_DATA_Type *P_Memory_DATA,uint32_t Size,uint32_t Align);
void __Memory_Free(Memory_DATA_Type *P_Memory_DATA,void *ap);

int __Memory_Calculate_Node_Verify(Memory_Node_Type *P_Node_DATA,uint32_t Size_Byte,Memory_Node_Type *P_Node_NEXT);
int __Memory_Check_Node_Verify(Memory_Node_Type *P_Node_DATA);

#endif /* MEMORY_H_ */
