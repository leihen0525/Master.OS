/*
 * Init.Module.c
 *
 *  Created on: 2019Äê9ÔÂ17ÈÕ
 *      Author: Master.HE
 */
#include "Error.h"

#include "Module/Module.Struct.h"
#include "Module/Module.h"

#include "Init.Module.h"

#include "__Sys.API.h"

#include "API.h"

int Module_Init_Task(void)
{
	__Module_Init_Task_Type *Index;
	int Err;
#pragma section=".Module.Init.Task"

	for(Index=__section_begin(".Module.Init.Task");Index < __section_end(".Module.Init.Task");Index++)
	{
		if(Index==Null)
		{
			return Error_Unknown;
		}
		if((Err=__Sys_Scheduling_Create_Task(
										Index->Name,
										Index->Task_Enter,
										Index->Args,
										Scheduling_Exit_Task,
										Index->Priority,
										Index->Stack,
										Index->Stack_Size_4Byte,
										Index->Option))<Error_OK)
		{
			return Err;
		}
	}
	return Error_OK;
}

int Module_Init_Sys_Device(void)
{
	Module_Init_Fun *Index;

#pragma section=".Module.Init.Sys.Device"

	for(Index=__section_begin(".Module.Init.Sys.Device");Index < __section_end(".Module.Init.Sys.Device");Index++)
	{
		if(Index==Null)
		{
			return Error_Unknown;
		}
		(*Index)();
	}
	return Error_OK;
}
int Module_Init_Sys_Com(void)
{
	Module_Init_Fun *Index;

#pragma section=".Module.Init.Sys.Com"

	for(Index=__section_begin(".Module.Init.Sys.Com");Index < __section_end(".Module.Init.Sys.Com");Index++)
	{
		if(Index==Null)
		{
			return Error_Unknown;
		}
		(*Index)();
	}
	return Error_OK;
}

int Module_Init_Com(void)
{
	Module_Init_Fun *Index;

#pragma section=".Module.Init.Com"

	for(Index=__section_begin(".Module.Init.Com");Index < __section_end(".Module.Init.Com");Index++)
	{
		if(Index==Null)
		{
			return Error_Unknown;
		}
		(*Index)();
	}
	return Error_OK;
}

int Module_Init_Application(void)
{
	Module_Init_Fun *Index;

#pragma section=".Module.Init.Application"

	for(Index=__section_begin(".Module.Init.Application");Index < __section_end(".Module.Init.Application");Index++)
	{
		if(Index==Null)
		{
			return Error_Unknown;
		}
		(*Index)();
	}
	return Error_OK;
}
