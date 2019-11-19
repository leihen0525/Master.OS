/*
 * Scheduling.Task.Define.h
 *
 *  Created on: 2019Äê4ÔÂ23ÈÕ
 *      Author: Master.HE
 */

#ifndef SCHEDULING_TASK_DEFINE_H_
#define SCHEDULING_TASK_DEFINE_H_

#define Scheduling_Task_Option_User							(0<<0)
#define Scheduling_Task_Option_System						(1<<0)

#ifdef __ARMVFP__
#define Scheduling_Task_Option_FPU_VFP						(1<<1)
#endif


typedef void (__task *Task_Enter_Function)(void *);

typedef void (*Task_Exit_Function)(void);

#endif /* SCHEDULING_TASK_DEFINE_H_ */
