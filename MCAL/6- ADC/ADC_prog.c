/**
 * @file			ADC_prog.c
 * @brief			This file implements the ADC driver
 * @author			Ibrahim Saber
 * @version			1.0
 * @date			19-4-2023
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"


#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_Interface.h"


/*those are global variables to store in them the parameters of the StartConvAsych to make them shown to the ISR (globally)*/
static uint16* ADC_pu16ConversionResult = NULL;
static void(*ADC_pvNotificationFunc)(void) = NULL;
static uint8 ADC_u8BusyFlag = IDLE;
static ADC_ChainConv_t* ADC_pstChainData = NULL;
static uint8 ADC_u8ChannelCounter;
static uint8 ADC_u8InterruptSource;

void ADC_voidInit(void)
{

	/*Initializing the Reference voltage configuration*/
#if REFERENCE_SELECTION == AVCC
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);
#elif REFERENCE_SELECTION == AREF
	CLR_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

#elif REFERENCE_SELECTION == INTERNAL_REF
	SET_BIT(ADMUX, ADMUX_REFS0);
	SET_BIT(ADMUX, ADMUX_REFS1);

#else
#error Wrong REFERENCE_SELECTION configuration option

#endif


	/*Initializing the result adjustment mode according to the resolution configuration*/
#if ADC_RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX, ADMUX_ADLAR);

#elif ADC_RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX, ADMUX_ADLAR);

#else
#error Wrong ADC_RESOLUTION configuration option

#endif

	/*Implementing the Auto-trigger mode configuration*/
#if ADC_AUTO_TRIGGER == DISABLED
	CLR_BIT(ADCSRA, ADCSRA_ADATE);

#elif ADC_AUTO_TRIGGER == ENABLED;
	SET_BIT(ADCSRA, ADCSRA_ADATE);

#else
#error Wrong ADC_AUTO_TRIGGER configuration option

#endif


	/*Implementing the Interrupt enable mode configuration*/
#if ADC_INTERRUPT_ENABLE == DISABLED
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

#elif ADC_INTERRUPT_ENABLE == ENABLED;
	SET_BIT(ADCSRA, ADCSRA_ADIE);

#else
#error Wrong ADC_INTERRUPT_ENABLE configuration option

#endif



	/*Initializing the Prescaler configuration*/
	ADCSRA &= PRESCALER_MASK;
	ADCSRA |= PRESCALER_SELECTION;

/*#if PRESCALER_SELECTION == DIVISION_FACTOR_2
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	CLR_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER_SELECTION == DIVISION_FACTOR_4
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	CLR_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER_SELECTION == DIVISION_FACTOR_8
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	CLR_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER_SELECTION == DIVISION_FACTOR_16
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER_SELECTION == DIVISION_FACTOR_32
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER_SELECTION == DIVISION_FACTOR_64
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER_SELECTION == DIVISION_FACTOR_128
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS2);

#endif*/



	/*Enabling the ADC*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);

}


uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result)
{

	uint8 Local_u8ErrorState = OK;

	if (Copy_pu16Result != NULL)
	{
		/*check if ADC is not busy*/
		if (ADC_u8BusyFlag == IDLE)
		{
			uint32 Local_u32TimeoutCounter = 0u;

			/*ADC is now Busy*/
			ADC_u8BusyFlag = BUSY;


			/*Setting the required channel*/
			ADMUX &= CHANNEL_MASK;
			ADMUX |= Copy_u8Channel;

			/*ADC Start Conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*waiting for the conversion done flag or timeout is passed*/
			while ((GET_BIT(ADCSRA, ADCSRA_ADIF) == 0) && (Local_u32TimeoutCounter < ADC_u32TIMEOUT))
			{
				Local_u32TimeoutCounter++;
			}

			if (Local_u32TimeoutCounter >= ADC_u32TIMEOUT)
			{
				/*Loop is broken because flag isn't raised until time out is passed*/
				Local_u8ErrorState = TIMEOUT_ERR;
			}

			else
			{
				/*Loop is broken because flag is raised before timeout is passed*/

				/*Clearing the flag after conversion done*/
					SET_BIT(ADCSRA, ADCSRA_ADIF);

				#if ADC_RESOLUTION == EIGHT_BITS
					*Copy_pu16Result = ADCH;

				#elif ADC_RESOLUTION == TEN_BITS
					*Copy_pu16Result = ADC;

				#endif

					/*ADC is now Idle*/
					ADC_u8BusyFlag = IDLE;

			}

		}


		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}

	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}


	return Local_u8ErrorState;

}











uint8 ADC_u8StartSingleConversionAsynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result, void(*Copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;

	if ((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{

		if (ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now Busy*/
			ADC_u8BusyFlag = BUSY;

			/*Setting the interrupt source flag*/
			ADC_u8InterruptSource = SINGLE_CONV_ASYNCH;

			/*Initializes the result pointer globally*/
			ADC_pu16ConversionResult = Copy_pu16Result;

			/*Initializes the result pointer globally*/
			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			/*Setting the required channel*/
			ADMUX &= CHANNEL_MASK;
			ADMUX |= Copy_u8Channel;

			/*ADC Start Conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable the ADC conversion complete interrupt*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);

		}

		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}


	}

	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


uint8 ADC_u8StartChainConversionAsynch(ADC_ChainConv_t* Copy_pstChain)
{
	uint8 Local_u8ErrorState = OK;

	if ((Copy_pstChain != NULL) && (Copy_pstChain -> ChainArr != NULL) && (Copy_pstChain -> NotificationFunc != NULL) && (Copy_pstChain->ResultArr != NULL))
	{
		/*Check if ADC is availabe*/
		if (ADC_u8BusyFlag == IDLE)
		{
			/*use it, now it's busy*/
			ADC_u8BusyFlag = BUSY;


			/*Setting the interrupt source flag*/
			ADC_u8InterruptSource = CHAIN_CONV_ASYNCH;


			/*Initializing the Global Chain data (variables)*/
			ADC_pstChainData = Copy_pstChain;
			ADC_u8ChannelCounter = 0u;


			/*Set the first Channel*/
			ADMUX &= CHANNEL_MASK;
			ADMUX |= ADC_pstChainData -> ChainArr[ADC_u8ChannelCounter];


			/*Starting the first conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);


			/*Enable ADC conversion Copmlete interrupt*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);


		}

		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}

	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}



/*
 *@brief ADC Conversion complete ISR
 *
 */
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{

	if (ADC_u8InterruptSource == SINGLE_CONV_ASYNCH)
	{
		if (ADC_pu16ConversionResult != NULL)
		{
		#if ADC_RESOLUTION == EIGHT_BITS
			*ADC_pu16ConversionResult = ADCH;

		#elif ADC_RESOLUTION == TEN_BITS
			*ADC_pu16ConversionResult = ADC;
		#endif

		/*Disable the ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA, ADCSRA_ADIE);

		/*ADC is now Idle*/
		ADC_u8BusyFlag = IDLE;

		/*Invoke the application notification function*/
		if (ADC_pvNotificationFunc != NULL)
		{
			ADC_pvNotificationFunc();
		}

		else
		{
			/*ADC_pvNotificationFunc is NULL*/
		}

	}

	else
	{
			/*just to follow MESRA rules*/
			/*ADC_puConversionResult is NULL*/
	}

	}

	else /*Interrupt is due to chain conversion*/
	{
		/*Redaing data from ADC Registers*/
		#if ADC_RESOLUTION == EIGHT_BITS
			ADC_pstChainData -> ResultArr[ADC_u8ChannelCounter] = ADCH;

		#elif ADC_RESOLUTION == TEN_BITS
			ADC_pstChainData -> ResultArr[ADC_u8ChannelCounter] = ADC;
		#endif


			/*Incrementing the chain counter*/
			ADC_u8ChannelCounter++;

			if(ADC_u8ChannelCounter < ADC_pstChainData -> ChainSize)
			{
				/*Chain is not finished yet*/

				/*Starting the next Conversion*/
				/*Set the first Channel*/
				ADMUX &= CHANNEL_MASK;
				ADMUX |= ADC_pstChainData -> ChainArr[ADC_u8ChannelCounter];

				/*Starting the conversion*/
				SET_BIT(ADCSRA, ADCSRA_ADSC);


			}

			else
			{
				/*Chain is done*/

				/*ADC is now IDLE*/
				ADC_u8BusyFlag = IDLE;

				/*Disable the ADC interrupt*/
				CLR_BIT(ADCSRA, ADCSRA_ADIE);

				/*Invoke the Notification Function*/
				if (ADC_pstChainData -> NotificationFunc != NULL)
				{
					ADC_pstChainData -> NotificationFunc();
				}

				else
				{
					/*do nothing*/
				}

			}

	}


}
