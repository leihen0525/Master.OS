/*
 * __Sys.Device.Legacy.h
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */

#ifndef SYS_DEVICE_LEGACY_H_
#define SYS_DEVICE_LEGACY_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "__Sys.Device.Legacy.Struct.h"

int __Sys_Device_Legacy_Register_Drivers(const __Sys_Device_Legacy_OPS_Type *P_OPS);


#ifdef __cplusplus
}
#endif

#endif /* SYS_DEVICE_LEGACY_H_ */
