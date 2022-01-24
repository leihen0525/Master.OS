/*
 * Semaphore.Struct.h
 *
 *  Created on: 2019年4月29日
 *      Author: Master.HE
 */

#ifndef SEMAPHORE_STRUCT_H_
#define SEMAPHORE_STRUCT_H_

#include "Master.Stdint.h"
#include "Event/Event.Enum.h"

typedef struct
{
	Event_Queue_Option_Type Option;

	uint32_t Count;
	uint32_t MAX_Count;

}Event_Semaphore_Node_Type;

#endif /* SEMAPHORE_STRUCT_H_ */
