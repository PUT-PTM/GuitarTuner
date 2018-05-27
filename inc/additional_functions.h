/*
 * additional_functions.h
 *
 *  Created on: 27 maj 2018
 *      Author: St.Wasik
 */

#include "arm_math.h"

#ifndef ADDITIONAL_FUNCTIONS_H_
#define ADDITIONAL_FUNCTIONS_H_

void USART_send_array(char * array, uint32_t size);

void USART_send_int(int * arr, uint32_t size);

void wait_ms(uint16_t ms);

void RGB_Red();

void RGB_Green();

void RGB_Blue();

#endif /* ADDITIONAL_FUNCTIONS_H_ */
