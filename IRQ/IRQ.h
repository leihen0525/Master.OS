/*
 * IRQ.h
 *
 *  Created on: 2019年4月15日
 *      Author: Master.HE
 */

#ifndef IRQ_H_
#define IRQ_H_

//#include "Master.OS.Config.h"
#include "IRQ/IRQ.Define.h"

#include "Machine/Machine.Struct.h"

int IRQ_Init(Machine_Desc_IRQ_Type *P_IRQ);

#ifdef Master_OS_Config_IRQ_Enable
int __Sys_IRQ_Enable(int IRQ_Index);
#endif
#ifdef Master_OS_Config_IRQ_Disable
int __Sys_IRQ_Disable(int IRQ_Index);
#endif
#ifdef Master_OS_Config_IRQ_Set_Priority
int __Sys_IRQ_Set_Priority(int IRQ_Index,int Priority);
#endif
#ifdef Master_OS_Config_IRQ_All_Enable
int __Sys_IRQ_All_Enable(void);
#endif
#ifdef Master_OS_Config_IRQ_All_Disable
int __Sys_IRQ_All_Disable(void);
#endif
#ifdef Master_OS_Config_IRQ_Register_Hook
int __Sys_IRQ_Register_Hook(int IRQ_Index,IRQ_Hook_Function Hook_Function,void *Args);
#endif
#ifdef Master_OS_Config_IRQ_Delete_Hook
int __Sys_IRQ_Delete_Hook(int IRQ_Index,int Handle);
#endif

void __IRQ_Entry(void);

#endif /* IRQ_H_ */
