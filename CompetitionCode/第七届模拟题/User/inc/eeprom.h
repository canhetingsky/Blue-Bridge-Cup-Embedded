#ifndef __EEPROM_H
#define __EEPROM_H

#include <stm32f10x.h>

uint8_t x24c02_read(uint8_t address);
void x24c02_write(uint8_t address,uint8_t info);
#endif
