/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
/* FPU present on STM32F4xx device */
#define __FPU_PRESENT   1

/* Use ARM MATH for Cortex-M4 */
#define ARM_MATH_CM4

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

	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			//while(1);
			for(int i=0; i<0x100000;i++);
			if(displayMode_ == Tone)
			{
				displayMode_ = Frequency;
			}
			else
			{
				displayMode_ = Tone;
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
		buffer_add(ADC_GetConversionValue(ADC1));
		/*
		int x = ADC_GetConversionValue(ADC1);
				char arr[4];
				int_to_string(x, arr);
				for(int i=0;i<0x1000;i++);
				*/
	}
}

#include "init.h"
#include "stm32_tm1637.h"

int main(void)
{
	GuitarTuner_init();

	for(;;)
	{

	}
}
