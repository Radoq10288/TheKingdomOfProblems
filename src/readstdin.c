/* File:         src/readstdin.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  11/09/2022-01:33:02-PM
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readstdin.h"


#define MAX_INPUT_SIZE	1024

int read_str(char *destination, size_t str_size) {
	/* Legend:
	 * Values of *status* variable.
	 * 1 - indicates str_size is larger than MAX_INPUT_SIZE.
	 * 2 - indicates a failed memory allocation. The allocated memory
	 *     will be used to store each of the characters getchar() reads.
	 * 3 - indicates an empty input from stdin.
	 * 4 - indicates input from stdin is more than the indicated in str_size.
	 */
	int ch, status = 0;
	if (str_size > MAX_INPUT_SIZE) { status = 1; goto read_str_error; }
	char *input = malloc(sizeof(char) * MAX_INPUT_SIZE);
	unsigned int i = 0;
	
	if (input == NULL) { status = 2; goto read_str_error; }
	while (true) {
		ch = getchar();
		
		if (ch != '\n' && i == str_size) {
			/* Issue:
			 * Due to the newline ('\n') character that is carried from
			 * the previous input to the next when running read_str()
			 * more than once which causes the following input to accept
			 * the newline ('\n') character.
			 *
			 * This is only based on my own observation on how getchar()
			 * reads each character from stdin. Its like getchar() is
			 * still reads characters from the previous line of input.
			 *
			 * Solution:
			 * This routine discards the excess characters until the
			 * newline ('\n') is encountered. These characters which is
			 * ignored by read_str() due to the specified number of
			 * characters ('str_size') to read.
			 */
			while (true) {
				ch = getchar();
				if (ch == '\n') {
					putchar('\b');
					input = "\0";
					status = 4;
					goto read_str_error;
				}
				putchar('\b');
			}
		}

		if ((ch == '\n' && i < str_size) || (ch == '\n' && i == str_size)) {
			input[i] = '\0';
			break;
		}
		
		input[i] = ch;
		i++;
	}
	
	if (i == 0) { status = 3; }
	strcpy(destination, input);
	free(input);
	input = NULL;
	
	read_str_error:;
	return status;
}


int read_number(int *destination, int const digit) {
	char temp[digit];
	switch (read_str(temp, digit)) {
		case 1: destination = NULL; return 1; break;	// digit is more than MAX_INPUT_SIZE.
		case 3: destination = NULL; return 2; break;	// empty input from stdin.
		case 4: destination = NULL; return 3; break;	// input is more than the value of digit.
	}
	
	for (int i = 0; temp[i] != '\0'; i++) {
		if (isdigit(temp[i]) == 0) { destination = NULL; return 4; }	// input is or has a non-numeric character.
	}
	
	*destination = atoi(temp);
	return 0;
}


