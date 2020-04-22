/*
 * BST_private.h
 *
 *  Created on: 4 Jan 2020
 *      Author: Yahia
 */

#ifndef BST_PRIVATE_H_
#define BST_PRIVATE_H_

#ifndef NULL
#define NULL	(void *)0
#endif

#ifndef MAX_Index
#define MAX_Index	0xFF
#endif

#ifndef BST_LEFT
#define BST_LEFT	0
#endif

#ifndef BST_RIGHT
#define BST_RIGHT	1
#endif

void BST_Free(BST_node* PtrToNode);
void BST_UpdateIndex(BST_node* current, BST_node* prev, uint8 direction);
BST_node* BST_Find_Parent(BST_node* root, uint8 index);

#endif /* BST_PRIVATE_H_ */
