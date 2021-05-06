/*
 * Sys_Call.s
 *
 *  Created on: 2020年12月2日
 *      Author: Master.HE
 */
#if ((__ARM_ARCH == 6) && (__ARM_ARCH_PROFILE == 'M'))

	MODULE Sys_Call

	SECTION .text:CODE:REORDER:NOROOT(2)

	THUMB

	PUBLIC SysCall

SysCall

	//push {r4, r5, r6, r7,r8,r12}
	push {r4-r7}
	mov r4,r8
	mov r5,r12
	push {r4-r5}


	mov r12, r0
	mov r0, r1
	mov r1, r2
	mov r2, r3

	//add r8, sp, #(4 * 6)
	mov r8,r0
	add r0, sp, #(4 * 6)

	//ldmia r8!, {r3, r4, r5, r6,r7}
	ldmia r0!, {r3, r4, r5, r6,r7}

	//
	mov r0,r8

	mov r8, r12
	swi 0x0

	//pop {r4, r5, r6, r7,r8,r12}
	pop {r4-r5}
	mov r8,r4
	mov r12,r5
	pop {r4-r7}


	bx lr

#endif

	END
