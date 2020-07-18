/*
 * Memory.c
 *
 *  Created on: 2019年4月12日
 *      Author: Master.HE
 */
//#include "__Sys.API.h"
#include "Error.h"
#include "Memory.Define.h"
#include "Memory.h"

#ifdef __UsrSP_SysSP__
Memory_DATA_Type __Sys_Memory_DATA;
#endif

Memory_DATA_Type __Usr_Memory_DATA;


int __Sys_Memory_Init(void)
{
	int Err;

#ifdef __UsrSP_SysSP__
#pragma section="__Sys_HEAP"
	if((Err=__Memory_Init(
			&__Sys_Memory_DATA,
			(uint8_t *)__section_begin("__Sys_HEAP"),
			__section_size("__Sys_HEAP")))!=Error_OK)
	{
		return Err;
	}
#endif

#pragma section="HEAP"
	if((Err=__Memory_Init(
			&__Usr_Memory_DATA,
			(uint8_t *)__section_begin("HEAP"),
			__section_size("HEAP")))!=Error_OK)
	{
		return Err;
	}
	return Error_OK;
}
#ifdef Master_OS_Config_Memory_Size_Malloc
uint32_t __Sys_Memory_Size_Malloc(void)
{
#ifdef __UsrSP_SysSP__
	return __Memory_Size_Malloc(&__Sys_Memory_DATA);
#else
	return __Memory_Size_Malloc(&__Usr_Memory_DATA);
#endif
}
#endif
#ifdef Master_OS_Config_Memory_Size_Free
uint32_t __Sys_Memory_Size_Free(void)
{
#ifdef __UsrSP_SysSP__
	return __Memory_Size_Free(&__Sys_Memory_DATA);
#else
	return __Memory_Size_Free(&__Usr_Memory_DATA);
#endif
}
#endif
#ifdef Master_OS_Config_Memory_Malloc_Align
void *__Sys_Memory_Malloc_Align(uint32_t Size,uint32_t Align)
{
#ifdef __UsrSP_SysSP__
	return __Memory_Malloc(&__Sys_Memory_DATA,Size,Align);
#else
	return __Memory_Malloc(&__Usr_Memory_DATA,Size,Align);
#endif
}
#endif
#ifdef Master_OS_Config_Memory_Malloc
void *__Sys_Memory_Malloc(uint32_t Size)
{
#ifdef __UsrSP_SysSP__
	return __Memory_Malloc(&__Sys_Memory_DATA,Size,4);
#else
	return __Memory_Malloc(&__Usr_Memory_DATA,Size,4);
#endif
}
#endif
#ifdef Master_OS_Config_Memory_Free
void __Sys_Memory_Free(void *ap)
{
#ifdef __UsrSP_SysSP__
	__Memory_Free(&__Sys_Memory_DATA,ap);
#else
	__Memory_Free(&__Usr_Memory_DATA,ap);
#endif
}
#endif
uint32_t __Usr_Memory_Size_Malloc(void)
{
	return __Memory_Size_Malloc(&__Usr_Memory_DATA);
}

uint32_t __Usr_Memory_Size_Free(void)
{
	return __Memory_Size_Free(&__Usr_Memory_DATA);
}

void *__Usr_Memory_Malloc_Align(uint32_t Size,uint32_t Align)
{
	return __Memory_Malloc(&__Usr_Memory_DATA,Size,Align);
}

void *__Usr_Memory_Malloc(uint32_t Size)
{
	return __Memory_Malloc(&__Usr_Memory_DATA,Size,4);
}

void __Usr_Memory_Free(void *ap)
{
	__Memory_Free(&__Usr_Memory_DATA,ap);
}

//-----------------------------------------------------------------------------------------
int __Memory_Test_List(Memory_Node_List_Type *P_List_DATA)
{
	if(P_List_DATA==Null)
	{
		return Error_Invalid_Parameter;
	}

	uint32_t Sum=0;

	Memory_Node_Type *Temp_Node=P_List_DATA->Begin;

	while(Temp_Node!=Null)
	{
		Sum=Sum+Temp_Node->Size_Byte;
		Temp_Node=Temp_Node->NEXT;
	}
	if(Sum==P_List_DATA->Size_Byte)
	{
		return Error_OK;
	}
	else
	{
		return Error_Dissatisfy;
	}
}
int __Memory_Init(
		Memory_DATA_Type *P_Memory_DATA,
		uint8_t *HEAP,
		uint32_t Size)
{
	if(P_Memory_DATA==Null || HEAP==Null|| ((uint32_t)HEAP&0x03)!=0)
	{
		return Error_Invalid_Parameter;
	}
	P_Memory_DATA->HEAP.Begin=HEAP;
	P_Memory_DATA->HEAP.End=(uint8_t *)((uint32_t)HEAP+Size-1);
	P_Memory_DATA->HEAP.Size_Byte=Size;

	int Err=Error_OK;

	Memory_Node_Type *Temp_Node;

	Temp_Node=(Memory_Node_Type *)&P_Memory_DATA->HEAP.Begin[0];

	//检查对齐问题
	BUILD_BUG_ON(Memory_Node_Head_Size!=8);

	P_Memory_DATA->Malloc.Begin=Null;
	P_Memory_DATA->Malloc.End=Null;
	P_Memory_DATA->Malloc.Size_Byte=0;

	P_Memory_DATA->Free.Size_Byte=Size-Memory_Node_Head_Size;



	if((Err=__Memory_Calculate_Node_Verify(Temp_Node,P_Memory_DATA->Free.Size_Byte,Null))!=Error_OK)
	{
		return Err;
	}

	P_Memory_DATA->Free.Begin=Temp_Node;
	P_Memory_DATA->Free.End=Null;//Temp_Node;

	P_Memory_DATA->Flag.DATA=0;



	return Error_OK;

}
uint32_t __Memory_Size_Malloc(Memory_DATA_Type *P_Memory_DATA)
{
	if(P_Memory_DATA==Null)
	{
		return 0;
	}
	return P_Memory_DATA->Malloc.Size_Byte;
}
uint32_t __Memory_Size_Free(Memory_DATA_Type *P_Memory_DATA)
{
	if(P_Memory_DATA==Null)
	{
		return 0;
	}
	return P_Memory_DATA->Free.Size_Byte;
}
//Align必须是2的倍数且不能小于4
void *__Memory_Malloc(Memory_DATA_Type *P_Memory_DATA,uint32_t Size,uint32_t Align)
{
	if(P_Memory_DATA==Null || Size==0 || Align==0 || (Align&0x3)!=0)
	{
		return Null;
	}

	//长度先用4字节对齐
	if((Size&0x03)!=0)
	{
		Size=(Size&0xFFFFFFFC)+0x04;
	}

#ifdef __Memory_TEST__
	//Test
	if(__Memory_Test_List(&P_Memory_DATA->Malloc)!=Error_OK)
	{
		P_Memory_DATA->Flag.TEST_Malloc_Size_Err=1;

		int i=1;
		while(i);
	}
	if(__Memory_Test_List(&P_Memory_DATA->Free)!=Error_OK)
	{
		P_Memory_DATA->Flag.TEST_Free_Size_Err=1;

		int i=1;
		while(i);
	}
#endif


	Memory_Node_Type *Temp_Node,*Temp_Node_LAST=Null;

	Temp_Node=P_Memory_DATA->Free.Begin;

	//开始进入Free链表查找满足的大小的数据节点
	while(Temp_Node!=Null)
	{
		//检验数据块头是否正确
		if(__Memory_Check_Node_Verify(Temp_Node)!=Error_OK)
		{
			P_Memory_DATA->Flag.Free_Head_Err=1;
			return Null;
		}


		uint32_t Begin_Address=(uint32_t)Temp_Node+Memory_Node_Head_Size;
		//uint32_t End_Adress=Begin_Address+Temp_Node->Size_Byte-1;


		//计算离需要对齐的目标还差多少个字节
		uint32_t Size_Align=0;

		if((Begin_Address&(Align-1))!=0)
		{
			Size_Align=Align-(Begin_Address&(Align-1));
		}

		uint32_t New_Size=Size+Size_Align;

		//找到大小满足条件的数据块
		if(Temp_Node->Size_Byte>=New_Size)
		{
			//地址对齐-误差控制在小于等于一个头的大小，则不进行分割，因为分割没有意义
			if(Size_Align<=Memory_Node_Head_Size)
			{

#ifdef __Memory_TEST__
				uint32_t old_Free_Size=P_Memory_DATA->Free.Size_Byte;
				if(__Memory_Test_List(&P_Memory_DATA->Free)!=Error_OK)
				{
					P_Memory_DATA->Flag.TEST_Free_Size_Err=1;

					int i=1;
					while(i);
				}
#endif

			//首先分割出需要的数据节点和剩余未使用的数据节点
				//计算下一个空余数据块
				Memory_Node_Type *Temp_Node_NEXT=Null;
				//当前节点可以分割出下一个剩余未使用的节点
				if(Temp_Node->Size_Byte>(New_Size+Memory_Node_Head_Size))
				{
					//计算出下一个未使用节点的首地址
					Temp_Node_NEXT=(Memory_Node_Type *)(Begin_Address+New_Size);

					//
					if(__Memory_Calculate_Node_Verify(Temp_Node_NEXT,Temp_Node->Size_Byte-New_Size-Memory_Node_Head_Size,Temp_Node->NEXT)!=Error_OK)
					{
						P_Memory_DATA->Flag.Unknown_Err=1;
						return Null;
					}
					//修正当前申请节点的长度
					if(__Memory_Calculate_Node_Verify(Temp_Node,New_Size,Null)!=Error_OK)
					{
						P_Memory_DATA->Flag.Unknown_Err=1;
						return Null;
					}

					//因为多出一个节点头，先减掉
					P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte-Memory_Node_Head_Size;
				}
				else//当前不能分割出下一个未使用的节点
				{
					Temp_Node_NEXT=Temp_Node->NEXT;

					//修正这个申请的节点
					if(__Memory_Calculate_Node_Verify(Temp_Node,Temp_Node->Size_Byte,Null)!=Error_OK)
					{
						P_Memory_DATA->Flag.Unknown_Err=1;
						return Null;
					}
				}
				//减掉这个申请的区域长度
				P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte-Temp_Node->Size_Byte;

				//将这个节点从Free链表中去除
				if(Temp_Node_LAST==Null || Temp_Node==P_Memory_DATA->Free.Begin)
				{
					P_Memory_DATA->Free.Begin=Temp_Node_NEXT;
				}
				else
				{
					if(__Memory_Calculate_Node_Verify(Temp_Node_LAST,Temp_Node_LAST->Size_Byte,Temp_Node_NEXT)!=Error_OK)
					{
						P_Memory_DATA->Flag.Unknown_Err=1;
						return Null;
					}

				}

#ifdef __Memory_TEST__
				if(__Memory_Test_List(&P_Memory_DATA->Free)!=Error_OK)
				{
					P_Memory_DATA->Flag.TEST_Free_Size_Err=1;

					int i=1;
					while(i)
					{
						old_Free_Size=old_Free_Size;
						New_Size=New_Size;
						Size=Size;
						Align=Align;
					}
				}
#endif
				//将申请的节点添加到Malloc链表中
				//
				P_Memory_DATA->Malloc.Size_Byte=P_Memory_DATA->Malloc.Size_Byte+Temp_Node->Size_Byte;

				if(P_Memory_DATA->Malloc.End!=Null)
				{
					if(__Memory_Check_Node_Verify(P_Memory_DATA->Malloc.End)!=Error_OK)
					{
						P_Memory_DATA->Flag.Malloc_Head_Err=1;
						return Null;
					}

					if(__Memory_Calculate_Node_Verify(P_Memory_DATA->Malloc.End,P_Memory_DATA->Malloc.End->Size_Byte,Temp_Node)!=Error_OK)
					{
						P_Memory_DATA->Flag.Unknown_Err=1;
						return Null;
					}
					P_Memory_DATA->Malloc.End=Temp_Node;
				}
				else
				{
					P_Memory_DATA->Malloc.Begin=Temp_Node;
					P_Memory_DATA->Malloc.End=Temp_Node;
				}

#ifdef __Memory_TEST__
				//Test
				if(__Memory_Test_List(&P_Memory_DATA->Malloc)!=Error_OK)
				{
					P_Memory_DATA->Flag.TEST_Malloc_Size_Err=1;

					int i=1;
					while(i);
				}
				if(__Memory_Test_List(&P_Memory_DATA->Free)!=Error_OK)
				{
					P_Memory_DATA->Flag.TEST_Free_Size_Err=1;

					int i=1;
					while(i);
				}
#endif
				//返回这个节点的数据首地址
				return (void *)((uint32_t)Temp_Node+Memory_Node_Head_Size+Size_Align);

			}
			else//地址对齐误差大于等于一个节点头，那么可以尝试切割成2个数据块
			{
				//计算是否能满足切割
				if(Temp_Node->Size_Byte>(Memory_Node_Head_Size+New_Size))
				{

					Memory_Node_Type *Temp_Node_Split;

					//计算出地址对齐的节点的首地址
					Temp_Node_Split=(Memory_Node_Type *)(Begin_Address+Size_Align-Memory_Node_Head_Size);


					//分割成一个满足需求的节点
					if(__Memory_Calculate_Node_Verify(Temp_Node_Split,Temp_Node->Size_Byte-(Size_Align-Memory_Node_Head_Size)-Memory_Node_Head_Size,Temp_Node->NEXT)!=Error_OK)
					{
						P_Memory_DATA->Flag.Unknown_Err=1;
						return Null;
					}

					//修正当前被被分割的节点
					if(__Memory_Calculate_Node_Verify(Temp_Node,Size_Align-Memory_Node_Head_Size,Temp_Node_Split)!=Error_OK)
					{
						P_Memory_DATA->Flag.Unknown_Err=1;
						return Null;
					}

					//减去这个分割出来的节点头
					P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte-Memory_Node_Head_Size;
				}
				

			}



		}

		Temp_Node_LAST=Temp_Node;

		Temp_Node=Temp_Node->NEXT;

	}
	P_Memory_DATA->Flag.Null_Err=1;
	return Null;


}

void __Memory_Free(Memory_DATA_Type *P_Memory_DATA,void *ap)
{
	if(P_Memory_DATA==Null || ap==Null)
	{
		return ;
	}

#ifdef __Memory_TEST__
	//Test
	if(__Memory_Test_List(&P_Memory_DATA->Malloc)!=Error_OK)
	{
		P_Memory_DATA->Flag.TEST_Malloc_Size_Err=1;

		int i=1;
		while(i);
	}
	if(__Memory_Test_List(&P_Memory_DATA->Free)!=Error_OK)
	{
		P_Memory_DATA->Flag.TEST_Free_Size_Err=1;

		int i=1;
		while(i);
	}
#endif

	Memory_Node_Type *Temp_Node,*Temp_Node_LAST=Null,*Temp_Node_NEXT=Null,*Temp_Node_Free=Null;

	Temp_Node=P_Memory_DATA->Malloc.Begin;

	//从Malloc链表中找到需要释放的节点
	while(Temp_Node!=Null)
	{
		//检验数据块头是否正确
		if(__Memory_Check_Node_Verify(Temp_Node)!=Error_OK)
		{
			P_Memory_DATA->Flag.Free_Head_Err=1;

			return ;
		}

		uint32_t Begin_Address_Free=(uint32_t)Temp_Node+Memory_Node_Head_Size;
		uint32_t End_Adress_Free=Begin_Address_Free+Temp_Node->Size_Byte-1;

		//找到这个需要释放的节点
		if((Begin_Address_Free<=(uint32_t)ap) && (uint32_t)ap<=End_Adress_Free)
		{
			//先从Malloc链表中将当前需要释放的节点剔除
			if(Temp_Node_LAST==Null || Temp_Node==P_Memory_DATA->Malloc.Begin)
			{
				P_Memory_DATA->Malloc.Begin=Temp_Node->NEXT;
			}
			else
			{
				if(__Memory_Calculate_Node_Verify(Temp_Node_LAST,Temp_Node_LAST->Size_Byte,Temp_Node->NEXT)!=Error_OK)
				{
					P_Memory_DATA->Flag.Unknown_Err=1;
					return ;
				}

				//Temp_Node_LAST->NEXT=Temp_Node->NEXT;
			}

			if(Temp_Node==P_Memory_DATA->Malloc.End || Temp_Node->NEXT==Null)
			{
				P_Memory_DATA->Malloc.End=Temp_Node_LAST;

			}
			P_Memory_DATA->Malloc.Size_Byte=P_Memory_DATA->Malloc.Size_Byte-Temp_Node->Size_Byte;

			//将回收的节点放到free中
			Temp_Node_Free=Temp_Node;

			Temp_Node=P_Memory_DATA->Free.Begin;


			Begin_Address_Free=(uint32_t)Temp_Node_Free;
			End_Adress_Free=Begin_Address_Free+Memory_Node_Head_Size+Temp_Node_Free->Size_Byte;

			//从Free中找到合适的位置放进去或者合并掉
			while(Temp_Node!=Null)
			{

				//检验数据块头是否正确
				if(__Memory_Check_Node_Verify(Temp_Node)!=Error_OK)
				{
					P_Memory_DATA->Flag.Free_Head_Err=1;

					return ;
				}
				Temp_Node_NEXT=Temp_Node->NEXT;

				//找出合适的上一节和下一节，然后 上一节 中间 下一节合并
				//假设上一节为LAST，Free为中间，下一节为NEXT
				//LAST为当前Temp_Node
				//那么有三种假设

				//Free<LAST || Free==LAST

				//(LAST<Free || LAST==Free) && (Free<NEXT || Free==NEXT)

				//NEXT<Free || NEXT==Free


				//
				if(Temp_Node==P_Memory_DATA->Free.Begin)
				{
					//Free<LAST || Free==LAST

					//释放的节点的地址在当前节点之前
					if(End_Adress_Free<=(uint32_t)Temp_Node)
					{
						//释放的节点可以和当前节点合并
						if(End_Adress_Free==(uint32_t)Temp_Node)
						{
							//
							P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte+Temp_Node_Free->Size_Byte+Memory_Node_Head_Size;

							if(__Memory_Calculate_Node_Verify(Temp_Node_Free,Temp_Node_Free->Size_Byte+Temp_Node->Size_Byte+Memory_Node_Head_Size,Temp_Node->NEXT)!=Error_OK)
							{
								P_Memory_DATA->Flag.Unknown_Err=1;
								return ;
							}

						}
						else//End_Adress_Free<(uint32_t)Temp_Node//不能合并，插入到头之前
						{
							P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte+Temp_Node_Free->Size_Byte;

							if(__Memory_Calculate_Node_Verify(Temp_Node_Free,Temp_Node_Free->Size_Byte,Temp_Node)!=Error_OK)
							{
								P_Memory_DATA->Flag.Unknown_Err=1;
								return ;
							}

						}

						P_Memory_DATA->Free.Begin=Temp_Node_Free;

#ifdef __Memory_TEST__
						//Test
						if(__Memory_Test_List(&P_Memory_DATA->Malloc)!=Error_OK)
						{
							P_Memory_DATA->Flag.TEST_Malloc_Size_Err=1;

							int i=1;
							while(i);
						}
						if(__Memory_Test_List(&P_Memory_DATA->Free)!=Error_OK)
						{
							P_Memory_DATA->Flag.TEST_Free_Size_Err=1;

							int i=1;
							while(i);
						}
#endif

						return ;
					}
				}
				//
				if(Temp_Node_NEXT!=Null)
				{
					//检验数据块头是否正确
					if(__Memory_Check_Node_Verify(Temp_Node_NEXT)!=Error_OK)
					{
						P_Memory_DATA->Flag.Free_Head_Err=1;

						return ;
					}

					uint32_t Begin_Address_LAST=(uint32_t)Temp_Node;
					uint32_t End_Adress_LAST=Begin_Address_LAST+Memory_Node_Head_Size+Temp_Node->Size_Byte;

					uint32_t Begin_Address_NEXT=(uint32_t)Temp_Node_NEXT;
					//uint32_t End_Adress_NEXT=Begin_Address_NEXT+Temp_Node_NEXT->Size_Byte+Memory_Node_Head_Size;

					//(LAST<Free || LAST==Free) && (Free<NEXT || Free==NEXT)
					if(End_Adress_LAST<=Begin_Address_Free && End_Adress_Free<=Begin_Address_NEXT)
					{
						//先看前半段
						//(LAST<Free || LAST==Free)
						if(End_Adress_LAST<Begin_Address_Free)//不能合并插到后面
						{
							P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte+Temp_Node_Free->Size_Byte;

							if(__Memory_Calculate_Node_Verify(Temp_Node,Temp_Node->Size_Byte,Temp_Node_Free)!=Error_OK)
							{
								P_Memory_DATA->Flag.Unknown_Err=1;
								return ;
							}

						}
						else if(End_Adress_LAST==Begin_Address_Free)//可以合并
						{
							P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte+(Memory_Node_Head_Size+Temp_Node_Free->Size_Byte);

							if(__Memory_Calculate_Node_Verify(Temp_Node,Temp_Node->Size_Byte+(Memory_Node_Head_Size+Temp_Node_Free->Size_Byte),Temp_Node->NEXT)!=Error_OK)
							{
								P_Memory_DATA->Flag.Unknown_Err=1;
								return ;
							}
							//如果合并那么当前这个节点便是释放的节点了
							Temp_Node_Free=Temp_Node;
						}
						else//不可能存在
						{
							P_Memory_DATA->Flag.Unknown_Err=1;
							return ;
						}

						//后半段
						//(Free<NEXT || Free==NEXT)
						if(End_Adress_Free<Begin_Address_NEXT)//不能合并
						{
							if(__Memory_Calculate_Node_Verify(Temp_Node_Free,Temp_Node_Free->Size_Byte,Temp_Node_NEXT)!=Error_OK)
							{
								P_Memory_DATA->Flag.Unknown_Err=1;
								return ;
							}

						}
						else if(End_Adress_Free==Begin_Address_NEXT)//可以合并
						{
							//因为NEXT的节点空间已经算在内了，所以合并后只能多出一个NEXT的节点头大小
							P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte+(Memory_Node_Head_Size+0);

							if(__Memory_Calculate_Node_Verify(Temp_Node_Free,Temp_Node_Free->Size_Byte+(Memory_Node_Head_Size+Temp_Node_NEXT->Size_Byte),Temp_Node_NEXT->NEXT)!=Error_OK)
							{
								P_Memory_DATA->Flag.Unknown_Err=1;
								return ;
							}
						}
						else//不可能存在
						{
							P_Memory_DATA->Flag.Unknown_Err=1;
							return ;
						}
#ifdef __Memory_TEST__
						//Test
						if(__Memory_Test_List(&P_Memory_DATA->Malloc)!=Error_OK)
						{
							P_Memory_DATA->Flag.TEST_Malloc_Size_Err=1;

							int i=1;
							while(i);
						}
						if(__Memory_Test_List(&P_Memory_DATA->Free)!=Error_OK)
						{
							P_Memory_DATA->Flag.TEST_Free_Size_Err=1;

							int i=1;
							while(i);
						}
#endif
						return ;
					}


				}
				else if(Temp_Node_NEXT==Null)
				{
					//当前是最后一个节点了

					//NEXT<Free || NEXT==Free
					uint32_t Begin_Address_LAST=(uint32_t)Temp_Node;
					//uint32_t End_Adress_LAST=Begin_Address_LAST+Temp_Node->Size_Byte+Memory_Node_Head_Size;

					if(Begin_Address_LAST<Begin_Address_Free)//不能合并
					{
						P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte+Temp_Node_Free->Size_Byte;

						if(__Memory_Calculate_Node_Verify(Temp_Node,Temp_Node->Size_Byte,Temp_Node_Free)!=Error_OK)
						{
							P_Memory_DATA->Flag.Unknown_Err=1;
							return ;
						}

						if(__Memory_Calculate_Node_Verify(Temp_Node_Free,Temp_Node_Free->Size_Byte,Null)!=Error_OK)
						{
							P_Memory_DATA->Flag.Unknown_Err=1;
							return ;
						}
					}
					else if(Begin_Address_LAST==Begin_Address_Free)//可以合并
					{
						P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte+(Memory_Node_Head_Size+Temp_Node_Free->Size_Byte);

						if(__Memory_Calculate_Node_Verify(Temp_Node,Temp_Node->Size_Byte+(Memory_Node_Head_Size+Temp_Node_Free->Size_Byte),Null)!=Error_OK)
						{
							P_Memory_DATA->Flag.Unknown_Err=1;
							return ;
						}
					}
					else//不可能存在
					{
						P_Memory_DATA->Flag.Unknown_Err=1;
						return ;
					}
#ifdef __Memory_TEST__
					//Test
					if(__Memory_Test_List(&P_Memory_DATA->Malloc)!=Error_OK)
					{
						P_Memory_DATA->Flag.TEST_Malloc_Size_Err=1;

						int i=1;
						while(i);
					}
					if(__Memory_Test_List(&P_Memory_DATA->Free)!=Error_OK)
					{
						P_Memory_DATA->Flag.TEST_Free_Size_Err=1;

						int i=1;
						while(i);
					}
#endif
					return ;
				}

				Temp_Node=Temp_Node->NEXT;
			}
			//这是一个特殊情况 当前Free链表中没有任何数据
			if(P_Memory_DATA->Free.Begin==Null)
			{
				P_Memory_DATA->Free.Size_Byte=P_Memory_DATA->Free.Size_Byte+Temp_Node_Free->Size_Byte;

				if(__Memory_Calculate_Node_Verify(Temp_Node_Free,Temp_Node_Free->Size_Byte,Null)!=Error_OK)
				{
					P_Memory_DATA->Flag.Unknown_Err=1;
					return ;
				}
				P_Memory_DATA->Free.Begin=Temp_Node_Free;
#ifdef __Memory_TEST__
				//Test
				if(__Memory_Test_List(&P_Memory_DATA->Malloc)!=Error_OK)
				{
					P_Memory_DATA->Flag.TEST_Malloc_Size_Err=1;

					int i=1;
					while(i);
				}
				if(__Memory_Test_List(&P_Memory_DATA->Free)!=Error_OK)
				{
					P_Memory_DATA->Flag.TEST_Free_Size_Err=1;

					int i=1;
					while(i);
				}
#endif
				return ;
			}
			else//出错
			{
				P_Memory_DATA->Flag.Unknown_Err=1;
				return ;
			}

		}


		Temp_Node_LAST=Temp_Node;

		Temp_Node=Temp_Node->NEXT;
	}

	//没有找到？当前需要释放的空间不存在？
	P_Memory_DATA->Flag.Free_Err=1;
	return ;


}
int __Memory_Calculate_Node_Verify(Memory_Node_Type *P_Node_DATA,uint32_t Size_Byte,Memory_Node_Type *P_Node_NEXT)
{
	if(P_Node_DATA==Null || Size_Byte>0x3FFFFFFF)
	{
		return Error_Invalid_Parameter;
	}
	P_Node_DATA->Size_Byte=Size_Byte;
	P_Node_DATA->NEXT=P_Node_NEXT;

	//Size_Byte=Size_Byte&0x3FFFFFFF;

	uint32_t NEXT_DATA=(uint32_t)P_Node_NEXT;

	int Sum_Size=0;
	int Sum_NEXT=0;
	for(int i=0;i<32;i++)
	{
		Sum_Size=Sum_Size+((Size_Byte>>i)&0x01);
		Sum_NEXT=Sum_NEXT+((NEXT_DATA>>i)&0x01);
	}
	P_Node_DATA->Flag_Size=Sum_Size&0x01;
	P_Node_DATA->Flag_NEXT=Sum_NEXT&0x01;

	return Error_OK;
}
int __Memory_Check_Node_Verify(Memory_Node_Type *P_Node_DATA)
{
	if(P_Node_DATA==Null)
	{
		return Error_Invalid_Parameter;
	}
	uint32_t Size_Byte=P_Node_DATA->Size_Byte;
	uint32_t NEXT_DATA=(uint32_t)P_Node_DATA->NEXT;

	int Sum_Size=0;
	int Sum_NEXT=0;
	for(int i=0;i<32;i++)
	{
		Sum_Size=Sum_Size+((Size_Byte>>i)&0x01);
		Sum_NEXT=Sum_NEXT+((NEXT_DATA>>i)&0x01);
	}

	if(	P_Node_DATA->Flag_Size!=(Sum_Size&0x01)
	|| P_Node_DATA->Flag_NEXT!=(Sum_NEXT&0x01))
	{
		return Error_Illegal;
	}
	return Error_OK;
}


