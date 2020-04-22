/*
 * MCAL.h
 *
 *  Created on: 9 Apr 2020
 *      Author: Yahia
 */

#ifndef MCAL_H_
#define MCAL_H_

#include "micro_config.h"
#include "DIO.h"
#include "UART.h"
#include "i2c.h"
#include "LCD.h"
#include "external_eeprom.h"

#define TreeCounterAdd	0x00
#define RootIndexAdd	0x01
#define TreeStartAddr	0x02

#define EEPROM_NUM		3
#define EEPROM_Size		2048
#define EEPROM_MaxElements	(EEPROM_Size/ClientSize)
#define EEPROM_StartAddress	0x00

#define	Demultiplexer_SelectFilter	0b11100000
#define Demultiplexer_PORT			DIO_PORTD

void Server_MC_Init(void);

#endif /* MCAL_H_ */
