/* File:         src/matrix2d.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  11/09/2022-11:44:53-AM
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix2d.h"
#include "readstdin.h"

/* Maximum size of rows and columns that function make_matrix_2d() can
 * create.
 */
#define MAX_ROW_SIZE	50
#define MAX_COL_SIZE	50

int make_matrix_2d(char ***matrix, size_t const row_size, size_t const col_size) {
	/* Legend:
	 * Values for the *status* variable.
	 * 1 - signifies the number of rows or columns or both that have
	 *     reached or surpassed the maximum allowed count.
	 * 2 - signifies the failed allocation of the matrix's row.
	 * 3 - signifies the failed allocation of the matrix's column.
	 */
	int status;
	
	if (row_size > MAX_ROW_SIZE || col_size > MAX_COL_SIZE) { status = 1; goto make_matrix_2d_error; }
	
	// Allocate a memory for how many rows the matrix should have.
	*matrix = malloc(sizeof(char*) * row_size);
	if (*matrix == NULL) { status = 2; goto make_matrix_2d_error; }

	/* Allocate a memory for each of the the row of the matrix. This
	 * will be the number of columns of the matrix.
	 */
	for (int y = 0; y != row_size; y++) {
		(*matrix)[y] = malloc(sizeof(char) * col_size);
		if ((*matrix)[y] == NULL) { status = 3; goto make_matrix_2d_error; }
	}

	return 0;

	make_matrix_2d_error:;
	return status;
}


void destroy_matrix_2d(char **matrix) {
	free(matrix);
	matrix = NULL;
}


static void free_get_line(char *ptr) {
	free(ptr);
	ptr = NULL;
}


int fill_matrix_2d(char **matrix, size_t const row_size, size_t const col_size) {
	/* Legend:
	 * Values for the *status* variable.
	 * 1 - indicates a failed memory allocation that will be used by
	 *     function read_str() to store the string from stdin.
	 * 2 - indicates a failure of reading string from stdin.
	 */
	int i = 0, status;
	char *temp = malloc(sizeof(char) * col_size);
	
	if (temp == NULL) { status = 1; goto fill_matrix_2d_error; }
	while (true) {
		printf("> ");
		status = read_str(temp, col_size);
		if (status != 0) { status = 2; free_get_line(temp); goto fill_matrix_2d_error; }
		strcpy(matrix[i], temp);
		i++;

		if (i == row_size) { break; }
	}
	
	free_get_line(temp);
	return 0;
	
	fill_matrix_2d_error:;
	return status;
}


int print_matrix_2d(char **matrix, size_t const row_size, size_t const col_size) {
	if (matrix == NULL) {
		fprintf(stderr, "No data is found to print!\n");
		return 1;
	}
	else {
		for (int i = 0; i != row_size; i++) {
			printf("%s\n", matrix[i]);
		}
		printf("\n");
	}
	
	return 0;
}


