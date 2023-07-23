#ifndef	TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

typedef enum
{
	TIMER0_OVF = 0,
	TIMER0_COMP

}TIMERS_Int_Src_t;

void TIMER0_voidInit(void);

uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_TmrIntSource, void(*Copy_pvCallBackFunc)(void));







#endif
