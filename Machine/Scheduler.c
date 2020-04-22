/*
 * Scheduler.c
 *
 *  Created on: 16 Apr 2020
 *      Author: Yahia
 */


#include "ATM.h"


extern volatile TCB	TCB_Container[NUmberOfTasks];
volatile boolean Scheduler_Flag;

void Scheduler_Init(void)
{
	InitiateSchedulerTimer(Scheduler_Tick);
	SetCallbackHandler(Scheduler_Trigger);
	Scheduler_Flag = FALSE;
	SortTCB(TCB_Container);
}

void Scheduler(void)
{
	uint8 Task_Counter;
	while(1)
	{
		while(Scheduler_Flag == FALSE);

		for(Task_Counter = 0; Task_Counter < NUmberOfTasks; Task_Counter++)
		{
			if(TCB_Container[Task_Counter].State == Ready && TCB_Container[Task_Counter].ReleaseTime <= 0)
			{
				TCB_Container[Task_Counter].State = Running;
				TCB_Container[Task_Counter].TaskPTR();
				TCB_Container[Task_Counter].State = Ready;
				TCB_Container[Task_Counter].ReleaseTime = TCB_Container[Task_Counter].TaskPeriod;
			}
		}

		for(Task_Counter = 0; Task_Counter < NUmberOfTasks; Task_Counter++)
		{
			if(TCB_Container[Task_Counter].State == Ready)
			{
				TCB_Container[Task_Counter].ReleaseTime -= 1;
			}
		}

		Scheduler_Flag = FALSE;
	}
}

void Scheduler_Trigger(void)
{
	Scheduler_Flag = TRUE;
}

static void SortTCB(TCB* TCB_Handle)
{
	TCB temp;
	for(uint8 count1 = 0; count1 < (NUmberOfTasks - 1); count1++)
	{
		for(uint8 count2 = count1+1; count2 < NUmberOfTasks; count2++)
		{
			if(TCB_Handle[count2].Priority < TCB_Handle[count1].Priority)
			{
				temp = TCB_Handle[count1];
				TCB_Handle[count1] = TCB_Handle[count2];
				TCB_Handle[count2] = temp;
			}
		}
	}
}
