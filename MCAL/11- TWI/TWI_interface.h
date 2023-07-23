#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum
{
	NoError,
	NullPtrErr,
	StartConditionError,
	RepeatedStartError,
	SlaveAdressWithWriteError,
	SlaveAdressWithReadError,
	MasterWriteByteWithAckError,
	MasterReadBytedWithAckError,

}TWI_ErrorStatus_t;


void TWI_voidMasterInit(uint8 Copy_u8Adress);

void TWI_voidSalveInit(uint8 Copy_u8Adress);

TWI_ErrorStatus_t TWI_SendStartCondition(void);

TWI_ErrorStatus_t TWI_SendRepeatedStart(void);

TWI_ErrorStatus_t TWI_SendSlaveAdressWithWrite(uint8 Copy_u8SlaveAdress);

TWI_ErrorStatus_t TWI_SendSlaveAdressWithRead(uint8 Copy_u8SlaveAdress);

TWI_ErrorStatus_t TWI_MasterWriteDataByte(uint8 Copy_u8DataByte);

TWI_ErrorStatus_t TWI_MasterReadDataByte(uint8* Copy_pu8DataByte);

TWI_ErrorStatus_t TWI_SendStopCondition(void);


#endif
