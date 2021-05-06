/*
 * List.h
 *
 *  Created on: 2021年3月16日
 *      Author: Master.HE
 */

#ifndef LIST_H_
#define LIST_H_


#include "Master.Stdint.h"
#include <string.h>

//插入一个节点到链表尾端
#define List_Add_Node_To_End(_P_Head,_P_End,_NEXT,_P_Add_Node)			\
	{																	\
		_P_Add_Node->_NEXT=Null;										\
		if(_P_End==Null)												\
		{																\
			_P_Head=_P_Add_Node;										\
		}																\
		else															\
		{																\
			_P_End->_NEXT=_P_Add_Node;									\
		}																\
		_P_End=_P_Add_Node;												\
	}

//删除一个节点(根据节点寻找并删除)
#define List_Del_Node_From_Pointer(_P_Node,_Type,_P_Head,_P_End,_NEXT,_P_Del_Node,_bool_OK)		\
	{																					\
		_Type *Temp_##_P_Node##_LAST=Null;												\
		_Type *Temp_##_P_Node;															\
		Temp_##_P_Node=_P_Head;															\
		_bool_OK=false;																	\
		while(Temp_##_P_Node!=Null)														\
		{																				\
			if(Temp_##_P_Node==_P_Del_Node)												\
			{																			\
				if(Temp_##_P_Node##_LAST==Null)											\
				{																		\
					_P_Head=Temp_##_P_Node->_NEXT;										\
				}																		\
				else																	\
				{																		\
					Temp_##_P_Node##_LAST->_NEXT=Temp_##_P_Node->_NEXT;					\
				}																		\
				if(Temp_##_P_Node==_P_End || Temp_##_P_Node->_NEXT==Null)				\
				{																		\
					_P_End=Temp_##_P_Node##_LAST;										\
				}																		\
				Temp_##_P_Node->_NEXT=Null;												\
				_bool_OK=true;															\
				break;																	\
			}																			\
			Temp_##_P_Node##_LAST=Temp_##_P_Node;										\
			Temp_##_P_Node=Temp_##_P_Node->_NEXT;										\
		}																				\
	}

//删除一个节点(根据符号信号寻找并删除)
#define List_Del_Node_From_Symbol(_P_Node,_Type,_P_Head,_P_End,_NEXT,_Symbol,_Symbol_Data,_P_Del_Node)		\
	{																								\
		_Type *Temp_##_P_Node##_LAST=Null;															\
		_P_Del_Node=_P_Head;																		\
		while(_P_Del_Node!=Null)																	\
		{																							\
			if(_P_Del_Node->_Symbol==_Symbol_Data)													\
			{																						\
				if(Temp_##_P_Node##_LAST==Null)														\
				{																					\
					_P_Head=_P_Del_Node->_NEXT;														\
				}																					\
				else																				\
				{																					\
					Temp_##_P_Node##_LAST->_NEXT=_P_Del_Node->_NEXT;								\
				}																					\
				if(_P_Del_Node==_P_End || _P_Del_Node->_NEXT==Null)									\
				{																					\
					_P_End=Temp_##_P_Node##_LAST;													\
				}																					\
				_P_Del_Node->_NEXT=Null;															\
				break;																				\
			}																						\
			Temp_##_P_Node##_LAST=_P_Del_Node;														\
			_P_Del_Node=_P_Del_Node->_NEXT;															\
		}																							\
	}

//寻找一个节点（根据符号信号寻找）
#define List_Find_Node_From_Symbol(_P_Head,_NEXT,_Symbol,_Symbol_Data,_P_Find_Node)					\
	{																								\
		_P_Find_Node=_P_Head;																		\
		while(_P_Find_Node!=Null)																	\
		{																							\
			if(_P_Find_Node->_Symbol==_Symbol_Data)													\
			{																						\
				break;																				\
			}																						\
			_P_Find_Node=_P_Find_Node->_NEXT;														\
		}																							\
	}

#define List_Find_Node_From_Symbol_2And(_P_Head,_NEXT,_Symbol_1,_Symbol_Data_1,_Symbol_2,_Symbol_Data_2,_P_Find_Node)	\
	{																													\
		_P_Find_Node=_P_Head;																							\
		while(_P_Find_Node!=Null)																						\
		{																												\
			if(_P_Find_Node->_Symbol_1==_Symbol_Data_1 && _P_Find_Node->_Symbol_2==_Symbol_Data_2)						\
			{																											\
				break;																									\
			}																											\
			_P_Find_Node=_P_Find_Node->_NEXT;																			\
		}																												\
	}

//寻找一个节点（根据字符串名字寻找）
#define List_Find_Node_From_CharName(_P_Head,_NEXT,_CharName,_CharName_Data,_P_Find_Node)			\
	{																								\
		_P_Find_Node=_P_Head;																		\
		while(_P_Find_Node!=Null)																	\
		{																							\
			if(strcmp(_P_Find_Node->_CharName,_CharName_Data)==0)									\
			{																						\
				break;																				\
			}																						\
			_P_Find_Node=_P_Find_Node->_NEXT;														\
		}																							\
	}


#endif /* LIST_H_ */
