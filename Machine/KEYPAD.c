/*
 * KEYPAD.c
 *
 *  Created on: 8 Apr 2019
 *      Author: Yahia
 */


#include"KEYPAD.h"

uint8 KEYPAD_GetStatus(void){
	uint8 Col, Rows;
	for(Col = 0; Col < Num_Columns; Col++){
#if(Num_Columns == 4)
		Keypad_PORT_Direction = (0b00010000<<Col);
		Keypad_PORT_Output = ~(0b00010000<<Col);
#elif(Num_Columns == 3)
		Keypad_PORT_Direction = (Keypad_PORT_Direction & 0x80)|(0b00010000<<Col);
		Keypad_PORT_Output = (Keypad_PORT_Output & 0x80)|((~(0b00010000<<Col))&0x7F);
#endif
		for(Rows= 0; Rows < Num_Rows; Rows++){
			if(BIT_IS_CLEAR(Keypad_PORT_Input, Rows)){
#if (Num_Columns == 3)
				return KEYPAD_4x3_adjustKeyNumber((Rows*Num_Columns)+Col+1);
#elif (Num_Columns == 4)
				return KEYPAD_4x4_adjustKeyNumber((Rows*Num_Columns)+Col+1);
#endif
			}
		}
	}
	return 'A';
}

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_NUM){
	switch(a_NUM){
	case(1):
		return '7';
	break;
	case(2):
		return '8';
	break;
	case(3):
		return '9';
	break;
	case(4):
		return '%';
	break;
	case(5):
		return '4';
	break;
	case(6):
		return '5';
	break;
	case(7):
		return '6';
	break;
	case(8):
		return '*';
	break;
	case(9):
		return '1';
	break;
	case(10):
		return '2';
	break;
	case(11):
		return '3';
	break;
	case(12):
		return '-';
	break;
	case(13):
		return 'C';
	break;
	case(14):
		return '0';
	break;
	case(15):
		return '=';
	break;
	case(16):
		return '+';
	break;
	default:
		return a_NUM;
	}
}
