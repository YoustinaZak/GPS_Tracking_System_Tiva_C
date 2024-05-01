#include "LED.h"

void TURN_ON_LED(uint8_t Colour)
	{
		CLEAR_BIT(GPIO_PORTF_DATA_R,1);
		CLEAR_BIT(GPIO_PORTF_DATA_R,2);
		CLEAR_BIT(GPIO_PORTF_DATA_R,3);
		GPIO_PORTF_DATA_R |= Colour;
  }
	
void Check_Distance(float distance, uint8_t Button_State)
	{
		if (distance >=100 || Button_State == 1)
			{
			   TURN_ON_LED(GREEN);
		  }
		else 
			{
					TURN_ON_LED(RED);
			}
  }
