/*
 * Message.Queue.Struct.h
 *
 *  Created on: 2019年4月30日
 *      Author: Master.HE
 */

#ifndef MESSAGE_QUEUE_STRUCT_H_
#define MESSAGE_QUEUE_STRUCT_H_

#include "Master.Stdint.h"

typedef struct
{

	void *Message_DATA;
	uint32_t *Message_Size;

	uint32_t Index_In;

	uint32_t Max_Message_Size;
	uint32_t Max_Message_Queue_Length;


}Event_Message_Queue_Node_Type;

#endif /* MESSAGE_QUEUE_STRUCT_H_ */
