/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "stm32_tm1637.h"
#include "FFT.h"
#include "toneContainer.h"

#undef __cplusplus

extern enum displayMode displayMode_;

void EXTI0_IRQHandler(void)
{
	tm1637Display("e___");
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			//while(1);
			for(int i=0; i<0x100000;i++);
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
	//tm1637Display("_adc");
	if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != RESET)
	{
		buffer_add(ADC_GetConversionValue(ADC1));

		int x = ADC_GetConversionValue(ADC1);
				char arr[4];
				int_to_string(x, arr);
				tm1637Display(arr);
				for(int i=0;i<0x1000;i++);

	}
	ADC_ClearITPendingBit(ADC1,ADC_FLAG_EOC);//<--clear automatically
}

#include "init.h"
#include "stm32_tm1637.h"

int main(void)
{
	init();

	for(;;)
	{
		/*
		ADC_SoftwareStartConv(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		int x = ADC_GetConversionValue(ADC1);
		char arr[4];
		int_to_string(x, arr);
		tm1637Display(arr);
		for(int i=0;i<0x1000000;i++);
		*/
	}
}
