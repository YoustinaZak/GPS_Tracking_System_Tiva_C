#include "EEPROM.h"


void EEPROM_INIT()
	{ 	
		SET_BIT(SYSCTL_RCGCEEPROM_R ,0);  //enable the cclk
		delay_in_millis(3);               //3 system clks (not exact)
  }

void writeEeprom(uint16_t index_of_word, uint32_t data)
	{ //add specifies the no. of word out of 256
    EEPROM_EEBLOCK_R = index_of_word >> 4;     //specifies the no. of block out of 32 (divide by 16 because each blck is 16 words)                         
    EEPROM_EEOFFSET_R = index_of_word & 0xF;   //specifies the no. of word out of 16
    EEPROM_EERDWR_R = data;   //the data to be written
    //while(~GET_BIT(EEPROM_EEDONE_R,0)){}
}

uint32_t readEeprom(uint16_t index_of_word)
	{
		EEPROM_EEBLOCK_R = index_of_word >> 4;
    EEPROM_EEOFFSET_R = index_of_word & 0xF;
    return EEPROM_EERDWR_R;
}
