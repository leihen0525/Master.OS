/*
 * IRQ.Struct.h
 *
 *  Created on: 2019Äê4ÔÂ16ÈÕ
 *      Author: Master.HE
 */

#ifndef IRQ_STRUCT_H_
#define IRQ_STRUCT_H_

#include "Master.Stdint.h"

#include "IRQ.Define.h"

#include "Machine/Machine.Struct.h"

typedef struct IRQ_Hook_List
{
	int Handle;

	void *Args;

	IRQ_Hook_Function Function;

	struct IRQ_Hook_List *NEXT;

}IRQ_Hook_Node_Type;


typedef struct
{
	Machine_Desc_IRQ_Type *IRQ;

	IRQ_Hook_Node_Type **IRQ_Hook_Node_List;


}IRQ_DATA_Type;

#endif /* IRQ_STRUCT_H_ */
