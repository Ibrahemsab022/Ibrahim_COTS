/*****************************************************************/
/*****************************************************************/
/****************	Authour: Ibrahim Saber	**********************/
/****************	File: LED_program.c	**********************/
/****************	Version: 1.00	        **********************/
/*****************************************************************/
/*****************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "DIO_interface.h"

#include "LED_interface.h"
#include "LED_prv.h"


void LED_voidLED_ON(uint8 Copy_u8Activation, uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
	if (Copy_u8Activation == ACTIVE_HIGH)
	{
		DIO_u8SetPinValue(Copy_u8Port, Copy_u8Pin, DIO_u8PIN_HIGH);
	}

	else if (Copy_u8Activation == ACTIVE_LOW)
	{
		DIO_u8SetPinValue(Copy_u8Port, Copy_u8Pin, DIO_u8PIN_LOW);
	}
}

void LED_voidLED_OFF(uint8 Copy_u8Activation, uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
	if (Copy_u8Activation == ACTIVE_HIGH)
	{
		DIO_u8SetPinValue(Copy_u8Port, Copy_u8Pin, DIO_u8PIN_LOW);
	}

	else if (Copy_u8Activation == ACTIVE_LOW)
	{
		DIO_u8SetPinValue(Copy_u8Port, Copy_u8Pin, DIO_u8PIN_HIGH);
	}
}

void LED_voidLED_Toggle(uint8 Copy_u8Port, uint8 Copy_u8Pin)
{

		DIO_u8TogglePinValue(Copy_u8Port, Copy_u8Pin);

}
