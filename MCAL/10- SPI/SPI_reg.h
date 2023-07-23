#ifndef SPI_REG_H_
#define SPI_REG_H_

#define SPCR			*((volatile uint8 *) 0x2D)			/*SPI control Register*/
#define SPCR_SPIE		7u									/*SPI Interrupt enable bit*/
#define SPCR_SPE		6u									/*SPI Perpheiral Enable*/
#define SPCR_DORD		5u									/*Data Order bit*/
#define SPCR_MSTR		4u									/*Master/Slave Select bit*/
#define SPCR_CPOL		3u									/*Clock Polarity Select bit*/
#define SPCR_CPHA		2u                                  /*Clock Phase select bit*/
#define SPCR_SPR1		1u                                  /*SPR1:0, SPI Clock rate select bits*/
#define SPCR_SPR0		0u


#define SPSR			*((volatile uint8 *) 0x2E)			/*SPI Status Register*/
#define SPSR_SPIF		7u                                  /*SPI Interrupt flag bit*/
#define SPSR_WCOL       6u                                  /*Write Collision Flag bit*/
#define SPSR_SPI2X      0u                                  /*Double SPI Speed bit*/

#define SPDR			*((volatile uint8 *) 0x2F)			/*Data Register*/

#endif
