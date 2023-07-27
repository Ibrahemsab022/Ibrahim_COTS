#ifndef KERNEL_INTERFACE_H_
#define KERNEL_INTERFACE_H_



void RTOS_voidStart(void);


uint8 RTOS_u8CreateTask(uint8 Copy_u8Priority, uint16 Copy_u16Perodicity, void(*Copy_pvTaskFunction)(void));

void RTOS_voidSuspendTask(uint8 Copy_u8Priority);

void RTOS_voidResumeTask(uint8 Copy_u8Priority);





#endif	
