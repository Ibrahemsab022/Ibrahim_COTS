#include "STD_TYPES.h"
#include <util/delay.h>


#include "PORT_interface.h"
#include "DIO_interface.h"
#include "SSD_prv.h"
#include "SSD_interface.h"


/*configure the data of the SSD in the struct SSD_T,
 * Type:		1- ANODE
 * 				2- CATHODE
 * 				3- ETA_KIT
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
 *
 * 	Enable PORT
 * 	Enable PIN
 *
 * 	*/


void main(void)
{
	PORT_voidInit();

	SSD_T SSD1 = {ETA_KIT, DIO_u8PORTA, DIO_u8PIN1, DIO_u8PORTC, DIO_u8PIN6};
	SSD_T SSD2 = {ETA_KIT, DIO_u8PORTA, DIO_u8PIN1, DIO_u8PORTC, DIO_u8PIN7};

	const SSD_T* PtrToSSD1 = &SSD1;
	const SSD_T* PtrToSSD2 = &SSD2;

	/*uint8 Local_u8Iterrator;*/
	/*SSD_u8SSD_ON(PtrToSSD1);*/
	while (1)
	{

	/*	for (Local_u8Iterrator = 0; Local_u8Iterrator < 10; Local_u8Iterrator++)
		{
			SSD_u8SetNumber(PtrToSSD1, Local_u8Iterrator);
			_delay_ms(1000);
		}*/

		SSD_u8SSD_ON(PtrToSSD1);
		SSD_u8SSD_OFF(PtrToSSD2);

		SSD_u8SetNumber(PtrToSSD1, 4);
		_delay_ms(10);

		SSD_u8SSD_OFF(PtrToSSD1);
		SSD_u8SSD_ON(PtrToSSD2);

		SSD_u8SetNumber(PtrToSSD2, 2);
		_delay_ms(10);






	}
}

