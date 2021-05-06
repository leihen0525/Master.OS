/*
 * Ring.Queue.h
 *
 *  Created on: 2021年4月21日
 *      Author: Master.HE
 */

#ifndef RING_QUEUE_H_
#define RING_QUEUE_H_


#include "Error.h"
#include "Master.Stdint.h"

#define Ring_Queue_Struct_Declare(_Struct_Name,_Queue_Data_Type)							\
	typedef struct																			\
	{																						\
		unsigned int IN;																	\
		unsigned int OUT;																	\
		unsigned int Count;																\
		_Queue_Data_Type *DATA;																\
	}Master_Ring_Queue_##_Struct_Name##_Type;

#define Ring_Queue_Struct_Define(_Struct_Name,_Variable_Name)								\
		Master_Ring_Queue_##_Struct_Name##_Type _Variable_Name


#define Ring_Queue_Init(Err,_Variable_Name,_Queue_Data_Type,_Queue_Length)					\
	{																						\
		Err=Error_OK;																		\
		_Variable_Name.IN=0;																\
		_Variable_Name.OUT=0;																\
		_Variable_Name.Count=_Queue_Length;													\
		_Variable_Name.DATA=Memory_Malloc(sizeof(_Queue_Data_Type)*_Queue_Length);			\
		if(_Variable_Name.DATA==Null)														\
		{																					\
			Err=Error_Allocation_Memory_Failed;												\
		}																					\
	}
#define Ring_Queue_DeInit(_Variable_Name)													\
	{																						\
		Memory_Free(_Variable_Name.DATA);													\
		_Variable_Name.DATA=Null;															\
		_Variable_Name.IN=0;																\
		_Variable_Name.OUT=0;																\
		_Variable_Name.Count=0;																\
	}

#define Ring_Queue_IN(Err,_Variable_Name,_Queue_Data_Type,_Queue_Data_IN,_Data_OverFlow)				\
	{																									\
		Err=Error_OK;																					\
		memcpy(&_Variable_Name.DATA[_Variable_Name.IN],&_Queue_Data_IN,sizeof(_Queue_Data_Type));		\
		_Variable_Name.IN=(_Variable_Name.IN+1)%_Variable_Name.Count;									\
		if(_Variable_Name.IN==_Variable_Name.OUT)							\
		{																								\
			Err=Error_OverFlow;																			\
			memcpy(&_Data_OverFlow,&_Variable_Name.DATA[_Variable_Name.OUT],sizeof(_Queue_Data_Type));	\
			_Variable_Name.OUT=(_Variable_Name.OUT+1)%_Variable_Name.Count;								\
		}																								\
	}

#define Ring_Queue_OUT(Err,_Variable_Name,_Queue_Data_Type,_Queue_Data_OUT,_Next_Empty)					\
	{																									\
		if(_Variable_Name.IN==_Variable_Name.OUT)														\
		{																								\
			Err=Error_Empty;																			\
			_Next_Empty=true;																			\
		}																								\
		else																							\
		{																								\
			memcpy(&_Queue_Data_OUT,&_Variable_Name.DATA[_Variable_Name.OUT],sizeof(_Queue_Data_Type));	\
			_Variable_Name.OUT=(_Variable_Name.OUT+1)%_Variable_Name.Count;								\
			Err=Error_OK;																				\
			if(_Variable_Name.IN==_Variable_Name.OUT)													\
			{																							\
				_Next_Empty=true;																		\
			}																							\
			else																						\
			{																							\
				_Next_Empty=false;																		\
			}																							\
		}																								\
	}

#define Ring_Queue_OUT_1(Err,_Variable_Name,_Queue_Data_Type,_P_Queue_Data_OUT)							\
	{																									\
		if(_Variable_Name.IN==_Variable_Name.OUT)														\
		{																								\
			Err=Error_Empty;																			\
		}																								\
		else																							\
		{																								\
			_P_Queue_Data_OUT=&_Variable_Name.DATA[_Variable_Name.OUT];									\
			Err=Error_OK;																				\
		}																								\
	}

#define Ring_Queue_OUT_2(_Variable_Name,_Next_Empty)													\
	{																									\
		_Variable_Name.OUT=(_Variable_Name.OUT+1)%_Variable_Name.Count;									\
		if(_Variable_Name.IN==_Variable_Name.OUT)														\
		{																								\
			_Next_Empty=true;																			\
		}																								\
		else																							\
		{																								\
			_Next_Empty=false;																			\
		}																								\
	}

#endif /* RING_QUEUE_H_ */
