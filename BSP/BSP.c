/*
 * BSP.c
 *
 *  Created on: 2020年7月9日
 *      Author: Master.HE
 */


#include "Error.h"

#include "BSP.Struct.h"
#include "BSP.h"

BSP_DATA_Type BSP_DATA;

int BSP_Init(
		int (*System_Reset)(void),
		Machine_Desc_Wdog_Type *P_Wdog,
		Machine_Desc_CPU_Type *P_CPU)
{
	if(System_Reset==Null || P_Wdog==Null || P_CPU==Null)
	{
		return Error_Invalid_Parameter;
	}
	BSP_DATA.System_Reset=System_Reset;
	BSP_DATA.Wdog=P_Wdog;
	BSP_DATA.CPU=P_CPU;

	if(BSP_DATA.Wdog->Enable==Null
	|| BSP_DATA.Wdog->Refresh==Null
	|| BSP_DATA.Wdog->Disable==Null)
	{
		return Error_Undefined;
	}
	if(BSP_DATA.CPU->Init==Null
	|| BSP_DATA.CPU->UpData_Clock_Tree==Null
	|| BSP_DATA.CPU->Clock_Source==Null
	|| BSP_DATA.CPU->Clock_Tree==Null)
	{
		return Error_Undefined;
	}

	return Error_OK;
}

int BSP_Init_CPU(void)
{
	if(BSP_DATA.CPU==Null)
	{
		return Error_Unknown;
	}

	if(BSP_DATA.CPU->Init==Null)
	{
		return Error_Undefined;
	}
	return BSP_DATA.CPU->Init();
}

int __Sys_BSP_UpData_Clock_Tree(
		void **Clock_Source,
		void **Clock_Tree)
{
	int Err;
	if(BSP_DATA.CPU==Null)
	{
		return Error_Unknown;
	}
	if(BSP_DATA.CPU->UpData_Clock_Tree==Null)
	{
		return Error_Undefined;
	}
	if((Err=BSP_DATA.CPU->UpData_Clock_Tree())!=Error_OK)
	{
		return Err;
	}
	if(Clock_Source!=Null)
	{
		*Clock_Source=(void *)BSP_DATA.CPU->Clock_Source;
	}
	if(Clock_Tree!=Null)
	{
		*Clock_Tree=BSP_DATA.CPU->Clock_Tree;
	}
	return Error_OK;
}
#ifdef Master_OS_Config_BSP_System_Reset
int __Sys_BSP_System_Reset(void)
{
	if(BSP_DATA.System_Reset==Null)
	{
		return Error_Unknown;
	}
	return BSP_DATA.System_Reset();
}
#endif
#ifdef Master_OS_Config_BSP_Wdog_Enable
int __Sys_BSP_Wdog_Enable(void)
{
	if(BSP_DATA.Wdog==Null)
	{
		return Error_Unknown;
	}

	if(BSP_DATA.Wdog->Enable==Null)
	{
		return Error_Undefined;
	}

	return BSP_DATA.Wdog->Enable();
}
#endif
#ifdef Master_OS_Config_BSP_Wdog_Disable
int __Sys_BSP_Wdog_Disable(void)
{
	if(BSP_DATA.Wdog==Null)
	{
		return Error_Unknown;
	}

	if(BSP_DATA.Wdog->Disable==Null)
	{
		return Error_Undefined;
	}

	return BSP_DATA.Wdog->Disable();
}
#endif
#ifdef Master_OS_Config_BSP_Wdog_Refresh
int __Sys_BSP_Wdog_Refresh(void)
{
	if(BSP_DATA.Wdog==Null)
	{
		return Error_Unknown;
	}

	if(BSP_DATA.Wdog->Refresh==Null)
	{
		return Error_Undefined;
	}

	return BSP_DATA.Wdog->Refresh();
}
#endif

