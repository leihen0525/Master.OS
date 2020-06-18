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

//-----------------------------------------------------------------------
int Machine_Wdog_Enable(Machine_Desc_Wdog_Type *P_Wdog)
{
	if(P_Wdog==Null)
	{
		return Error_Invalid_Parameter;
	}

	if(P_Wdog->Enable==Null)
	{
		return Error_Undefined;
	}

	return P_Wdog->Enable();
}

int Machine_Wdog_Disable(Machine_Desc_Wdog_Type *P_Wdog)
{
	if(P_Wdog==Null)
	{
		return Error_Invalid_Parameter;
	}

	if(P_Wdog->Disable==Null)
	{
		return Error_Undefined;
	}

	return P_Wdog->Disable();
}

int Machine_Wdog_Clear(Machine_Desc_Wdog_Type *P_Wdog)
{
	if(P_Wdog==Null)
	{
		return Error_Invalid_Parameter;
	}

	if(P_Wdog->Clear==Null)
	{
		return Error_Undefined;
	}

	return P_Wdog->Clear();
}
//-----------------------------------------------------------------------

int Machine_Init_CPU(Machine_Desc_CPU_Type *P_CPU)
{
	if(P_CPU==Null)
	{
		return Error_Invalid_Parameter;
	}

	if(P_CPU->Init==Null)
	{
		return Error_Undefined;
	}
	return P_CPU->Init();
}

//-----------------------------------------------------------------------

