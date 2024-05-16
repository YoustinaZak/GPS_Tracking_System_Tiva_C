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
               if(uart=='U')
			{
				
				uint8_t arr_to_fill[10];
				uint16_t count;
				uint32_t no;
				float f;
				printString_toLCD("Loading Data.."); 
			  for(count=0;count<1000;count++)
				   {
			       no = readEeprom(count);
			       f =(float) (no)/1000000;
					   sprintf(arr_to_fill,"%f ",f);
	           
						 if(count%2 !=0)                   //if odd number
						 {
							 printString(arr_to_fill);
							 printString("\n\r");
						 }
						 else {
							 printString(arr_to_fill);
							 printString(",");
		         }
					 }						 
					 LCD_send_Command(0x80);  //rewrite first line
				   printString_toLCD("Data Loaded..");
		       
				 }
           else{
			printString_toLCD("Distance:");
		  LCD_send_Command(0xC0); 
			while(1)
		   {
			 //uint8_t input[]="$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
			      uint8_t input[50]={0};
			      Get_Data(input);
				    
			if(input[3]=='G'&& input[4]=='G'&&input[5]=='A')
				{
					
				Process_str(input, &Unprocessed_latitude, &Unprocessed_longitude);  //check if data is valid and store lat and long in Unprocessed variables
			  Get_Map_Coordinates(Unprocessed_latitude, Unprocessed_longitude, arr_store_index);   //changes the  format of the unprocessed variables
					 
					arr_store_index=i/5;
						    i++;
			if(arr_store_index>0 && i%5==0)
				{ 
					sprintf(lat,"%f ",Extracted_Coordinates[arr_store_index][0]);
					printString(lat);
					sprintf(longit,"%f\n\r",Extracted_Coordinates[arr_store_index][1]);
					printString(longit);					
			    distance +=Get_GPS_distance(Extracted_Coordinates[arr_store_index][1], Extracted_Coordinates[arr_store_index][0], Extracted_Coordinates[arr_store_index-1][1], Extracted_Coordinates[arr_store_index-1][0]);
				}
				 
			   sprintf(distance_LCD, "%f\n\r", distance);
			  
				 LCD_send_Command(0xC0);
				                      //don't remove the delay //problem
			   printString_toLCD(distance_LCD);
				
			if(i==1000 || Check_Distance(distance, Button_Status())==1)  //needs a long press to work (due to delay)
				{
					LCD_send_Command(0xC0);
					printString("Done\n");
					printString_toLCD("End Point");
				  break;
			  }
			 //dont put delay here  */
		} 	
  }
