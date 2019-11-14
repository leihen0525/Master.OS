/*
 * Machine.h
 *
 *  Created on: 2019Äê9ÔÂ17ÈÕ
 *      Author: Master.HE
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include "Machine.Struct.h"

#define MACHINE_START(_Type,_Name)												\
__root const Machine_Desc_Type __Mach_Desc_##_Type	@".Arch.BSP.Init" =		\
{																				\
	.Name = _Name,

#define MACHINE_END																\
};


#endif /* MACHINE_H_ */
