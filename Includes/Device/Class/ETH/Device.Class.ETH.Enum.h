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

	Device_Class_ETH_Enum_Flag_CRC					=(1<<0),
	Device_Class_ETH_Enum_Flag_IP_CheckSum			=(1<<1),
	Device_Class_ETH_Enum_Flag_TCP_CheckSum			=(1<<2),
	Device_Class_ETH_Enum_Flag_UDP_CheckSum			=(1<<3),

}Device_Class_ETH_Enum_Flag_Type;

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
