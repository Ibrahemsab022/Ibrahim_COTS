#ifndef	TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_


#define FALLING_EDGE		1u
#define RISING_EDGE			2u


typedef enum
{
	TIMER0_OVF = 0,
	TIMER0_COMP,
	TIMER1_ICU,
	TIMER2_OVF,

}TIMERS_Int_Src_t;




void TIMER0_voidInit(void);

void TIMER1_voidInit(void);

uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_TmrIntSource, void(*Copy_pvCallBackFunc)(void));

void TIMER0_voidSetCmpValue(uint8 Copy_u8Val);


void TIMER1_voidSetCmpValue(uint16 Copy_u16Val);

void TIMER1_voidSetTimerVal(uint16 Copy_u16Value);

uint16 TIMER1_voidGetTimerVal(void);

void ICU_voidInit(void);

uint8 ICU_u8SetTriggerSrc(uint8 Copy_u8TrigSrc);

void ICU_voidIntEnable(void);

void ICU_voidIntDisable(void);

uint16 ICU_u16GetInputValue(void);

void TIMER2_voidInit(void);
void TIMER2_voidGetNumberOfTicks(void);
void TIMER2_voidStartTimer(void);
void TIMER2_voidStopTimer(void);





#endif
