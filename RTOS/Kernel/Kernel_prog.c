#include "STD_TYPES.h"
#include "defines.h"

#include "TIMERS_interface.h"

#include "Kernel_cfg.h"
#include "Kernel_interface.h"
#include "Kernel_prv.h"


/*The index of the task in the array === the priority*/
static Task_t SystemTasks[TASK_NUM];




static void Scheduler(void)
{
	static uint16 Local_u16TickCounter = 0u;
	uint8 Local_u8TaskCounter;

	Local_u16TickCounter++;

	for (Local_u8TaskCounter = 0; Local_u8TaskCounter < TASK_NUM; Local_u8TaskCounter++)
	{
		/*check if the peridocity of the task is matching that of the counter*/
		if (((Local_u16TickCounter % (SystemTasks[Local_u8TaskCounter].Periodicity)) == 0) && (SystemTasks[Local_u8TaskCounter].StateOfTask == 1))
		{
			/*invoking that task(fucntion)*/
			SystemTasks[Local_u8TaskCounter].TaskFunction();
		}

		else
		{
			/*Do Nothing*/
		}
	}

}

void RTOS_voidStart(void)
{
	uint8 Local_u8TaskItterator;

	TIMER0_voidInit();

	TIMER0_voidSetCmpValue(250);

	TIMERS_u8SetCallBack(TIMER0_COMP, &Scheduler);

	/*Intializing the state of the tasks to be initally active*/
	for (Local_u8TaskItterator = 0; Local_u8TaskItterator < TASK_NUM; Local_u8TaskItterator++)
	{
		SystemTasks[Local_u8TaskItterator].StateOfTask = 1;
	}

}


uint8 RTOS_u8CreateTask(uint8 Copy_u8Priority, uint16 Copy_u16Perodicity, void(*Copy_pvTaskFunction)(void))
{
	uint8 Local_u8ErroState = OK;

	if (Copy_pvTaskFunction != NULL)
	{
		SystemTasks[Copy_u8Priority].Periodicity = Copy_u16Perodicity;
		SystemTasks[Copy_u8Priority].TaskFunction = Copy_pvTaskFunction;
	}

	else
	{
		Local_u8ErroState = NULL_PTR_ERR;
	}

	return Local_u8ErroState;

}


void RTOS_voidSuspendTask(uint8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].StateOfTask = 0;
}

void RTOS_voidResumeTask(uint8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].StateOfTask = 1;
}

