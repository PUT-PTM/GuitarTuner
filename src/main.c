/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "init.h"
#include "display.h"

extern const int DECIMATION_FACTOR;
extern const int OUT_FREQ;
extern const int PDM_Input_Buffer_SIZE;
extern const int PCM_Output_Buffer_SIZE;

enum displayMode {frequency, tone };

enum displayMode mode = tone;


/* Private variables ---------------------------------------------------------*/
uint8_t  PDM_Input_Buffer[PDM_Input_Buffer_SIZE];
uint16_t PCM_Output_Buffer[PCM_Output_Buffer_SIZE];

float32_t buffer_input[1024];
float32_t buffer_input_copy[256];
float32_t buffer_output[1024];
float32_t buffer_output_mag[1024];
float32_t buffer_output_mag_copy[256];
float32_t maxvalue;
uint32_t  maxvalueindex;
uint8_t   mode;

uint16_t  g_SPECTRUM_Xpos;
uint8_t   g_SPECTRUM_Ypos;
char      text[100];

arm_rfft_instance_f32 S;
arm_cfft_radix4_instance_f32 S_CFFT;
PDMFilter_InitStruct Filter;



int main(void)
{
	init();

	int i=0;
	while (1) {
	char arr[4];
	int_to_string(i,arr);
	tm1637Display("xxxx",0);
	i++;
	if (i==10000) i=0;
	}
	for(;;)
	{


	}
}
