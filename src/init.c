/*
 * init.c
 *
 *  Created on: 23 mar 2018
 *      Author: st-wasik
 */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "pdm_filter.h"

#include "stm32_tm1637.h"
#include "init.h"
#include "FFT.h"
#include "toneContainer.h"

const int DECIMATION_FACTOR = 64;
const int OUT_FREQ = 32000;
const int PDM_Input_Buffer_SIZE = 25600;
const int PCM_Output_Buffer_SIZE = 3200;
//const int PDM_Input_Buffer_SIZE = (OUT_FREQ/1000)*DECIMATION_FACTOR/8;
//const int PCM_Output_Buffer_SIZE = OUT_FREQ/1000;

extern PDMFilter_InitStruct Filter;
extern toneContainer container;

void GPIO_Configure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure MP45DT02's CLK / I2S2_CLK (PB10) line
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Configure MP45DT02's DOUT / I2S2_DATA (PC3) line
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_SPI2);  // Connect pin 10 of port B to the SPI2 peripheral
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2);   // Connect pin 3 of port C to the SPI2 peripheral

	//USER button

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void I2S_Configure(void)
{
  I2S_InitTypeDef I2S_InitStructure;

  SPI_I2S_DeInit(SPI2);
  I2S_InitStructure.I2S_AudioFreq = OUT_FREQ*2;
  I2S_InitStructure.I2S_Standard = I2S_Standard_LSB;
  I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
  I2S_InitStructure.I2S_CPOL = I2S_CPOL_High;
  I2S_InitStructure.I2S_Mode = I2S_Mode_MasterRx;
  I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
  I2S_Init(SPI2, &I2S_InitStructure);

  // Enable the Rx buffer not empty interrupt
  SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);
}

void NVIC_Configure(void)
{
	//Konfiguracja przerwań - przerwania zewnętrzne.
	//W pierwszej kolejności należy uruchomić zasilanie systemu przerwań:
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;

	// Configure the interrupt priority grouping
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);


	//------for SPI2
	NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//------for USER button
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void RCC_Configure(void)
{
	//USER
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//PB10, PC3
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_CRC, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	RCC_PLLI2SCmd(ENABLE);
}

void PDMFilter_init()
{
	  Filter.Fs = OUT_FREQ;
	  Filter.HP_HZ = 10;
	  Filter.LP_HZ = 16000;
	  Filter.In_MicChannels = 1;
	  Filter.Out_MicChannels = 1;

	  PDM_Filter_Init(&Filter);
}

void EXTI_init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	// wybór numeru aktualnie konfigurowanej linii przerwań
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	// wybór trybu - przerwanie bądź zdarzenie
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	// wybór zbocza, na które zareaguje przerwanie
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	// uruchom daną linię przerwań
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	// zapisz strukturę konfiguracyjną przerwań zewnętrznych do rejestrów
	EXTI_Init(&EXTI_InitStructure);

	// podłączenie danego pinu portu do kontrolera przerwań
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
}

void init()
{
	tm1637Init();
	tm1637ShowLogo();

	RCC_Configure();
	GPIO_Configure();

	NVIC_Configure();
	EXTI_init();
	I2S_Configure();

	PDMFilter_init();
	FFT_init();
	TC_fill(&container);
}
