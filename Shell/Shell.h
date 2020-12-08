/*
 * Shell.h
 *
 *  Created on: 2019年9月23日
 *      Author: Master.HE
 */

#ifndef SHELL_H_
#define SHELL_H_

//#include "Master.OS.Config.h"

#include "Machine/Machine.Struct.h"

#ifdef Master_OS_Config_Shell
int Shell_Init(Machine_Desc_UART_Type *P_UART);
#endif

#endif /* SHELL_H_ */
