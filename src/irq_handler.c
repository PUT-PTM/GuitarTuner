/*
 * irq_handler.c
 *
 *  Created on: 27 maj 2018
 *      Author: St.Wasik
 */
#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FFT.h"
#include "init.h"
#include "stm32_tm1637.h"
#include "additional_functions.h"

extern enum displayMode displayMode_;

uint16_t ADC_Output;

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			//for(int i=0;i<0x100FFF;i++);
			wait_ms(100u); //debounce
			if(displayMode_ == Tone)
			{
				displayMode_ = Frequency;
			}
			else
			{
				displayMode_ = Tone;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void ADC_IRQHandler()
{
	if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != RESET)
	{
		ADC_Output = ADC_GetConversionValue(ADC1);
	}
}

void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		buffer_add(ADC_Output);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

extern uint16_t WAIT_Counter;

void TIM3_IRQHandler()
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		WAIT_Counter++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
