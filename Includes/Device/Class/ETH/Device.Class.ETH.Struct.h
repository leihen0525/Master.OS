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
	uint32_t Tx_Queue_Depth;
	uint32_t Rx_Queue_Depth;

	uint32_t Buff_Size;
}Device_Class_ETH_Static_Cfg_Queue_Type;

typedef union
{
	uint32_t Data;
	struct
	{
		uint32_t Timestamp					:1;
		uint32_t Insert_IP_Header_CheckSum	:1;
		uint32_t Insert_Protocol_CheckSum	:1;
		uint32_t							:1;

		uint32_t							:1;
		uint32_t							:1;
		uint32_t							:1;
		uint32_t							:1;

		uint32_t						:24;
	};

}Device_Class_ETH_Struct_Send_Flag_Type;

typedef union
{
	uint32_t Data;
	struct
	{
		uint32_t Payload_Checksum			:16;

		uint32_t CRC_Error					:1;
		uint32_t IP_Header_CheckSum_Error	:1;
		uint32_t Protocol_CheckSum_Error	:1;
		uint32_t VLAN_Tag					:1;

		uint32_t Broadcast					:1;
		uint32_t Multicast					:1;
		uint32_t Unicast					:1;
		uint32_t IPv4_Fragment				:1;

		uint32_t IPv6_Frame					:1;
		uint32_t Timestamp					:1;
		uint32_t Payload_Checksum_En		:1;
		uint32_t							:5;

	};

}Device_Class_ETH_Struct_Receive_Flag_Type;

typedef struct
{
	Device_Class_ETH_Struct_Send_Flag_Type Send;
	Device_Class_ETH_Struct_Receive_Flag_Type Receive;
}Device_Class_ETH_Static_Cfg_Support_Transfer_Flag_Type;

typedef union
{
	uint32_t Data;
	struct
	{
		uint32_t MII					:1;
		uint32_t GMII					:1;
		uint32_t SMII					:1;
		uint32_t SGMII					:1;
		uint32_t RMII					:1;
		uint32_t RGMII					:1;

		uint32_t						:1;
		uint32_t						:1;

		uint32_t						:24;
	};
}Device_Class_ETH_Static_Cfg_Support_Interface_xMII_Type;

typedef union
{
	uint32_t Data;
	struct
	{
		uint32_t Speed_10Mbps			:1;
		uint32_t Speed_100Mbps			:1;
		uint32_t Speed_1Gbps			:1;
		uint32_t Speed_2_5Gbps			:1;
		uint32_t Speed_10Gbps			:1;

		uint32_t						:1;
		uint32_t						:1;
		uint32_t						:1;

		uint32_t						:24;
	};
}Device_Class_ETH_Static_Cfg_Support_Interface_Speed_Type;

typedef struct
{
	Device_Class_ETH_Static_Cfg_Support_Interface_xMII_Type xMII;
	Device_Class_ETH_Static_Cfg_Support_Interface_Speed_Type Speed;
	bool Full_Duplex;
}Device_Class_ETH_Static_Cfg_Support_Interface_Type;


typedef struct
{
	uint8_t *MAC_Address;// 例子 .MAC_Address="\x10\x22\x33\x44\x55\x66" OR Null

	struct
	{
		uint32_t Count;
		const Device_Class_ETH_Static_Cfg_Queue_Type *P_Data;
	}Queue;

	struct
	{
		const Device_Class_ETH_Static_Cfg_Support_Transfer_Flag_Type *P_Transfer;
		const Device_Class_ETH_Static_Cfg_Support_Interface_Type *P_Interface;
	}Support;

}Device_Class_ETH_Static_Cfg_Type;


typedef struct
{
	uint8_t *P_Buffer;
	uint32_t Size;

}Device_Class_ETH_Send_Slice_Data_Type;




#endif /* DEVICE_CLASS_ETH_STRUCT_H_ */
