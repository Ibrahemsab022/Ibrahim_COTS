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
	/*WaveForm Generation mode: CTC*/
	CLR_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);

	/*Clear the prescaler bits*/
	TCCR0 &= PRESCALER_MASK;

	/*Choosing the prescaler value*/
	TCCR0 |= DIVISON_BY_64;

	/*set compare value*/
	ORC0 = 250;

	/*Enable PIE of timer0 compare match event*/
	SET_BIT(TIMSK, TIMSK_OCIE0);

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


void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if (TIMERS_pvCallBackFuncArr[TIMER0_COMP] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER0_COMP]();
	}
}

