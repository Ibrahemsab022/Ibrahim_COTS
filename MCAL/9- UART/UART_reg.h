#ifndef UART_REG_H_
#define UART_REG_H_

#define UDR					*((volatile uint8 *) 0x2C)		/*USART DATA register*/


#define UCSRA				*((volatile uint8 *) 0x2B)		/*Control and status reg A*/
#define UCSRA_RXC			7u								/*Recive Compelete flag*/
#define UCSRA_TXC			6u								/*Trasmitt compelete flag*/
#define UCSRA_UDRE			5u								/*Indicate the transmitt buffer is ready to recive new data*/
#define UCSRA_FE			4u								/*Frame error bit*/
#define UCSRA_DOR			3u								/*Data overrun bit flag*/
#define UCSRA_PE			2u								/*Parity Error flag bit*/
#define UCSRA_U2X			1u								/*Double The transmission speed bit*/
#define UCSRA_MPCM			0u								/*Multi-processor Communication Mode bit*/



#define UCSRB				*((volatile uint8 *) 0x2A)      /*Control and status reg B*/
#define UCSRB_RXCIE			7u								/*RX Compelete interrupt enable*/
#define UCSRB_TXCIE			6u								/*TX Compelete interrupt enable*/
#define UCSRB_UDRIE			5u								/*Data reg empty interrupt enable*/
#define UCSRB_RXEN			4u								/*Reciver Enable*/
#define UCSRB_TXEN			3u								/*Transimitter Enable*/
#define UCSRB_UCSZ2			2u								/*combined with UCSZ1,UCSZ0 selects the size of data 5-9 bits*/
#define UCSRB_RXB8			1u								/*in case 9 bits used, the 8th will be here*/
#define UCSRB_TXB8			0u								/*in case 9 bits used, the 8th will be here*/




#define UCSRC				*((volatile uint8 *) 0x40)		/*Control and status reg C*/
#define UCSRC_URSEL			7u								/*This bit selects between accessing UCSRC or UBRRH*/
#define UCSRC_UMSEL         6u								/*Selects USART or UART Mode: Synch vs Asynch*/
#define UCSRC_UPM1          5u								/*bit5-4 selects parity mode*/
#define UCSRC_UPM0          4u
#define UCSRC_USBS          3u								/*Stop bit select mode*/
#define UCSRC_UCSZ1         2u								/*bits 2-1 combined with UCSRB_UCSZ2 slects data size*/
#define UCSRC_UCSZ0         1u
#define UCSRC_UCPOL         0u								/*Clock ploarity mode select*/




#define UBRRH				*((volatile uint8 *) 0x40)		/*Control and status reg C*/
#define UBRRH_URSEL			7u								/*This bit selects between accessing UCSRC or UBRRH*/
#define UBRRH_B6         	6u								/*bits 6-4 Reserved*/
#define UBRRH_B5          	5u
#define UBRRH_B4          	4u
#define UBRRH_B3          	3u								/*bits 3-0 Baud Rate Register high*/
#define UBRRH_B2         	2u								/*bits 2-1 combined with UCSRB_UCSZ2 slects data size*/
#define UBRRH_B0         	1u
#define UBRRH_B1         	0u

#define UBRRL				*((volatile uint8 *) 0x29)		/*Baud Rate Register LOW*/



#endif
