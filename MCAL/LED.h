#ifndef LED_H_
#define LED_H_

#include "../LIB/tm4c123gh6pm.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#define RED 0x2
#define BLUE 0x4

void TURN_ON_LED(uint8_t Colour);
void Check_Distance(float distance, uint8_t Button_State);


#endif
