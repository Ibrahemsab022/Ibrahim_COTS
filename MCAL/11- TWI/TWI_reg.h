#ifndef TWI_REG_H_
#define TWI_REG_H_


#define TWBR			*((volatile uint8 *) 0x20)			/*Bit Rate Rigester*/
#define TWBR_TWBR7		7u									/*bit7-0, selects the divison factor for bit rate generator*/
#define TWBR_TWBR6		6u
#define TWBR_TWBR5		5u
#define TWBR_TWBR4		4u
#define TWBR_TWBR3      3u
#define TWBR_TWBR2      2u
#define TWBR_TWBR1      1u
#define TWBR_TWBR0      0u

#define TWCR			*((volatile uint8 *) 0x56)			/*Control Register*/
#define TWCR_TWINT		7u									/*TWI interrupt flag bit*/
#define TWCR_TWEA	    6u                                  /*Enable Acknowlege bit*/
#define TWCR_TWSTA      5u                                  /*Start Condition bit*/
#define TWCR_TWSTO      4u                                  /*Stop Condition bit*/
#define TWCR_TWWC       3u                                  /*Write Colision Flag bit*/
#define TWCR_TWEN       2u                                  /*TWI Perphiral enable bit*/
#define TWCR_TWIE       0u                                  /*TWI Interrupt Enable*/


#define TWSR			*((volatile uint8 *) 0x21)			  /*TWI Status Register*/
#define TWSR_TWS7         7u                                  /*bit7-3, TWI Status bits*/
#define TWSR_TWS6         6u
#define TWSR_TWS5         5u
#define TWSR_TWS4         4u
#define TWSR_TWS3         3u
#define TWSR_TWPS1        1u                                  /*TWPS1-0: TWI Prescaler bits*/
#define TWSR_TWPS0        0u


#define TWDR			*((volatile uint8 *) 0x23)					  /*TWI DATA register*/


#define TWAR			*((volatile uint8 *) 0x22)			/*TWI Adress Register*/
#define TWAR_TWGCE		0u									/*General Call Recoginition Enable Bit (Broadcasting)*/





#endif
