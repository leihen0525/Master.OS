/*
 * MPU.h
 *
 *  Created on: 2019年11月18日
 *      Author: Master.HE
 */

#ifndef MPU_H_
#define MPU_H_

#ifdef __MPU__

#include "Machine/Machine.Struct.h"

int MPU_Init(Machine_Desc_MPU_Type *P_MPU);

int MPU_SET(uint32_t Sys_Base_Address,uint32_t Sys_Region_Size,uint32_t Usr_Base_Address,uint32_t Usr_Region_Size);
int MPU_SET_Region_Disable(void);

void MPU_Handle_Data_Fault(uint32_t Mode,uint32_t *Fault_SP,uint32_t Fault_Code_Address);

#endif

#endif /* MPU_H_ */
