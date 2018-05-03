/*
 * FFT.h
 *
 *  Created on: 3 maj 2018
 *      Author: St.Wasik
 */
#include "arm_math.h"

#ifndef FFT_H_
#define FFT_H_

uint8_t  PDM_Input_Buffer[25600];
uint16_t PCM_Output_Buffer[3200];

arm_rfft_instance_f32 S;
arm_cfft_radix4_instance_f32 S_CFFT;

float32_t buffer_input[1024];
float32_t buffer_output[1024];
float32_t buffer_output_mag[1024];
float32_t maxvalue;
uint32_t  maxvalueindex;
uint8_t   mode;

void FFT_init();

void FFT();

#endif /* FFT_H_ */
