/*
 * SysCall.h
 *
 *  Created on: 2019年4月8日
 *      Author: Master.HE
 */

#ifndef SYSCALL_H_
#define SYSCALL_H_

#ifdef __cplusplus
 extern "C" {
#endif

int SysCall(
		int number,
		...//Max:8
		);

#ifdef __cplusplus
}
#endif

#endif /* SYSCALL_H_ */
