/*
 * Context_Switch.s
 *
 *  Created on: 2019年4月9日
 *      Author: Master.HE
 */
#include "Interrupt_Header.inc"

	MODULE Context_Switch

	SECTION .text:CODE:REORDER:NOROOT(2)

#if ((__ARM_ARCH == 6) || (__ARM_ARCH == 7)) && (__ARM_ARCH_PROFILE == 'M')


	THUMB

	PUBLIC __Sys_Switch_To_Idle

__Sys_Switch_To_Idle

	MOV R4,R0
	//LDR r0,=0x02020000 ;* End of start stack area *
	//LDR r1,=0x02000000 ;* End of start stack area *
	LDR r12,=0xEFEFEFEF ;* Clear value *
Clear_Idle_Stack_Loop:
	SUB r0, r0, #4 ;* calculate next address in start stack *
	STR r12, [r0] ;* write 32-bit value to force ECC bits calculation *
	CMP r0, r1 ;* check if TCMRAM start is reached *
	BNE Clear_Idle_Stack_Loop


	MSR PSP, R4

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


	ARM

#ifdef __MPU__
	EXTERN __Sys_Scheduling_MPU_SET_Current_Task
#endif

	PUBLIC __Sys_Switch_To_Idle

__Sys_Switch_To_Idle

/*
	EXTERN __Sys_Scheduling_GET_System_SP

	ldr r0,=__Sys_Scheduling_GET_System_SP
	blx r0

	b __Sys_Switch_To_Idle
*/




	MOV R4,R0
	//LDR r0,=0x02020000 ;* End of start stack area *
	//LDR r1,=0x02000000 ;* End of start stack area *
	LDR r12,=0xEFEFEFEF
Clear_Idle_Stack_Loop:
	SUB r0, r0, #4
	STR r12, [r0]
	CMP r0, r1
	BNE Clear_Idle_Stack_Loop

#ifdef __MPU__

	PUSH {r2,r4}

	//mov r0,r3
	//mov r1,r1
	ldr r4,=__Sys_Scheduling_MPU_SET_Current_Task
	blx r4

	POP {r2,r4}

	//add r1,r1,#32

#endif


	MRS r0, cpsr                ; Original PSR value

	BIC r0 ,r0, #MODE_MSK       ; Clear the mode bits
	ORR r0 ,r0, #USR_MODE       ; Set User mode bits
	MSR cpsr_c, r0              ; Change the mode
	//cps #USR_MODE

	mov sp,R4



	mov pc,r2


	PUBLIC __Sys_Switch_To
__Sys_Switch_To

	//检查当前任务 如果存在则保存当前任务的栈到TCB中
	CMP R0,#0x0
	BEQ __Sys_Switch_To_Step2

#ifdef __MPU__

	CMP R2,#0x0
	BEQ __Sys_Switch_To_Step2

	stmdb sp!,{r4-r12,lr}

#else

	stmdb sp!,{r2-r12,lr}

#endif

	
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

	//将下一个任务的栈进行装载进来
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

	LDMIA   r12!, {r4}

	mov r5,r4

	//检查下一个任务的运行模式 如果为user或者system则认为是第一次装载这个任务
	and r4 ,r4, #MODE_MSK

	cmp r4,#USR_MODE

	BEQ __Sys_Switch_To_New

	cmp r4,#SYS_MODE

	BEQ __Sys_Switch_To_New


#ifdef __MPU__
	PUSH {r5,r12}
	ldr r4,=__Sys_Scheduling_MPU_SET_Current_Task
	blx r4
	POP {r5,r12}
#endif


	//不是第一次装载这个任务
	MSR     cpsr_cxsf, r5

	LDMIA   r12!, {r5}

	MSR     spsr_cxsf, r5

	mov sp,r12



#ifdef __MPU__
	ldmia sp!,{r4-r12,pc}
#else
	ldmia sp!,{r2-r12,pc}
#endif



__Sys_Switch_To_New
	//这是新的任务被装载

#ifdef __MPU__
	PUSH {r3,r5}
	ldr r4,=__Sys_Scheduling_MPU_SET_Current_Task
	blx r4
	POP {r3,r5}
#endif

	mov sp,#0//清除内核堆栈指针

	msr cpsr_c, #(SVC_MODE|I_Bit|F_Bit)//切换到SVC模式

	MSR spsr_cxsf, r5

#ifdef __MPU__
	ldr r12,[r3]
#endif

	LDMIA R12!, {lr}

	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式

	mov sp,r12



	ldmia sp!,{r0-r12,lr}


	msr cpsr_c, #(SVC_MODE|I_Bit|F_Bit)//切换到SVC模式


	MOVS PC,LR

	//b __Sys_Switch_To

//-----------------------------------------------------------------
	PUBLIC __Sys_SET_CPU_SP

__Sys_SET_CPU_SP

	and r0 ,r0, #MODE_MSK

	cmp r0,#USR_MODE

	BEQ __Sys_SET_CPU_SP_Usr

__Sys_SET_CPU_SP_1


	MRS r2, cpsr                ; Original PSR value

	mov r3,r2

	BIC r2 ,r2, #MODE_MSK       ; Clear the mode bits
	ORR r2 ,r2, r0       		; Set  mode bits
	MSR cpsr_c, r2              ; Change the mode

	mov sp,r1

	MSR cpsr_c,r3

	blx lr

__Sys_SET_CPU_SP_Usr

	mov r0,#SYS_MODE
	b __Sys_SET_CPU_SP_1

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'A')


#else

#error "123"

#endif


	END
