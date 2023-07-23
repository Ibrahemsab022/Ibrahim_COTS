#include "STD_TYPES.h"
#include "defines.h"
#include "BIT_MATH.h"

#include "UART_reg.h"
#include "UART_interface.h"


void UART_voidInit(void)
{

	uint8 Local_u8UCSRCValue = 0u;

	/*Transimtter Enable*/
	SET_BIT(UCSRB, UCSRB_TXEN);

	/*Reciver Enable*/
	SET_BIT(UCSRB, UCSRB_RXEN);

	/*Asynch Mode select*/
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UMSEL);

	/*Disable Parity*/
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UPM0);
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UPM1);

	/*Selects stop bit = 1 bit*/
	CLR_BIT(Local_u8UCSRCValue, UCSRC_USBS);

	/*Character Size: 8 bits*/
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
	CLR_BIT(UCSRB, UCSRB_UCSZ2);


	/*Register select UCSRC*/
	SET_BIT(Local_u8UCSRCValue, UCSRC_URSEL);

	/*Assigning the final configs of UCSRC to the register*/
	UCSRC = Local_u8UCSRCValue;

	/*Baud Rate: 9600bPs*/
	UBRRL = 103u;

}

void UART_voidTransmit(uint8 Copy_u8Data)
{
	/*Wait until the transmit buffer is ready*/
	while((GET_BIT(UCSRA, UCSRA_UDRE)) == 0);

	UDR = Copy_u8Data;
}


uint8 UART_u8Recive(void)
{

	while((GET_BIT(UCSRA, UCSRA_RXC)) == 0);

	return UDR;

}
