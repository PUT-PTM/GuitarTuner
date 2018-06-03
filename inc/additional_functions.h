/*
 * additional_functions.h
 *
 *  Created on: 27 maj 2018
 *      Author: St.Wasik
 */

#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#define RED GPIO_Pin_7
#define GREEN GPIO_Pin_8
#define BLUE GPIO_Pin_5

#ifndef ADDITIONAL_FUNCTIONS_H_
#define ADDITIONAL_FUNCTIONS_H_

void USART_send_array(char * array, uint32_t size);

void USART_send_int(int * arr, uint32_t size);

void wait_ms(uint16_t ms);

void RGB(uint16_t Color);

void RGB_Red();

void RGB_Green();

void RGB_Blue();

void charCopy(unsigned int n, char new[], char orig[]);

void intro();

#endif /* ADDITIONAL_FUNCTIONS_H_ */
