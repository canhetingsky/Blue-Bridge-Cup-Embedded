#ifndef __RTC_H
#define __RTC_H

#include <stm32f10x.h>

void RTC_Init(void);
void RTC_Configuration(void);
void Time_Adjust(uint32_t TH, uint32_t TM,uint32_t TS);

#endif
