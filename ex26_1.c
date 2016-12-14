#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include "dbg.h"

#define MAX_DATA 100
#define MAX_STRINGS 10

/* 
	read_in_search reads in user input. 
	
	-The user input is a set of strings separated
	by spaces.
	
	-Each char of this input is placed contiguously
	in memory (to_search), with each set of chars (forming a string)
	separated by a null byte.
	
	-Additionally, an index array (idx) is used to store the
	locations in to_search where each string begins 
*/

int read_in_search(char *to_search, int *idx)
{
	int stop = 0; /* while loop condition */
	int char_num = 0; /* location in to_search */
	int i = 0; /* location in idx */
	idx[i] = char_num; 
	char c = '\0';
	
	while (stop == 0) {
		c = fgetc(stdin); 
		check(c, "Character not copied.");
		
		switch (c) {
			case ' ':
				to_search[char_num] = '\0'; 
				i++;
				idx[i] = char_num + 1;
				break;
				
			case '\n':
				stop = 1;
				break;
			
			case '\0':
				sentinel("Found null byte.");
				
			default:
				to_search[char_num] = c;
		}	
		char_num++;
	}
	
	return i + 1;
	
error:
	return -1;
}
				

int main(int argc, char *argv[])
{
	char *to_search = malloc(MAX_DATA * sizeof(char)); /* create place for input to be stored */
	int *idx = malloc(MAX_STRINGS * sizeof(int)); /* create a place to store string locations */
	
	printf("What would you like to search for? "); /* prompt user */
	int count = read_in_search(to_search, idx); /* read what the user has inputted */
	check(count >= 0, "Read in failed."); 

	/* 
		Outer loop represents which string is being printed.
		Inner loop represents which character. 
		Inner loop stops when it finds a null byte.
		Space is printed after each string. 
	*/
	for (int i = 0; i < count; i++) { 
		for (int j = idx[i]; to_search[j] != '\0'; j++) { 
			printf("%c", to_search[j]); 
		}
		printf(" "); 
	}
	printf("\n"); 
	
	free(to_search);
	free(idx);
	
	return 0;
	
error:
	if (to_search) free(to_search);
	if(idx) free(idx);
	return -1;
}
