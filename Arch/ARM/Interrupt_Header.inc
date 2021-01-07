/*
 * Interrupt-Header.inc
 *
 *  Created on: 2019年4月26日
 *      Author: Master.HE
 */


#if ((__ARM_ARCH == 6) || (__ARM_ARCH == 7)) && (__ARM_ARCH_PROFILE == 'M')



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
