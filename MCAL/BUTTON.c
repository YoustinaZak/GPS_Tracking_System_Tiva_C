#include "BUTTON.h"


uint8_t Button_Status(){
	if( GET_BIT(GPIO_PORTF_DATA_R,0)== BUTTON_PRESSED)
		{
			return 1;
	  }
		else
			{
			   return 0;
		  }
}

uint8_t Button2_Status(){
	if(GET_BIT(GPIO_PORTF_DATA_R,4)== BUTTON_PRESSED)
		{
			return 1;
	  }
		else
			{
			   return 0;
		  }
}