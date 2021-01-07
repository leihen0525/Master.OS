/*
 * Context_Switch.s
 *
 *  Created on: 2019年4月9日
 *      Author: Master.HE
 */

//__Sys_Switch_To_Idle
//1.初始化用户堆栈空间
//2.将用户堆栈空间指针给用户SP
//3.将内核堆栈空间指针给内核SP
//4.跳转到Task_Enter处运行

//__Sys_Switch_To
//1.判断当前任务TCB的内核和用户堆栈空间指针是否为空
//2.不为空，则保存当前CPU寄存器信息到当前任务的TCB中
//3.将下一个运行任务的TCB的内核和用户堆栈空间数据从TCB中取出，并初始化当前CPU寄存器


#if (__ARM_ARCH == 6) && (__ARM_ARCH_PROFILE == 'M')

	MODULE Context_Switch

	SECTION .text:CODE:REORDER:NOROOT(2)

	THUMB

	PUBLIC __Sys_Switch_To_Idle

__Sys_Switch_To_Idle

	MSR PSP, R0

	LDR r4,=0xEFEFEFEF ;* Clear value *
Clear_Idle_Stack_Loop:
	SUBS r0, r0, #4 ;* calculate next address in start stack *
	STR r4, [r0] ;* write 32-bit value to force ECC bits calculation *
	CMP r0, r1 ;* check if TCMRAM start is reached *
	BNE Clear_Idle_Stack_Loop


#ifdef __UsrSP_SysSP__
	MSR MSP, R3
#else
	movs r0,#0
	MSR MSP, R0
#endif

	movs r0,#0x02
	msr control,r0

	mov pc,r2


	PUBLIC __Sys_Switch_To
__Sys_Switch_To


	//检查当前任务 如果存在则保存当前任务的栈到TCB中
	CMP R0,#0x0
	BEQ __Sys_Switch_To_Step2

#ifdef __UsrSP_SysSP__
	CMP R2,#0x0
	BEQ __Sys_Switch_To_Step2



	stmdb sp!,{r4-r7,lr}

	mov r4,r8
	mov r5,r9
	mov r6,r10
	mov r7,r11
	stmdb sp!,{r4-r7}

	mov r4,r12
	stmdb sp!,{r4}


	MRS R4, MSP
	STR R4,[R0]

	MRS R4,PSP
	STR R4,[R2]
#else


	stmdb sp!,{r4-r7,lr}

	mov r4,r8
	mov r5,r9
	mov r6,r10
	mov r7,r11
	stmdb sp!,{r4-r7}

	mov r4,r12
	stmdb sp!,{r4}


	MRS R4, PSP
	PUSH {R4}


	MRS R4, MSP
	STR R4,[R0]

#endif

__Sys_Switch_To_Step2

#ifdef __UsrSP_SysSP__
	//将下一个任务的栈进行装载进来
	LDR r0, [R1]						// 把next task 的sp指针送到R0中
	MSR MSP,r0

	LDR r0,[r3]
	MSR PSP,r0


	ldmia sp!,{r4}
	mov r12,r4

	ldmia sp!,{r4-r7}
	mov r8,r4
	mov r9,r5
	mov r10,r6
	mov r11,r7

	ldmia sp!,{r4-r7,pc}


#else

	LDR R0, [R1]						// 把next task 的sp指针送到R12中.
	MSR MSP, R0							//将新的SP更新到PSP中

	POP {R4}
	MSR PSP, R4

	ldmia sp!,{r4}
	mov r12,r4

	ldmia sp!,{r4-r7}
	mov r8,r4
	mov r9,r5
	mov r10,r6
	mov r11,r7

	ldmia sp!,{r4-r7,pc}

#endif


#endif


	END
