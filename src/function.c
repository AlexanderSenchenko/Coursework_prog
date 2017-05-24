#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>
#include <sys/types.h>
#include "main.h"

#define CSI "\x1B\x5B"

char colors[][5] = {
"0;30", /* Black */ "1;30", /* Dark Gray */
"0;31", /* Red */ "1;31", /* Bold Red */
"0;32", /* Green */ "1;32", /* Bold Green */
"0;33", /* Yellow */ "1;33", /* Bold Yellow */
"0;34", /* Blue */ "1;34", /* Bold Blue */
"0;35", /* Purple */ "1;35", /* Bold Purple */
"0;36", /* Cyan */ "1;36" /*Bold Cyan */ };
int colors_sz = sizeof(colors) / sizeof(colors[0]);

unsigned int hash_f(const char *word)
{
	unsigned int h = 0;
	int n = strlen(word), m = n , d = 7;
	for (int i = 0; i < n; i++, m--) {
		if (word[i] == '\n') {
			continue;
		}
		h += word[i] * pow(d, m);
	}
	return h;
}

void search(const char *word, const char *text, int line)
{
	int n_text = strlen(text), buf_hash = 0;//, test = 0;
	int n_word = strlen(word), h_word;//, z = 0;
	char cpy[n_text], buf[1];
	Results *res = create_res(n_text / n_word);

	strcpy(cpy, text);
	h_word = hash_f(word);

	for (int i = 0; i < n_text - n_word; i++) {
		
		buf[0] = cpy[i + n_word];
		cpy[i + n_word] = '\0';
		buf_hash = hash_f(&cpy[i]);

		if (buf_hash == h_word) {
			if (strcmp(word, &cpy[i]) == 0) {
				printf("%s", text);
				res->column[res->n_column] = i;
				res->n_column++;
				/*for (int j = z; j < i; j++) {
					printf("%c", cpy[j]);
				}
				printf("%s%sm", CSI, colors[2]);
				for (int j = i; cpy[j] != '\0'; j++) {
					printf("%c", cpy[j]);
				}
				printf("%s0m", CSI);*/
				//for (int j = i + n_word; text[j] != '\0'; j++) {
				//	printf("%c", text[j]);
				//}
				//z = i + n_word;
				//printf("\n");
				//printf("%d~%d\n", i, test);
				//printf("%d\n", z + i);
				//printf("\n");
			}
		}
		//i += n_word;
		cpy[i + n_word] = buf[0];
		//if (z != 0) {
		//	//printf("\n");
		//}	
	
	}
	if (res->n_column != 0) {
		res->line = line;
		printf("//%d// ", res->line);
		printf("//%d// ", res->n_column);
		for (int i = 0; i < res->n_column; i++) {
			printf("%d ", res->column[i]);
		}
		printf("\n");
		output(res, text, n_word);
	}
	free_res(res);
}

void output(Results *res, const char *text, int n_word)
{
	int z = 0;
	for (int j = z; j < res->column[0]; j++) {
		printf("%c", text[j]);
	}
	printf("%s%sm", CSI, colors[2]);
	for (int j = res->column[0]; j < res->column[0] + n_word; j++) {
		printf("%c", text[j]);
	}
	printf("%s0m", CSI);
	z += res->column[0] + n_word;
	for (int j = z; j < res->column[1]; j++) {
		printf("%c", text[j]);
	}
	printf("%s%sm", CSI, colors[2]);
	for (int j = res->column[1]; j < res->column[1] + n_word; j++) {
		printf("%c", text[j]);
	}
	printf("%s0m", CSI);
	printf("\n");
	z = 0;
	for (int i = 0; i < res->n_column; i++) {
		//printf("##%d/%d##", z, res->column[i]);
		for (int j = z; j < res->column[i]; j++) {
			printf("%c", text[j]);
		}
		printf("%s%sm", CSI, colors[2]);
		for (int j = res->column[i]; j < res->column[i] + n_word; j++) {
			printf("%c", text[j]);
		}
		printf("%s0m", CSI);
		z = res->column[i] + n_word;
	}
	//printf("\n");
	printf("%s", &text[z]);
}

Results *create_res(int n)
{
	Results *res = malloc(sizeof(Results));
	if (res == NULL) {
		return NULL;
	}
	res->n_column = 0;
	res->column = malloc(sizeof(int) * n);
	if (res->column == NULL) {
		free(res);
		return NULL;
	}
	return res;
}

void free_res(Results *res)
{
	if (res != NULL) {
		free(res->column);
		free(res);
	}
}

void input(const char *file, const char *word)
{
	
	FILE *in = fopen(file, "r");
	int line = 0;
	if (!in) {
		perror(file);
		return;
	}

	fseek(in, 0, SEEK_END);
	long int len = ftell(in);
	rewind(in);

	char *text = malloc(sizeof(char) * len);
	while (fgets(text, len, in)) {
		line++;
		search(word, text, line);
	}

	if (fclose(in) == EOF) {
		printf("Error file end: %s\n", file);
		perror(file);
	}

	free(text);
}

char *create_new_path(const char *external_dir, const char *interior_dir)
{
	int ex_dir = strlen(external_dir);
	int int_dir = strlen(interior_dir);
	int new_path = ex_dir + int_dir;
	char *new_dir = malloc(sizeof(char) * new_path * 2);

	strcpy(new_dir, external_dir);
	new_dir[ex_dir] = '/';
	strcpy(&new_dir[ex_dir + 1], interior_dir);

	return new_dir;
}

int crawling_dir(const char *direct, const char *word)
{
	struct dirent *entry;
	char *new_path;
	DIR *dir = opendir(direct);
	if (!dir) {
		perror(direct);
		return -1;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.') {
			continue;
		}
		if (entry->d_type & DT_DIR) {
			new_path = create_new_path(direct, entry->d_name);
			crawling_dir(new_path, word);
			free(new_path);
		} else {
			new_path = create_new_path(direct, entry->d_name);
			printf("\nPath: %s\n", new_path);
			input(new_path, word);
			free(new_path);
		}
	}

	closedir(dir);

	return 0;
}
