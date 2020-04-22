/*
 * TIMER.c
 *
 *  Created on: 13 Oct 2018
 *      Author: Yahia
 */


#include "TIMER.h"
#include "DIO.h"

void(*PTR_TIM1_Handler)(void) = STUB;

void TIMER1_InitCM_ChannelA(uint8 a_Prescaler, uint16 a_TIMER1_Bottom, uint16 a_TIMER1_Top){
	/*  This function is set to initialize Timer1 for the compare mode,
	 	for channel A.
	    a_Prescaler is the frequency prescaler.
	    a_TIMER1_Bottom the value that the timer will start count from,
	    it varies from 0 to 65535.
	    a_TIMER1_Top the value that the timer will count to,
	    it varies from 0 to 65535.
	    clock period = 1 / (operating frequency*Prescaler).
	    Tick equation = clock period * ((a_TIMER1_Top - a_TIMER1_Bottom) + 1).
	    You can also use T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64,
	    T1_F_CPU_256, T1_F_CPU_1024 for a_Prescaler.
	     */
	SREG  |= (1<<7);// global interrupt bit.
	TCCR1A = (1 << FOC1A);// Enable output compare mode for channel A.
	TIMSK |= (1 << OCIE1A);// interrupt enable bit for Timer1 in compare mode for channel A.
	OCR1A = a_TIMER1_Top;// the value that the timer will count to.
	TCNT1 = a_TIMER1_Bottom;// the value that the timer will start count from.
	TCCR1B = (1 << WGM12);// Enable Compare mode.
	TCCR1B = (TCCR1B & 0xF8) | (a_Prescaler & 0x07);// Prescaler.
}

void TIMER1_InitCM_ChannelB(uint8 a_Prescaler, uint16 a_TIMER1_Bottom, uint16 a_TIMER1_Top){
	/*  This function is set to initialize Timer1 for the compare mode,
	 	for channel B.
	    a_Prescaler is the frequency prescaler.
	    a_TIMER1_Bottom the value that the timer will start count from,
	    it varies from 0 to 65535.
	    a_TIMER1_Top the value that the timer will count to,
	    it varies from 0 to 65535.
	    clock period = 1 / (operating frequency*Prescaler).
	    Tick equation = clock period * ((a_TIMER1_Top - a_TIMER1_Bottom) + 1).
	    You can also use T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64,
	    T1_F_CPU_256, T1_F_CPU_1024 for a_Prescaler.
	     */
	SREG  |= (1<<7);// global interrupt bit.
	TCCR1A = (1 << FOC1B);// Enable output compare mode for channel B.
	TIMSK |= (1 << OCIE1B);// interrupt enable bit for Timer1 in compare mode for channel B.
	OCR1A = a_TIMER1_Top;// the value that the timer will count to.
	TCNT1 = a_TIMER1_Bottom;// the value that the timer will start count from.
	TCCR1B = (1 << WGM12);// Enable Compare mode.
	TCCR1B = (TCCR1B & 0xF8) | (a_Prescaler & 0x07);// Prescaler.
}

void TIMER1_Init_MSeconds(uint8 a_Prescaler, uint16 MS, uint8 Channel){
	/*
	 * This function is set to start the timer in compare mode to count some seconds,
	   based on values that user will enter.
	 * This function uses Timer1.
	 * Channel for channelA or channelB, 0 for A and 1 for B.
	 * a_Prescaler is the frequency prescaler.
	 * MS the time chosen to count.
	 * You can also use T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64,
	   T1_F_CPU_256, T1_F_CPU_1024 for a_Prescaler.
	 */
	uint16 a_TIMER_Top;// the value that the timer will count to.
	uint32 Frequency;// Operating Frequency after prescaler.
	switch(a_Prescaler){
	case T1_F_CPU_:
		Frequency = (F_CPU);
		break;

	case T1_F_CPU_8:
		Frequency = (F_CPU)/8;
		break;

	case T1_F_CPU_64:
		Frequency = (F_CPU)/64;
		break;

	case T1_F_CPU_256:
		Frequency = (F_CPU)/256;
		break;

	case T1_F_CPU_1024:
		Frequency = (F_CPU)/1024;
		break;

	default:
		return;
		break;
	}

	a_TIMER_Top = (float32)(((float32)MS/1000)) * Frequency;

	if(Channel){
		TIMER1_InitCM_ChannelB(a_Prescaler, 0, a_TIMER_Top);
	}
	else{
		TIMER1_InitCM_ChannelA(a_Prescaler, 0, a_TIMER_Top);
	}
}

void PTR_TIM1_Handler_Setter(void(*ptr)(void))
{
	PTR_TIM1_Handler = ptr;
}

ISR(TIMER1_COMPA_vect)
{
	PTR_TIM1_Handler();
}

void STUB(void)
{

}
