/*
 * Module.h
 *
 *  Created on: 2019Äê4ÔÂ8ÈÕ
 *      Author: Master.HE
 */

#ifndef MODULE_H_
#define MODULE_H_

#include "Module.Struct.h"

typedef int (*Module_Init_Fun)(void);

#define Module_Init_Export(Fun_Module,level)		\
			__root const Module_Init_Fun __Module_Init_##Fun_Module##__ @".Module.Init."level = Fun_Module




#define __Sys_Device_Module_Init_Export(__Sys_Fun)		Module_Init_Export(__Sys_Fun,"Sys.Device")

#define __Sys_Com_Module_Init_Export(__Sys_Fun)			Module_Init_Export(__Sys_Fun,"Sys.Com")

#define Com_Module_Init_Export(Fun)						Module_Init_Export(Fun,"Com")

#define Application_Module_Init_Export(Fun)				Module_Init_Export(Fun,"Application")




#define __Sys_Module_Init_Task(_Name,_Task_Enter,_Args,_Priority,_Stack,_Stack_Size_4Byte,_Option)		\
__root const __Module_Init_Task_Type __Module_Init_Task_##_Task_Enter @".Module.Init.Task" =			\
{																										\
	.Name = _Name,																						\
	.Task_Enter=_Task_Enter,																			\
	.Args=_Args,																						\
	.Priority=_Priority,																				\
	.Stack=_Stack,																						\
	.Stack_Size_4Byte=_Stack_Size_4Byte,																\
	.Option=_Option,																					\
};



#endif /* MODULE_H_ */
