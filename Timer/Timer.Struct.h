/*
 * Timer.Struct.h
 *
 *  Created on: 2019年4月29日
 *      Author: Master.HE
 */

#ifndef TIMER_STRUCT_H_
#define TIMER_STRUCT_H_

#include "Timer.Define.h"
#include "Master.Stdint.h"

#include "Machine/Machine.Struct.h"

typedef struct
{
	void *Args;
	Timer_Enter_Function Timer_Function;
}Timer_Function_Type;

typedef struct Timer_Node
{
	int Handle;

	//Init
	int32_t N_Time_Cycle;				//次数
	int32_t Cycle_Time_MS;				//周期

	//Temp
	int32_t Suspended_Time_MS;			//被挂起时时间
	int32_t Now_Countdown_N_Time_Cycle;

	int32_t TimeOut_MS;//倒计时时间

	Timer_Function_Type Timer_Function;

	struct Timer_Node *NEXT;

}Timer_Node_Type;

typedef struct
{
	Timer_Node_Type *Begin;
	Timer_Node_Type *End;
}Timer_Queue_Type;

typedef struct
{
	Machine_Desc_Timer_Type *Timer;


	Enabled_Type Enabled;

	int FIFO_Queue;


	//定时器队列
	Timer_Queue_Type Timer_Queue;




}Timer_DATA_Type;

#endif /* TIMER_STRUCT_H_ */
