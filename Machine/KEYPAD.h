/*
 * KEYPAD.h
 *
 *  Created on: 8 Apr 2019
 *      Author: Yahia
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include"DIO.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * Please Specify the type of keypad (4*4 or 4*3)        *
   * by defining the type you have and undefine the other  *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   */
#define Num_Columns 4
#define Num_Rows 4

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *  * Please choose the port that you will connect your  *
   *  * keypad to it                                       *
   *  * make sure that you connect the pins of rows to the *
   *    LSB and pins of columns to MSB.                    *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   */
#define Keypad_PORT_Direction PORTA_direction
#define Keypad_PORT_Input PORTA_input
#define Keypad_PORT_Output PORTA_output

uint8 KEYPAD_GetStatus(void);
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 a_NUM);
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_NUM);

#endif /* KEYPAD_H_ */
