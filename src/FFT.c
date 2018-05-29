#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FFT.h"
#include "toneContainer.h"
#include "stm32_tm1637.h"
#include "additional_functions.h"

#define SAMPLES (2048)
#define FFT_SIZE (SAMPLES / 2)
#define SAMPLE_FREQ 2400

extern enum displayMode displayMode_;

double Input[SAMPLES]; 				/*!< Input buffer is always 2 * FFT_SIZE */
float32_t Input_f32[SAMPLES];
double Output_Mag_f32[FFT_SIZE]; 	/*!< Output buffer is always FFT_SIZE */

double MaxValue; 					/*!< Max value in FTT result after calculation */
uint32_t MaxIndex;

uint16_t Count = 0;
double frequency = 0;

void buffer_add(uint16_t elem)
{
	if (Count < FFT_SIZE)
	{
		Input[2 * Count] = elem; /* Add to buffer, real part */
		Input[2 * Count + 1] = 0; /* Imaginary part set to 0 */
		Count++;
	}

	if (Count == FFT_SIZE)
	{
		Count = 0;

		//FFT init
		arm_cfft_radix4_instance_f32 S;
		arm_cfft_radix4_init_f32(&S, FFT_SIZE, 0, 1);

		for(int i=0;i<SAMPLES;i++)
		{
			Input_f32[i] = (float)Input[i];
		}

		int Fake_freq=0;						// MICROPHONE ERROR CHECK
		for (int i=0;i<SAMPLES;i+=2) 			// SPRAWDZANIE CZY PRZEPELNILO
		{ 										//
			if (Input[i]<650) Fake_freq++;		//
		}										//
		if (Fake_freq>500)						//
		{										//
			tm1637Display("err ");				//
		}										//
		else
		{
			//FFT
			arm_cfft_radix4_f32(&S, Input_f32);
			Input_f32[0] = 0; //rubbish value in first cell

			//Magnitude
			arm_cmplx_mag_squared_f32(Input_f32, Output_Mag_f32, FFT_SIZE);
			Output_Mag_f32[0] = 0; //rubbish value in first cell

			//Max value (frequency)
			arm_max_f32(Output_Mag_f32, FFT_SIZE/2, &MaxValue, &MaxIndex);
			frequency = (double)MaxIndex * (double)SAMPLE_FREQ / (double)FFT_SIZE ;

			//display
			char display[4] = {0};
			uint16_t Color = 0;
			TC_find(frequency, display, &Color);

			if(displayMode_ == Frequency)
			{
				Color |= BLUE;
				int_to_string(frequency, display);
			}
			else
			{
				/*
				if(MaxValue < 900000)
				{
					charCopy(4, display, "----");
				}
				*/
			}
			RGB(Color);
			tm1637Display(display);
		}
	}
}

