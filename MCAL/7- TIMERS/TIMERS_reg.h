#ifndef	TIMERS_REG_H_
#define TIMERS_REG_H_


#define ORC0			*((volatile uint8*) 0x5C)			/*Out compare match register*/


#define TIMSK			*((volatile uint8*) 0x59)			/*Timer Mask register*/
#define TIMSK_TOIE0		0									/*Timer0 overflow interrupt enable bit*/
#define TIMSK_OCIE0		1									/*Timer0 compare match interrupt enable*/


#define TCCR0			*((volatile uint8*) 0x53)			/*Timer/counter control register 0*/
#define TCCR0_COM01		5
#define TCCR0_COM00		4
#define TCCR0_WGM00		6
#define TCCR0_WGM01		3


#define TCNT0		*((volatile uint8*) 0x52)			/*Timer/counter 0 register*/


#define TIFR		*((volatile uint8*) 0x58)
#define SREG		*((volatile uint8*) 0x5F)






#endif