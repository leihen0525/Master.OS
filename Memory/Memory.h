/*
 * Memory.h
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "Master.Stdint.h"
#include "Master.OS.Config.h"

#include "Memory.Struct.h"

int __Sys_Memory_Init(void);

#ifdef Master_OS_Config_Memory_Size_Malloc
uint32_t __Sys_Memory_Size_Malloc(void);
#endif
#ifdef Master_OS_Config_Memory_Size_Free
uint32_t __Sys_Memory_Size_Free(void);
#endif
#ifdef Master_OS_Config_Memory_Malloc_Align
void *__Sys_Memory_Malloc_Align(uint32_t Size,uint32_t Align);
#endif
#ifdef Master_OS_Config_Memory_Malloc
void *__Sys_Memory_Malloc(uint32_t Size);
#endif
#ifdef Master_OS_Config_Memory_Free
void __Sys_Memory_Free(void *ap);
#endif

uint32_t __Usr_Memory_Size_Malloc(void);
uint32_t __Usr_Memory_Size_Free(void);
void *__Usr_Memory_Malloc_Align(uint32_t Size,uint32_t Align);
void *__Usr_Memory_Malloc(uint32_t Size);

void __Usr_Memory_Free(void *ap);
//------------------------------------------------
int __Memory_Test_List(Memory_Node_List_Type *P_List_DATA);
int __Memory_Init(
		Memory_DATA_Type *P_Memory_DATA,
		uint8_t *HEAP,
		uint32_t Size);

uint32_t __Memory_Size_Malloc(Memory_DATA_Type *P_Memory_DATA);
uint32_t __Memory_Size_Free(Memory_DATA_Type *P_Memory_DATA);
void *__Memory_Malloc(Memory_DATA_Type *P_Memory_DATA,uint32_t Size,uint32_t Align);
void __Memory_Free(Memory_DATA_Type *P_Memory_DATA,void *ap);
//-------------------------------------------------

int __Memory_Calculate_Node_Verify(Memory_Node_Type *P_Node_DATA,uint32_t Size_Byte,Memory_Node_Type *P_Node_NEXT);
int __Memory_Check_Node_Verify(Memory_Node_Type *P_Node_DATA);

#endif /* MEMORY_H_ */
