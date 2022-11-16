/* File:         src/readstdin.h
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  11/09/2022-01:33:02-PM
 */

#ifndef READSTR_H
#define READSTR_H

/* This function reads a string of character from stdin until str_size.
 * If the string input is beyond what is indicated on str_size, the
 * remaining characters from string input are discarded.
 *
 * Return:
 * If the function succeeds returns zero else, returns a non-negative value,
 * and sets *destination* parameter to NULL.
 */
int read_str(char *destination, size_t str_size);


/* This function reads a numeric  value from stdin until digit.
 * If the numeric input is beyond what is indicated on digit, the
 * remaining digits from input are discarded.
 *
 * Return:
 * If the function succeeds returns zero else, returns a non-negative value,
 * and sets *destination* parameter to NULL.
 */
int read_number(int *destination, int const digit);

#endif //READSTR_H_INCLUDED


