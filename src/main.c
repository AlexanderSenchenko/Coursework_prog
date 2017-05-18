#include <stdio.h>
#include <string.h>
#include "main.h"

//Разобраться как точно работае функция getline.
//По первым ощущениям очень упрощает жизнь,
//в плане того что она сама занимается выделением и 
//перераспределением памяти при считывании текста.
//Так же был кондидат fread.
int main(int argc, char *argv[])
{
	FILE *in = fopen("test.txt", "r");
	if (in == NULL) {
		return 0;
	}
	char *word, *text = NULL;
	//int *arr_suf;
	size_t len = 0;

	word = argv[1];
	printf("%s", word);
	printf("\n");

	getline(&text, &len, in);
	printf("%s", text);

	printf("%d\n", hash_f(word));

	search(word, text);

	/*arr_suf = compute_good_suffix(text);
	for (int i = 0; i < strlen(text) - 1; i++) {
		printf("%d ", arr_suf[i]);
	}
	printf("\n");*/

	fclose(in);
	return 0;
}


