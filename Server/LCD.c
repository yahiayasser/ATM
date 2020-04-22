/*
 * LCD.c
 *
 *  Created on: 5 Apr 2019
 *      Author: Yahia
 */
#include"LCD.h"

void LCD_Init(volatile const uint8 a_NumBits, volatile const uint8 a_Cursor){
	/*This function is responsible for initializing LCD.
	 * DataPort is for defining the port of data.
	 * You can use PORTA, PORTB, PORTC, PORTD
	   for DataPort in header file.
	 * RS is for defining the pin of RS, you should choose number
	   from 0:31.
	 * RW is for defining the pin of RW, you should choose number
	   from 0:31.
	 * Enable is for defining the pin of E, you should choose number
	   from 0:31.
	 * a_Cursor for defining the status of the cursor, you can also
	   use CursorOff, CursorOn, CursorBlinking OR 0x0C, 0x0E, 0x0F respectively.
	 * a_NumBits for defining the number of bits(data to be transmitted 4/8 bits)
	   you can also use LCD_4Bit, LCD_4Bit OR 0x28, 0x38 respectively.
	 * */
	DIO_PortOutput(DataPort);
	DIO_MakeOutput(RS);
	DIO_MakeOutput(RW);
	DIO_MakeOutput(Enable);
	LCD_SendCommand(a_NumBits);
	LCD_SendCommand(a_Cursor);
	LCD_SendCommand(Clear_LCD);
}

void LCD_SendCommand(volatile const uint8 a_Command){
	DIO_ClearChannel(RS); //RS = 0 ===> command mode.
	DIO_ClearChannel(RW); //RW = 0 ===> Write Data.
	_delay_ms(1); /* delay for processing Tas = 50ns */
	DIO_WriteChannel(Enable);
	_delay_ms(1); /* delay for processing Tpw - Tdsw = 190ns */
	DIO_WritePort(DataPort, a_Command);
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_ClearChannel(Enable);
	_delay_ms(1); /* delay for processing Th = 13ns */
}

void LCD_SendCharacter(volatile const uint8 a_Character){
	DIO_WriteChannel(RS); //RS = 1 ===> data mode.
	DIO_ClearChannel(RW); //RW = 0 ===> Write Data.
	_delay_ms(1); /* delay for processing Tas = 50ns */
	DIO_WriteChannel(Enable);
	_delay_ms(1); /* delay for processing Tpw - Tdsw = 190ns */
	DIO_WritePort(DataPort, a_Character);
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_ClearChannel(Enable);
	_delay_ms(1); /* delay for processing Th = 13ns */
}

void LCD_SendString(const uint8 *String){
	uint8 count = 0;
	while(String[count] != '\0'){
		LCD_SendCharacter(String[count]);
		count++;
	}
}

void LCD_SetCursor(uint8 a_Row, uint8 a_Column){
	uint8 a_Command;
	switch(a_Row){
	case(0):
		a_Command = 0x80 + a_Column;
	break;
	case(1):
		a_Command = 0x80 + 0x40 + a_Column;
	break;
	case(2):
		a_Command = 0x80 + 0x10 + a_Column;
	break;
	case(3):
		a_Command = 0x80 + 0x50 + a_Column;
	break;
	}
	LCD_SendCommand(a_Command);
}

void LCD_DisplayInteger(sint32 a_Int){
	uint8 Integer[10];
	uint8 count = 0;
	uint8 count_ = 0;
	uint8 temp = 0;
	uint8 flag = 0;
	if(a_Int < 0){
		Integer[count] = '-';
		a_Int = a_Int*-1;
		count ++;
		count_ ++;
		flag = 1;
	}
	if(a_Int == 0){
		Integer[count] = 48;
		Integer[count + 1] = '\0';
	}
	else{
		while(a_Int != 0){
			Integer[count] = a_Int % 10;
			a_Int = a_Int / 10;
			count ++;
		}
		while((count-1) >= count_){
			temp = Integer[count_];
			Integer[count_] = Integer[count - 1] + '0';
			Integer[count - 1] = temp + '0';
			count--;
			count_++;
		}
		if(flag == 0)
			Integer[count + count_] = '\0';
		else
			Integer[count + count_ - 1] = '\0';
	}
	LCD_SendString(Integer);
}

void LCD_ClearScreen(void){
	LCD_SendCommand(Clear_LCD);
	LCD_SetCursor(0, 0);
}
