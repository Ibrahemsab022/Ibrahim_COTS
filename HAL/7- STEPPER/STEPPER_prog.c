#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "STEPPER_interface.h"






uint8 STEPPER_u8Rotate(const STEPPER_T* Copy_pStepper, uint16 Copy_u16Angle, uint8 Copy_u8Direction)
{

	uint8 Local_u8ErrorState = OK;

	if (Copy_pStepper != NULL)
	{
		Local_u8ErrorState = OK;
		uint16 Local_u16Steps;
		uint16 Local_u16Counter;

		Local_u16Steps = ((uint16) (((uint32)Copy_u16Angle * 2048UL) / 360UL));

		if (Copy_u8Direction == CCW)
		{
			for (Local_u16Counter = 0; Local_u16Counter < Local_u16Steps; Local_u16Counter++)
			{

				if (Local_u16Counter % 4 == 0)
				{
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->BluePin, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->PinkPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->YellowPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->OrangePin, DIO_u8PIN_LOW);
					_delay_ms(2);
				}

				else if (Local_u16Counter % 4 == 1)
				{
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->PinkPin, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->BluePin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->YellowPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->OrangePin, DIO_u8PIN_LOW);
					_delay_ms(2);
				}

				else if (Local_u16Counter % 4 == 2)
				{
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->YellowPin, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->PinkPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->BluePin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->OrangePin, DIO_u8PIN_LOW);
					_delay_ms(2);
				}

				else if (Local_u16Counter % 4 == 3)
				{
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->OrangePin, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->PinkPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->YellowPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->BluePin, DIO_u8PIN_LOW);
					_delay_ms(2);
				}

			}
		}

		else if (Copy_u8Direction == CW)
		{
			for (Local_u16Counter = 0; Local_u16Counter < Local_u16Steps; Local_u16Counter++)
			{

				if (Local_u16Counter % 4 == 0)
				{
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->OrangePin, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->PinkPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->YellowPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->BluePin, DIO_u8PIN_LOW);
					_delay_ms(2);
				}

				else if (Local_u16Counter % 4 == 1)
				{

					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->YellowPin, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->BluePin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->BluePin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->OrangePin, DIO_u8PIN_LOW);
					_delay_ms(2);
				}


				else if (Local_u16Counter % 4 == 2)
				{

					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->PinkPin, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->BluePin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->YellowPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->OrangePin, DIO_u8PIN_LOW);
					_delay_ms(2);
				}

				else if (Local_u16Counter % 4 == 3)
				{
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->BluePin, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->PinkPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->YellowPin, DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pStepper->PORT, Copy_pStepper->OrangePin, DIO_u8PIN_LOW);
					_delay_ms(2);
				}

			}
		}

	}

	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}


	return Local_u8ErrorState;

}
