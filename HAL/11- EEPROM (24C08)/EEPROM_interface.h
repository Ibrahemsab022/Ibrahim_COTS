#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


uint8 EEPROM_u8WriteDataByte(uint16 Copy_u16LocAddress, uint8 Copy_u8DataByte);

uint8 EEPROM_u8ReadDataByte(uint16 Copy_u16LocAddress, uint8* Copy_pu8DataByte);





#endif
