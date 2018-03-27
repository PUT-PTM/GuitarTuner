/*
 * init.c
 *
 *  Created on: 23 mar 2018
 *      Author: st-wasik
 */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "init.h"

void init()
{
	GPIO_init();
	NVIC_init();
	ADC_init();
}

void GPIO_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	//segmenty
	/*
	 *   -   a
	 *  | | f b
	 *   -   g
	 *  | | e c
	 *   -   d
	 */



	GPIO_InitStructure.GPIO_Pin =
	GPIO_Pin_0|  //a
	GPIO_Pin_1|  //b
	GPIO_Pin_2|  //c
	GPIO_Pin_4|  //d
 	GPIO_Pin_5|  //e
	GPIO_Pin_7|  //f
	GPIO_Pin_8|  //g
	GPIO_Pin_11|
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
