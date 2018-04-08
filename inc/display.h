/*
 * display.h
 *
 *  Created on: 27 mar 2018
 *      Author: st-wasik
 */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#ifndef DISPLAY_H_
#define DISPLAY_H_

void set_screen(char char_set[4]);

void display_update();

void intToChar4(int32_t number, char array[4]);

#endif /* DISPLAY_H_ */
