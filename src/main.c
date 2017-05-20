#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[])
{
	FILE *in = fopen("text.txt", "r");
	if (in == NULL) {
		return 0;
	}
	char *word, *text = NULL;
	size_t len = 0;

	word = argv[1];

	getline(&text, &len, in);
	printf("%s", text);

	printf("%d\n", crawling_dir());

	fclose(in);

	printf("%u\n", hash_f(word));

	search(word, text);

	/*arr_suf = compute_good_suffix(text);
	for (int i = 0; i < strlen(text) - 1; i++) {
		printf("%d ", arr_suf[i]);
	}
	printf("\n");*/

	//free(text);
	//fclose(in);
	return 0;
}


