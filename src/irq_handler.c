/*
 * irq_handler.c
 *
 *  Created on: 23 mar 2018
 *      Author: st-wasik
 */

#include "irq_handler.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "stm32_tm1637.h"
#include "pdm_filter.h"
#include "toneContainer.h"
#include "FFT.h"

extern uint32_t InternalBufferSize;

extern const int PDM_Input_Buffer_SIZE;

extern PDMFilter_InitStruct Filter;
extern uint8_t  PDM_Input_Buffer[];
extern uint16_t PCM_Output_Buffer[];

extern float32_t maxvalue;

void SPI2_IRQHandler(void)
{
	  u16 volume;
	  u16 app;

	  // Check if new data are available in SPI data register
	  if (SPI_GetITStatus(SPI2, SPI_I2S_IT_RXNE) != RESET)
	  {
		// Read received data and save it in internal table
		app = SPI_I2S_ReceiveData(SPI2);
		PDM_Input_Buffer[InternalBufferSize++] = (uint8_t)app;
		PDM_Input_Buffer[InternalBufferSize++] = (uint8_t)HTONS(app);

		// Check to prevent overflow condition
			if (InternalBufferSize >= PDM_Input_Buffer_SIZE)
			{
			  InternalBufferSize = 0;

			  volume = 50;

			  PDM_Filter_64_LSB(PDM_Input_Buffer, PCM_Output_Buffer, volume, &Filter);
			  FFT();

			  char display[4];
			  if(displayMode_ == frequency)
			  {
				  int_to_string((int)maxvalue, display);
			  }
			  else
			  {
				  TC_find(&container, maxvalue, display);
			  }
			  tm1637Display(display);
			}
		SPI_ClearITPendingBit(SPI2, SPI_I2S_IT_RXNE);
	  }
}


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
