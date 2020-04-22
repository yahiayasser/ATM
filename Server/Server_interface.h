/*
 * Server_interface.h
 *
 *  Created on: 9 Apr 2020
 *      Author: Yahia
 */

#ifndef SERVER_INTERFACE_H_
#define SERVER_INTERFACE_H_

/* Module Version 1.0.0 */
#define SERVER_INTERFACE_SW_MAJOR_VERSION           (1U)
#define SERVER_INTERFACE_SW_MINOR_VERSION           (0U)
#define SERVER_INTERFACE_SW_PATCH_VERSION           (0U)


#define Store	1
#define	Update	0


#define ClientSize	16


void Server_Init(void);
Std_ReturnType Server_StoreUpdateClient(CLIENT_PROFILE* client, uint8 StoreUpdateVar);
CLIENT_PROFILE Server_GetClient(uint8 ID, Std_ReturnType* returnVal);
Std_ReturnType Server_DeleteClient(uint8 ID);
void Server_HandleCommand(void);

#endif /* SERVER_INTERFACE_H_ */
