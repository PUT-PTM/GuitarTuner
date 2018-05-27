/*
 * FFT.h
 *
 *  Created on: 3 maj 2018
 *      Author: St.Wasik
 */
#include "arm_math.h"

#ifndef FFT_H_
#define FFT_H_

void buffer_add(uint16_t elem);

void USART_send_array(char * array, uint32_t size);

void USART_send_int(int * arr, uint32_t size);

#endif /* FFT_H_ */
