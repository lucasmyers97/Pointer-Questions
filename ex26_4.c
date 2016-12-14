#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_STRINGS 30
#define MAX_CHARS 10

int read_in_search(char (*scan_ptr)[MAX_CHARS])
{
	int stop = 0;
	char c = '\0';
	int str_num = 0;
	int char_num = 0;
	
	while (stop == 0) {
		c = fgetc(stdin);
		
		switch (c) {
			case ' ':
				scan_ptr[str_num][char_num] = '\0';
				str_num++;
				char_num = 0;
				break;
				
			case '\n':
				scan_ptr[str_num][char_num] = '\0';
				stop = 1;
				break;
				
			case '\0':
				sentinel("Read in null byte.");
				
			default:
				scan_ptr[str_num][char_num] = c;
				char_num++;
		}
	}
	
	return str_num;
	
error:
	return -1;
}			

int main(int arc, char *argv[])
{
	char to_scan[MAX_STRINGS][MAX_CHARS];
	char (*to_scan_ptr)[MAX_CHARS] = to_scan;
	
	printf("What would you like to input? ");
	int count = read_in_search(to_scan_ptr);
	check(count >= 0, "Read in failed.");
	
	for (int i = 0; i <= count; i++) {
		printf("%s ", to_scan_ptr[i]);
	}
	
	printf("\n");

	return 0;
	
error:
	return -1;
}
