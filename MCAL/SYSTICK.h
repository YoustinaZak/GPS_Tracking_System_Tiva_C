#ifndef SYSTICK_H_
 #define SYSTICK_H_
 
 #include "../LIB/tm4c123gh6pm.h"
 
 void SYSTICK_INIT();
 void delay_a_sec();
 void delay_in_seconds(int sec);
 void delay_a_millis();
 void delay_in_millis(int millisec);
 void delay_a_micros();
 void delay_in_micros(int microsec);

 
 #endif
