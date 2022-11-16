/* File:         src/readstdin.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  11/09/2022-01:33:02-PM
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readstdin.h"


#define MAX_INPUT_SIZE	1024

int read_str(char *destination, size_t str_size) {
	/* Legend:
	 * Values of *status* variable.
	 * 1 - indicates a failed memory allocation. The allocated memory
	 *     will be used to store each of the characters getchar() reads.
	 * 2 - indicates an empty input from stdin.
	 */
	int ch, status = 0;
	char *input = malloc(sizeof(char) * MAX_INPUT_SIZE);
	unsigned int i = 0;
	
	if (input == NULL) { status = 1; goto read_str_error; }
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
					input[i] = '\0';
					break;
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
	
	if (i == 0) { status = 2; }
	strcpy(destination, input);
	free(input);
	input = NULL;
	
	read_str_error:;
	return status;
}


int read_number(int *destination, int const digit) {
	char temp[digit];
	printf("> ");
	if (read_str(temp, digit) != 0) { destination = NULL; return 1; }
	*destination = atoi(temp);

	return 0;
}


