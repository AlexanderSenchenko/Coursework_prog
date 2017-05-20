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
	int n_text = strlen(text) - 1, buf_hash = 0;
	int n_word = strlen(word), h_word;
	char *cpy = malloc(sizeof(char) * n_word), buf[1];

	strncpy(cpy, text, n_text);
	h_word = hash_f(word);

	for (int i = 0; i < n_text - n_word; i++) {
		buf[0] = cpy[i + n_word];
		cpy[i + n_word] = '\0';
		buf_hash = hash_f(&cpy[i]);

		if (buf_hash == h_word) {
			if (strcmp(word, &cpy[i]) == 0) {
				printf("///%d///\n", i);
			}
		}

		cpy[i + n_word] = buf[0];
	}
	//free(cpy);
}

void input(const char *file, const char *word)
{
	FILE *in = fopen(file, "r");
	if (in == NULL) {
		fclose(in);
		return;
	}
	char *text = NULL;
	size_t len = 0;
	
	getline(&text, &len, in);

	search(word, text);
	//free(text);
	fclose(in);
}

int crawling_dir(const char *direct, const char *word)
{
	struct dirent *entry;
	DIR *dir = opendir(direct);
	if (!dir) {
		perror(direct);
		closedir(dir);
		return -1;
	}

	perror(direct);

	while ((entry = readdir(dir)) != NULL) {
		if (!strcmp(entry->d_name, ".")) {
			printf("\t\t---%s---\n", entry->d_name);
			continue;
		} else if (!strcmp(entry->d_name, "..")) {
			printf("\t\t---%s---\n", entry->d_name);
			continue;
		}
		if (entry->d_type == 4) {
			printf("dir %s\n", entry->d_name);
			printf("%d\n", crawling_dir(entry->d_name, word));
		} else {
			printf("file\n");
		//	input(entry->d_name, word);
		}
	}

	closedir(dir);

	return 0;
}
