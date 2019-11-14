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


	EXTERN __SysCall_Table
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


	sub sp,sp,#0x0c

	str r6,[sp,#0x8]
	str r5,[sp,#0x4]
	str r4,[sp]

	ldr r6,=__SysCall_Table
	lsls r7,r7,#2
	ldr r7,[r6,r7]
	blx r7

	add sp,sp,#0x0c

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

	EXTERN __SysCall_Table
	EXTERN __IRQ_Entry

	ARM

	PUBLIC __SVC_Entry
__SVC_Entry

	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式

	stmdb sp!,{r0-r12,lr}//压栈

	mov r12,sp

	msr cpsr_c, #(SVC_MODE|I_Bit|F_Bit)//切换到SVC模式

	mov sp,r12

	STMDB sp!, {lr}
//

	sub sp,sp,#0x0c

	str r6,[sp,#0x8]
	str r5,[sp,#0x4]
	str r4,[sp]

	ldr r6,=__SysCall_Table
	lsls r7,r7,#2
	ldr r7,[r6,r7]
	blx r7

	add sp,sp,#0x0c


//
	LDMIA sp!, {lr}
	mov r12,sp
	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式

	mov sp,r12

	str r0,[sp]//修正返回值

	ldmia sp!,{r0-r12,lr}

	msr cpsr_c, #(SVC_MODE|I_Bit|F_Bit)//切换到SVC模式
	mov sp,#0//清除内核堆栈指针
	MOVS PC,LR

	b __SVC_Entry

//---------------------------------
	PUBLIC __Interrupt_Entry
__Interrupt_Entry

	SUB LR, LR, #4

	msr cpsr_c, #(SYS_MODE | I_Bit | F_Bit)//切换到sys模式

	stmdb sp!,{r0-r12,lr}//压栈

	mov r12,sp

	msr cpsr_c, #(IRQ_MODE|I_Bit|F_Bit)//切换到IRQ模式

	mov sp,r12

	STMDB sp!, {lr}
//


	ldr r1,=__IRQ_Entry
	blx r1

//
	LDMIA sp!, {lr}
	mov r12,sp
	msr cpsr_c, #(SYS_MODE|I_Bit|F_Bit)//切换到sys模式

	mov sp,r12

	ldmia sp!,{r0-r12,lr}

	msr cpsr_c, #(IRQ_MODE|I_Bit|F_Bit)//切换到IRQ模式
	mov sp,#0//清除内核堆栈指针
	MOVS PC,LR

	b __Interrupt_Entry

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'A')


#else

#error "123"

#endif


	END
