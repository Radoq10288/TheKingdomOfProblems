/* File:         src/map.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  11/04/2022-11:01:17-PM
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "stack.h"


static struct Reference_Position {
	int row_pos;
	int column_pos;
}ref_pos;


/* This function will seek for possible army or armies lurking in the region
 * being explored.
 *
 * Note:
 * It assumes that the army or armies is consist of small caps 26 letter of
 * the english alphabet. Any big caps letter will be ignored.
 *
 * Return
 * If function succeed, returns zero else, returns non-negative value.
 *
 * Description of each non-negative values returned by
 * seek_armies_in_region().
 * 1 - the initial position indicated is not an empty land or an army.
 * 2 - no army or armies found within the region being explored.
 *
 * int seek_armies_in_region(
 *		char **map,							// The 2D array map.
 *		unsigned int const row_size,		// The size of the 2D array map in its x-axis.
 *		unsigned int const col_size,		// The size of the 2D array map in its y-axis.
 *		unsigned int const start_x_pos,		// The x-axis position in the map where to start survey of the region.
 *		unsigned int const start_y_pos,		// The y-axis position in the map where to start survey of the region.
 *		Kingdom *kngdm						// Output: This will contain the list of army that is found in each region.
 * );
 */


static int seek_armies_in_region(char **map, size_t const row_size, size_t const col_size, unsigned int const start_x_pos, unsigned int const start_y_pos, Kingdom kngdm[]) {
	bool found_armies = false;
	char label = '0', empty_land = '.';
	int count = 0;
	unsigned int x_pos = start_x_pos, y_pos = start_y_pos;
	
	make_stack();
	Map_Item *temp;
	
	if (map[x_pos][y_pos] == empty_land  || (isalpha(map[x_pos][y_pos]) && islower(map[x_pos][y_pos]))) {
		push(map[x_pos][y_pos], x_pos, y_pos);
		map[x_pos][y_pos] = label;
		temp = pop();
	}
	else {
		return 1; // Not an empty land or an army.
	}
	
	while (temp != NULL) {
		
		if (isalpha(temp->item)) {
			found_armies = true;
			kngdm[count].factn.army = temp->item;
			kngdm[count].factn.controlled_regions = 1;
			kngdm[count].regn.contested = false;
			kngdm[count].regn.occupying_army_count = 1;
			count++;
		}
		
		x_pos = temp->row;
		y_pos = temp->col;
		
		/* Save the current reference position to be able to return to this
		 * position after scanning each four neighbor.
		 */
		ref_pos.row_pos = x_pos;
		ref_pos.column_pos = y_pos;
		
		for (int n = 0; n != 4; n++) {
			
			switch (n) {
				case 0: if (y_pos > 0) { y_pos--; } break;
				case 1: if (x_pos > 0) { x_pos--; } break;
				/* To prevent out of bound index, col_size and row_size is lessen
				 * by one.
				 */
				case 2: if (y_pos < (col_size - 1)) { y_pos++; } break;
				case 3: if (x_pos < (row_size - 1)) { x_pos++; } break;
			}
			
			if (map[x_pos][y_pos] == empty_land || (isalpha(map[x_pos][y_pos]) && islower(map[x_pos][y_pos]))) {
				push(map[x_pos][y_pos], x_pos, y_pos);
				map[x_pos][y_pos] = label;
			}
			
			x_pos = ref_pos.row_pos;
			y_pos = ref_pos.column_pos;
		}
		
		temp = pop();
	}
	
	destroy_stack(temp);
	kngdm[count].factn.army = '\0';
	if (found_armies == false) { return 2; } // No army is found.
	return 0;
}


int explore_the_map(char **map, size_t const row_size, size_t const col_size, Kingdom *kngdm) {
	if (map == NULL) { return 1; }
	for (int x = 0; x != row_size; x++) {
		for (int y = 0; y != col_size; y++) {
			seek_armies_in_region(map, row_size, col_size, x, y, kngdm);
		}
	}
	return 0;
}


int sort_out_armies(Kingdom *kngdm) {
	if (kngdm == NULL) { return 1; }
	/* Sort out similar faction residing in the same region.
	 */
	for (int r = 0; kngdm[r].factn.army != '\0'; r++) {
		for (int y = 0; kngdm[y].factn.army != '\0'; y++) {
			if (kngdm[r].factn.army == kngdm[y].factn.army && kngdm[r].regn.region_number == kngdm[y].regn.region_number && r != y) {
				kngdm[y].factn.army = '~';
				kngdm[y].factn.controlled_regions = 0;
				kngdm[y].regn.region_number = 0;
				kngdm[y].regn.occupying_army_count = 0;
			}
		}
	}


	// Sort out different faction occupying the same region.
	int region = 1;
	for (int n = 0; kngdm[n].factn.army != '\0'; n++) {
		int found_unique_army = 0;
		
		for (int r = 0; kngdm[r].factn.army != '\0'; r++) {
			// Count how many unique faction are found in the same region.
			for (int y = 0; kngdm[y].factn.army != '\0'; y++) {
				if (isalpha(kngdm[y].factn.army) && kngdm[y].regn.region_number == region) { found_unique_army++; }
			}
			
			if (isalpha(kngdm[r].factn.army) && kngdm[r].regn.region_number == region && found_unique_army > 1) {
				kngdm[r].factn.controlled_regions = 0;
				kngdm[r].regn.contested = true;
				kngdm[r].regn.occupying_army_count = found_unique_army;
			}
			found_unique_army = 0;
		}
		region++;
	}


	/* Sort out similar factions that resides in different regions.
	 */
	for (int r = 0; kngdm[r].factn.army != '\0'; r++) {
		for (int y = 0; kngdm[y].factn.army != '\0'; y++) {
			if (kngdm[r].factn.army == kngdm[y].factn.army && kngdm[r].regn.region_number != kngdm[y].regn.region_number && r != y) {
				if (kngdm[y].regn.contested == false && kngdm[r].regn.contested == false) {
					kngdm[r].factn.controlled_regions += 1;
					kngdm[r].regn.region_number = 0;
					kngdm[r].regn.occupying_army_count = 0;
					
					kngdm[y].factn.army = '~';
					kngdm[y].factn.controlled_regions = 0;
					kngdm[y].regn.region_number = 0;
					kngdm[y].regn.occupying_army_count = 0;
				}
			}
		}
	}
	
	/* Sort list alphabetically.
	 */
	Kingdom temp;
	for (int r = 0; kngdm[r].factn.army != '\0'; r++) {
		for (int y = 0; kngdm[y].factn.army != '\0'; y++) {
			if (isalpha(kngdm[y].factn.army) && isalpha(kngdm[y + 1].factn.army) && kngdm[y].factn.army > kngdm[y + 1].factn.army) {
				temp = kngdm[y + 1];
				kngdm[y + 1] = kngdm[y];
				kngdm[y] = temp;
			}
		}
	}
	
	return 0;
}


int print_kingdom_report(Kingdom *kngdm, size_t const row_size, size_t const column_size) {
	if (kngdm == NULL) { return 1; }
	for (int i = 0; kngdm[i].factn.army != '\0'; i++) {
		if (isalpha(kngdm[i].factn.army) && kngdm[i].factn.controlled_regions != 0) {
			printf("%c %d\n", kngdm[i].factn.army, kngdm[i].factn.controlled_regions);
		}
	}
	
	int K = 0, region = 0;
	for (int i = 0; kngdm[i].factn.army != '\0'; i++) {
		if (kngdm[i].regn.contested == true && kngdm[i].regn.region_number != region) {
			region = kngdm[i].regn.region_number;
			K += 1;
		}
	}
	
	if (K != 0) { printf("contested: %d\n", K); }
	printf("\n");
	return 0;
}


int print_faction_list(Kingdom *kngdm) {
	if (kngdm == NULL) { return 1; }
	for (int i = 0; kngdm[i].factn.army != '\0'; i++) {
		printf("faction=%c CR=%d RN=%d C=%d OAC=%d\n",
			kngdm[i].factn.army,
			kngdm[i].factn.controlled_regions,
			kngdm[i].regn.region_number,
			kngdm[i].regn.contested,
			kngdm[i].regn.occupying_army_count
		);
	}
	printf("\n");
	return 0;
}


