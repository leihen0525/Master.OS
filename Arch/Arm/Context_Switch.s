/*
 * Context_Switch.s
 *
 *  Created on: 2019年4月9日
 *      Author: Master.HE
 */
#include "Interrupt_Header.inc"

	MODULE Context_Switch

#if ((__ARM_ARCH == 6) || (__ARM_ARCH == 7)) && (__ARM_ARCH_PROFILE == 'M')

	SECTION .text:CODE:REORDER:NOROOT(2)


	THUMB

	PUBLIC __Sys_Switch_To_Idle

__Sys_Switch_To_Idle

	MOV R3,R0
	//LDR r0,=0x02020000 ;* End of start stack area *
	//LDR r1,=0x02000000 ;* End of start stack area *
	LDR r12,=0xEFEFEFEF ;* Clear value *
Clear_Idle_Stack_Loop:
	SUB r0, r0, #4 ;* calculate next address in start stack *
	STR r12, [r0] ;* write 32-bit value to force ECC bits calculation *
	CMP r0, r1 ;* check if TCMRAM start is reached *
	BNE Clear_Idle_Stack_Loop


	MSR PSP, R3

	mov r0,#0
	MSR MSP, R0

	mov r0,#0x02
	msr control,r0

	mov pc,r2


	PUBLIC __Sys_Switch_To
__Sys_Switch_To

	CMP R0,#0x0
	BEQ __Sys_Switch_To_Step2

	MRS R12, PSP
	PUSH {R12}

	PUSH {lr}

	PUSH {R4-R11}



	MRS R12, MSP
	STR R12,[R0]

__Sys_Switch_To_Step2


	LDR R12, [R1]						// 把next task 的sp指针送到R12中.

	MSR MSP, R12							//将新的SP更新到PSP中


	POP {R4-R11}
	POP {lr}

	POP {R12}
	MSR PSP, R12


	bx lr

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R')

	SECTION .text:CODE:REORDER:NOROOT(2)


	ARM

	PUBLIC __Sys_Switch_To_Idle

__Sys_Switch_To_Idle

	MOV R3,R0
	//LDR r0,=0x02020000 ;* End of start stack area *
	//LDR r1,=0x02000000 ;* End of start stack area *
	LDR r12,=0xEFEFEFEF ;* Clear value *
Clear_Idle_Stack_Loop:
	SUB r0, r0, #4 ;* calculate next address in start stack *
	STR r12, [r0] ;* write 32-bit value to force ECC bits calculation *
	CMP r0, r1 ;* check if TCMRAM start is reached *
	BNE Clear_Idle_Stack_Loop


	MRS r0, cpsr                ; Original PSR value

	BIC r0 ,r0, #MODE_MSK       ; Clear the mode bits
	ORR r0 ,r0, #USR_MODE       ; Set User mode bits
	MSR cpsr_c, r0              ; Change the mode
	//cps #USR_MODE

	mov sp,R3
	mov pc,r2


	PUBLIC __Sys_Switch_To
__Sys_Switch_To

	CMP R0,#0x0
	BEQ __Sys_Switch_To_Step2

	stmdb sp!,{r2-r12,lr}

	
	MRS r4, cpsr
	MRS r5, spsr
	
	stmdb sp!,{r4-r5}

#ifdef __ARMVFP__
	VMRS    r4,  fpexc
	TST     r4,  #0x40000000
	BEQ     __no_vfp_frame1

	VMRS    r5, fpscr
	STMDB   sp!, {r5}

	VSTMDB  sp!, {S0-S31}

__no_vfp_frame1:
	STMDB   sp!, {r4}
#endif


	STR sp,[R0]

__Sys_Switch_To_Step2


	LDR r12, [R1]						// 把next task 的sp指针送到R12中.


#ifdef __ARMVFP__
	LDMIA   r12!, {r4}
	VMSR    fpexc,  r4
	TST     r4,  #0x40000000
	BEQ     __no_vfp_frame2

	VLDMIA  r12!, {S0-S31}

	LDMIA   r12!, {r5}
	VMSR    fpscr, r5

__no_vfp_frame2:
#endif

	LDMIA   r12!, {r2}

	mov r3,r2

	and r2 ,r2, #MODE_MSK

	cmp r2,#USR_MODE

	BEQ __Sys_Switch_To_New

	cmp r2,#SYS_MODE

	BEQ __Sys_Switch_To_New

	MSR     cpsr_cxsf, r3

	LDMIA   r12!, {r3}

	MSR     spsr_cxsf, r3

	mov sp,r12

	ldmia sp!,{r2-r12,pc}


__Sys_Switch_To_New

	msr cpsr_c, #(IRQ_MODE|I_Bit|F_Bit)//切换到SVC模式


	MSR     spsr_cxsf, r3

	LDMIA   R12!, {lr}

	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式

	mov sp,r12

	ldmia sp!,{r0-r12,lr}

	msr cpsr_c, #(IRQ_MODE|I_Bit|F_Bit)//切换到SVC模式

	mov sp,#0//清除内核堆栈指针
	MOVS PC,LR

	b __Sys_Switch_To




#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'A')


#else

#error "123"

#endif


	END
