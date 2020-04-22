/*
 * Abstraction.h
 *
 *  Created on: 8 Apr 2020
 *      Author: Yahia
 */

#ifndef ABSTRACTION_H_
#define ABSTRACTION_H_

#define IO_INIT		DIO_DefinePinsDirections()
#define COM_INIT	{\
	UART_Init(BIT8, Asynchronous, ONE_STOP_BIT, BAUD_115200, DISABLE_PARITY);\
	TWI_init();\
}

#define	SendCommand(command)	SEND_DATA_UART(command)
#define SendByte(Byte)			SEND_DATA_UART(Byte)
#define GetCommand	RECEIVE_DATA_UART()
#define GetByte		RECEIVE_DATA_UART()
#define GetID		RECEIVE_DATA_UART()

#define _StoreByte(Add, Byte)	{\
	while(EEPROM_writeByte(Add, Byte) != SUCCESS);\
	_delay_ms(10);\
}
#define _ReadByteIn(Add, Byte)	{\
	while(EEPROM_readByte(Add, &Byte) != SUCCESS);\
	_delay_ms(10);\
}

#define SetDemultiplexerIndex(Index)	DIO_WritePins(Demultiplexer_PORT, (Index/EEPROM_MaxElements), Demultiplexer_SelectFilter)
#define SetDemultiplexerBST()			DIO_WritePins(Demultiplexer_PORT, 0x7, Demultiplexer_SelectFilter)

#define SetStartAddress(Index)	(EEPROM_StartAddress + ((Index % Server_MaxElements) * ClientSize))

#define	Delay(ms)	_delay_ms(ms)


#endif /* ABSTRACTION_H_ */

