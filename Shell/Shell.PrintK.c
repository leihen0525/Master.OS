/*
 * Shell.PrintK.c
 *
 *  Created on: 2019年9月23日
 *      Author: Master.HE
 */
#include <stdarg.h>
#include <string.h>

#include "Error.h"

#include "Master.Stdint.h"

#include "Shell.UART.h"

#include "Shell.PrintK.Define.h"

#include "Shell.PrintK.h"

typedef union
{
	uint8_t DATA;
	struct
	{
		uint8_t Flags_Minus				:1;//'-'
		uint8_t Flags_Plus				:1;//'+'
		uint8_t Flags_Space				:1;//' '
		uint8_t Flags_Zero				:1;//' '

		uint8_t Flags_Pound				:1;//'#'
		uint8_t Done					:1;
		uint8_t Precision_used			:1;
	};
}PrintK_Flags_Type;

typedef struct
{

	int ns;
	int width;

	int Precision;
	int i;
	int ii;
	union
	{
		int ival;
		unsigned int uval ;
		unsigned int Temp;
		uint8_t *sval;
	};

	union
	{
		char schar;
		char Xiaoxie;
	};



	uint8_t IntLen;
	uint8_t Temp_DATA[12];
}Printf_DATA_Type;


//typedef long long LL;
int pows(int base, int exponent);
int pows(int base, int exponent)
{
	int ans = 1;
	for (int i = 0; i < exponent; ++i)
	{
		ans *= base;
	}
	return ans;
}

uint8_t Printk_Calculate_Int_Len(int N,int radix,bool fh);
uint8_t Printk_Calculate_Int_Len(int N,int radix,bool fh)
{
	uint8_t Len=0;

	if(fh==false)
	{
		uint32_t n=N;

		if(n==0)return 1;


		while(n)
		{
			n=n/radix;
			Len++;
		}
		return Len;

	}
	else
	{
		if(N==0)return 1;

		if(N<0)N=-N;

		while(N)
		{
			N=N/radix;
			Len++;
		}
		return Len;
	}


}

Printf_DATA_Type SDP_DATA;

int __Sys_PrintK(const char *Format,...)
{
	int Err;

	int length=0;

	va_list ap;

	va_start(ap,Format);     //将ap指向第一个实际参数的地址

	while(*Format)
	{
		if(*Format != '%')
		{
			if(*Format !='\n')
			{
				if((Err=Shell_UART_Tx_DATA((uint8_t *)Format,1))!=Error_OK)
				{
					return Err;
				}
				length+=1;
			}
			else
			{

				if((Err=Shell_UART_Tx_DATA("\r\n",2))!=Error_OK)
				{
					return Err;
				}
				length+=2;
			}
		}
		else
		{
			//Flags
			PrintK_Flags_Type Flags;
			Flags.DATA=0;
			Flags.Done=true;
			while(Flags.Done)
			{
				switch (*++Format)
				{
					case '-':
					{
						Flags.Flags_Minus=1;
					}break;
					case '+':
					{
						Flags.Flags_Plus=1;
					}break;
					case ' ':
					{
						Flags.Flags_Space=1;
					}break;
					case '0':
					{
						Flags.Flags_Zero=1;
					}break;
					case '#':
					{
						Flags.Flags_Pound=1;
					}break;
					default:
					{
						--Format;
						Flags.Done = false;
					}break;

				}
			}

			//width
			SDP_DATA.width=0;

			Flags.Done=true;

			while (Flags.Done)
			{
				switch (*++Format)
				{
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					{
						SDP_DATA.width = (SDP_DATA.width * 10) + (*Format - '0');
					}break;
					case '*':
					{
						SDP_DATA.width=va_arg(ap,int);

						Flags.Done = false;
					}break;
					default:
					{
						--Format;
						Flags.Done = false;
					}break;
				}
			}
			SDP_DATA.Precision=0;

			if(*++Format=='.')
			{
				Flags.Precision_used=true;
				Flags.Done=true;

				while (Flags.Done)
				{
					switch (*++Format)
					{
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						{
							SDP_DATA.Precision = (SDP_DATA.Precision * 10) + (*Format - '0');
						}break;
						case '*':
						{
							SDP_DATA.Precision=va_arg(ap,int);

							Flags.Done = false;
						}break;
						default:
						{
							--Format;
							Flags.Done = false;
						}break;
					}
				}
			}
			else
			{
				--Format;
				Flags.Precision_used=false;
			}

			switch (*++Format)
			{
				case 'h':
					/* length_modifier |= LENMOD_h; */
					break;
				case 'l':
					/* length_modifier |= LENMOD_l; */
					break;
				case 'L':
					/* length_modifier |= LENMOD_L; */
					break;
				default:
					/* we've gone one char too far */
					--Format;
					break;
			}

			switch(*++Format)
			{

				//输出十进制有符号32bits整数，i是老式写法
				case 'd':
				case 'i':
				{

					SDP_DATA.ival = (int)va_arg(ap, int);



					if(SDP_DATA.ival<0)
					{
						SDP_DATA.schar='-';
						SDP_DATA.width=SDP_DATA.width-1;
					}
					else
					{
						if(Flags.Flags_Plus==1)
						{
							SDP_DATA.schar='+';
							SDP_DATA.width=SDP_DATA.width-1;
						}
						else
						{
							if(Flags.Flags_Space==1)
							{
								SDP_DATA.schar=' ';
								SDP_DATA.width=SDP_DATA.width-1;
							}
							else
							{
								SDP_DATA.schar=0;
							}
						}
					}
					SDP_DATA.IntLen=Printk_Calculate_Int_Len(SDP_DATA.ival,10,true);
					SDP_DATA.width=SDP_DATA.width-SDP_DATA.IntLen;
					if(Flags.Flags_Zero==1)
					{
						if(SDP_DATA.schar)
						{

							if((Err=Shell_UART_Tx_DATA((uint8_t *)&SDP_DATA.schar,1))!=Error_OK)
							{
								return Err;
							}
							length+=1;
						}

						Printk_Same_Char(SDP_DATA.width,'0');
						//width=0;
					}
					else
					{
						if(Flags.Flags_Minus==0)
						{
							Printk_Same_Char(SDP_DATA.width,' ');
						}
						if(SDP_DATA.schar)
						{
							if((Err=Shell_UART_Tx_DATA((uint8_t *)&SDP_DATA.schar,1))!=Error_OK)
							{
								return Err;
							}
							length+=1;
						}

					}
					if(SDP_DATA.ival<0)SDP_DATA.ival=-SDP_DATA.ival;
					for(SDP_DATA.i=SDP_DATA.IntLen-1;0<=SDP_DATA.i;SDP_DATA.i--)
					{
						SDP_DATA.ns=(SDP_DATA.ival/(int)pows(10,SDP_DATA.i)%10);

						System_HMI_PutChar(&SDP_DATA.Len,SDP_DATA.Temp_DATA,&SDP_DATA.Index,(uint8_t)'0'+SDP_DATA.ns);
					}


					if(Flags.Flags_Minus==1 && Flags.Flags_Zero==0)
					{
						Printk_Same_Char(SDP_DATA.width,' ');
					}


				}break;
/*
				//无符号8进制(octal)整数(不输出前缀0)
				case 'o':
				{

				}break;

				//无符号10进制整数
				case 'u':
				{

				}break;
*/
				//无符号16进制整数，x对应的是abcdef，X对应的是ABCDEF（不输出前缀0x)
				case 'x':
				case 'X':
				{
					SDP_DATA.Xiaoxie=0;
					if(*Format=='x')SDP_DATA.Xiaoxie=32;



					SDP_DATA.uval = (unsigned int)va_arg(ap, unsigned int);

					SDP_DATA.IntLen=Printk_Calculate_Int_Len(SDP_DATA.uval,16,false);
					SDP_DATA.width=SDP_DATA.width-SDP_DATA.IntLen;

					if(Flags.Flags_Pound==1)
					{
						SDP_DATA.width=SDP_DATA.width-2;
					}

					if(Flags.Flags_Zero==1)
					{
						if(Flags.Flags_Pound==1)
						{
							if((Err=Shell_UART_Tx_DATA("0x",2))!=Error_OK)
							{
								return Err;
							}
							length+=2;
						}
						Printk_Same_Char(SDP_DATA.width,'0');
					}
					else
					{
						if(Flags.Flags_Minus==0)
						{
							Printk_Same_Char(SDP_DATA.width,' ');

							if(Flags.Flags_Pound==1)
							{
								if((Err=Shell_UART_Tx_DATA("0x",2))!=Error_OK)
								{
									return Err;
								}
								length+=2;
							}

						}
						else
						{
							if(Flags.Flags_Pound==1)
							{
								if((Err=Shell_UART_Tx_DATA("0x",2))!=Error_OK)
								{
									return Err;
								}
								length+=2;
							}
						}
					}

					for(SDP_DATA.i=SDP_DATA.IntLen-1;0<=SDP_DATA.i;SDP_DATA.i--)
					{
						SDP_DATA.ns=(SDP_DATA.uval/(int)pows(16,SDP_DATA.i)%16);

						if(SDP_DATA.ns<10)
						{
							System_HMI_PutChar(&SDP_DATA.Len,SDP_DATA.Temp_DATA,&SDP_DATA.Index,(uint8_t)'0'+SDP_DATA.ns);
						}
						else
						{
							System_HMI_PutChar(&SDP_DATA.Len,SDP_DATA.Temp_DATA,&SDP_DATA.Index,(uint8_t)'A'+SDP_DATA.ns-10+SDP_DATA.Xiaoxie);
						}
					}


					if(Flags.Flags_Minus==1 && Flags.Flags_Zero==0)
					{
						Printk_Same_Char(SDP_DATA.width,' ');
					}

				}break;
				/*
				//单精度浮点数用f,双精度浮点数用lf(printf可混用，但scanf不能混用)
				case 'f':
				{

				}break;

				case 'l':
				{

				}break;
				//与f格式相同，只不过 infinity 和 nan 输出为大写形式。
				case 'F':
				{

				}break;

				//科学计数法，使用指数(Exponent)表示浮点数，此处”e”的大小写代表在输出时“e”的大小写
				case 'e':
				case 'E':
				{

				}break;

				//根据数值的长度，选择以最短的方式输出，%f或%e
				case 'g':
				{

				}break;
				//根据数值的长度，选择以最短的方式输出，%f或%E
				case 'G':
				{

				}break;
*/
				//字符型。可以把输入的数字按照ASCII码相应转换为对应的字符
				case 'c':
				{

					SDP_DATA.Temp=(char)va_arg(ap, unsigned int);

					System_HMI_PutChar(&SDP_DATA.Len,SDP_DATA.Temp_DATA,&SDP_DATA.Index,(uint8_t)SDP_DATA.Temp);
				}break;

				//字符串。输出字符串中的字符直至字符串中的空字符（字符串以空字符’\0‘结尾）
				case 's':
				{

					SDP_DATA.sval= (char *)va_arg(ap, char *);

					if(SDP_DATA.sval!=Null)
					{
						SDP_DATA.width=SDP_DATA.width-strlen(SDP_DATA.sval);

						if(Flags.Flags_Minus==0)
						{
							Printk_Same_Char(SDP_DATA.width,' ');

						}
						while(*SDP_DATA.sval)
						{
							System_HMI_PutChar(&SDP_DATA.Len,SDP_DATA.Temp_DATA,&SDP_DATA.Index,(uint8_t)*SDP_DATA.sval++);
						}
						if(Flags.Flags_Minus==1)
						{
							Printk_Same_Char(SDP_DATA.width,' ');
						}
					}

				}break;
/*
				//宽字符串。输出字符串中的字符直至字符串中的空字符（宽字符串以两个空字符’\0‘结尾）
				case 'S':
				{

				}break;

				//以16进制形式输出指针
				case 'p':
				{

				}break;

				//什么也不输出。%n对应的参数是一个指向signed int的指针，在此之前输出的字符数将存储到指针所指的位置
				case 'n':
				{

				}break;

				//输出字符‘%’（百分号）本身
				case '%':
				{

				}break;

				//打印errno值对应的出错内容
				case 'm':
				{

				}break;

				//十六进制p计数法输出浮点数，a为小写，A为大写
				case 'a':
				case 'A':
				{

				}break;
*/
				default:
				{
					if((Err=Shell_UART_Tx_DATA((uint8_t *)Format,1))!=Error_OK)
					{
						return Err;
					}
					length+=1;
				}break;


			}
		}
		Format++;
	}
	va_end(ap);


	return length;
}
