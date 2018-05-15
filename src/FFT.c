#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FFT.h"
#include "toneContainer.h"
#include "stm32_tm1637.h"

#include "tm_stm32f4_fft.h"

#define BUFFER_INPUT_SIZE 2048

#define SAMPLES (128)         /* 256 real party and 256 imaginary parts */
#define FFT_SIZE (SAMPLES / 2) /* FFT size is always the same size as we have samples, so 256 in our case */

/* Global variables */
float32_t Input[SAMPLES];   /*!< Input buffer is always 2 * FFT_SIZE */
float32_t Output[FFT_SIZE]; /*!< Output buffer is always FFT_SIZE */



TM_FFT_F32_t FFT_instance;    /*!< FFT structure */
uint16_t i;
uint32_t frequency = 10000;

/*
int buffer_input_length = 0;
float32_t buffer_input[BUFFER_INPUT_SIZE];
float32_t buffer_output[BUFFER_INPUT_SIZE];
float32_t buffer_output_mag[BUFFER_INPUT_SIZE];
double maxvalue;
uint32_t  maxvalueindex;

arm_rfft_instance_f32 S;
arm_cfft_radix4_instance_f32 S_CFFT;
*/

void FFT_init()
{
	/*
	if(ARM_MATH_SUCCESS == arm_rfft_init_f32(&S, &S_CFFT, BUFFER_INPUT_SIZE, 0, 1))
	{
		tm1637Display("a__2");
	}
	else
	{
		tm1637Display("a__0");
	}
	*/
	TM_FFT_Init_F32(&FFT_instance, FFT_SIZE, 0);
	/* We didn't used malloc for allocation, so we have to set pointers ourself */
	/* Input buffer must be 2 * FFT_SIZE in length because of real and imaginary part */
	/* Output buffer must be FFT_SIZE in length */
	TM_FFT_SetBuffers_F32(&FFT_instance, Input, Output);
}

void FFT_go()
{
	tm1637Display("ffgo");
	/*
	// transformata
	  arm_rfft_f32(&S, buffer_input, buffer_output);
	  // modu³y liczb
	  tm1637Display("ff2_");
	  //arm_cmplx_mag_f32(buffer_output, buffer_output_mag,  BUFFER_INPUT_SIZE/2);
	  // max
	//  arm_max_f32(&(buffer_output_mag[1]), BUFFER_INPUT_SIZE/2, &maxvalue, &maxvalueindex);
*/

	  TM_FFT_Process_F32(&FFT_instance);

	  char display[4];
	  int_to_string(TM_FFT_GetMaxValue(&FFT_instance),display);
	  tm1637Display(display);
	  while(1);

	  /*// wypisz
	  char display[4];
	  if(displayMode_ == Frequency)
	  {
		  int_to_string((int)maxvalue, display);
	  }
	  else
	  {
		  TC_find(maxvalue, display);
	  }

	  tm1637Display(display);
	  */
}

void buffer_add(uint16_t elem1)
{
	double elem = (double)elem1;
	//char res = TM_FFT_AddToBuffer(&FFT_instance, elem);

	if (FFT_instance.Count < FFT_instance.FFT_Size)
	{
		/* Add to buffer, real part */
		FFT_instance.Input[2 * FFT_instance.Count] = elem;
		/* Imaginary part set to 0 */
		FFT_instance.Input[2 * FFT_instance.Count + 1] = 0;

		/* Increase count */
		FFT_instance.Count++;
	}

	/* Check if buffer full */
	if (FFT_instance.Count == FFT_instance.FFT_Size)
	{
		/* Buffer full, samples ready to be calculated */

		//FFT
		tm1637Display("ff1_");
		//TM_FFT
		//TM_FFT_Process_F32(&FFT_instance);
		arm_cfft_f32(FFT_instance.S, FFT_instance.Input, 0, 1);
		tm1637Display("ff2_");
		/* Process the data through the Complex Magniture Module for calculating the magnitude at each bin */
		arm_cmplx_mag_f32(FFT_instance.Input, FFT_instance.Output, FFT_instance.FFT_Size);
		tm1637Display("ff3_");
		/* Calculates maxValue and returns corresponding value and index */
		arm_max_f32(FFT_instance.Output, FFT_instance.FFT_Size, &FFT_instance.MaxValue, &FFT_instance.MaxIndex);
		tm1637Display("ff4_");
		/* Reset count */
		FFT_instance.Count = 0;

		tm1637Display("ff5_");

		  while(1);

		  char display[4];
		  int_to_string(TM_FFT_GetMaxValue(&FFT_instance),display);
		  tm1637Display(display);
		  while(1);



	}

/*
	if(res)
	{
		FFT_go();
	}
	/*
	double elem = (double)elem1;

	if(buffer_input_length == SAMPLES)
	{
		FFT();
		buffer_input_length = 0;
	}

	buffer_input[buffer_input_length] = elem;
	buffer_input_length++;
	*/

}
