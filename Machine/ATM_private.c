/*
 * ATM_private.c
 *
 *  Created on: 13 Apr 2020
 *      Author: Yahia
 */

#include "ATM.h"
#include "ATM_private.h"

CLIENT_PROFILE CurrentClient;
extern boolean LCD_ModificationFlag;
extern boolean ChangePasswordFlag;
extern ATM_State CurrentState;
extern uint8 KeypadChar;
extern ATM_Error ERROR;
extern uint8 SWC3_SystemTick;
extern uint16 SWC2_SystemTick;
extern uint8 User_ID;
extern uint8 PasswordCounter;
extern sint8 Password[PassSize];
extern uint8 PasswordWrongCounter;
extern uint8 CashCounter;
extern sint8 Cash[CashSize];
extern uint8 LCD_PrintCharFlag;
extern uint8 LCD_Char;
extern sint8 ConfirmedPassword[PassSize];
extern uint8 ID_Counter;
extern uint8 GateState;


void ATM_Init(void){
	ATM_MC_Init();
	ATM_HW_Init();
}

void LCD_WelcomeInATM(void)
{
	LCD_SendString("Welcome in ATM");
	LCD_SetCursor(1, 0);
	LCD_SendString("1 Access account");
	LCD_SetCursor(2, 0);
	LCD_SendString("2 Create account");
}

void LCD_EnterID(void)
{
	LCD_SendString("Enter your ID");
	LCD_SetCursor(3, 0);
	LCD_SendString("          Exit -");
	LCD_SetCursor(1, 0);
}

void LCD_EnterPassword(void)
{
	LCD_SendString("Please enter 4");
	LCD_SetCursor(1, 0);
	LCD_SendString("digit password");
	LCD_SetCursor(3, 0);
	LCD_SendString("          Exit -");
	LCD_SetCursor(2, 0);
}

void LCD_ConfirmPassword(void)
{
	LCD_SendString("Please rewrite");
	LCD_SetCursor(1, 0);
	LCD_SendString("password");
	LCD_SetCursor(3, 0);
	LCD_SendString("          Exit -");
	LCD_SetCursor(2, 0);
}

void LCD_NewAccount(void)
{
	LCD_SendString("Welcome In ATM");
	LCD_SetCursor(1, 0);
	LCD_SendString("Your ID: ");
	LCD_SendString(CurrentClient.ID);
}

void LCD_Account(void)
{
	LCD_SendString("1 Cash withdraw");
	LCD_SetCursor(1, 0);
	LCD_SendString("2 Other Services");
	LCD_SetCursor(3, 0);
	LCD_SendString("          Exit 3");
}

void LCD_CashWithdraw(void)
{
	LCD_SendString("1 100      200 2");
	LCD_SetCursor(1, 0);
	LCD_SendString("3 500     1000 4");
	LCD_SetCursor(2, 0);
	LCD_SendString("5 2000    5000 6");
	LCD_SetCursor(3, 0);
	LCD_SendString("          Exit -");
}

void LCD_CashWithdraw_Service(void)
{
	LCD_SendString("Enter amount of");
	LCD_SetCursor(1, 0);
	LCD_SendString("cash and press C");
	LCD_SetCursor(3, 0);
	LCD_SendString("Max amount ");
	LCD_SendString(MaxAmountOfCash_String);
	LCD_SetCursor(2, 0);
}

void LCD_OtherServices(void)
{
	LCD_SendString("1 Cash withdraw");
	LCD_SetCursor(1, 0);
	LCD_SendString("2 Cash deposit");
	LCD_SetCursor(2, 0);
	LCD_SendString("3 Cash inquiry");
	LCD_SetCursor(3, 0);
	LCD_SendString("4 Change password");
}

void LCD_CreditDeposit_Service(void)
{
	LCD_SendString("Enter amount of");
	LCD_SetCursor(1, 0);
	LCD_SendString("cash and press C");
	LCD_SetCursor(3, 0);
	LCD_SendString("Max amount ");
	LCD_SendString(MaxAmountOfCash_String);
	LCD_SetCursor(2, 0);
}

void LCD_CashWithdraw_Response(void)
{
	LCD_SendString("You have now:");
	LCD_SetCursor(1, 0);
	LCD_SendString(CurrentClient.Cash);
	LCD_SetCursor(2, 0);
	LCD_SendString("Please wait for");
	LCD_SetCursor(3, 0);
	LCD_SendString("the money");
}

void LCD_CreditInquiry_Response(void)
{
	LCD_SendString("You have now:");
	LCD_SetCursor(1, 0);
	LCD_SendString(CurrentClient.Cash);
}

void LCD_CreditDeposit_Response(void)
{
	LCD_SendString("Your transaction");
	LCD_SetCursor(1, 0);
	LCD_SendString("is completed");
	LCD_SetCursor(2, 0);
	LCD_SendString("You have now:");
	LCD_SetCursor(3, 0);
	LCD_SendString(CurrentClient.Cash);
}

void LCD_ChangePassword_Response(void)
{
	LCD_SendString("Your Password is");
	LCD_SetCursor(1, 0);
	LCD_SendString("successfully");
	LCD_SetCursor(2, 0);
	LCD_SendString("Changed");
}

void LCD_Error(void)
{
	switch(ERROR)
	{
	case ThreeWrongPassword:
		LCD_SendString("3 times wrong");
		LCD_SetCursor(1, 0);
		LCD_SendString("password");
		LCD_SetCursor(2, 0);
		LCD_SendString("The system halts");
		LCD_SetCursor(3, 0);
		LCD_SendString("for 30 seconds");
		break;
	case SignInWrongPassword:
		LCD_SendString(" Wrong Password");
		break;
	case MaxAmountPerTransaction:
		LCD_SendString("The amount of");
		LCD_SetCursor(1, 0);
		LCD_SendString("cash you entered");
		LCD_SetCursor(2, 0);
		LCD_SendString("exceeds the ");
		LCD_SetCursor(3, 0);
		LCD_SendString("maximum limit");
		break;
	case WrongID:
		LCD_SendString("The ID is not");
		LCD_SetCursor(1, 0);
		LCD_SendString("valid");
		break;
	case Timeout:
		LCD_SendString("Timeout error:");
		LCD_SetCursor(1, 0);
		LCD_SendString("ATM is not");
		LCD_SetCursor(2, 0);
		LCD_SendString("receiving from");
		LCD_SetCursor(3, 0);
		LCD_SendString("you");
		break;
	case Mismatch:
		LCD_SendString("The passwords");
		LCD_SetCursor(1, 0);
		LCD_SendString("you entered are");
		LCD_SetCursor(2, 0);
		LCD_SendString("not identical");
		break;
	case UnsuccessfulTransaction:
		LCD_SendString("Unsuccessful");
		LCD_SetCursor(1, 0);
		LCD_SendString("Transaction,");
		LCD_SetCursor(2, 0);
		LCD_SendString("please try again");
		break;
	case NoCash:
		LCD_SendString("The amount of");
		LCD_SetCursor(1, 0);
		LCD_SendString("cash you entered");
		LCD_SetCursor(2, 0);
		LCD_SendString("is not available");
		break;
	default:
		//error message
		break;
	}
}


void APP_WelcomeInATM(void)
{
	if(KeypadChar == '1')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		HandleState(EnterID, NoError);
	}
	else if(KeypadChar == '2')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		HandleState(SignUpEnterPassword, NoError);
	}else{}
}

void APP_EnterID(void)
{
	if(KeypadChar >= '0' && KeypadChar <= '9')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		if(User_ID == NULL_ID)
		{
			LCD_PrintCharFlag = TRUE;
			LCD_Char = KeypadChar;
			User_ID = KeypadChar - '0';
		}
		else if(User_ID <= 9)
		{
			LCD_PrintCharFlag = TRUE;
			LCD_Char = KeypadChar;
			User_ID = (User_ID * 10) + (KeypadChar - '0');
		}else{}
	}
	else if(KeypadChar == 'C')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		if((User_ID >= 0 && User_ID <= 99))
		{
			if(GetClient(&CurrentClient, User_ID) != E_OK)
			{
				User_ID = NULL_ID;
				SWC2_SystemTick = StandardDelay;
				HandleState(Error, WrongID);
				// counter
			}
			else
			{
				User_ID = NULL_ID;
				HandleState(SignInEnterPassword, NoError);
			}
		}else{}
	}
	else if(KeypadChar == '-')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		HandleState(WelcomeInATM, NoError);
	}else{}
}

void APP_SignInEnterPassword(void)
{
	if(KeypadChar >= '0' && KeypadChar <= '9')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		Password[PasswordCounter] = KeypadChar;
		PasswordCounter++;
		LCD_Char = '*';
		LCD_PrintCharFlag = TRUE;
		if(PasswordCounter == PASSWORD_DigitNum)
		{
			PasswordCounter = 0;
			if(Strings_Is_Equal(Password, CurrentClient.Pass) == TRUE)
			{
				PasswordWrongCounter = 0;
				HandleState(Account, NoError);
			}
			else
			{
				PasswordWrongCounter++;
				if(PasswordWrongCounter == WrongPassword_Max)
				{
					SWC2_SystemTick = ExtendedDelay;
					PasswordWrongCounter = 0;
					HandleState(Error, ThreeWrongPassword);
				}
				else
				{
					SWC2_SystemTick = StandardDelay;
					HandleState(Error, SignInWrongPassword);
				}
			}
		}else{}
	}
	else if(KeypadChar == '-')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		HandleState(WelcomeInATM, NoError);
	}else{}
}

void APP_SignUpEnterPassword(void)
{
	if(KeypadChar >= '0' && KeypadChar <= '9')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		Password[PasswordCounter] = KeypadChar;
		PasswordCounter++;
		LCD_Char = '*';
		LCD_PrintCharFlag = TRUE;
		if(PasswordCounter == PASSWORD_DigitNum)
		{
			PasswordCounter = 0;
			HandleState(ConfirmPassword, NoError);
		}else{}
	}
	else if(KeypadChar == '-')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		HandleState(WelcomeInATM, NoError);
	}else{}
}

void APP_ConfirmPassword(void)
{
	if(KeypadChar >= '0' && KeypadChar <= '9')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		ConfirmedPassword[PasswordCounter] = KeypadChar;
		PasswordCounter++;
		LCD_Char = '*';
		LCD_PrintCharFlag = TRUE;
		if(PasswordCounter == PASSWORD_DigitNum)
		{
			PasswordCounter = 0;
			if(Strings_Is_Equal(Password, ConfirmedPassword) == TRUE)
			{
				if(ChangePasswordFlag == TRUE)
				{
					ChangePasswordFlag = FALSE;
					SWC2_SystemTick = StandardDelay;
					if(UpdateClient(&CurrentClient, UpdatePass, Password) != E_OK)
					{
						HandleState(Error, UnsuccessfulTransaction);
					}
					else
					{
						HandleState(ChangePassword_Response, NoError);
					}
				}
				else
				{
					ClientInit(Password);
					SWC2_SystemTick = StandardDelay;
					if(SendClient(&CurrentClient) != E_OK)
					{
						HandleState(Error, UnsuccessfulTransaction);
					}
					else
					{
						HandleState(NewAccount, NoError);
					}
				}
			}
			else
			{
				SWC2_SystemTick = StandardDelay;
				HandleState(Error, Mismatch);
			}
		}else{}
	}
	else if(KeypadChar == '-')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		HandleState(WelcomeInATM, NoError);
	}else{}
}

void APP_Account(void)
{
	if(KeypadChar == '1')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		HandleState(CashWithdraw, NoError);
	}
	else if(KeypadChar == '2')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		HandleState(OtherServices, NoError);
	}
	else if(KeypadChar == '3')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		HandleState(WelcomeInATM, NoError);
	}else{}
}

void APP_CashWithdraw(void)
{
	if(KeypadChar >= '0' && KeypadChar <= '6')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		switch(KeypadChar)
		{
		case '1':
			CashWithdrawHandle(100);
			break;
		case '2':
			CashWithdrawHandle(200);
			break;
		case '3':
			CashWithdrawHandle(500);
			break;
		case '4':
			CashWithdrawHandle(1000);
			break;
		case '5':
			CashWithdrawHandle(2000);
			break;
		case '6':
			CashWithdrawHandle(5000);
			break;
		default:
			break;
		}
	}
}

void APP_OtherServices(void)
{
	if(KeypadChar >= '0' && KeypadChar <= '4')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		switch(KeypadChar)
		{
		case '1':
			HandleState(CashWithdraw_Service, NoError);
			break;
		case '2':
			HandleState(CreditDeposit_Service, NoError);
			break;
		case '3':
			SWC2_SystemTick = StandardDelay;
			HandleState(CreditInquiry_Response, NoError);
			break;
		case '4':
			ChangePasswordFlag = TRUE;
			HandleState(SignUpEnterPassword, NoError);
			break;
		default:
			break;
		}
	}
}

void APP_CashWithdraw_Service(void)
{
	uint64 NewCash = 0;
	if(KeypadChar >= '0' && KeypadChar <= '9')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		Cash[CashCounter] = KeypadChar;
		CashCounter++;
		LCD_Char = KeypadChar;
		LCD_PrintCharFlag = TRUE;
		if(CashCounter == CASH_DigitNum)
		{
			Cash[CashCounter] = '\0';
			CashCounter = 0;
			if(StringToNumber(Cash) > MaxAmountOfCash)
			{
				SWC2_SystemTick = StandardDelay;
				HandleState(Error, MaxAmountPerTransaction);
			}
			else if(StringToNumber(CurrentClient.Cash) >= StringToNumber(Cash))
			{
				NewCash = StringToNumber(CurrentClient.Cash) - StringToNumber(Cash);
				NumberToString(NewCash, Cash);
				if(UpdateClient(&CurrentClient, UpdateCash, Cash) != E_OK)
				{
					SWC2_SystemTick = StandardDelay;
					HandleState(Error, UnsuccessfulTransaction);
				}
				else
				{
					SWC2_SystemTick = CashGateDelay;
					GateState = OPEN;
					HandleState(CashWithdraw_Response, NoError);
				}
			}
			else
			{
				SWC2_SystemTick = StandardDelay;
				HandleState(Error, NoCash);
			}
		}else{}
	}
	else if(KeypadChar == 'C')
	{
		if(CashCounter != 0)
		{
			Cash[CashCounter] = '\0';
			CashCounter = 0;
			if(StringToNumber(CurrentClient.Cash) >= StringToNumber(Cash))
			{
				NewCash = StringToNumber(CurrentClient.Cash) - StringToNumber(Cash);
				NumberToString(NewCash, Cash);
				if(UpdateClient(&CurrentClient, UpdateCash, Cash) != E_OK)
				{
					SWC2_SystemTick = StandardDelay;
					HandleState(Error, UnsuccessfulTransaction);
				}
				else
				{
					SWC2_SystemTick = CashGateDelay;
					GateState = OPEN;
					HandleState(CashWithdraw_Response, NoError);
				}
			}
			else
			{
				SWC2_SystemTick = StandardDelay;
				HandleState(Error, NoCash);
			}
		}else{}
	}else{}
}

void APP_CreditDeposit_Service(void)
{
	uint64 NewCash = 0;
	if(KeypadChar >= '0' && KeypadChar <= '9')
	{
		SWC3_SystemTick = KYEPAD_DelayTicks;
		Cash[CashCounter] = KeypadChar;
		CashCounter++;
		LCD_Char = KeypadChar;
		LCD_PrintCharFlag = TRUE;
		if(CashCounter == CASH_DigitNum)
		{
			Cash[CashCounter] = '\0';
			CashCounter = 0;
			if(StringToNumber(Cash) > MaxAmountOfCash)
			{
				SWC2_SystemTick = StandardDelay;
				HandleState(Error, MaxAmountPerTransaction);
			}
			else
			{
				NewCash = StringToNumber(CurrentClient.Cash) + StringToNumber(Cash);
				NumberToString(NewCash, Cash);
				if(UpdateClient(&CurrentClient, UpdateCash, Cash) != E_OK)
				{
					SWC2_SystemTick = StandardDelay;
					HandleState(Error, UnsuccessfulTransaction);
				}
				else
				{
					SWC2_SystemTick = StandardDelay;
					HandleState(CreditDeposit_Response, NoError);
				}
			}
		}else{}
	}
	else if(KeypadChar == 'C'){
		if(CashCounter != 0)
		{
			Cash[CashCounter] = '\0';
			CashCounter = 0;
			NewCash = StringToNumber(CurrentClient.Cash) + StringToNumber(Cash);
			NumberToString(NewCash, Cash);
			if(UpdateClient(&CurrentClient, UpdateCash, Cash) != E_OK)
			{
				SWC2_SystemTick = StandardDelay;
				HandleState(Error, UnsuccessfulTransaction);
			}
			else
			{
				SWC2_SystemTick = StandardDelay;
				HandleState(CreditDeposit_Response, NoError);
			}
		}else{}
	}else{}
}

Std_ReturnType Restart(void)
{
	Std_ReturnType ReturnValue = E_NOT_OK;
	SendCommand(ATM_TriggerTransmission);
	if(GetCommand() != Server_Ready)
	{
		SendCommand(ATM_TriggerTransmission);
		return ReturnValue;
	}
	SendCommand(ATM_Restart);
	if(GetCommand() != Server_Success)
	{
		SendCommand(ATM_TriggerTransmission);
		return ReturnValue;
	}
	SendCommand(ATM_EndTransmission);
	if(GetCommand() != Server_Success)
	{
		SendCommand(ATM_TriggerTransmission);
		return ReturnValue;
	}
	ReturnValue = E_OK;
	return ReturnValue;
}

void HandleState(ATM_State state, ATM_Error error)
{
	LCD_ModificationFlag = TRUE;
	CurrentState = state;
	ERROR = error;

}

static void CashWithdrawHandle(uint16 cash)
{
	uint64 NewCash = StringToNumber(CurrentClient.Cash);
	if(NewCash >= cash)
	{
		NewCash -= cash;
		NumberToString(NewCash, Cash);
		if(UpdateClient(&CurrentClient, UpdateCash, Cash) != E_OK)
		{
			SWC2_SystemTick = StandardDelay;
			HandleState(Error, UnsuccessfulTransaction);
		}
		else
		{
			SWC2_SystemTick = CashGateDelay;
			GateState = OPEN;
			HandleState(CashWithdraw_Response, NoError);
		}
	}
	else
	{
		SWC2_SystemTick = StandardDelay;
		HandleState(Error, NoCash);
	}
}

static uint64 StringToNumber(sint8* str)
{
	uint32 multiply, output = 0;
	uint8 length = string_length(str);
	for(uint8 count1 = 0; count1 < length; count1++)
	{
		if(str[count1] == '\0')
			break;

		multiply = str[count1] - '0';
		if(multiply != 0)
		{
			for(uint8 count2 = count1; count2 < (length - 1); count2++)
			{
				multiply *= 10;
			}
		}
		output += multiply;
	}
	return output;
}

static void NumberToString(uint64 num, sint8* str)
{
    uint8 count, rem, length = 0;
    uint32 value = num;

    while (value != 0)
    {
    	length++;
    	value /= 10;
    }
    for (count = 0; count < length; count++)
    {
        rem = num % 10;
        num = num / 10;
        str[length - (count + 1)] = rem + '0';
    }
    str[length] = '\0';
}

static Std_ReturnType UpdateClient(CLIENT_PROFILE* client, uint8 Item, sint8* NewVlue)
{
	Std_ReturnType ReturnValue = E_NOT_OK;
	uint8* PTR = (uint8*)client;
	if(Item == UpdateCash)
	{
		PTR = (uint8*)(client -> Cash);
		for(uint8 count = 0; count < CashSize; count++)
		{
			PTR[count] = NewVlue[count];
		}
	}
	else if(Item == UpdatePass)
	{
		PTR = (uint8*)(client -> Pass);
		for(uint8 count = 0; count < PassSize; count++)
		{
			PTR[count] = NewVlue[count];
		}
	}
	else
	{
		return ReturnValue;
	}
	PTR = (uint8*)client;
	SendCommand(ATM_TriggerTransmission);
	if(GetCommand() != Server_Ready)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	SendCommand(ATM_UpdateClient);
	if(GetCommand() != Server_Ready)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	for(uint8 count = 0; count < ClientSize; count++)
	{
		SendByte(PTR[count]);
	}
	SendCommand(ATM_FrameEnd);
	if(GetCommand() != Server_Success)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	SendCommand(ATM_EndTransmission);
	if(GetCommand() != Server_Success)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	ReturnValue = E_OK;
	return ReturnValue;
}

static Std_ReturnType GetClient(CLIENT_PROFILE* client, uint8 id)
{
	Std_ReturnType ReturnValue = E_NOT_OK;
	uint8* PTR = (uint8*)(client -> Cash);
	SendCommand(ATM_TriggerTransmission);
	if(GetCommand() != Server_Ready)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	SendCommand(ATM_GetClientCash);
	if(GetCommand() != Server_Ready)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	SendByte(id);
	if(GetCommand() != Server_Success)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	for(uint8 count = 0; count < CashSize; count++)
	{
		PTR[count] = GetByte();
	}
	if(GetCommand() != Server_FrameEnd)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	SendCommand(ATM_EndTransmission);
	if(GetCommand() != Server_Success)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	PTR = (uint8*)(client -> Pass);
	SendCommand(ATM_TriggerTransmission);
	if(GetCommand() != Server_Ready)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	SendCommand(ATM_GetClientPass);
	if(GetCommand() != Server_Ready)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	SendByte(id);
	if(GetCommand() != Server_Success)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	for(uint8 count = 0; count < PassSize; count++)
	{
		PTR[count] = GetByte();
	}
	if(GetCommand() != Server_FrameEnd)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	SendCommand(ATM_EndTransmission);
	if(GetCommand() != Server_Success)
	{
		return ReturnValue;
	}
	client -> ID[0] = (id/10) + '0';
	client -> ID[1] = (id%10) + '0';
	ReturnValue = E_OK;
	return ReturnValue;
}

static Std_ReturnType SendClient(CLIENT_PROFILE* client)
{
	Std_ReturnType ReturnValue = E_NOT_OK;
	uint8* PTR = (uint8*)client;
	SendCommand(ATM_TriggerTransmission);
	if(GetCommand() != Server_Ready)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	SendCommand(ATM_WriteClient);
	if(GetCommand() != Server_Ready)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	for(uint8 count = 0; count < ClientSize; count++)
	{
		SendByte(PTR[count]);
	}
	SendCommand(ATM_FrameEnd);
	if(GetCommand() != Server_Success)
	{
		SendCommand(ATM_EndTransmission);
		return ReturnValue;
	}
	SendCommand(ATM_EndTransmission);
	if(GetCommand() != Server_Success)
	{
		return ReturnValue;
	}
	ReturnValue = E_OK;
	return ReturnValue;
}

static uint8 string_length(sint8 str[])
{
	uint8 count;
	/* count the string start from element 0 until the element before the NULL terminator */
	for(count = 0; str[count] != '\0'; ++count);
	return count;
}

static uint8 Strings_Is_Equal(sint8 Str1[], sint8 Str2[]){
	uint8 count = 0;
	uint8 Str1_length = string_length(Str1);
	uint8 Str2_length = string_length(Str2);
	if(Str1_length == Str2_length){
		while(count < Str1_length){
			if(Str1[count] != Str2[count]){
				return FALSE;
			}
			count++;
		}
		return TRUE;
	}
	else{
		return FALSE;
	}
}

