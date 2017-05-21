#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>
#include <sys/types.h>

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

void search(const char *word, const char *text)
{
	printf("\n---Search---\n");
	int n_text = strlen(text) - 1, buf_hash = 0;
	int n_word = strlen(word), h_word;
	char cpy[n_text], buf[1];

	strcpy(cpy, text);
	h_word = hash_f(word);

	for (int i = 0; i < n_text - n_word; i++) {
		buf[0] = cpy[i + n_word];
		cpy[i + n_word] = '\0';
		buf_hash = hash_f(&cpy[i]);

		if (buf_hash == h_word) {
			if (strcmp(word, &cpy[i]) == 0) {
				printf("#%d#\n", i);
			}
		}

		cpy[i + n_word] = buf[0];
	}
	printf("---End search---\n\n");
}

void input(const char *file, const char *word)
{
	printf("\n/////Add text in: %s/////\n", file);
	FILE *in = fopen(file, "r");
	if (!in) {
		printf("Error begin file: %s\n", file);
		printf("/////End text: %s/////\n\n", file);
		return;
	} else {
		printf("Begin file: %s\n", file);
	}
	char *text, *estr;
	text = malloc(sizeof(char) * 50);
	if (text == NULL) {
		return;
	}	

	estr = fgets(text, 50, in);
	if (estr == NULL) {
		if (feof(in) != 0) {
			printf("Fail read: %s\n", file);
		} else {
			printf("Error fail read: %s\n",file);
		}
	}

	printf("Text: %s", text);
	printf("Len text: %d\n", strlen(text));

	if (fclose(in) == EOF) {
		printf("Error file end: %s\n", file);
	} else {
		printf("File end: %s\n", file);
	}
		
	search(word, text);
	free(text);
	printf("/////End text: %s/////\n", file);
}

char *create_new_path(const char *external_dir, const char *interior_dir) {
	int ex_dir = strlen(external_dir);
	int int_dir = strlen(interior_dir);
	int new_path = ex_dir + int_dir;
	char *new_dir = malloc(sizeof(char) * new_path);

	printf("\nDir %s\n", interior_dir);
	printf("Len 1 dir: %d\n", ex_dir);
	printf("Len 2 dir: %d\n", int_dir);
	printf("Len New path: %d\n", new_path);

	strcpy(new_dir, external_dir);
	new_dir[ex_dir] = '/';
	printf("Border: %c\n", new_dir[ex_dir]);
	strcpy(&new_dir[ex_dir + 1], interior_dir);

	printf("New dir: %s\n", new_dir);
	printf("Len dir cpy: %d\n", strlen(new_dir));
	return new_dir;	
}

int crawling_dir(const char *direct, const char *word)
{
	printf("\n|||||Crawling dir: %s|||||\n", direct);
	struct dirent *entry;
	DIR *dir = opendir(direct);
	if (!dir) {
		perror(direct);
		printf("|||||End crawling dir: %s|||||\n", direct);
		return -1;
	}

	perror(direct);

	while ((entry = readdir(dir)) != NULL) {
		if (!strcmp(entry->d_name, ".")) {
			continue;
		} else if (!strcmp(entry->d_name, "..")) {
			continue;
		}
		if (entry->d_type & DT_DIR) {
			char *new_path;
			new_path = create_new_path(direct, entry->d_name);
			printf("New path: %s\n", new_path);
			crawling_dir(new_path, word);
			free(new_path);
		} else {
			printf("\nFile: %s", entry->d_name);
			//input(entry->d_name, word);
		}
	}

	closedir(dir);
	printf("\n|||||End crawling dir: %s|||||\n", direct);

	return 0;
}
