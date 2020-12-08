/*
 * Shell.UART.h
 *
 *  Created on: 2019年9月23日
 *      Author: Master.HE
 */

#ifndef SHELL_UART_H_
#define SHELL_UART_H_

//#include "Master.OS.Config.h"

#include "Master.Stdint.h"

#include "Machine/Machine.Struct.h"

#ifdef Master_OS_Config_Shell

int Shell_UART_Init(Machine_Desc_UART_Type *P_UART);

void Shell_UART_IRQ(void *Args,int IRQ_Index);

int Shell_UART_Tx_DATA(uint8_t *DATA,int Size);

int Shell_UART_Tx_FIFO_Init(void);
int Shell_UART_Tx_FIFO_In(uint8_t DATA);
int Shell_UART_Tx_FIFO_Out(uint8_t *DATA);

#endif

#endif /* SHELL_UART_H_ */
