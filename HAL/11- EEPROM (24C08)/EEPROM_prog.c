#include "STD_TYPES.h"
#include "defines.h"
#include <util/delay.h>

#include "TWI_interface.h"

#include "EEPROM_cfg.h"
#include "EEPROM_interface.h"
#include "EEPROM_prv.h"



uint8 EEPROM_u8WriteDataByte(uint16 Copy_u16LocAddress, uint8 Copy_u8DataByte)
{
	uint8 Local_u8ErroState = OK;

	if (Copy_u16LocAddress <= EEPROM_MAX_ADDRESS)
	{
		uint8 Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (EEPROM_A2_CONNECTION << 2) | (uint8)(Copy_u16LocAddress >> 8);

		TWI_SendStartCondition();

		/*Send the address packet with fixed address and the A2 connection and the first 2 bits of the loc address*/
		TWI_SendSlaveAdressWithWrite(Local_u8AddressPacket);

		/*Send a data packet with the least 8 bits of the location address*/
		TWI_MasterWriteDataByte((uint8) Copy_u16LocAddress);

		/*Send a data packet with the required data byted to be wrtitten into memory*/
		TWI_MasterWriteDataByte(Copy_u8DataByte);

		/*Sending stop condition*/
		TWI_SendStopCondition();

		/*wait for the writing time of the EEPROM: 10ms*/
		_delay_ms(10);
	}

	else
	{
		Local_u8ErroState = NOK;
	}


	return Local_u8ErroState;
}


/*************************************************************************************************/

uint8 EEPROM_u8ReadDataByte(uint16 Copy_u16LocAddress, uint8* Copy_pu8DataByte)
{
	uint8 Local_u8ErroState = OK;

	if (Copy_pu8DataByte != NULL)
	{
		if (Copy_u16LocAddress <= EEPROM_MAX_ADDRESS)
			{
				uint8 Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (EEPROM_A2_CONNECTION << 2) | (uint8)(Copy_u16LocAddress >> 8);

				TWI_SendStartCondition();

				/*Send the address packet with fixed address and the A2 connection and the first 2 bits of the loc address*/
				TWI_SendSlaveAdressWithWrite(Local_u8AddressPacket);

				/*Send a data packet with the least 8 bits of the location address*/
				TWI_MasterWriteDataByte((uint8) Copy_u16LocAddress);

				/*Sending repeated start to change write request to read request*/
				TWI_SendRepeatedStart();

				/*Sending SLA again after the repeated start but with read request*/
				TWI_SendSlaveAdressWithRead(Local_u8AddressPacket);

				/*Reading from the data byte from the memory*/
				TWI_MasterReadDataByte(Copy_pu8DataByte);

				/*Sending stop condition*/
				TWI_SendStopCondition();
			}

			else
			{
				Local_u8ErroState = NOK;
			}

	}

	else
	{
		Local_u8ErroState = NULL_PTR_ERR;
	}


	return Local_u8ErroState;
}

