/*
 * Device.Class.c
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */
#include "Define.h"
#include "Error.h"
#include "__Device.Class.h"

#include "ETH/__Device.Class.ETH.h"

//Device_Class_DATA_Type Device_Class_DATA;

int Device_Class_Init(void)
{
	int Err;

	Error_NoArgs_Return(Err,Device_Class_ETH_Init());

	return Error_OK;
}
