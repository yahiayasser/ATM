/*
 * Server.c
 *
 *  Created on: Apr 5, 2020
 *      Author: Yahia
 */


#include "Server.h"

#include "Server_private.h"
/* Checking between Server and Server_Private Modules */
#if ((SERVER_SW_MAJOR_VERSION != SERVER_PRIVATE_SW_MAJOR_VERSION)\
		||  (SERVER_SW_MINOR_VERSION != SERVER_PRIVATE_SW_MINOR_VERSION)\
		||  (SERVER_SW_PATCH_VERSION != SERVER_PRIVATE_SW_PATCH_VERSION))
#error "The SW version of Server_Private.h does not match the expected version"
#endif

#include "BST_interface.h"

BST Server_BinarySearchTree;
uint8 Tree_Counter;


void Server_Init(void)
{
	Server_MC_Init();
	GetServerTree(&Server_BinarySearchTree);
}

static void GetServerTree(BST* tree)
{
	uint8* NodePTR = (uint8*)&(tree -> Tree);
	uint8 RootIndex;
	uint16 StartAddress = TreeStartAddr;

	SetDemultiplexerBST();

	_ReadByteIn(TreeCounterAdd, Tree_Counter);
	_ReadByteIn(RootIndexAdd, RootIndex);

	if(Tree_Counter == 0xFF)
	{
		Tree_Counter = 0;
		_StoreByte(TreeCounterAdd, Tree_Counter);
		BST_Init(&Server_BinarySearchTree);
		return;
	}
	else if(Tree_Counter == 0)
	{
		BST_Init(&Server_BinarySearchTree);
		return;
	}
	else
	{
		BST_Init(&Server_BinarySearchTree);
	}

	for(uint8 count1 = 0; count1 < Tree_Counter; count1++)
	{
		for(uint8 count2 = 0; count2 < NodeSize; count2++)
		{
			_ReadByteIn(StartAddress++, NodePTR[count2]);
		}

		NodePTR += NodeSize;
	}

	Server_BinarySearchTree.Root = &(Server_BinarySearchTree.Tree[RootIndex]);
}

void StoreBST(BST* tree)
{
	uint8 Node_Counter = 0;
	uint8* Ptr_Node;
	uint16 StartAddress = TreeStartAddr;
	BST_node* Ptr_Elemnets = (BST_node*)&(tree -> Tree[0]);
	BST_node* TreeRoot = tree -> Root;

	SetDemultiplexerBST();
	if(TreeRoot == NULL)
	{
		return;
	}

	_StoreByte(RootIndexAdd, (TreeRoot -> Index));

	for(uint8 count = 0; count < BST_Max_Elements; count++)
	{
		if(Ptr_Elemnets[count].State == BST_NODE_OCCUPIED)
		{
			Ptr_Node = (uint8*)&Ptr_Elemnets[count];
			for(uint8 count2 = 0; count2 < NodeSize; count2++)
			{
				_StoreByte(StartAddress++, Ptr_Node[count2]);
			}
			Node_Counter++;
		}
	}

	Tree_Counter = Node_Counter;
	_StoreByte(TreeCounterAdd, Tree_Counter);
}


void HandleBST(void)
{
	StoreBST(&Server_BinarySearchTree);
}

static void WriteClient(CLIENT_PROFILE* client, uint8 index)
{
	uint16 Address;
	uint8* PTR = (uint8*)client;

	Address = SetStartAddress(index);
	SetDemultiplexerIndex(index);

	for(uint8 count = 0; count < ClientSize; count++)
	{
		_StoreByte(Address++, PTR[count]);
	}
}

static void ReadClient(CLIENT_PROFILE* client, uint8 index)
{
	uint16 Address;
	uint8* PTR = (uint8*)client;

	Address = SetStartAddress(index);
	SetDemultiplexerIndex(index);

	for(uint8 count = 0; count < ClientSize; count++)
	{
		_ReadByteIn(Address++, PTR[count]);
	}
}

Std_ReturnType Server_StoreUpdateClient(CLIENT_PROFILE* client, uint8 StoreUpdateVar)
{
	uint8 Index, HashValue;
	BST_node* NodeRef = NULL;
	uint8 ID_String[3] = {client -> ID[0], client -> ID[1]};
	uint8 ID_Number;

	ID_Number = Number(ID_String);
	HashValue = GetHash(ID_Number);

	if(StoreUpdateVar == Store){
		NodeRef = BST_Insert(&Server_BinarySearchTree, HashValue);
		/*if(NodeRef != NULL){
			InsertOriginalTree(NodeRef);
		}*/
	}
	else if(StoreUpdateVar == Update)
		NodeRef = BST_FindElement(&Server_BinarySearchTree, HashValue);
	else{
		//error message
	}

	if(NodeRef == NULL)
		return E_NOT_OK;
	else{
		Index = NodeRef -> Index;
		WriteClient(client, Index);
	}

	return E_OK;
}

CLIENT_PROFILE Server_GetClient(uint8 ID, Std_ReturnType* returnVal)
{
	CLIENT_PROFILE client;
	uint8 Index, HashValue;
	BST_node* NodeRef = NULL;

	*returnVal = E_NOT_OK;

	HashValue = GetHash(ID);
	NodeRef = BST_FindElement(&Server_BinarySearchTree, HashValue);

	if(NodeRef == NULL){
		return client;
	}
	else{
		Index = NodeRef -> Index;
		ReadClient(&client, Index);
	}

	*returnVal = E_OK;
	return client;
}

static void ReceiveClient(CLIENT_PROFILE* client)
{
	uint8* PTR = (uint8*)client;

	for(uint8 count = 0; count < ClientSize; count++)
	{
		PTR[count] = GetByte;
	}
}

static Std_ReturnType SendClient(uint8 id, uint8 PassCashVar)
{
	Std_ReturnType Return = E_NOT_OK;
	CLIENT_PROFILE Client;
	uint8* PTR;

	Client = Server_GetClient(id, &Return);
	PTR = (uint8*)(&Client);

	if(PassCashVar == PASS)
	{
		for(uint8 count = 0; count < PassSize; count++)
		{
			SendByte(Client.Pass[count]);
			Delay(10);
		}
	}
	else if(PassCashVar == CASH)
	{
		for(uint8 count = 0; count < CashSize; count++)
		{
			SendByte(Client.Cash[count]);
			Delay(10);
		}
	}
	else
	{
		Return = E_NOT_OK;
		//error message
	}

	return Return;
}

static void Server_HandleRestartCommand(void)
{
	uint16 StartAddress = TreeStartAddr;

	SetDemultiplexerBST();

	_ReadByteIn(TreeCounterAdd, Tree_Counter);

	if(Tree_Counter == 0)
	{
		SendCommand(Server_Success);
		return;
	}
	else if(Tree_Counter == 0xFF)
	{
		SendCommand(Server_Success);
		_StoreByte(TreeCounterAdd, 0)
		return;
	}
	else
	{
		_StoreByte(TreeCounterAdd, 0);
		_StoreByte(RootIndexAdd, 0);
		_StoreByte(TreeStartAddr, 0);
		for(uint8 count1 = 0; count1 < Tree_Counter; count1++)
		{
			for(uint8 count2 = 0; count2 < NodeSize; count2++)
			{
				_StoreByte(StartAddress++, 0xFF);
			}
		}
	}
	Tree_Counter = 0;
	SendCommand(Server_Success);
	BST_Init(&Server_BinarySearchTree);
}

void Server_HandleCommand(void)
{
	uint8 command;
	CLIENT_PROFILE client;
	uint8 id;

	SendCommand(Server_Ready);
	command = GetCommand;

	switch(command)
	{
	case ATM_WriteClient:
		Server_HandleWriteCommand();
		break;
	case ATM_UpdateClient:
		Server_HandleUpdateCommand();
		break;
	case ATM_GetClientPass:
		Server_HandleGetPassCommand();
		break;
	case ATM_GetClientCash:
		Server_HandleGetCashCommand();
		break;
	case ATM_Restart:
		Server_HandleRestartCommand();
		break;
	default:
		SendCommand(Server_Error);
		return;
	}

	if(GetCommand != ATM_EndTransmission){
		SendCommand(Server_Error);
		return;
	}
	else{
		SendCommand(Server_Success);
	}
}
