#ifndef GPIO_H_
#define GPIO_H_

#include "../LIB/tm4c123gh6pm.h"
#include "../LIB/BIT_MATH.h"

#define PORTA_SysRC       0x01
#define PORTB_SysRC       0x02
#define PORTC_SysRC       0x04
#define PORTD_SysRC       0x08
#define PORTE_SysRC       0x10
#define PORTF_SysRC       0x20

void PortA_Init();
void PortB_Init();
void PortC_Init();
void PortD_Init();
void PortE_Init();
void PortF_Init();

#endif
