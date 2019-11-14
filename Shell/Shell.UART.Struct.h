/*
 * Shell.UART.Struct.h
 *
 *  Created on: 2019Äê9ÔÂ23ÈÕ
 *      Author: Master.HE
 */

#ifndef SHELL_UART_STRUCT_H_
#define SHELL_UART_STRUCT_H_

#include "Master.Stdint.h"

#include "Machine/Machine.Struct.h"

typedef struct
{
	Machine_Desc_UART_Type *UART;

	struct
	{
		bool Send_Ing;

		uint8_t In;
		uint8_t Out;
		uint8_t DATA[256];
	}Tx_FIFO;

}Shell_UART_DATA_Type;

#endif /* SHELL_UART_STRUCT_H_ */
