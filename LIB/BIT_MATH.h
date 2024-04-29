#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(regis,bit)    (regis |=(1<<bit))
#define CLEAR_BIT(regis,bit)   (regis &= ~(1<<bit))
#define GET_BIT(regis,bit)     (regis &(1<<bit))
#define TOGGLE_BIT(regis,bit)  (regis ^=(1<<bit))

#define SET_32bits(regist)        (regist|=0xffffffff)
#define CLR_32bits(regist)        (regist&=~0xffffffff)
#define SET_8bits(regist)        (regist|=0xff)
#define CLR_8bits(regist)        (regist&=~0xff)


#endif
