/*
 * MPU.c
 *
 *  Created on: 2019Äê11ÔÂ18ÈÕ
 *      Author: Master.HE
 */
#ifdef __MPU__

#include "Error.h"

#include "MPU.Struct.h"

#include "MPU.h"

MPU_DATA_Type MPU_DATA;

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
	|| MPU_DATA.MPU->SET_Region_Disable==Null)
	{
		return Error_Undefined;
	}

	int Err=MPU_DATA.MPU->Init();

	if(Err!=Error_OK)
	{
		return Err;
	}

	return Error_OK;

}









#endif
