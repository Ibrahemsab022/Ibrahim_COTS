#include "STD_TYPES.h"
#include <util/delay.h>

#include "PORT_interface.h"

#include "LED_prv.h"
#include "LED_interface.h"



/*configure the data of the LEDs you want to use
 * Activation:		1- ACTIVE_HIGH
 * 					2- ACTIVE_LOW
 *
 *
 * PORT:		1- DIO_u8PORTA
 * 				2- DIO_u8PORTB
 * 				3- DIO_u8PORTC
 * 				4- DIO_u8PORTD
 *
 * LEDA PIN:	1-DIO_u8PIN0
 * 				.
 * 				.
 * 				.
 * 				8- DIO_u8PIN7
 * 	*/

void main(void)
{


	PORT_voidInit();

	while (1)
	{
		LED_voidLED_ON(ACTIVE_HIGH, DIO_u8PORTC, DIO_u8PIN0);
		_delay_ms(2000);
		LED_voidLED_OFF(ACTIVE_HIGH, DIO_u8PORTC, DIO_u8PIN0);
		_delay_ms(2000);
		LED_voidLED_Toggle(DIO_u8PORTC, DIO_u8PIN2);
	}



}
