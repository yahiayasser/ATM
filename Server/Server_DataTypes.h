
/*
 * ATM_Server.h
 *
 *  Created on: Apr 5, 2020
 *      Author: Yahia
 */

#ifndef SERVER_DATATYPES_H_
#define SERVER_DATATYPES_H_

#include "Platform_Types.h"

/* Module Version 1.0.0 */
#define SERVER_DATATYPES_SW_MAJOR_VERSION           (1U)
#define SERVER_DATATYPES_SW_MINOR_VERSION           (0U)
#define SERVER_DATATYPES_SW_PATCH_VERSION           (0U)


#define PassSize	5
#define CashSize	8
#define IDSize		3

typedef uint8 ClientID;

typedef uint8 Std_ReturnType;
#define E_OK 					(Std_ReturnType)0
#define E_NOT_OK 				(Std_ReturnType)1

typedef enum{
	ATM_TriggerTransmission = 'A',
	ATM_EndTransmission,
	ATM_WriteClient,
	ATM_UpdateClient,
	ATM_GetClientPass,
	ATM_GetClientCash,
	ATM_FrameEnd,
	ATM_Restart,
	Server_Success,
	Server_Ready,
	Server_FrameEnd,
	Server_Error
}ATM_Server_Commands;

typedef struct{
	uint8       Cash[CashSize];
    uint8		Pass[PassSize];
    ClientID    ID[IDSize];
}CLIENT_PROFILE;

#endif
