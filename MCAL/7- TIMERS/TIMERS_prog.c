#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "TIMERS_cfg.h"
#include "TIMERS_interface.h"
#include "TIMERS_prv.h"
#include "TIMERS_reg.h"


static void (*TIMERS_pvCallBackFuncArr[8])(void) = {NULL};


void TIMER0_voidInit(void)
{
	/*WaveForm Generation mode: Fast PWM*/
	SET_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);

	/*Clear the prescaler bits*/
	TCCR0 &= PRESCALER_MASK;

	/*Choosing the prescaler value*/
	TCCR0 |= DIVISON_BY_64;

	/*set on top, clear on compare*/
	CLR_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);

}


void TIMER1_voidInit(void)
{
	/*Normal Mode*/
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TCCR1B, TCCR1B_WGM13);


	/*Clear the prescaler bits*/
	TCCR1B &= PRESCALER_MASK;

	/*Choosing the prescaler value*/
	TCCR1B |= DIVISON_BY_64;

}


void TIMER0_voidSetCmpValue(uint8 Copy_u8Val)
{
	ORC0 = Copy_u8Val;
}


void TIMER1_voidSetCmpValue(uint16 Copy_u16Val)
{
	OCR1A = Copy_u16Val;
}

void TIMER1_voidSetTimerVal(uint16 Copy_u16Value)
{
	TCNT1 = Copy_u16Value;
}


uint16 TIMER1_voidGetTimerVal(void)
{
	return TCNT1;
}

void ICU_voidInit(void)
{

	#if ICU_u8_TRIGGER_SRC == RISING_EDGE
	SET_BIT(TCCR1B, TCCR1B_ICES1);

	#elif ICU_u8_TRIGGER_SRC == FALLING_EDGE
	CLR_BIT(TCCR1B, TCCR1B_ICES1);

	#else
	#error Wrong Selection of ICU Trigger Source

	#endif


	#if ICU_u8_INT_INIT_STATE == ENABLED
	SET_BIT(TIMSK, TIMSK_TICIE1);

	#elif ICU_u8_INT_INIT_STATE == DISABLED
	CLR_BIT(TIMSK, TIMSK_TICIE1);

	#else
	#error Wrong Selection of ICU Interrupt Initial State

	#endif

	/*Noise Canceler is off*/
	CLR_BIT(TCCR1B, TCCR1B_ICNC1);

}

uint8 ICU_u8SetTriggerSrc(uint8 Copy_u8TrigSrc)
{
	uint8 Local_u8ErrorState = OK;

	switch (Copy_u8TrigSrc)
	{
	case RISING_EDGE: SET_BIT(TCCR1B, TCCR1B_ICES1); break;
	case FALLING_EDGE: CLR_BIT(TCCR1B, TCCR1B_ICES1); break;
	default: Local_u8ErrorState = NOK; break;
	}

	/*Clearing the interrupt flag after each edge change, refer to datasheet p:92*/
	SET_BIT(TIFR, TIFR_ICF1);


	return Local_u8ErrorState;
}

void ICU_voidIntEnable(void)
{
	SET_BIT(TIMSK, TIMSK_TICIE1);
}


void ICU_voidIntDisable(void)
{
	CLR_BIT(TIMSK, TIMSK_TICIE1);
}

uint16 ICU_u16GetInputValue(void)
{
	return ICR1;
}



uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_TmrIntSource, void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState = OK;

	if (Copy_pvCallBackFunc != NULL)
	{
		TIMERS_pvCallBackFuncArr[Copy_TmrIntSource] = Copy_pvCallBackFunc;
	}


	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


/*************************************************************************************************************/

void TIMER2_voidInit(void)
{
	/*Selecting Normal Mode*/
	CLR_BIT(TCCR2, TCCR2_WGM21);
	CLR_BIT(TCCR2, TCCR2_WGM20);
	CLR_BIT(TCCR2, TCCR2_COM20);
	CLR_BIT(TCCR2, TCCR2_COM21);

	/*Set prescaler value to 256, tick time = 16 us*/
	SET_BIT(TCCR2, TCCR2_CS22);
	SET_BIT(TCCR2, TCCR2_CS21);
	CLR_BIT(TCCR2, TCCR2_CS20);

	/*Enabling the Over flow interrupt*/
	SET_BIT(TIMSK, TIMSK_TOIE2);

}
void TIMER2_voidGetNumberOfTicks(void)
{

}
void TIMER2_voidStartTimer(void)
{

}
void TIMER2_voidStopTimer(void)
{

}

/****************************************************************************************************************/


void __vector_5 (void) __attribute__((signal));
void __vector_5 (void)
{
	if (TIMERS_pvCallBackFuncArr[TIMER2_OVF] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER2_OVF]();
	}
}

void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if (TIMERS_pvCallBackFuncArr[TIMER1_ICU] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER1_ICU]();
	}
}


void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if (TIMERS_pvCallBackFuncArr[TIMER0_COMP] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER0_COMP]();
	}
}

