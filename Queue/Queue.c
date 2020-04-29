/*
 * Queue.c
 *
 *  Created on: 2019年4月23日
 *      Author: Master.HE
 */
#include "Define.h"

#include "Error.h"

#include "Queue.h"

Queue_DATA_Type Queue_DATA;

int Queue_Init(void)//初始化队列
{

	Queue_DATA.TCB_Queue.Begin=Null;
	Queue_DATA.TCB_Queue.End=Null;

	Queue_DATA.Ready_Queue.Begin=Null;
	Queue_DATA.Ready_Queue.End=Null;


	Queue_DATA.Suspended_Queue.Begin=Null;
	Queue_DATA.Suspended_Queue.End=Null;

	return Error_OK;
}
int Queue_Read_TCB_Queue(Task_Queue_Type **TCB_Queue)
{
	if(TCB_Queue==Null)
	{
		return Error_Invalid_Parameter;
	}
	*TCB_Queue=&Queue_DATA.TCB_Queue;
	return Error_OK;
}
int Queue_TCB_Add_TCB_Queue(__Sys_Scheduling_Task_TCB_Type *Add_TCB)
{
	if(Add_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}

	if(Queue_DATA.TCB_Queue.End==Null)
	{
		Queue_DATA.TCB_Queue.Begin=Add_TCB;
	}
	else
	{
		Queue_DATA.TCB_Queue.End->Queue.TCB_NEXT=Add_TCB;
	}
	Queue_DATA.TCB_Queue.End=Add_TCB;
	Add_TCB->Queue.TCB_NEXT=Null;

	return Error_OK;
}
int Queue_TCB_Delete_TCB_Queue(
		__Sys_Scheduling_Task_TCB_Type **Delete_TCB,
		int Handle)
{

	__Sys_Scheduling_Task_TCB_Type *Temp_TCB_LAST=Null,*Temp_TCB;


	Temp_TCB=Queue_DATA.TCB_Queue.Begin;
	while(Temp_TCB!=Null)
	{
		if(Delete_TCB==Null)
		{
			if(Temp_TCB->Info.Handle!=Handle)
			{
				goto Loop_End;
			}
		}
		else
		{
			if(*Delete_TCB==Null)
			{
				if(Temp_TCB->Info.Handle!=Handle)
				{
					goto Loop_End;
				}
			}
			else
			{
				if(*Delete_TCB!=Temp_TCB)
				{
					goto Loop_End;
				}
			}

		}

		//调整链表
		if(Temp_TCB_LAST==Null)
		{
			Queue_DATA.TCB_Queue.Begin=Temp_TCB->Queue.TCB_NEXT;
		}
		else
		{
			Temp_TCB_LAST->Queue.TCB_NEXT=Temp_TCB->Queue.TCB_NEXT;
		}

		if(Temp_TCB==Queue_DATA.TCB_Queue.End || Temp_TCB->Queue.TCB_NEXT==Null)
		{
			Queue_DATA.TCB_Queue.End=Temp_TCB_LAST;
		}

		Temp_TCB->Queue.TCB_NEXT=Null;

		if(Delete_TCB!=Null)
		{
			*Delete_TCB=Temp_TCB;
		}
		return Error_OK;

Loop_End:
		Temp_TCB_LAST=Temp_TCB;
		Temp_TCB=Temp_TCB->Queue.TCB_NEXT;
	}

	return Error_Invalid_Handle;
}
int Queue_Find_TCB_Queue(
		__Sys_Scheduling_Task_TCB_Type **Find_TCB,
		int Handle)
{

	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null;


	Temp_TCB=Queue_DATA.TCB_Queue.Begin;

	while(Temp_TCB!=Null)
	{

		if(Find_TCB==Null)
		{
			if(Temp_TCB->Info.Handle!=Handle)
			{
				goto Loop_End;
			}
		}
		else
		{
			if(*Find_TCB==Null)
			{
				if(Temp_TCB->Info.Handle!=Handle)
				{
					goto Loop_End;
				}
			}
			else
			{
				if(*Find_TCB!=Temp_TCB)
				{
					goto Loop_End;
				}
			}

		}
		if(Find_TCB!=Null)
		{
			*Find_TCB=Temp_TCB;
		}
		return Error_OK;
Loop_End:
		Temp_TCB=Temp_TCB->Queue.TCB_NEXT;
	}

	return Error_Invalid_Handle;
}

//添加到准备运行队列的 专用函数
//必要说明一下 实现过程 将任务按照从大到小的优先级排列方式放入准备运行队列 优先级相同的队列 按照FIFO方式摆放
int Queue_TCB_Add_Ready_Queue(__Sys_Scheduling_Task_TCB_Type *Add_TCB)//这个地方有个开关 存放完成后是否立即进行调度
{
	__Sys_Scheduling_Task_TCB_Type *Temp_TCB;//,*LSAT_TCB,*NEXT_TCB;

	if(Add_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}

	Add_TCB->Info.Task_State=Task_State_Ready;
	Add_TCB->Queue.Event_NEXT=Null;
	Add_TCB->Event.Event_Queue=Null;

	if(Queue_DATA.Ready_Queue.Begin==Null || Queue_DATA.Ready_Queue.End==Null)//第一次加
	{
		Queue_DATA.Ready_Queue.Begin=Add_TCB;
		Queue_DATA.Ready_Queue.End=Add_TCB;

		Add_TCB->Queue.Queue_NEXT=Null;
	}
	else
	{
		if(Add_TCB->Priority.Current<Queue_DATA.Ready_Queue.Begin->Priority.Current)//优先级比头大 加入头
		{

			Add_TCB->Queue.Queue_NEXT=Queue_DATA.Ready_Queue.Begin;

			Queue_DATA.Ready_Queue.Begin=Add_TCB;
		}
		else if(Queue_DATA.Ready_Queue.End->Priority.Current<=Add_TCB->Priority.Current)//加入的优先级比尾小（或者等于尾） 加入末尾
		{
			Queue_DATA.Ready_Queue.End->Queue.Queue_NEXT=Add_TCB;

			Add_TCB->Queue.Queue_NEXT=Null;

			Queue_DATA.Ready_Queue.End=Add_TCB;
		}
		else //优先级在中间
		{
			Temp_TCB=Queue_DATA.Ready_Queue.Begin;
			while(Temp_TCB!=Null)
			{
				if(Temp_TCB->Priority.Current<=Add_TCB->Priority.Current)//插入的任务优先级比Temp_TCB小（或者等于）
				{
					if(Temp_TCB->Queue.Queue_NEXT!=Null)//Temp_TCB下一个还有节点
					{
						if(Add_TCB->Priority.Current<Temp_TCB->Queue.Queue_NEXT->Priority.Current)//当前任务比Temp_TCB下一个节点的优先级小
						{
//							LSAT_TCB=Temp_TCB;
//
//							NEXT_TCB=Temp_TCB->Queue.Queue_NEXT;
//
//							LSAT_TCB->Queue.Queue_NEXT=Add_TCB;
//
//							Add_TCB->Queue.Queue_NEXT=NEXT_TCB;

							Add_TCB->Queue.Queue_NEXT=Temp_TCB->Queue.Queue_NEXT;
							Temp_TCB->Queue.Queue_NEXT=Add_TCB;

							break;
						}
						else
						{
							Temp_TCB=Temp_TCB->Queue.Queue_NEXT;
						}
					}
					else//如果找到数据在尾端
					{
						Queue_DATA.Ready_Queue.End->Queue.Queue_NEXT=Add_TCB;

						Add_TCB->Queue.Queue_NEXT=Null;

						Queue_DATA.Ready_Queue.End=Add_TCB;

						break;
					}

				}
				else//插入的任务优先级比Temp_TCB大
				{

					Add_TCB->Queue.Queue_NEXT=Queue_DATA.Ready_Queue.Begin;

					Queue_DATA.Ready_Queue.Begin=Add_TCB;

					break;
				}


			}
		}


	}

	return Error_OK;

}
//添加一个TCB到Suspended_Queue队列中
//特别说明 队列按照差分时间链方式排列
//没有倒计时的任务（TimeOut==-1） 一律放到队列末尾
int Queue_TCB_Add_Suspended_Queue(
		__Sys_Scheduling_Task_TCB_Type *Add_TCB,
		Task_State_Type Add_TCB_Task_State,
		int32_t TimeOut)
{

	int32_t Temp_TimeOut_NEXT=-1;


	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null,*Temp_TCB_LAST=Null,*Temp_TCB_NEXT=Null;

	if(Add_TCB==Null
	|| Add_TCB_Task_State>=Task_State_End
	|| TimeOut<-1)
	{
		return Error_Invalid_Parameter;
	}

	Add_TCB->Info.Task_State=Add_TCB_Task_State;

	if(TimeOut<0)
	{
		if(Queue_DATA.Suspended_Queue.End==Null)
		{
			Queue_DATA.Suspended_Queue.Begin=Add_TCB;

		}
		else
		{
			Queue_DATA.Suspended_Queue.End->Queue.Queue_NEXT=Add_TCB;

		}
		Queue_DATA.Suspended_Queue.End=Add_TCB;
		Add_TCB->Queue.Queue_NEXT=Null;
		Add_TCB->Info.TimeOut=-1;

		return Error_OK;
	}


	Temp_TCB=Queue_DATA.Suspended_Queue.Begin;

	//计算插入的任务在差分时间链的位置
	while(Temp_TCB!=Null)
	{
		if(Temp_TCB->Info.TimeOut<0)break;//Temp_TCB为不需要倒计时任务 跳出

		TimeOut=TimeOut-Temp_TCB->Info.TimeOut;//做差值

		if(TimeOut<0)//要插入的任务在当前Temp_TCB任务之前
		{

			Temp_TCB_NEXT=Temp_TCB;


			TimeOut=TimeOut+Temp_TCB_NEXT->Info.TimeOut;//还原刚刚被做差值的结果

			Temp_TimeOut_NEXT=Temp_TCB_NEXT->Info.TimeOut-TimeOut;//重新计算Temp_TCB的差分时间

			break;

		}
		else if(TimeOut==0)//要插入的任务和当前任务时间一致 那么不用重新计算差分时间 直接插入到Temp_TCB任务后面
		{
			Temp_TCB_LAST=Temp_TCB;

			Temp_TCB_NEXT=Temp_TCB->Queue.Queue_NEXT;

			TimeOut=0;

			Temp_TimeOut_NEXT=-1;

			break;
		}
		else//Temp_TimeOut>0 //Temp_TCB节点不符合 继续查找下一个
		{
			Temp_TCB_LAST=Temp_TCB;

			Temp_TCB=Temp_TCB->Queue.Queue_NEXT;
		}

	}

	//数据在头 或者第一次
	if(Temp_TCB_LAST==Null)
	{
		//队列为空 第一次创建
		if(Queue_DATA.Suspended_Queue.Begin==Null)
		{
			Queue_DATA.Suspended_Queue.Begin=Add_TCB;
			Add_TCB->Queue.Queue_NEXT=Null;

			Queue_DATA.Suspended_Queue.End=Add_TCB;

			Add_TCB->Info.TimeOut=TimeOut;

		}
		else if(Queue_DATA.Suspended_Queue.Begin==Temp_TCB_NEXT)//数据在头之前
		{

			if(Temp_TimeOut_NEXT!=-1)
			{
				Temp_TCB_NEXT->Info.TimeOut=Temp_TimeOut_NEXT;
			}

			Queue_DATA.Suspended_Queue.Begin=Add_TCB;


			Add_TCB->Queue.Queue_NEXT=Temp_TCB_NEXT;
			Add_TCB->Info.TimeOut=TimeOut;

		}
		else	//数据在头之前 但是头是无限等待
		{

			Add_TCB->Queue.Queue_NEXT=Queue_DATA.Suspended_Queue.Begin;

			Queue_DATA.Suspended_Queue.Begin=Add_TCB;

			Add_TCB->Info.TimeOut=TimeOut;
		}

	}
	else //数据在中间或者在尾
	{
		//数据在中间
		if(Temp_TCB_NEXT!=Null)
		{
			Temp_TCB_LAST->Queue.Queue_NEXT=Add_TCB;


			Add_TCB->Info.TimeOut=TimeOut;

			Add_TCB->Queue.Queue_NEXT=Temp_TCB_NEXT;



			if(Temp_TimeOut_NEXT!=-1)
			{
				Temp_TCB_NEXT->Info.TimeOut=Temp_TimeOut_NEXT;
			}
		}
		else//数据在尾
		{
			if(Temp_TCB_LAST==Queue_DATA.Suspended_Queue.End)
			{
				Temp_TCB_LAST->Queue.Queue_NEXT=Add_TCB;


				Add_TCB->Info.TimeOut=TimeOut;

				Add_TCB->Queue.Queue_NEXT=Null;

				Queue_DATA.Suspended_Queue.End=Add_TCB;

			}
			else	//数据在尾之前 尾是时间无限等待
			{
				Temp_TCB_NEXT=Temp_TCB_LAST->Queue.Queue_NEXT;

				//
				Temp_TCB_LAST->Queue.Queue_NEXT=Add_TCB;



				Add_TCB->Info.TimeOut=TimeOut;

				Add_TCB->Queue.Queue_NEXT=Temp_TCB_NEXT;



			}
		}
	}
	return Error_OK;
}
//将一个任务从Suspended_Queue队列删除
int Queue_TCB_Delete_Suspended_Queue(__Sys_Scheduling_Task_TCB_Type *Delete_TCB)
{
	if(Delete_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}

	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null,*Temp_TCB_LAST=Null,*Temp_TCB_NEXT=Null;

	Temp_TCB=Queue_DATA.Suspended_Queue.Begin;


	while(Temp_TCB!=Null)
	{
		if(Temp_TCB==Delete_TCB)//查找到
		{
			Temp_TCB_NEXT=Temp_TCB->Queue.Queue_NEXT;

			//如果这个数据是头
			if(Temp_TCB_LAST==Null || Delete_TCB==Queue_DATA.Suspended_Queue.Begin)
			{
				Queue_DATA.Suspended_Queue.Begin=Queue_DATA.Suspended_Queue.Begin->Queue.Queue_NEXT;

				if(Queue_DATA.Suspended_Queue.Begin!=Null)//下一个还有
				{
					//修补时间队列
					if(Queue_DATA.Suspended_Queue.Begin->Info.TimeOut>=0)
					{
						if(Delete_TCB->Info.TimeOut>=0)
						{
							Queue_DATA.Suspended_Queue.Begin->Info.TimeOut=Queue_DATA.Suspended_Queue.Begin->Info.TimeOut+Delete_TCB->Info.TimeOut;
						}
					}
					else
					{

					}

				}
			}
			//如果这个数据是尾
			if(Temp_TCB_NEXT==Null || Delete_TCB==Queue_DATA.Suspended_Queue.End)
			{
				Queue_DATA.Suspended_Queue.End=Temp_TCB_LAST;

				if(Queue_DATA.Suspended_Queue.End!=Null)
				{
					Queue_DATA.Suspended_Queue.End->Queue.Queue_NEXT=Null;
				}
			}

			//如果头和尾都不是空 那么数据在中间
			if(Temp_TCB_LAST!=Null && Temp_TCB_NEXT!=Null)
			{
				//修补时间队列
				if(Delete_TCB->Info.TimeOut>=0
				&& Temp_TCB_NEXT->Info.TimeOut>=0)
				{
					Temp_TCB_NEXT->Info.TimeOut=Temp_TCB_NEXT->Info.TimeOut+Delete_TCB->Info.TimeOut;
				}

				Temp_TCB_LAST->Queue.Queue_NEXT=Temp_TCB_NEXT;

			}

			Delete_TCB->Queue.Queue_NEXT=Null;

			Delete_TCB->Info.TimeOut=-1;

			return Error_OK;
		}
		else
		{
			Temp_TCB_LAST=Temp_TCB;
			Temp_TCB=Temp_TCB->Queue.Queue_NEXT;
		}

	}


	return Error_Invalid_Parameter;
}
int Queue_TimeOut_1MS_AT_Suspended_Queue(__Sys_Scheduling_Task_TCB_Type **TimeOut_TCB)
{
	if(TimeOut_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(Queue_DATA.Suspended_Queue.Begin==Null)
	{
		return Error_Operation_Failed;
	}
	;

	if(Queue_DATA.Suspended_Queue.Begin->Info.TimeOut<0)
	{
		return Error_Operation_Failed;
	}
	else
	{
		if(Queue_DATA.Suspended_Queue.Begin->Info.TimeOut>0)
		{
			Queue_DATA.Suspended_Queue.Begin->Info.TimeOut--;
		}
		if(Queue_DATA.Suspended_Queue.Begin->Info.TimeOut==0)
		{
			*TimeOut_TCB=Queue_DATA.Suspended_Queue.Begin;
			Queue_DATA.Suspended_Queue.Begin=Queue_DATA.Suspended_Queue.Begin->Queue.Queue_NEXT;
			if(Queue_DATA.Suspended_Queue.Begin==Null)
			{
				Queue_DATA.Suspended_Queue.End=Null;
			}
			return Error_OK;
		}
		else
		{
			return Error_Operation_Failed;
		}

	}
}
int Queue_Read_Ready_Queue_First_TCB(__Sys_Scheduling_Task_TCB_Type **First_Ready_TCB)
{
	if(First_Ready_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(Queue_DATA.Ready_Queue.Begin==Null)
	{
		return Error_Operation_Failed;
	}
	*First_Ready_TCB=Queue_DATA.Ready_Queue.Begin;

	return Error_OK;
}
int Queue_Delete_Ready_Queue_First_TCB(__Sys_Scheduling_Task_TCB_Type **Delet_First_Ready_TCB)
{
	if(Delet_First_Ready_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(Queue_DATA.Ready_Queue.Begin==Null)
	{
		return Error_Operation_Failed;
	}
	if(*Delet_First_Ready_TCB==Null)
	{
		*Delet_First_Ready_TCB=Queue_DATA.Ready_Queue.Begin;
	}
	else if(*Delet_First_Ready_TCB!=Queue_DATA.Ready_Queue.Begin)
	{
		return Error_Invalid_Parameter;
	}
	Queue_DATA.Ready_Queue.Begin=Queue_DATA.Ready_Queue.Begin->Queue.Queue_NEXT;
	if(Queue_DATA.Ready_Queue.Begin==Null)
	{
		Queue_DATA.Ready_Queue.End=Null;
	}
	return Error_OK;

}
//-------------------------------------------------------
int Queue_Event_Node_Init(Task_Queue_Type *Event_Node_Queue)
{
	if(Event_Node_Queue==Null)
	{
		return Error_Invalid_Parameter;
	}
	Event_Node_Queue->Begin=Null;
	Event_Node_Queue->End=Null;
	return Error_OK;
}

int Queue_TCB_Add_Event_Node_Queue(
		Task_Queue_Type *Event_Node_Queue,
		__Sys_Scheduling_Task_TCB_Type *Add_TCB,
		Event_Queue_Option_Type Queue_Option)
{
	if(Event_Node_Queue==Null || Add_TCB==Null || Queue_Option>=Event_Queue_Option_End)
	{
		return Error_Invalid_Parameter;
	}
	if(Queue_Option==Event_Queue_Option_FIFO)
	{
		if(Event_Node_Queue->End==Null)
		{
			Event_Node_Queue->Begin=Add_TCB;
		}
		else
		{
			Event_Node_Queue->End->Queue.Event_NEXT=Add_TCB;
		}
		Event_Node_Queue->End=Add_TCB;
		Add_TCB->Queue.Event_NEXT=Null;
		Add_TCB->Event.Event_Queue=Event_Node_Queue;
		return Error_OK;
	}
	else
	{
		__Sys_Scheduling_Task_TCB_Type *Temp_TCB,*LSAT_TCB,*NEXT_TCB;

		if(Event_Node_Queue->Begin==Null || Event_Node_Queue->End==Null)//第一次加
		{
			Event_Node_Queue->Begin=Add_TCB;
			Event_Node_Queue->End=Add_TCB;

			Add_TCB->Queue.Event_NEXT=Null;
		}
		else
		{
			if(Add_TCB->Priority.Current<Event_Node_Queue->Begin->Priority.Current)//优先级比头大 加入头
			{

				Add_TCB->Queue.Event_NEXT=Event_Node_Queue->Begin;

				Event_Node_Queue->Begin=Add_TCB;
			}
			else if(Event_Node_Queue->End->Priority.Current<=Add_TCB->Priority.Current)//加入的优先级比较小（或者等于尾） 加入末尾
			{
				Event_Node_Queue->End->Queue.Event_NEXT=Add_TCB;


				Add_TCB->Queue.Event_NEXT=Null;

				Event_Node_Queue->End=Add_TCB;
			}
			else //优先级在中间
			{
				Temp_TCB=Event_Node_Queue->Begin;
				while(Temp_TCB!=Null)
				{
					if(Temp_TCB->Priority.Current<=Add_TCB->Priority.Current)
					{
						if(Temp_TCB->Queue.Event_NEXT!=Null)
						{
							if(Add_TCB->Priority.Current<Temp_TCB->Queue.Event_NEXT->Priority.Current)
							{
								LSAT_TCB=Temp_TCB;

								NEXT_TCB=Temp_TCB->Queue.Event_NEXT;

								LSAT_TCB->Queue.Event_NEXT=Add_TCB;

								Add_TCB->Queue.Event_NEXT=NEXT_TCB;

								break;
							}
							else
							{
								Temp_TCB=Temp_TCB->Queue.Event_NEXT;
							}
						}
						else//如果找到数据在尾端
						{
							Event_Node_Queue->End->Queue.Event_NEXT=Add_TCB;


							Add_TCB->Queue.Event_NEXT=Null;

							Event_Node_Queue->End=Add_TCB;

							break;
						}

					}
					else
					{

						Add_TCB->Queue.Event_NEXT=Event_Node_Queue->Begin;

						Event_Node_Queue->Begin=Add_TCB;

						break;
					}


				}
			}


		}
		Add_TCB->Event.Event_Queue=Event_Node_Queue;
		return Error_OK;
	}


}
int Queue_Read_Event_Node_Queue_First_TCB(
		Task_Queue_Type *Event_Node_Queue,
		__Sys_Scheduling_Task_TCB_Type **First_Event_TCB)
{
	if(Event_Node_Queue==Null || First_Event_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(Event_Node_Queue->Begin==Null)
	{
		return Error_Operation_Failed;
	}
	*First_Event_TCB=Event_Node_Queue->Begin;

	return Error_OK;
}

int Queue_TCB_Delete_Event_Node_Queue_First_TCB(
		Task_Queue_Type *Event_Node_Queue,
		__Sys_Scheduling_Task_TCB_Type **Delet_First_TCB)
{
	if(Event_Node_Queue==Null || Delet_First_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(Event_Node_Queue->Begin==Null)
	{
		return Error_Operation_Failed;
	}

	if(*Delet_First_TCB==Null)
	{
		*Delet_First_TCB=Event_Node_Queue->Begin;
	}
	else if(*Delet_First_TCB!=Event_Node_Queue->Begin)
	{
		return Error_Invalid_Parameter;
	}
	Event_Node_Queue->Begin->Event.Event_Queue=Null;
	Event_Node_Queue->Begin=Event_Node_Queue->Begin->Queue.Event_NEXT;
	if(Event_Node_Queue->Begin==Null)
	{
		Event_Node_Queue->End=Null;
	}
	return Error_OK;

}

int Queue_TCB_Delete_Event_Node_Queue(
		Task_Queue_Type *Event_Node_Queue,
		__Sys_Scheduling_Task_TCB_Type *Delet_TCB)
{
	if(Event_Node_Queue==Null || Delet_TCB==Null)
	{
		return Error_Invalid_Parameter;
	}
	__Sys_Scheduling_Task_TCB_Type *Temp_TCB=Null,*Temp_TCB_LAST=Null,*Temp_TCB_NEXT=Null;

	Temp_TCB=Event_Node_Queue->Begin;

	while(Temp_TCB!=Null)
	{
		if(Temp_TCB==Delet_TCB)//查找到
		{
			Temp_TCB_NEXT=Temp_TCB->Queue.Event_NEXT;

			//如果这个数据是头
			if(Temp_TCB_LAST==Null || Delet_TCB==Event_Node_Queue->Begin)
			{
				Event_Node_Queue->Begin=Event_Node_Queue->Begin->Queue.Event_NEXT;

			}
			//如果这个数据是尾
			if(Temp_TCB_NEXT==Null || Delet_TCB==Event_Node_Queue->End)
			{
				Event_Node_Queue->End=Temp_TCB_LAST;

				if(Event_Node_Queue->End!=Null)
				{
					Event_Node_Queue->End->Queue.Event_NEXT=Null;
				}
			}

			//如果头和尾都不是空 那么数据在中间
			if(Temp_TCB_LAST!=Null && Temp_TCB_NEXT!=Null)
			{
				Temp_TCB_LAST->Queue.Event_NEXT=Temp_TCB_NEXT;

			}
			Delet_TCB->Event.Event_Queue=Null;
			Delet_TCB->Queue.Event_NEXT=Null;
			return Error_OK;
		}
		else
		{
			Temp_TCB_LAST=Temp_TCB;
			Temp_TCB=Temp_TCB->Queue.Event_NEXT;
		}

	}
	return Error_Invalid_Parameter;
}

