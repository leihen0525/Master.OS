/*
 * Device.c
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */
#include "Error.h"
#include "Define.h"

#include "__Device.h"

#include "Legacy/Device.Legacy.h"
#include "Class/__Device.Class.h"

int Device_Init(void)
{
	int Err;

	Error_NoArgs_Return(Err,Device_Legacy_Init());
	Error_NoArgs_Return(Err,Device_Class_Init());

	return Error_OK;
}
