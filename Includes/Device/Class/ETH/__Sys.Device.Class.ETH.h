/*
 * __Sys.Device.Class.ETH.h
 *
 *  Created on: 2022年1月7日
 *      Author: Master.HE
 */

#ifndef SYS_DEVICE_CLASS_ETH_H_
#define SYS_DEVICE_CLASS_ETH_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "__Sys.Device.Class.ETH.Struct.h"

#include "Device.Class.ETH.h"

int __Sys_Device_Class_ETH_Register_Drivers(const __Sys_Device_Class_ETH_OPS_Type *P_OPS);

#ifdef __cplusplus
}
#endif

#endif /* SYS_DEVICE_CLASS_ETH_H_ */
