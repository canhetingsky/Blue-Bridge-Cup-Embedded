#ifndef __USART1_H
#define __USAERT_H

#include "stm32f10x.h"                  // Device header

void Usart1_Init(uint32_t baudrate);
void USART_SendString(int8_t *str);

#endif
