/*
 * Master.Stdint.h
 *
 *  Created on: 2019年4月8日
 *      Author: Master.HE
 */

#ifndef MASTER_STDINT_H_
#define MASTER_STDINT_H_

#include <stdint.h>


typedef enum
{
	false=0,
	true,

	bool_End,
}bool;

typedef enum	//使能状态
{
	Disable=0,		//关闭
	Enable,			//开启

	Enabled_End
}Enabled_Type;



#define Null ((void *)0)

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#endif /* MASTER_STDINT_H_ */
