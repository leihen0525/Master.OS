/*
 * Scheduling.Task.Stack.c
 *
 *  Created on: 2019年4月23日
 *      Author: Master.HE
 */
#include "Error.h"

#include "Scheduling.Task.Stack.Struct.h"

#include "Scheduling.Task.Stack.h"


int Scheduling_Task_Stack_Init(
		Task_Enter_Function Task_Enter,
		void *Args,
#ifdef Master_OS_Config_Scheduling_Exit_Task
		Task_Exit_Function Task_Exit,
#endif
#ifdef __UsrSP_SysSP__
		uint32_t **Sys_SP,
		uint32_t **Usr_SP,
#else
		uint32_t **SP,
#endif
		int Option)
{


	if(Task_Enter==Null
#ifdef Master_OS_Config_Scheduling_Exit_Task
	|| Task_Exit==Null
#endif
#ifdef __UsrSP_SysSP__
	|| Sys_SP==Null
	|| Usr_SP==Null
#else
	|| SP==Null
#endif
	)
	{
		return Error_Invalid_Parameter;
	}

#if ((__ARM_ARCH == 6) || (__ARM_ARCH == 7)) && (__ARM_ARCH_PROFILE == 'M')

#ifdef __UsrSP_SysSP__
	Scheduling_Task_Stack_CPU_PSP_Type *P_Task_Stack_CPU_PSP;
	*Usr_SP=(uint32_t*)((uint32_t)(*Usr_SP)-sizeof(Scheduling_Task_Stack_CPU_PSP_Type)+4);
	P_Task_Stack_CPU_PSP=(Scheduling_Task_Stack_CPU_PSP_Type *)*Usr_SP;

	Scheduling_Task_Stack_CPU_MSP_Type *P_Task_Stack_CPU_MSP;
	*Sys_SP=(uint32_t*)((uint32_t)(*Sys_SP)-sizeof(Scheduling_Task_Stack_CPU_MSP_Type)+4);
	P_Task_Stack_CPU_MSP=(Scheduling_Task_Stack_CPU_MSP_Type *)*Sys_SP;


	P_Task_Stack_CPU_MSP->MSP_R4=0x44444444;
	P_Task_Stack_CPU_MSP->MSP_R5=0x55555555;
	P_Task_Stack_CPU_MSP->MSP_R6=0x66666666;
	P_Task_Stack_CPU_MSP->MSP_R7=0x77777777;
	P_Task_Stack_CPU_MSP->MSP_R8=0x88888888;
	P_Task_Stack_CPU_MSP->MSP_R9=0x99999999;
	P_Task_Stack_CPU_MSP->MSP_R10=0xAAAAAAAA;
	P_Task_Stack_CPU_MSP->MSP_R11=0xBBBBBBBB;
	P_Task_Stack_CPU_MSP->MSP_R12=0xCCCCCCCC;

	P_Task_Stack_CPU_MSP->MSP_LR=0xfffffffd;


	P_Task_Stack_CPU_PSP->PSP_R0=(uint32_t)Args;
	P_Task_Stack_CPU_PSP->PSP_R1=0x11111111;
	P_Task_Stack_CPU_PSP->PSP_R2=0x22222222;
	P_Task_Stack_CPU_PSP->PSP_R3=0x33333333;
	P_Task_Stack_CPU_PSP->PSP_R12=0xCCCCCCCC;
#ifdef Master_OS_Config_Scheduling_Exit_Task
	P_Task_Stack_CPU_PSP->PSP_LR=(uint32_t)Task_Exit;
#else
	P_Task_Stack_CPU_PSP->PSP_LR=0xFFFFFFFF,//?????
#endif
	P_Task_Stack_CPU_PSP->PSP_PC=(uint32_t)Task_Enter;
	P_Task_Stack_CPU_PSP->xPSR=0x01000000;




#else
	Scheduling_Task_Stack_CPU_Type *P_Task_Stack_CPU;
	*SP=(uint32_t*)((uint32_t)(*SP)-sizeof(Scheduling_Task_Stack_CPU_Type)+4);
	P_Task_Stack_CPU=(Scheduling_Task_Stack_CPU_Type *)*SP;


	P_Task_Stack_CPU->MSP_R4=0x44444444;
	P_Task_Stack_CPU->MSP_R5=0x55555555;
	P_Task_Stack_CPU->MSP_R6=0x66666666;
	P_Task_Stack_CPU->MSP_R7=0x77777777;
	P_Task_Stack_CPU->MSP_R8=0x88888888;
	P_Task_Stack_CPU->MSP_R9=0x99999999;
	P_Task_Stack_CPU->MSP_R10=0xAAAAAAAA;
	P_Task_Stack_CPU->MSP_R11=0xBBBBBBBB;
	P_Task_Stack_CPU->MSP_R12=0xCCCCCCCC;
	P_Task_Stack_CPU->MSP_LR=0xfffffffd;


	P_Task_Stack_CPU->PSP=(uint32_t)&P_Task_Stack_CPU->PSP_R0;

	P_Task_Stack_CPU->PSP_R0=(uint32_t)Args;
	P_Task_Stack_CPU->PSP_R1=0x11111111;
	P_Task_Stack_CPU->PSP_R2=0x22222222;
	P_Task_Stack_CPU->PSP_R3=0x33333333;
	P_Task_Stack_CPU->PSP_R12=0xCCCCCCCC;
	P_Task_Stack_CPU->PSP_LR=(uint32_t)Task_Exit;
	P_Task_Stack_CPU->PSP_PC=(uint32_t)Task_Enter;
	P_Task_Stack_CPU->xPSR=0x01000000;

#endif

	return Error_OK;

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R')

	int VFP_Nb=0;

#ifdef __ARMVFP__
	if((Option&Scheduling_Task_Option_FPU_VFP)!=0)
	{
		VFP_Nb=sizeof(Scheduling_Task_Stack_VFP_Type);
	}
	else
	{
		VFP_Nb=4;
	}
#endif

#ifdef __UsrSP_SysSP__

#else

#endif

#ifdef __UsrSP_SysSP__
	*Sys_SP=(uint32_t*)((uint32_t)(*Sys_SP)-sizeof(Scheduling_Task_Stack_CPU_Type)-sizeof(Scheduling_Task_Stack_CPU_CPSR_Type)-VFP_Nb+4);
	*Usr_SP=(uint32_t*)((uint32_t)(*Usr_SP)-sizeof(Scheduling_Task_Stack_CPU_Type)+4);
#else
	*SP=(uint32_t*)((uint32_t)(*SP)-sizeof(Scheduling_Task_Stack_CPU_Type)-sizeof(Scheduling_Task_Stack_CPU_CPSR_Type)-VFP_Nb+4);
#endif

#ifdef __ARMVFP__

	Scheduling_Task_Stack_VFP_Type *P_Task_Stack_VFP;

#ifdef __UsrSP_SysSP__
	P_Task_Stack_VFP=(Scheduling_Task_Stack_VFP_Type *)*Sys_SP;
#else
	P_Task_Stack_VFP=(Scheduling_Task_Stack_VFP_Type *)*SP;
#endif

	//P_Task_Stack_VFP->VFP_FPEXC.DATA=0;

	if((Option&Scheduling_Task_Option_FPU_VFP)!=0)
	{
		P_Task_Stack_VFP->VFP_FPEXC=(Scheduling_Task_Stack_VFP_FPEXC_Type){.EN=1};
		for(int i=0; i<32;i++)
		{
			P_Task_Stack_VFP->VFP_S[i]=0;
		}
		P_Task_Stack_VFP->VFP_FPSCR=(Scheduling_Task_Stack_VFP_FPSCR_Type){.DN=1};
	}
	else
	{
		P_Task_Stack_VFP->VFP_FPEXC=(Scheduling_Task_Stack_VFP_FPEXC_Type){.EN=0};
	}

#endif

	Scheduling_Task_Stack_CPU_CPSR_Type *P_CPU_CPSR;

#ifdef __UsrSP_SysSP__
	P_CPU_CPSR=(Scheduling_Task_Stack_CPU_CPSR_Type *)((uint32_t)(*Sys_SP)+VFP_Nb);
#else
	P_CPU_CPSR=(Scheduling_Task_Stack_CPU_CPSR_Type *)((uint32_t)(*SP)+VFP_Nb);
#endif

	P_CPU_CPSR->DATA=0;

	if((Option&Scheduling_Task_Option_System)!=0)
	{
		P_CPU_CPSR->M=0x1F;
	}
	else
	{
		P_CPU_CPSR->M=0x10;
	}

	if(((uint32_t)Task_Enter&0x01)!=0)
	{
		P_CPU_CPSR->T=1;
	}
	else
	{
		P_CPU_CPSR->T=0;
	}
#ifdef __UsrSP_SysSP__
	P_Task_Stack_CPU=(Scheduling_Task_Stack_CPU_Type *)((uint32_t)(*Usr_SP));
#else
	P_Task_Stack_CPU=(Scheduling_Task_Stack_CPU_Type *)((uint32_t)(*SP)+VFP_Nb+sizeof(Scheduling_Task_Stack_CPU_CPSR_Type));
#endif

	P_Task_Stack_CPU->CPU_R[0]=(uint32_t)Args;
	P_Task_Stack_CPU->CPU_R[1]=0x01;
	P_Task_Stack_CPU->CPU_R[2]=0x02;
	P_Task_Stack_CPU->CPU_R[3]=0x03;
	P_Task_Stack_CPU->CPU_R[4]=0x04;
	P_Task_Stack_CPU->CPU_R[5]=0x05;
	P_Task_Stack_CPU->CPU_R[6]=0x06;
	P_Task_Stack_CPU->CPU_R[7]=0x07;
	P_Task_Stack_CPU->CPU_R[8]=0x08;
	P_Task_Stack_CPU->CPU_R[9]=0x09;
	P_Task_Stack_CPU->CPU_R[10]=0x10;
	P_Task_Stack_CPU->CPU_R[11]=0x11;
	P_Task_Stack_CPU->CPU_R[12]=0x12;

	P_Task_Stack_CPU->CPU_LR=(uint32_t)Task_Exit;
	P_Task_Stack_CPU->CPU_PC=(uint32_t)Task_Enter;


	return Error_OK;


#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'A')


#else

#error "123"

#endif
}
