/* File:         src/stack.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  11/19/2022-02:12:58-PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define STACK_MAX_SIZE	2500

static Map_Item *mapi; 
static int stack_size = -1;


int make_stack(void) {
	mapi = malloc(sizeof(Map_Item) * STACK_MAX_SIZE);
	if (mapi == NULL) { return 1; }
	return 0;
}


int push(char const item, unsigned int const item_row, unsigned int const item_col) {
	if (mapi == NULL) { return 1; }
	stack_size++;
	if (stack_size == STACK_MAX_SIZE) {
		stack_size--;
		return 2;
	}
	else {
		mapi[stack_size].item = item;
		mapi[stack_size].row = item_row;
		mapi[stack_size].col = item_col;
	}
	return 0;
}


Map_Item* pop(void) {
	Map_Item *element = malloc(sizeof(Map_Item));
	if (stack_size == -1 || mapi == NULL) {
		return NULL;
	}
	else {
		element->item = mapi[stack_size].item;
		element->row = mapi[stack_size].row;
		element->col = mapi[stack_size].col;
		stack_size--;
	}
	
	return element;
}


void destroy_stack(Map_Item *stack) {
	free(mapi); // Frees the actual stack.
	mapi = NULL;
	free(stack); // Frees the Map_Item variable allocated from the pop() function.
	stack = NULL;
}


