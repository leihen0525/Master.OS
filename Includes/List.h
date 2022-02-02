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
#define List_Add_Node_To_End(_P_Head,_P_End,_Symbol_NEXT,_P_Add_Node)	\
	{																	\
		_P_Add_Node->_Symbol_NEXT=Null;									\
		if(_P_End==Null)												\
		{																\
			_P_Head=_P_Add_Node;										\
		}																\
		else															\
		{																\
			_P_End->_Symbol_NEXT=_P_Add_Node;							\
		}																\
		_P_End=_P_Add_Node;												\
	}

//删除一个节点(根据节点寻找并删除)
#define List_Del_Node_From_Pointer(_Name,_Node_Type,_P_Head,_P_End,_Symbol_NEXT,_P_Del_Node,_bool_OK)		\
	{																					\
		_Node_Type *Temp_##_Name##_LAST=Null;												\
		_Node_Type *Temp_##_Name;															\
		Temp_##_Name=_P_Head;															\
		_bool_OK=false;																	\
		while(Temp_##_Name!=Null)														\
		{																				\
			if(Temp_##_Name==_P_Del_Node)												\
			{																			\
				if(Temp_##_Name##_LAST==Null)											\
				{																		\
					_P_Head=Temp_##_Name->_Symbol_NEXT;								\
				}																		\
				else																	\
				{																		\
					Temp_##_Name##_LAST->_Symbol_NEXT=Temp_##_Name->_Symbol_NEXT;	\
				}																		\
				if(Temp_##_Name==_P_End || Temp_##_Name->_Symbol_NEXT==Null)		\
				{																		\
					_P_End=Temp_##_Name##_LAST;										\
				}																		\
				Temp_##_Name->_Symbol_NEXT=Null;										\
				_bool_OK=true;															\
				break;																	\
			}																			\
			Temp_##_Name##_LAST=Temp_##_Name;										\
			Temp_##_Name=Temp_##_Name->_Symbol_NEXT;								\
		}																				\
	}

//删除一个节点(根据符号信号寻找并删除)
#define List_Del_Node_From_Symbol(_Name,_Node_Type,_P_Head,_P_End,_Symbol_NEXT,_Symbol,_Symbol_Data,_P_Del_Node)		\
	{																								\
		_Node_Type *Temp_##_Name##_LAST=Null;															\
		_P_Del_Node=_P_Head;																		\
		while(_P_Del_Node!=Null)																	\
		{																							\
			if(_P_Del_Node->_Symbol==_Symbol_Data)													\
			{																						\
				if(Temp_##_Name##_LAST==Null)														\
				{																					\
					_P_Head=_P_Del_Node->_Symbol_NEXT;												\
				}																					\
				else																				\
				{																					\
					Temp_##_Name##_LAST->_Symbol_NEXT=_P_Del_Node->_Symbol_NEXT;					\
				}																					\
				if(_P_Del_Node==_P_End || _P_Del_Node->_Symbol_NEXT==Null)							\
				{																					\
					_P_End=Temp_##_Name##_LAST;													\
				}																					\
				_P_Del_Node->_Symbol_NEXT=Null;														\
				break;																				\
			}																						\
			Temp_##_Name##_LAST=_P_Del_Node;														\
			_P_Del_Node=_P_Del_Node->_Symbol_NEXT;													\
		}																							\
	}

#define List_Del_Node_From_Strcmp(_Name,_Node_Type,_P_Head,_P_End,_Symbol_NEXT,_Symbol_Strcmp,_Strcmp_Data,_P_Del_Node)		\
	{																								\
		_Node_Type *Temp_##_Name##_LAST=Null;															\
		_P_Del_Node=_P_Head;																		\
		while(_P_Del_Node!=Null)																	\
		{																							\
			if(strcmp(_P_Del_Node->_Symbol_Strcmp,_Strcmp_Data)==0)													\
			{																						\
				if(Temp_##_Name##_LAST==Null)														\
				{																					\
					_P_Head=_P_Del_Node->_Symbol_NEXT;												\
				}																					\
				else																				\
				{																					\
					Temp_##_Name##_LAST->_Symbol_NEXT=_P_Del_Node->_Symbol_NEXT;					\
				}																					\
				if(_P_Del_Node==_P_End || _P_Del_Node->_Symbol_NEXT==Null)							\
				{																					\
					_P_End=Temp_##_Name##_LAST;													\
				}																					\
				_P_Del_Node->_Symbol_NEXT=Null;														\
				break;																				\
			}																						\
			Temp_##_Name##_LAST=_P_Del_Node;														\
			_P_Del_Node=_P_Del_Node->_Symbol_NEXT;													\
		}																							\
	}

#define List_Del_Node_From_Memcmp(_Name,_Node_Type,_P_Head,_P_End,_Symbol_NEXT,_Symbol_Memcmp,_Memcmp_Data,_Memcmp_Size,_P_Del_Node)		\
	{																								\
		_Node_Type *Temp_##_Name##_LAST=Null;														\
		_P_Del_Node=_P_Head;																		\
		while(_P_Del_Node!=Null)																	\
		{																							\
			if(memcmp(_P_Del_Node->_Symbol_Memcmp,_Memcmp_Data,_Memcmp_Size)==0)							\
			{																						\
				if(Temp_##_Name##_LAST==Null)														\
				{																					\
					_P_Head=_P_Del_Node->_Symbol_NEXT;												\
				}																					\
				else																				\
				{																					\
					Temp_##_Name##_LAST->_Symbol_NEXT=_P_Del_Node->_Symbol_NEXT;					\
				}																					\
				if(_P_Del_Node==_P_End || _P_Del_Node->_Symbol_NEXT==Null)							\
				{																					\
					_P_End=Temp_##_Name##_LAST;													\
				}																					\
				_P_Del_Node->_Symbol_NEXT=Null;														\
				break;																				\
			}																						\
			Temp_##_Name##_LAST=_P_Del_Node;														\
			_P_Del_Node=_P_Del_Node->_Symbol_NEXT;													\
		}																							\
	}

//删除第一个节点
#define List_Del_Node_From_First(_P_Head,_P_End,_Symbol_NEXT,_P_Del_Node)							\
	{																								\
		if(_P_Head==Null)																			\
		{																							\
			_P_Del_Node=Null;																		\
		}																							\
		else																						\
		{																							\
			_P_Del_Node=_P_Head;																	\
			_P_Head=_P_Head->_Symbol_NEXT;															\
			if(_P_Head==Null)																		\
			{																						\
				_P_End=Null;																		\
			}																						\
		}																							\
	}



//寻找一个节点（根据1个条件符号信号寻找）
#define List_Find_Node_From_Symbol(_P_Head,_Symbol_NEXT,_Symbol,_Symbol_Data,_P_Find_Node)			\
	{																								\
		_P_Find_Node=_P_Head;																		\
		while(_P_Find_Node!=Null)																	\
		{																							\
			if(_P_Find_Node->_Symbol==_Symbol_Data)													\
			{																						\
				break;																				\
			}																						\
			_P_Find_Node=_P_Find_Node->_Symbol_NEXT;												\
		}																							\
	}
//寻找一个节点（根据2个条件符号信号寻找）
#define List_Find_Node_From_Symbol_2And(_P_Head,_Symbol_NEXT,_Symbol_1,_Symbol_Data_1,_Symbol_2,_Symbol_Data_2,_P_Find_Node)	\
	{																													\
		_P_Find_Node=_P_Head;																							\
		while(_P_Find_Node!=Null)																						\
		{																												\
			if(_P_Find_Node->_Symbol_1==_Symbol_Data_1)																	\
			{																											\
				if(_P_Find_Node->_Symbol_2==_Symbol_Data_2)																\
				{																										\
					break;																								\
				}																										\
			}																											\
			_P_Find_Node=_P_Find_Node->_Symbol_NEXT;																	\
		}																												\
	}

//寻找一个节点（根据字符串名字寻找）
#define List_Find_Node_From_Strcmp(_P_Head,_Symbol_NEXT,_Symbol_Strcmp,_Strcmp_Data,_P_Find_Node)		\
	{																								\
		_P_Find_Node=_P_Head;																		\
		while(_P_Find_Node!=Null)																	\
		{																							\
			if(strcmp(_P_Find_Node->_Symbol_Strcmp,_Strcmp_Data)==0)									\
			{																						\
				break;																				\
			}																						\
			_P_Find_Node=_P_Find_Node->_Symbol_NEXT;												\
		}																							\
	}

#define List_Find_Node_From_Memcmp(_P_Head,_Symbol_NEXT,_Symbol_Memcmp,_Memcmp_Data,_Memcmp_Size,_P_Find_Node)		\
	{																								\
		_P_Find_Node=_P_Head;																		\
		while(_P_Find_Node!=Null)																	\
		{																							\
			if(memcmp(_P_Find_Node->_Symbol_Memcmp,_Memcmp_Data,_Memcmp_Size)==0)					\
			{																						\
				break;																				\
			}																						\
			_P_Find_Node=_P_Find_Node->_Symbol_NEXT;												\
		}																							\
	}

#endif /* LIST_H_ */
