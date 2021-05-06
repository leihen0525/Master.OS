/*
 * Error.h
 *
 *  Created on: 2019年4月15日
 *      Author: Master.HE
 */

#ifndef ERROR_H_
#define ERROR_H_

typedef enum
{
	Error_No_Bind						=-29,					//没有绑定
	Error_No_Connect					=-28,					//没有连接

	Error_No_Init						=-27,					//未初始化

	Error_Not_Responding				=-26,					//未响应
	Error_No_Enable						=-25,					//未使能

	Error_Config						=-24,					//配置错误

	Error_No_Clock_Config				=-23,					//时钟未配置

	Error_Write_Register_Fault			=-22,					//写入寄存器失败
	Error_Read_Register_Fault			=-21,					//读取寄存器失败
	Error_Clear_Register_Fault			=-20,					//清除寄存器失败

	Error_Clock_Fault					=-19,					//时钟故障
	Error_No_Find						=-18,					//未找到
	Error_No_Start						=-17,					//没有开始
	Error_No_Space						=-16,					//
	Error_No_Link						=-15,					//没有连接
	Error_Exist							=-14,					//已经存在
	Error_OverFlow						=-13,					//溢出
	Error_Empty							=-12,					//空

	Error_Busy							=-11,					//忙碌
	Error_No_Open						=-10,					//未打开
	Error_Illegal						=-9,					//不合法的
	Error_Dissatisfy					=-8,					//无法得到满足
	Error_Time_Out						=-7,					//超时
	Error_Operation_Failed				=-6,					//操作失败
	Error_Unknown						=-5,					//未知错误
	Error_Allocation_Memory_Failed		=-4,					//内存分配失败
	Error_Invalid_Parameter				=-3,					//无效参数
	Error_Invalid_Handle				=-2,					//无效句柄
	Error_Undefined						=-1,					//未定义

	Error_OK							=0,						//OK


}Error_Type;

#endif /* ERROR_H_ */
