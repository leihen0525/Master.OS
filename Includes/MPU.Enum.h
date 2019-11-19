/*
 * MPU.Enum.h
 *
 *  Created on: 2019Äê11ÔÂ18ÈÕ
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
	MPU_Region_Size_Null	= 3,

	MPU_Region_Size_32Byte  = 4,    /*!< Region size 32 Byte */
	MPU_Region_Size_64Byte  = 5,    /*!< Region size 64 Byte */
	MPU_Region_Size_128Byte = 6,    /*!< Region size 128 Byte */
	MPU_Region_Size_256Byte = 7,    /*!< Region size 256 Byte */
	MPU_Region_Size_512Byte = 8,    /*!< Region size 512 Byte */
	MPU_Region_Size_1kB     = 9,    /*!< Region size 1 kB */
	MPU_Region_Size_2kB     = 10,   /*!< Region size 2 kB */
	MPU_Region_Size_4kB     = 11,   /*!< Region size 4 kB */
	MPU_Region_Size_8kB     = 12,   /*!< Region size 8 kB */
	MPU_Region_Size_16kB    = 13,   /*!< Region size 16 kB */
	MPU_Region_Size_32kB    = 14,   /*!< Region size 32 kB */
	MPU_Region_Size_64kB    = 15,   /*!< Region size 64 kB */
	MPU_Region_Size_128kB   = 16,   /*!< Region size 128 kB */
	MPU_Region_Size_256kB   = 17,   /*!< Region size 256 kB */
	MPU_Region_Size_512kB   = 18,   /*!< Region size 512 kB */
	MPU_Region_Size_1MB     = 19,   /*!< Region size 1M MB */
	MPU_Region_Size_2MB     = 20,   /*!< Region size 2 MB */
	MPU_Region_Size_4MB     = 21,   /*!< Region size 4 MB */
	MPU_Region_Size_8MB     = 22,   /*!< Region size 8 MB */
	MPU_Region_Size_16MB    = 23,   /*!< Region size 16 MB */
	MPU_Region_Size_32MB    = 24,   /*!< Region size 32 MB */
	MPU_Region_Size_64MB    = 25,   /*!< Region size 64 MB */
	MPU_Region_Size_128MB   = 26,   /*!< Region size 128 MB */
	MPU_Region_Size_256MB   = 27,   /*!< Region size 256 MB */
	MPU_Region_Size_512MB   = 28,   /*!< Region size 512 MB */
	MPU_Region_Size_1GB     = 29,   /*!< Region size 1 GB */
	MPU_Region_Size_2GB     = 30,   /*!< Region size 2 GB */
	MPU_Region_Size_4GB     = 31,   /*!< Region size 4 GB */

	MPU_Region_Size_End,
}MPU_Region_Size_Type;

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


#endif

#endif /* MPU_ENUM_H_ */
