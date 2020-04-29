/*
 * Init.Module.h
 *
 *  Created on: 2019年9月17日
 *      Author: Master.HE
 */

#ifndef INIT_MODULE_H_
#define INIT_MODULE_H_

int Module_Init_Task(void);

int Module_Init_Sys_Device(void);
int Module_Init_Sys_Com(void);

int Module_Init_Com(void);
int Module_Init_Application(void);

#endif /* INIT_MODULE_H_ */
