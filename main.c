#include <stdio.h>
#include "MCAL/UART.h"
#include "MCAL/GPIO.h"
#include "HAL/GPS.h"
#include "MCAL/EEPROM.h" 
#include "MCAL/LED.h"
#include "MCAL/BUTTON.h"
#include "MCAL/SYSTICK.h"
#include "HAL/LCD.h"

extern float Extracted_Coordinates[1000][2]={0};  //max eeprom = 256 so /2 = 128

int main()
	{
	  uint16_t i=0;
		char uart;
		uint16_t arr_store_index=0;
	  double Unprocessed_latitude=0;
		double Unprocessed_longitude=0;
		float distance=0;
		
		char distance_LCD[20];
		char lat [10];
		char longit[10];
		char arr_index[6];
		
	
	  PORTA_UART_INIT();
		PORTD_UART_INIT();
	  PortF_Init();
		SYSTICK_INIT();
		PortB_Init();
		LCD_INIT_4bitMODE();
		LCD_send_Command(0x01);                                       //clear LCD
		                                      //next line 
		EEPROM_INIT(); 
		while((UART0_FR_R & (1<<4))!=0){}
			//wait until you receive something
			uart =UART0_DR_R; 
			UART0_DR_R= uart;
