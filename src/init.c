/*
 * init.c
 *
 *  Created on: 23 mar 2018
 *      Author: st-wasik
 */

const int DECIMATION_FACTOR = 64;
const int OUT_FREQ = 32000;
const int PDM_Input_Buffer_SIZE = 25600;
const int PCM_Output_Buffer_SIZE = 3200;
//const int PDM_Input_Buffer_SIZE = (OUT_FREQ/1000)*DECIMATION_FACTOR/8;
//const int PCM_Output_Buffer_SIZE = OUT_FREQ/1000;

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32_tm1637.h"
#include "init.h"
#include "stm32_tm1637.h"
#include "pdm_filter.h"
/*
void GPIO_init()
{
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//GPIO_InitTypeDef GPIO_InitStructure;
	//segmenty
	/*
	 *   -   a
	 *  | | f b
	 *   -   g
	 *  | | e c
	 *   - . d h
	 *

	GPIO_InitStructure.GPIO_Pin =
	GPIO_Pin_0|  //a
	GPIO_Pin_1|  //b
	GPIO_Pin_2|  //c
	GPIO_Pin_4|  //d
 	GPIO_Pin_5|  //e
	GPIO_Pin_7|  //f
	GPIO_Pin_8|  //g
	GPIO_Pin_11| //h
	//wybor cyfry
	GPIO_Pin_12 | //1
	GPIO_Pin_13 | //2
	GPIO_Pin_14 | //3
	GPIO_Pin_15;  //4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void ADC_init()
{
	// ADC input is on PA1

	// zegar dla portu GPIO z którego wykorzystany zostanie pin jako wejście ADC (PA1)
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);

	// zegar dla modułu ADC1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	// GPIO dla wejścia ADC
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//ogólna konfiguracja ADC
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	// czas przerwy pomiędzy kolejnymi konwersjami
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	//konfiguracja ADC1
	ADC_InitTypeDef ADC_InitStructure;
	//ustawienie rozdzielczości przetwornika na maksymalną (12 bitów)
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	//wyłączenie trybu skanowania (odczytywać będziemy jedno wejście ADC
	//w trybie skanowania automatycznie wykonywana jest konwersja na wielu //wejściach/kanałach)
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	//włączenie ciągłego trybu pracy
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	//wyłączenie zewnętrznego wyzwalania
	//konwersja może być wyzwalana timerem, stanem wejścia itd. (szczegóły w //dokumentacji)
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//wartość binarna wyniku będzie podawana z wyrównaniem do prawej
	//funkcja do odczytu stanu przetwornika ADC zwraca wartość 16-bitową
	//dla przykładu, wartość 0xFF wyrównana w prawo to 0x00FF, w lewo 0x0FF0
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//liczba konwersji równa 1, bo 1 kanał
	ADC_InitStructure.ADC_NbrOfConversion = 1;

	ADC_Init(ADC1, &ADC_InitStructure);

	//konfiguracja kanału ADC_Ch1
	//W przykładzie powyżej konfigurujemy pierwszy kanał przetwornika ADC1 do samodzielnej pracy,
	//ustawiając czas próbkowania na 84 cykle sygnału zegarowego.
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);

	ADC_Cmd(ADC1, ENABLE);
}

void NVIC_init()
{
	// ustawienie trybu pracy priorytetów przerwań
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;
	// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
	// priorytet główny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kanał
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wypełnioną strukturę do rejestrów
	NVIC_Init(&NVIC_InitStructure);


	// wyczyszczenie przerwania adc1 (wystąpiło przy konfiguracji timera)
	ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
	// zezwolenie na przerwania od adc1
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
}
*/

void GPIO_Configure(void){
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
}


void I2S_Configure(void){
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

void NVIC_Configure(void){
  NVIC_InitTypeDef NVIC_InitStructure;

  // Configure the interrupt priority grouping
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  // Configure the SPI2 interrupt channel
  NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_Init(&NVIC_InitStructure);
}

void RCC_Configure(void)
{

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC |
                         RCC_AHB1Periph_CRC, ENABLE);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  RCC_PLLI2SCmd(ENABLE);
}

void PDM_Filter_init()
{
	PDMFilter_InitStruct Filter;
	  Filter.Fs = OUT_FREQ;
	  Filter.HP_HZ = 10;
	  Filter.LP_HZ = 16000;
	  Filter.In_MicChannels = 1;
	  Filter.Out_MicChannels = 1;
	  PDM_Filter_Init(&Filter);
}

void init()
{
	tm1637Init();
	RCC_Configure();
	NVIC_Configure();
	GPIO_Configure();
	I2S_Configure();
}
