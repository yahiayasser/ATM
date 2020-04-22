#ifndef __ATM_DEPENDENCIES_H_
#define __ATM_DEPENDENCIES_H_

/* Module Version 1.0.0 */
#define ATM_DEPENDENCIES_SW_MAJOR_VERSION           (1U)
#define ATM_DEPENDENCIES_SW_MINOR_VERSION           (0U)
#define ATM_DEPENDENCIES_SW_PATCH_VERSION           (0U)


#include "micro_config.h"

#if(ATMEGA32 != ATM_TARGET)
#error "The SW version of ATM does not suppot this type of micro controller"
#endif

#include "DIO.h"
#include "TIMER.h"
#include "UART.h"
#include <avr/eeprom.h>
#include "LCD.h"
#include "KEYPAD.h"

void ATM_MC_Init(void);
void ATM_HW_Init(void);

#endif
