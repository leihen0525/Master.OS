/*
 * Memory.c
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */
//#include "__Sys.API.h"
#include "Error.h"

#include "Memory.h"

#ifdef __MPU__
Memory_DATA_Type __Sys_Memory_DATA;
#endif

Memory_DATA_Type __Usr_Memory_DATA;


int __Sys_Memory_Init(void)
{
	int Err;

#ifdef __MPU__
#pragma section="__Sys_HEAP"
	if((Err=__Memory_Init(
			&__Sys_Memory_DATA,
			__section_begin("__Sys_HEAP"),
			__section_end("__Sys_HEAP"),
			__section_size("__Sys_HEAP")))!=Error_OK)
	{
		return Err;
	}
#endif

#pragma section="HEAP"
	if((Err=__Memory_Init(
			&__Usr_Memory_DATA,
			__section_begin("HEAP"),
			__section_end("HEAP"),
			__section_size("HEAP")))!=Error_OK)
	{
		return Err;
	}
	return Error_OK;
}

uint32_t __Sys_Memory_Size(void)
{
#ifdef __MPU__
	return __Memory_Size(&__Sys_Memory_DATA);
#else
	return __Memory_Size(&__Usr_Memory_DATA);
#endif
}

void *__Sys_Memory_Malloc(unsigned int Size)
{
#ifdef __MPU__
	return __Memory_Malloc(&__Sys_Memory_DATA,Size);
#else
	return __Memory_Malloc(&__Usr_Memory_DATA,Size);
#endif
}

void __Sys_Memory_Free(void *ap)
{
#ifdef __MPU__
	__Memory_Free(&__Sys_Memory_DATA,ap);
#else
	__Memory_Free(&__Usr_Memory_DATA,ap);
#endif
}

uint32_t __Usr_Memory_Size(void)
{
	return __Memory_Size(&__Usr_Memory_DATA);
}

void *__Usr_Memory_Malloc(unsigned int Size)
{
	return __Memory_Malloc(&__Usr_Memory_DATA,Size);
}

void __Usr_Memory_Free(void *ap)
{
	__Memory_Free(&__Usr_Memory_DATA,ap);
}

int __Memory_Init(
		Memory_DATA_Type *P_Memory_DATA,
		uint32_t *HEAP_Begin,
		uint32_t *HEAP_End,
		uint32_t HEAP_Size)
{
	if(P_Memory_DATA==Null || HEAP_End==Null || HEAP_Size==0)
	{
		return Error_Invalid_Parameter;
	}
	P_Memory_DATA->HEAP_Begin=HEAP_Begin;
	P_Memory_DATA->HEAP_End=HEAP_End;
	P_Memory_DATA->HEAP_Size=HEAP_Size;

	Memory_Node_Type *Temp_Node;

	Temp_Node=(Memory_Node_Type *)&P_Memory_DATA->HEAP_Begin[0];

	//检查对齐问题
	BUILD_BUG_ON(sizeof(Memory_Node_Type)!=4);


	Temp_Node->Size=(P_Memory_DATA->HEAP_Size/4)-1;
	Temp_Node->Free=1;

	Temp_Node->NEXT_Index=(P_Memory_DATA->HEAP_Size/4);


	P_Memory_DATA->Size_Byte=Temp_Node->Size*4;

	return Error_OK;

}
uint32_t __Memory_Size(Memory_DATA_Type *P_Memory_DATA)
{
	if(P_Memory_DATA==Null)
	{
		return 0;
	}
	return P_Memory_DATA->HEAP_Size;
}

void *__Memory_Malloc(Memory_DATA_Type *P_Memory_DATA,unsigned int Size)
{
	if(P_Memory_DATA==Null)
	{
		return Null;
	}
	Memory_Node_Type *Temp_Node,*Temp_Node1;

	void *Re;

	uint32_t Index;

	uint16_t sy=0;

	if(Size==0)
	{
		return Null;
	}

	if((Size%4)==0)
	{
		Size=Size/4;
	}
	else
	{
		Size=Size/4+1;
	}

	Temp_Node=(Memory_Node_Type *)&P_Memory_DATA->HEAP_Begin[0];

	while(1)
	{
		if(Temp_Node->Free==1 && Temp_Node->Size>=Size)
		{
			Temp_Node->Free=0;			//做标记 占用

			sy=Temp_Node->Size-Size;	//计算剩余空间

			Temp_Node->Size=Size;		//标记占用空间大小

			P_Memory_DATA->Size_Byte=P_Memory_DATA->Size_Byte-Size*4;

			Re=(void*)((uint32_t)Temp_Node+4);

			if(sy>1)//剩余空间至少2个单位
			{

				Index=(uint32_t)Temp_Node-(uint32_t)&P_Memory_DATA->HEAP_Begin[0];//计算当前偏移量

				Index=Index/4;

				Temp_Node1=(Memory_Node_Type *)&P_Memory_DATA->HEAP_Begin[Index+Size+1];

				Temp_Node1->NEXT_Index=Temp_Node->NEXT_Index;

				Temp_Node->NEXT_Index=Index+Size+1;

				Temp_Node1->Free=1;
				Temp_Node1->Size=sy-1;

				P_Memory_DATA->Size_Byte=P_Memory_DATA->Size_Byte-4;
			}

			return Re;
		}
		if(Temp_Node->NEXT_Index==(P_Memory_DATA->HEAP_Size/4))
		{
			return Null;
		}
		else
		{
			Temp_Node=(Memory_Node_Type *)&P_Memory_DATA->HEAP_Begin[Temp_Node->NEXT_Index];
		}
	}
}

void __Memory_Free(Memory_DATA_Type *P_Memory_DATA,void *ap)
{
	if(P_Memory_DATA==Null)
	{
		return ;
	}
	Memory_Node_Type *Temp_Node,*Temp_Node_LAST=Null,*Temp_Node_NEXT;

	if(ap==Null)
	{
		return;
	}

	Temp_Node=(Memory_Node_Type *)&P_Memory_DATA->HEAP_Begin[0];

	while(1)
	{
		if(Temp_Node->Free==0)
		{

			Temp_Node_NEXT=(Memory_Node_Type *)&P_Memory_DATA->HEAP_Begin[Temp_Node->NEXT_Index];

			if(((uint32_t)Temp_Node)<=((uint32_t)ap) && ((uint32_t)ap)<=((uint32_t)Temp_Node_NEXT))
			{
				Temp_Node->Free=1;

				P_Memory_DATA->Size_Byte=P_Memory_DATA->Size_Byte+Temp_Node->Size*4;


				//整理之前的
				if(Temp_Node_LAST!=Null)//上一个节点是如果有且是空闲 那么合并
				{
					if(Temp_Node_LAST->Free==1)
					{
						Temp_Node_LAST->Size=Temp_Node_LAST->Size+Temp_Node->Size+1;

						Temp_Node_LAST->NEXT_Index=Temp_Node->NEXT_Index;

						P_Memory_DATA->Size_Byte=P_Memory_DATA->Size_Byte+4;

						Temp_Node=Temp_Node_LAST;
					}
					else
					{
						return;//这种情况不存在
					}

				}
				else
				{
					Temp_Node_LAST=Null;
				}

				//整理后面的
				Temp_Node_LAST=Temp_Node;
				while(1)
				{
					if(Temp_Node->NEXT_Index==(P_Memory_DATA->HEAP_Size/4))
					{
						return;
					}
					else
					{
						Temp_Node=(Memory_Node_Type *)&P_Memory_DATA->HEAP_Begin[Temp_Node->NEXT_Index];
					}

					if(Temp_Node->Free==1)
					{
						if(Temp_Node_LAST!=Null)
						{
							if(Temp_Node_LAST->Free==1)
							{
								Temp_Node_LAST->Size=Temp_Node_LAST->Size+Temp_Node->Size+1;

								Temp_Node_LAST->NEXT_Index=Temp_Node->NEXT_Index;

								P_Memory_DATA->Size_Byte=P_Memory_DATA->Size_Byte+4;

								Temp_Node=Temp_Node_LAST;
							}
							else
							{
								return;//这种情况不存在
							}
						}
						else
						{
							return;//这种情况不存在
						}

					}
					else
					{
						return;
					}

				}

			}
			else
			{
				Temp_Node_LAST=Null;
			}

		}
		else //Temp_Node->Free==1
		{
			//整理之前的
			if(Temp_Node_LAST!=Null)//上一个节点是如果有且是空闲 那么合并
			{
				if(Temp_Node_LAST->Free==1)
				{
					Temp_Node_LAST->Size=Temp_Node_LAST->Size+Temp_Node->Size+1;

					Temp_Node_LAST->NEXT_Index=Temp_Node->NEXT_Index;

					P_Memory_DATA->Size_Byte=P_Memory_DATA->Size_Byte+4;

					Temp_Node=Temp_Node_LAST;
				}
				else
				{
					return;//这种情况不存在
				}

			}
			else//Temp_Node_LAST==Null
			{
				Temp_Node_LAST=Temp_Node;
			}
		}
		if(Temp_Node->NEXT_Index==(P_Memory_DATA->HEAP_Size/4))
		{
			break;
		}
		else
		{
			Temp_Node=(Memory_Node_Type *)&P_Memory_DATA->HEAP_Begin[Temp_Node->NEXT_Index];
		}
	}

}
