#ifndef LCD_H_
#define LCD_H_

#include "../MCAL/GPIO.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/SYSTICK.h"

#define RS 0x01				 	//reset PB0 (0x01) (tells if the set bits are data(1) or commands(0))
#define EN 0x04  		 	 	//enable PB2 (0x04)


//Functions Declaration
void delayUs(int);   														   //Delay in Micro Seconds
void delayMs(int);   														   //Delay in Milli Seconds
void LCD_INIT_4bitMODE();													 //Initialization of LCD Dispaly
void LCD_Write4bits(uint8_t bitsToBeWritten , uint8_t DataOrCommand); //Write data as (4 bits) on LCD
void printString_toLCD(uint8_t* str);											 //Write a string on LCD 
void LCD_send_Command(uint8_t command);									 //Write command 
void LCD_send_Data(uint8_t data);								 //Write a character 

#endif
