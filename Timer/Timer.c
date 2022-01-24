/*
 * Timer.c
 *
 *  Created on: 2019年4月29日
 *      Author: Master.HE
 */
#include "Define.h"
#include "Error.h"

#include "Timer.h"

#include "__Sys.API.h"

#include "Timer/Timer.Enum.h"

#include "API.h"

#include "IRQ/IRQ.h"

#include "Scheduling/Scheduling.h"

Timer_DATA_Type Timer_DATA;

int Timer_Init(Machine_Desc_Timer_Type *P_Timer)
{
	if(P_Timer==Null)
	{
		return Error_Invalid_Parameter;
	}
	Timer_DATA.Timer=P_Timer;

	Timer_DATA.Counter=0;

	if(Timer_DATA.Timer->Init==Null
	|| Timer_DATA.Timer->GET_Flag==Null
	|| Timer_DATA.Timer->Enable==Null
	|| Timer_DATA.Timer->Disable==Null)
	{
		return Error_Undefined;
	}

	//初始化定时器
	int Err=Timer_DATA.Timer->Init();

	if(Err!=Error_OK)
	{
		return Err;
	}

	//注册定时器中断函数
	Err=__Sys_IRQ_Register_Hook(Timer_DATA.Timer->IRQ_Index,Timer_IRQ,Null);
	if(Err<Error_OK)
	{
		return Err;
	}

	//使能定时器中断
	Err=__Sys_IRQ_Enable(Timer_DATA.Timer->IRQ_Index);
	if(Err!=Error_OK)
	{
		return Err;
	}

	//先关闭定时器
	Err=Timer_DATA.Timer->Disable();
	if(Err!=Error_OK)
	{
		return Err;
	}

	Timer_DATA.Enabled=Enable;

	Timer_DATA.Timer_Queue.Begin=Null;
	Timer_DATA.Timer_Queue.End=Null;

	Err=__Sys_FIFO_Queue_Create(Null,sizeof(Timer_Function_Type),Timer_FIFO_Queue_Max_Length,Null,Null);

	if(Err<Error_OK)
	{
		return Err;
	}
	Timer_DATA.FIFO_Queue=Err;

	return Error_OK;
}
int Timer_Get_Flag(void)
{
	if(Timer_DATA.Timer->GET_Flag==Null)
	{
		return Error_Undefined;
	}
	return Timer_DATA.Timer->GET_Flag();
}
int __Sys_Timer_GET_Counter(uint64_t *Counter_MS)
{
	if(Counter_MS==Null)
	{
		return Error_Invalid_Parameter;
	}
	*Counter_MS=Timer_DATA.Counter;
	return Error_OK;
}
#ifdef Master_OS_Config_Timer_Enable
int __Sys_Timer_Enable(void)
{
	if(Timer_DATA.Timer->Enable==Null)
	{
		return Error_Undefined;
	}
	return Timer_DATA.Timer->Enable();
}
#endif
#ifdef Master_OS_Config_Timer_Disable
int __Sys_Timer_Disable(void)
{
	if(Timer_DATA.Timer->Disable==Null)
	{
		return Error_Undefined;
	}
	return Timer_DATA.Timer->Disable();
}
#endif
void Timer_IRQ(void *Args,int IRQ_Index)
{
	if(Timer_Get_Flag()==Error_OK)
	{
		Timer_DATA.Counter++;

		__Timer_SysTick_Entry();

		Scheduling_SysTick();
	}

	//while(1);
}
//------------------------------------------------------------------------------------------
//--API----以下API只能是特权级模式调用
#ifdef Master_OS_Config_Timer_Register
int __Sys_Timer_Register(
		Timer_Enter_Function Timer_Function,
		void *Args)
{
	int Err;
	if(Timer_Function==Null)
	{
		return Error_Invalid_Parameter;
	}


	Timer_Node_Type *Temp_Timer_Node;

	Temp_Timer_Node=(Timer_Node_Type *)__Sys_Memory_Malloc(sizeof(Timer_Node_Type));

	if(Temp_Timer_Node==Null)
	{
		return Error_Allocation_Memory_Failed;
	}

	Error_Args(Temp_Timer_Node->Handle,__Sys_Handle_New())
	{
		Err=Temp_Timer_Node->Handle;
		goto __Sys_Timer_Register_Exit;
	}


	Temp_Timer_Node->N_Time_Cycle=-1;
	Temp_Timer_Node->Cycle_Time_MS=-1;

	Temp_Timer_Node->Suspended_Time_MS=-1;
	Temp_Timer_Node->Now_Countdown_N_Time_Cycle=-1;

	Temp_Timer_Node->TimeOut_MS=-1;

	Temp_Timer_Node->Timer_Function.Args1=Args;
	Temp_Timer_Node->Timer_Function.Args2=Null;
	Temp_Timer_Node->Timer_Function.Timer_Function=Timer_Function;
	Temp_Timer_Node->Timer_Function.Timer_Function2=Null;

	Error_NoArgs(Err,Timer_Add_Timer_Queue(Temp_Timer_Node,-1))
	{
		goto __Sys_Timer_Register_Exit1;
	}

	return Temp_Timer_Node->Handle;

__Sys_Timer_Register_Exit1:
	__Sys_Handle_Free(Temp_Timer_Node->Handle);

__Sys_Timer_Register_Exit:
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(Temp_Timer_Node);
#endif

	return Err;
}
#endif
#ifdef Master_OS_Config_Timer_Register
int __Sys_Timer_Register2(
		Timer_Enter_Function2 Timer_Function,
		void *Args1,
		void *Args2)
{
	int Err;
	if(Timer_Function==Null)
	{
		return Error_Invalid_Parameter;
	}


	Timer_Node_Type *Temp_Timer_Node;

	Temp_Timer_Node=(Timer_Node_Type *)__Sys_Memory_Malloc(sizeof(Timer_Node_Type));

	if(Temp_Timer_Node==Null)
	{
		return Error_Allocation_Memory_Failed;
	}

	Error_Args(Temp_Timer_Node->Handle,__Sys_Handle_New())
	{
		Err=Temp_Timer_Node->Handle;
		goto __Sys_Timer_Register_Exit;
	}


	Temp_Timer_Node->N_Time_Cycle=-1;
	Temp_Timer_Node->Cycle_Time_MS=-1;

	Temp_Timer_Node->Suspended_Time_MS=-1;
	Temp_Timer_Node->Now_Countdown_N_Time_Cycle=-1;

	Temp_Timer_Node->TimeOut_MS=-1;

	Temp_Timer_Node->Timer_Function.Args1=Args1;
	Temp_Timer_Node->Timer_Function.Args2=Args2;
	Temp_Timer_Node->Timer_Function.Timer_Function=Null;
	Temp_Timer_Node->Timer_Function.Timer_Function2=Timer_Function;

	Error_NoArgs(Err,Timer_Add_Timer_Queue(Temp_Timer_Node,-1))
	{
		goto __Sys_Timer_Register_Exit1;
	}

	return Temp_Timer_Node->Handle;

__Sys_Timer_Register_Exit1:
	__Sys_Handle_Free(Temp_Timer_Node->Handle);

__Sys_Timer_Register_Exit:
#ifdef Master_OS_Config_Memory_Free
	__Sys_Memory_Free(Temp_Timer_Node);
#endif

	return Err;
}
#endif
#ifdef Master_OS_Config_Timer_Delete
int __Sys_Timer_Delete(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	int Err;
	Timer_Node_Type *Delete_Node=Null;
	if((Err=Timer_Delete_Timer_Queue(Handle,&Delete_Node))==Error_OK)
	{
		if(Delete_Node==Null)
		{
			return Error_Unknown;
		}
		__Sys_Memory_Free(Delete_Node);
		__Sys_Handle_Free(Handle);
	}
	return Err;

}
#endif
#ifdef Master_OS_Config_Timer_Start
int __Sys_Timer_Start(
		int Handle,
		int32_t N_Time_Cycle,	//次数
		int32_t Cycle_Time_MS,	//周期
		Timer_Operation_Type Timer_Operation)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	if((N_Time_Cycle<=0 && Timer_Operation==Timer_Operation_N_Time_Cycle)
	|| Cycle_Time_MS<=0
	|| Timer_Operation>=Timer_Operation_End)
	{
		return Error_Invalid_Parameter;
	}

	//将定时器任务从 队列中取出来
	int Err;
	Timer_Node_Type *Temp_Node=Null;
	if((Err=Timer_Delete_Timer_Queue(Handle,&Temp_Node))!=Error_OK)
	{
		return Err;
	}
	if(Temp_Node==Null)
	{
		return Error_Unknown;
	}
	//参数复制
	if(Timer_Operation==Timer_Operation_N_Time_Cycle)
	{
		Temp_Node->N_Time_Cycle=N_Time_Cycle;
	}
	else
	{
		Temp_Node->N_Time_Cycle=-1;
	}
	Temp_Node->Cycle_Time_MS=Cycle_Time_MS;

	Temp_Node->Suspended_Time_MS=-1;
	Temp_Node->Now_Countdown_N_Time_Cycle=Temp_Node->N_Time_Cycle;

	if((Err=Timer_Add_Timer_Queue(Temp_Node,Cycle_Time_MS))!=Error_OK)
	{
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(Temp_Node);
#endif
		return Err;
	}
	return Error_OK;

}
#endif
#ifdef Master_OS_Config_Timer_Stop
int __Sys_Timer_Stop(int Handle)
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	//将定时器任务从 队列中取出来
	int Err;
	Timer_Node_Type *Temp_Node=Null;
	if((Err=Timer_Delete_Timer_Queue(Handle,&Temp_Node))!=Error_OK)
	{
		return Err;
	}
	if(Temp_Node==Null)
	{
		return Error_Unknown;
	}
	//重置参数
	Temp_Node->Suspended_Time_MS=-1;
	Temp_Node->Now_Countdown_N_Time_Cycle=-1;

	if((Err=Timer_Add_Timer_Queue(Temp_Node,-1))!=Error_OK)
	{
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(Temp_Node);
#endif
		return Err;
	}
	return Error_OK;

}
#endif
#ifdef Master_OS_Config_Timer_Suspend
int __Sys_Timer_Suspend(int Handle)//暂停
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	//将定时器任务从 队列中取出来
	int Err;
	Timer_Node_Type *Temp_Node=Null;
	if((Err=Timer_Delete_Timer_Queue(Handle,&Temp_Node))!=Error_OK)
	{
		return Err;
	}
	if(Temp_Node==Null)
	{
		return Error_Unknown;
	}
	//保存时间
	Temp_Node->Suspended_Time_MS=Temp_Node->TimeOut_MS;

	if((Err=Timer_Add_Timer_Queue(Temp_Node,-1))!=Error_OK)
	{
		__Sys_Memory_Free(Temp_Node);
		return Err;
	}
	return Error_OK;

}
#endif
#ifdef Master_OS_Config_Timer_Resume
int __Sys_Timer_Resume(int Handle)//恢复
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	//将定时器任务从 队列中取出来
	int Err;
	Timer_Node_Type *Temp_Node=Null;
	if((Err=Timer_Delete_Timer_Queue(Handle,&Temp_Node))!=Error_OK)
	{
		return Err;
	}
	if(Temp_Node==Null)
	{
		return Error_Unknown;
	}
	//检查参数是否初始化过
	if(Temp_Node->Cycle_Time_MS<=0
	|| Temp_Node->N_Time_Cycle==0
	|| Temp_Node->Now_Countdown_N_Time_Cycle==0)
	{

		if((Err=Timer_Add_Timer_Queue(Temp_Node,-1))!=Error_OK)
		{
			__Sys_Memory_Free(Temp_Node);
			return Err;
		}

		return Error_Operation_Failed;
	}

	//时间
	int32_t TimeOut_MS=Temp_Node->Suspended_Time_MS;
	Temp_Node->Suspended_Time_MS=-1;
	if(TimeOut_MS<0)
	{
		if(Temp_Node->TimeOut_MS<0)
		{
			TimeOut_MS=Temp_Node->Cycle_Time_MS;
		}
		else
		{
			TimeOut_MS=Temp_Node->TimeOut_MS;
		}
	}

	if((Err=Timer_Add_Timer_Queue(Temp_Node,TimeOut_MS))!=Error_OK)
	{
		__Sys_Memory_Free(Temp_Node);
		return Err;
	}
	return Error_OK;

}
#endif
#ifdef Master_OS_Config_Timer_Reset
int __Sys_Timer_Reset(int Handle)//复位
{
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}
	//将定时器任务从 队列中取出来
	int Err;
	Timer_Node_Type *Temp_Node=Null;
	if((Err=Timer_Delete_Timer_Queue(Handle,&Temp_Node))!=Error_OK)
	{
		return Err;
	}
	if(Temp_Node==Null)
	{
		return Error_Unknown;
	}
	//检查参数是否初始化过
	if(Temp_Node->Cycle_Time_MS<=0
	|| Temp_Node->N_Time_Cycle==0)
	{

		if((Err=Timer_Add_Timer_Queue(Temp_Node,-1))!=Error_OK)
		{
#ifdef Master_OS_Config_Memory_Free
			__Sys_Memory_Free(Temp_Node);
#endif
			return Err;
		}

		return Error_Operation_Failed;
	}

	//时间

	Temp_Node->Suspended_Time_MS=-1;
	Temp_Node->Now_Countdown_N_Time_Cycle=Temp_Node->N_Time_Cycle;


	if((Err=Timer_Add_Timer_Queue(Temp_Node,Temp_Node->Cycle_Time_MS))!=Error_OK)
	{
#ifdef Master_OS_Config_Memory_Free
		__Sys_Memory_Free(Temp_Node);
#endif
		return Err;
	}
	return Error_OK;

}
#endif
#ifdef Master_OS_Config_Timer_Enabled
int __Sys_Timer_Enabled(uint8_t Enabled)
{
	if(Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	Timer_DATA.Enabled=(Enabled_Type)Enabled;

	return Error_OK;

}
#endif
//--End-API---

int Timer_Add_Timer_Queue(Timer_Node_Type *Add_Node,int32_t TimeOut_MS)
{
	if(Add_Node==Null || TimeOut_MS<(-1))
	{
		return Error_Invalid_Parameter;
	}
	if(TimeOut_MS<0)
	{
		if(Timer_DATA.Timer_Queue.End==Null)
		{
			Timer_DATA.Timer_Queue.Begin=Add_Node;
		}
		else
		{
			Timer_DATA.Timer_Queue.End->NEXT=Add_Node;
		}
		Timer_DATA.Timer_Queue.End=Add_Node;
		Add_Node->NEXT=Null;
		Add_Node->TimeOut_MS=-1;

		return Error_OK;
	}

	Timer_Node_Type *Temp_Node=Null,*Temp_Node_LAST=Null,*Temp_Node_NEXT=Null;
	int32_t Time_MS_NEXT=-1;


	Temp_Node=Timer_DATA.Timer_Queue.Begin;


	while(Temp_Node!=Null)
	{
		if(Temp_Node->TimeOut_MS<0)break;

		TimeOut_MS=TimeOut_MS-Temp_Node->TimeOut_MS;

		if(TimeOut_MS<0)
		{

			Temp_Node_NEXT=Temp_Node;

			TimeOut_MS=TimeOut_MS+Temp_Node->TimeOut_MS;

			Time_MS_NEXT=Temp_Node_NEXT->TimeOut_MS-TimeOut_MS;

			break;
		}
		else if(TimeOut_MS==0)
		{
			Temp_Node_LAST=Temp_Node;
			Temp_Node_NEXT=Temp_Node->NEXT;

			TimeOut_MS=0;

			Time_MS_NEXT=-1;

			break;
		}
		else //Time_MS>0
		{
			Temp_Node_LAST=Temp_Node;

			Temp_Node=Temp_Node->NEXT;
		}

	}


	if(Temp_Node_LAST==Null)//数据在头 或者第一次
	{

		if(Timer_DATA.Timer_Queue.Begin==Null)//队列为空 第一次创建
		{
			Timer_DATA.Timer_Queue.Begin=Add_Node;


			Timer_DATA.Timer_Queue.End=Add_Node;
			Add_Node->NEXT=Null;

			Add_Node->TimeOut_MS=TimeOut_MS;

		}
		else if(Timer_DATA.Timer_Queue.Begin==Temp_Node_NEXT)//数据在头之前
		{

			if(Time_MS_NEXT!=-1)
			{
				Temp_Node_NEXT->TimeOut_MS=Time_MS_NEXT;
			}

			Timer_DATA.Timer_Queue.Begin=Add_Node;


			Add_Node->NEXT=Temp_Node_NEXT;
			Add_Node->TimeOut_MS=TimeOut_MS;

		}
		else//数据在头之前 但是头是无限等待
		{
			Add_Node->NEXT=Timer_DATA.Timer_Queue.Begin;

			Timer_DATA.Timer_Queue.Begin=Add_Node;

			Add_Node->TimeOut_MS=TimeOut_MS;

		}
	}
	else//数据在中间或者在尾
	{
		if(Temp_Node_NEXT!=Null)//数据在中间
		{
			Temp_Node_LAST->NEXT=Add_Node;


			Add_Node->TimeOut_MS=TimeOut_MS;
			Add_Node->NEXT=Temp_Node_NEXT;



			if(Time_MS_NEXT!=-1)
			{
				Temp_Node_NEXT->TimeOut_MS=Time_MS_NEXT;
			}
		}
		else//数据在尾
		{
			if(Temp_Node_LAST==Timer_DATA.Timer_Queue.End)
			{
				Temp_Node_LAST->NEXT=Add_Node;

				Add_Node->TimeOut_MS=TimeOut_MS;
				Add_Node->NEXT=Null;

				Timer_DATA.Timer_Queue.End=Add_Node;
			}
			else//数据在尾之前 尾是时间无限等待
			{
				Temp_Node_NEXT=Temp_Node_LAST->NEXT;

				Temp_Node_LAST->NEXT=Add_Node;

				Add_Node->TimeOut_MS=TimeOut_MS;

				Add_Node->NEXT=Temp_Node_NEXT;
			}
		}
	}

	return Error_OK;
}
int Timer_Delete_Timer_Queue(int Handle,Timer_Node_Type **Delete_Node)
{
	if(Delete_Node==Null)
	{
		return Error_Invalid_Parameter;
	}
	Timer_Node_Type *Temp_Node=Null,*Temp_Node_LAST=Null,*Temp_Node_NEXT=Null;

	Temp_Node=Timer_DATA.Timer_Queue.Begin;

	while(Temp_Node!=Null)
	{
		if((*Delete_Node)==Null)
		{
			if(Temp_Node->Handle==Handle)
			{
				*Delete_Node=Temp_Node;
			}
			else
			{
				goto Loop_End;
			}
		}
		else
		{
			if(Temp_Node==(*Delete_Node))
			{
				;
			}
			else
			{
				goto Loop_End;
			}
		}

		Temp_Node_NEXT=Temp_Node->NEXT;

		//如果这个数据是头
		if(Temp_Node_LAST==Null || Temp_Node==Timer_DATA.Timer_Queue.Begin)
		{
			Timer_DATA.Timer_Queue.Begin=Timer_DATA.Timer_Queue.Begin->NEXT;

			if(Timer_DATA.Timer_Queue.Begin!=Null)//下一个还有
			{
				if(Timer_DATA.Timer_Queue.Begin->TimeOut_MS>=0)
				{
					if(Temp_Node->TimeOut_MS>=0)
					{
						Timer_DATA.Timer_Queue.Begin->TimeOut_MS=Timer_DATA.Timer_Queue.Begin->TimeOut_MS+Temp_Node->TimeOut_MS;
					}
				}
			}
		}
		//如果这个数据是尾
		if(Temp_Node_NEXT==Null || Temp_Node==Timer_DATA.Timer_Queue.End)
		{
			Timer_DATA.Timer_Queue.End=Temp_Node_LAST;

			if(Timer_DATA.Timer_Queue.End!=Null)
			{
				Timer_DATA.Timer_Queue.End->NEXT=Null;
			}
		}
		//如果头和尾都不是空 那么数据在中间
		if(Temp_Node_LAST!=Null && Temp_Node_NEXT!=Null)
		{
			//修补时间队列
			if(Temp_Node->TimeOut_MS>=0 && Temp_Node_NEXT->TimeOut_MS>=0)
			{
				Temp_Node_NEXT->TimeOut_MS=Temp_Node_NEXT->TimeOut_MS+Temp_Node->TimeOut_MS;
			}
			Temp_Node_LAST->NEXT=Temp_Node_NEXT;
		}
		Temp_Node->NEXT=Null;

		return Error_OK;
Loop_End:
		Temp_Node_LAST=Temp_Node;
		Temp_Node=Temp_Node->NEXT;
	}

	if((*Delete_Node)==Null)
	{
		return Error_Invalid_Handle;
	}
	else
	{
		return Error_Invalid_Parameter;
	}

}


//定时器执行部分 里面API必须是 API_User
void __Timer_Task(void)
{
	Timer_Function_Type Timer_Function;

	FIFO_Queue_Open(Timer_DATA.FIFO_Queue);
	Timer_Function.Args1=Null;
	Timer_Function.Args2=Null;
	Timer_Function.Timer_Function=Null;
	Timer_Function.Timer_Function2=Null;
	while(1)
	{
		if(FIFO_Queue_Wait(Timer_DATA.FIFO_Queue,&Timer_Function,sizeof(Timer_Function_Type),Null,-1)==Error_OK)
		{
			if(Timer_Function.Timer_Function!=Null && Timer_Function.Timer_Function2==Null)
			{
				Timer_Function.Timer_Function(Timer_Function.Args1);
			}
			else if(Timer_Function.Timer_Function==Null && Timer_Function.Timer_Function2!=Null)
			{
				Timer_Function.Timer_Function2(Timer_Function.Args1,Timer_Function.Args2);
			}
			else
			{
				;
			}
			Timer_Function.Args1=Null;
			Timer_Function.Args2=Null;
			Timer_Function.Timer_Function=Null;
			Timer_Function.Timer_Function2=Null;
		}
		else
		{
			Scheduling_Sleep_Task(10);
		}
	}
}

void __Timer_SysTick_Entry(void)
{
	bool Context_Switch1=false;
	Timer_Node_Type *Temp_Node=Null;

	if(Timer_DATA.Enabled==Disable || Timer_DATA.Timer_Queue.Begin==Null)
	{
		goto __Timer_SysTick_Entry_Exit;
	}
	if(Timer_DATA.Timer_Queue.Begin->TimeOut_MS<0)
	{
		goto __Timer_SysTick_Entry_Exit;
	}
	else
	{
		if(Timer_DATA.Timer_Queue.Begin->TimeOut_MS>0)
		{
			Timer_DATA.Timer_Queue.Begin->TimeOut_MS--;
		}
	}



	while(Timer_DATA.Timer_Queue.Begin!=Null)
	{
		if(Timer_DATA.Timer_Queue.Begin->TimeOut_MS!=0)
		{
			goto __Timer_SysTick_Entry_Exit;
		}
		Temp_Node=Timer_DATA.Timer_Queue.Begin;

		Timer_DATA.Timer_Queue.Begin=Timer_DATA.Timer_Queue.Begin->NEXT;
		if(Timer_DATA.Timer_Queue.Begin==Null)
		{
			Timer_DATA.Timer_Queue.End=Null;
		}
		Temp_Node->NEXT=Null;

		//TODO
		bool Context_Switch=false;
		if(__Sys_FIFO_Queue_Set(Timer_DATA.FIFO_Queue,&Temp_Node->Timer_Function,sizeof(Timer_Function_Type),&Context_Switch)==Error_OK)
		{
			if(Context_Switch==true)
			{
				Context_Switch1=true;
			}
		}


		Temp_Node->Suspended_Time_MS=-1;

		if(Temp_Node->Now_Countdown_N_Time_Cycle>0)
		{
			Temp_Node->Now_Countdown_N_Time_Cycle--;
			if(Temp_Node->Now_Countdown_N_Time_Cycle==0)
			{


				//加入挂起队列
				if(Timer_Add_Timer_Queue(Temp_Node,-1)!=Error_OK)
				{
					;
				}
			}
		}
		else
		{
			if(Timer_Add_Timer_Queue(Temp_Node,Temp_Node->Cycle_Time_MS)!=Error_OK)
			{
				;
			}
		}

	}

__Timer_SysTick_Entry_Exit:
	if(Context_Switch1==true)
	{
		__Sys_Scheduling_Try_Context_Switch();
	}
}

