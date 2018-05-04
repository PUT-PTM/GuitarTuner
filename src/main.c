/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#undef __cplusplus

#define __FPU_PRESENT 1

#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "stm32_tm1637.h"
#include "init.h"
#include "toneContainer.h"


toneContainer container;

enum displayMode {frequency, tone};
enum displayMode displayMode_ = tone;



int main(void)
{
	init();
	TC_fill(&container);

/*
	int i=0;
	while (1) {
	char arr[4];
	int_to_string(i,arr);
	tm1637Display("xxxx",0);
	i++;
	if (i==10000) i=0;
	}
	*/
	for(;;)
	{


	}
}
