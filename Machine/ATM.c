/*
 * ATM_private.c
 *
 *  Created on: 13 Apr 2020
 *      Author: Yahia
 */

#include "ATM.h"
#include "ATM_private.h"

boolean LCD_ModificationFlag;
boolean ChangePasswordFlag;
ATM_State CurrentState;
uint8 KeypadChar;
ATM_Error ERROR;
uint8 SWC3_SystemTick;
uint16 SWC2_SystemTick;
uint8 SWC7_SystemTick;
uint16 TimeOutTick;
uint8 User_ID;
uint8 PasswordCounter;
sint8 Password[PassSize];
uint8 PasswordWrongCounter;
uint8 CashCounter;
sint8 Cash[CashSize];
uint8 LCD_PrintCharFlag;
uint8 LCD_Char;
sint8 ConfirmedPassword[PassSize];
uint8 ID_Counter;
uint8 GateState;


void ATM_Start(void)
{
	ATM_Init();
	Scheduler_Init();
	SetVariables();
	Scheduler();
}

void SWC1_SystemTicks(void)
{
	SWC2_SystemTick ? SWC2_SystemTick-- : SWC2_SystemTick;
	SWC3_SystemTick ? SWC3_SystemTick-- : SWC3_SystemTick;
	SWC7_SystemTick ? SWC7_SystemTick-- : SWC7_SystemTick;
	if(CurrentState != WelcomeInATM && CurrentState != ChangePassword_Response &&\
			CurrentState != CashWithdraw_Response && CurrentState != CreditInquiry_Response &&\
			CurrentState != CreditDeposit_Response && CurrentState != Error)
	{
		TimeOutTick++;
		if(TimeOutTick == TimeOutDelay)
		{
			TimeOutTick = 0;
			SWC2_SystemTick = StandardDelay;
			HandleState(Error, Timeout);
		}
	}
}

void SWC2_Application(void)
{
	if(SWC2_SystemTick == 0)
	{
		switch(CurrentState)
		{
		case WelcomeInATM:
			APP_WelcomeInATM();
			break;
		case EnterID:
			APP_EnterID();
			break;
		case SignInEnterPassword:
			APP_SignInEnterPassword();
			break;
		case SignUpEnterPassword:
			APP_SignUpEnterPassword();
			break;
		case ConfirmPassword:
			APP_ConfirmPassword();
			break;
		case NewAccount:
			HandleState(WelcomeInATM, NoError);
			break;
		case Account:
			APP_Account();
			break;
		case CashWithdraw:
			APP_CashWithdraw();
			break;
		case OtherServices:
			APP_OtherServices();
			break;
		case CashWithdraw_Service:
			APP_CashWithdraw_Service();
			break;
		case CreditDeposit_Service:
			APP_CreditDeposit_Service();
			break;
		case Error:
			switch(ERROR)
			{
			case SignInWrongPassword:
				HandleState(SignInEnterPassword, NoError);
				break;
			case Mismatch:
				HandleState(SignUpEnterPassword, NoError);
				break;
			case MaxAmountPerTransaction:
				HandleState(Account, NoError);
				break;
			case NoCash:
				HandleState(Account, NoError);
				break;
			default:
				HandleState(WelcomeInATM, NoError);
				break;
			}
			break;
		default:
			HandleState(Account, NoError);
			break;
		}
	}
	KeypadChar = NULL_CHAR;
}

void SWC3_Keypad(void)
{
	if(SWC3_SystemTick == 0)
	{
		KeypadChar = KEYPAD_GetStatus();
		if((KeypadChar >= '0' && KeypadChar <= '9') || (KeypadChar == '%') || \
				(KeypadChar == '*') || (KeypadChar == '-') || \
				(KeypadChar == '+') || (KeypadChar == '=') || \
				(KeypadChar == 'C'))
		{
			TimeOutTick = 0;
		}
		else
		{
			KeypadChar = NULL_CHAR;
		}
	}
}

void SWC4_LCD(void)
{
	if(LCD_PrintCharFlag == TRUE)
	{
		LCD_SendCharacter(LCD_Char);
		LCD_PrintCharFlag = FALSE;
	}

	if(LCD_ModificationFlag == TRUE)
	{
		LCD_ClearScreen();
		switch(CurrentState)
		{
		case WelcomeInATM:
			LCD_WelcomeInATM();
			break;
		case EnterID:
			LCD_EnterID();
			break;
		case SignInEnterPassword:
			LCD_EnterPassword();
			break;
		case SignUpEnterPassword:
			LCD_EnterPassword();
			break;
		case ConfirmPassword:
			LCD_ConfirmPassword();
			break;
		case NewAccount:
			LCD_NewAccount();
			break;
		case Account:
			LCD_Account();
			break;
		case CashWithdraw_Service:
			LCD_CashWithdraw_Service();
			break;
		case CashWithdraw:
			LCD_CashWithdraw();
			break;
		case OtherServices:
			LCD_OtherServices();
			break;
		case CreditDeposit_Service:
			LCD_CreditDeposit_Service();
			break;
		case CashWithdraw_Response:
			LCD_CashWithdraw_Response();
			break;
		case CreditInquiry_Response:
			LCD_CreditInquiry_Response();
			break;
		case CreditDeposit_Response:
			LCD_CreditDeposit_Response();
			break;
		case ChangePassword_Response:
			LCD_ChangePassword_Response();
			break;
		case Error:
			LCD_Error();
			break;
		default:
			//error message
			break;
		}
		LCD_ModificationFlag = FALSE;
	}
}

void SWC5_Restart(void)
{
	if(RestartButton() == TRUE)
	{
		if(Restart() != E_OK)
		{
			SWC2_SystemTick = StandardDelay;
			LCD_ModificationFlag = TRUE;
			CurrentState = Error;
			ERROR = UnsuccessfulTransaction;
		}
		else
		{
			ID_Counter = 0;
			eeprom_update_byte(ID_Counter_Address, ID_Counter);
			LCD_ModificationFlag = TRUE;
			CurrentState = WelcomeInATM;
		}
	}
}

void SWC6_LED(void)
{
	if(SWC2_SystemTick == 0)
	{
		TurnOnLED(GreenLed);
		TurnOffLED(RedLed);
	}
	else
	{
		TurnOnLED(RedLed);
		TurnOffLED(GreenLed);
	}
}

void SWC7_CashGate(void)
{
	if(SWC7_SystemTick == 0 && GateState == OPEN)
	{
		MotorClockWise();
		SWC7_SystemTick = CashGateDelay;
	}
	else if(SWC7_SystemTick == (CashGateDelay - 10) && GateState == OPEN)
	{
		MotorStop();
		GateState = CLOSE;
	}
	else if(SWC7_SystemTick == 10 && GateState == CLOSE)
	{
		MotorAntiClockWise();
	}
	else if(SWC7_SystemTick == 0 && GateState == CLOSE)
	{
		MotorStop();
		GateState = GATE_NULL;
	}
	else
	{

	}
}




