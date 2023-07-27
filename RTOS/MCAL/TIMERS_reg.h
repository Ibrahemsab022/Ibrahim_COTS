#ifndef	TIMERS_REG_H_
#define TIMERS_REG_H_


#define ORC0			*((volatile uint8*) 0x5C)			/*Out compare match register*/


#define TIMSK			*((volatile uint8*) 0x59)			/*Timer Mask register*/
#define TIMSK_TOIE0		0u									/*Timer0 overflow interrupt enable bit*/
#define TIMSK_OCIE0		1u									/*Timer0 compare match interrupt enable*/
#define TIMSK_TICIE1	5u
#define TIMSK_OCIE1A	4u
#define TIMSK_OCIE1B	3u
#define TIMSK_TOIE1		2u
#define TIMSK_TICIE1	5u									/*ICU Interrupt enable bit*/
#define TIMSK_TOIE2		6u									/*Timer/counter2 overflow interrupt enable*/
#define TIMSK_OCIE2		7u									/*Timer2 output cmp match int enable*/

#define TCCR0			*((volatile uint8*) 0x53)			/*Timer/counter control register 0*/
#define TCCR0_COM01		5u
#define TCCR0_COM00		4u
#define TCCR0_WGM00		6u
#define TCCR0_WGM01		3u


#define TCNT0			*((volatile uint8*) 0x52)			/*Timer/counter 0 register*/


#define TCCR1A			*((volatile uint8*) 0x4F)			/*Timer/Couner1 control Register A*/
#define TCCR1A_COM1A1	7u									/*COM1A1-COM1A0 comp output mode bits for channel A*/
#define TCCR1A_COM1A0	6u
#define TCCR1A_COM1B1	5u									/*COM1A1-COM1A0 comp output mode bits for channel B*/
#define TCCR1A_COM1B0	4u
#define TCCR1A_FOC1A	3u									/*Force output cmp mode for channel A*/
#define TCCR1A_FOC1B	2u									/*Force output cmp mode for channel B*/
#define TCCR1A_WGM11	1u									/*WGM11-10 Waveform generation mode*/
#define TCCR1A_WGM10	0u


#define TCCR1B			*((volatile uint8*) 0x4E)		/*Timer/Couner1 control Register B*/
#define TCCR1B_ICNC1	7u								/*Input Capture Noise Cancler bit*/
#define TCCR1B_ICES1	6u								/*Input capture Edge Select bit*/
#define TCCR1B_WGM13	4u								/*WGM13-12 Waveform generation mode*/
#define TCCR1B_WGM12	3u
#define TCCR1B_CS12		2u								/*CS12-11-10 Clock select bits*/
#define TCCR1B_CS11		1u
#define TCCR1B_CS10		0u


#define TCNT1H		*((volatile uint8*) 0x4D)
#define TCNT1L		*((volatile uint8*) 0x4C)
#define TCNT1		*((volatile uint16*) 0x4C)


#define OCR1AH		*((volatile uint8*) 0x4B)
#define OCR1AL		*((volatile uint8*) 0x4A)
#define OCR1A		*((volatile uint16*) 0x4A)

#define OCR1BH		*((volatile uint8*) 0x49)
#define OCR1BL		*((volatile uint8*) 0x48)
#define OCR1B		*((volatile uint16*) 0x48)

#define ICR1H		*((volatile uint8*) 0x47)
#define ICR1L		*((volatile uint8*) 0x46)
#define ICR1		*((volatile uint16*) 0x46)



#define TIFR		*((volatile uint8*) 0x58)
#define TIFR_ICF1	5u									/*ICU Interrupt Flag bit*/
#define SREG		*((volatile uint8*) 0x5F)


#define TCCR2		*((volatile uint8*) 0x45)           	 /*Timer/Counter2 Control Register*/
#define TCCR2_FOC2        7u                                  /*Force Output Compare*/
#define TCCR2_WGM20       6u                                  /*WGM20,21 Waveform generation mode bits*/
#define TCCR2_COM21       5u                                  /*COM21,20 compare match output mode*/
#define TCCR2_COM20       4u
#define TCCR2_WGM21       3u
#define TCCR2_CS22        2u                                  /*CS22:CS20 Clock select bits*/
#define TCCR2_CS21        1u
#define TCCR2_CS20        0u


#define TCNT2       *((volatile uint8*) 0x44)           /*Counter Register*/


#define OCR2        *((volatile uint8*) 0x43)           /*Output Compare register*/


#define ASSR        *((volatile uint8*) 0x42)           /**/






#endif
