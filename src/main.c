/* File:         kingdom-problem/src/main.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  10/25/2022-08:27:10-PM
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readstdin.h"
#include "matrix2d.h"
#include "map.h"


#define MAX_TEST_CASE	5


// It's the map.
static char **the_map;

// The Crystal Kingdom.
static Kingdom *kngdm;

// Uncomment the line below to enable debugging.
//#define DEBUG_MODE

int set_test_case() {
	int T = 0, N = 0, M = 0;
	int *int_ptr[2] = {&N, &M};
	
	// How many test case to attempt?
	read_number(&T, 1);
	if (T > MAX_TEST_CASE) {
		fprintf(stderr,
				"User's fault:\n"
				"Attempt to abuse test case!\n"
				"Your horrible, you know that!\n\n"
				"Information:\n"
				"To avoid doing this again, I inform\n"
				"you that you are only limited to 5\n"
				"test case per program run.\n"
				"Thank you\n\n"
				"Note:\n"
				"It is only a humor error message.\n"
				"If you find it offensive, please let me know.\n\n"
				);
		return 1;
	}
	printf("\n");

	for (int n = 0; n != T; n++) {
		for (int i = 0; i != 2; i++) {
			read_number(int_ptr[i], 2);
		}
		
		kngdm = malloc(sizeof(Kingdom) * 26);
		make_matrix_2d(&the_map, N, M);
		
		fill_matrix_2d(the_map, N, M);
		
		explore_the_map(the_map, N, M, kngdm);
		
		#ifdef DEBUG_MODE
		// Print the map after exploration
		printf("=====Map after being explored=====\n");
		print_matrix_2d(the_map, N, M);
		
		// Faction list before sorting out
		printf("=====Faction list before sorting out=====\n");
		print_faction_list(kngdm);
		#endif
		
		sort_out_armies(kngdm);
		
		#ifdef DEBUG_MODE
		// Faction list after sorting out
		printf("=====Faction list after sorting out=====\n");
		print_faction_list(kngdm);
		#endif
		
		printf("Case %d:\n", n + 1);
		print_kingdom_report(kngdm, N, M);
		
		destroy_matrix_2d(the_map);
		free(kngdm);
	}
	
	return 0;
}


int main(int argc, char *argv[]) {
	
	set_test_case();

    return 0;
}


