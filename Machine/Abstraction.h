#ifndef __ABSTRACTION_H_
#define __ABSTRACTION_H_

#define IO_INIT 	DIO_DefinePinsDirections()
#define COM_INIT	UART_init()

#define InitiateSchedulerTimer(Tick)	TIMER1_Init_MSeconds(T1_F_CPU_1024, Tick, ChannelA)
#define SetCallbackHandler(function)	PTR_TIM1_Handler_Setter(function)

#define	OUTPUT_MODULES_INIT	LCD_Init(LCD_8Bit, CursorOff)

#define TurnOnLED(led)	DIO_WriteChannel(led)
#define TurnOffLED(led)	DIO_ClearChannel(led)

#define MotorClockWise()	{\
		DIO_ClearChannel(GATE_PIN_1);\
		DIO_WriteChannel(GATE_PIN_2);\
}

#define MotorAntiClockWise()	{\
		DIO_WriteChannel(GATE_PIN_1);\
		DIO_ClearChannel(GATE_PIN_2);\
}

#define MotorStop()	{\
		DIO_ClearChannel(GATE_PIN_1);\
		DIO_ClearChannel(GATE_PIN_2);\
}

#define RestartButton()	DIO_ReadChannel(27)

#define	SendCommand(command)	UART_sendByte(command)
#define SendByte(Byte)			UART_sendByte(Byte)
#define GetCommand()	UART_recieveByte()
#define GetByte()		UART_recieveByte()
#define GetID()			UART_recieveByte()


#endif
