/* File:         src/stack.h
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  11/19/2022-02:12:58-PM
 */

#ifndef STACK_H
#define STACK_H

typedef struct Map_Item {
	char item;
	int row;
	int col;
}Map_Item;


int make_stack(void);


int push(char const item, unsigned int const item_row, unsigned int const item_col);


Map_Item* pop(void);


void destroy_stack(Map_Item *stack);

#endif //STACK_H_INCLUDED


