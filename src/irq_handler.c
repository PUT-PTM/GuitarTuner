/*
 * irq_handler.c
 *
 *  Created on: 23 mar 2018
 *      Author: st-wasik
 */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "irq_handler.h"
#include "FFT.h"
#include "stm32_tm1637.h"

extern enum displayMode displayMode_;

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			for(int i=0; i<0x10000;i++);
			if(displayMode_ == tone)
			{
				displayMode_ = frequency;
			}
			else
			{
				displayMode_ = tone;
			}
		}
		// wyzerowanie flagi wyzwolonego przerwania
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void ADC_IRQHandler()
{
	if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != RESET)
	{
		buffer_add((float32_t)ADC_GetConversionValue(ADC1));
	}
	//ADC_ClearITPendingBit(ADC1,ADC_FLAG_EOC);//<--clear automatically
}
