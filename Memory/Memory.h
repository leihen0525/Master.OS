/*
 * Memory.h
 *
 *  Created on: 2019Äê4ÔÂ12ÈÕ
 *      Author: Master.HE
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "Master.Stdint.h"

void Memory_Init(void);

uint32_t __Sys_Memory_Size(void);

void *__Sys_Memory_Malloc(unsigned int Size);

void __Sys_Memory_Free(void *ap);

#endif /* MEMORY_H_ */
