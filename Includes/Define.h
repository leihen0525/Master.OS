/*
 * Define.h
 *
 *  Created on: 2019年4月16日
 *      Author: Master.HE
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#ifdef __MPU__
#include "MPU.Define.h"
#endif

#define Valid_Handle								(0)

#define Task_Time_Slice_MS							(10)

//#define IRQ_Priority								((1UL << __NVIC_PRIO_BITS) - 1UL)

#define IRQ_PendSV									(-2)
#define IRQ_SysTick									(-1)

//Priority
#define Priority_Task_Idle							(255)

#define Priority_Task_Mutex							(1)
#define Priority_Task_Task							(10)

//Stack
#ifdef __MPU__
#define Stack_Default_Protection_Size				MPU_Region_Size_32Byte
#define Stack_Default_Protection_Size_Byte(x)		(1<<(x+1))
//#define Stack_Alignment_Byte						(32)
#else
#define Stack_Alignment_Byte						(8)
#endif

//
#define Stack_Add_Size_4Byte						(16)
#define Stack_System_Default_Size_4Byte				(100)
#define Stack_Task_Task_4Byte						(150)




#define Event_Flag_Group_Max_Len					(12)
#define Timer_FIFO_Queue_Max_Length					(16)


#endif /* DEFINE_H_ */
