/*
 * Device.Class.ETH.Struct.h
 *
 *  Created on: 2022年1月6日
 *      Author: Master.HE
 */

#ifndef DEVICE_CLASS_ETH_STRUCT_H_
#define DEVICE_CLASS_ETH_STRUCT_H_

#include "Master.Stdint.h"

typedef struct
{
	uint8_t *P_Buffer;
	uint32_t Size;

}Device_Class_ETH_Send_Slice_Data_Type;

typedef union
{
	uint32_t Data;
	struct
	{
		uint32_t CRC					:1;
		uint32_t IP_CheckSum			:1;
		uint32_t TCP_CheckSum			:1;
		uint32_t UDP_CheckSum			:1;

		uint32_t						:1;
		uint32_t						:1;
		uint32_t						:1;
		uint32_t						:1;

		uint32_t						:16;
	};

}Device_Class_ETH_Struct_Flag_Type;


#endif /* DEVICE_CLASS_ETH_STRUCT_H_ */
