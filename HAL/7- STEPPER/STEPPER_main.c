#include "STD_TYPES.h"
#include "util/delay.h"

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "STEPPER_interface.h"

/*configure the data of the STEPPER in the struct STEPPER_T,
 * PORT:		1- DIO_u8PORTA
 * 				2- DIO_u8PORTB
 * 				3- DIO_u8PORTC
 * 				4- DIO_u8PORTD
 *
 * BluePin:		1-DIO_u8PIN0		for the first coil
 * 				.
 * 				.
 * 				.
 * 				8- DIO_u8PIN7
 *
 *
 * PinkPin:		1-DIO_u8PIN0  		for the second coil
 * 				.
 * 				.
 * 				.
 * 				8- DIO_u8PIN7
 *
 * YellowPin:		1-DIO_u8PIN0 	for the third coil
 * 				.
 * 				.
 * 				.
 * 				8- DIO_u8PIN7
 *
 * OrangePin:		1-DIO_u8PIN0  	for the fourth coil
 * 				.
 * 				.
 * 				.
 * 				8- DIO_u8PIN7
 *
 * 	*/




void main(void)
{

	PORT_voidInit();


	STEPPER_T STEPPER = {DIO_u8PORTC, DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3};

	const STEPPER_T* PtrToStepper = &STEPPER;

	while (1)
	{
		STEPPER_u8Rotate(PtrToStepper, 30, CW);
		_delay_ms(2000);
		STEPPER_u8Rotate(PtrToStepper, 30, CW);
		_delay_ms(2000);
	/*	STEPPER_u8Rotate(PtrToStepper, 45, CCW);
		STEPPER_u8Rotate(PtrToStepper, 60, CCW);
		_delay_ms(5000);*/

	}

}
