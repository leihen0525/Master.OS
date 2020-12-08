/*
 * Shell.c
 *
 *  Created on: 2019年9月23日
 *      Author: Master.HE
 */
#include "Error.h"

#include "Shell.UART.h"

#include "Shell.h"

#ifdef Master_OS_Config_Shell

int Shell_Init(Machine_Desc_UART_Type *P_UART)
{
	int Err=Shell_UART_Init(P_UART);

	if(Err!=Error_OK)
	{
		return Err;
	}

	return Error_OK;
}

#endif
