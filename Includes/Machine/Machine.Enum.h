/*
 * Machine.Enum.h
 *
 *  Created on: 2019年9月17日
 *      Author: Master.HE
 */

#ifndef MACHINE_ENUM_H_
#define MACHINE_ENUM_H_

typedef enum
{
	Machine_Desc_UART_Flag_Null						=0,

	Machine_Desc_UART_Flag_Tx_Complete				=(1<<0),

	Machine_Desc_UART_Flag_Tx_Empty					=(1<<1),

	Machine_Desc_UART_Flag_Rx						=(1<<2),


}Machine_Desc_UART_Flag_Type;

#endif /* MACHINE_ENUM_H_ */
