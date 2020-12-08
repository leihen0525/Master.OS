/*
 * Sys_Call.S
 *
 *  Created on: 2019年4月8日
 *      Author: Master.HE
 */




#if (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R')

	MODULE Sys_Call

	SECTION .text:CODE:REORDER:NOROOT(2)

	ARM

	PUBLIC SysCall

SysCall

	push {r4, r5, r6, r7,r8,r12}

	mov r12, r0
	mov r0, r1
	mov r1, r2
	mov r2, r3
	add r8, sp, #(4 * 6)
	ldmia r8!, {r3, r4, r5, r6,r7}
	mov r8, r12
	swi 0x0

	pop {r4, r5, r6, r7,r8,r12}


	bx lr

#endif

	END
