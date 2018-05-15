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

void GPIO_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//USER button
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void NVIC_init(void)
{

	//Konfiguracja przerwań - przerwania zewnętrzne.
	//W pierwszej kolejności należy uruchomić zasilanie systemu przerwań:
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		// Configure the interrupt priority grouping
		//------for USER button
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}

	{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
		// priorytet główny
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		// subpriorytet
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		// uruchom dany kanał
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		// zapisz wypełnioną strukturę do rejestrów
		NVIC_Init(&NVIC_InitStructure);

		// wyczyszczenie przerwania adc1
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
	}

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
	ADC_SoftwareStartConv(ADC1);
}


void GuitarTuner_init()
{
	tm1637Init();
	tm1637Display("123a");
	FFT_init();

	TC_fill();

	GPIO_init(); //USER-BUTTON

	ADC_init();

	NVIC_init(); //USER

	EXTI_init(); //USER

	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
}
