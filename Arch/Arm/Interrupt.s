/*
 * Interrupt.S
 *
 *  Created on: 2019年4月4日
 *      Author: Master.HE
 */
#include "Interrupt_Header.inc"

	MODULE Interrupt

#if ((__ARM_ARCH == 6) || (__ARM_ARCH == 7)) && (__ARM_ARCH_PROFILE == 'M')

	SECTION .text:CODE:REORDER:NOROOT(2)


	EXTERN __Sys_Call_Table
	EXTERN __IRQ_Entry
	//EXTERN __Scheduling_SysTick_Entry
	//EXTERN __Scheduling_PendSV_Entry
	//EXTERN __Timer_SysTick_Entry


	THUMB

	PUBLIC __Invalid_Entry
__Invalid_Entry
	B __Invalid_Entry

	PUBLIC __SVC_Entry
__SVC_Entry


	Exception_Entry


	sub sp,sp,#0x10

	str r7,[sp,#0xC]
	str r6,[sp,#0x8]
	str r5,[sp,#0x4]
	str r4,[sp]

	ldr r6,=__Sys_Call_Table
	lsls r8,r8,#2
	ldr r8,[r6,r8]
	blx r8

	add sp,sp,#0x10

	MRS R7, PSP

	str r0,[r7]


	Exception_Slow_Exit

	bx lr

	//B __SVC_Entry
/*
	PUBLIC __PendSV_Entry
__PendSV_Entry
	Exception_Entry



	ldr r0,=__Scheduling_PendSV_Entry
	blx r0



	Exception_Slow_Exit

	bx lr
	//B __PendSV_Entry
*/

/*
	PUBLIC __SysTick_Entry
__SysTick_Entry

	Exception_Entry

	ldr r0,=__Scheduling_SysTick_Entry
	blx r0

	ldr r0,=__Timer_SysTick_Entry
	blx r0

	Exception_Fast_Exit

	bx lr
*/



	PUBLIC __Interrupt_Entry
__Interrupt_Entry


	Exception_Entry


	ldr r1,=__IRQ_Entry
	blx r1


	Exception_Fast_Exit

	bx lr


	//B __Interrupt_Entry

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R')

	SECTION .text:CODE:NOROOT(2)

	EXTERN __Sys_Call_Table
	EXTERN __IRQ_Entry

#ifdef __MPU__
	EXTERN __Sys_Scheduling_GET_System_SP_End
	EXTERN __Sys_Scheduling_GET_User_SP
	EXTERN MPU_Handle_Data_Fault
#endif

	ARM

	//特权模式M[4∶0]=0b10011-Supervisor
	PUBLIC __SVC_Entry
__SVC_Entry

	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式

	stmdb sp!,{r0-r12,lr}//压栈

#ifdef __MPU__

	mov r9,r0
	mov r10,r1
	mov r11,r2
	mov r12,r3

	ldr r0,=__Sys_Scheduling_GET_User_SP
	blx r0
	str sp,[r0]

	ldr r0,=__Sys_Scheduling_GET_System_SP_End
	blx r0

	msr cpsr_c, #(SVC_MODE|I_Bit|F_Bit)//切换到SVC模式

	ldr sp,[r0]

	mov r0,r9
	mov r1,r10
	mov r2,r11
	mov r3,r12

#else
	mov r12,sp

	msr cpsr_c, #(SVC_MODE|I_Bit|F_Bit)//切换到SVC模式

	mov sp,r12
#endif

	STMDB sp!, {lr}
//

	sub sp,sp,#0x10

	str r7,[sp,#0xC]
	str r6,[sp,#0x8]
	str r5,[sp,#0x4]
	str r4,[sp]

	ldr r6,=__Sys_Call_Table
	lsls r8,r8,#2
	ldr r8,[r6,r8]
	blx r8

	add sp,sp,#0x10


//


#ifdef __MPU__

	mov r12,r0

	ldr r0,=__Sys_Scheduling_GET_User_SP
	blx r0

	LDMIA sp!, {lr}

	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式

	ldr sp,[r0]

	mov r0,r12

#else

	LDMIA sp!, {lr}

	mov r12,sp
	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式

	mov sp,r12
#endif

	str r0,[sp]//修正返回值

	ldmia sp!,{r0-r12,lr}

	msr cpsr_c, #(SVC_MODE|I_Bit|F_Bit)//切换到SVC模式

	mov sp,#0//清除内核堆栈指针

	MOVS PC,LR

	//b __SVC_Entry

//---------------------------------
	//外部中断请求M[4∶0]=0b10010-IRQ
	PUBLIC __Interrupt_Entry
__Interrupt_Entry

	SUB LR, LR, #4

	msr cpsr_c, #(SYS_MODE | I_Bit | F_Bit)//切换到sys模式

	stmdb sp!,{r0-r12,lr}//压栈

#ifdef __MPU__

	ldr r0,=__Sys_Scheduling_GET_User_SP
	blx r0
	str sp,[r0]

	ldr r0,=__Sys_Scheduling_GET_System_SP_End
	blx r0

	msr cpsr_c, #(IRQ_MODE|I_Bit|F_Bit)//切换到IRQ模式

	ldr sp,[r0]

#else

	mov r12,sp

	msr cpsr_c, #(IRQ_MODE|I_Bit|F_Bit)//切换到IRQ模式

	mov sp,r12

#endif

	STMDB sp!, {lr}
//


	ldr r1,=__IRQ_Entry
	blx r1

//

#ifdef __MPU__

	ldr r0,=__Sys_Scheduling_GET_User_SP
	blx r0

	LDMIA sp!, {lr}

	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式

	ldr sp,[r0]

#else

	LDMIA sp!, {lr}

	mov r12,sp
	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式

	mov sp,r12

#endif

	ldmia sp!,{r0-r12,lr}

	msr cpsr_c, #(IRQ_MODE|I_Bit|F_Bit)//切换到IRQ模式
	mov sp,#0//清除内核堆栈指针
	MOVS PC,LR

	//b __Interrupt_Entry
//---------------------------------------------------------------------
	//未定义指令中止//M[4∶0]=0b11011-Undefined
	PUBLIC Undefined_Handler
Undefined_Handler


	b Undefined_Handler
//---------------------------------------------------------------------
	//预取指令访问中止//M[4∶0]=0b10111-Abort
	PUBLIC Prefetch_Handler
Prefetch_Handler

	SUB LR, LR, #4


	b Prefetch_Handler
//---------------------------------------------------------------------
	//数据访问中止//M[4∶0]=0b10111-Abort
	PUBLIC Abort_Handler
Abort_Handler

	SUB LR, LR, #8

	stmdb sp!,{r0-r12,lr}//压栈

#ifdef __MPU__

	MRS r0, spsr
	and r0 ,r0, #MODE_MSK


	cmp r0,#USR_MODE

	BEQ Abort_Handler_GET_USR_SYS_SP

	cmp r0,#SYS_MODE

	BEQ Abort_Handler_GET_USR_SYS_SP

	cmp r0,#FIQ_MODE

	BEQ Abort_Handler_GET_FIQ_SP

	cmp r0,#IRQ_MODE

	BEQ Abort_Handler_GET_IRQ_SP

	cmp r0,#SVC_MODE

	BEQ Abort_Handler_GET_SVC_SP

Abort_Handler_GET_USR_SYS_SP

	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式
	mov r1,sp
	b Abort_Handler_GET_SP_Exit

Abort_Handler_GET_FIQ_SP
	msr cpsr_c, #(FIQ_MODE|I_Bit|F_Bit)//切换到FIQ模式
	mov r1,sp
	b Abort_Handler_GET_SP_Exit

Abort_Handler_GET_IRQ_SP
	msr cpsr_c, #(IRQ_MODE|I_Bit|F_Bit)//切换到IRQ模式
	mov r1,sp
	b Abort_Handler_GET_SP_Exit

Abort_Handler_GET_SVC_SP
	msr cpsr_c, #(SVC_MODE|I_Bit|F_Bit)//切换到SVC模式
	mov r1,sp
	b Abort_Handler_GET_SP_Exit


Abort_Handler_GET_SP_Exit

	msr cpsr_c, #(ABT_MODE|I_Bit|F_Bit)//切换到ABT模式

	mov r2, lr


	ldr r4,=MPU_Handle_Data_Fault
	blx r4


#else
Abort_Handler_Undefined

	b Abort_Handler_Undefined

#endif

	ldmia sp!,{r0-r12,pc}^

	b Abort_Handler
//---------------------------------------------------------------------
#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'A')


#else

#error "123"

#endif


	END
