/*
 * MPU.Enum.h
 *
 *  Created on: 2019年11月18日
 *      Author: Master.HE
 */

#ifndef MPU_ENUM_H_
#define MPU_ENUM_H_

#ifdef __MPU__

typedef enum
{
	MPU_Execute_Never_Enable		=0,   /*!< all instruction fetches enabled */
	MPU_Execute_Never_Disable		=1,   /*!< no instruction fetches enabled. */
	MPU_Execute_Never_End,
}MPU_Execute_Never_Type;



typedef enum
{
	MPU_AP_All_NoAccess					=0,
	MPU_AP_Sys_WR_AND_User_NoAccess		=1,
	MPU_AP_Sys_WR_AND_User_OR			=2,
	MPU_AP_Sys_WR_AND_User_WR			=3,
	MPU_AP_All_Reserve1					=4,
	MPU_AP_Sys_OR_AND_User_NoAccess		=5,
	MPU_AP_Sys_OR_AND_User_OR			=6,
	MPU_AP_All_Reserve2					=7,

	MPU_AP_End,
}MPU_AP_Type;

//Attributes
typedef enum
{										//S-BIT
	MPU_Attributes_Share_NonShared		=(0<<2),
	MPU_Attributes_Share_Shared			=(1<<2),
}MPU_Attributes_Share_Type;

//Wt=write-through
//Wa=write-allocate
//Wb=write-back
typedef enum
{
	//												//TEX	C		B
	MPU_Attributes_Strongly_Ordered_Shareable		=((0<<3)|(0<<1)|(0<<0)),
	MPU_Attributes_Device_Shareable					=((0<<3)|(0<<1)|(1<<0)),
	MPU_Attributes_Normal_Wt_NoWa_ShareBit			=((0<<3)|(1<<1)|(0<<0)),
	MPU_Attributes_Normal_Wb_NoWa_ShareBit			=((0<<3)|(1<<1)|(1<<0)),
	MPU_Attributes_Normal_NonCacheable_ShareBit		=((1<<3)|(0<<1)|(0<<0)),

	MPU_Attributes_Normal_Wb_Wa_ShareBit			=((1<<3)|(1<<1)|(1<<0)),
	MPU_Attributes_Device_NonShareable				=((2<<3)|(0<<1)|(0<<0)),

	MPU_Attributes_Normal_DiffCache_Policy_ShareBit	=((4<<3)|(0<<1)|(0<<0)),
}MPU_Attributes_Type;

typedef enum
{
	//												//TEX[1:0]
	MPU_Attributes_Outer_Policy_NonCacheable		=((0<<4)|(0<<3)),
	MPU_Attributes_Outer_Policy_Wb_Wa				=((0<<4)|(1<<3)),
	MPU_Attributes_Outer_Policy_Wt_NoWa				=((1<<4)|(0<<3)),
	MPU_Attributes_Outer_Policy_Wb_NoWa				=((1<<4)|(1<<3)),
}MPU_Attributes_Outer_Policy_Type;

typedef enum
{
	//												//C			B
	MPU_Attributes_Inner_Policy_NonCacheable		=((0<<1)|(0<<0)),
	MPU_Attributes_Inner_Policy_Wb_Wa				=((0<<1)|(1<<0)),
	MPU_Attributes_Inner_Policy_Wt_NoWa				=((1<<1)|(0<<0)),
	MPU_Attributes_Inner_Policy_Wb_NoWa				=((1<<1)|(1<<0)),
}MPU_Attributes_Inner_Policy_Type;



typedef enum
{
	MPU_Fault_Status_Null							=0,

	MPU_Fault_Status_Background,
	MPU_Fault_Status_Background_Read,
	MPU_Fault_Status_Background_Write,

	MPU_Fault_Status_Permission,
	MPU_Fault_Status_Permission_Read,
	MPU_Fault_Status_Permission_Write,

	MPU_Fault_Status_End,
}MPU_Fault_Status_Type;

#endif

#endif /* MPU_ENUM_H_ */
