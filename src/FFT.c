#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "pdm_filter.h"

#include "FFT.h"

extern const int DECIMATION_FACTOR;
extern const int OUT_FREQ;
extern const int PDM_Input_Buffer_SIZE;
extern const int PCM_Output_Buffer_SIZE;

extern PDMFilter_InitStruct Filter;
extern arm_rfft_instance_f32 S;
extern arm_cfft_radix4_instance_f32 S_CFFT;

void FFT_init()
{
	arm_rfft_init_f32(&S, &S_CFFT, 512, 0, 1);
}

void FFT()
{
	static int z=0;
	int i;
	// Przekopiuj dane paczki do bufora
	for(int i=0; i<(OUT_FREQ/1000); i++)
	{
	  buffer_input[i+(OUT_FREQ/1000)*z] = (float32_t) PCM_Output_Buffer[i];
	}

	++z;
	if(z > 512/(OUT_FREQ/1000))
	{
	  z = 0;
	  // Wyznaczenie transformaty Fouriera
	  arm_rfft_f32(&S, buffer_input, buffer_output);
	  // Obliczenie modu³ów
	  arm_cmplx_mag_f32(buffer_output, buffer_output_mag, 512);
	  // Znalezienie sk³adowej harmonicznej sygna³u o najwiêkszej amplitudzie
	  arm_max_f32(&(buffer_output_mag[1]), 512, &maxvalue, &maxvalueindex);
	  // Skalowanie wartoœci modu³ów
	  for(i=0; i<512; ++i)
	  {
		buffer_output_mag[i+1] = 140*buffer_output_mag[i+1]/20000000;
	  }

	  // ************************************************************
	  // Rysowanie nowego widma
#warning ustawienie na wyœwietlaczu wartoœci

	  //DrawSpectrum_Update(Green);
	}
}
