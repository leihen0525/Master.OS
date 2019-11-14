/*
 * IRQ.c
 *
 *  Created on: 2019Äê4ÔÂ15ÈÕ
 *      Author: Master.HE
 */
#include "Master.Stdint.h"

#include "Error.h"

#include "IRQ.Struct.h"

#include "IRQ.h"

#include "Define.h"

#include "__Sys.API.h"

#include "Memory/Memory.h"

IRQ_DATA_Type IRQ_DATA;

int IRQ_Init(Machine_Desc_IRQ_Type *P_IRQ)
{
	if(P_IRQ==Null)
	{
		return Error_Invalid_Parameter;
	}

	IRQ_DATA.IRQ=P_IRQ;

	if(IRQ_DATA.IRQ->Init==Null
	|| IRQ_DATA.IRQ->Disable==Null
	|| IRQ_DATA.IRQ->Enable==Null
	|| IRQ_DATA.IRQ->Set_Priority==Null
	|| IRQ_DATA.IRQ->All_Disable==Null
	|| IRQ_DATA.IRQ->All_Enable==Null
	|| IRQ_DATA.IRQ->Get_IRQ_Index==Null
	|| IRQ_DATA.IRQ->Clear_IRQ_Flag==Null)
	{
		return Error_Undefined;
	}

	int Err=IRQ_DATA.IRQ->Init();

	if(Err!=Error_OK)
	{
		return Err;
	}

	IRQ_DATA.IRQ_Hook_Node_List=__Sys_Memory_Malloc(IRQ_DATA.IRQ->IRQ_Max_Index*sizeof(IRQ_Hook_Node_Type *));

	if(IRQ_DATA.IRQ_Hook_Node_List==Null)
	{
		return Error_Allocation_Memory_Failed;
	}


	for(int i=0;i<IRQ_DATA.IRQ->IRQ_Max_Index;i++)
	{
		IRQ_DATA.IRQ_Hook_Node_List[i]=Null;
	}

	return Error_OK;

}


int __Sys_IRQ_Enable(int IRQ_Index)
{
	if(IRQ_DATA.IRQ==Null)
	{
		return Error_Unknown;
	}
	if(IRQ_DATA.IRQ->IRQ_Max_Index<=IRQ_Index)
	{
		return Error_Invalid_Parameter;
	}
	if(IRQ_DATA.IRQ->Enable==Null)
	{
		return Error_Undefined;
	}

	return IRQ_DATA.IRQ->Enable(IRQ_Index);
}
int __Sys_IRQ_Disable(int IRQ_Index)
{
	if(IRQ_DATA.IRQ==Null)
	{
		return Error_Unknown;
	}
	if(IRQ_DATA.IRQ->IRQ_Max_Index<=IRQ_Index)
	{
		return Error_Invalid_Parameter;
	}
	if(IRQ_DATA.IRQ->Disable==Null)
	{
		return Error_Undefined;
	}

	return IRQ_DATA.IRQ->Disable(IRQ_Index);

}
int __Sys_IRQ_Set_Priority(int IRQ_Index,int Priority)
{
	if(IRQ_DATA.IRQ==Null)
	{
		return Error_Unknown;
	}
	if(IRQ_DATA.IRQ->IRQ_Max_Index<=IRQ_Index)
	{
		return Error_Invalid_Parameter;
	}
	if(IRQ_DATA.IRQ->Set_Priority==Null)
	{
		return Error_Undefined;
	}

	return IRQ_DATA.IRQ->Set_Priority(IRQ_Index,Priority);

}
int __Sys_IRQ_All_Enable(void)
{
	if(IRQ_DATA.IRQ==Null)
	{
		return Error_Unknown;
	}
	if(IRQ_DATA.IRQ->All_Enable==Null)
	{
		return Error_Undefined;
	}

	return IRQ_DATA.IRQ->All_Enable();
}
int __Sys_IRQ_All_Disable(void)
{
	if(IRQ_DATA.IRQ==Null)
	{
		return Error_Unknown;
	}
	if(IRQ_DATA.IRQ->All_Disable==Null)
	{
		return Error_Undefined;
	}

	return IRQ_DATA.IRQ->All_Disable();
}
int __Sys_IRQ_Register_Hook(
		int IRQ_Index,
		IRQ_Hook_Function Hook_Function,
		void *Args)
{
	if(IRQ_DATA.IRQ==Null)
	{
		return Error_Unknown;
	}

	if(IRQ_Index<0 || IRQ_DATA.IRQ->IRQ_Max_Index<=IRQ_Index || Hook_Function==Null)
	{
		return Error_Invalid_Parameter;
	}

	int Handle=__Sys_Apply_Handle();
	if(Handle<Valid_Handle)
	{
		return Handle;
	}

	IRQ_Hook_Node_Type *Temp_Node=__Sys_Memory_Malloc(sizeof(IRQ_Hook_Node_Type));

	if(Temp_Node==Null)
	{
		return Error_Allocation_Memory_Failed;
	}
	Temp_Node->Handle=Handle;
	Temp_Node->Args=Args;
	Temp_Node->Function=Hook_Function;
	Temp_Node->NEXT=Null;


	if(IRQ_DATA.IRQ_Hook_Node_List[IRQ_Index]==Null)
	{
		IRQ_DATA.IRQ_Hook_Node_List[IRQ_Index]=Temp_Node;
	}
	else
	{
		IRQ_Hook_Node_Type *P_Node_Temp=IRQ_DATA.IRQ_Hook_Node_List[IRQ_Index];

		while(1)
		{
			if(P_Node_Temp->NEXT==Null)
			{
				P_Node_Temp->NEXT=Temp_Node;
				break;
			}
			P_Node_Temp=P_Node_Temp->NEXT;
		}
	}
	return Temp_Node->Handle;
}
int __Sys_IRQ_Delete_Hook(int IRQ_Index,int Handle)
{
	if(IRQ_DATA.IRQ==Null)
	{
		return Error_Unknown;
	}

	if(IRQ_Index<0 || IRQ_DATA.IRQ->IRQ_Max_Index<=IRQ_Index )
	{
		return Error_Invalid_Parameter;
	}
	if(Handle<Valid_Handle)
	{
		return Error_Invalid_Handle;
	}

	IRQ_Hook_Node_Type *P_Node_LAST=Null;

	IRQ_Hook_Node_Type *P_Node_Temp=IRQ_DATA.IRQ_Hook_Node_List[IRQ_Index];


	while(P_Node_Temp!=Null)
	{
		if(P_Node_Temp->Handle==Handle)
		{
			if(P_Node_LAST==Null || P_Node_Temp==IRQ_DATA.IRQ_Hook_Node_List[IRQ_Index])
			{
				IRQ_DATA.IRQ_Hook_Node_List[IRQ_Index]=P_Node_Temp->NEXT;
			}
			else
			{
				P_Node_LAST->NEXT=P_Node_Temp->NEXT;
			}

			__Sys_Memory_Free(P_Node_Temp);

			return Error_OK;
		}
		P_Node_LAST=P_Node_Temp;

		P_Node_Temp=P_Node_Temp->NEXT;
	}

	return Error_Invalid_Handle;
}


void __IRQ_Entry(void)
{
	if(IRQ_DATA.IRQ==Null)
	{
		return ;
	}
	if(IRQ_DATA.IRQ->Get_IRQ_Index==Null)
	{
		return ;
	}
	int IRQ_Index=IRQ_DATA.IRQ->Get_IRQ_Index();

	if(IRQ_Index<0 || IRQ_DATA.IRQ->IRQ_Max_Index<=IRQ_Index)
	{
		return ;
	}

	if(IRQ_DATA.IRQ->Clear_IRQ_Flag!=Null)
	{
		IRQ_DATA.IRQ->Clear_IRQ_Flag(IRQ_Index);
	}

	IRQ_Hook_Node_Type *P_Node_Temp=IRQ_DATA.IRQ_Hook_Node_List[IRQ_Index];

	while(P_Node_Temp!=Null)
	{
		P_Node_Temp->Function(P_Node_Temp->Args,IRQ_Index);

		P_Node_Temp=P_Node_Temp->NEXT;
	}


}


