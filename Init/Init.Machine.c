/*
 * Init.Machine.c
 *
 *  Created on: 2019年9月17日
 *      Author: Master.HE
 */
#include "Master.Stdint.h"

#include "Error.h"

#include "Init.Machine.h"

#include "Machine/Machine.Struct.h"

int Machine_Init(Machine_Desc_Type **P_Machine_Desc)
{
	if(P_Machine_Desc==Null)
	{
		return Error_Invalid_Parameter;
	}

#pragma section=".Arch.BSP.Init"

	if(sizeof(Machine_Desc_Type)!=__section_size(".Arch.BSP.Init"))
	{
		return Error_Operation_Failed;
	}

	*P_Machine_Desc=__section_begin(".Arch.BSP.Init");

	if(*P_Machine_Desc==Null)
	{
		return Error_Undefined;
	}
	if((*P_Machine_Desc)->Init==Null)
	{
		return Error_Undefined;
	}

	return (*P_Machine_Desc)->Init();
}


