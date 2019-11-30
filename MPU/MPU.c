/*
 * MPU.c
 *
 *  Created on: 2019年11月18日
 *      Author: Master.HE
 */
#ifdef __MPU__

#include <stdlib.h>

#include "Error.h"
#include "MPU.Enum.h"
#include "MPU.Define.h"
#include "MPU.Struct.h"

#include "MPU.h"

#include "Scheduling/Scheduling.h"



MPU_DATA_Type MPU_DATA=
{
	.Sys_Cfg=
	{
		.Base_Address=0x00000000,
		.Region_Index=0x00,

		.Enabled=Enable,
		.Sub_Region_Disable=0x00,
		.Region_Size=MPU_Region_Size_32Byte,
		.Execute_Never=MPU_Execute_Never_Enable,
		.Access_Permission=MPU_AP_All_NoAccess,
		.Attributes=MPU_Attributes_Normal_Wb_NoWa_ShareBit,
	},

	.Usr_Cfg=
	{
		.Base_Address=0x00000000,
		.Region_Index=0x00,

		.Enabled=Enable,
		.Sub_Region_Disable=0x00,
		.Region_Size=MPU_Region_Size_32Byte,
		.Execute_Never=MPU_Execute_Never_Enable,
		.Access_Permission=MPU_AP_All_NoAccess,
		.Attributes=MPU_Attributes_Normal_Wb_NoWa_ShareBit,
	},
	.MPU=Null,
};

int MPU_Init(Machine_Desc_MPU_Type *P_MPU)
{
	if(P_MPU==Null)
	{
		return Error_Invalid_Parameter;
	}

	MPU_DATA.MPU=P_MPU;

	if(MPU_DATA.MPU->P_MPU_Cfg==Null
	|| MPU_DATA.MPU->Init==Null
	|| MPU_DATA.MPU->Enable==Null
	|| MPU_DATA.MPU->Disable==Null
	|| MPU_DATA.MPU->GET_Region_Number==Null
	|| MPU_DATA.MPU->SET_Region==Null
	|| MPU_DATA.MPU->GET_Region==Null
	|| MPU_DATA.MPU->SET_Region_Enable==Null
	|| MPU_DATA.MPU->SET_Region_Disable==Null
	|| MPU_DATA.MPU->GET_Data_Fault_Status==Null
	|| MPU_DATA.MPU->GET_Instruction_Fault_Status==Null)
	{
		return Error_Undefined;
	}

	int Err=MPU_DATA.MPU->Init();

	if(Err!=Error_OK)
	{
		return Err;
	}

	//
	Err=MPU_DATA.MPU->GET_Region_Number();

	if(Err<Error_OK)
	{
		return Err;
	}

	int Max_Index=Err;

	if(Max_Index<2)
	{
		return Error_Unknown;
	}


	MPU_DATA.Sys_Cfg.Region_Index=Max_Index-1;
	MPU_DATA.Usr_Cfg.Region_Index=Max_Index-2;


	return Error_OK;

}

int MPU_SET(uint32_t Sys_Base_Address,uint32_t Sys_Region_Size,uint32_t Usr_Base_Address,uint32_t Usr_Region_Size)
{

	if((Sys_Base_Address&0x1F)!=0
	|| (Usr_Base_Address&0x1F)!=0
	|| Sys_Region_Size<=MPU_Region_Size_Null
	|| MPU_Region_Size_End<=Sys_Region_Size
	|| Usr_Region_Size<=MPU_Region_Size_Null
	|| MPU_Region_Size_End<=Usr_Region_Size)
	{
		return Error_Invalid_Parameter;
	}

	MPU_DATA.Sys_Cfg.Base_Address=Sys_Base_Address&0xFFFFFFE0;
	MPU_DATA.Sys_Cfg.Region_Size=Sys_Region_Size;
	MPU_DATA.Usr_Cfg.Base_Address=Usr_Base_Address&0xFFFFFFE0;
	MPU_DATA.Usr_Cfg.Region_Size=Usr_Region_Size;

	int Err=Error_OK;
	if((Err=MPU_DATA.MPU->SET_Region(&MPU_DATA.Sys_Cfg))!=Error_OK)
	{
		return Err;
	}
	if((Err=MPU_DATA.MPU->SET_Region(&MPU_DATA.Usr_Cfg))!=Error_OK)
	{
		return Err;
	}

	asm("DSB");
	asm("ISB");

	return Error_OK;

}
int MPU_SET_Region_Disable(void)
{
	int Err=Error_OK;
	if((Err=MPU_DATA.MPU->SET_Region_Disable(MPU_DATA.Sys_Cfg.Region_Index))!=Error_OK)
	{
		return Err;
	}
	if((Err=MPU_DATA.MPU->SET_Region_Disable(MPU_DATA.Usr_Cfg.Region_Index))!=Error_OK)
	{
		return Err;
	}

	asm("DSB");
	asm("ISB");

	return Error_OK;
}



void MPU_Handle_Data_Fault(uint32_t Mode,uint32_t *Fault_SP,uint32_t Fault_Code_Address)
{
	uint32_t Fault_Address=0;

	int Err=MPU_DATA.MPU->GET_Data_Fault_Status(&Fault_Address);

	if(Err==MPU_Fault_Status_Permission_Read || Err==MPU_Fault_Status_Permission_Write)
	{
		//检查当前栈和出错地址之间的差值，如果大于32，那么当前可能不是栈溢出，而是出现其他未知错误
		//if(abs((uint32_t)Fault_SP-Fault_Address)>32)
		{
			//while(1);
		}
		//无解
		while(1);

		if(__Sys_Scheduling_MPU_Add_Stack(Mode,Fault_SP,Fault_Address)!=Error_OK)
		{
			while(1)Fault_Code_Address=Fault_Code_Address;
		}
	}
	else
	{
		while(1);
	}

}



#endif
