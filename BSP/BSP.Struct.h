/*
 * BSP.Struct.h
 *
 *  Created on: 2020年7月9日
 *      Author: Master.HE
 */

#ifndef BSP_STRUCT_H_
#define BSP_STRUCT_H_

#include "Master.Stdint.h"

#include "Machine/Machine.Struct.h"

typedef struct
{
	int (*System_Reset)(void);

	Machine_Desc_Wdog_Type *Wdog;
	Machine_Desc_CPU_Type *CPU;

}BSP_DATA_Type;

#endif /* BSP_STRUCT_H_ */
