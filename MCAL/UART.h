
#ifndef UART_H_
#define UART_H_

#include "../LIB/tm4c123gh6pm.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#define BAUD_RATE       9600
#define int_BRD         (uint8_t)(16000000 / (16 * BAUD_RATE))  //=104.1677
#define float_BRD       (uint8_t)(0.1677 * 64 + 0.5)  //=11

void PORTA_UART_INIT();
void PORTD_UART_INIT();
void PrintChar_PC(uint8_t x);
char readChar();
char printChar();
void transChar_GPS_to_PC();
void printString(uint8_t* x);
void printString2(uint8_t* x);
void Get_Data(uint8_t data[]);

#endif
