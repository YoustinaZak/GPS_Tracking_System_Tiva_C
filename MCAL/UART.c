#include "UART.h"

void PORTA_UART_INIT(){
	//PORT INIT
	SYSCTL_RCGCGPIO_R |=0x01;
	while((SYSCTL_PRGPIO_R & 0x01)==0);
	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTA_CR_R |=0x03;        //COMMIT INIT BEFORE PUR PDR DEN
	GPIO_PORTA_DEN_R |=0x03;
	
	//UART0 INIT
	SYSCTL_RCGCUART_R |=0x01;
	while((SYSCTL_PRUART_R & 0x1)==0);
	GPIO_PORTA_AFSEL_R |=0x03;          //pin 0 and 1 are alternate func
	
	GPIO_PORTA_PCTL_R |= 0x11;          //1 in decimal = uart (EACH PIN HAS 4 BITS)
	UART0_CTL_R &=~0x01;                //diable uart
	                                    // baudrate must be written before LCRH
	UART0_IBRD_R = int_BRD ;
	UART0_FBRD_R = float_BRD;
	UART0_LCRH_R= (0<<7)|(11<<5);       //disable stick parity, 8bits, FIFO disabled, 1stop bit
	UART0_CC_R =0x05;
	UART0_CTL_R = (1<<0)|(1<<8)|(1<<9); //UART ENABLED, TX ENABLED, RX ENABLED
}


void PORTD_UART_INIT(){   
	//PORT INIT
	SYSCTL_RCGCGPIO_R |=0x08;
	while((SYSCTL_PRGPIO_R & 0x08)==0);

	GPIO_PORTD_CR_R |=(1<<6)|(1<<7);          //COMMIT INIT BEFORE PUR PDR DEN
	GPIO_PORTD_DEN_R |=(1<<6)|(1<<7);         //0XC
	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
	SYSCTL_RCGCUART_R |=(1<<2);
	while((SYSCTL_PRUART_R &(1<<2))!=(1<<2));
	GPIO_PORTD_AFSEL_R |=(1<<6)|(1<<7);   //pin 0 and 1 are alternate func 0XC
	
	GPIO_PORTD_PCTL_R |= 0x11000000;      //1 in decimal = uart (EACH PIN HAS 4 BITS) pin 6 and pin 7
	UART2_CTL_R &=~0x01;                  //diable uart
	                                      // baudrate must be written before LCRH
	UART2_IBRD_R = int_BRD;
	UART2_FBRD_R = float_BRD;
	   
	UART2_LCRH_R= 0x60;                 //disable stick parity, 8bits, FIFO disabled, 1stop bit
	UART2_CTL_R = (1<<0)|(1<<8)|(1<<9); //UART ENABLED, TX ENABLED, RX ENABLED
	
}

void PrintChar_PC(uint8_t x){
	while((UART0_FR_R & (1<<5))!=0){} //loop if receive holding reg is empty 
	 UART0_DR_R =x; 
}

char GetChar_GPS(){
	while((UART2_FR_R & (1<<4)) !=0){} //CHECK RECEIVE REG
	return UART2_DR_R;
}

void transChar_GPS_to_PC(){
	while((UART2_FR_R & (1<<4))!=0){} //loop if receive holding reg is empty 
	while((UART0_FR_R & (1<<5)) !=0){} // loop if trans reg is not empty 
	UART0_DR_R=UART2_DR_R;
}

void printString(uint8_t* x){
    while(*x)
			{
			while((UART0_FR_R & (1<<5)) !=0){}
		    UART0_DR_R= (*(x++));
		  }
}

void printString2(uint8_t* x){
    while(*x)
			{
			while((UART2_FR_R & (1<<5)) !=0){}
		    UART2_DR_R= (*(x++));
		  }
}

void Get_Data(uint8_t data[])         //gets nmea sentence
	{
		uint8_t i;
		while((UART2_FR_R & (1<<4))!=0){} //receive flag
		if( UART2_DR_R =='$')
				  {
						for(i=0; i<30; i++)
						{
					    data[i]= UART2_DR_R;
						  while((UART0_FR_R & (1<<5))!=0){}
							if(data[i]=='*')
								{
									break;
								}
							while((UART2_FR_R & (1<<4))!=0){}
				    }		 
	        }
					
	}
