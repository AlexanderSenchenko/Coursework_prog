#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[])
{
	char *word, *dir;
	word = argv[1];
	dir = argv[2];
	printf("Search '%s' in directory %s\n", word, dir);

	if (crawling_dir(dir, word) == -1) {
		perror(dir);
	}
	return 0;
}


