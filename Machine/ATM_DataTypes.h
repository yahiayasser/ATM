#ifndef __ATM_DATATYPES_H_
#define __ATM_DATATYPES_H_

#include "Platform_Types.h"


#define PassSize	5
#define CashSize	8
#define IDSize		3

typedef sint8 ClientID;

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

typedef enum{
	WelcomeInATM,
	EnterID,
	SignInEnterPassword,
	SignUpEnterPassword,
	ConfirmPassword,
	NewAccount,
	Account,
	CashWithdraw,
	OtherServices,
	CashWithdraw_Service,
	CreditDeposit_Service,
	ChangePassword_Response,
	CashWithdraw_Response,
	CreditInquiry_Response,
	CreditDeposit_Response,
	Error
}ATM_State;

typedef enum{
	NoError,
	SignInWrongPassword,
	ThreeWrongPassword,
	MaxAmountPerTransaction,
	WrongID,
	UnsuccessfulTransaction,
	NoCash,
	Mismatch,
	Timeout
}ATM_Error;

typedef struct{
	sint8       Cash[CashSize];
    sint8		Pass[PassSize];
    ClientID    ID[IDSize];
}CLIENT_PROFILE;

#endif
