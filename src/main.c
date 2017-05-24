#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[])
{
	char *word, *dir;
	int result;
	if (argc != 3) {
		printf("Invalid number of arguments\n");
		return 0;
	}
	word = argv[1];
	dir = argv[2];
	printf("Search '%s' in directory %s\n", word, dir);

	result = crawling_dir(dir, word, 0);
	if (result == -1) {
		perror(dir);
	} else {
		printf("\nTotal words found in derictori %s: %d\n", dir, result);
	}	
	return 0;
}


