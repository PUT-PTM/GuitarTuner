#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FFT.h"
#include "toneContainer.h"
#include "stm32_tm1637.h"

#define BUFFER_INPUT_SIZE 2048

#define SAMPLES (2048)         /* 256 real party and 256 imaginary parts */
#define FFT_SIZE (SAMPLES / 2) /* FFT size is always the same size as we have samples, so 256 in our case */

/* Global variables */
q31_t Input[SAMPLES];   /*!< Input buffer is always 2 * FFT_SIZE */
q31_t Output[FFT_SIZE]; /*!< Output buffer is always FFT_SIZE */
q31_t Output_Mag[FFT_SIZE]; /*!< Output buffer is always FFT_SIZE */

const arm_rfft_instance_q31* S;
q31_t MaxValue;           /*!< Max value in FTT result after calculation */
q31_t MaxIndex;

uint16_t Count = 0;

void max(q31_t* Input, uint16_t InputSize, q31_t* MaxIndex, q31_t* MaxValue)
{
	*MaxValue=Input[0];
	*MaxIndex=0;

	for(int i=1;i<InputSize; i++)
	{
		if (Input[i]>max)
		{
			*MaxIndex=i;
			*MaxValue=Input[i];

		}
	}
}


void FFT_init()
{
	arm_rfft_init_q31(&S, FFT_SIZE, 0, 0);
}

void buffer_add(uint16_t elem)
{
	if (Count < FFT_SIZE)
	{
		/* Add to buffer, real part */
		Input[2 * Count] = elem;
		/* Imaginary part set to 0 */
		Input[2 * Count + 1] = 0;

		Count++;
	}

	/* Check if buffer full */
	if (Count == FFT_SIZE)
	{
		arm_rfft_q31(&S, Input, Output);

		/* Process the data through the Complex Magniture Module for calculating the magnitude at each bin */
		arm_cmplx_mag_q31(Input, Output_Mag, FFT_SIZE);

		/* Calculates maxValue and returns corresponding value and index */
		max(Output_Mag, FFT_SIZE, &MaxValue, &MaxIndex);
		//arm_max_q31(Output_Mag, FFT_SIZE, &MaxValue, &MaxIndex);
		Count = 0;

		char display[4];
		int_to_string(MaxValue,display);
		tm1637DisplayDecimal(MaxValue,0);
	}
}
