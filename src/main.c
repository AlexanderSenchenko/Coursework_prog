#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[])
{
	char *word, *dir;
	word = argv[1];
	dir = argv[2];
	printf("Search '%s' in dir %s\n", word, dir);

	input("search/main.c", word);
	input("search/test.txt", word);
	printf("Hash word %u\n", hash_f(word));
	printf("Crawling %d\n", crawling_dir("search", word));
	return 0;
}


