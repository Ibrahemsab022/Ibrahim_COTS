#include "STD_TYPES.h"
#include "defines.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SPI_prv.h"
#include "SPI_cfg.h"
#include "SPI_reg.h"
#include "SPI_interface.h"




void SPI_voidInit(void)
{

	/*Congiuring The interrupt of the SPI Peripheral*/
#if	SPI_INTERRUPT_INITIAL_STATE == DISABLED
	    CLR_BIT(SPCR, SPCR_SPIE);

#elif	SPI_INTERRUPT_INITIAL_STATE == ENABLED
		SET_BIT(SPCR, SPCR_SPIE);

#else
#error Wrong Configuration of Interrupt Intital State of SPI

#endif


		/*Coniguring the Data Order*/
#if SPI_DATA_ORDER == LSB_FIRST
		SET_BIT(SPCR, SPCR_DORD);

#elif SPI_DATA_ORDER == MSB
		CLR_BIT(SPCR, SPCR_DORD);

#else
#error Wrong Configuration of Data Order of the SPI

#endif


		/*Configuring the microcontroller mdoe*/
#if SPI_MICRO_MODE_SELECT == MASTER_MODE
		SET_BIT(SPCR, SPCR_MSTR);

#elif SPI_MICRO_MODE_SELECT == SLAVE_MODE
		CLR_BIT(SPCR, SPCR_MSTR);

#else
#error Wrong Configuration of Microcontroller mode Select of the SPI

#endif

		/*Configuring The Clk Ploarity*/
#if SPI_CLK_POLARITY == LEADING_RISING
		CLR_BIT(SPCR, SPCR_CPOL);

#elif SPI_CLK_POLARITY == LEADING_FALLING
		SET_BIT(SPCR, SPCR_CPOL);

#else
#error Wrong Configuration of CLK Polarity of SPI

#endif

		/*Configuring The clk phase*/
#if SPI_CLK_PHASE == SAMPLE_FIRST
		CLR_BIT(SPCR, SPCR_CPHA);

#elif SPI_CLK_PHASE	== SETUP_FIRST
		SET_BIT(SPCR, SPCR_CPHA);

#else
#error Wrong Configuration of Clk Phase of SPI

#endif

		/*Configuring The Clk Rate*/

#if SPI_CLK_RATE == DIVIDE_BY_4
		CLR_BIT(SPSR, SPSR_SPI2X);
		CLR_BIT(SPCR, SPCR_SPR1);
		CLR_BIT(SPCR, SPCR_SPR0);


#elif SPI_CLK_RATE == DIVIDE_BY_16
		CLR_BIT(SPSR, SPSR_SPI2X);
		CLR_BIT(SPCR, SPCR_SPR1);
		SET_BIT(SPCR, SPCR_SPR0);

#elif SPI_CLK_RATE == DIVIDE_BY_64
		CLR_BIT(SPSR, SPSR_SPI2X);
		SET_BIT(SPCR, SPCR_SPR1);
		CLR_BIT(SPCR, SPCR_SPR0);

#elif SPI_CLK_RATE == DIVIDE_BY_128
		CLR_BIT(SPSR, SPSR_SPI2X);
		SET_BIT(SPCR, SPCR_SPR1);
		SET_BIT(SPCR, SPCR_SPR0);

#elif SPI_CLK_RATE == DIVIDE_BY_2
		SET_BIT(SPSR, SPSR_SPI2X);
		CLR_BIT(SPCR, SPCR_SPR1);
		CLR_BIT(SPCR, SPCR_SPR0);

#elif SPI_CLK_RATE == DIVIDE_BY_8
		SET_BIT(SPSR, SPSR_SPI2X);
		CLR_BIT(SPCR, SPCR_SPR1);
		SET_BIT(SPCR, SPCR_SPR0);

#elif SPI_CLK_RATE == DIVIDE_BY_32
		SET_BIT(SPSR, SPSR_SPI2X);
		SET_BIT(SPCR, SPCR_SPR1);
		CLR_BIT(SPCR, SPCR_SPR0);

#else
#error Wrong Configuration of Clk Rate of SPI

#endif

		/*Enable the SPI Perphieral*/
		SET_BIT(SPCR, SPCR_SPE);


}





uint8 SPI_u8Transceive(uint8 Copy_u8Data)
{

	/*starting Transmission*/
	SPDR = Copy_u8Data;

	/*Wait for transmission to complete*/
	while (GET_BIT(SPSR, SPSR_SPIF) == 0);


	/*Return the data reg*/
	return SPDR;
}
