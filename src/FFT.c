#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FFT.h"
#include "arm_const_structs.h"
#include "toneContainer.h"
#include "stm32_tm1637.h"

#define SAMPLES (256)
#define FFT_SIZE (SAMPLES / 2)

/* Global variables */
q31_t Input[SAMPLES];   /*!< Input buffer is always 2 * FFT_SIZE */
q31_t Output[FFT_SIZE]; /*!< Output buffer is always FFT_SIZE */
q31_t Output_Mag[FFT_SIZE]; /*!< Output buffer is always FFT_SIZE */
arm_cfft_instance_q31 FFTi;
arm_cfft_instance_q31 * FFT_inst = &FFTi;
q31_t MaxValue;           /*!< Max value in FTT result after calculation */
uint32_t MaxIndex;

uint16_t Count = 0;

void UART_send_arr(char * array, uint32_t size)
{
	//while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	//USART_SendData(USART3, '^');
	//while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);

	for(int i=0;i<size;i++)
	{
		while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		// wyslanie danych
		USART_SendData(USART3, array[i]);
		// czekaj az dane zostana wyslane
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	}


}

void UART_send(q31_t * arr, uint32_t size)
{
	for(int i=0;i<size;i++)
	{
		char display[4]= {0};
		/*if(arr[i] >=0 && arr[i] < 10)
		{
			char x = arr[i] + 48;
			UART_send_arr(&x, 1);
		}
		else
		{*/
			int_to_string(arr[i],display);
			UART_send_arr(display, 4);
		//}
	}
}


void max(q31_t* Input, uint16_t InputSize, q31_t* MaxIndex, uint32_t * MaxValue)
{
	*MaxValue=Input[0];
	*MaxIndex=0;

	for(int i=1;i<InputSize; i++)
	{
		if (Input[i]>(*MaxValue))
		{
			*MaxIndex=i;
			*MaxValue=Input[i];
		}
	}
}

void FFT_init()
{
	arm_cfft_radix4_init_q31(FFT_inst, FFT_SIZE, 0, 1);
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



		arm_cfft_q31(&arm_cfft_sR_q31_len128, Input,0,0);



		arm_cmplx_mag_q31(Input, Output_Mag, FFT_SIZE);


		UART_send_arr("\nBEGIN:\n",8);
		UART_send(Input, FFT_SIZE);

		MaxValue=0;
		MaxIndex=0;
		arm_max_q31(Output_Mag, FFT_SIZE, &MaxValue, &MaxIndex);

		char display[4];
		int_to_string(MaxValue,display);
		tm1637Display(display);
	}
}
