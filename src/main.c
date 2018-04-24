/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "init.h"
#include "display.h"

int main(void)
{
	tm1637Init();
	//tm1637SetBrightness();
	//tm1637DisplayDecimal(1010,0);
	//for (int i=0;i<9999;i++) {
	//tm1637Display(i,0);
	//for (int j=0;j<80000;j++);
	//}
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
