/*
 * Interrupt-ARMv7M.s
 *
 *  Created on: 2020年12月2日
 *      Author: Master.HE
 */

	MODULE Interrupt

#if ((__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'M'))

	SECTION .text:CODE:REORDER:NOROOT(2)


	EXTERN __Sys_Call_Table
	EXTERN __IRQ_Entry


	THUMB

	PUBLIC __Invalid_Entry
__Invalid_Entry
	B __Invalid_Entry

	PUBLIC __SVC_Entry
__SVC_Entry

#ifdef __UsrSP_SysSP__

#else
	//下面这个意思是
	//if(lr==#0xfffffffd)
	//{
	//	r12=psp
	//	msp=r12
	//}
	cmp lr,#0xfffffffd
	BNE __SVC_Entry_Next1
	mrs r12,psp
	msr msp,r12
__SVC_Entry_Next1:
#endif
	push {lr}

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

#ifdef __UsrSP_SysSP__

	pop {pc}

#else
	pop {lr}

	//下面这个意思是
	//if(lr==#0xfffffffd)
	//{
	//	r12=0
	//	msp=r12
	//}
	cmp lr,#0xfffffffd
	BNE __SVC_Entry_Next2
	mov r12,#0x00
	msr msp,r12
__SVC_Entry_Next2:
	bx lr
#endif



	PUBLIC __Interrupt_Entry
__Interrupt_Entry

#ifdef __UsrSP_SysSP__

#else
	cmp lr,#0xfffffffd
	BNE __Interrupt_Entry_Next1
	mrs r12,psp
	msr msp,r12
__Interrupt_Entry_Next1:
#endif

	push {lr}

	ldr r1,=__IRQ_Entry
	blx r1

#ifdef __UsrSP_SysSP__
	pop {pc}
#else

	pop {lr}

	cmp lr,#0xfffffffd
	BNE __Interrupt_Entry_Next2
	mov r12,#0x00
	msr msp,r12
__Interrupt_Entry_Next2:
	bx lr
#endif



#endif

	END
