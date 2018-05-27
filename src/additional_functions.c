/*
 * additional_functions.c
 *
 *  Created on: 27 maj 2018
 *      Author: St.Wasik
 */
#include "additional_functions.h"

#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "stm32_tm1637.h"

uint16_t WAIT_Counter = 2;

void wait_ms(uint16_t ms)
{
	TIM_Cmd(TIM3, ENABLE);
	while(WAIT_Counter < ms);
	TIM_Cmd(TIM3, DISABLE);
	WAIT_Counter = 0;
}

void RGB(uint16_t Color)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_5);
	GPIO_SetBits(GPIOB, Color);
}

void RGB_Red()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
}

void RGB_Green()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_7 | GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
}

void RGB_Blue()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_7 | GPIO_Pin_8);
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
}

void USART_send_array(char * array, uint32_t size)
{
	for(int i=0;i<size;i++)
	{
		while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		USART_SendData(USART3, array[i]);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	}
}

void USART_send_int(int * arr, uint32_t size)
{
	for(int i=0;i<size;i++)
	{
		char display[8]= {0};
		int_to_string_8((int)arr[i],display);
		USART_send_array(display, 8);
		USART_send_array("_", 1);
	}
}

void charCopy(unsigned int n, char new[], char orig[])
{
	for(unsigned int i=0; i<n; i++)
	{
		new[i]=orig[i];
	}
}

