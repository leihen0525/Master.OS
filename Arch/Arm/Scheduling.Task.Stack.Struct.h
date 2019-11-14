/*
 * Scheduling.Task.Stack.Struct.h
 *
 *  Created on: 2019Äê4ÔÂ23ÈÕ
 *      Author: Master.HE
 */

#ifndef SCHEDULING_TASK_STACK_STRUCT_H_
#define SCHEDULING_TASK_STACK_STRUCT_H_

#include "Master.Stdint.h"

typedef struct
{
#if ((__ARM_ARCH == 6) || (__ARM_ARCH == 7)) && (__ARM_ARCH_PROFILE == 'M')
	uint32_t MSP_R4;
	uint32_t MSP_R5;
	uint32_t MSP_R6;
	uint32_t MSP_R7;
	uint32_t MSP_R8;
	uint32_t MSP_R9;
	uint32_t MSP_R10;
	uint32_t MSP_R11;

	uint32_t MSP_LR;
	


	uint32_t PSP;
	//uint32_t MSP_LR1;

	uint32_t PSP_R0;
	uint32_t PSP_R1;
	uint32_t PSP_R2;
	uint32_t PSP_R3;
	uint32_t PSP_R12;
	uint32_t PSP_LR;
	uint32_t PSP_PC;
	uint32_t xPSR;

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R')


	uint32_t CPU_CPSR;

	uint32_t CPU_PC;

	uint32_t CPU_R[13];

	uint32_t CPU_LR;




#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'A')


#else

#error "123"

#endif

}Scheduling_Task_Stack_CPU_Type;


#ifdef __ARMVFP__
typedef struct
{
	uint32_t VFP_FPEXC;

	uint32_t VFP_S[32];

	uint32_t VFP_FPSCR;
}Scheduling_Task_Stack_VFP_Type;
#endif

#endif /* SCHEDULING_TASK_STACK_STRUCT_H_ */
