/*
 * LCD.h
 *
 *  Created on: 5 Apr 2019
 *      Author: Yahia
 */

#ifndef LCD_H_
#define LCD_H_

#include"DIO.h"
#include"TIMER.h"

#define No_Lines 4
/*Please specify a port for DataPort and pins for RS, RW, Enable(pins from 0:31)*/
#define DataPort DIO_PORTB/*DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD*/
#define RS 29/*(0:31)*/
#define RW 30/*(0:31)*/
#define Enable 31/*(0:31)*/

#define FunctionSet_8bit_2line 0x38
#define FunctionSet_4bit_2line 0x28
#define CursorOff 0x0C
#define CursorOn 0x0E
#define CursorBlinking 0x0F
#define Clear_LCD 0x01
#define Cursor_Location 0x80

typedef enum{
	LCD_4Bit = 0x28, LCD_8Bit = 0x38
}LCD_NUM_BITS;

void LCD_Init(volatile const uint8 a_NumBits, volatile const uint8 a_Cursor);
void LCD_SendCommand(volatile const uint8 a_Command);
void LCD_SendCharacter(volatile const uint8 a_Character);
void LCD_SendString(const sint8 *String);
void LCD_DisplayInteger(sint32 a_Int);
void LCD_SetCursor(uint8 a_Row, uint8 a_Column);
void LCD_ClearScreen(void);

#endif /* LCD_H_ */
