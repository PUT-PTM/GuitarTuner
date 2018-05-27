#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FFT.h"
#include "toneContainer.h"
#include "stm32_tm1637.h"

#define SAMPLES (2048)
#define FFT_SIZE (SAMPLES / 2)
#define SAMPLE_FREQ 2400

extern enum displayMode displayMode_;

double Input[SAMPLES]; /*!< Input buffer is always 2 * FFT_SIZE */
float32_t Input_f32[SAMPLES];
double Output_Mag_f32[FFT_SIZE]; /*!< Output buffer is always FFT_SIZE */
double MaxValue; /*!< Max value in FTT result after calculation */
uint32_t MaxIndex;

uint16_t Count = 0;
double frequency = 0;

void USART_send_array(char * array, uint32_t size)
{
	for(int i=0;i<size;i++)
	{
		while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		USART_SendData(USART3, array[i]);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	}
}

void USART_send_int(int * arr, uint32_t size)
{
	for(int i=0;i<size;i++)
	{
		char display[8]= {0};
		int_to_string_8((int)arr[i],display);
		USART_send_array(display, 8);
		USART_send_array("_", 1);
	}
}

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

		//FFT
		arm_cfft_radix4_instance_f32 S;
		arm_cfft_radix4_init_f32(&S, FFT_SIZE, 0, 1);

		for(int i=0;i<SAMPLES;i++)
		{
			Input_f32[i] = (float)Input[i];
		}

		arm_cfft_radix4_f32(&S, Input_f32);
		Input_f32[0] = 0; //rubbish value in first cell

		arm_cmplx_mag_squared_f32(Input_f32, Output_Mag_f32, FFT_SIZE);
		Output_Mag_f32[0] = 0; //rubbish value in first cell

		arm_max_f32(Output_Mag_f32, FFT_SIZE/2, &MaxValue, &MaxIndex);

		 frequency = (double)MaxIndex * (double)SAMPLE_FREQ / (double)FFT_SIZE ;

		 char display[4] = {0};
		 /*if(MaxValue < 7.0E9)
		 	 { display[0] = '_'; display[1] = '_'; display[2] = '_'; display[3] = '_';}
		 else */
		 if(displayMode_ == Tone)
		 {
			TC_find(frequency,display);
		 }
		 else
		 {
			int_to_string(frequency, display);
		 }
		 tm1637Display(display);
	}
}

extern uint16_t WAIT_Counter;

void wait_ms(uint16_t ms)
{
	WAIT_Counter = 0;
	TIM_Cmd(TIM3, ENABLE);
	while(WAIT_Counter < ms);
	TIM_Cmd(TIM3, DISABLE);
}

void RGB_Red()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
}

void RGB_Green()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
}
