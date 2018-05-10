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

#include "init.h"
#include "stm32_tm1637.h"

int main(void)
{

	tm1637Init();
	tm1637Display("1234");
	//init();

	int i=0;
	while (1) {
	char arr[4];
	int_to_string(i,arr);
	tm1637Display(arr);
	i++;
	if (i==10000) i=0;
	}
}
