/*
 * init.c
 *
 *  Created on: 23 mar 2018
 *      Author: st-wasik
 */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void init()
{

}

void GPIO_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	//segmenty
	/*
	 *   -   a
	 *  | | f b
	 *   -   g
	 *  | | e c
	 *   -   d
	 */



	GPIO_InitStructure.GPIO_Pin =
	GPIO_Pin_0|  //a
	GPIO_Pin_1|  //b
	GPIO_Pin_2|  //c
	GPIO_Pin_4|  //d
 	GPIO_Pin_5|  //e
	GPIO_Pin_7|  //f
	GPIO_Pin_8|  //g
	GPIO_Pin_11|
	//wybor cyfry
	GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
