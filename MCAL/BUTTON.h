#ifndef BUTTON_H_
#define BUTTON_H_

#include "GPIO.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#define BUTTON_PRESSED  0x0
#define BUTTON_NOT_PRESSED 0x1

uint8_t Button_Status();
uint8_t Button2_Status();

#endif
