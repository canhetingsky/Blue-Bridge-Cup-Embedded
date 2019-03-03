#ifndef __LED_H
#define __LED_H

#include <stm32f10x.h>

#define LED_ON 0
#define LED_OFF 1

#define LED1_PIN GPIO_Pin_8
#define LED2_PIN GPIO_Pin_9
#define LED3_PIN GPIO_Pin_10
#define LED4_PIN GPIO_Pin_11
#define LED5_PIN GPIO_Pin_12
#define LED6_PIN GPIO_Pin_13
#define LED7_PIN GPIO_Pin_14
#define LED8_PIN GPIO_Pin_15
#define LEDALL	GPIO_Pin_All

void LED_Init(void);
void LED_Control(uint16_t LED_Pin,uint16_t LED_STATE);

#endif
