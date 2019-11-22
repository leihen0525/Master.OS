/*
 * Define.h
 *
 *  Created on: 2019Äê4ÔÂ16ÈÕ
 *      Author: Master.HE
 */

#ifndef DEFINE_H_
#define DEFINE_H_

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
#define Stack_System_Default_Size_4Byte				(100)
#define Stack_Task_Task_4Byte						(100)



#define Event_Flag_Group_Max_Len					(12)
#define Timer_FIFO_Queue_Max_Length					(16)


#endif /* DEFINE_H_ */
