#ifndef __ATM_PRIVATE_H_
#define __ATM_PRIVATE_H_

/* Module Version 1.0.0 */
#define ATM_PRIVATE_SW_MAJOR_VERSION           (1U)
#define ATM_PRIVATE_SW_MINOR_VERSION           (0U)
#define ATM_PRIVATE_SW_PATCH_VERSION           (0U)

#define ID_Counter_Address	0x00

#define StandardDelay	30
#define CashGateDelay	50
#define ExtendedDelay	300

#define NULL_ID	0xFF
#define PASSWORD_DigitNum	4
#define CASH_DigitNum		4

#define NULL_CHAR	'A'

#define SetVariables() {\
		CurrentState = WelcomeInATM;\
		LCD_ModificationFlag = TRUE;\
		LCD_PrintCharFlag = FALSE;\
		KeypadChar = 'A';\
		ERROR = NoError;\
		SWC3_SystemTick = 0;\
		SWC2_SystemTick = 0;\
		SWC7_SystemTick = 0;\
		TimeOutTick = 0;\
		User_ID = NULL_ID;\
		PasswordCounter = 0;\
		PasswordWrongCounter = 0;\
		CashCounter = 0;\
		Password[PassSize - 1] = '\0';\
		Cash[CashSize - 1] = '\0';\
		ConfirmedPassword[PassSize - 1] = '\0';\
		ID_Counter = eeprom_read_byte(ID_Counter_Address);\
		if(ID_Counter == 0xFF){\
			ID_Counter = 0;\
		}\
		ChangePasswordFlag = FALSE;\
		GateState = GATE_NULL;\
}

#define ClientInit(pass)	{\
		for(uint8 count = 0; count < PassSize; count++)\
		{\
			CurrentClient.Pass[count] = pass[count];\
		}\
		CurrentClient.Pass[PassSize - 1] = '\0';\
		CurrentClient.Cash[0] = '0';\
		CurrentClient.Cash[1] = '\0';\
		CurrentClient.ID[0] = (ID_Counter/10) + '0';\
		CurrentClient.ID[1] = (ID_Counter%10) + '0';\
		CurrentClient.ID[2] = '\0';\
		eeprom_update_byte(ID_Counter_Address, ++ID_Counter);\
}


void ATM_Init(void);

void LCD_WelcomeInATM(void);
void LCD_EnterID(void);
void LCD_EnterPassword(void);
void LCD_ConfirmPassword(void);
void LCD_NewAccount(void);
void LCD_Account(void);
void LCD_CashWithdraw(void);
void LCD_CashWithdraw_Service(void);
void LCD_OtherServices(void);
void LCD_CashWithdraw_Service(void);
void LCD_CreditDeposit_Service(void);
void LCD_CashWithdraw_Response(void);
void LCD_CreditInquiry_Response(void);
void LCD_CreditDeposit_Response(void);
void LCD_ChangePassword_Response(void);
void LCD_Error(void);

void APP_WelcomeInATM(void);
void APP_EnterID(void);
void APP_SignInEnterPassword(void);
void APP_SignUpEnterPassword(void);
void APP_ConfirmPassword(void);
void APP_Account(void);
void APP_CashWithdraw(void);
void APP_OtherServices(void);
void APP_CashWithdraw_Service(void);
void APP_CreditDeposit_Service(void);

void HandleState(ATM_State state, ATM_Error error);
static void CashWithdrawHandle(uint16 cash);
static Std_ReturnType UpdateClient(CLIENT_PROFILE* client, uint8 Item, sint8* NewVlue);
static Std_ReturnType GetClient(CLIENT_PROFILE* client, uint8 id);
static Std_ReturnType SendClient(CLIENT_PROFILE* client);
static uint64 StringToNumber(sint8* cash);
static void NumberToString(uint64 num, sint8* str);
static uint8 string_length(sint8 str[]);
static uint8 Strings_Is_Equal(sint8 Str1[], sint8 Str2[]);

#endif
