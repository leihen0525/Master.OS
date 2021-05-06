/*
 * Entry.s
 *
 *  Created on: 2019年9月17日
 *      Author: Master.HE
 */
#if ((__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'M'))

	MODULE Entry

	SECTION CSTACK:DATA:NOROOT(3)

	SECTION .intvec:CODE:NOROOT(2)


	PUBLIC __iar_program_start
	PUBLIC __Master_OS_vector_table

	EXTERN __Interrupt_Entry

	DATA


__Master_OS_vector_table
	DCD sfe(CSTACK)
	DCD __iar_program_start			; 1-Reset Handler

	DCD NMI_Handler					; 2-NMI Handler
	DCD HardFault_Handler			; 3-Hard Fault Handler
	DCD MemManage_Handler			; 4-MPU Fault Handler
	DCD BusFault_Handler			; 5-Bus Fault Handler
	DCD UsageFault_Handler			; 6-Usage Fault Handler
	DCD __Invalid_Entry				; 7-Reserved
	DCD __Invalid_Entry				; 8-Reserved
	DCD __Invalid_Entry				; 9-Reserved
	DCD __Invalid_Entry				; 10-Reserved
	DCD __SVC_Entry					; 11-SVCall Handler
	DCD DebugMon_Handler			; 12-Debug Monitor Handler
	DCD __Invalid_Entry				; 13-Reserved
	DCD __PendSV_Entry				; 14-PendSV Handler

	DCD __SysTick_Entry				; 15-SysTick Handler

/* External Interrupts*/


	REPT 240
	DCD __Interrupt_Entry
	ENDR

	EXTWEAK BSP_Core_Init

	EXTERN  Start_Kernel

	EXTWEAK __iar_data_init3
	EXTWEAK __iar_init_core
	EXTWEAK __iar_init_vfp
	EXTWEAK __iar_data_init_done


	PUBLIC _call_main

	THUMB
	SECTION .text:CODE:NOROOT(2)

__iar_program_start:

	//更新一下SP指针 防止不是上电进来的
	LDR R0,=sfe(CSTACK)
	MSR MSP,R0

	BL BSP_Core_Init


	BL      __iar_init_core

	BL      __iar_init_vfp


	bl      __iar_data_init3

_call_main:
	BL      __iar_data_init_done

	bl Start_Kernel
	
	REQUIRE __Master_OS_vector_table


	PUBWEAK NMI_Handler
	SECTION .text:CODE:REORDER:NOROOT(2)
NMI_Handler:
	B NMI_Handler

	PUBWEAK HardFault_Handler
	SECTION .text:CODE:REORDER:NOROOT(2)
HardFault_Handler:
	B HardFault_Handler

	PUBWEAK MemManage_Handler
	SECTION .text:CODE:REORDER:NOROOT(2)
MemManage_Handler:
	B MemManage_Handler

	PUBWEAK BusFault_Handler
	SECTION .text:CODE:REORDER:NOROOT(2)
BusFault_Handler:
	B BusFault_Handler

	PUBWEAK UsageFault_Handler
	SECTION .text:CODE:REORDER:NOROOT(2)
UsageFault_Handler:
	B UsageFault_Handler

	PUBWEAK __SVC_Entry
	SECTION .text:CODE:REORDER:NOROOT(2)
__SVC_Entry:
	B __SVC_Entry

	PUBWEAK DebugMon_Handler
	SECTION .text:CODE:REORDER:NOROOT(2)
DebugMon_Handler:
	B DebugMon_Handler

	PUBWEAK __PendSV_Entry
	SECTION .text:CODE:REORDER:NOROOT(2)
__PendSV_Entry:
	B __PendSV_Entry


	PUBWEAK __SysTick_Entry
	SECTION .text:CODE:REORDER:NOROOT(2)
__SysTick_Entry:
	B __SysTick_Entry


	PUBWEAK __Invalid_Entry
	SECTION .text:CODE:REORDER:NOROOT(2)
__Invalid_Entry:
	B __Invalid_Entry


#endif


	END
