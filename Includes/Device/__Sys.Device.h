/*
 * __Sys.Device.h
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */

#ifndef __SYS_DEVICE_H_
#define __SYS_DEVICE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "__Sys.Device.Struct.h"

int __Sys_Device_Register_Drivers(const __Sys_Device_OPS_Type *P_OPS);


#ifdef __cplusplus
}
#endif

#endif /* __SYS_DEVICE_H_ */
