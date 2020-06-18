/*
 * Shell.UART.c
 *
 *  Created on: 2019年9月23日
 *      Author: Master.HE
 */

#include "Error.h"

#include "Shell.UART.Struct.h"

#include "Shell.UART.h"

#include "Machine/Machine.Enum.h"

#include "IRQ/IRQ.h"

Shell_UART_DATA_Type Shell_UART_DATA;

int Shell_UART_Init(Machine_Desc_UART_Type *P_UART)
{
	if(P_UART==Null)
	{
		return Error_Invalid_Parameter;
	}

	Shell_UART_DATA.UART=P_UART;

	if(Shell_UART_DATA.UART->Init==Null
	|| Shell_UART_DATA.UART->Set_BaudRate==Null
	|| Shell_UART_DATA.UART->Rx_DATA==Null
	|| Shell_UART_DATA.UART->Tx_DATA==Null
	|| Shell_UART_DATA.UART->Get_Flag==Null)
	{
		return Error_Undefined;
	}

	int Err=Shell_UART_DATA.UART->Init();
	if(Err!=Error_OK)
	{
		return Err;
	}

	Err=Shell_UART_DATA.UART->Set_BaudRate(Shell_UART_DATA.UART->BaudRate);
	if(Err!=Error_OK)
	{
		return Err;
	}

	Err=__Sys_IRQ_Register_Hook(Shell_UART_DATA.UART->IRQ_Index,Shell_UART_IRQ,Null);
	if(Err<Error_OK)
	{
		return Err;
	}

	Err=__Sys_IRQ_Enable(Shell_UART_DATA.UART->IRQ_Index);
	if(Err!=Error_OK)
	{
		return Err;
	}

	Shell_UART_Tx_FIFO_Init();

	return Error_OK;
}

uint8_t *P_DATA={"12345"};

void Shell_UART_IRQ(void *Args,int IRQ_Index)
{
	int Flag=Shell_UART_DATA.UART->Get_Flag();

	if((Flag&Machine_Desc_UART_Flag_Rx)!=0)
	{
		uint8_t DATA;
		if(Shell_UART_DATA.UART->Rx_DATA(&DATA)==Error_OK)
		{
			//Shell_UART_DATA.UART->Tx_DATA(DATA);
			if(DATA=='z')
			{
				Shell_UART_Tx_DATA(P_DATA,5);
			}

		}

	}

	if((Flag&Machine_Desc_UART_Flag_Tx_Complete)!=0)
	{
		uint8_t DATA;
		if(Shell_UART_Tx_FIFO_Out(&DATA)==Error_OK)
		{
			Shell_UART_DATA.UART->Tx_DATA(DATA);
		}
		else
		{
			Shell_UART_DATA.Tx_FIFO.Send_Ing=false;
		}

	}


}
//-----------------------------------------------------------------------------------
int Shell_UART_Tx_DATA(uint8_t *DATA,int Size)
{
	if(Shell_UART_DATA.UART->Tx_DATA==Null)
	{
		return Error_Undefined;
	}

	if(DATA==Null || Size==0)
	{
		return Error_Invalid_Parameter;
	}

	if(Shell_UART_DATA.Tx_FIFO.Send_Ing==true)
	{
		int Err=Error_OK;
		for(int i=0;i<Size;i++)
		{
			if(Shell_UART_Tx_FIFO_In(DATA[i])!=Error_OK)
			{
				Err=Error_OverFlow;
			}
		}

		return Err;
	}
	else
	{
		Shell_UART_DATA.Tx_FIFO.Send_Ing=true;

		int Err;
		Err=Shell_UART_DATA.UART->Tx_DATA(DATA[0]);
		if(Err!=Error_OK)
		{
			return Err;
		}

		for(int i=1;i<Size;i++)
		{
			if(Shell_UART_Tx_FIFO_In(DATA[i])!=Error_OK)
			{
				Err=Error_OverFlow;
			}
		}

		return Err;
	}

}


//-----------------------------------------------------------------------------------
int Shell_UART_Tx_FIFO_Init(void)
{
	Shell_UART_DATA.Tx_FIFO.Send_Ing=false;
	Shell_UART_DATA.Tx_FIFO.In=0;
	Shell_UART_DATA.Tx_FIFO.Out=0;

	return Error_OK;
}

int Shell_UART_Tx_FIFO_In(uint8_t DATA)
{
	Shell_UART_DATA.Tx_FIFO.DATA[Shell_UART_DATA.Tx_FIFO.In++]=DATA;

	if(Shell_UART_DATA.Tx_FIFO.In==Shell_UART_DATA.Tx_FIFO.Out)
	{
		return Error_OverFlow;
	}
	else
	{
		return Error_OK;
	}
}
int Shell_UART_Tx_FIFO_Out(uint8_t *DATA)
{
	if(DATA==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(Shell_UART_DATA.Tx_FIFO.In==Shell_UART_DATA.Tx_FIFO.Out)
	{
		return Error_Empty;
	}
	else
	{
		*DATA=Shell_UART_DATA.Tx_FIFO.DATA[Shell_UART_DATA.Tx_FIFO.Out++];

		return Error_OK;
	}
}
