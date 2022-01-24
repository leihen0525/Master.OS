/*
 * FPU.Define.h
 *
 *  Created on: 2019年11月19日
 *      Author: Master.HE
 */

#ifndef FPU_DEFINE_H_
#define FPU_DEFINE_H_

#ifdef __ARMVFP__

#if ((__ARM_ARCH == 6) || (__ARM_ARCH == 7)) && (__ARM_ARCH_PROFILE == 'M')

#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R')
#define __FPU_IRQ_Temp_Enable_Begin__														\
											int VFP_FPEXC_old=0;							\
											int VFP_FPEXC_New=0x40000000;					\
											asm("VMRS %0, FPEXC"							\
													:"+r"(VFP_FPEXC_old));					\
											asm("VMSR FPEXC, %0"							\
													:"+r"(VFP_FPEXC_New));


#define __FPU_IRQ_Temp_Enable_End__															\
											asm("VMSR FPEXC, %0"							\
													:"+r"(VFP_FPEXC_old));
#endif

#endif

#endif /* FPU_DEFINE_H_ */
