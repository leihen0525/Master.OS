/*
 * Event.Enum.h
 *
 *  Created on: 2019年4月29日
 *      Author: Master.HE
 */

#ifndef EVENT_ENUM_H_
#define EVENT_ENUM_H_



typedef enum
{
	Event_Queue_Option_FIFO=0,
	Event_Queue_Option_Priority,

	Event_Queue_Option_End,
}Event_Queue_Option_Type;

typedef enum
{
	Event_Time_Out_Query				=-2,		//查询

	Event_Time_Out_Infinite				=-1,		//无限等待

	Event_Time_Out_Occupy_Return_Back	=0,			//尝试占用并立即返回

}Event_Time_Out_Type;



typedef enum
{
	Event_Flag_Group_Clear_Any_Read_Retain		=0,					//任何读取都保持
	Event_Flag_Group_Clear_Any_Read_Clear,							//任何读取后都清除


	//Event_Flag_Group_Clear_Any_Read_Result_OK_Retain_NoOK_Retain,	//结果OK保留 NoOK保留

	Event_Flag_Group_Clear_Any_Read_Result_OK_Retain_Dissatisfy_Clear,//结果OK保留 Dissatisfy清除

	Event_Flag_Group_Clear_Any_Read_Result_OK_Clear_Dissatisfy_Retain,//结果OK清除 Dissatisfy保留

	//Event_Flag_Group_Clear_Any_Read_Result_OK_Clear_NoOK_Clear,		//结果OK清除 NoOK清除

	Event_Flag_Group_Clear_End,
}Event_Flag_Group_Clear_Type;

#endif /* EVENT_ENUM_H_ */
