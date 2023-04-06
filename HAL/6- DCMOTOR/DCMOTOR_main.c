#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "DCMOTOR_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"


/*configure the data of the DCMOTOR in the struct DCMOTOR_T,
 * PORT:		1- DIO_u8PORTA
 * 				2- DIO_u8PORTB
 * 				3- DIO_u8PORTC
 * 				4- DIO_u8PORTD
 *
 * PIN2_3:		1-DIO_u8PIN0		The pins 2,3 of the H-Bridge
 * 				.
 * 				.
 * 				.
 * 				8- DIO_u8PIN7
 *
 * PIN1_4:		1-DIO_u8PIN0  		The pins 1,4 of the H-Bridge
 * 				.
 * 				.
 * 				.
 * 				8- DIO_u8PIN7
 * 	*/




void main(void)
{

	PORT_voidInit();
	CLCD_voidInit();


	DCMOTOR_T	MOTOR1 = {DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN1};

	const DCMOTOR_T* PtrToMOTOR1 = &MOTOR1;

	CLCD_u8SendString("Welcome to:");
	CLCD_voidGoToXY(0,1);
	CLCD_u8SendString("DC Motor Dashboard");
	_delay_ms(4000);

	CLCD_voidSendCmd(1);

	CLCD_u8SendString("Rotate CW (1)");
	CLCD_voidGoToXY(0,1);
	CLCD_u8SendString("Rotate CCW (2)");


	uint8 Local_u8PressedKey;
	uint8 Local_u8MotorOn = 0;



	while (1)
	{
		Local_u8PressedKey = KPD_u8GetPressedKey();


		switch (Local_u8PressedKey)
		{
		 case 'C':
		 {
			 Local_u8MotorOn = 1;

			 DCMOTOR_u8RotateCW(PtrToMOTOR1);
			 CLCD_voidSendCmd(1);
			 CLCD_u8SendString("rotating CW...");
			 CLCD_voidGoToXY(0,1);
			 CLCD_u8SendString("To stop (3)");
			 break;
		 }

		 case 'W':
		 {
			 Local_u8MotorOn = 1;

			 DCMOTOR_u8RotateCCW(PtrToMOTOR1);
			 CLCD_voidSendCmd(1);
			 CLCD_u8SendString("rotating CCW...");
			 CLCD_voidGoToXY(0,1);
			 CLCD_u8SendString("To stop (3)");
			 break;
		 }

		 case 'S':
		 {
			 if (Local_u8MotorOn == 1)
			 {
				 Local_u8MotorOn = 0;

				 CLCD_voidSendCmd(1);
				 CLCD_u8SendString("Stopping");
				 _delay_ms(100);
				 CLCD_voidSendData('.');
				 _delay_ms(100);
				 CLCD_voidSendData('.');
				 _delay_ms(100);
				 CLCD_voidSendData('.');
				 _delay_ms(100);
				 CLCD_voidSendData('.');
				 _delay_ms(100);
				 CLCD_voidSendData('.');
				 _delay_ms(100);
				 CLCD_voidSendData('.');
				 _delay_ms(100);

				 DCMOTOR_u8Stop(PtrToMOTOR1);


				 CLCD_voidSendCmd(1);
				 CLCD_u8SendString("Rotate CW (1)");
				 CLCD_voidGoToXY(0,1);
				 CLCD_u8SendString("Rotate CCW (2)");
			 }

		 }
		}

	}

}
