/*****************************************************************/
/*****************************************************************/
/****************	Authour: Ibrahim Saber	**********************/
/****************	File: STEPPER_interface.h	 *****************/
/****************	Version: 1.00	        **********************/
/*****************************************************************/
/*****************************************************************/


#ifndef STEPPER_INTERFACE_H_
#define STEPPER_INTERFACE_H_


typedef struct
{
	uint8 PORT;
	uint8 BluePin;
	uint8 PinkPin;
	uint8 YellowPin;
	uint8 OrangePin;

}STEPPER_T;



uint8 STEPPER_u8Rotate(const STEPPER_T* Copy_pStepper, uint16 Copy_u16Angle, uint8 Copy_u8Direction);


#define CW	0u
#define CCW	1u



#endif
