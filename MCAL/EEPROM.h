#ifndef EEPROM_H_
#define EEPROM_H_

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/tm4c123gh6pm.h"
#include "SYSTICK.h"

uint32_t readEeprom(uint16_t index_of_word);
void writeEeprom(uint16_t index_of_word, uint32_t data); 
void EEPROM_INIT();
#endif
