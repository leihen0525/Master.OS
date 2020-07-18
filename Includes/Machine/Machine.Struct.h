/*
 * Machine.Struct.h
 *
 *  Created on: 2019年9月17日
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

	const void *Clock_Source;
	void *Clock_Tree;

	int (*UpData_Clock_Tree)(void);
}Machine_Desc_CPU_Type;
//-------------------------------------------------------------------------
#ifdef __MPU__

typedef struct
{
	unsigned int Base_Address;
	unsigned int Region_Index				:4;
	unsigned int Enabled					:1;
	unsigned int Sub_Region_Disable		:8;
	unsigned int Region_Size				:5;
	unsigned int Execute_Never				:1;
	unsigned int Access_Permission			:3;
	unsigned int Attributes				:6;
}Machine_Desc_MPU_Cfg_Type;

typedef struct
{
	const Machine_Desc_MPU_Cfg_Type *P_MPU_Cfg;

	int MPU_Cfg_Index;

	int (*Init)(void);

	int (*Enable)(void);
	int (*Disable)(void);

	int (*GET_Region_Number)(void);

	int (*SET_Region)(Machine_Desc_MPU_Cfg_Type *);
	int (*GET_Region)(unsigned int,Machine_Desc_MPU_Cfg_Type *);

	int (*SET_Region_Enable)(unsigned int);
	int (*SET_Region_Disable)(unsigned int);

	int (*GET_Data_Fault_Status)(unsigned int *);
	int (*GET_Instruction_Fault_Status)(unsigned int *);

}Machine_Desc_MPU_Type;

#endif
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

#ifdef __MPU__
	Machine_Desc_MPU_Type MPU;
#endif

}Machine_Desc_Type;
//-------------------------------------------------------------------------

#endif /* MACHINE_STRUCT_H_ */
