/*
 * IRQ.h
 *
 *  Created on: 2019Äê4ÔÂ15ÈÕ
 *      Author: Master.HE
 */

#ifndef IRQ_H_
#define IRQ_H_

#include "IRQ.Define.h"

#include "Machine/Machine.Struct.h"

int IRQ_Init(Machine_Desc_IRQ_Type *P_IRQ);

int __Sys_IRQ_Enable(int IRQ_Index);
int __Sys_IRQ_Disable(int IRQ_Index);
int __Sys_IRQ_Set_Priority(int IRQ_Index,int Priority);
int __Sys_IRQ_All_Enable(void);
int __Sys_IRQ_All_Disable(void);
int __Sys_IRQ_Register_Hook(int IRQ_Index,IRQ_Hook_Function Hook_Function,void *Args);
int __Sys_IRQ_Delete_Hook(int IRQ_Index,int Handle);

void __IRQ_Entry(void);

#endif /* IRQ_H_ */
