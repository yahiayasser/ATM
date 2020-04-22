#ifndef __ATM_INTERFACE_H_
#define __ATM_INTERFACE_H_

#include "ATM_DataTypes.h"

/* Module Version 1.0.0 */
#define ATM_INTERFACE_SW_MAJOR_VERSION           (1U)
#define ATM_INTERFACE_SW_MINOR_VERSION           (0U)
#define ATM_INTERFACE_SW_PATCH_VERSION           (0U)

#define ClientSize	16

#define GATE_NULL	0
#define OPEN		1
#define CLOSE		2

#define UpdateCash	0
#define UpdatePass	1

void ATM_Start(void);

void SWC1_SystemTicks(void);
void SWC2_Application(void);
void SWC3_Keypad(void);
void SWC4_LCD(void);
void SWC5_Restart(void);
void SWC6_LED(void);
void SWC7_CashGate(void);

Std_ReturnType Restart(void);

#endif
