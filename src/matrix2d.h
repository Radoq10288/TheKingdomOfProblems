/* File:         src/matrix2d.h
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  11/09/2022-11:44:53-AM
 */

#ifndef MATRIX2D_H
#define MATRIX2D_H

/* This function creates a 2D array of *char* data type only. User can
 * specify the number of rows and columns that is up to 50x50 to create.
 * It only accepts non-negative values as *row_size* and *col_size*.
 *
 * Return:
 * If the function succeeds returns zero else, returns a non-negative.
 */
int make_matrix_2d(char ***matrix, size_t const row_size, size_t const col_size);


/* Frees the memory allocated to the 2D array.
 */
void destroy_matrix_2d(char **matrix);


/* Fills the 2D matrix with *char* data from stdin.
 *
 * Return:
 * If the function succeeds return zero else, return non-negative value.
 */
int fill_matrix_2d(char **matrix, size_t const row_size, size_t const col_size);


/* For debugging purposes only.
 *
 * Prints the 2D matrix.
 */
int print_matrix_2d(char **matrix, size_t const row_size, size_t const col_size);

#endif //MATRIX2D_H_INCLUDED


