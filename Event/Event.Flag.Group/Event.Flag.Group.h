/*
 * Event.Flag.Group.h
 *
 *  Created on: 2019年4月30日
 *      Author: Master.HE
 */

#ifndef EVENT_FLAG_GROUP_H_
#define EVENT_FLAG_GROUP_H_

#include "__Sys.Scheduling.Task.Struct.h"

static bool Event_Flag_Group_Operation_And(
		Task_Event_DATA_Event_Flag_Group_Type *Event_Flag_Group,

		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,

		uint32_t Flag_Group_LEN);
static bool Event_Flag_Group_Operation_And_R(
		Task_Event_DATA_Event_Flag_Group_Type *Event_Flag_Group,
		uint32_t Flag_Group_LEN);

static bool Event_Flag_Group_Operation_Or(
		Task_Event_DATA_Event_Flag_Group_Type *Event_Flag_Group,

		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_BIT,

		uint32_t Flag_Group_LEN);
static bool Event_Flag_Group_Operation_Or_R(
		Task_Event_DATA_Event_Flag_Group_Type *Event_Flag_Group,
		uint32_t Flag_Group_LEN);
static bool Event_Flag_Group_Operation_Clear_BIT(
		Task_Event_DATA_Event_Flag_Group_Type *Event_Flag_Group,

		uint8_t *Event_Flag_Group_Mask,
		uint8_t *Event_Flag_Group_Clear_BIT,

		uint32_t Flag_Group_LEN);

#endif /* EVENT_FLAG_GROUP_H_ */
