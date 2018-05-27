/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
/* FPU present on STM32F4xx device */
#define __FPU_PRESENT   1

/* Use ARM MATH for Cortex-M4 */
#define ARM_MATH_CM4

#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "init.h"

#undef __cplusplus

int main(void)
{
	GuitarTuner_init();

	for(;;);
}
