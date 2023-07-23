#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "TWI_interface.h"
#include "TWI_cfg.h"
#include "TWI_prv.h"
#include "TWI_reg.h"


/*In case of the master will not be addressed, pass the adress parameter as zero*/
void TWI_voidMasterInit(uint8 Copy_u8Adress)
{
	if (Copy_u8Adress != 0u)
	{
		TWAR = Copy_u8Adress << 1u;
	}

	/*CPU Freq = 16 MHz, Prescaler = 0, Communication Freq = 400KHz*/
	CLR_BIT(TWSR, TWSR_TWPS0);
	CLR_BIT(TWSR, TWSR_TWPS1);
	TWBR = 12u;

	/*Enable TWI*/
	SET_BIT(TWCR, TWCR_TWEN);
}


/*******************************************************************************************************/


void TWI_voidSalveInit(uint8 Copy_u8Adress)
{

	/*Setting node adress*/
	TWAR = Copy_u8Adress << 1u;

	/*Enable Acknlowdege*/
	SET_BIT(TWCR, TWCR_TWEA);


	/*Enable TWI*/
	SET_BIT(TWCR, TWCR_TWEN);
}


TWI_ErrorStatus_t TWI_SendStartCondition(void)
{
	TWI_ErrorStatus_t Local_ErrorState = NoError;

	/*Set Start Condition bit*/
	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear The interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Wait unitl the previous action finishes, and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if ((TWSR & STATUS_BITS_MASK) != START_ACK)
	{
		Local_ErrorState = StartConditionError;
	}

	else
	{
		/*Do nothing*/
	}

	return Local_ErrorState;
}


/*******************************************************************************************************/


TWI_ErrorStatus_t TWI_SendRepeatedStart(void)
{
	TWI_ErrorStatus_t Local_ErrorState = NoError;

	/*Set Start Condition bit*/
	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear The interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Wait unitl the previous action finishes, and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if ((TWSR & STATUS_BITS_MASK) != REP_START_ACK)
	{
		Local_ErrorState = RepeatedStartError;
	}

	else
	{
		/*Do nothing*/
	}

	return Local_ErrorState;
}


/*******************************************************************************************************/


TWI_ErrorStatus_t TWI_SendSlaveAdressWithWrite(uint8 Copy_u8SlaveAdress)
{
	TWI_ErrorStatus_t Local_ErrorState = NoError;

	/*Set The slave address into the data register*/
	TWDR = Copy_u8SlaveAdress << 1u;

	/*Clear Bit zero for write request*/
	CLR_BIT(TWDR, 0u);

	/*Clear the start Condition bit*/
	CLR_BIT(TWCR, TWCR_TWSTA);

	/*Clear The interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Wait unitl the previous action finishes, and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if ((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_ErrorState = SlaveAdressWithWriteError;
	}

	else
	{
		/*Do nothing*/
	}

	return Local_ErrorState;
}


/*******************************************************************************************************/


TWI_ErrorStatus_t TWI_SendSlaveAdressWithRead(uint8 Copy_u8SlaveAdress)
{
	TWI_ErrorStatus_t Local_ErrorState = NoError;

	/*Set The slave address into the data register*/
	TWDR = Copy_u8SlaveAdress << 1u;

	/*Set Bit zero for Read request*/
	SET_BIT(TWDR, 0u);

	/*Clear the start Condition bit*/
	CLR_BIT(TWCR, TWCR_TWSTA);

	/*Clear The interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Wait unitl the previous action finishes, and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if ((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_ErrorState = SlaveAdressWithReadError;
	}

	else
	{
		/*Do nothing*/
	}

	return Local_ErrorState;
}


/*******************************************************************************************************/


TWI_ErrorStatus_t TWI_MasterWriteDataByte(uint8 Copy_u8DataByte)
{
	TWI_ErrorStatus_t Local_ErrorState = NoError;

	/*Set the DataByte in the Data Register (put data on the bus)*/
	TWDR = Copy_u8DataByte;

	/*Clear The interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Wait unitl the previous action finishes, and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if ((TWSR & STATUS_BITS_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_ErrorState = MasterWriteByteWithAckError;
	}

	else
	{
		/*Do nothing*/
	}


	return Local_ErrorState;
}


/*******************************************************************************************************/


TWI_ErrorStatus_t TWI_MasterReadDataByte(uint8* Copy_pu8DataByte)
{
	TWI_ErrorStatus_t Local_ErrorState = NoError;

	if (Copy_pu8DataByte != NULL)
	{
		/*Clear The interrupt flag to enable slave to send data*/
		SET_BIT(TWCR, TWCR_TWINT);

		/*Wait unitl the slave writing finish and the interrupt flag is raised again*/
		while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

		/*Check the status of the bus*/
		if ((TWSR & STATUS_BITS_MASK) != MSTR_RD_BYTE_WITH_ACK)
		{
			Local_ErrorState = MasterReadBytedWithAckError;
		}

		else
		{
			/*Reading the bus*/
			*Copy_pu8DataByte = TWDR;
		}

	}

	else
	{
		Local_ErrorState = NullPtrErr;
	}


	return Local_ErrorState;
}


/*******************************************************************************************************/



TWI_ErrorStatus_t TWI_SendStopCondition(void)
{
	TWI_ErrorStatus_t Local_ErrorState = NoError;

	/*Setting the stop condition bit*/
	SET_BIT(TWCR, TWCR_TWSTO);

	/*Clear The interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);


	return Local_ErrorState;
}


