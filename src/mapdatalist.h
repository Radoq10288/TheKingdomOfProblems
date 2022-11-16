/* File:         mapdatalist.h
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  10/31/2022-02:58:43-PM
 */

#ifndef MAPDATALIST_H
#define MAPDATALIST_H


typedef struct Map_Item {
	char item;
	int row;
	int col;
	struct Map_Item *next;
}Map_Item;


/* This is a simple linked-list implementation used by map.h header file.
 */


int insert_item_to_top(char const item, unsigned int const item_row, unsigned int const item_col);


int delete_item(char const item);


Map_Item* pop_top_item(void);


int print_item_list(void);


void empty_item_list(void);

#endif //MAPDATALIST_H_INCLUDED


