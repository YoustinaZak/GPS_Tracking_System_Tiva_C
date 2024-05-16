#include "Systick.h"

void SYSTICK_INIT(){
	NVIC_ST_CTRL_R=0;
	NVIC_ST_RELOAD_R= 0xFFFFFF;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R=0x5; //enbled, clk src=1
}

void delay_a_sec()
	{
		NVIC_ST_RELOAD_R= (16000000)-1; //delay for 1 sec (24bits has max of 16,777,216)
	  NVIC_ST_CURRENT_R=0;
		while((NVIC_ST_CTRL_R &(1<<16))==0){}
}
	
void delay_a_millis()
	{
		NVIC_ST_RELOAD_R= (16000)-1; 
	  NVIC_ST_CURRENT_R=0;
		while((NVIC_ST_CTRL_R &(1<<16))==0){}
}
	
void delay_a_micros()
	{
		NVIC_ST_RELOAD_R= (16)-1; 
	  NVIC_ST_CURRENT_R=0;
		while((NVIC_ST_CTRL_R &(1<<16))==0){}
	}
	
void delay_in_seconds(int sec)
{
	int i;
	for(i=0;i<sec;i++)
	{
		delay_a_sec();
	}
}
	
void delay_in_millis(int millisec)
	{
		int i;
	  for(i=0;i<millisec;i++)
	    {
		    delay_a_millis();
      }
  }

void delay_in_micros(int microsec)
	{
		int i;
	  for(i=0;i<microsec;i++)
	    {
		    delay_a_micros();
      }
  }
