/*
 * Init.Machine.h
 *
 *  Created on: 2019年9月17日
 *      Author: Master.HE
 */

#ifndef INIT_MACHINE_H_
#define INIT_MACHINE_H_

#include "Machine/Machine.Struct.h"

int Machine_Init(Machine_Desc_Type **P_Machine_Desc);

int Machine_Wdog_Enable(Machine_Desc_Wdog_Type *P_Wdog);
int Machine_Wdog_Disable(Machine_Desc_Wdog_Type *P_Wdog);
int Machine_Wdog_Clear(Machine_Desc_Wdog_Type *P_Wdog);

int Machine_Init_CPU(Machine_Desc_CPU_Type *P_CPU);



#endif /* INIT_MACHINE_H_ */
