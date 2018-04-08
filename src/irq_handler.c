/*
 * irq_handler.c
 *
 *  Created on: 23 mar 2018
 *      Author: st-wasik
 */

#include "../inc/irq_handler.h"
#include "../inc/display.h"

void ADC_IRQHandler(void)
{
	//FFT

	//test:
	char temp[4] = {'a','b','c','d'};
	set_screen(temp);
}

