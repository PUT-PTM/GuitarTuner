/*
 * irq_handler.h
 *
 *  Created on: 23 mar 2018
 *      Author: st-wasik
 */

#include "arm_math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "toneContainer.h"

#ifndef IRQ_HANDLER_H_
#define IRQ_HANDLER_H_

enum displayMode {tone, frequency};
enum displayMode displayMode_ = tone;

toneContainer container;

uint32_t InternalBufferSize = 0;

void SPI2_IRQHandler(void);

#endif /* IRQ_HANDLER_H_ */
