/*
 * Scheduler.h
 *
 *  Created on: 16 Apr 2020
 *      Author: Yahia
 */


/* Module Version 1.0.0 */
#define SCHEDULER_SW_MAJOR_VERSION           (1U)
#define SCHEDULER_SW_MINOR_VERSION           (0U)
#define SCHEDULER_SW_PATCH_VERSION           (0U)

#define Scheduler_Tick	100

typedef enum
{
	Blocked,
	Ready,
	Running
}TaskState;

typedef struct
{
	void(*TaskPTR)(void);
	sint8 TaskPeriod;
	uint8 Priority;
	TaskState State;
	sint8 ReleaseTime;
}TCB;

void Scheduler(void);
void Scheduler_Init(void);
void CreateCriticalSection(void);
void ExitCriticalSection(void);
void Scheduler_Trigger(void);
static void SortTCB(TCB* TCB_Handle);
