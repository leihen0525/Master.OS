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

uint32_t __Sys_Memory_Size(void);

void *__Sys_Memory_Malloc(unsigned int Size);

void __Sys_Memory_Free(void *ap);

uint32_t __Usr_Memory_Size(void);

void *__Usr_Memory_Malloc(unsigned int Size);

void __Usr_Memory_Free(void *ap);

int __Memory_Init(
		Memory_DATA_Type *P_Memory_DATA,
		uint32_t *HEAP_Begin,
		uint32_t *HEAP_End,
		uint32_t HEAP_Size);

uint32_t __Memory_Size(Memory_DATA_Type *P_Memory_DATA);
void *__Memory_Malloc(Memory_DATA_Type *P_Memory_DATA,unsigned int Size);
void __Memory_Free(Memory_DATA_Type *P_Memory_DATA,void *ap);

#endif /* MEMORY_H_ */
