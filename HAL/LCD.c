#include "LCD.h"

void LCD_INIT_4bitMODE()
{
	LCD_send_Command(0x28);          //2 lines and 5x7 character (4-bit data, D4 to D7)
	LCD_send_Command(0x06);          //Automatic Increment cursor (shift cursor to right)
	LCD_send_Command(0x01);					 //Clear display screen
	LCD_send_Command(0x0F);          //Display on, cursor blinking
	LCD_send_Command(0x01);								//Clear the display
	LCD_send_Command(0x80);               //Force the cursor to beginning of 1st line
}


void LCD_Write4bits(uint8_t bitsToBeWritten, uint8_t DataOrCommand)
{
	GPIO_PORTB_DATA_R = bitsToBeWritten | DataOrCommand;         //Including RS value (command or data ) with data 
	GPIO_PORTB_DATA_R = bitsToBeWritten | DataOrCommand | EN;    //pulse EN
	delay_in_micros(1);													                         //delay for pulsing EN
	GPIO_PORTB_DATA_R = bitsToBeWritten | DataOrCommand;				//Turn off the pulse EN
	GPIO_PORTB_DATA_R = 0;                                      //Clear pins 
}

void printString_toLCD(uint8_t * str)
{  
	volatile int i = 0;          //volatile is important 
	while(*(str+i))              //til null
	{
		LCD_send_Data(*(str+i));    //Write each character of string
		i++;                        //increment for next character
	}
}


void LCD_send_Command(uint8_t command)
{
	LCD_Write4bits(command & 0xF0 , 0);    //upper 4bits first, 0= command
	LCD_Write4bits(command << 4 , 0);			 //lower 4bits, 0=command
	
	delay_in_millis(2);       //commands 1 and 2 need up to 1.64ms
	
}

void LCD_send_Data(uint8_t data)
{
	LCD_Write4bits(data & 0xF0 , RS);   //send upper 4 bits of data , RS= data
	LCD_Write4bits(data << 4 , RS);     //send lower 4 bits of data , RS= data
	delay_in_micros(40);											//delay for LCD (MCU is faster than LCD)
}
