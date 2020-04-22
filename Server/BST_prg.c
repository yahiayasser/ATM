/*
 * BST_prg.c
 *
 *  Created on: 4 Jan 2020
 *      Author: Yahia
 */

#include "Platform_Types.h"
#include "common_macros.h"

#include "BST_interface.h"
#include "BST_private.h"

#if(BST_PRINT == BST_PRINTING)
#include <stdio.h>
#include <stdlib.h>
#endif

void BST_Init(BST* BST_ptr){
	BST_node* Ptr_Elemnets = (BST_node*)&(BST_ptr -> Tree);
	uint8 count = 0;
	while(count != BST_Max_Elements){
		Ptr_Elemnets[count].Data = 0;
		Ptr_Elemnets[count].PtrToLeftNode = NULL;
		Ptr_Elemnets[count].PtrToRightNode = NULL;
		Ptr_Elemnets[count].State = BST_NODE_EMPTY;
		Ptr_Elemnets[count].Index = MAX_Index;
		Ptr_Elemnets[count].leaf_state = BST_NODE_NULL;
		count++;
	}
	BST_ptr -> Root = NULL;
}

BST_node* BST_Insert(BST* BST_ptr, BST_DataSize data){

	BST_node* Ptr_Elemnets = (BST_node*)&(BST_ptr -> Tree);
	BST_node* current = BST_ptr -> Root;
	uint8 count = 0;
	uint8 index = 0;
	BST_node* NodeRef;
	while((count < BST_Max_Elements) && ((Ptr_Elemnets[count].State) == BST_NODE_OCCUPIED)){
		count++;
	}
	if(count == BST_Max_Elements){
		return NULL;
	}
	else{
		Ptr_Elemnets[count].State = BST_NODE_OCCUPIED;
		Ptr_Elemnets[count].Data = data;
		Ptr_Elemnets[count].leaf_state = BST_NODE_LEAF;
		NodeRef = &Ptr_Elemnets[count];
		if(current == NULL){
			Ptr_Elemnets[count].Index = index;
			BST_ptr -> Root = &Ptr_Elemnets[count];
			return NodeRef;
		}
		else{
			while(!((((current -> PtrToLeftNode) == NULL) && (data <= (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (data > (current -> Data)))))){
				if(data < (current -> Data)){
					current = current -> PtrToLeftNode;
					index = (index << 1) + 1;
				}
				else if(data > (current -> Data)){
					current = current -> PtrToRightNode;
					index = (index << 1) + 2;
				}
				else{
					Ptr_Elemnets[count].State = BST_NODE_EMPTY;
					Ptr_Elemnets[count].Data = 0;
					Ptr_Elemnets[count].leaf_state = BST_NODE_NULL;
					return NULL;
				}
			}
			if(data < (current -> Data)){
				current -> PtrToLeftNode = &Ptr_Elemnets[count];
				current -> leaf_state += BST_NODE_LEFT_CHILD;
				Ptr_Elemnets[count].Index = (index << 1) + 1;
				return NodeRef;
			}
			else if (data > (current -> Data)){
				current -> PtrToRightNode = &Ptr_Elemnets[count];
				current -> leaf_state += BST_NODE_RIGHT_CHILD;
				Ptr_Elemnets[count].Index = (index << 1) + 2;
				return NodeRef;
			}
			else{
				Ptr_Elemnets[count].State = BST_NODE_EMPTY;
				Ptr_Elemnets[count].Data = 0;
				Ptr_Elemnets[count].leaf_state = BST_NODE_NULL;
				return NULL;
			}
		}
	}
}

BST_node* BST_FindElement(BST* BST_ptr, BST_DataSize data){
	BST_node* current = BST_ptr -> Root;
	if(current == NULL){
		return current;
	}
	while(!((((current -> PtrToLeftNode) == NULL) && (data < (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (data > (current -> Data)))))){
		if(data == (current -> Data)){
			return current;
		}
		if(data < (current -> Data)){
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_RIGHT_CHILD)){
				return NULL;
			}
			else{
				current = current -> PtrToLeftNode;
			}
		}
		else{
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_LEFT_CHILD)){
				return NULL;
			}
			else{
				current = current -> PtrToRightNode;
			}
		}
	}
	return NULL;
}

void BST_Free(BST_node* PtrToNode){
	PtrToNode -> Data = 0;
	PtrToNode -> PtrToLeftNode = NULL;
	PtrToNode -> PtrToRightNode = NULL;
	PtrToNode -> State = BST_NODE_EMPTY;
	PtrToNode -> Index = MAX_Index;
	PtrToNode -> leaf_state = BST_NODE_NULL;
}

void BST_UpdateIndex(BST_node* current, BST_node* prev, uint8 direction){
	if(current == NULL){
		return;
	}
	if(prev == NULL){
		current -> Index = 0;
	}

	else{
		if(direction == BST_LEFT)
			current -> Index = ((prev -> Index) << 1) + 1;
		else
			current -> Index = ((prev -> Index) << 1) + 2;
	}
	if(((current -> PtrToLeftNode) == NULL) && ((current -> PtrToRightNode) == NULL)){
		return;
	}
	BST_UpdateIndex(current -> PtrToLeftNode, current, BST_LEFT);
	BST_UpdateIndex(current -> PtrToRightNode, current, BST_RIGHT);
}

BST_node* BST_Find_Parent(BST_node* root, uint8 index){
	index += 1;
	index = index >> 1;
	uint8 temp = index;
	uint8 count = 0;
	uint8 sum = 0;
	while(temp != 1){
		sum = (temp % 2) + (sum << count);
		count++;
		temp = temp >> 1;
	}
	while(count != 0){
		if(sum & 1){
			root = root -> PtrToRightNode;
		}
		else{
			root = root -> PtrToLeftNode;
		}
		sum = sum >> 1;
		count--;
	}
	return root;
}

BST_ErrorType BST_Delete(BST* BST_ptr, BST_DataSize data){
	BST_node* current = BST_ptr -> Root;
	BST_node* prev = BST_ptr -> Root;
	uint8 index = 0;
	uint8 direction_flag = 0;
	BST_node* temp_add = prev;
	BST_NODE_LeafOrNot temp_child;
	BST_DataSize temp;
	if(current == NULL){
		return BST_Empty;
	}
	while(!((((current -> PtrToLeftNode) == NULL) && (data < (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (data > (current -> Data)))))){
		if(data == (current -> Data)){
			if(((current -> PtrToLeftNode) == NULL) && ((current -> PtrToRightNode) == NULL)){
				if(current == prev){
					BST_ptr -> Root = NULL;
					BST_Free(current);
					return BST_NoError;
				}
				if((current -> Data) <= (prev -> Data)){
					prev -> PtrToLeftNode = NULL;
					prev -> leaf_state -= BST_NODE_LEFT_CHILD;
				}
				else{
					prev -> PtrToRightNode = NULL;
					prev -> leaf_state -= BST_NODE_RIGHT_CHILD;
				}
				BST_Free(current);
				return BST_NoError;
			}
			else if(((current -> PtrToLeftNode) == NULL)){
				if(current == prev){
					BST_ptr -> Root = current -> PtrToRightNode;
					BST_Free(current);
					return BST_NoError;
				}
				if((current -> Data) <= (prev -> Data)){
					prev -> PtrToLeftNode = current -> PtrToRightNode;
				}
				else{
					prev -> PtrToRightNode = current -> PtrToRightNode;
				}
				BST_Free(current);
				BST_UpdateIndex(BST_ptr -> Root, NULL, BST_LEFT);
				return BST_NoError;
			}
			else if(((current -> PtrToRightNode) == NULL)){
				if(current == prev){
					BST_ptr -> Root = current -> PtrToLeftNode;
					BST_Free(current);
					return BST_NoError;
				}
				if((current -> Data) <= (prev -> Data)){
					prev -> PtrToLeftNode = current -> PtrToLeftNode;
				}
				else{
					prev -> PtrToRightNode = current -> PtrToLeftNode;
				}
				BST_Free(current);
				BST_UpdateIndex(BST_ptr -> Root, NULL, BST_LEFT);
				return BST_NoError;
			}
			else{
				prev = current;
				current = current -> PtrToRightNode;
				while((current -> PtrToLeftNode) != NULL){
					current = current -> PtrToLeftNode;
					direction_flag = 1;
				}
				temp_add = current -> PtrToRightNode;
				temp = current -> Data;
				current -> Data = prev -> Data;
				prev -> Data = temp;
				//prev -> leaf_state = current -> leaf_state;
				temp_child = current -> leaf_state;
				index = current -> Index;
				BST_Free(current);
				current = BST_Find_Parent(BST_ptr -> Root, index);
				if(direction_flag){
					current -> PtrToLeftNode = temp_add;
					current -> leaf_state = (current -> leaf_state) - BST_NODE_LEFT_CHILD + temp_child;
				}
				else{
					current -> PtrToRightNode = temp_add;
					current -> leaf_state = (current -> leaf_state) - BST_NODE_RIGHT_CHILD + temp_child;
				}
				BST_UpdateIndex(BST_ptr -> Root, NULL, BST_LEFT);
				return BST_NoError;

			}
		}
		if(data < (current -> Data)){
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_RIGHT_CHILD)){
				return BST_ElementNotFound;
			}
			else{
				prev = current;
				current = current -> PtrToLeftNode;
			}
		}
		else{
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_LEFT_CHILD)){
				return BST_ElementNotFound;
			}
			else{
				prev = current;
				current = current -> PtrToRightNode;
			}
		}
	}
	return BST_ElementNotFound;
}

#if(BST_PRINT ==  BST_PRINTING)
BST_ErrorType BST_Print(BST* BST_ptr){
	BST_node* Ptr_Elemnets = (BST_node*)&(BST_ptr -> Tree);
	BST_node* current = BST_ptr -> Root;
	const uint8 arr_size = 200;
	BST_DataSize arr[arr_size];
	uint8 max_index = 0;
	uint8 count1 = 0;
	uint8 count2 = 0;
	uint8 count3 = 0;
	uint8 count4 = 0;
	//setbuf(stdout, NULL);
	if(current == NULL){
		return BST_Empty;
	}
	while(count1 != arr_size){
		arr[count1] = MAX_Index;
		count1++;
	}
	count1 = 0;
	while(count1 != BST_Max_Elements){
		if((Ptr_Elemnets[count1].Index) == MAX_Index){

		}
		else{
			arr[Ptr_Elemnets[count1].Index] = Ptr_Elemnets[count1].Data;
			if((Ptr_Elemnets[count1].Index) > max_index)
				max_index = Ptr_Elemnets[count1].Index;
		}
		count1++;
	}
	for(count1 = 0; count1 < 10; count1++){
		while(count3 != (10 - count1)){
			printf("   ");
			count3 += 1;
		}
		count3 = 0;
		for(count2 = 0; count2 < (1 << count1); count2++){
			if(arr[count4] == MAX_Index){
				printf(" _ ");
			}
			else{
				printf(" %d ", arr[count4]);
			}
			if(count4 == max_index){
				printf("\n");
				return BST_NoError;
			}
			count4++;
		}
		printf("\n");
	}
	printf("\n");
	return BST_NoError;
}
#endif

