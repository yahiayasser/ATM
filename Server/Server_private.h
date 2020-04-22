/*
 * ATM_Server_private.h
 *
 *  Created on: 6 Apr 2020
 *      Author: Yahia
 */

#ifndef SERVER_PRIVATE_H_
#define SERVER_PRIVATE_H_

/* Module Version 1.0.0 */
#define SERVER_PRIVATE_SW_MAJOR_VERSION           (1U)
#define SERVER_PRIVATE_SW_MINOR_VERSION           (0U)
#define SERVER_PRIVATE_SW_PATCH_VERSION           (0U)


#include "Server_DataTypes.h"
/* Checking between Server_Private and Server_DataTypes Modules */
#if ((SERVER_PRIVATE_SW_MAJOR_VERSION != SERVER_DATATYPES_SW_MAJOR_VERSION)\
 ||  (SERVER_PRIVATE_SW_MINOR_VERSION != SERVER_DATATYPES_SW_MINOR_VERSION)\
 ||  (SERVER_PRIVATE_SW_PATCH_VERSION != SERVER_DATATYPES_SW_PATCH_VERSION))
  #error "The SW version of Server_DataTypes.h does not match the expected version"
#endif

#include "BST_interface.h"

#ifndef NULL
#define NULL	(void *)0
#endif

#define Server_MaxElements 211

#define PASS	0
#define CASH	1

#define BST_Mode	0x7

#define GetHash(value)	(((value + 6)*87)%Server_MaxElements)
#define Number(id)		(((id[0] - 48)*10) + (id[1] - 48))

#define	Server_HandleWriteCommand()	{\
		SendCommand(Server_Ready);\
		ReceiveClient(&client);\
		if(GetCommand != ATM_FrameEnd){\
			SendCommand(Server_Error);\
			return;\
		}\
		else{\
			if(Server_StoreUpdateClient(&client, Store) != E_OK){\
				SendCommand(Server_Error);\
				return;\
			}\
			else{\
				SendCommand(Server_Success);\
			}\
		}\
}

#define	Server_HandleUpdateCommand()	{\
		SendCommand(Server_Ready);\
		ReceiveClient(&client);\
		if(GetCommand != ATM_FrameEnd){\
			SendCommand(Server_Error);\
			return;\
		}\
		else{\
			if(Server_StoreUpdateClient(&client, Update) != E_OK){\
				SendCommand(Server_Error);\
				return;\
			}\
			else{\
				SendCommand(Server_Success);\
			}\
		}\
}

#define	Server_HandleGetPassCommand()	{\
		SendCommand(Server_Ready);\
		id = GetID;\
		if(id >= Tree_Counter){\
			SendCommand(Server_Error);\
			return;\
		}\
		else{\
			SendCommand(Server_Success);\
		}\
		if(SendClient(id, PASS) != E_OK){\
			SendCommand(Server_Error);\
			return;\
		}\
		else{\
			SendCommand(Server_FrameEnd);\
		}\
}

#define	Server_HandleGetCashCommand()	{\
		SendCommand(Server_Ready);\
		id = GetID;\
		if(id >= Tree_Counter){\
			SendCommand(Server_Error);\
			return;\
		}\
		else{\
			SendCommand(Server_Success);\
		}\
		if(SendClient(id, CASH) != E_OK){\
			SendCommand(Server_Error);\
			return;\
		}\
		else{\
			SendCommand(Server_FrameEnd);\
		}\
}


static void ReceiveClient(CLIENT_PROFILE* client);
static void ReadClient(CLIENT_PROFILE* client, uint8 index);
static void WriteClient(CLIENT_PROFILE* client, uint8 index);
static Std_ReturnType SendClient(uint8 id, uint8 PassCashVar);
static void GetServerTree(BST* Tree);
static void Server_HandleRestartCommand(void);
void StoreBST(BST* tree);
void HandleBST(void);
//static void InsertOriginalTree(BST_node* node);


#endif /* SERVER_PRIVATE_H_ */
