/*
 * List.Timer.h
 *
 *  Created on: 2022年2月2日
 *      Author: Master.HE
 */

#ifndef LIST_TIMER_H_
#define LIST_TIMER_H_

#include "Master.Stdint.h"
#include <string.h>
#include "List.h"

#define List_Timer_Task_To_List(_P_Head,_Symbol_TimeOut)\
	{\
		if(_P_Head!=Null)\
		{\
			if(_P_Head->_Symbol_TimeOut>0)\
			{\
				_P_Head->_Symbol_TimeOut--;\
			}\
		}\
	}

#define List_Timer_Add_Node_To_List(_Name,_Node_Type,_P_Head,_P_End,_Symbol_NEXT,_Symbol_TimeOut,_P_Add_Node,_TimeOut_Type,_TimeOut)	\
	{\
		if(_TimeOut<0)\
		{\
			if(_P_End==Null)\
			{\
				_P_Head=_P_Add_Node;\
			}\
			else\
			{\
				_P_End->_Symbol_NEXT=_P_Add_Node;\
			}\
			_P_End=_P_Add_Node;\
			_P_Add_Node->_Symbol_NEXT=Null;\
			_P_Add_Node->_Symbol_TimeOut=-1;\
		}\
		else\
		{\
			_Node_Type *Temp_##_Name##_Node=Null,*Temp_##_Name##_Node_LAST=Null,*Temp_##_Name##_Node_NEXT=Null;\
			int32_t Temp_##_Name##_Time_MS_NEXT=-1;\
			Temp_##_Name##_Node=_P_Head;\
			while(Temp_##_Name##_Node!=Null)\
			{\
				if(Temp_##_Name##_Node->_Symbol_TimeOut<0)break;\
				_TimeOut=_TimeOut-Temp_##_Name##_Node->_Symbol_TimeOut;\
				if(_TimeOut<0)\
				{\
					Temp_##_Name##_Node_NEXT=Temp_##_Name##_Node;\
					_TimeOut=_TimeOut+Temp_##_Name##_Node->_Symbol_TimeOut;\
					Temp_##_Name##_Time_MS_NEXT=Temp_##_Name##_Node_NEXT->_Symbol_TimeOut-_TimeOut;\
					break;\
				}\
				else if(_TimeOut==0)\
				{\
					Temp_##_Name##_Node_LAST=Temp_##_Name##_Node;\
					Temp_##_Name##_Node_NEXT=Temp_##_Name##_Node->_Symbol_NEXT;\
					_TimeOut=0;\
					Temp_##_Name##_Time_MS_NEXT=-1;\
					break;\
				}\
				else/*Time_MS>0*/ \
				{\
					Temp_##_Name##_Node_LAST=Temp_##_Name##_Node;\
					Temp_##_Name##_Node=Temp_##_Name##_Node->_Symbol_NEXT;\
				}\
			}\
			if(Temp_##_Name##_Node_LAST==Null)/*数据在头 或者第一次*/\
			{\
				if(_P_Head==Null)/*队列为空 第一次创建*/\
				{\
					_P_Head=_P_Add_Node;\
					_P_End=_P_Add_Node;\
					_P_Add_Node->_Symbol_NEXT=Null;\
					_P_Add_Node->_Symbol_TimeOut=_TimeOut;\
				}\
				else if(_P_Head==Temp_##_Name##_Node_NEXT)/*数据在头之前*/\
				{\
					if(Temp_##_Name##_Time_MS_NEXT!=-1)\
					{\
						Temp_##_Name##_Node_NEXT->_Symbol_TimeOut=Temp_##_Name##_Time_MS_NEXT;\
					}\
					_P_Head=_P_Add_Node;\
					_P_Add_Node->_Symbol_NEXT=Temp_##_Name##_Node_NEXT;\
					_P_Add_Node->_Symbol_TimeOut=_TimeOut;\
				}\
				else/*数据在头之前 但是头是无限等待*/\
				{\
					_P_Add_Node->_Symbol_NEXT=_P_Head;\
					_P_Head=_P_Add_Node;\
					_P_Add_Node->_Symbol_TimeOut=_TimeOut;\
				}\
			}\
			else/*数据在中间或者在尾*/\
			{\
				if(Temp_##_Name##_Node_NEXT!=Null)/*数据在中间*/\
				{\
					Temp_##_Name##_Node_LAST->_Symbol_NEXT=_P_Add_Node;\
					_P_Add_Node->_Symbol_TimeOut=_TimeOut;\
					_P_Add_Node->_Symbol_NEXT=Temp_##_Name##_Node_NEXT;\
					if(Temp_##_Name##_Time_MS_NEXT!=-1)\
					{\
						Temp_##_Name##_Node_NEXT->_Symbol_TimeOut=Temp_##_Name##_Time_MS_NEXT;\
					}\
				}\
				else/*数据在尾*/\
				{\
					if(Temp_##_Name##_Node_LAST==_P_End)\
					{\
						Temp_##_Name##_Node_LAST->_Symbol_NEXT=_P_Add_Node;\
						_P_Add_Node->_Symbol_TimeOut=_TimeOut;\
						_P_Add_Node->_Symbol_NEXT=Null;\
						_P_End=_P_Add_Node;\
					}\
					else/*数据在尾之前 尾是时间无限等待*/\
					{\
						Temp_##_Name##_Node_NEXT=Temp_##_Name##_Node_LAST->_Symbol_NEXT;\
						Temp_##_Name##_Node_LAST->_Symbol_NEXT=_P_Add_Node;\
						_P_Add_Node->_Symbol_TimeOut=_TimeOut;\
						_P_Add_Node->_Symbol_NEXT=Temp_##_Name##_Node_NEXT;\
					}\
				}\
			}\
		}\
	}

#define List_Timer_Del_Node_From_Pointer(_Name,_Node_Type,_P_Head,_P_End,_Symbol_NEXT,_Symbol_TimeOut,_P_Del_Node,_bool_OK)\
	{\
		_Node_Type *Temp_##_Name##_Node=Null,*Temp_##_Name##_Node_LAST=Null,*Temp_##_Name##_Node_NEXT=Null;\
		Temp_##_Name##_Node=_P_Head;\
		_bool_OK=false;\
		while(Temp_##_Name##_Node!=Null)\
		{\
			if(Temp_##_Name##_Node==_P_Del_Node)\
			{\
				Temp_##_Name##_Node_NEXT=Temp_##_Name##_Node->_Symbol_NEXT;\
				if(Temp_##_Name##_Node_LAST==Null || Temp_##_Name##_Node==_P_Head)/*如果这个数据是头*/\
				{\
					_P_Head=_P_Head->_Symbol_NEXT;\
					if(_P_Head!=Null)/*下一个*/\
					{\
						if(_P_Head->_Symbol_TimeOut>=0)\
						{\
							if(Temp_##_Name##_Node->_Symbol_TimeOut>=0)\
							{\
								_P_Head->_Symbol_TimeOut=_P_Head->_Symbol_TimeOut+Temp_##_Name##_Node->_Symbol_TimeOut;\
							}\
						}\
					}\
				}\
				if(Temp_##_Name##_Node_NEXT==Null || Temp_##_Name##_Node==_P_End)/*如果这个数据是尾*/\
				{\
					_P_End=Temp_##_Name##_Node_LAST;\
					if(_P_End!=Null)\
					{\
						_P_End->_Symbol_NEXT=Null;\
					}\
				}\
				if(Temp_##_Name##_Node_LAST!=Null && Temp_##_Name##_Node_NEXT!=Null)/*如果头和尾都不是空 那么数据在中间*/\
				{\
					if(Temp_##_Name##_Node->_Symbol_TimeOut>=0 && Temp_##_Name##_Node_NEXT->_Symbol_TimeOut>=0)/*修补时间队列*/\
					{\
						Temp_##_Name##_Node_NEXT->_Symbol_TimeOut=Temp_##_Name##_Node_NEXT->_Symbol_TimeOut+Temp_##_Name##_Node->_Symbol_TimeOut;\
					}\
					Temp_##_Name##_Node_LAST->_Symbol_NEXT=Temp_##_Name##_Node_NEXT;\
				}\
				Temp_##_Name##_Node->_Symbol_NEXT=Null;\
				_bool_OK=true;\
				break;\
			}\
			Temp_##_Name##_Node_LAST=Temp_##_Name##_Node;\
			Temp_##_Name##_Node=Temp_##_Name##_Node->_Symbol_NEXT;\
		}\
	}

#define List_Timer_Del_Node_From_Symbol(_Name,_Node_Type,_P_Head,_P_End,_Symbol_NEXT,_Symbol_TimeOut,_Symbol,_Symbol_Data,_P_Del_Node)\
	{\
		_Node_Type *Temp_##_Name##_Node_LAST=Null,*Temp_##_Name##_Node_NEXT=Null;\
		_P_Del_Node=_P_Head;\
		while(_P_Del_Node!=Null)\
		{\
			if(_P_Del_Node->_Symbol==_Symbol_Data)\
			{\
				Temp_##_Name##_Node_NEXT=_P_Del_Node->_Symbol_NEXT;\
				if(Temp_##_Name##_Node_LAST==Null || _P_Del_Node==_P_Head)/*如果这个数据是头*/\
				{\
					_P_Head=_P_Head->_Symbol_NEXT;\
					if(_P_Head!=Null)/*下一个*/\
					{\
						if(_P_Head->_Symbol_TimeOut>=0)\
						{\
							if(_P_Del_Node->_Symbol_TimeOut>=0)\
							{\
								_P_Head->_Symbol_TimeOut=_P_Head->_Symbol_TimeOut+_P_Del_Node->_Symbol_TimeOut;\
							}\
						}\
					}\
				}\
				if(Temp_##_Name##_Node_NEXT==Null || _P_Del_Node==_P_End)/*如果这个数据是尾*/\
				{\
					_P_End=Temp_##_Name##_Node_LAST;\
					if(_P_End!=Null)\
					{\
						_P_End->_Symbol_NEXT=Null;\
					}\
				}\
				if(Temp_##_Name##_Node_LAST!=Null && Temp_##_Name##_Node_NEXT!=Null)/*如果头和尾都不是空 那么数据在中间*/\
				{\
					if(_P_Del_Node->_Symbol_TimeOut>=0 && Temp_##_Name##_Node_NEXT->_Symbol_TimeOut>=0)/*修补时间队列*/\
					{\
						Temp_##_Name##_Node_NEXT->_Symbol_TimeOut=Temp_##_Name##_Node_NEXT->_Symbol_TimeOut+_P_Del_Node->_Symbol_TimeOut;\
					}\
					Temp_##_Name##_Node_LAST->_Symbol_NEXT=Temp_##_Name##_Node_NEXT;\
				}\
				_P_Del_Node->_Symbol_NEXT=Null;\
				break;\
			}\
			Temp_##_Name##_Node_LAST=_P_Del_Node;\
			_P_Del_Node=_P_Del_Node->_Symbol_NEXT;\
		}\
	}

#define List_Timer_Del_Node_From_Strcmp(_Name,_Node_Type,_P_Head,_P_End,_Symbol_NEXT,_Symbol_TimeOut,_Symbol_Strcmp,_Strcmp_Data,_P_Del_Node)\
	{\
		_Node_Type *Temp_##_Name##_Node_LAST=Null,*Temp_##_Name##_Node_NEXT=Null;\
		_P_Del_Node=_P_Head;\
		while(_P_Del_Node!=Null)\
		{\
			if(strcmp(_P_Del_Node->_Symbol_Strcmp,_Strcmp_Data)==0)\
			{\
				Temp_##_Name##_Node_NEXT=_P_Del_Node->_Symbol_NEXT;\
				if(Temp_##_Name##_Node_LAST==Null || _P_Del_Node==_P_Head)/*如果这个数据是头*/\
				{\
					_P_Head=_P_Head->_Symbol_NEXT;\
					if(_P_Head!=Null)/*下一个*/\
					{\
						if(_P_Head->_Symbol_TimeOut>=0)\
						{\
							if(_P_Del_Node->_Symbol_TimeOut>=0)\
							{\
								_P_Head->_Symbol_TimeOut=_P_Head->_Symbol_TimeOut+_P_Del_Node->_Symbol_TimeOut;\
							}\
						}\
					}\
				}\
				if(Temp_##_Name##_Node_NEXT==Null || _P_Del_Node==_P_End)/*如果这个数据是尾*/\
				{\
					_P_End=Temp_##_Name##_Node_LAST;\
					if(_P_End!=Null)\
					{\
						_P_End->_Symbol_NEXT=Null;\
					}\
				}\
				if(Temp_##_Name##_Node_LAST!=Null && Temp_##_Name##_Node_NEXT!=Null)/*如果头和尾都不是空 那么数据在中间*/\
				{\
					if(_P_Del_Node->_Symbol_TimeOut>=0 && Temp_##_Name##_Node_NEXT->_Symbol_TimeOut>=0)/*修补时间队列*/\
					{\
						Temp_##_Name##_Node_NEXT->_Symbol_TimeOut=Temp_##_Name##_Node_NEXT->_Symbol_TimeOut+_P_Del_Node->_Symbol_TimeOut;\
					}\
					Temp_##_Name##_Node_LAST->_Symbol_NEXT=Temp_##_Name##_Node_NEXT;\
				}\
				_P_Del_Node->_Symbol_NEXT=Null;\
				break;\
			}\
			Temp_##_Name##_Node_LAST=_P_Del_Node;\
			_P_Del_Node=_P_Del_Node->_Symbol_NEXT;\
		}\
	}

#define List_Timer_Del_Node_From_Memcmp(_Name,_Node_Type,_P_Head,_P_End,_Symbol_NEXT,_Symbol_TimeOut,_Symbol_Memcmp,_Memcmp_Data,_Memcmp_Size,_P_Del_Node)\
	{\
		_Node_Type *Temp_##_Name##_Node_LAST=Null,*Temp_##_Name##_Node_NEXT=Null;\
		_P_Del_Node=_P_Head;\
		while(_P_Del_Node!=Null)\
		{\
			if(memcmp(_P_Del_Node->_Symbol_Memcmp,_Memcmp_Data,_Memcmp_Size)==0)\
			{\
				Temp_##_Name##_Node_NEXT=_P_Del_Node->_Symbol_NEXT;\
				if(Temp_##_Name##_Node_LAST==Null || _P_Del_Node==_P_Head)/*如果这个数据是头*/\
				{\
					_P_Head=_P_Head->_Symbol_NEXT;\
					if(_P_Head!=Null)/*下一个*/\
					{\
						if(_P_Head->_Symbol_TimeOut>=0)\
						{\
							if(_P_Del_Node->_Symbol_TimeOut>=0)\
							{\
								_P_Head->_Symbol_TimeOut=_P_Head->_Symbol_TimeOut+_P_Del_Node->_Symbol_TimeOut;\
							}\
						}\
					}\
				}\
				if(Temp_##_Name##_Node_NEXT==Null || _P_Del_Node==_P_End)/*如果这个数据是尾*/\
				{\
					_P_End=Temp_##_Name##_Node_LAST;\
					if(_P_End!=Null)\
					{\
						_P_End->_Symbol_NEXT=Null;\
					}\
				}\
				if(Temp_##_Name##_Node_LAST!=Null && Temp_##_Name##_Node_NEXT!=Null)/*如果头和尾都不是空 那么数据在中间*/\
				{\
					if(_P_Del_Node->_Symbol_TimeOut>=0 && Temp_##_Name##_Node_NEXT->_Symbol_TimeOut>=0)/*修补时间队列*/\
					{\
						Temp_##_Name##_Node_NEXT->_Symbol_TimeOut=Temp_##_Name##_Node_NEXT->_Symbol_TimeOut+_P_Del_Node->_Symbol_TimeOut;\
					}\
					Temp_##_Name##_Node_LAST->_Symbol_NEXT=Temp_##_Name##_Node_NEXT;\
				}\
				_P_Del_Node->_Symbol_NEXT=Null;\
				break;\
			}\
			Temp_##_Name##_Node_LAST=_P_Del_Node;\
			_P_Del_Node=_P_Del_Node->_Symbol_NEXT;\
		}\
	}

#define List_Timer_Del_Node_From_TimeOut(_P_Head,_P_End,_Symbol_NEXT,_Symbol_TimeOut,_P_Del_Node)	\
	{\
		if(_P_Head==Null)																			\
		{																							\
			_P_Del_Node=Null;																		\
		}\
		else\
		{\
			if(_P_Head->_Symbol_TimeOut==0)\
			{\
				_P_Del_Node=_P_Head;\
				_P_Head=_P_Head->_Symbol_NEXT;\
				if(_P_Head==Null)\
				{\
					_P_End=Null;\
				}\
				_P_Del_Node->_Symbol_NEXT=Null;\
			}\
		}\
	}

#define List_Timer_Find_Node_From_Symbol List_Find_Node_From_Symbol

#define List_Timer_Find_Node_From_Symbol_2And List_Find_Node_From_Symbol_2And

#define List_Timer_Find_Node_From_Strcmp List_Find_Node_From_Strcmp

#define List_Timer_Find_Node_From_Memcmp List_Find_Node_From_Memcmp

#endif /* LIST_TIMER_H_ */
