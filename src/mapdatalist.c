/* File:         mapdatalist.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  10/31/2022-02:58:43-PM
 */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mapdatalist.h"


static Map_Item *mi = NULL;


int insert_item_to_top(char const item, unsigned int const item_row, unsigned int const item_col) {
	Map_Item *new_item = (Map_Item*)malloc(sizeof(Map_Item));
	if (new_item == NULL) { return 1; }

	new_item->item = item;
	new_item->row = item_row;
	new_item->col = item_col;
	new_item->next = mi;

	mi = new_item;

	return 0;
}


int delete_item(char const item) {
	if (mi == NULL) { return 1; }

	Map_Item *temp = mi, *prev;
	bool is_item_found = false;

	while (temp != NULL) {
		if (temp->item == item) {
			is_item_found = true;
			break;
		}
		prev = temp;
		temp = temp->next;
	}

	if (is_item_found == false) {
		return 2;
	}

	prev->next = temp->next;
	free(temp);
	return 0;
}


Map_Item* pop_top_item(void) {
	Map_Item *new_head, *old_head;

	if (mi == NULL) { return NULL; }
	old_head = mi;
	new_head = mi->next;
	mi = new_head;

	return old_head;
}


int print_item_list(void) {
	if (mi == NULL) {
		printf("No item found to print!\n");
		return 1;
	}

	printf("Items:\n");
	while (mi != NULL) {
		printf("%c\t%d\t%d\n", mi->item, mi->row, mi->col);
		mi = mi->next;
	}
	printf("\n");

	return 0;
}


void empty_item_list(void) {
	free(mi);
	mi = NULL;
}


