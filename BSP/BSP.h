/*
 * BSP.h
 *
 *  Created on: 2020年7月9日
 *      Author: Master.HE
 */

#ifndef BSP_H_
#define BSP_H_

#include "Master.OS.Config.h"
#include "Master.Stdint.h"
#include "Machine/Machine.Struct.h"

int BSP_Init(
		Machine_Desc_Wdog_Type *P_Wdog,
		Machine_Desc_CPU_Type *P_CPU);

int BSP_Init_CPU(void);

int __Sys_BSP_UpData_Clock_Tree(
		void **Clock_Source,
		void **Clock_Tree);

#ifdef Master_OS_Config_BSP_Wdog_Enable
int __Sys_BSP_Wdog_Enable(void);
#endif
#ifdef Master_OS_Config_BSP_Wdog_Disable
int __Sys_BSP_Wdog_Disable(void);
#endif
#ifdef Master_OS_Config_BSP_Wdog_Clear
int __Sys_BSP_Wdog_Clear(void);
#endif

#endif /* BSP_H_ */
