/*
 * Scheduling.Task.Stack.Struct.h
 *
 *  Created on: 2019Äê4ÔÂ23ÈÕ
 *      Author: Master.HE
 */

#ifndef SCHEDULING_TASK_STACK_STRUCT_H_
#define SCHEDULING_TASK_STACK_STRUCT_H_

#include "Master.Stdint.h"


#if ((__ARM_ARCH == 6) || (__ARM_ARCH == 7)) && (__ARM_ARCH_PROFILE == 'M')
typedef struct
{
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

}Scheduling_Task_Stack_CPU_Type;

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R')

typedef union
{
	uint32_t DATA;
	struct
	{
		uint32_t M				:5;
		uint32_t T				:1;
		uint32_t F				:1;
		uint32_t I				:1;

		uint32_t A				:1;
		uint32_t E				:1;
		uint32_t IT_7_2			:6;

		uint32_t GE				:4;
		uint32_t DNM			:4;

		uint32_t J				:1;
		uint32_t IT_1_0			:2;
		uint32_t Q				:1;
		uint32_t V				:1;
		uint32_t C				:1;
		uint32_t Z				:1;
		uint32_t N				:1;
	};
}Scheduling_Task_Stack_CPU_CPSR_Type;

typedef struct
{

	Scheduling_Task_Stack_CPU_CPSR_Type CPU_CPSR;

	uint32_t CPU_PC;

	uint32_t CPU_R[13];

	uint32_t CPU_LR;


}Scheduling_Task_Stack_CPU_Type;

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'A')


#else

#error "123"

#endif



#ifdef __ARMVFP__

typedef union
{
	uint32_t DATA;
	struct
	{
		uint32_t			:30;
		uint32_t EN			:1;
		uint32_t EX			:1;

	};
}Scheduling_Task_Stack_VFP_FPEXC_Type;


typedef struct
{
	Scheduling_Task_Stack_VFP_FPEXC_Type VFP_FPEXC;

	uint32_t VFP_S[32];

	uint32_t VFP_FPSCR;
}Scheduling_Task_Stack_VFP_Type;
#endif

#endif /* SCHEDULING_TASK_STACK_STRUCT_H_ */
