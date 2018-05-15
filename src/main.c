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


void HardFault_Handler(void)
{
	//tm1637Display("hard");
    __asm volatile
    (
        " tst lr, #4                                                \n"
        " ite eq                                                    \n"
        " mrseq r0, msp                                             \n"
        " mrsne r0, psp                                             \n"
        " ldr r1, [r0, #24]                                         \n"
        " ldr r2, handler2_address_const                            \n"
        " bx r2                                                     \n"
        " handler2_address_const: .word prvGetRegistersFromStack    \n"
    );
}

volatile uint32_t r0;
volatile uint32_t r1;
volatile uint32_t r2;
volatile uint32_t r3;
volatile uint32_t r12;
volatile uint32_t lr; /* Link register. */
volatile uint32_t pc; /* Program counter. */
volatile uint32_t psr;/* Program status register. */

void prvGetRegistersFromStack( uint32_t *pulFaultStackAddress )
{
/* These are volatile to try and prevent the compiler/linker optimising them
away as the variables never actually get used.  If the debugger won't show the
values of the variables, make them global my moving their declaration outside
of this function. */
    r0 = pulFaultStackAddress[ 0 ];
    r1 = pulFaultStackAddress[ 1 ];
    r2 = pulFaultStackAddress[ 2 ];
    r3 = pulFaultStackAddress[ 3 ];

    r12 = pulFaultStackAddress[ 4 ];
    lr = pulFaultStackAddress[ 5 ];
    pc = pulFaultStackAddress[ 6 ];
    psr = pulFaultStackAddress[ 7 ];

/*
    char disp[4];
    	int_to_string((int)r2,disp);
    	tm1637Display(disp);
    	*/
    /* When the following line is hit, the variables contain the register values. */
    for( ;; );
}

void EXTI0_IRQHandler(void)
{
	tm1637Display("e___");
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
	tm1637Display("_adc");
	if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != RESET)
	{
		tm1637Display("addb");
		buffer_add(ADC_GetConversionValue(ADC1));
		tm1637Display("afab");
		int x = ADC_GetConversionValue(ADC1);
				char arr[4];
				int_to_string(x, arr);
				tm1637Display(arr);
				for(int i=0;i<0x1000;i++);
	}
	//ADC_ClearITPendingBit(ADC1,ADC_FLAG_EOC);//<--clear automatically
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
