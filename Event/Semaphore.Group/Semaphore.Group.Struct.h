/*
 * Semaphore.Group.Struct.h
 *
 *  Created on: 2019Äê4ÔÂ30ÈÕ
 *      Author: Master.HE
 */

#ifndef SEMAPHORE_GROUP_STRUCT_H_
#define SEMAPHORE_GROUP_STRUCT_H_

#include "Master.Stdint.h"
#include "Event.Enum.h"

typedef struct
{
	Event_Queue_Option_Type Option;

	int32_t Count;

}Event_Semaphore_Group_Node_Type;

#endif /* SEMAPHORE_GROUP_STRUCT_H_ */
