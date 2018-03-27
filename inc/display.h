/*
 * display.h
 *
 *  Created on: 27 mar 2018
 *      Author: st-wasik
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

uint32_t digits[10]={
		/*0*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7,
		/*1*/ GPIO_Pin_1 | GPIO_Pin_2,
		/*2*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_4,
		/*3*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_2 | GPIO_Pin_4,
		/*4*/ GPIO_Pin_7 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_2,
		/*5*/ GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_2 | GPIO_Pin_4,
		/*6*/ GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_2,
		/*7*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2,
		/*8*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8,
		/*9*/ GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_2 | GPIO_Pin_4
};

uint32_t A = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_2;
uint32_t B = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_2 | GPIO_Pin_4;
uint32_t C = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_4;
uint32_t D = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8 | GPIO_Pin_4 | GPIO_Pin_5;
uint32_t E = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_2 | GPIO_Pin_4;
uint32_t F = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_8;
uint32_t G = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_2;
uint32_t H = GPIO_Pin_7 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_2;

char on_screen[4]={'T','E','S','T'};

void set_screen(char char_set[]) {

}

void update() {


}



#endif /* DISPLAY_H_ */
