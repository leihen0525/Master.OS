/*
 * MPU.Struct.h
 *
 *  Created on: 2019年11月18日
 *      Author: Master.HE
 */

#ifndef MPU_STRUCT_H_
#define MPU_STRUCT_H_

#ifdef __MPU__

#include "Master.Stdint.h"

#include "Machine/Machine.Struct.h"



typedef struct
{
	Machine_Desc_MPU_Cfg_Type Sys_Cfg;
	Machine_Desc_MPU_Cfg_Type Usr_Cfg;

	Machine_Desc_MPU_Type *MPU;

}MPU_DATA_Type;

#endif

#endif /* MPU_STRUCT_H_ */
