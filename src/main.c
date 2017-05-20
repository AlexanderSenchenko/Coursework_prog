#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[])
{
	char *word;
	word = argv[1];

	printf("Crawling %d\n", crawling_dir("search", word));

	input("search/main.c", word);
	//input("search/test.txt", word);
	//printf("Hash word %u\n", hash_f(word));
	return 0;
}


