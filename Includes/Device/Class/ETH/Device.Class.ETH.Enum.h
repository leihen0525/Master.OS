/*
 * Device.Class.ETH.Enum.h
 *
 *  Created on: 2022年1月7日
 *      Author: Master.HE
 */

#ifndef DEVICE_CLASS_ETH_ENUM_H_
#define DEVICE_CLASS_ETH_ENUM_H_

typedef enum
{

	Device_Class_ETH_Enum_Send_Flag_Timestamp					=(1<<0),
	Device_Class_ETH_Enum_Send_Flag_Insert_IP_Header_CheckSum	=(1<<1),
	Device_Class_ETH_Enum_Send_Flag_Insert_Protocol_CheckSum	=(1<<2),


}Device_Class_ETH_Enum_Send_Flag_Type;

typedef enum
{
	Device_Class_ETH_Enum_Receive_Flag_Payload_Checksum_Mask	=0xFFFF,

	Device_Class_ETH_Enum_Receive_Flag_CRC_Error				=(1<<16),
	Device_Class_ETH_Enum_Receive_Flag_IP_Header_CheckSum_Error	=(1<<17),
	Device_Class_ETH_Enum_Receive_Flag_Protocol_CheckSum_Error	=(1<<18),
	Device_Class_ETH_Enum_Receive_Flag_VLAN_Tag					=(1<<19),

	Device_Class_ETH_Enum_Receive_Flag_Broadcast				=(1<<20),
	Device_Class_ETH_Enum_Receive_Flag_Multicast				=(1<<21),
	Device_Class_ETH_Enum_Receive_Flag_Unicast					=(1<<22),
	Device_Class_ETH_Enum_Receive_Flag_IPv4_Fragment			=(1<<23),

	Device_Class_ETH_Enum_Receive_Flag_IPv6_Frame				=(1<<24),
	Device_Class_ETH_Enum_Receive_Flag_Timestamp				=(1<<25),
	Device_Class_ETH_Enum_Receive_Flag_Payload_Checksum_En		=(1<<26),

}Device_Class_ETH_Enum_Receive_Flag_Type;

typedef enum
{
	Device_Class_ETH_Enum_Interface_xMII_MII				=0,

	Device_Class_ETH_Enum_Interface_xMII_GMII,

	Device_Class_ETH_Enum_Interface_xMII_SMII,
	Device_Class_ETH_Enum_Interface_xMII_SGMII,

	Device_Class_ETH_Enum_Interface_xMII_RMII,
	Device_Class_ETH_Enum_Interface_xMII_RGMII,

	Device_Class_ETH_Enum_Interface_xMII_End,

}Device_Class_ETH_Enum_Interface_xMII_Type;

typedef enum
{
	Device_Class_ETH_Enum_Interface_Speed_10Mbps			=0,
	Device_Class_ETH_Enum_Interface_Speed_100Mbps,

	Device_Class_ETH_Enum_Interface_Speed_1Gbps,
	Device_Class_ETH_Enum_Interface_Speed_2_5Gbps,

	Device_Class_ETH_Enum_Interface_Speed_10Gbps,

	Device_Class_ETH_Enum_Interface_Speed_End,
}Device_Class_ETH_Enum_Interface_Speed_Type;

#endif /* DEVICE_CLASS_ETH_ENUM_H_ */
