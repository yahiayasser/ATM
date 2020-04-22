/*
 * External_EEPROM_I2C.c
 *
 * Created: 3/12/2014 12:05:19 PM
 *  Author: Mohamed Tarek
 */


#include "Server.h"
#include "BST_interface.h"

int main(void)
{
	Server_Init();

	while(1){
		if(GetByte == ATM_TriggerTransmission)
		{
			Server_HandleCommand();
		}
		HandleBST();
	}
}
