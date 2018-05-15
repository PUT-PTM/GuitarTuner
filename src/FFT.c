#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FFT.h"
#include "toneContainer.h"
#include "stm32_tm1637.h"

extern arm_rfft_instance_f32 S;
extern arm_cfft_radix4_instance_f32 S_CFFT;

toneContainer container;

int buffer_input_length = 0;
float32_t buffer_input[BUFFER_INPUT_SIZE];
float32_t buffer_output[BUFFER_INPUT_SIZE];
float32_t buffer_output_mag[BUFFER_INPUT_SIZE];
float32_t maxvalue;
uint32_t  maxvalueindex;

arm_rfft_instance_f32 S;
arm_cfft_radix4_instance_f32 S_CFFT;

void FFT_init()
{
	arm_rfft_init_f32(&S, &S_CFFT, 512, 0, 1);
}

void FFT()
{
	  // transformata
	  //arm_rfft_f32(&S, buffer_input, buffer_output);
	  // modu³y liczb

	  //arm_cmplx_mag_f32(buffer_output, buffer_output_mag,  BUFFER_INPUT_SIZE/2);
	  // max
	//  arm_max_f32(&(buffer_output_mag[1]), BUFFER_INPUT_SIZE/2, &maxvalue, &maxvalueindex);



	  /*// wypisz
	  char display[4];
	  if(displayMode_ == frequency)
	  {
		  int_to_string((int)maxvalue, display);
	  }
	  else
	  {
		  TC_find(&container, maxvalue, display);
	  }

	  tm1637Display(display);
	  */
}

void buffer_add(uint16_t elem1)
{
	double elem = (double)elem1;

	//float32_t elem = (float32_t)elem2;

	if(buffer_input_length == BUFFER_INPUT_SIZE)
	{
		FFT();
		buffer_input_length = 0;
	}

	buffer_input[buffer_input_length] = elem;
	buffer_input_length++;
}
