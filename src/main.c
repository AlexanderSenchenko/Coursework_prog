#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include "main.h"

//Разобраться как точно работае функция getline.
//По первым ощущениям очень упрощает жизнь,
//в плане того что она сама занимается выделением и 
//перераспределением памяти при считывании текста.
//Так же был кондидат fread.
int main()
{
	FILE *in = fopen("test.txt", "r");
	if (in == NULL) {
		return 0;
	}
	char *path, *text = NULL;
	int *pi;
	size_t len = 0;

	path = input();
	if (path == NULL) {
		return 0;
	}
	printf("%s", path);

	getline(&text, &len, in);
	printf("%s", text);

	pi = compute_prefix_f(text);
	if (pi == NULL) {
		return 0;
	}

	for (int i = 0; i < 11; i++) {
		printf("%d ", pi[i]);
	}
	printf("\n");

	fclose(in);
	return 0;
}


