/*
 * display.c
 *
 *  Created on: 27 mar 2018
 *      Author: st-wasik
 */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "../inc/display.h"

//Global const
//Choose digit
const uint32_t digit[10]={
		/*0*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7,
		/*1*/ GPIO_Pin_1 | GPIO_Pin_2,
		/*2*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_4,
		/*3*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_2 | GPIO_Pin_4,
		/*4*/ GPIO_Pin_7 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_2,
		/*5*/ GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_2 | GPIO_Pin_4,
		/*6*/ GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_2,
		/*7*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2,
		/*8*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8,
		/*9*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_2 | GPIO_Pin_4
};
const uint32_t ALL_Digit = GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_11 ;

//Choose letter
const uint32_t A = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_2;
const uint32_t B = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_2 | GPIO_Pin_4;
const uint32_t C = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_4;
const uint32_t D = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8 | GPIO_Pin_4 | GPIO_Pin_5;
const uint32_t E = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_2 | GPIO_Pin_4;
const uint32_t F = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_8;
const uint32_t G = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_2;
const uint32_t H = GPIO_Pin_7 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_2;
const uint32_t Dot = GPIO_Pin_11;

//Choose segment
const uint32_t Num1 = GPIO_Pin_12;
const uint32_t Num2 = GPIO_Pin_13;
const uint32_t Num3 = GPIO_Pin_14;
const uint32_t Num4 = GPIO_Pin_15;
const uint32_t ALL_Num = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

// use chars a-h, 0-9 only
char on_screen[4]={'a','b','c','d'};
//END:Global const

void set_screen(char screen[])
{
	for(int i=0;i<4;i++)
	{
		on_screen[i] = screen[i];
	}
}

void display_update()
{
	for (int i=0;i<4;i++)
	{
		GPIO_ResetBits(GPIOB,ALL_Num);
		GPIO_ResetBits(GPIOB,ALL_Digit);

		switch(i)
		{
			case 0: { GPIO_SetBits(GPIOB,Num1); break;}
			case 1: { GPIO_SetBits(GPIOB,Num2); break;}
			case 2: { GPIO_SetBits(GPIOB,Num3); break;}
			case 3: { GPIO_SetBits(GPIOB,Num4); break;}
		}

		switch (on_screen[i])
		{
			case 'a': { GPIO_SetBits(GPIOB,A); break;}
			case 'b': { GPIO_SetBits(GPIOB,B); break;}
			case 'c': { GPIO_SetBits(GPIOB,C); break;}
			case 'd': { GPIO_SetBits(GPIOB,D); break;}
			case 'e': { GPIO_SetBits(GPIOB,E); break;}
			case 'f': { GPIO_SetBits(GPIOB,F); break;}
			case 'g': { GPIO_SetBits(GPIOB,G); break;}
			case 'h': { GPIO_SetBits(GPIOB,H); break;}
			case '0': { GPIO_SetBits(GPIOB,digit[0]); break;}
			case '1': { GPIO_SetBits(GPIOB,digit[1]); break;}
			case '2': { GPIO_SetBits(GPIOB,digit[2]); break;}
			case '3': { GPIO_SetBits(GPIOB,digit[3]); break;}
			case '4': { GPIO_SetBits(GPIOB,digit[4]); break;}
			case '5': { GPIO_SetBits(GPIOB,digit[5]); break;}
			case '6': { GPIO_SetBits(GPIOB,digit[6]); break;}
			case '7': { GPIO_SetBits(GPIOB,digit[7]); break;}
			case '8': { GPIO_SetBits(GPIOB,digit[8]); break;}
			case '9': { GPIO_SetBits(GPIOB,digit[9]); break;}
		}
	}
}

void intToChar4(int32_t number, char array[4])
{
	for(int i=3;i>=0;i--)
	{
		array[i] = (number%10)+48;
		number /= 10;
	}
}
