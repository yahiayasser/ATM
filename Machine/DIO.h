/*
 * DIO.h
 *
 *  Created on: 12 Oct 2018
 *      Author: Yahia
 */

#ifndef DIO_H_
#define DIO_H_

#include "Platform_Types.h"
#include "common_macros.h"
#include "micro_config.h"

#define DIO_PORTA	0
#define DIO_PORTB	1
#define DIO_PORTC	2
#define DIO_PORTD	3

#define PIN_INPUT   0
#define PIN_OUTPUT  1

/************PIN Configuration************/
#define PA0_Direction PIN_OUTPUT
#define PA1_Direction PIN_OUTPUT
#define PA2_Direction PIN_OUTPUT
#define PA3_Direction PIN_OUTPUT
#define PA4_Direction PIN_OUTPUT
#define PA5_Direction PIN_OUTPUT
#define PA6_Direction PIN_OUTPUT
#define PA7_Direction PIN_OUTPUT

#define PB0_Direction PIN_INPUT
#define PB1_Direction PIN_INPUT
#define PB2_Direction PIN_INPUT
#define PB3_Direction PIN_INPUT
#define PB4_Direction PIN_INPUT
#define PB5_Direction PIN_INPUT
#define PB6_Direction PIN_INPUT
#define PB7_Direction PIN_INPUT

#define PC0_Direction PIN_OUTPUT
#define PC1_Direction PIN_OUTPUT
#define PC2_Direction PIN_OUTPUT
#define PC3_Direction PIN_OUTPUT
#define PC4_Direction PIN_OUTPUT
#define PC5_Direction PIN_OUTPUT
#define PC6_Direction PIN_OUTPUT
#define PC7_Direction PIN_OUTPUT

#define PD0_Direction PIN_OUTPUT
#define PD1_Direction PIN_OUTPUT
#define PD2_Direction PIN_OUTPUT
#define PD3_Direction PIN_OUTPUT
#define PD4_Direction PIN_OUTPUT
#define PD5_Direction PIN_OUTPUT
#define PD6_Direction PIN_OUTPUT
#define PD7_Direction PIN_OUTPUT


#define PORTA_direction DDRA
#define PORTB_direction DDRB
#define PORTC_direction DDRC
#define PORTD_direction DDRD

#define PORTA_input PINA
#define PORTB_input PINB
#define PORTC_input PINC
#define PORTD_input PIND

#define PORTA_output PORTA
#define PORTB_output PORTB
#define PORTC_output PORTC
#define PORTD_output PORTD

#define CONC(Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7)   CONC_HELP(Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7)
#define CONC_HELP(Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7)  (0b##Bit0##Bit1##Bit2##Bit3##Bit4##Bit5##Bit6##Bit7)

uint8 DIO_ReadChannel(volatile const uint8 a_PIN);
void DIO_WriteChannel(volatile const uint8 a_PIN);
void DIO_ToggleChannel(volatile const uint8 a_PIN);
void DIO_ClearChannel(volatile const uint8 a_PIN);
void DIO_MakeInput(volatile const uint8 a_PIN);
void DIO_MakeOutput(volatile const uint8 a_PIN);
void DIO_DefinePinsDirections(void);
void DIO_PortOutput(volatile const uint8 port);
void DIO_PortInput(volatile const uint8 port);
void DIO_WritePort(volatile const uint8 port, volatile const uint8 value);

#endif /* DIO_H_ */
