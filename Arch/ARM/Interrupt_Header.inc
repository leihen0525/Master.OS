/*
 * Interrupt-Header.inc
 *
 *  Created on: 2019年4月26日
 *      Author: Master.HE
 */


#if ((__ARM_ARCH == 6) || (__ARM_ARCH == 7)) && (__ARM_ARCH_PROFILE == 'M')

Exception_Entry MACRO
	LOCAL Exception_Entry_Err
	LOCAL Exception_Entry_1
	LOCAL Exception_Entry_2
	LOCAL Exception_Entry_3
	LOCAL Exception_Entry_Exit
	
	//cpsid i

	cmp lr,#0xfffffffd
	beq Exception_Entry_1

	cmp lr,#0xfffffff9
	beq Exception_Entry_2

	cmp lr,#0xfffffff1
	beq Exception_Entry_3

Exception_Entry_Err:
	b Exception_Entry_Err


//	add r12, sp, #32
//	stmdb sp!,{r4-r12, lr}


Exception_Entry_1:
	mrs r12,psp
	msr msp,r12

	b Exception_Entry_Exit

Exception_Entry_2:
	b Exception_Entry_Exit

Exception_Entry_3:
	b Exception_Entry_Exit
Exception_Entry_Exit:

	//push {lr}
	stmdb sp!,{lr}
	
	ENDM



Exception_Fast_Exit MACRO
	LOCAL Exception_Fast_Exit_Err
	LOCAL Exception_Fast_Exit_1
	LOCAL Exception_Fast_Exit_2
	LOCAL Exception_Fast_Exit_3
	LOCAL Exception_Fast_Exit_Exit

	//pop {pc}
	ldmia sp!, {lr}

	cmp lr,#0xfffffffd
	beq Exception_Fast_Exit_1

	cmp lr,#0xfffffff9
	beq Exception_Fast_Exit_2

	cmp lr,#0xfffffff1
	beq Exception_Fast_Exit_3

Exception_Fast_Exit_Err:
	b Exception_Fast_Exit_Err

	Exception_Fast_Exit_1:
	mov r12,#0x00
	msr msp,r12

	b Exception_Fast_Exit_Exit

Exception_Fast_Exit_2:
	b Exception_Fast_Exit_Exit

Exception_Fast_Exit_3:
	b Exception_Fast_Exit_Exit
Exception_Fast_Exit_Exit:

	//cpsie i
	ENDM

Exception_Slow_Exit MACRO
	LOCAL Exception_Slow_Exit_Err
	LOCAL Exception_Slow_Exit_1
	LOCAL Exception_Slow_Exit_2
	LOCAL Exception_Slow_Exit_3
	LOCAL Exception_Slow_Exit_Exit

	//pop {pc}
	ldmia sp!, {lr}

	cmp lr,#0xfffffffd
	beq Exception_Slow_Exit_1

	cmp lr,#0xfffffff9
	beq Exception_Slow_Exit_2

	cmp lr,#0xfffffff1
	beq Exception_Slow_Exit_3

Exception_Slow_Exit_Err:
	b Exception_Slow_Exit_Err

Exception_Slow_Exit_1:
	mov r12,#0x00
	msr msp,r12

	b Exception_Slow_Exit_Exit

Exception_Slow_Exit_2:
	b Exception_Slow_Exit_Exit

Exception_Slow_Exit_3:
	b Exception_Slow_Exit_Exit
Exception_Slow_Exit_Exit:

	//cpsie i
	ENDM

	//END

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R')

MODE_MSK EQU 0x1F				; Bit mask for mode bits in CPSR

USR_MODE EQU 0x10				; User mode
FIQ_MODE EQU 0x11				; Fast Interrupt Request mode
IRQ_MODE EQU 0x12				; Interrupt Request mode
SVC_MODE EQU 0x13				; Supervisor mode
ABT_MODE EQU 0x17				; Abort mode
UND_MODE EQU 0x1B				; Undefined Instruction mode
SYS_MODE EQU 0x1F				; System mode


I_Bit EQU 0x80					; when I bit is set, IRQ is disabled
F_Bit EQU 0x40					; when F bit is set, FIQ is disabled



#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'A')


#else

#error "123"

#endif
