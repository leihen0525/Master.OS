/*
 * Scheduling.Task.Define.h
 *
 *  Created on: 2019Äê4ÔÂ23ÈÕ
 *      Author: Master.HE
 */

#ifndef SCHEDULING_TASK_DEFINE_H_
#define SCHEDULING_TASK_DEFINE_H_



#ifdef __MPU__
#define Scheduling_Task_Stack_Usr_Size_4Byte(x)						(x&0xFFFF)
#define Scheduling_Task_Stack_SET_Sys_Size_4Byte(x)					((x<<16)&0xFFFF0000)
#define Scheduling_Task_Stack_GET_Sys_Size_4Byte(x)					((x>>16)&0xFFFF)

//#define Scheduling_Task_Option_SET_Usr_Stack_Protection_Size(x)		(x&0xFF)
#define Scheduling_Task_Option_GET_Usr_Stack_Protection_Size(x)		(x&0xFF)
#endif

#define Scheduling_Task_Option_User									(0<<8)
#define Scheduling_Task_Option_System								(1<<8)



#ifdef __ARMVFP__
#define Scheduling_Task_Option_FPU_VFP								(1<<9)
#endif


typedef void (__task *Task_Enter_Function)(void *);

typedef void (*Task_Exit_Function)(void);

#endif /* SCHEDULING_TASK_DEFINE_H_ */
