/*
 * Timer.h
 *
 *  Created on: 2019年4月29日
 *      Author: Master.HE
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "Master.Stdint.h"

#include "Timer.Struct.h"


int Timer_Init(Machine_Desc_Timer_Type *P_Timer);

int Timer_Get_Flag(void);

int __Sys_Timer_Enable(void);
int __Sys_Timer_Disable(void);

void Timer_IRQ(void *Args,int IRQ_Index);

int Timer_Add_Timer_Queue(Timer_Node_Type *Add_Node,int32_t TimeOut_MS);
int Timer_Delete_Timer_Queue(int Handle,Timer_Node_Type **Delete_Node);
void __Timer_Task(void);
void __Timer_SysTick_Entry(void);

#endif /* TIMER_H_ */
