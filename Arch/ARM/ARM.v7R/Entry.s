/*
 * Entry-ARMv7R.s
 *
 *  Created on: 2020年12月2日
 *      Author: Master.HE
 */
#include "../Interrupt_Header.inc"

#if ((__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R'))

	MODULE Entry

	//SECTION IRQ_STACK:DATA:NOROOT(3)
	//SECTION FIQ_STACK:DATA:NOROOT(3)
	SECTION CSTACK:DATA:NOROOT(3)
	SECTION UND_STACK:DATA:NOROOT(3)
	SECTION ABT_STACK:DATA:NOROOT(3)


	SECTION .intvec:CODE:NOROOT(2)

	PUBLIC __vector
	PUBLIC __iar_program_start



	DATA

; The vector table is not needed ; until after copy initialization is done
__iar_init$$done:


; Make this a DATA label, so that stack usage; analysis doesn't consider it an uncalled fun
__vector:


	ARM

	LDR PC,=__iar_program_start			; Reset
	LDR PC,=Undefined_Handler			; Undefined instructions
	LDR PC,=__SVC_Entry					; Software interrupt (SWI/SVC)
	LDR PC,=Prefetch_Handler			; Prefetch abort
	LDR PC,=Abort_Handler				; Data abort
	DCD 0								; RESERVED
	LDR PC,=__Interrupt_Entry			; IRQ
	LDR PC,=__FIQ_Entry					; FIQ

	SECTION .text:CODE:NOROOT(2)


	EXTWEAK BSP_Core_Init

	EXTERN  Start_Kernel

	EXTWEAK __iar_data_init3
	EXTWEAK __iar_init_core
	EXTWEAK __iar_init_vfp

	ARM

__iar_program_start:



	BL BSP_Core_Init


	MRS r0, cpsr                ; Original PSR value


	BIC r0, r0, #MODE_MSK       ; Clear the mode bits
	ORR r0, r0, #ABT_MODE       ; Set ABT mode bits
	MSR cpsr_c, r0              ; Change the mode


	LDR r1, =SFE(ABT_STACK)     ; End of ABT_STACK
	BIC sp,r1,#0x7              ; Make sure SP is 8 aligned

	BIC r0, r0, #MODE_MSK       ; Clear the mode bits
	ORR r0, r0, #UND_MODE       ; Set UND mode bits
	MSR cpsr_c, r0              ; Change the mode


	LDR r1, =SFE(UND_STACK)     ; End of UND_STACK
	BIC sp,r1,#0x7              ; Make sure SP is 8 aligned

	BIC r0 ,r0, #MODE_MSK       ; Clear the mode bits
	ORR r0 ,r0, #SYS_MODE       ; Set System mode bits
	MSR cpsr_c, r0              ; Change the mode


	LDR r1, =SFE(CSTACK)        ; End of CSTACK
	BIC sp,r1,#0x7              ; Make sure SP is 8 aligned


	//FUNCALL __iar_program_start, __iar_init_core
	BL      __iar_init_core
	//FUNCALL __iar_program_start, __iar_init_vfp
	//BL      __iar_init_vfp
#ifdef __ARMVFP__
C1_ACCESS_FP_EN  DEFINE   0x00F00000                            ; C1, Coprocessor Access Register cp10 and cp11 enabled

FPEXC_EN         DEFINE   0x40000000                            ; VFP enable bit.

	MRC     P15, 0, R0, C1, C0, 2                               ; Read Coprocessor Access Register Bit Functions.
	MOV     R3, #C1_ACCESS_FP_EN                                ; Enable Coprocessors cp10 & cp11
	ORR     R0, R0, R3
	MCR     P15, 0, R0, C1, C0, 2
	                                                            ; Set the EN bit of FPEXC[30] to enable Neon/VFP

	MOV     R0, #0//#FPEXC_EN
	VMSR    FPEXC, R0
/*
	MOV     R1, #0

	FMDRR   D0, R1, R1
	FMDRR   D1, R1, R1
	FMDRR   D2, R1, R1
	FMDRR   D3, R1, R1
	FMDRR   D4, R1, R1
	FMDRR   D5, R1, R1
	FMDRR   D6, R1, R1
	FMDRR   D7, R1, R1
	FMDRR   D8, R1, R1
	FMDRR   D0, R1, R1
	FMDRR   D10, R1, R1
	FMDRR   D11, R1, R1
	FMDRR   D12, R1, R1
	FMDRR   D13, R1, R1
	FMDRR   D14, R1, R1
	FMDRR   D15, R1, R1
	*/
#endif


	//FUNCALL __iar_program_start, __cmain
	//BL      __cmain
	bl      __iar_data_init3





SCTLR_M          DEFINE   0x00000001
SCTLR_A          DEFINE   0x00000002
SCTLR_C          DEFINE   0x00000004
SCTLR_CP15BEN   DEFINE   0x00000020
SCTLR_B          DEFINE   0x00000080
SCTLR_SW         DEFINE   0x00000400
SCTLR_Z          DEFINE   0x00000800
SCTLR_I          DEFINE   0x00001000
SCTLR_V          DEFINE   0x00002000
SCTLR_RR         DEFINE   0x00004000
SCTLR_BR         DEFINE   0x00020000
SCTLR_DZ         DEFINE   0x00080000
SCTLR_FI         DEFINE   0x00200000
SCTLR_U          DEFINE   0x00400000
SCTLR_VE         DEFINE   0x01000000
SCTLR_EE         DEFINE   0x02000000
SCTLR_NMFI       DEFINE   0x08000000
SCTLR_TE         DEFINE   0x40000000
SCTLR_IE         DEFINE   0x80000000

	//MRC P15, 0, R0, C1, C0, 0                               ; Read SCTLR

	MRC P15, 0, R0, C1, C0, 0
	//ORR R0, R0, #SCTLR_VE                                   ; Enable vectored interrupts
	//BIC R0, R0, #SCTLR_VE                                   ; Disable vectored interrupts
	BIC R0, R0, #SCTLR_V                                    ; Set the vector base address to 0x00000000
	MCR P15, 0, R0, C1, C0, 0
	MRC P15, 0, R0, C1, C0, 0


	bl Start_Kernel


	REQUIRE __vector


	ARM


	PUBWEAK Undefined_Handler
	SECTION .text:CODE:NOROOT(2)
Undefined_Handler
	B Undefined_Handler

	PUBWEAK __SVC_Entry
	SECTION .text:CODE:NOROOT(2)
__SVC_Entry
	B __SVC_Entry

	PUBWEAK Prefetch_Handler
	SECTION .text:CODE:NOROOT(2)
Prefetch_Handler
	B Prefetch_Handler

	PUBWEAK Abort_Handler
	SECTION .text:CODE:NOROOT(2)
Abort_Handler
	B Abort_Handler

	PUBWEAK __Interrupt_Entry
	SECTION .text:CODE:NOROOT(2)
__Interrupt_Entry
	B __Interrupt_Entry

	PUBWEAK __FIQ_Entry
	SECTION .text:CODE:NOROOT(2)
__FIQ_Entry
	B __FIQ_Entry



#endif

	END
