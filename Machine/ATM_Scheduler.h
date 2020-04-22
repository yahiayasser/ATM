/*
 * ATM_Scheduler.h
 *
 *  Created on: 16 Apr 2020
 *      Author: Yahia
 */

#ifndef ATM_SCHEDULER_H_
#define ATM_SCHEDULER_H_

#define NUmberOfTasks	7

#define	TickInMs	Scheduler_Tick

#define SWC1_PeriodInMs	100
#define SWC2_PeriodInMs	100
#define SWC3_PeriodInMs	100
#define SWC4_PeriodInMs	100
#define SWC5_PeriodInMs	100
#define SWC6_PeriodInMs	200
#define SWC7_PeriodInMs	200

#define SWC1_ReleaseTimeInMs	0
#define SWC2_ReleaseTimeInMs	0
#define SWC3_ReleaseTimeInMs	0
#define SWC4_ReleaseTimeInMs	0
#define SWC5_ReleaseTimeInMs	0
#define SWC6_ReleaseTimeInMs	0
#define SWC7_ReleaseTimeInMs	0

#define SWC1_Period		0
#define SWC2_Period		1
#define SWC3_Period		2
#define SWC4_Period		3
#define SWC5_Period		4
#define SWC6_Period		5
#define SWC7_Period		6

#define SWC1_PeriodInTicks	(SWC1_PeriodInMs/TickInMs)
#define SWC2_PeriodInTicks	(SWC2_PeriodInMs/TickInMs)
#define SWC3_PeriodInTicks	(SWC3_PeriodInMs/TickInMs)
#define SWC4_PeriodInTicks	(SWC4_PeriodInMs/TickInMs)
#define SWC5_PeriodInTicks	(SWC5_PeriodInMs/TickInMs)
#define SWC6_PeriodInTicks	(SWC6_PeriodInMs/TickInMs)
#define SWC7_PeriodInTicks	(SWC7_PeriodInMs/TickInMs)

#define SWC1_ReleaseTimeInTicks	(SWC1_ReleaseTimeInMs/TickInMs)
#define SWC2_ReleaseTimeInTicks	(SWC2_ReleaseTimeInMs/TickInMs)
#define SWC3_ReleaseTimeInTicks	(SWC3_ReleaseTimeInMs/TickInMs)
#define SWC4_ReleaseTimeInTicks	(SWC4_ReleaseTimeInMs/TickInMs)
#define SWC5_ReleaseTimeInTicks	(SWC5_ReleaseTimeInMs/TickInMs)
#define SWC6_ReleaseTimeInTicks	(SWC6_ReleaseTimeInMs/TickInMs)
#define SWC7_ReleaseTimeInTicks	(SWC7_ReleaseTimeInMs/TickInMs)

#endif /* ATM_SCHEDULER_H_ */
