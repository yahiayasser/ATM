/*
 * Scheduler_CFG.c
 *
 *  Created on: 16 Apr 2020
 *      Author: Yahia
 */


#include "ATM.h"

volatile TCB TCB_Container[NUmberOfTasks] =
{
		{
				SWC1_SystemTicks,
				SWC1_PeriodInTicks,
				SWC1_Period,
				Ready,
				SWC1_ReleaseTimeInTicks
		}
		,
		{
				SWC2_Application,
				SWC2_PeriodInTicks,
				SWC2_Period,
				Ready,
				SWC2_ReleaseTimeInTicks
		}
		,
		{
				SWC3_Keypad,
				SWC3_PeriodInTicks,
				SWC3_Period,
				Ready,
				SWC3_ReleaseTimeInTicks
		}
		,
		{
				SWC4_LCD,
				SWC4_PeriodInTicks,
				SWC4_Period,
				Ready,
				SWC4_ReleaseTimeInTicks
		}
		,
		{
				SWC5_Restart,
				SWC5_PeriodInTicks,
				SWC5_Period,
				Ready,
				SWC5_ReleaseTimeInTicks
		}
		,
		{
				SWC6_LED,
				SWC6_PeriodInTicks,
				SWC6_Period,
				Ready,
				SWC6_ReleaseTimeInTicks
		}
		,
		{
				SWC7_CashGate,
				SWC7_PeriodInTicks,
				SWC7_Period,
				Ready,
				SWC7_ReleaseTimeInTicks
		}
};
