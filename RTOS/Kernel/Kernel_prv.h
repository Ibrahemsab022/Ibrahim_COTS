#ifndef KERNEL_PRV_H_
#define KERNEL_PRV_H_


typedef struct
{
	uint16 Periodicity;
	void (*TaskFunction)(void);
	uint8 StateOfTask;

}Task_t;

static void Scheduler(void);




#endif
