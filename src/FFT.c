#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FFT.h"
#include "arm_const_structs.h"
#include "toneContainer.h"
#include "stm32_tm1637.h"

#define SAMPLES (2048)
#define FFT_SIZE (SAMPLES / 2)
#define SAMPLE_FREQ 40000

/* Global variables */
/*
q31_t Input[SAMPLES];
q31_t Output[FFT_SIZE];
q31_t Output_Mag[FFT_SIZE];
arm_cfft_instance_q31 FFTi;
arm_cfft_instance_q31 * FFT_inst = &FFTi;
q31_t MaxValue;
uint32_t MaxIndex;
*/

double Input[SAMPLES];   /*!< Input buffer is always 2 * FFT_SIZE */
double Output[FFT_SIZE*2]; /*!< Output buffer is always FFT_SIZE */
double Output_Mag[FFT_SIZE]; /*!< Output buffer is always FFT_SIZE */
arm_cfft_instance_q31 FFTi;
arm_cfft_instance_q31 * FFT_inst = &FFTi;
double MaxValue;           /*!< Max value in FTT result after calculation */
uint32_t MaxIndex;

uint16_t Count = 0;

int frequency = 0;

#define AVG_ELEMENTS 15
uint16_t AvgCount = 0;
double AvgArray[AVG_ELEMENTS];
double Avg = 0;

void push_avg(int x)
{
	AvgArray[AvgCount] = x;
	AvgCount++;
	if(AvgCount == AVG_ELEMENTS)
	{
		double sum = 0;
		for(int i=0;i<AVG_ELEMENTS;i++)
		{
			sum+=AvgArray[i];
		}
		Avg = sum/(double)AVG_ELEMENTS;
		AvgCount = 0;
	}
}

void UART_send_arr(char * array, uint32_t size)
{
	for(int i=0;i<size;i++)
	{
		while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		// wyslanie danych
		USART_SendData(USART3, array[i]);
		// czekaj az dane zostana wyslane
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	}
}

//void UART_send(q31_t * arr, uint32_t size)
void UART_send(double * arr, uint32_t size)
{
	for(int i=0;i<size;i++)
	{
		char display[8]= {0};
		int_to_string_8((int)arr[i],display);
		UART_send_arr(display, 8);
		UART_send_arr("_", 1);
	}
}

void FFT_init()
{
	//arm_cfft_radix4_init_q31(FFT_inst, FFT_SIZE, 0, 1);
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

	if (Count == FFT_SIZE)
	{
		Count = 0;

		arm_cfft_radix4_instance_f32 S; // ARM CFFT module
		// Initialize the CFFT/CIFFT module, intFlag = 0, doBitReverse = 1
		arm_cfft_radix4_init_f32(&S, FFT_SIZE, 0, 1);

		//UART_send_arr("\nRAW INPUT:\n",12);
		//UART_send(Input, FFT_SIZE*2);



		// Process the data through the CFFT/CIFFT module
		arm_cfft_radix4_f32(&S, Input);
		//UART_send_arr("\nFFT INPUT:\n",12);
		//UART_send(Input, FFT_SIZE*2);


		// Process the data through the Complex Magniture Module for calculating the magnitude at each bin
		arm_cmplx_mag_squared_f32(Input, Output, FFT_SIZE*2);
		Output[0] = 0;
		//UART_send_arr("\nMAG OUTPUT:\n",13);
		//UART_send(Output, FFT_SIZE);

		// Calculates maxValue and returns corresponding value
		arm_max_f32(Output, FFT_SIZE, &MaxValue, &MaxIndex);
		//push_avg(MaxValue);

		char a[8] = {0};
		int_to_string_8(MaxValue, a);
		UART_send_arr("\nMAX value:\n",12);
		UART_send_arr(a, 8);
		UART_send_arr("\n\n\n\n\n",5);

		 double smplRate = (FFT_SIZE / 1.0);

		 frequency = (double)((MaxIndex * SAMPLE_FREQ) / smplRate);
		 push_avg(frequency);

		 char display[4] = {0};
		 TC_find(Avg,display);
		 tm1637Display(display);
	}
}
