/*
 * Interrupt.s
 *
 *  Created on: 2020年12月2日
 *      Author: Master.HE
 */
#include "../Interrupt_Header.inc"

	MODULE Interrupt

#if (__ARM_ARCH == 6) && (__ARM_ARCH_PROFILE == 'M')

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

#ifdef __UsrSP_SysSP__

	push {lr}

	sub sp,sp,#0x10

	str r7,[sp,#0xC]
	str r6,[sp,#0x8]
	str r5,[sp,#0x4]
	str r4,[sp]

	ldr r6,=__Sys_Call_Table
	mov r7,r8
	lsls r7,r7,#2
	ldr r7,[r6,r7]
	blx r7

	add sp,sp,#0x10

	MRS R7, PSP

	str r0,[r7]

	pop {pc}

#else
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
#endif



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

#ifdef __UsrSP_SysSP__
	push {lr}

	ldr r1,=__IRQ_Entry
	blx r1

	pop {pc}
#else
	Exception_Entry


	ldr r1,=__IRQ_Entry
	blx r1


	Exception_Fast_Exit
#endif
	bx lr


#endif

	END
