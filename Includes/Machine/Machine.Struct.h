/*
 * Machine.Struct.h
 *
 *  Created on: 2019Äê9ÔÂ17ÈÕ
 *      Author: Master.HE
 */

#ifndef MACHINE_STRUCT_H_
#define MACHINE_STRUCT_H_

//-------------------------------------------------------------------------
typedef struct
{

	int (*Enable)(void);
	int (*Disable)(void);
	int (*Clear)(void);

}Machine_Desc_Wdog_Type;
//-------------------------------------------------------------------------
typedef struct
{
	int IRQ_Index;

	int (*Init)(void);
	int (*GET_Flag)(void);

	int (*Enable)(void);
	int (*Disable)(void);
}Machine_Desc_Timer_Type;
//-------------------------------------------------------------------------
typedef struct
{
	int IRQ_Max_Index;

	int (*Init)(void);

	int(*Enable)(int);
	int(*Disable)(int);
	int(*Set_Priority)(int,int);

	int(*All_Enable)(void);
	int(*All_Disable)(void);

	int (*Get_IRQ_Index)(void);
	int (*Clear_IRQ_Flag)(int);

}Machine_Desc_IRQ_Type;

//-------------------------------------------------------------------------
typedef struct
{
	int IRQ_Index;
	int BaudRate;

	int (*Init)(void);
	int (*Set_BaudRate)(int);

	int (*Tx_DATA)(unsigned char );
	int (*Rx_DATA)(unsigned char *);
	int (*Get_Flag)(void);

}Machine_Desc_UART_Type;
//-------------------------------------------------------------------------
typedef struct
{
	int (*Init)(void);

}Machine_Desc_CPU_Type;
//-------------------------------------------------------------------------
typedef struct
{
	const char *Name;
	const char *Info;


	int (*Init)(void);

	Machine_Desc_Wdog_Type Wdog;

	Machine_Desc_Timer_Type Timer;

	Machine_Desc_IRQ_Type IRQ;

	Machine_Desc_UART_Type UART;

	Machine_Desc_CPU_Type CPU;

}Machine_Desc_Type;
//-------------------------------------------------------------------------

#endif /* MACHINE_STRUCT_H_ */
