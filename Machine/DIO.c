/*
 * DIO.c
 *
 *  Created on: 12 Oct 2018
 *      Author: Yahia
 */


#include"DIO.h"


void DIO_DefinePinsDirections(void)
{
	PORTA_direction = CONC(PA0_Direction, PA1_Direction, PA2_Direction, PA3_Direction, PA4_Direction, PA5_Direction, PA6_Direction, PA7_Direction);
	PORTB_direction = CONC(PB0_Direction, PB1_Direction, PB2_Direction, PB3_Direction, PB4_Direction, PB5_Direction, PB6_Direction, PB7_Direction);
	PORTC_direction = CONC(PC0_Direction, PC1_Direction, PC2_Direction, PC3_Direction, PC4_Direction, PC5_Direction, PC6_Direction, PC7_Direction);
	PORTD_direction = CONC(PD0_Direction, PD1_Direction, PD2_Direction, PD3_Direction, PD4_Direction, PD5_Direction, PD6_Direction, PD7_Direction);
}

uint8 DIO_ReadChannel(volatile const uint8 a_PIN){
	uint8 a_Data = 0;
	if(a_PIN/8 == 0){
		a_Data = (PORTA_input & (1 << a_PIN));
		a_Data = a_Data >> a_PIN;
	}
	else if(a_PIN/8 == 1)
		a_Data = ((PORTB_input&(1 << (a_PIN-8))) >> (a_PIN-8));
	else if(a_PIN/8 == 2)
		a_Data = ((PORTC_input&(1 << (a_PIN-16))) >> (a_PIN-16));
	else
		a_Data = ((PORTD_input&(1 << (a_PIN-24))) >> (a_PIN-24));

	return a_Data;
}

void DIO_WriteChannel(volatile const uint8 a_PIN){
	if(a_PIN/8 == 0){
		PORTA_output |= (1<<a_PIN);
	}
	else if(a_PIN/8 == 1){
		PORTB_output |= (1<<(a_PIN-8));
	}
	else if(a_PIN/8 == 2){
		PORTC_output |= (1<<(a_PIN-16));
	}
	else{
		PORTD_output |= (1<<(a_PIN-24));
	}
}

void DIO_ClearChannel(volatile const uint8 a_PIN){
	if(a_PIN/8 == 0)
		PORTA_output &= ~(1 << a_PIN);
	else if(a_PIN/8 == 1)
		PORTB_output &= ~(1 << (a_PIN - 8));
	else if(a_PIN/8 == 2)
		PORTC_output &= ~(1 << (a_PIN - 16));
	else
		PORTD_output &= ~(1 << (a_PIN - 24));
}

void DIO_MakeInput(volatile const uint8 a_PIN){
	if(a_PIN/8 == 0)
		PORTA_direction &= ~(1 << a_PIN);
	else if(a_PIN/8 == 1)
		PORTB_direction &= ~(1 << (a_PIN - 8));
	else if(a_PIN/8 == 2)
		PORTC_direction &= ~(1 << (a_PIN - 16));
	else
		PORTD_direction &= ~(1 << (a_PIN - 24));
}

void DIO_MakeOutput(volatile const uint8 a_PIN){
	if(a_PIN/8 == 0)
		PORTA_direction |= (1 << a_PIN);
	else if(a_PIN/8 == 1)
		PORTB_direction |= (1 << (a_PIN - 8));
	else if(a_PIN/8 == 2)
		PORTC_direction |= (1 << (a_PIN - 16));
	else
		PORTD_direction |= (1 << (a_PIN - 24));
}

void DIO_ToggleChannel(volatile const uint8 a_PIN){
	if(a_PIN/8 == 0)
		PORTA_output ^= (1 << a_PIN);
	else if(a_PIN/8 == 1)
		PORTB_output ^= (1 << (a_PIN - 8));
	else if(a_PIN/8 == 2)
		PORTC_output ^= (1 << (a_PIN - 16));
	else
		PORTD_output ^= (1 << (a_PIN - 24));
}

void DIO_PortOutput(volatile const uint8 port)
{
	switch(port)
	{
	case DIO_PORTA:
		PORTA_direction = 0xFF;
		break;
	case DIO_PORTB:
		PORTB_direction = 0xFF;
		break;
	case DIO_PORTC:
		PORTC_direction = 0xFF;
		break;
	case DIO_PORTD:
		PORTD_direction = 0xFF;
		break;
	default:
		//error
		break;
	}
}

void DIO_PortInput(volatile const uint8 port)
{
	switch(port)
	{
	case DIO_PORTA:
		PORTA_direction = 0;
		break;
	case DIO_PORTB:
		PORTB_direction = 0;
		break;
	case DIO_PORTC:
		PORTC_direction = 0;
		break;
	case DIO_PORTD:
		PORTD_direction = 0;
		break;
	default:
		//error
		break;
	}
}

void DIO_WritePort(volatile const uint8 port, volatile const uint8 value)
{
	switch(port)
	{
	case DIO_PORTA:
		PORTA_output = value;
		break;
	case DIO_PORTB:
		PORTB_output = value;
		break;
	case DIO_PORTC:
		PORTC_output = value;
		break;
	case DIO_PORTD:
		PORTD_output = value;
		break;
	default:
		//error
		break;
	}
}
